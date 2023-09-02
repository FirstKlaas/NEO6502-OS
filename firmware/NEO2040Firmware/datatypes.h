#ifndef DATATYPES_H
#define DATATYPES_H

#include <Arduino.h>

#define KBD    0xd010    // Keyboard regster
#define KBDCR  0xd011    // Keyboard control register
#define DIS    0xd012    // Display register
#define DISCR  0xd013    // Display control register
#define DISCMD 0xd014    // Display command register
#define DIS00  0xd015    // Data exchange register 
#define DIS01  0xd016    // Data exchange register 
#define DIS02  0xd017    // Data exchange register 
#define DIS03  0xd018    // Data exchange register 
#define DIS04  0xd019    // Data exchange register 
#define DIS05  0xd01A    // Data exchange register 
#define DIS06  0xd01B    // Data exchange register 
#define DIS07  0xd01C    // Data exchange register 

// CIA Stuff

typedef struct {

  uint16_t timer_a_start_value;
  uint16_t timer_b_start_value;
  uint16_t timer_a_counter;
  uint16_t timer_b_counter; 
  uint8_t  raised_interrupts;     // Source of the interrupt
  uint8_t  enabled_interrupts;    // enabled interupts
  boolean  timer_a_running;
  boolean  timer_b_running;   
  boolean  irq_active;            // IRQ is pending => IRQB is low

} CIA_t, *CIA_Ptr_t;

typedef struct HardwareType_ {
  uint16_t address;
  uint8_t data;
  uint8_t *memory;
  //TRegister reg;
  CIA_t cia; 
  unsigned long clock_cycle;
  unsigned long frame_number;
  bool cpu_running;
  unsigned long frame_update_time;
  bool irq_active;
} TContext, *TContextPtr;

#endif