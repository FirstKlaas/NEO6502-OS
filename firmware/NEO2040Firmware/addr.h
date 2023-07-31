#ifndef ADDR_H
#define ADDR_H


#define REG_KBD_ADDR      0xD010  // Address for the character buffer
#define REG_KBDCR_ADDR    0xD011  // Address for the character control register
                                  // Bit 7 : IRQ Flag: 1 = IRQ active; 0 = No IRQ


#define REG_DIS_ADDR      0xD012  // Display Register. The charcter to write to
                                  // the screen at the current position
#define REG_DISCR_ADDR    0xD013  // Display Control register.
                                  // Bit 7: IRQ Bit
                                  // Bit 6: Show Cursor (1= true; 0 = false)
#define REG_DIS_XPOS      0xD014
#define REG_DIS_YPOS      0xD015
#define REG_DIS_COLOR_LO  0xD016  // Colors are always defined in 16bit (5-6-5) 
#define REG_DIS_COLOR_HI  0xD017  // Therefore we need two bytes to represent a color

#define REG_DIS_CMD_MASK  0x0f 

#define REG_KBD_IRQ_FLAG  0x80    // 10000000b
#define REG_DIS_IRQ_FLAG  0x80    // 10000000b

#define KBD_IRQ_SET(h) = (h->reg.KBCR & REG_KBD_IRQ_FLAG == REG_KBD_IRQ_FLAG)


#define DIS_CMD_NOP       0x00    // No operation

#endif