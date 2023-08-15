#include "display.h"
#include "addr.h"
#include <PicoDVI.h>

// #define DEBUG_DISPLAY

// Pico HDMI for Olimex Neo6502
static const struct dvi_serialiser_cfg dvi_cfg = {
    .pio = DVI_DEFAULT_PIO_INST,
    .sm_tmds = {0, 1, 2},
    .pins_tmds = {14, 18, 16},
    .pins_clk = 12,
    .invert_diffpairs = true};
DVIGFX8 display(DVI_RES_320x240p60, true, dvi_cfg);

typedef struct
{
  uint8_t width;
  uint8_t height;
  uint8_t x; // For xpos > 255: flags bit 0 = 1
  uint8_t y;
  uint8_t flags; // Bit 0: X > 255 | Bit 1: Visibility
  uint8_t color;
  union
  {
    uint16_t address;
    struct
    {
      uint8_t address_high;
      uint8_t address_low;
    };
  };
} TSprite, *TSpritePtr;

typedef struct
{
  uint8_t count;
  uint16_t address;
  uint8_t *flags;
  uint8_t *xpos;
  uint8_t *ypos;
  uint8_t *color;
  uint8_t *width;
  uint8_t *height;
  uint8_t *data_lo;
  uint8_t *data_hi;
} TSpriteDataBlock, *TSpriteDataBlockPtr;

struct
{
  uint16_t x;       // X position in pixel
  uint16_t y;       // Y position in pixel
  uint8_t offset_y; // Top offset in pixel
  uint8_t offset_x; // Left offset in pixel

  uint8_t textbuffer[LINES * LINECHARS];
  uint8_t currentColor;   // Current foreground color
  uint8_t currentBgColor; // Current background color
  uint8_t currentXpos;    // X position in character
  uint8_t currentYpos;    // Y position in character

  uint32_t needsRefresh;  // If > 0: Screen will be updated.
  TSprite sprites[32];
  TSpriteDataBlock sdb;
} screendata;

uint8_t buffer[] = {12, 15, 67};

inline __attribute__((always_inline))
uint16_t
getSpriteOffset(TContextPtr ctx, uint8_t index)
{
  return ((screendata.sdb.data_hi[index] << 8) | screendata.sdb.data_lo[index]);
}

inline __attribute__((always_inline))
uint8_t *
getSpriteDataPtr(TContextPtr ctx, uint8_t index)
{
  return ctx->memory + getSpriteOffset(ctx, index);
}

inline __attribute__((always_inline))
uint16_t
convertColor565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

inline __attribute__((always_inline)) void setColor(uint8_t vColor)
{
  screendata.currentColor = vColor;
  display.setTextColor(vColor);
}

