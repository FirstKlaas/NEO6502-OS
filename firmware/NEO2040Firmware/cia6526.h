#ifndef CIA6526_h
#define CIA6526_h

#include "datatypes.h"

void setupCIAPins();
void initCIA(TContextPtr ctx);
boolean memWriteCIA(TContextPtr ctx);
boolean memReadCIA(TContextPtr ctx);
void checkCIA(TContextPtr ctx);

#endif