#include "cia6526.h"
#include <pico/stdlib.h>
#include "addr.h"

#define USE_IRQB

#define uP_IRQB   22      // UEXT
#define IRQ_LOW   false
#define IRQ_HIGH  true

#define TIMER_RESTART_FLAG 0x08 // Bit 3  : 00001000
#define ICR_IRQ_FLAG       0x80 // Bit 7  : 10000000
#define ICR_NO_IRQ         0x00 //
#define ICR_SOURCE_MASK    0x7f // Bit 0-6: 01111111

#define TIMER_A_INTERRUPT_FLAG  0x01
#define TIMER_B_INTERRUPT_FLAG  0x02
#define FRAME_INTERRUPT_FLAG    0x04
#define KBD_INTERRUPT_FLAG      0x08

#define CIA_IRQ_MASK            0x0f

void setIRQB(bool irqb)
{
#ifdef USE_IRQB
  gpio_put(uP_IRQB, irqb);
#endif
}

void requestFrameIinterrupt(TContextPtr ctx) {
  // When there is an unacknowledged IRQ,
  // ignore the request.
  if (ctx->cia.irq_active) return;
  ctx->cia.raised_interrupts |= FRAME_INTERRUPT_FLAG;
}

inline __attribute__((always_inline)) void trigger6502IRQ(TContextPtr ctx)
{
  // If IRQ is still active and not acknowledged,
  // ignore the IRQ request.
  //Serial.printf("CIA   : Setting IRQB LO. State is %d\n", ctx->cia.irq_active);
  if (ctx->cia.irq_active) return;
  ctx->cia.irq_active = true;
  setIRQB(IRQ_LOW); // IRQB is active low.
  //asm volatile("nop\nnop\nnop\nnop\nnop\n");
  /**
  setIRQB(IRQ_HIGH); // IRQB is active low.  
  asm volatile("nop\nnop\nnop\nnop\nnop\n");
  */
}

inline __attribute__((always_inline)) void release6502IRQ(TContextPtr ctx)
{
  if (!(ctx->cia.irq_active))
    return;
  // If IRQ is not active
  // ignore the IRQ request.
  //Serial.println("CIA   : Setting IRQB HI");
  setIRQB(IRQ_HIGH); // IRQB is active low.
  asm volatile("nop\nnop\nnop\nnop\nnop\n");
  ctx->cia.irq_active = false;
}

void setupCIAPins()
{
// Initializing IRQB line.
// Because it is active low, we set it high.
// Pin BUS.24 needs to we wired to UEXT.22
// to make it work.
#ifdef USE_IRQB
  pinMode(uP_IRQB, OUTPUT);
  setIRQB(IRQ_HIGH); // Because it's and active low signal.
#endif
}

/**
 * Initialization of the CIA Chip.
 * It's not the intention to emulate every feature and every behaviour
 * of the original chip. But to pick some useful things, leave some things
 * out and add some specific stuff. So maybe the name is a bit irritating.
 *
 * All the registers are set to default values. This function should be
 * called only once and after the memory has been initialized.
 *
 * As a difference to the original chip, this implementation handles also
 * keyboard and display interrupts. So we have only a single point for
 * interrupt management.
 *
 * The NEO6502 Rev A board has no out-of-the-box wiring for the IRQB pin.
 * To make this code work, you need to hookup the IRQB pin to one of the UEXT
 * pins and define the correct pin.
 */
void initCIA(TContextPtr ctx)
{
  ctx->cia.irq_active = false;
  ctx->cia.enabled_interrupts = 0;  // Which interrupts are allowed?
  ctx->cia.raised_interrupts = 0; // Which interrupts have been signaled?

  ctx->cia.timer_a_counter = 0;
  ctx->cia.timer_b_counter = 0;
  ctx->cia.timer_a_start_value = 0;
  ctx->cia.timer_b_start_value = 0;
  ctx->cia.timer_a_running = false;
  ctx->cia.timer_b_running = false;
}

/**
 * Check, if a write request to memory is handled by the CIA.
 */
