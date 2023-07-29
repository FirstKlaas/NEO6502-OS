#include <Arduino.h>

#define DEBUG

#include "memory.h"
#include "mos6502c.h"
#include "keyboard.h"

void setup() 
{
  uint8_t cycle(0);
  Serial.begin(9600);
  while (!Serial && millis() < 10000UL);
  Serial.println("############ NEO6502 FirstKlaas OS v0.0.1 ############");
  // put your setup code here, to run once:
  
  initmemory();
  initKeyboard();
  init6502();
  reset6502();
  
  tick6502(cycle++);
  tick6502(cycle++);
  tick6502(cycle++);
  tick6502(cycle++);
  tick6502(cycle++);
  tick6502(cycle++);
  tick6502(cycle++);
  tick6502(cycle++);
  tick6502(cycle++);
  tick6502(cycle++);
  tick6502(cycle++);
  tick6502(cycle++);
  tick6502(cycle++);
  tick6502(cycle++);
  
  /*
  tick6502(0);
  */
}

void loop() {
  // put your main code here, to run repeatedly:
}
