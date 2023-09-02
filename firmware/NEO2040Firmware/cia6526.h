#ifndef CIA6526_h
#define CIA6526_h

#include "datatypes.h"

#define TIMER_A_INTERRUPT_FLAG  0x01
#define TIMER_B_INTERRUPT_FLAG  0x02
#define FRAME_INTERRUPT_FLAG    0x04
#define KBD_INTERRUPT_FLAG      0x08

void setupCIAPins();
void initCIA(TContextPtr ctx);
boolean memWriteCIA(TContextPtr ctx);
boolean memReadCIA(TContextPtr ctx);
void checkCIA(TContextPtr ctx);
void raiseFrameRequest(TContextPtr ctx);

bool isFrameInterruptRaised(TContextPtr ctx);

#endif