#include "memory.h"


// Actually 64KB of memory allocated
uint8_t mem[MEMORY_SIZE];

/**
 * @brief Nothing to do so far.
 * In upcoming versions we will have addresses wil a special
 * meaning. So we might have to initialise somthing.
 * 
 */
void initmemory() {
  mem[0xFFFC] = 0xEA;
  mem[0xFFFD] = 0xEA;
  mem[0xFFFE] = 0xEA;
  mem[0xFFFF] = 0xEA;
  mem[0xEAEA] = 0xEA;
  mem[0xEAEB] = 0x4C;
  mem[0xEAEC] = 0xEA;
  mem[0xEAED] = 0xEA;

}

inline __attribute__((always_inline))
uint8_t rmem(uint16_t adr) {
    return mem[adr];
}

inline __attribute__((always_inline))
void wmem(uint16_t adr, uint8_t data) {
    mem[adr] = data;
}

/**
 * @brief Returns the data from the memory for the given
 * address. No checks are performed
 * 
 * @param address The address to look up
 * @return uint8_t The data from the memory
 */
uint8_t readFromMemory(const uint16_t address) {
    return mem[address];
}

/**
 * @brief Store data to the memory
 * 
 * @param address The address to store to
 * @param data The data to store.
 */
void writeToMemory(uint16_t address, uint8_t data) {
    mem[address] = data;
}
