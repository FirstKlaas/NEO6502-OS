#ifndef DATATYPES_H
#define DATATYPES_H

#include <Arduino.h>
#include <PicoDVI.h>

typedef struct Register_ {
  uint8_t KBD;    // Keyboard register
  uint8_t KBDCR;  // Keyboard control register
  uint8_t DIS;    // Display Register
  uint8_t DISCR;  // Display control rgister
  uint8_t DDRA;   // Data direction register
  uint8_t XPOS;   // cursor xpos
  uint8_t YPOS;   // cursor ypos
  uint8_t COLHI;   // COLOR HI
  uint8_t COLLO;   // COLOR LO
    
} TRegister;

typedef void (*TSetXPos)(uint8_t);

typedef struct Display_ {
  TSetXPos setXPos;
} TDisplay;

typedef struct HardwareType_ {
  uint16_t address;
  uint8_t data;
  uint8_t *memory;
  TRegister reg; 
  unsigned long clock_cycle;
  TDisplay display;
} THardware, *THardwarePtr;

#endif