boolean memWriteCIA(TContextPtr ctx)
{
  if (ctx->address < REG_CIA_PRA || ctx->address > REG_CIA_CRB)
    return false; // Not our business

  //Serial.printf("CIA     : Writing %02x to %04x\n", ctx->data, ctx->address);
  switch (ctx->address)
  {
  case REG_CIA_ICR:
    ctx->memory[ctx->address] = ctx->data;
    if (ctx->data & 0x80)
    {
      // Source bit (Bit7) equals 1: Every set bit (1) in data sets the corresponding
      // bit in irq mask
      ctx->cia.enabled_interrupts |= (ctx->data & ICR_SOURCE_MASK);
    }
    else
    {
      // Source bit is 0: Every set bit (1) clears the corresponding
      // bit in irq mask
      ctx->cia.enabled_interrupts &= ((~ctx->data) & ICR_SOURCE_MASK);
    };
    break;
  case REG_CIA_TA_LO:
    // Setting the start time for timer a (low byte)
    ctx->cia.timer_a_start_value = ((ctx->cia.timer_a_start_value & 0xff00) | ctx->data);
    //Serial.printf("Timer A startvalue (setlo): %04x\n", ctx->cia.timer_a_start_value);
    break;
  case REG_CIA_TA_HI:
    // Setting the start time for timer a (high byte)
    ctx->cia.timer_a_start_value = ((ctx->cia.timer_a_start_value & 0x00ff) | (ctx->data << 8));
    //Serial.printf("Timer A startvalue (sethi): %04x\n", ctx->cia.timer_a_start_value);
    if (!ctx->cia.timer_a_running)
    {
      // IF timer is not running set also the highbyte of the counter
      ctx->cia.timer_a_counter = ((ctx->cia.timer_a_counter & 0xf0) | ctx->data);
    }
    break;
  case REG_CIA_TB_LO:
    // Setting the start time for timer B (low byte)
    ctx->cia.timer_b_start_value = ((ctx->cia.timer_b_start_value & 0xf0) | ctx->data);
    break;
  case REG_CIA_TB_HI:
    // Setting the start time for timer B (high byte)
    ctx->cia.timer_b_start_value = ((ctx->cia.timer_b_start_value & 0xf0) | ctx->data);
    if (!ctx->cia.timer_b_running)
    {
      // IF timer is not running set also the highbyte of the counter
      ctx->cia.timer_b_counter = ((ctx->cia.timer_b_counter & 0xf0) | ctx->data);
    }
    break;

  case REG_CIA_CRA:
    ctx->cia.timer_a_running = (ctx->data & 1);
    //Serial.printf("Timer a is running: %d\n", ctx->cia.timer_a_running);
    if (ctx->data & 0x10)
    {
      // Load latch values into timer
      ctx->cia.timer_a_counter = ctx->cia.timer_a_start_value;
      //Serial.printf("Timer A counter loaded from latch %05d \n", ctx->cia.timer_a_counter);
    }
    ctx->memory[ctx->address] = ctx->data;
    break;

  case REG_CIA_CRB:
    ctx->cia.timer_b_running = (ctx->data & 1);
    //Serial.printf("Timer B is running: %d", ctx->cia.timer_a_running);
    if (ctx->data & 0x10)
    {
      // Load latch values into timer
      ctx->cia.timer_b_counter = ctx->cia.timer_b_start_value;
      //Serial.printf("Timer B counter loaded from latch %05d \n", ctx->cia.timer_b_counter);
    }
    ctx->memory[ctx->address] = ctx->data;
    break;

  default:
    ctx->memory[ctx->address] = ctx->data;
    break;
  };
  return true;
}

boolean memReadCIA(TContextPtr ctx)
{
  if (ctx->address < REG_CIA_PRA || ctx->address > REG_CIA_CRB)
    return false; // Not our business

  switch (ctx->address)
  {
  // Set the IRQ signaling flag (mask & flags > 0)
  case REG_CIA_ICR:
    if (ctx->cia.raised_interrupts & ctx->cia.enabled_interrupts)
    {
      ctx->data = ICR_IRQ_FLAG;
    }
    else
    {
      ctx->data = ICR_NO_IRQ;
    };
    // Set the source bits
    ctx->data |= (ctx->cia.raised_interrupts & CIA_IRQ_MASK);
    // So the valid information is returned, but only
    // once.
    // Reading this register automatically clears the
    // interrupt flags and clears the IRQB interrupt.
    ctx->cia.raised_interrupts = 0;

    // Reading also releases the IRQB line and
    // serves as an aknowledgement for the irq.
    release6502IRQ(ctx);

  default:
    ctx->data = ctx->memory[ctx->address];
  };
  return true;
}