void initDisplay(TContextPtr ctx)
{

  if (!display.begin())
  {
#ifdef DEBUG_DISPLAY
    Serial.println("ERROR: not enough RAM available");
#endif
    for (;;)
      ;
  }
  // Activate correct codepage
  // Issue #14
  display.cp437(true);

  screendata.offset_x = 1;
  screendata.offset_y = 1;

  display.setColor(0, convertColor565(0x00, 0x00, 0x00)); // Black
  display.setColor(1, convertColor565(0xff, 0xff, 0xff)); // White
  display.setColor(2, convertColor565(0x13, 0x13, 0x13));
  display.setColor(3, convertColor565(0x1b, 0x1b, 0x1b));
  display.setColor(4, convertColor565(0x27, 0x27, 0x27));
  display.setColor(5, convertColor565(0x3d, 0x3d, 0x3d));
  display.setColor(6, convertColor565(0x5d, 0x5d, 0x5d));
  display.setColor(7, convertColor565(0x85, 0x85, 0x85));
  display.setColor(8, convertColor565(0xb4, 0xb4, 0xb4));
  display.setColor(9, convertColor565(0xff, 0xff, 0xff));
  display.setColor(10, convertColor565(0xc7, 0xcf, 0xdd));
  display.setColor(11, convertColor565(0x92, 0xa1, 0xb9));
  display.setColor(12, convertColor565(0x65, 0x73, 0x92));
  display.setColor(13, convertColor565(0x42, 0x4c, 0x6e));
  display.setColor(14, convertColor565(0x2a, 0x2f, 0x4e));
  display.setColor(15, convertColor565(0x1a, 0x19, 0x32));
  display.setColor(16, convertColor565(0x0e, 0x07, 0x1b));
  display.setColor(17, convertColor565(0x1c, 0x12, 0x1c));
  display.setColor(18, convertColor565(0x39, 0x1f, 0x21));
  display.setColor(19, convertColor565(0x5d, 0x2c, 0x28));
  display.setColor(20, convertColor565(0x8a, 0x48, 0x36));
  display.setColor(21, convertColor565(0xbf, 0x6f, 0x4a));
  display.setColor(22, convertColor565(0xe6, 0x9c, 0x69));
  display.setColor(23, convertColor565(0xf6, 0xca, 0x9f));
  display.setColor(24, convertColor565(0xf9, 0xe6, 0xcf));
  display.setColor(25, convertColor565(0xed, 0xab, 0x50));
  display.setColor(26, convertColor565(0xe0, 0x74, 0x38));
  display.setColor(27, convertColor565(0xc6, 0x45, 0x24));
  display.setColor(28, convertColor565(0x8e, 0x25, 0x1d));
  display.setColor(29, convertColor565(0xff, 0x50, 0x00));
  display.setColor(30, convertColor565(0xed, 0x76, 0x14));
  display.setColor(31, convertColor565(0xff, 0xa2, 0x14));
  display.setColor(32, convertColor565(0xff, 0xc8, 0x25));
  display.setColor(33, convertColor565(0xff, 0xeb, 0x57));
  display.setColor(34, convertColor565(0xd3, 0xfc, 0x7e));
  display.setColor(35, convertColor565(0x99, 0xe6, 0x5f));
  display.setColor(36, convertColor565(0x5a, 0xc5, 0x4f));
  display.setColor(37, convertColor565(0x33, 0x98, 0x4b));
  display.setColor(38, convertColor565(0x1e, 0x6f, 0x50));
  display.setColor(39, convertColor565(0x13, 0x4c, 0x4c));
  display.setColor(40, convertColor565(0x0c, 0x2e, 0x44));
  display.setColor(41, convertColor565(0x00, 0x39, 0x6d));
  display.setColor(42, convertColor565(0x00, 0x69, 0xaa));
  display.setColor(43, convertColor565(0x00, 0x98, 0xdc));
  display.setColor(44, convertColor565(0x00, 0xcd, 0xf9));
  display.setColor(45, convertColor565(0x0c, 0xf1, 0xff));
  display.setColor(46, convertColor565(0x94, 0xfd, 0xff));
  display.setColor(47, convertColor565(0xfd, 0xd2, 0xed));
  display.setColor(48, convertColor565(0xf3, 0x89, 0xf5));
  display.setColor(49, convertColor565(0xdb, 0x3f, 0xfd));
  display.setColor(50, convertColor565(0x7a, 0x09, 0xfa));
  display.setColor(51, convertColor565(0x30, 0x03, 0xd9));
  display.setColor(52, convertColor565(0x0c, 0x02, 0x93));
  display.setColor(53, convertColor565(0x03, 0x19, 0x3f));
  display.setColor(54, convertColor565(0x3b, 0x14, 0x43));
  display.setColor(55, convertColor565(0x62, 0x24, 0x61));
  display.setColor(56, convertColor565(0x93, 0x38, 0x8f));
  display.setColor(57, convertColor565(0xca, 0x52, 0xc9));
  display.setColor(58, convertColor565(0xc8, 0x50, 0x86));
  display.setColor(59, convertColor565(0xf6, 0x81, 0x87));
  display.setColor(60, convertColor565(0xf5, 0x55, 0x5d));
  display.setColor(61, convertColor565(0xea, 0x32, 0x3c));
  display.setColor(62, convertColor565(0xc4, 0x24, 0x30));
  display.setColor(63, convertColor565(0x89, 0x1e, 0x2b));
  display.setColor(64, convertColor565(0x57, 0x1c, 0x27));

  // Clear back framebuffer
  display.fillScreen(0);
  display.setFont();       // Use default font
  display.setCursor(0, 0); // Initial cursor position
  display.setTextSize(1);  // Default size
  display.setTextWrap(false);
  display.swap(false, true); // Duplicate same palette into front & back buffers
  screendata.needsRefresh = 1;
};

