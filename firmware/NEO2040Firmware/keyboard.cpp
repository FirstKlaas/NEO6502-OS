#include "keyboard.h"
#include "addr.h"

#define KBDDEBUG

#ifdef KBDDEBUG
char DEBUGMSG[50];
#endif

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
void initKeyboard(THardwarePtr hardware) {
    hardware->reg.KBD = 0x00;
    hardware->reg.KBDCR = 0x00;
    #ifdef KBDDEBUG
    Serial.println("Keyboard initlialized.");
    #endif
}

/**
 Called, when data shoul be written to memory.
 Checks, if one of the keyboard registers is addressed.
 If true, register management is done properly and true
 will be returned. False otherwise.
**/
boolean readKeyboard(THardwarePtr hardware) {
    if (hardware->address == REG_KBD_ADDR) {
      hardware->data = hardware->reg.KBD;
      // Reading the register value also clears the
      // IRQ flag (if set) in the control register.
      hardware->reg.KBDCR &= 0x7f;
      return true;
    };

    if (hardware->address == REG_KBDCR_ADDR) {
      hardware->data = hardware->reg.KBDCR;
      return true;
    };

    return false; 

}


inline __attribute__((always_inline))
bool irqSet(THardwarePtr h) {
  return (h->reg.KBDCR & REG_KBD_IRQ_FLAG);  
}

inline __attribute__((always_inline))
bool irqClear(THardwarePtr h) {
  return (~irqSet(h));  
}

boolean writeKeyboard(THardwarePtr hardware) {
    // No idea, if it makes sense to write to the keyboard
    // register from assembler code. But why not. We can change
    // things later down the road.
    // But, if the IRQ Bit is set, we are not allowed to write
    // to this register.
    if (hardware->address == REG_KBD_ADDR) {
      // Store only, if not IRQ Bit is set
      // In any case we will return true, to indicate that the
      // write request has been handled.
      if (irqClear(hardware)) hardware->reg.KBD = hardware->data;
      return true;
    };

    // Save data to the keyboard control register.
    // Bit 7 (the IRQ bit) is read only. Therefore
    // it is left changed.
    if (hardware->address == REG_KBDCR_ADDR) {
      hardware->reg.KBDCR = ((hardware->data & 0x7f) | (hardware->data & 0x80));
      return true;
    };

    return false; 
}

/**
 * @brief Checks the hardware serial, which
 * is connected to the keyboard, for a pressed
 * character. If a character is available, it
 * will be stored in the KEY register. But
 * only, if the flag has been cleared.
 * 
 */
void checkForKeyPressed(THardwarePtr hardware) {

    if (Serial.available()) {

        // First check for reset key (^R)
        // Not yet implemented. Code fpr ^R is 0x12

        // Test, if the interrupt has been cleared? 
        if ((hardware->reg.KBDCR & FLAG_UNCONSUMED_KEY) == ~FLAG_UNCONSUMED_KEY) {
            // There is no unconsumed character
            noInterrupts();
            hardware->reg.KBD = Serial.read();
            hardware->reg.KBDCR |= FLAG_UNCONSUMED_KEY;
            interrupts();
            #ifdef KBDDEBUG
            sprintf(DEBUGMSG, "Key pressed. Code is %d (or 0x%02X)", hardware->reg.KBD, hardware->reg.KBD);
            Serial.println(DEBUGMSG);
            #endif
        }
    }
}
