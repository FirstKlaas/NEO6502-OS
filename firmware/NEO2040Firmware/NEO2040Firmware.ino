//#include <Arduino.h>

#include "pico/stdlib.h" // In Pico SDK

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
#include <Fonts/FreeMono12pt7b.h>
  
static TContext ctx;
static TContextPtr ctxPtr(&ctx); 

//#define FRAMERATE 10
//#define FRAME_DURATION_MS  10000 / FRAMERATE

unsigned long lastClockTS;

void setup() 
{
  uint8_t cycle(0);
  Serial.begin(9600);
  while (!Serial && millis() < 10000UL);
  Serial.println("############ NEO6502 FirstKlaas OS v0.0.1 ############");
  // put your setup code here, to run once:

  
  
  //display.setFont(&FreeMono12pt7b);
  ctx.clock_cycle = 0L;
  
  // Setting text color to amber 
  //display.setTextColor(convertColor565(255,191,0));
  //display.setTextColor(0xffff);
  
  initmemory(ctxPtr);
  initKeyboard(ctxPtr);
  initDisplay(ctxPtr);
  init6502(ctxPtr);
  reset6502();

  sleep_ms(2000);
  //printWelcomeMsg(ctxPtr);
  
  
  for (int i=0; i<15000; i++)
    tick6502(ctxPtr);
    updateDisplay();
    
}

void loop() {
  tick6502(ctxPtr);
  if ((millis() - lastClockTS) >= FRAMETIME) {
    updateDisplay();
    lastClockTS = millis();
  }
  // put your main code here, to run repeatedly:
}
