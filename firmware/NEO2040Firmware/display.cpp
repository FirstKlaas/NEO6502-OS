#include "display.h"
#include "addr.h"

void initDisplay(THardwarePtr hardware) {

};

boolean readDisplay(THardwarePtr hardware) {
  if (hardware->address == REG_DIS_ADDR) {
    hardware->data = hardware->reg.DIS;
    return true;
  };

  if (hardware->address == REG_DISCR_ADDR) {
    hardware->data = hardware->reg.DISCR;
    return true;
  };

  return false;

}

boolean writeDisplay(THardwarePtr hardware) {
  switch (hardware->address) {

    case REG_DIS_ADDR:
      hardware->reg.DIS = hardware->data;
      hardware->display.setXPos(hardware->data);
      return true;

    case REG_DISCR_ADDR:
      hardware->reg.DISCR = hardware->data;
      return true;
  }

  return false;
}
