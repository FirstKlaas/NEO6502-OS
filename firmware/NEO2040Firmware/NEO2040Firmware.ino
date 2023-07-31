//#include <Arduino.h>

#include "pico/stdlib.h" // In Pico SDK

//#include "pico/stdlib.h"
#define DEBUG

// Board Manager
// https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
// Board: Raspberry Pi Pico

#include <PicoDVI.h>

#include "memory.h"
#include "mos6502c.h"
#include "keyboard.h"
#include "datatypes.h"


static THardware hardware;
static THardwarePtr hardwarePtr(&hardware); 

// Pico HDMI for Olimex Neo6502 
static const struct dvi_serialiser_cfg dvi_cfg = { 
  .pio = DVI_DEFAULT_PIO_INST, 
  .sm_tmds = {0, 1, 2}, 
  .pins_tmds = {14, 18, 16}, 
  .pins_clk = 12, 
  .invert_diffpairs = true 
};
//DVIGFX8 display(DVI_RES_320x240p60, true, dvi_cfg);
//DVItext1 display(DVI_RES_640x480p60, dvi_cfg);

static DVItext1 display(DVI_RES_320x240p60, dvi_cfg);
// DVItext1

void setXPosImpl(uint8_t xpos) {
  display.setCursor(xpos, display.getCursorY()); 
}

void setup() 
{
  uint8_t cycle(0);
  Serial.begin(9600);
  while (!Serial && millis() < 10000UL);
  Serial.println("############ NEO6502 FirstKlaas OS v0.0.1 ############");
  // put your setup code here, to run once:

  hardware.clock_cycle = 0L;
  hardware.display.setXPos = setXPosImpl;
  
  initmemory(hardwarePtr);
  initKeyboard(hardwarePtr);
  init6502(hardwarePtr);
  reset6502();

  sleep_ms(500);
  display.setCursor(0, 2);
  display.setTextColor(0xfb00, 0x0000);
  display.println("Klaas Nebuhr ist FirstKlaas");
  display.println("Klaas Nebuhr ist FirstKlaas");
  display.println("Klaas Nebuhr ist FirstKlaas");
  display.println("Klaas Nebuhr ist FirstKlaas");
  for (int i=0; i<300; i++)
    tick6502(hardwarePtr);
}

void loop() {
  // put your main code here, to run repeatedly:
}