/**
* Checks the state of all the registers and hardware to
* see, if an interrupt must be triggered or handled or
* whatsoever. For the timers, the implementation followed
* the documentation of the original CIA chip.
*
* Further reading: https://www.c64-wiki.de/wiki/CIA#CIA_1
*
* TODO:
* What to do, if we triggered an irq (setting IRQB to low) and another 
* "interrupt" occurs. Will it be thrown away? Or triggered after the first has been cleared?
* As an example. Timer B gets an underflow while the irq routine for timer A is still doing things.
*
* TODO:
* Serial stuff not implemented.
*
* TODO:
* Clock stuff not implemented.
*/
void checkTimer(TContextPtr ctx) {
  if (ctx->cia.timer_a_running) {
    //Serial.printf("CIA: Timer a is running: %04x [%03d]", ctx->cia.timer_a_counter, ctx->cia.enabled_interrupts);
    if (ctx->cia.timer_a_counter == 0) {
      //Serial.printf("Time A is up. CIA_CRA: 0xdc0e = 0x%02x\n",ctx->memory[REG_CIA_CRA]);
      // Next decrement would generate an underflow (in a signed value)
      // Trigger IRQ (if endabled)
      // Check, if we need to restart the timer.
      if (ctx->memory[REG_CIA_CRA] & TIMER_RESTART_FLAG)
      {
        //Serial.println("Stopping timer A");
        ctx->cia.timer_a_running = false;
      }
      else
      {
        //Serial.println("Restarting timer A. Not actively stopping.");
        ctx->cia.timer_a_counter = ctx->cia.timer_a_start_value;
      };
      //Serial.printf("IRQ Mask: %02x\n", ctx->cia.enabled_interrupts);
      if (ctx->cia.enabled_interrupts & TIMER_A_INTERRUPT_FLAG)
      {
        // Timer A interrupts are enabled
        // Setting the source of the IRQ
        ctx->cia.raised_interrupts |= TIMER_A_INTERRUPT_FLAG;
        // Now trigger the interrupt, by pulling IRQB low.
        // It will stay low, until the IRQ has been aknowledged
        //Serial.println("BOOOOOOM. Timer A has underflow.");
      }
      else
      {
        //Serial.println("Timer A underflow, but IRQ not enabled.");
      }
    }
    else
    {
      ctx->cia.timer_a_counter--;
      // Serial.printf("Counter: %06d", ctx->cia.timer_a_counter);
    }
  };

  // -----------------------------------------------
  // Timer B
  // -----------------------------------------------
  if (ctx->cia.timer_b_running)
  {
    // Serial.printf("CIA: Timer B is running: %04x [%03d]", ctx->cia.timer_B_counter, ctx->cia.enabled_interrupts);
    if (ctx->cia.timer_b_counter == 0)
    {
      //Serial.printf("Time B is up. CIA_CRB: 0xdc0f = 0x%02x\n", ctx->memory[REG_CIA_CRB]);
      // Next decrement would generate an underflow (in a signed value)
      // Trigger IRQ (if endabled)
      // Check, if we need to restart the timer.
      if (ctx->memory[REG_CIA_CRB] & TIMER_RESTART_FLAG)
      {
        //Serial.println("Stopping timer B");
        ctx->cia.timer_b_running = false;
      }
      else
      {
        //Serial.println("Restarting timer B. Not actively stopping.");
        ctx->cia.timer_b_counter = ctx->cia.timer_b_start_value;
      };
      //Serial.printf("IRQ Mask: %02x\n", ctx->cia.enabled_interrupts);
      if (ctx->cia.enabled_interrupts & TIMER_A_INTERRUPT_FLAG)
      {
        // Timer A interrupts are enabled
        // Setting the source of the IRQ
        ctx->cia.raised_interrupts |= TIMER_B_INTERRUPT_FLAG;
        // Now trigger the interrupt, by pulling IRQB low.
        // It will stay low, until the IRQ has been aknowledged
      } else {
        //Serial.println("Timer B underflow, but IRQ not enabled.");
      }
    }
    else
    {
      // At this point we know: counter > 0.
      ctx->cia.timer_b_counter--;
    }
  };
}

void raiseFrameRequest(TContextPtr ctx) {
  ctx->frame_number++;
    
  if (ctx->cia.irq_active) return;
  ctx->memory[DIS] = ctx->frame_number & 0xff;
  ctx->cia.raised_interrupts |= FRAME_INTERRUPT_FLAG;
}

void checkCIA(TContextPtr ctx) {
  // When an interrupt is active (aka IRQB low)
  // return whithout further checks.
  // So interrups may not happen during interrupts. 
  if (ctx->cia.irq_active) return;
  if (!ctx->cia.enabled_interrupts) return;
  checkTimer(ctx);

  if (ctx->cia.enabled_interrupts & ctx->cia.raised_interrupts) {
    trigger6502IRQ(ctx);
  } else {
    ctx->cia.raised_interrupts = 0;
  }
}
