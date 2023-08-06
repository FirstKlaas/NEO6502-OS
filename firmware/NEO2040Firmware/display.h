#ifndef DISPLAY_H
#define DISPLAY_H

#include <pico/stdlib.h>
#include "datatypes.h"

#define FRAMERATE           25 // frames per sec
#define FRAMETIME         1000 // msec
#define SCREEN_WIDTH       320
#define SCREEN_HEIGHT      240
#define FONT_CHAR_WIDTH      6  
#define FONT_CHAR_HEIGHT     8

#define LINES             SCREEN_HEIGHT / (FONT_CHAR_HEIGHT + 1)
#define LINECHARS         52 //SCREEN_WIDTH / FONT_CHAR_WIDTH

#define COLOR_BLACK   0
#define COLOR_RED     1
#define COLOR_GREEN   2
#define COLOR_YELLOW  3
#define COLOR_BLUE    4
#define COLOR_ORANGE  5
#define COLOR_MAGENTA 6
#define COLOR_AMBER   7
#define COLOR_WHITE   255

enum {
  CMD_NOP             = 0x00,

  // Text Commands
  CMD_GET_CURSOR_X    = 0x01,
  CMD_GET_CURSOR_Y    = 0x02,
  CMD_SET_CURSOR_X    = 0x03,
  CMD_SET_CURSOR_Y    = 0x04,
  CMD_GET_FG_COLOR    = 0x05,
  CMD_GET_BG_COLOR    = 0x06,
  CMD_SET_FG_COLOR    = 0x07,
  CMD_SET_BG_COLOR    = 0x08,
  CMD_GET_X_OFFSET    = 0x09,
  CMD_GET_Y_OFFSET    = 0x0A,
  CMD_SET_X_OFFSET    = 0x0B,
  CMD_SET_Y_OFFSET    = 0x0C,
  CMD_WRITE_CHAR      = 0x0D,
  CMD_FILL_SCREEN     = 0x0E,
  CMD_CLEAR_SCREEN    = 0x0F,
  CMD_SCROLL_UP       = 0x10,
  CMD_SCROLL_DOWN     = 0x11,
  CMD_SHOW_CURSOR     = 0x12,
  CMD_HIDE_CURSOR     = 0x13,
  // Graphics Commands
  CMD_DRAW_LINE       = 0x14,
  CMD_DRAW_HLINE      = 0x15,
  CMD_DRAW_VLINE      = 0x16
} TDisplayCommand;

void initDisplay(TContextPtr ctx);
/*
void setColor(uint8_t vColor);
void setCursor(TContextPtr ctx, uint8_t x, uint8_t y);
void writeChar(TContextPtr ctx, uint8_t c);
void updateDisplay();
void printWelcomeMsg(TContextPtr ctx);
*/
void updateDisplay();
boolean memReadDisplayRegister(TContextPtr ctx);
boolean memWriteDisplayRegister(TContextPtr ctx);

uint16_t convertColor565(uint8_t r, uint8_t g, uint8_t b);
#endif