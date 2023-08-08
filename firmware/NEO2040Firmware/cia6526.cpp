#include "cia6526.h"
#include <pico/stdlib.h>
#include "addr.h"


void initCIA(TContextPtr ctx) {
    ctx->cia.mask = 0;
    ctx->cia.flags = 0;
    ctx->cia.timer_a_counter = 0;
    ctx->cia.timer_b_counter = 0;
    ctx->cia.timer_a_start_value = 0;
    ctx->cia.timer_b_start_value = 0;
    ctx->cia.timer_a_running = false;
    ctx->cia.timer_b_running = false;
}

boolean memWriteCIA(TContextPtr ctx) {
  if (ctx->address < REG_CIA_PRA || ctx->address > REG_CIA_CRB) return false; // Not our business

  switch (ctx->address) {
    case REG_CIA_ICR:
      ctx->data = ctx->memory[ctx->address];
      if (ctx->data & 0x80) {
        // Source bit is 1: Every set bit (1) sets the corresponding
        // bit in irq mask
        ctx->cia.mask |= (ctx->data & 0x0f);

      } else {
        // Source bit is 0: Every set bit (1) clears the corresponding
        // bit in irq mask
        ctx->cia.mask &= ((~ctx->data) & 0xf);
      }; 
      break;
    case REG_CIA_TA_LO:
        // Setting the start time for timer a (low byte)
        ctx->cia.timer_a_start_value = ((ctx->cia.timer_a_start_value & 0xf0) | ctx->data);
        break;
    case REG_CIA_TA_HI:
        // Setting the start time for timer a (high byte)
        ctx->cia.timer_a_start_value = ((ctx->cia.timer_a_start_value & 0xf0) | ctx->data);
        if (!ctx->cia.timer_a_running) {
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
        if (!ctx->cia.timer_b_running) {
          // IF timer is not running set also the highbyte of the counter
          ctx->cia.timer_b_counter = ((ctx->cia.timer_b_counter & 0xf0) | ctx->data);
        }
        break;
        
    case REG_CIA_CRA:
        ctx->cia.timer_a_running = (ctx->data & 1);
        ctx->data = ctx->memory[ctx->address];
        break;

    case REG_CIA_CRB:
        ctx->cia.timer_b_running = (ctx->data & 1);
        ctx->data = ctx->memory[ctx->address];
        break;

    default:
        ctx->memory[ctx->address] = ctx->data;
        break;
  };
  return true;
}

boolean memReadCIA(TContextPtr ctx) {
  if (ctx->address < REG_CIA_PRA || ctx->address > REG_CIA_CRB) return false; // Not our business

  switch (ctx->address) {
    // Set the IRQ signaling flag (mask & flags > 0)
    case REG_CIA_ICR:
      if (ctx->cia.flags & ctx->cia.mask) {
        ctx->data = 0x80;
      } else {
        ctx->data = 0x00;
      };
      // Set the source bits
      ctx->data |= (ctx->cia.flags & CIA_IRQ_MASK);
      // Reading this register automatically clears the 
      // interrupt flags.
      ctx->cia.flags = 0;
      // TODO: The IRQB line should go high if an irg is pending.

    default:
      ctx->data = ctx->memory[ctx->address];
  };
  return true;
}

void checkCIA(TContextPtr ctx) {
  if (ctx->cia.timer_a_running) {
    Serial.printf("CIA: Timer a is running: %04x [%03d]", ctx->cia.timer_a_counter, ctx->cia.mask);
    if (ctx->cia.timer_a_counter == 0) {
      // Next decrement would generate an underflow (in a signed value)
      // Trigger IRQ (if endabled)
      if (ctx->cia.mask & TIMER_A_INTERRUPT_FLAG) {
        // Timer A interrupts are enabled
        // Set the source
        ctx->cia.flags |= TIMER_A_INTERRUPT_FLAG;
        // Now trigger the interrupt, by pulling IRQB low.
        // It will stay low, until the IRQ has been aknowledged
        Serial.println("BOOOOOOM");
      } 
    } else {
      ctx->cia.timer_a_counter--;
    }
  };

  if (ctx->cia.timer_b_running) {

  };
}