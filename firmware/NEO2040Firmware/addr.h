#ifndef ADDR_H
#define ADDR_H


#define REG_KBD_ADDR        0xD010  // Address for the character buffer
#define REG_KBDCR_ADDR      0xD011  // Address for the character control register
                                  // Bit 7 : IRQ Flag: 1 = IRQ active; 0 = No IRQ


#define REG_DIS_START       0xD012
#define REG_DIS_END         0xD01C

#define REG_DIS_ADDR        0xD012  // Display Register. The charcter to write to
                                    // the screen at the current position
#define REG_DISCR_ADDR      0xD013  // Display Control register.
                                    // Bit 7: IRQ Bit
                                    // Bit 6: Spites enable flag
                                  
#define REG_DIS_CMD_ADDR    0xD014
#define REG_DIS_00_ADDR     0xD015
#define REG_DIS_01_ADDR     0xD016
#define REG_DIS_02_ADDR     0xD017
#define REG_DIS_03_ADDR     0xD018
#define REG_DIS_04_ADDR     0xD019
#define REG_DIS_05_ADDR     0xD01A
#define REG_DIS_06_ADDR     0xD01B
#define REG_DIS_07_ADDR     0xD01C

// CIA 6526
#define REG_CIA_PRA         0xDC00  // Not implemented
#define REG_CIA_PRB         0xDC01  // Not implemented
#define REG_CIA_DDRA        0xDC01  // Not implemented
#define REG_CIA_DDRB        0xDC01  // Not implemented
#define REG_CIA_TA_LO       0xDC04
#define REG_CIA_TA_HI       0xDC05
#define REG_CIA_TB_LO       0xDC06
#define REG_CIA_TB_HI       0xDC07
#define REG_CIA_TOD_10THSEC 0xDC08
#define REG_CIA_TOD_SEC     0xDC09
#define REG_CIA_TOD_MIN     0xDC0A
#define REG_CIA_TOD_HR      0xDC0B
#define REG_CIA_SDR         0xDC0C // Not supported
#define REG_CIA_ICR         0xDC0D
#define REG_CIA_CRA         0xDC0E
#define REG_CIA_CRB         0xDC0F

// Register 0xD100 - 0xD1ff = Spriteregister

#define REG_KBD_IRQ_FLAG    0x80    // 10000000b
#define REG_DIS_IRQ_FLAG    0x80    // 10000000b
#define SHOW_CURSOR_FLAG    0x02     
#define ADJUST_CURSOR_FLAG  0x04
#define AUTO_WRAP_FLAG      0x08
#define FRAME_UPDATE_IRQ    0x01

#define KBD_IRQ_SET(h) = (h->reg.KBCR & REG_KBD_IRQ_FLAG == REG_KBD_IRQ_FLAG)


#define DIS_CMD_NOP       0x00    // No operation

#endif