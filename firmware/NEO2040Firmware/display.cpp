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

typedef struct {
  uint16_t width;
  uint16_t height;
  uint16_t x;
  uint16_t y;
  uint8_t  flags;
  uint8_t  color;  
  uint16_t address;
} TSprite, *TSpritePtr;

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
  TSprite sprites[32];
  
} screendata;

uint8_t buffer[] = {12,15,67};

void setColor(uint8_t vColor) {
  screendata.currentColor = vColor;
  display.setTextColor(vColor);
}

const uint8_t bitti[] = { 
  0xea, 0xea, 0xea,
  0xea, 0xea, 0xea,
  0xea, 0xea, 0xea,
  0xea, 0xea, 0xea,
  0xea, 0xea, 0xea,
  0xea, 0xea, 0xea,
  0xea, 0xea, 0xea,
  0xea, 0xea, 0xea
};

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
  screendata.needsRefresh = 1;
  display.setCursor(1,0);
  setColor(255);

  display.drawBitmap(100,100,bitti,24,8,2);
};


void setCursor(TContextPtr ctx, uint8_t x, uint8_t y) {
  uint8_t ox(screendata.currentXpos);
  uint8_t oy(screendata.currentYpos);
  
  screendata.currentXpos = x;
  screendata.currentYpos = y;

  if (x >= LINECHARS && (ctx->reg.DISCR & AUTO_WRAP_FLAG)) {
    screendata.currentXpos = (x % LINECHARS);
    screendata.currentYpos += (x / LINECHARS);
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

const TSpritePtr getSprite(const TContextPtr ctx) {
  return screendata.sprites + (ctx->reg.DIS00 & 0x1f);
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
      setColor(ctx->reg.DIS00);
      break;
    case CMD_GET_CURSOR_X:
      getCursorX(ctx);
      break;
    case CMD_GET_CURSOR_Y:
      getCursorY(ctx);
      break;

    case CMD_SPRITE_GET_ADRESS:
      const TSpritePtr sprite(getSprite(ctx));
      ctx->reg.DIS01 = sprite->address & 0xff;
      ctx->reg.DIS02 = (sprite->address >> 8) & 0xff;
      break; 

    case CMD_SPRITE_SET_ADRESS:
      const TSpritePtr sprite(getSprite(ctx));
      const uint16_t address(ctx->reg.DIS01 | (ctx->reg.DIS02 << 8));
      sprite->address = address;
      break;

    case CMD_SPRITE_GET_POSITION:
      const TSpritePtr sprite(getSprite(ctx));
      const uint16_t xpos_high((sprite->x >> 8) & 0xff);
      const uint8_t xpos_low(sprite->x & 0xff);
      ctx->reg.DIS01 = xpos_low;
      ctx->reg.DIS02 = xpos_high;
      ctx->reg.DIS03 = ypos;
      break;

    case CMD_SPRITE_SET_POSITION:
      const TSpritePtr sprite(getSprite(ctx));
      const uint16_t xpos(ctx->reg.DIS01 | (ctx->reg.DIS02 << 8));
      const uint8_t ypos(ctx->reg.DIS03);
      sprite->x = xpos;
      sprite->y = ypos;
      break;

    case CMD_SPRITE_SET_COLOR:
      const TSpritePtr sprite(getSprite(ctx));
      sprite->color = ctx->reg.DIS01;
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