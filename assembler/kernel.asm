.cpu _65c02

// --------------------------------
// NEO6502 OS V0.0.1
// --------------------------------
// @author: <klaas.nebuhr@gmal.com>
// @version: 0.0.1
//
// Documentation for the CIA: https://www.c64-wiki.de/wiki/CIA#CIA_1

.macro EnableCursorAutoAdjustment() {
    lda DISCR   // Set the auto adjust 
    ora #$0C    // and wrap flag
    sta DISCR                
}

.macro EnableFrameIRQ() {
    lda #(CIA_SET_FLAGS | FRAME_INTERRUPT_FLAG)
    sta $dc0d
}

.macro DisableFrameIRQ() {
    lda #FRAME_INTERRUPT_FLAG
    sta $dc0d
}

.macro EnableKeyboardIRQ() {
    lda #(CIA_SET_FLAGS | KBD_INTERRUPT_FLAG)
    sta $dc0d
}

.macro DisableAllIRQ() {
    lda #CIA_IRQ_MASK
    sta REG_CIA_ICR
}

.macro SetVectorNMI(label) {
    sei
    lda #<label
    sta $fffa 
    lda #>label
    sta $fffb
    cli
}

.macro SetVectorIRQ(label) {
    sei
    lda #<label
    sta $fffe 
    lda #>label
    sta $ffff
    cli
}

.macro AcknowledgeIRQ() {
    lda REG_CIA_ICR
}

.macro DisableCursorAutoAdjustment() {
    lda DISCR   // Clear the auto adjust 
    and #$fd    // flag>
    sta DISCR                
}

.macro PrintText(addr) {
    lda #<addr
    sta zpRegE0
    lda #>addr
    sta zpRegE1
    jsr print_text_
}

// Lowbyte in DIS00 Highbyte in DIS03 (32 Bit)
.macro GetClockCycle() {
    jsr GFX.get_clock_cycle
}

.macro GetClockCycleAndSave() {
    GetClockCycle()
    // Data is in DIS00-DIS03
    ldx #3
!ccl:
    lda DIS00,x 
    sta zpRegFC,x
    dex 
    bpl !ccl-
}


// Get current clockcycle and subtract it
// from zpRegFC:zpRegFF 
// The result is stored back to zpRegFC:zpRegFF 
.macro GetClockCyleDelta() {
    GetClockCycle()
    sec 
    lda DIS00
    sbc zpRegFC
    sta zpRegFC
    lda DIS01
    sbc zpRegFD 
    sta zpRegFD
    lda DIS02 
    sbc zpRegFE 
    sta zpRegFE 
    lda DIS03 
    sbc zpRegFF
    sta zpRegFF 
}

.macro PrintClockCycleDelta() {
    GetClockCyleDelta()
    HexPrintM(zpRegFF)
    HexPrintM(zpRegFE)
    HexPrintM(zpRegFD)
    HexPrintM(zpRegFC)
}
.macro PrintFrameNumber(sx,sy) {
    SetCursorI(sx,sy)
    lda $d0fd       // Framecounter LO Byte
    sta Math.HTD_IN
    lda $d0fe       // Framecounter HI Byte
    sta Math.HTD_IN+1
    jsr Math.bcd_convert_word_
    lda Math.HTD_OUT+2
    HexPrintA()
    lda Math.HTD_OUT+1
    HexPrintA()
    lda Math.HTD_OUT
    HexPrintA()
}

.macro WriteDebugNumberI(code) {
    lda #code
    sta DEBUG
}

// Colors
.const AMBER                    = 32

// CIA Contants
.const TIMER_A_INTERRUPT_FLAG   = $01
.const TIMER_B_INTERRUPT_FLAG   = $02
.const FRAME_INTERRUPT_FLAG     = $04
.const KBD_INTERRUPT_FLAG       = $08

.const CIA_SET_FLAGS            = $80

.const STD_BACKGROUND_COLOR     =  41
.const STD_FOREGROUND_COLOR     =  31
.const TITLE_FG_COLOR           =  46
.const FONT_CHAR_WIDTH          =   6
.const FONT_CHAR_HEIGHT         =   8
.const SCREEN_WIDTH             = 320
.const SCREEN_HEIGHT            = 240
.const LINECHARS                =  52
.const LINES                    = SCREEN_HEIGHT / (FONT_CHAR_HEIGHT + 1)


.const KBD    = $d010       // Keyboard regster
.const KBDCR  = $d011       // Keyboard control register
.const DIS    = $d012       // Display register
.const DISCR  = $d013       // Display control register
                            // Bit 7 $80: Execute Command
                            // Bit 6 $40: undefined
                            // Bit 5 $20: undefined
                            // Bit 4 $10: Autoclean screen
                            // Bit 3 $08: Text and colorbuf
                            // Bit 2 $04: Autoadjust Cursor
                            // Bit 1 $02: Show Cursor
                            // Bit 0 $01: Sprite activation 

.const DISCMD = $d014       // Display command register
.const DIS00 = $d015        // Data exchange register 
.const DIS01 = $d016        // Data exchange register 
.const DIS02 = $d017        // Data exchange register 
.const DIS03 = $d018        // Data exchange register 
.const DIS04 = $d019        // Data exchange register 
.const DIS05 = $d01A        // Data exchange register 
.const DIS06 = $d01B        // Data exchange register 
.const DIS07 = $d01C        // Data exchange register
.const DIS08 = $d01D        // Data exchange register
.const DIS09 = $d01E        // Data exchange register

.const DISFL = $d0fd        // Frame number lo
.const DISFH = $d0fe        // Frame number hi
.const DEBUG = $d0ff        // Debug register

// CIA register and constants
.const REG_CIA_ICR  = $dc0d
.const CIA_IRQ_MASK = %01111111
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
.const CMD_DRAW_CHAR        = $25

.const CMD_GET_CLOCK_CYCLE  = $30
                
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

.namespace KRNL {
    .macro HALT() {
        // Any write to $ffee will halt the cpu
        lda #5  
        sta $ffee
    }
}

.import source "asm/main.asm"

/* ============================================================================
                KERNAL ROUTINES
   ----------------------------------------------------------------------------
*/
                * = $E000 "Kernel Routines Entry Points"

.namespace KRNL {
    get_key:            jmp get_key_
    set_cursor_x:       jmp set_cursor_x_
    set_cursor_y:       jmp set_cursor_y_
    print_char:         jmp print_char_

    draw_pixel:         jmp GFX.draw_pixel_
    draw_line:          jmp GFX.draw_line_
    draw_hline:         jmp GFX.draw_horizonal_line_ 
    draw_vline:         jmp GFX.draw_vertical_line_
    draw_rect:          jmp GFX.draw_rect_
    fill_rect:          jmp GFX.fill_rect_
    draw_circle:        jmp GFX.draw_circle_
    fill_circle:        jmp GFX.fill_circle_
    draw_triangle:      jmp GFX.draw_triangle_
    fill_triangle:      jmp GFX.fill_triangle_
    draw_round_rect:    jmp GFX.draw_round_rect_
    fill_round_rect:    jmp GFX.fill_round_rect_
    draw_char:          jmp GFX.draw_char_
}



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
.import source "asm/color.asm"
.import source "asm/kernel_text_routines.asm"
.import source "asm/kernel_graphic_primitives.asm"

// Starts at 0x1000
.import source "asm/space_invaders/main.asm"

/* ============================================================================
                KERNAL DATA
   ----------------------------------------------------------------------------
*/
                * = $f000 "Kernel Data"

hex_chars:      .text "0123456789ABCDEF"
msg_01:         .text "NE/OS v0.2 by FirstKlaas 2023"
