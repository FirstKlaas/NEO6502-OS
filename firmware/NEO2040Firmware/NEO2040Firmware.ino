//#include <Arduino.h>

#include "pico/stdlib.h"  // In Pico SDK

//#include "pico/stdlib.h"
#define DEBUG

#define uP_CLOCKCYCLE_PIN 23
#define uP_TICKCYCLE_PIN  29


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

volatile uint8_t blip;

static TContext ctx;
static TContextPtr ctxPtr(&ctx);
static repeating_timer_t clock_timer;

unsigned long lastClockTS;

bool clock_cycle_callback(struct repeating_timer *t) {
  blip++;
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

  /*
  gpio_init(uP_CLOCKCYCLE_PIN);
  gpio_set_dir(uP_CLOCKCYCLE_PIN, true);
  // pinMode(uP_CLOCKCYCLE_PIN, OUTPUT);
  gpio_put(uP_CLOCKCYCLE_PIN, false);
  pinMode(uP_TICKCYCLE_PIN, OUTPUT);
  gpio_put(uP_TICKCYCLE_PIN, false);
  */
  reset6502();

  sleep_ms(2000);
  Serial.println("Installing clock cycle timer");
  add_repeating_timer_us(-1000, clock_cycle_callback, ctxPtr, &clock_timer);
}

void loop() {
  tick6502(ctxPtr);
  if ((millis() - lastClockTS) >= FRAMETIME) {
    lastClockTS = millis();
    clearDisplay();
    drawSprites(ctxPtr);
    updateDisplay();
    raiseFrameRequest(ctxPtr);
    Serial.printf("Blip: %03d\n", blip);
  }
  checkCIA(ctxPtr);
  
}
