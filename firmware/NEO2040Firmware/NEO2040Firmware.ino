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

static TContext ctx;
static TContextPtr ctxPtr(&ctx);

unsigned long lastClockTS;

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

  pinMode(uP_CLOCKCYCLE_PIN, OUTPUT);
  gpio_put(uP_CLOCKCYCLE_PIN, false);
  pinMode(uP_TICKCYCLE_PIN, OUTPUT);
  gpio_put(uP_TICKCYCLE_PIN, false);

  reset6502();

  sleep_ms(2000);
  Serial.println("Starting programm");
}

void loop() {
  gpio_put(uP_TICKCYCLE_PIN, true);
  tick6502(ctxPtr);
  gpio_put(uP_TICKCYCLE_PIN, false);
  if ((millis() - lastClockTS) >= FRAMETIME) {
    lastClockTS = millis();
    gpio_put(uP_CLOCKCYCLE_PIN, true);
    //clearDisplay();
    drawSprites(ctxPtr);
    updateDisplay(ctxPtr);
    raiseFrameRequest(ctxPtr);
    gpio_put(uP_CLOCKCYCLE_PIN, false);
  }
  checkCIA(ctxPtr);
  
}
