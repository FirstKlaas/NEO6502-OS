#include "memory.h"
#include "keyboard.h"
#include "kernel.h"
#include "addr.h"

// Actually 64KB of memory allocated
uint8_t mem[MEMORY_SIZE];

/**
 * @brief Nothing to do so far.
 * In upcoming versions we will have addresses wil a special
 * meaning. So we might have to initialise somthing.
 *
 */
void initmemory(THardwarePtr hardware)
{
    hardware->memory = mem;
    mem[0xFFFC] = lowByte(kernel_start);
    mem[0xFFFD] = highByte(kernel_start);
    mem[0xFFFE] = lowByte(kernel_start);
    mem[0xFFFF] = highByte(kernel_start);

    // Write kernel code to ram. 
    for (uint8_t i=0; i<kernel_size; i++) {
      mem[kernel_start + i] = kernel_data[i];
    }
}

inline __attribute__((always_inline))
uint8_t
rmem(uint16_t adr)
{
    return mem[adr];
}

inline __attribute__((always_inline)) void wmem(uint16_t adr, uint8_t data)
{
    mem[adr] = data;
}

/**
 * @brief Returns the data from the memory for the given
 * address. No checks are performed
 *
 * @param address The address to look up
 * @return uint8_t The data from the memory
 */
void readFromMemory(THardwarePtr hardware)
{
    if (hardware->address == REG_KBD_ADDR) {
      hardware->data = hardware->reg.KBD;
    }
    if (hardware->address == REG_KBD_ADDR) {
      hardware->data = hardware->reg.KBD;
    }
    hardware->data = hardware->memory[hardware->address];
}

/**
 * @brief Store data to the memory
 *
 * @param address The address to store to
 * @param data The data to store.
 */
void writeToMemory(THardwarePtr hardware)
  {
    if (writeKeyboard(hardware)) return;
    hardware->memory[hardware->address] = hardware->data;
}
