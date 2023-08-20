.cpu _65c02

// --------------------------------
// NEO6502 OS V0.0.1
// --------------------------------
// @author: <klaas.nebuhr@gmal.com>
// @version: 0.0.1
//
// Documentation for the CIA: https://www.c64-wiki.de/wiki/CIA#CIA_1


                .const KBD    = $d010    // Keyboard regster
                .const KBDCR  = $d011    // Keyboard control register
                .const DIS    = $d012    // Display register
                .const DISCR  = $d013    // Display control register
                                         // Bit 7 $80: Execute Command
                                         // Bit 6 $40: undefined
                                         // Bit 5 $20: undefined
                                         // Bit 4 $10: Autoclean screen
                                         // Bit 3 $08: Text and colorbuf
                                         // Bit 2 $04: Autoadjust Cursor
                                         // Bit 1 $02: Show Cursor
                                         // Bit 0 $01: Sprite activation 

                .const DISCMD = $d014    // Display command register
                .const DIS00 = $d015    // Data exchange register 
                .const DIS01 = $d016    // Data exchange register 
                .const DIS02 = $d017    // Data exchange register 
                .const DIS03 = $d018    // Data exchange register 
                .const DIS04 = $d019    // Data exchange register 
                .const DIS05 = $d01A    // Data exchange register 
                .const DIS06 = $d01B    // Data exchange register 
                .const DIS07 = $d01C    // Data exchange register
                .const DISFL = $d0fd    // Frame number lo
                .const DISFH = $d0fe    // Frame number hi
                .const DEBUG = $d0ff    // Debug register

                .const KBD_IRQ_FLAG = $80
                .const DIS_IRQ_FLAG = $80

                .const KEY_MOD_MASK = %01110000  // Mask for the modifiers

                .const CMD_GET_CURSOR_X     = $01
                .const CMD_GET_CURSOR_Y     = $02
                .const CMD_SET_CURSOR_X     = $03
                .const CMD_SET_CURSOR_Y     = $04
                .const CMD_GET_FG_COLOR     = $05
                .const CMD_GET_BG_COLOR     = $06
                .const CMD_SET_FG_COLOR     = $07
                .const CMD_SET_BG_COLOR     = $08
                .const CMD_GET_X_OFFSET     = $09
                .const CMD_GET_Y_OFFSET     = $0a
                .const CMD_SET_X_OFFSET     = $0b
                .const CMD_SET_Y_OFFSET     = $0c
                .const CMD_WRITE_CHAR       = $0d
                .const CMD_FILL_SCREEN      = $0e
                .const CMD_CLEAR_SCREEN     = $0f
                .const CMD_SCROLL_UP        = $10
                .const CMD_SCROLL_DOWN      = $11
                .const CMD_SHOW_CURSOR      = $12
                .const CMD_HIDE_CURSOR      = $13
                // Graphics Commands
                .const CMD_DRAW_LINE        = $14
                .const CMD_DRAW_HLINE       = $15
                .const CMD_DRAW_VLINE       = $16
                .const CMD_SET_SDB          = $17
                .const CMD_GET_BGCOLOR      = $18
                .const CMD_SET_BGCOLOR      = $19
                .const CMD_DRAW_RECT        = $1A
                .const CMD_FILL_RECT        = $1B
                .const CMD_DRAW_CIRCLE      = $1C
                .const CMD_FILL_CIRCLE      = $1D
                .const CMD_DRAW_SPRITES     = $1E

                .const CMD_DRAW_BITMAP      = $1F
                .const CMD_DRAW_PIXEL       = $20
                .const CMD_DRAW_TRIANGLE    = $21
                .const CMD_FILL_TRIANGLE    = $22
                .const CMD_DRAW_ROUND_RECT  = $23
                .const CMD_FILL_ROUND_RECT  = $24
                

.import source "asm/colors.asm"

/* ----------------------------------------------------------------------------
                ZERO PAGE 
                The kernel uses some space in the zero page for internal stuff.
                The addresses from E0 up FF (32 bytes) may not be used by other
                routines other than documented.

                By definition, the addresses F0-FF are volatile and can be used
                temporarily by any subroutine. (also by main programm).
                So these parameters should not be used for parameters or 
                Returnvalues.
   ----------------------------------------------------------------------------
*/
              
*=$E0 "Zero Kernel" virtual 
.zp {
                zpRegE0: .byte 0
                zpRegE1: .byte 0
                zpRegE2: .byte 0
                zpRegE3: .byte 0
                zpRegE4: .byte 0
                zpRegE5: .byte 0
                zpRegE6: .byte 0
                zpRegE7: .byte 0
                zpRegE8: .byte 0
                zpRegE9: .byte 0
                zpRegEA: .byte 0
                zpRegEB: .byte 0
                zpRegEC: .byte 0
                zpRegED: .byte 0
                zpRegEE: .byte 0
                zpRegEF: .byte 0
                zpRegF0: .byte 0
                zpRegF1: .byte 0
                zpRegF2: .byte 0
                zpRegF3: .byte 0
                zpRegF4: .byte 0
                zpRegF5: .byte 0
                zpRegF6: .byte 0
                zpRegF7: .byte 0
                zpRegF8: .byte 0
                zpRegF9: .byte 0
                zpRegFA: .byte 0
                zpRegFB: .byte 0
                zpRegFC: .byte 0
                zpRegFD: .byte 0
                zpRegFE: .byte 0
                zpRegFF: .byte 0
}

.macro HALT() {
    // Any write to $ffee will halt the cpu  
    sta $ffee
}

.import source "asm/main.asm"


/* ============================================================================
                KERNAL ROUTINES
   ----------------------------------------------------------------------------
*/
                * = $E000 "Kernel Routines Entry Points"

get_key:        jmp get_key_
set_cursor_x:   jmp set_cursor_x_
set_cursor_y:   jmp set_cursor_y_
print_char:     jmp print_char_

/* ----------------------------------------------------------------------------
    Display Routines.
    For most operations, we don't need a subroutine, as writing to the the 
    right register is all we need. For all one-byte operations writing to
    the register is enough. Setting the color takes two bytes. But the 16bit
    value is written to the display as we write the high byte. So just write
    first the low and then the hih byte and we are good to go.

    Same for reading. 
  
    Since         : 31.07.2023
    Last modified : 31.07.2023
    ----------------------------------------------------------------------------
*/


                * = $E100 "Kernel Routines"

.import source "asm/math.asm"
.import source "asm/kernel_text_routines.asm"
.import source "asm/kernel_graphic_primitives.asm"

// Starts at 0x1000
.import source "asm/space_invaders/spin_main.asm"

/* ============================================================================
                KERNAL DATA
   ----------------------------------------------------------------------------
*/
                * = $f000 "Kernel Data"

hex_chars:      .text "0123456789ABCDEF"
msg_01:         .text "Welcome to FirstKlaas OS v0.1"
