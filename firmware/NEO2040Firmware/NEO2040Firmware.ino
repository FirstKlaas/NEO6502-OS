//#include <Arduino.h>

#include "pico/stdlib.h"  // In Pico SDK

//#include "pico/stdlib.h"
#define DEBUG

#define uP_CLOCKCYCLE_PIN 23
#define uP_TICKCYCLE_PIN  29
#define CLOCKCYCLE_HIGH   true
#define CLOCKCYCLE_LOW    false
#define TICK_HIGH         true
#define TICK_LOW          false


// Board Manager
// https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
// Board: Raspberry Pi Pico

#include <PicoDVI.h>

#include "memory.h"
#include "mos6502c.h"
#include "keyboard.h"
#include "datatypes.h"
#include "display.h"
#include "cia6526.h"
#include "hardware/timer.h"

static TContext ctx;
static TContextPtr ctxPtr(&ctx);
static repeating_timer_t clock_timer, frame_timer;

unsigned long lastClockTS;

bool frame_update_callback(struct repeating_timer *t) {
  clearDisplay();
  drawSprites((TContextPtr)t->user_data);
  updateDisplay();
  raiseFrameRequest((TContextPtr)t->user_data);
  return true;
}

bool clock_cycle_callback(struct repeating_timer *t) {
  tick6502((TContextPtr)t->user_data);
  return true;
}

void setup() {
  Serial.begin(9600);
  while (!Serial && millis() < 10000UL);
  Serial.println("############ NEO6502 FirstKlaas OS v0.0.1 ############");

  ctx.clock_cycle = 0L;
  ctx.frame_number = 0L;

  initmemory(ctxPtr);
  setupCIAPins();
  initKeyboard(ctxPtr);
  initDisplay(ctxPtr);
  init6502(ctxPtr);
  initCIA(ctxPtr);

  
  gpio_init(uP_CLOCKCYCLE_PIN);
  gpio_set_dir(uP_CLOCKCYCLE_PIN, GPIO_OUT);
  gpio_put(uP_CLOCKCYCLE_PIN, CLOCKCYCLE_LOW);
  gpio_init(uP_TICKCYCLE_PIN);
  gpio_set_dir(uP_TICKCYCLE_PIN, GPIO_OUT);
  gpio_put(uP_TICKCYCLE_PIN, TICK_LOW);
  
  reset6502();

  sleep_ms(2000);
  Serial.println("Installing frame update timer");
  add_repeating_timer_us(-(FRAMETIME*1000), frame_update_callback, ctxPtr, &frame_timer);
  //add_repeating_timer_us(100, clock_cycle_callback, ctxPtr, &clock_timer);
  while (true) {
    gpio_put(uP_TICKCYCLE_PIN, TICK_HIGH);
    tick6502(ctxPtr);
    gpio_put(uP_TICKCYCLE_PIN, TICK_LOW);
    checkCIA(ctxPtr);
  }
}

void loop() {
  tick6502(ctxPtr);
  checkCIA(ctxPtr);
}
