//#include <Arduino.h>

#include "pico/stdlib.h"  // In Pico SDK

//#include "pico/stdlib.h"
#define DEBUG

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
  uint8_t cycle(0);
  Serial.begin(9600);
  while (!Serial && millis() < 10000UL)
    ;
  Serial.println("############ NEO6502 FirstKlaas OS v0.0.1 ############");

  ctx.clock_cycle = 0L;
  setupCIAPins();
  initmemory(ctxPtr);
  initKeyboard(ctxPtr);
  initDisplay(ctxPtr);
  init6502(ctxPtr);
  initCIA(ctxPtr);

  reset6502();

  sleep_ms(2000);
}

void loop() {
  tick6502(ctxPtr);
  checkCIA(ctxPtr);
  if ((millis() - lastClockTS) >= FRAMETIME) {
    animateAlien(ctxPtr);
    drawSprites(ctxPtr);
    updateDisplay();
    lastClockTS = millis();
  }
}
