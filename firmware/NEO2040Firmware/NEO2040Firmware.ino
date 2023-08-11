//#include <Arduino.h>

#include "pico/stdlib.h"  // In Pico SDK

//#include "pico/stdlib.h"
#define DEBUG

#define uP_CLOCKCYCLE_PIN 28

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

void signalTest() {
  uint8_t test_pin(29);

  pinMode(test_pin, OUTPUT);
  while(true) {
    gpio_put(test_pin, true);
    Serial.print("1");
    delay(1000);
    gpio_put(test_pin, false);
    Serial.print("0");
    delay(1000);
  }
}


void setup() {
  uint8_t cycle(0);
  Serial.begin(9600);
  while (!Serial && millis() < 10000UL);
  Serial.println("############ NEO6502 FirstKlaas OS v0.0.1 ############");

  ctx.clock_cycle = 0L;
  setupCIAPins();
  initKeyboard(ctxPtr);
  initDisplay(ctxPtr);
  init6502(ctxPtr);
  initCIA(ctxPtr);
  initmemory(ctxPtr);

  pinMode(uP_CLOCKCYCLE_PIN, OUTPUT);
  gpio_put(uP_CLOCKCYCLE_PIN, false);

  reset6502();

  sleep_ms(2000);
  Serial.println("Starting programm");
}

void loop() {
  pinMode(uP_CLOCKCYCLE_PIN, OUTPUT);
  tick6502(ctxPtr);
  gpio_put(uP_CLOCKCYCLE_PIN, false);
  if ((millis() - lastClockTS) >= FRAMETIME) {
    lastClockTS = millis();
    raiseFrameRequest(ctxPtr);
    drawSprites(ctxPtr);
    updateDisplay();
  }
  checkCIA(ctxPtr);
}
