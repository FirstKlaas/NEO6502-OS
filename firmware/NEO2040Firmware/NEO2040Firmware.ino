//#include <Arduino.h>

#include "pico/stdlib.h"  // In Pico SDK

//#include "pico/stdlib.h"
#define DEBUG

#define uP_CLOCKCYCLE_PIN 23
#define uP_TICKCYCLE_PIN  29


// Board Manager
// https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
// Board: Raspberry Pi Pico

#include "hardware/timer.h"
#include <PicoDVI.h>

#include "memory.h"
#include "mos6502c.h"
#include "keyboard.h"
#include "datatypes.h"
#include "display.h"
#include "cia6526.h"

static TContext ctx;
static TContextPtr ctxPtr(&ctx);
static repeating_timer_t frame_timer;

unsigned long lastClockTS;
volatile bool needsDisplayUpdate;

bool frame_update_callback(struct repeating_timer *t) {
  const TContextPtr ctx((TContextPtr)t->user_data);
  needsDisplayUpdate = true;
  return true;
}

void setup() {
  needsDisplayUpdate = false;
  //Serial.begin(9600);
  //while (!Serial && millis() < 1000UL);
  sleep_ms(1000);
  //Serial.println("############ NEO6502 FirstKlaas OS v0.0.1 ############");

  ctx.clock_cycle = 0L;
  ctx.frame_number = 0L;
  ctx.cpu_running = true;
  
  initmemory(ctxPtr);
  setupCIAPins();
  initKeyboard(ctxPtr);
  initDisplay(ctxPtr);
  init6502(ctxPtr);
  initCIA(ctxPtr);

  pinMode(uP_CLOCKCYCLE_PIN, OUTPUT);
  gpio_put(uP_CLOCKCYCLE_PIN, false);
  pinMode(uP_TICKCYCLE_PIN, OUTPUT);
  gpio_put(uP_TICKCYCLE_PIN, false);

  reset6502();

  // Adding a repeating timer for the frame 
  // updates. We use a negative value, so the time between
  // calls is including the execution time
  //add_repeating_timer_us(-(FRAMETIME*1000), frame_update_callback, ctxPtr, &frame_timer);

  //Serial.println("Starting programm");
}


/**
 * Never gets called.
 */
void loop() {
  if ((millis() - lastClockTS) >= FRAMETIME) {
    lastClockTS = millis();
    updateDisplay(ctxPtr);
    raiseFrameRequest(ctxPtr);
  }
  checkCIA(ctxPtr);
  tick6502(ctxPtr);
}
