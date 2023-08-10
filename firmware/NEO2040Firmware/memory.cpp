#include "memory.h"
#include "keyboard.h"
#include "kernel.h"
#include "addr.h"
#include "display.h"
#include "cia6526.h"

//#define DEBUG_MEMORY

// Actually 64KB of memory allocated
uint8_t mem[MEMORY_SIZE];

/**
 * @brief Nothing to do so far.
 * In upcoming versions we will have addresses wil a special
 * meaning. So we might have to initialise somthing.
 *
 */
void initmemory(TContextPtr ctx)
{
    ctx->memory = mem;
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x08;
    mem[0xFFFE] = 0x00;
    mem[0xFFFF] = 0x08;
    load_kernel_to_memory(mem);
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
void readFromMemory(TContextPtr ctx)
{
    if (readKeyboard(ctx)) return;
    if (memReadDisplayRegister(ctx)) return;
    if (memReadCIA(ctx)) return;

    // No special register. Store to memory.
    #ifdef DEBUG_MEMORY
    Serial.printf("[R] memory[%04X] -> %02X\n", ctx->address, ctx->memory[ctx->address]);
    #endif
    ctx->data = ctx->memory[ctx->address];
    if (ctx->address > 0xff00) {
      Serial.printf("[R] memory[%04X] -> %02X\n", ctx->address, ctx->memory[ctx->address]);
      if (ctx->address == 0xfffc) Serial.println("Fetching program vector lowbyte.");
      if (ctx->address == 0xfffd) Serial.println("Fetching program vector highbyte.");
      if (ctx->address == 0xfffe) Serial.println("Fetching ISR vector lowbyte.");
      if (ctx->address == 0xffff) Serial.println("Fetching ISR vector highbyte.");
    };
}

/**
 * @brief Store data to the memory
 *
 * @param address The address to store to
 * @param data The data to store.
 */
void writeToMemory(TContextPtr ctx)
  {
    #ifdef DEBUG_MEMORY
    Serial.printf("[W] check [%04X] -> %02X\n", ctx->address, ctx->data);
    #endif
    if (writeKeyboard(ctx)) return;
    if (memWriteDisplayRegister(ctx)) return;
    if (memWriteCIA(ctx)) return;
    #ifdef DEBUG_MEMORY
    Serial.printf("[W] memory[%04X] <- %02X\n", ctx->address, ctx->data);
    #endif
    ctx->memory[ctx->address] = ctx->data;

    if (ctx->address == 0xfffe) Serial.printf("Setting ISR vector lowbyte. %02x\n", ctx->data);
    if (ctx->address == 0xffff) Serial.printf("Setting ISR vector highbyte. %02x\n", ctx->data);
}
