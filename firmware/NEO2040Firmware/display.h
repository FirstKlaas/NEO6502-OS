#ifndef DISPLAY_H
#define DISPLAY_H

#include <pico/stdlib.h>
#include "datatypes.h"

#define FRAMERATE 25  // frames per sec
#define FRAMETIME 1000/FRAMERATE  // msec
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define FONT_CHAR_WIDTH 6
#define FONT_CHAR_HEIGHT 8

#define LINES SCREEN_HEIGHT / (FONT_CHAR_HEIGHT + 1)
#define LINECHARS 52  //SCREEN_WIDTH / FONT_CHAR_WIDTH

#define BLACK 0x00
#define MAROON 0x01
#define GREEN 0x02
#define OLIVE 0x03
#define NAVY 0x04
#define PURPLE 0x05
#define TEAL 0x06
#define SILVER 0x07
#define GREY 0x08
#define RED 0x09
#define LIME 0x0a
#define YELLOW 0x0b
#define BLUE 0x0c
#define FUCHSIA 0x0d
#define AQUA 0x0e
#define WHITE 0x0f

enum {
  CMD_NOP = 0x00,

  // Text Commands
  CMD_GET_CURSOR_X = 0x01,
  CMD_GET_CURSOR_Y = 0x02,
  CMD_SET_CURSOR_X = 0x03,
  CMD_SET_CURSOR_Y = 0x04,
  CMD_GET_FG_COLOR = 0x05,
  CMD_GET_BG_COLOR = 0x06,
  CMD_SET_FG_COLOR = 0x07,
  CMD_SET_BG_COLOR = 0x08,
  CMD_GET_X_OFFSET = 0x09,
  CMD_GET_Y_OFFSET = 0x0A,
  CMD_SET_X_OFFSET = 0x0B,
  CMD_SET_Y_OFFSET = 0x0C,
  CMD_WRITE_CHAR = 0x0D,
  CMD_FILL_SCREEN = 0x0E,
  CMD_CLEAR_SCREEN = 0x0F,
  CMD_SCROLL_UP = 0x10,
  CMD_SCROLL_DOWN = 0x11,
  CMD_SHOW_CURSOR = 0x12,
  CMD_HIDE_CURSOR = 0x13,
  // Graphics Commands
  CMD_DRAW_LINE = 0x14,
  CMD_DRAW_HLINE = 0x15,
  CMD_DRAW_VLINE = 0x16,
  CMD_SET_SDB = 0x17,  // SET Sprite Definition Block Pointer


  // Sprite handling
  CMD_SPRITE_SET_POSITION = 0x40,
  CMD_SPRITE_GET_POSITION = 0x41,
  CMD_SPRITE_SET_DIMENSIONS = 0x42,
  CMD_SPRITE_GET_DIMENSIONS = 0x43,
  CMD_SPRITE_SET_ADRESS = 0x44,
  CMD_SPRITE_GET_ADRESS = 0x45,
  CMD_SPRITE_SET_COLOR = 0x46,
  CMD_SPRITE_GET_COLOR = 0x47,
  CMD_SPRITE_SET_FLAGS = 0x48,
  CMD_SPRITE_GET_FLAGS = 0x49





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
void clearDisplay();
void drawSprites(TContextPtr ctx);

boolean memReadDisplayRegister(TContextPtr ctx);
boolean memWriteDisplayRegister(TContextPtr ctx);

void animateAlien(TContextPtr ctx);
#endif