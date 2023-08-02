#include "display.h"
#include "addr.h"
#include <PicoDVI.h>

#define DEBUG_DISPLAY

// Pico HDMI for Olimex Neo6502 
static const struct dvi_serialiser_cfg dvi_cfg = { 
  .pio = DVI_DEFAULT_PIO_INST, 
  .sm_tmds = {0, 1, 2}, 
  .pins_tmds = {14, 18, 16}, 
  .pins_clk = 12, 
  .invert_diffpairs = true 
};
DVIGFX8 display(DVI_RES_320x240p60, true, dvi_cfg);

struct {
  uint8_t x;
  uint8_t y;
  uint8_t offset_y;
  uint8_t offset_x;

  uint8_t textbuffer[LINES * LINECHARS];
  uint8_t currentColor;
  uint8_t currentXpos;
  uint8_t currentYpos;

  boolean needsRefresh;

} screendata;

uint8_t buffer[] = {12,15,67};

void initDisplay(TContextPtr ctx) {

  if (!display.begin()) {
    #ifdef DEBUG_DISPLAY
    Serial.println("ERROR: not enough RAM available");
    #endif
    for (;;);
  }
  screendata.offset_x = 1;
  screendata.offset_y = 1;
  
  display.setColor(0, 0x0000);   // Black
  display.setColor(1, 0XF800);   // Red
  display.setColor(2, 0x07e0);   // Green
  display.setColor(3, 0xffe0);   // Yellow
  display.setColor(4, 0x001f);   // Blue
  display.setColor(5, 0xFA80);   // Orange
  display.setColor(6, 0xF8F9);   // Magenta
  display.setColor(7, convertColor565(255,191,0));   // Amber
  
  display.setColor(255, 0xFFFF); // Last palette entry = White
  // Clear back framebuffer
  display.fillScreen(0);
  display.setFont();             // Use default font
  display.setCursor(0, 0);       // Initial cursor position
  display.setTextSize(1);        // Default size
  display.setTextWrap(false);
  display.swap(false, true);     // Duplicate same palette into front & back buffers
};

void setColor(uint8_t vColor) {
  screendata.currentColor = vColor;
  display.setTextColor(vColor);
}

void setCursor(uint16_t x, uint16_t y) {
  screendata.currentXpos = x;
  screendata.currentYpos = y;
  screendata.x = x * FONT_CHAR_WIDTH + screendata.offset_x;
  screendata.y = y * FONT_CHAR_HEIGHT  + screendata.offset_y;
  display.setCursor(screendata.x , screendata.y);
}

void writeChar(uint8_t c) {
  
}

char HEXCHARS[] = "0123456789ABCDEF";

void writeHex(uint8_t v) {
  display.write(HEXCHARS[(v >> 4) & 0x0f]);
  setCursor(screendata.currentXpos+1, screendata.currentYpos);
  display.write(HEXCHARS[v & 0x0f]);
  setCursor(screendata.currentXpos+2, screendata.currentYpos);
  updateDisplay();
}

void updateDisplay() {
  display.swap(true,false);
}

void printWelcomeMsg() {
  setCursor(0, 0);
  setColor(7); // AMBER
  display.print("NEO6502");
  setColor(255); // WHITE
  display.println(" - Cute little thing");
  setColor(2); // GREEN   
  setCursor(3,2);
  display.println("FirstKlaas Firmware");
  setCursor(0,5);
}

boolean memReadDisplayRegister(TContextPtr ctx) {
  if (ctx->address == REG_DIS_ADDR) {
    ctx->data = ctx->reg.DIS;
    return true;
  };

  if (ctx->address == REG_DISCR_ADDR) {
    ctx->data = ctx->reg.DISCR;
    return true;
  };

  return false;

}

boolean memWriteDisplayRegister(TContextPtr ctx) {
  if (ctx->address < REG_DIS_ADDR || ctx->address > REG_DIS_07_ADDR) return false;

  #ifdef DEBUG_DISPLAY
  Serial.printf("Display write: [%04X] := %02X\n", ctx->address, ctx->data);
  #endif

  // If the IRQ flag is set, we do not change anything, but
  // still the write request is handled.
  if (ctx->reg.DISCR & 0x80) {
    #ifdef DEBUG_DISPLAY
    Serial.println("IRQ Flag for display set. Register stay unchanged.");
    #endif
    return true;
  }

  switch (ctx->address) {
    case REG_DIS_ADDR:
      ctx->reg.DIS = ctx->data;
      return true;

    case REG_DISCR_ADDR:
      ctx->reg.DISCR = ctx->data;
      return true;

    case REG_DIS_00_ADDR:
      ctx->reg.DIS00 = ctx->data;
      // Test code
      writeHex(ctx->data);
      return true;

    case REG_DIS_01_ADDR:
      ctx->reg.DIS01 = ctx->data;
      return true;
      
    case REG_DIS_02_ADDR:
      ctx->reg.DIS02 = ctx->data;
      return true;
      
    case REG_DIS_03_ADDR:
      ctx->reg.DIS03 = ctx->data;
      return true;
      
    case REG_DIS_04_ADDR:
      ctx->reg.DIS04 = ctx->data;
      return true;
      
    case REG_DIS_05_ADDR:
      ctx->reg.DIS05 = ctx->data;
      return true;
      
    case REG_DIS_06_ADDR:
      ctx->reg.DIS06 = ctx->data;
      return true;
      
    case REG_DIS_07_ADDR:
      ctx->reg.DIS07 = ctx->data;
      return true;
      
  }

  return false;
}

uint16_t convertColor565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}