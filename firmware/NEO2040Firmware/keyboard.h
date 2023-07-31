#include <Arduino.h>
#include "datatypes.h"

#define FLAG_UNCONSUMED_KEY 0x80  // 1000 0000 / Bit 7

void initKeyboard(THardwarePtr hardware);
/**
 * @brief Checks, if a key has been pressed. 
 * If a key has been pressed, it will be stored in 
 * the global variable KBD and a bit flag in KBDCR
 * is set. While this bit is set, no other keyboard
 * inputs will be read from the serial buffer.
 * 
 */
void checkForKeyPressed();


boolean readKeyboard(THardwarePtr hardware);
boolean writeKeyboard(THardwarePtr hardware);
