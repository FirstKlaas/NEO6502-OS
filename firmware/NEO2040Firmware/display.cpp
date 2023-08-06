#include "display.h"
#include "addr.h"
#include <PicoDVI.h>

//#define DEBUG_DISPLAY

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
  uint16_t x;         // X position in pixel
  uint16_t y;         // Y position in pixel
  uint8_t offset_y;   // Top offset in pixel
  uint8_t offset_x;   // Left offset in pixel

  uint8_t textbuffer[LINES * LINECHARS];
  uint8_t currentColor;
  uint8_t currentXpos;  // X position in character
  uint8_t currentYpos;  // Y position in character

  uint32_t needsRefresh;  // If > 0: Screen will be updated.

} screendata;

uint8_t buffer[] = {12,15,67};

void setColor(uint8_t vColor) {
  screendata.currentColor = vColor;
  Serial.printf("Setting color %02x %02d\n", vColor, vColor);
  display.setTextColor(vColor);
}


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
  
  display.setColor(255, 0xFFFF); // Last palette entry = Whi
  // Clear back framebuffer
  display.fillScreen(0);
  display.setFont();             // Use default font
  display.setCursor(0, 0);       // Initial cursor position
  display.setTextSize(1);        // Default size
  display.setTextWrap(false);
  display.swap(false, true);     // Duplicate same palette into front & back buffers
  screendata.needsRefresh = 0;
  display.setCursor(1,0);
  setColor(255);
};


void setCursor(TContextPtr ctx, uint8_t x, uint8_t y) {
  uint8_t ox(screendata.currentXpos);
  uint8_t oy(screendata.currentYpos);
  
  screendata.currentXpos = x;
  screendata.currentYpos = y;

  if (x >= LINECHARS && (ctx->reg.DISCR & AUTO_WRAP_FLAG)) {
    //screendata.currentXpos = 0;
    //screendata.currentYpos = y+1;
    screendata.currentXpos = (x % LINECHARS);
    screendata.currentYpos += (x / LINECHARS);
    /*
      Serial.printf("######## Wrapping: %02d %02d\n", x, y);
      Serial.printf("                   %02d %02d\n", screendata.currentXpos, screendata.currentYpos);
      Serial.printf("                   %02d %02d\n", ox, oy);
    */
  };

  screendata.x = screendata.currentXpos * FONT_CHAR_WIDTH + screendata.offset_x;
  screendata.y = screendata.currentYpos * FONT_CHAR_HEIGHT  + screendata.offset_y;

  display.setCursor(screendata.x , screendata.y);
  if (ctx->reg.DISCR && SHOW_CURSOR_FLAG) {
    // If there is a change and we show the cursor,
    // we need to refresh the screen.
    screendata.needsRefresh++;
  }
}

void setCursorX(TContextPtr ctx,uint8_t x) {
  setCursor(ctx, x, screendata.currentYpos);
}

void setCursorY(TContextPtr ctx,uint8_t y) {
  setCursor(ctx, screendata.currentXpos, y);
}

void getCursorX(TContextPtr ctx) {
  ctx->reg.DIS00 = screendata.currentXpos;
}

void getCursorY(TContextPtr ctx) {
  ctx->reg.DIS00 = screendata.currentYpos;
}

void updateDisplay() {
  if (screendata.needsRefresh) {
    display.swap(true,false);
  };
  screendata.needsRefresh = 0;
}

void writeChar(TContextPtr ctx, uint8_t c) {
  // Cursor position is off screen, do nothing
  if (screendata.currentXpos >= LINECHARS || screendata.currentYpos >= LINES) return;

  display.write(c);
  screendata.needsRefresh++;
  // Check, if we need to adjust the cursor
  // automatically
  if (ctx->reg.DISCR && ADJUST_CURSOR_FLAG) {
    setCursor(ctx, screendata.currentXpos+1, screendata.currentYpos);  
  }
}

char HEXCHARS[] = "0123456789ABCDEF";

void writeHex(TContextPtr ctx, uint8_t v) {
  display.write(HEXCHARS[(v >> 4) & 0x0f]);
  setCursor(ctx, screendata.currentXpos+1, screendata.currentYpos);
  display.write(HEXCHARS[v & 0x0f]);
  setCursor(ctx, screendata.currentXpos+2, screendata.currentYpos);
  updateDisplay();
}


void printWelcomeMsg(TContextPtr ctx) {
}

void executeCommand(TContextPtr ctx) {

  switch (ctx->reg.DISCMD) {
    case CMD_NOP:
      break;
    case CMD_SET_CURSOR_X:
      setCursorX(ctx, ctx->reg.DIS00);
      break;
    case CMD_SET_CURSOR_Y:
      setCursorY(ctx, ctx->reg.DIS00);
      break;
    case CMD_WRITE_CHAR:
      writeChar(ctx, ctx->reg.DIS00);
      screendata.needsRefresh++;
      break;
    case CMD_SET_FG_COLOR:
      Serial.printf("Set color %d\n", ctx->reg.DIS00);
      setColor(ctx->reg.DIS00);
      break;
    case CMD_GET_CURSOR_X:
      getCursorX(ctx);
      break;
    case CMD_GET_CURSOR_Y:
      getCursorY(ctx);
      break;
  }
  ctx->reg.DISCR &= 0x7f; // Clear IRQ flag. Leave the rest
}

boolean memReadDisplayRegister(TContextPtr ctx) {
  if (ctx->address < REG_DIS_START || ctx->address > REG_DIS_END) return false;
  ctx->data = ctx->reg.displayRegister[ctx->address - REG_DIS_START];
  return true;
}

boolean memWriteDisplayRegister(TContextPtr ctx) {
  if (ctx->address < REG_DIS_START || ctx->address > REG_DIS_END) return false;

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

  ctx->reg.displayRegister[ctx->address - REG_DIS_START] = ctx->data;

  // Check for IRQ Flag
  if (ctx->reg.DISCR & 0x80) {
    
      // If the IRQ flag is set, we know that it was set through this write
      // instruction. This means, we are requested to execute the
      // prepared command. 
      #ifdef DEBUG_DISPLAY
      Serial.printf("IRQ Flag for display set. Executing command. %02x\n", ctx->reg.DISCMD);
      #endif
      executeCommand(ctx); // Execute command and clear irq flag
  }
  return true;    
 }

uint16_t convertColor565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}