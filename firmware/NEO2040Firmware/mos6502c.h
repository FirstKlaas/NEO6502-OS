// 
// Author: Rien Matthijsse
// 

#ifndef _MOS65C02_h
#define _MOS65C02_h

#include <Arduino.h>
#include "pins.h"
#include "memory.h"
#include "datatypes.h"


#define CPU_DEBUG   1


#define RESET_LOW   false
#define RESET_HIGH  true

#define ENABLE_LOW  false
#define ENABLE_HIGH true

#define CLOCK_LOW   false
#define CLOCK_HIGH  true

#define RW_READ     true
#define RW_WRITE    false

void init6502(TContextPtr ctx);
void reset6502();
void tick6502(TContextPtr ctx);

#endif
