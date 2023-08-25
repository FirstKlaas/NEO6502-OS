#ifndef _MEMORY_h
#define _MEMORY_h

#include <Arduino.h>
#include "datatypes.h"

#define MEMORY_SIZE     0x10000   // 64k
#define RESET_VECTOR_LB 0xfffc
#define RESET_VECTOR_HB 0xfffd

#define MEMCR           0xd000    // Memory control register
#define BANKOUT_KERNAL  00000001b // If this bit is set in the MEMCR register,
                                  // The kernal rom space is no longer write protected
                                  // and treated as ram

#define KERNAL_START    0xe000    // Starting address of the kernal rom
#define KERNAL_SIZE     0

/**
 * @brief  Initialize emulated memory
 * 
 * Page 00 : 0000-00FF : Zeropage
 * Page 01 : 0100-01FF : Stack
 * 
 * 0xFFFC  : Resetvector Low Byte
 * 0xFFFD  : Resetvector High Byte
 * 
 * 0xD000 - 0xD00FF: Special registers
 * 
 * 0xD000 : MEMCR - Memory Control Register
 *  
 * 0xD010 : Keyboard Character 
 * 
 * E0000 - FEFF: Kernal routines
 * 
 */
void initmemory(TContextPtr ctx);

void readFromMemory(TContextPtr ctx);

void writeToMemory(TContextPtr ctx);

inline __attribute__((always_inline))
uint8_t rmem(uint16_t adr);

inline __attribute__((always_inline))
void wmem(uint16_t adr, uint8_t data);

#endif