void setCursor(TContextPtr ctx, uint8_t x, uint8_t y)
{
  uint8_t ox(screendata.currentXpos);
  uint8_t oy(screendata.currentYpos);

  screendata.currentXpos = x;
  screendata.currentYpos = y;

  if (x >= LINECHARS && (ctx->memory[DISCR] & AUTO_WRAP_FLAG))
  {
    screendata.currentXpos = (x % LINECHARS);
    screendata.currentYpos += (x / LINECHARS);
  };

  screendata.x = screendata.currentXpos * FONT_CHAR_WIDTH + screendata.offset_x;
  screendata.y = screendata.currentYpos * FONT_CHAR_HEIGHT + screendata.offset_y;

  display.setCursor(screendata.x, screendata.y);
  if (ctx->memory[DISCR] && SHOW_CURSOR_FLAG)
  {
    // If there is a change and we show the cursor,
    // we need to refresh the screen.
    screendata.needsRefresh++;
  }
}

void setCursorX(TContextPtr ctx, uint8_t x)
{
  setCursor(ctx, x, screendata.currentYpos);
}

void setCursorY(TContextPtr ctx, uint8_t y)
{
  setCursor(ctx, screendata.currentXpos, y);
}

void getCursorX(TContextPtr ctx)
{
  ctx->memory[DIS00] = screendata.currentXpos;
}

void getCursorY(TContextPtr ctx)
{
  ctx->memory[DIS00] = screendata.currentYpos;
}

void clearDisplay() {
  display.fillScreen(screendata.currentBgColor);
}

void updateDisplay()
{
  // screendata.needsRefresh
  if (true)
  {

    display.swap(true, false);
  };
  screendata.needsRefresh = 0;
}

void writeChar(TContextPtr ctx, uint8_t c)
{
  // Cursor position is off screen, do nothing
  if (screendata.currentXpos >= LINECHARS || screendata.currentYpos >= LINES)
    return;

  display.write(c);
  screendata.needsRefresh++;
  // Check, if we need to adjust the cursor
  // automatically
  if (ctx->memory[DISCR] && ADJUST_CURSOR_FLAG)
  {
    setCursor(ctx, screendata.currentXpos + 1, screendata.currentYpos);
  }
}

const TSpritePtr getSprite(const TContextPtr ctx)
{
  return screendata.sprites + (ctx->memory[DIS00] & 0x1f);
}

inline __attribute__((always_inline))
uint16_t word(uint8_t* p) {
  return (p[0] | (p[1] << 8));
}

inline __attribute__((always_inline))
void markDirty() {
  screendata.needsRefresh++;
}

void executeCommand(TContextPtr ctx)
{
  static uint8_t* params = ctx->memory + DIS00; 

  switch (ctx->memory[DISCMD])
  {
  case CMD_NOP:
    break;
  case CMD_SET_CURSOR_X:
    setCursorX(ctx, ctx->memory[DIS00]);
    break;
  case CMD_SET_CURSOR_Y:
    setCursorY(ctx, ctx->memory[DIS00]);
    break;
  case CMD_WRITE_CHAR:
    writeChar(ctx, ctx->memory[DIS00]);
    markDirty();
    break;
  case CMD_SET_FG_COLOR:
    setColor(ctx->memory[DIS00]);
    break;
  case CMD_GET_CURSOR_X:
    getCursorX(ctx);
    break;
  case CMD_GET_CURSOR_Y:
    getCursorY(ctx);
    break;
  case CMD_SET_BG_COLOR:
    screendata.currentBgColor = ctx->memory[DIS00];
    break;
  case CMD_GET_BG_COLOR:
    ctx->memory[DIS00] = screendata.currentBgColor;
    break;
  case CMD_DRAW_HLINE:
    display.drawFastHLine(
      word(params),   // XPOS   DIS00 DIS01
      params[2],      // YPOS   DIS02
      word(params+3), // LENGTH DIS03 DIS04
      params[5]       // COLRO  DIS05
    );
    markDirty();
    break;

  case CMD_DRAW_RECT:
    display.drawRect(
      word(params),   // XPOS   DIS00 DIS01
      params[2],      // YPOS   DIS02
      word(params+3), // WIDTH  DIS03 DIS04
      params[5],      // HEIGHT DIS05
      params[6]       // COLOR  DIS06
    );
    markDirty();
    break;

  case CMD_FILL_RECT:
    display.fillRect(
      word(params),   // XPOS   DIS00 DIS01
      params[2],      // YPOS   DIS02
      word(params+3), // WIDTH  DIS03 DIS04
      params[5],      // HEIGHT DIS05
      params[6]       // COLOR  DIS06
    );
    markDirty();
    break;

  case CMD_SET_SDB:
  {
    screendata.sdb.address = ((ctx->memory[DIS01] << 8) | ctx->memory[DIS00]);
    screendata.sdb.count = ctx->memory[DIS02];
    screendata.sdb.flags = ctx->memory + screendata.sdb.address;
    screendata.sdb.xpos = screendata.sdb.flags + screendata.sdb.count;
    screendata.sdb.ypos = screendata.sdb.xpos + screendata.sdb.count;
    screendata.sdb.color = screendata.sdb.ypos + screendata.sdb.count;
    screendata.sdb.width = screendata.sdb.color + screendata.sdb.count;
    screendata.sdb.height = screendata.sdb.width + screendata.sdb.count;
    screendata.sdb.data_lo = screendata.sdb.height + screendata.sdb.count;
    screendata.sdb.data_hi = screendata.sdb.data_lo + screendata.sdb.count;


    screendata.sdb.flags[0] = 0x80;
    screendata.sdb.flags[1] = 0x80;
    
    //#ifdef DEBUG_DISPLAY
    Serial.printf(
        "Sprite initalisation: Address %04x | Count %02d | width %02d | height %02d | flags %02x | color %02x\n",
        screendata.sdb.address,
        screendata.sdb.count,
        screendata.sdb.width[0],
        screendata.sdb.height[0],
        screendata.sdb.flags[0],
        screendata.sdb.color[0]
        );
    //#endif
    uint16_t offset = getSpriteOffset(ctx, 0);
  };
  break;
  }
  ctx->memory[DISCR] &= 0x7f; // Clear IRQ flag. Leave the rest
}

