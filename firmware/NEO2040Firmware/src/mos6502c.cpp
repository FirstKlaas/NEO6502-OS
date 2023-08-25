//
// Author: Rien Matthijsse
//
#include "mos6502c.h"

#include <pico/stdlib.h>
//#define CPUDEBUG

#define DELAY_FACTOR_SHORT() asm volatile("nop\nnop\nnop\nnop\nnop\n");
#define DELAY_FACTOR_LONG() asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

// # of clock cycles to keep rest pin low
#define RESET_COUNT 4

// mask used for the mux address/data bus: GP0-7
uint32_t BUS_MASK = 0xFF;


#ifdef CPUDEBUG
char CPUDEBUGMSG[50];
#endif

//
uint8_t resetCount;
boolean inReset = false;
uint8_t dataDir = 2;

/// <summary>
/// drive the clockpin
/// </summary>
/// <param name="enable"></param>
inline __attribute__((always_inline)) void setClock(boolean clock)
{
  gpio_put(uP_CLOCK, clock);
}

/// <summary>
/// drive the reset pin
/// </summary>
/// <param name="enable"></param>
inline __attribute__((always_inline)) void setReset(boolean reset)
{
  gpio_put(uP_RESET, reset);
}

/// <summary>
/// drive the enable pins
/// </summary>
/// <param name="enable"></param>
inline __attribute__((always_inline)) void setEnable(uint32_t enable)
{
  gpio_put_masked(en_MASK, enable);
}

/// <summary>
/// set direction of databus mux
/// </summary>
/// <param name="direction"></param>
inline __attribute__((always_inline)) void setDir(uint8_t direction)
{
  if (direction != dataDir)
  {
    switch (direction)
    {
    case OUTPUT:
      gpio_set_dir_masked(BUS_MASK, BUS_MASK);
      break;
    case INPUT:
      gpio_set_dir_masked(BUS_MASK, (uint32_t)0UL);
      break;
    }

    dataDir = direction;
  }
}

/// <summary>
/// read the R/W pin
/// </summary>
/// <returns></returns>
inline __attribute__((always_inline)) bool getRW()
{
  return gpio_get(uP_RW);
}

/// <summary>
/// read the address bus
/// </summary>
/// <returns></returns>
inline __attribute__((always_inline))
uint16_t
getAddress()
{
  // we are already in INPUT
  // setDir(INPUT);

  // read A0-7
  setEnable(en_A0_7);
  DELAY_FACTOR_SHORT();
  uint16_t addr = gpio_get_all() & BUS_MASK;

  // read A8-15
  setEnable(en_A8_15);
  DELAY_FACTOR_SHORT();
  addr |= (gpio_get_all() & BUS_MASK) << 8;

  return addr;
}

/// <summary>
/// read the databus
/// </summary>
/// <returns></returns>
inline __attribute__((always_inline))
uint8_t
getData()
{
  // we are already in INPUT
  // setDir(INPUT);

  setEnable(en_D0_7);
  DELAY_FACTOR_SHORT();
  uint8_t data = gpio_get_all() & BUS_MASK;

  return data;
}

/// <summary>
/// write the databus
/// </summary>
/// <param name="data"></param>
inline __attribute__((always_inline)) void putData(uint8_t data)
{

  setDir(OUTPUT);
  setEnable(en_D0_7);
  gpio_put_masked(BUS_MASK, (uint32_t)data);
}

/// <summary>
/// initialise the 65C02
/// </summary>
void init6502(TContextPtr ctx)
{
  // CLOCK
  pinMode(uP_CLOCK, OUTPUT);
  setClock(CLOCK_HIGH);

  // RESET
  pinMode(uP_RESET, OUTPUT);
  setReset(RESET_HIGH);

  // RW
  pinMode(uP_RW, INPUT_PULLUP);

  // BUS ENABLE
  gpio_init_mask(en_MASK);
  gpio_set_dir_out_masked(en_MASK); // enable as output
  setEnable(en_NONE);               // all high

  // ADDRESS
  // DATA
  gpio_init_mask(BUS_MASK);
  setDir(INPUT);
}

/// <summary>
/// reset the 65C02
/// </summary>
void reset6502()
{
  setReset(RESET_LOW);

  resetCount = RESET_COUNT;
  inReset = true;
}

/// <summary>
/// clock cycle 65C02
/// </summary>
// inline __attribute__((always_inline))
void tick6502(TContextPtr ctx)
{
  uint8_t data(0);
  uint16_t address(0);

  setEnable(en_NONE); // all high

  //------------------------------------------------------------------------------------
  setClock(CLOCK_LOW);
  // set INPUT
  setDir(INPUT);

  DELAY_FACTOR_LONG();

  //------------------------------------------------------------------------------------
  setClock(CLOCK_HIGH);

  DELAY_FACTOR_SHORT();


  ctx->address = getAddress();
  ctx->clock_cycle++;

  // depending on the status of the R/W pin,
  // we read the data from memory and write to the bus
  // or we read the data from the bus and store it
  // to the memory.
  switch (getRW())
  {
  case RW_READ: // Read the data from memory and write to the bus
    readFromMemory(ctx); // data = @address
    putData(ctx->data);
    #ifdef CPUDEBUG
    sprintf(CPUDEBUGMSG, "%04d: 0x%04X | R | %02X", ctx->clock_cycle, ctx->address, ctx->data);
    Serial.println(CPUDEBUGMSG);
    #endif
    break;

  case RW_WRITE: // Read data from the bus and store it to the memory
    ctx->data = getData();
    writeToMemory(ctx);
    #ifdef CPUDEBUG
    sprintf(CPUDEBUGMSG, "%04d: 0x%04X | W | %02X", ctx->clock_cycle, ctx->address, ctx->data);
    Serial.println(CPUDEBUGMSG);
    #endif
    break;
  }


  // reset mgmt
  if (inReset)
  {
    if (resetCount-- == 0)
    {
      // end of reset
      setReset(RESET_HIGH);
      inReset = false;
      //        Serial.printf("RESET release\n");
    }
  }
}
