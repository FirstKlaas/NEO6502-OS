#include <Arduino.h>

#define KBD   0xD010  // Address for the character buffer
#define KBDCR 0xD010  // Address for the character control register

#define FLAG_UNCONSUMED_KEY 0x80  // 1000 0000 / Bit 7

extern uint8_t regKBD; // place to store the current character
extern uint8_t regKBDCR; // place to store te keyboard control register 

void initKeyboard();
/**
 * @brief Checks, if a key has been pressed. 
 * If a key has been pressed, it will be stored in 
 * the global variable KBD and a bit flag in KBDCR
 * is set. While this bit is set, no other keyboard
 * inputs will be read from the serial buffer.
 * 
 */
void checkForKeyPressed();
