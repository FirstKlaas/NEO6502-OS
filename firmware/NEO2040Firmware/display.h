#ifndef DISPLAY_H
#define DISPLAY_H

#include <pico/stdlib.h>
#include "datatypes.h"

#define FRAMERATE           10 // frames per sec
#define FRAMETIME         1000 / FRAMERATE  // msec
#define SCREEN_WIDTH       320
#define SCREEN_HEIGHT      240
#define FONT_CHAR_WIDTH      6  
#define FONT_CHAR_HEIGHT     8

#define LINES             SCREEN_HEIGHT / (FONT_CHAR_HEIGHT + 1)
#define LINECHARS         SCREEN_WIDTH / FONT_CHAR_WIDTH

#define COLOR_BLACK   0
#define COLOR_RED     1
#define COLOR_GREEN   2
#define COLOR_YELLOW  3
#define COLOR_BLUE    4
#define COLOR_ORANGE  5
#define COLOR_MAGENTA 6
#define COLOR_AMBER   7
#define COLOR_WHITE   255

void initDisplay(TContextPtr ctx);
void setColor(uint8_t vColor);
void setCursor(uint16_t x, uint16_t y);
void updateDisplay();
void printWelcomeMsg();

boolean memReadDisplayRegister(TContextPtr ctx);
boolean memWriteDisplayRegister(TContextPtr ctx);

uint16_t convertColor565(uint8_t r, uint8_t g, uint8_t b);
#endif