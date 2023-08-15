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
                .const DIS_00 = $d015    // Data exchange register 
                .const DIS_01 = $d016    // Data exchange register 
                .const DIS_02 = $d017    // Data exchange register 
                .const DIS_03 = $d018    // Data exchange register 
                .const DIS_04 = $d019    // Data exchange register 
                .const DIS_05 = $d01A    // Data exchange register 
                .const DIS_06 = $d01B    // Data exchange register 
                .const DIS_07 = $d01C    // Data exchange register 

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
                
*=$E0 virtual 
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

.import source "asm/kernel_text_routines.asm"
.import source "asm/kernel_graphic_primitives.asm"
.import source "asm/kernel_sprite.asm"
.import source "asm/debug_register.asm"


/* ----------------------------------------------------------------------------
    convert a single byte to two hex values (not characters).
    The value to be converted has to be in the accu and is left unchanged
    after return.
  
    Params In:
        Accu    : Value to be converted

    Params Out:
        zpRegE0 : Hexvalue lowbyte
        zpRegE1 : Hex value highbyte

    Since         : 31.07.2023
    Last modified : 31.07.2023
   ----------------------------------------------------------------------------
*/
byte_to_hex:    pha                     // Save value to stack.
                and #%00001111
                sta zpRegE0             // store the lower nibble
                pla                     // Load the original value
                pha                     // and save it again
                lsr                     // shift the higher nibbel to the lower nibble
                lsr
                lsr
                lsr
                sta zpRegE1             // store the higher nibble
                pla                     // restore the accu
                rts



/* ----------------------------------------------------------------------------
   converting a three byte color value (r,g,b) to a compressed two byte value
   (5-6-5).

   The input values are stored in the zeropage addresses

   @param: zpRegE0: Red Value 
   @param: zpRegE1: Green Value 
   @param: zpRegE2: Blue Value

   @return: 16bit color value. Highbyte in zpRegE0 und low byte in zpRegE1

  
   Since         : 31.07.2023
   Last modified : 31.07.2023
   ----------------------------------------------------------------------------
*/
convert565:     lda zpRegE0             // red value
                asl                     // shift three to the left as we
                asl                     // need to move the lower 5 bits of red
                asl                     // to the bits 7-5
                sta zpRegE0             // Save as the High Byte of the compressed color
                lda zpRegE1             // load green. We need the bits 3-5 to be the 
                lsr                     // lower bits of the output highbyte
                lsr
                lsr
                and #%00000111          // Only the lower three bits.
                ora zpRegE0             // combine this with the compressed red
                sta zpRegE0             // Store the final high byte
                lda zpRegE1             // Load green again. We need the lower three bits
                asl                     // Shift everything 5 bits to the left and fill
                asl                     // it with zeros
                asl
                asl
                asl
                sta zpRegE1             // Store the green part in the lowbyte of the result
                lda zpRegE2             // Load blue
                and #%00011111          // Only need the 5 lower bits.
                ora zpRegE1             // Combine it with the green fraction
                sta zpRegE1             // Store the final low byte of the compressed color
                rts

/* ============================================================================
                KERNAL DATA
   ----------------------------------------------------------------------------
*/
                * = $f000 "Kernel Data"

hex_chars:      .text "0123456789ABCDEF"
msg_01:         .text "Welcome to FirstKlaas OS v0.1"
