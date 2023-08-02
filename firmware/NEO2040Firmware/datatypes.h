#ifndef DATATYPES_H
#define DATATYPES_H

#include <Arduino.h>

typedef struct Register_ {
  uint8_t KBD;    // Keyboard register
  uint8_t KBDCR;  // Keyboard control register
  uint8_t DIS;    // Display Register
  uint8_t DISCR;  // Display control rgister
  uint8_t DIS00;  // Display Data Register
  uint8_t DIS01;  // Display Data Register
  uint8_t DIS02;  // Display Data Register
  uint8_t DIS03;  // Display Data Register
  uint8_t DIS04;  // Display Data Register
  uint8_t DIS05;  // Display Data Register
  uint8_t DIS06;  // Display Data Register
  uint8_t DIS07;  // Display Data Register
} TRegister;

typedef struct HardwareType_ {
  uint16_t address;
  uint8_t data;
  uint8_t *memory;
  TRegister reg; 
  unsigned long clock_cycle;
} TContext, *TContextPtr;

#endif