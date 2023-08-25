#include "keyboard.h"
#include "addr.h"

//#define DEBUG_KEYBOARD

/**
 * @brief Initializes the keyboard interface
 * If key has been pressed, it will be stored
 * in the key "register" and a the 
 * FAG_UNCONSUMED_FLAG will be set.
 * 
 * Ony one key at at time will be stored in the
 * register. It has to be read from the code
 * and the flad bit has to be cleared.  
 * 
 */
void initKeyboard(TContextPtr ctx) {
    ctx->memory[KBD] = 0x00;
    ctx->memory[KBDCR] = 0x00;
    #ifdef DEBUG_KEYBOARD
    Serial.println("Keyboard initlialized.");
    #endif
}

/**
 Called, when data shoul be written to memory.
 Checks, if one of the keyboard registers is addressed.
 If true, register management is done properly and true
 will be returned. False otherwise.
**/
boolean readKeyboard(TContextPtr ctx) {
    if (ctx->address == REG_KBD_ADDR) {
      ctx->data = ctx->memory[KBD];
      // Reading the register value also clears the
      // IRQ flag (if set) in the control register.
      ctx->memory[KBDCR] &= 0x7f;
      #ifdef DEBUG_KEYBOARD
      Serial.printf("readKeyboard: Key value read (0x%02X) and IRG flag cleared (0x%02X)", ctx->data, ctx->reg.KBDCR);
      #endif
      return true;
    };

    if (ctx->address == REG_KBDCR_ADDR) {
      ctx->data = ctx->memory[KBDCR];
      return true;
    };

    return false; 

}


inline __attribute__((always_inline))
bool irqSet(TContextPtr h) {
  return (h->memory[KBDCR] & REG_KBD_IRQ_FLAG);  
}

inline __attribute__((always_inline))
bool irqClear(TContextPtr h) {
  return (~irqSet(h));  
}

boolean writeKeyboard(TContextPtr ctx) {
    // No idea, if it makes sense to write to the keyboard
    // register from assembler code. But why not. We can change
    // things later down the road.
    // But, if the IRQ Bit is set, we are not allowed to write
    // to this register.
    if (ctx->address == REG_KBD_ADDR) {
      // Store only, if not IRQ Bit is set
      // In any case we will return true, to indicate that the
      // write request has been handled.
      if (irqClear(ctx)) {
        ctx->memory[KBD] = ctx->data;
      } else {
        #ifdef DEBUG_KEYBOARD
        Serial.println("writeKeyboard: Could not write to keyboard register, as the irg for existing key data is still unhandled.");
        #endif
      }
      return true;
    };

    // Save data to the keyboard control register.
    // Bit 7 (the IRQ bit) is read only. Therefore
    // it is left changed.
    if (ctx->address == REG_KBDCR_ADDR) {
      ctx->memory[KBDCR] = ((ctx->data & 0x7f) | (ctx->data & 0x80));
      return true;
    };

    return false; 
}

/**
 * @brief Checks the ctx serial, which
 * is connected to the keyboard, for a pressed
 * character. If a character is available, it
 * will be stored in the KEY register. But
 * only, if the flag has been cleared.
 * 
 */
void checkForKeyPressed(TContextPtr ctx) {

    if (Serial.available()) {

        // First check for reset key (^R)
        // Not yet implemented. Code fpr ^R is 0x12

        // Test, if the interrupt has been cleared? 
        if ((ctx->memory[KBDCR] & FLAG_UNCONSUMED_KEY) == ~FLAG_UNCONSUMED_KEY) {
            // There is no unconsumed character
            noInterrupts();
            ctx->memory[KBD] = Serial.read();
            ctx->memory[KBDCR] |= FLAG_UNCONSUMED_KEY;
            interrupts();
            #ifdef DEBUG_KEYBOARD
            Serial.printf("checkForKeyPressed: Key pressed. Code is [%d] (0x%02X)\n", ctx->memory[KBD], ctx->memory[KBD]);
            #endif
        } else {
            #ifdef DEBUG_KEYBOARD
            Serial.println("checkForKeyPressed: New key available, but there is still an unconsumed character in the register.");
            #endif          
        }
    }
}
