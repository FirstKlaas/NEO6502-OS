.cpu _65c02

// --------------------------------
// NEO6502 OS V0.0.1
// --------------------------------
// @author: <klaas.nebuhr@gmal.com>
// @version: 0.0.1
//
// Documentation for the CIA: https://www.c64-wiki.de/wiki/CIA#CIA_1

.import source "asm/macros.asm"
.import source "asm/constants.asm"

                
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

/* ============================================================================
                KERNEL MAIN
   ----------------------------------------------------------------------------
*/
.import source "asm/main.asm"


/* ============================================================================
                KERNEL ROUTINES [STABLE JUMP TABLE]
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


                * = $E100 "Kernel Routines"

.import source "asm/math.asm"
.import source "asm/color.asm"
.import source "asm/kernel_text_routines.asm"
.import source "asm/kernel_graphic_primitives.asm"
.import source "asm/ui.asm"
.import source "asm/sprites.asm"

// Starts at 0x1000
.import source "asm/space_invaders/main.asm"

/* ============================================================================
                KERNAL DATA
   ----------------------------------------------------------------------------
*/
.import source "asm/kernel_data.asm"
