#include <Arduino.h>

#include "keyboard.h"
#include "memory.h"

#define KBDDEBUG

uint8_t regKBD(0);    // place to store the current character
uint8_t regKBDCR(0);  // place to store te keyboard control register 

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
void initKeyboard() {
    regKBD   = 0x00;
    regKBDCR = 0x00;
    #ifdef KBDDEBUG
    Serial.println("Keyboard initlialized.");
    #endif
}

/**
 * @brief Checks the hardware serial, which
 * is connected to the keyboard, for a pressed
 * character. If a character is available, it
 * will be stored in the KEY register. But
 * only, if the flag has been cleared.
 * 
 */
void checkForKeyPressed() {

    if (Serial.available()) {

        // First check for reset key (^R)
        // Not yet implemented. Code fpr ^R is 0x12

        // Test, if the interrupt has been cleared? 
        if ((regKBDCR & FLAG_UNCONSUMED_KEY) == ~FLAG_UNCONSUMED_KEY) {
            // There is no unconsumed character
            noInterrupts();
            regKBD = Serial.read();
            regKBDCR |= FLAG_UNCONSUMED_KEY;
            interrupts();
            #ifdef KBDDEBUG
            sprintf(DEBUGMSG, "Key pressed. Code is %d (or 0x%02X)", regKBD, regKBD);
            Serial.println(DEBUGMSG);
            #endif
        }
    }
}
