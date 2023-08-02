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
#define REG_DIS_00_ADDR   0xD014
#define REG_DIS_01_ADDR   0xD015
#define REG_DIS_02_ADDR   0xD016
#define REG_DIS_03_ADDR   0xD017
#define REG_DIS_04_ADDR   0xD018
#define REG_DIS_05_ADDR   0xD019
#define REG_DIS_06_ADDR   0xD01A
#define REG_DIS_07_ADDR   0xD01B

#define REG_DIS_CMD_MASK  0x0f 

#define REG_KBD_IRQ_FLAG  0x80    // 10000000b
#define REG_DIS_IRQ_FLAG  0x80    // 10000000b

#define KBD_IRQ_SET(h) = (h->reg.KBCR & REG_KBD_IRQ_FLAG == REG_KBD_IRQ_FLAG)


#define DIS_CMD_NOP       0x00    // No operation

#endif