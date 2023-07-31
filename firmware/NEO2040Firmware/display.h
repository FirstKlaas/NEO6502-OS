#ifndef DISPLAY_H
#define DISPLAY_H

#include <pico/stdlib.h>
#include "datatypes.h"

void initDisplay(THardwarePtr hardware);
boolean readDisplay(THardwarePtr hardware);
boolean writeDisplay(THardwarePtr hardware);

#endif