uint8_t HEXVALUES[] = "0123456789ABCDEF";

inline __attribute__((always_inline)) void writeHexByte(TContextPtr ctx, uint8_t c)
{
  writeChar(ctx, HEXVALUES[c & 0xff]);
  writeChar(ctx, HEXVALUES[(c >> 8) & 0xff]);
}

inline __attribute__((always_inline))
uint8_t
getSpriteXPos(uint8_t index)
{
  return screendata.sdb.xpos[index];
}

inline __attribute__((always_inline))
uint8_t
getSpriteYPos(uint8_t index)
{
  return screendata.sdb.ypos[index];
}

inline __attribute__((always_inline))
uint8_t
getSpriteWidth(uint8_t index)
{
  return screendata.sdb.width[index];
}

inline __attribute__((always_inline))
uint8_t
getSpriteHeight(uint8_t index)
{
  return screendata.sdb.height[index];
}

inline __attribute__((always_inline))
uint8_t
getSpriteColor(uint8_t index)
{
  return screendata.sdb.color[index];
}

void drawSprites(TContextPtr ctx)
{
  if (true) //ctx->memory[DISCR] & 0x40)
  {
    for (uint8_t i = 0; i < screendata.sdb.count; i++)
    {
      if (screendata.sdb.flags[i] & 0x80)
      {
        display.drawBitmap(
            getSpriteXPos(i),
            getSpriteYPos(i),
            getSpriteDataPtr(ctx, i),
            getSpriteWidth(i),
            getSpriteHeight(i),
            getSpriteColor(i));
      }
    };
    screendata.needsRefresh++;
  };
}

boolean memReadDisplayRegister(TContextPtr ctx)
{
  if (ctx->address < REG_DIS_START || ctx->address > REG_DIS_END)
    return false;
  ctx->data = ctx->memory[ctx->address];
  return true;
}

boolean memWriteDisplayRegister(TContextPtr ctx)
{
  if (ctx->address < REG_DIS_START || ctx->address > REG_DIS_END)
    return false;

#ifdef DEBUG_DISPLAY
  Serial.printf("Display write: [%04X] := %02X\n", ctx->address, ctx->data);
#endif

  // If the IRQ flag is set, we do not change anything, but
  // still the write request is handled.
  if (ctx->memory[DISCR] & 0x80)
  {
#ifdef DEBUG_DISPLAY
    Serial.println("IRQ Flag for display set. Register stay unchanged.");
#endif
    return true;
  }

  ctx->memory[ctx->address] = ctx->data;

  // Check for IRQ Flag
  if (ctx->memory[DISCR] & 0x80)
  {

// If the IRQ flag is set, we know that it was set through this write
// instruction. This means, we are requested to execute the
// prepared command.
#ifdef DEBUG_DISPLAY
    Serial.printf("IRQ Flag for display set. Executing command. %02x\n", ctx->memory[DISCMD]);
#endif
    executeCommand(ctx); // Execute command and clear irq flag
  }
  return true;
}
