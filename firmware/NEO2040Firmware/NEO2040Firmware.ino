//#include <Arduino.h>
#include "pico/stdio.h"
#include "pico/stdlib.h"  // In Pico SDK

#ifdef USE_SPI
#include "hardware/spi.h"
#include "pico/binary_info.h"
#define BUF_LEN 10
#endif 

#define DEBUG

#define uP_CLOCKCYCLE_PIN 23
#define uP_TICKCYCLE_PIN  29


// Board Manager
// https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
// Board: Raspberry Pi Pico

#include "hardware/timer.h"
#include <PicoDVI.h>

#include "memory.h"
#include "mos6502c.h"
#include "keyboard.h"
#include "datatypes.h"
#include "display.h"
#include "cia6526.h"

static TContext ctx;
static TContextPtr ctxPtr(&ctx);
static repeating_timer_t frame_timer;

unsigned long lastClockTS;
volatile bool needsDisplayUpdate;

#ifdef USE_SPI
uint8_t out_buf [BUF_LEN], in_buf [BUF_LEN];
#endif

bool frame_update_callback(struct repeating_timer *t) {
  const TContextPtr ctx((TContextPtr)t->user_data);
  if (!isFrameInterruptRaised(ctx)) {
    needsDisplayUpdate = true;
  };
  return true;
}


void setup() {
  needsDisplayUpdate = false;
  Serial.begin(9600);
  while (!Serial && millis() < 1000UL);
  //sleep_ms(1000);
  Serial.println("############ NEO6502 FirstKlaas OS v0.0.1 ############");

  ctx.clock_cycle = 0L;
  ctx.frame_number = 0L;
  ctx.cpu_running = true;
  ctx.irq_active = false;
  
  initmemory(ctxPtr);
  setupCIAPins();
  initKeyboard(ctxPtr);
  initDisplay(ctxPtr);
  init6502(ctxPtr);
  initCIA(ctxPtr);

  pinMode(uP_CLOCKCYCLE_PIN, OUTPUT);
  gpio_put(uP_CLOCKCYCLE_PIN, false);
  pinMode(uP_TICKCYCLE_PIN, OUTPUT);
  gpio_put(uP_TICKCYCLE_PIN, false);

  reset6502();

  // Adding a repeating timer for the frame 
  // updates. We use a negative value, so the time between
  // calls is including the execution time
  add_repeating_timer_us(-(FRAMETIME*1000), frame_update_callback, ctxPtr, &frame_timer);
  //Serial.begin(9600);
  
  //Serial.println("Starting programm");

  #ifdef USE_SPI
  // Enable SPI0 at 1 MHz
  spi_init (spi_default, 1 * 1000000);

  // Assign SPI functions to the default SPI pins
  gpio_set_function (PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
  gpio_set_function (PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
  gpio_set_function (PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
  gpio_set_function (PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI);

  // Initialize the buffers to 0.
  for (u_int8_t i = 0; i < BUF_LEN; ++i) {
    out_buf [i] = 0;
    in_buf [i] = 0;
  }
  spi_write_read_blocking (spi_default, out_buf, in_buf, 1);
  #endif
}


/**
 * Never gets called.
 */
void loop() {

  if (needsDisplayUpdate) {
    needsDisplayUpdate = false;
    lastClockTS = millis();
    updateDisplay(ctxPtr);
    ctx.frame_update_time = millis()-lastClockTS;
    raiseFrameRequest(ctxPtr);
  }
  checkCIA(ctxPtr);
  tick6502(ctxPtr);
}

int no_main() {
  setup();
  while (true) loop();
  return 0;
}
