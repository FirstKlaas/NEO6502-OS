#ifndef DATATYPES_H
#define DATATYPES_H

#include <Arduino.h>

typedef struct Register_ {
  union {
    struct {
      uint8_t KBD;    // Keyboard register
      uint8_t KBDCR;  // Keyboard control register
    };
    uint8_t keyboardRegister[2];
  };
  union {
    struct {
      uint8_t DIS;    // Display Register
      uint8_t DISCR;  // Display control rgister
      uint8_t DISCMD;
      uint8_t DIS00;  // Display Data Register
      uint8_t DIS01;  // Display Data Register
      uint8_t DIS02;  // Display Data Register
      uint8_t DIS03;  // Display Data Register
      uint8_t DIS04;  // Display Data Register
      uint8_t DIS05;  // Display Data Register
      uint8_t DIS06;  // Display Data Register
      uint8_t DIS07;  // Display Data Register
    };
    uint8_t displayRegister[11];
  };
} TRegister;

// CIA Stuff

typedef struct {

  uint16_t timer_a_start_value;
  uint16_t timer_b_start_value;
  uint16_t timer_a_counter;
  uint16_t timer_b_counter; 
  uint8_t  flags;           // Source of the interrupt
  uint8_t  mask;            // enabled interupts
  boolean  timer_a_running;
  boolean  timer_b_running;   
  boolean  irq_active;      // IRQ is pending => IRQB is low

} CIA_t, *CIA_Ptr_t;

typedef struct HardwareType_ {
  uint16_t address;
  uint8_t data;
  uint8_t *memory;
  TRegister reg;
  CIA_t cia; 
  unsigned long clock_cycle;
} TContext, *TContextPtr;

#endif