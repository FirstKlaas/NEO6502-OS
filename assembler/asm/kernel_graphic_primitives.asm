.macro DRAW_HLINE_I(xlo, xhi, y, lenlo, lenhi, col) {
    pha
    lda #xlo
    sta DIS00
    lda #xhi 
    sta DIS01
    lda #y 
    sta DIS02
    lda #lenlo 
    sta DIS03
    lda #lenhi
    sta DIS04
    lda #col
    sta DIS05
    jsr GFX.draw_horizonal_line_
    pla 
}

.macro FILL_RECT_I(xlo, xhi, y, width_lo, width_hi, height,col) {
    pha
    lda #xlo
    sta DIS00
    lda #xhi 
    sta DIS01
    lda #y 
    sta DIS02
    lda #width_lo 
    sta DIS03
    lda #width_hi
    sta DIS04
    lda #height
    sta DIS05
    lda #col 
    sta DIS06
    jsr GFX.fill_rect_
    pla 
}

.macro DRAW_RECT_I(xlo, xhi, y, width_lo, width_hi, height,col) {
    pha
    lda #xlo
    sta DIS00
    lda #xhi 
    sta DIS01
    lda #y 
    sta DIS02
    lda #width_lo 
    sta DIS03
    lda #width_hi
    sta DIS04
    lda #height
    sta DIS05
    lda #col 
    sta DIS06
    jsr GFX.draw_rect_
    pla 
}

.macro DRAW_SPRITES() {
    jsr GFX.draw_sprites_
}

.macro FILL_SCREEN_A() {
    sta DIS00
    jsr GFX.fill_screen_
}

.macro FILL_SCREEN_I(color) {
    lda #color 
    FILL_SCREEN_A()
}

.macro FILL_SCREEN_M(color) {
    lda color
    FILL_SCREEN_A()
}

.namespace GFX {

    .macro EXECUTE_DISPLAY_COMMAND_A() {
        sta DISCMD
        lda DISCR
        ora #$80
        sta DISCR               // Raise the IRQ flag
    !wait_for_ready:
        bit DISCR               // Check, if the excecution/irg flag is cleared
        bmi !wait_for_ready-    // No! Let's wait
    }

    /* ----------------------------------------------------------------------------
        Draw a horizontal line.
    
        Params In:
            DIS00 XPOS_LO    
            DIS01 XPOS_HI   
            DIS02 YPOS      
            DIS03 LENGTH_LO  
            DIS04 LENGTH_HI 
            DIS05 COLOR     

        Params Out:
            None

        Since         : 15.08.2023
        Last modified : 15.08.2023
    ----------------------------------------------------------------------------
    */
    draw_horizonal_line_: {
        lda #CMD_DRAW_HLINE
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    /* ----------------------------------------------------------------------------
        Draw a horizontal line.
    
        Params In:
            DIS00 XPOS_LO    
            DIS01 XPOS_HI   
            DIS02 YPOS      
            DIS03 LENGTH_LO  
            DIS04 LENGTH_HI 
            DIS05 COLOR     

        Params Out:
            None

        Since         : 15.08.2023
        Last modified : 15.08.2023
    ----------------------------------------------------------------------------
    */
    draw_vertical_line_: {
        lda #CMD_DRAW_VLINE
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    clear_screen_: {
        lda #CMD_CLEAR_SCREEN
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    draw_rect_: {
        lda #CMD_DRAW_RECT
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    fill_rect_: {
        lda #CMD_FILL_RECT
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    draw_sprites_: {
        lda #CMD_DRAW_SPRITES
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    draw_pixel_: {
        lda #CMD_DRAW_PIXEL
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    draw_bitmap_: {
        lda #CMD_DRAW_BITMAP
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    draw_circle_: {
        lda #CMD_DRAW_CIRCLE
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    fill_circle_: {
        lda #CMD_FILL_CIRCLE
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    draw_triangle_: {
        lda #CMD_DRAW_TRIANGLE
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    fill_triangle_: {
        lda #CMD_FILL_TRIANGLE
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    draw_round_rect_: {
        lda #CMD_DRAW_ROUND_RECT
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    fill_round_rect_: {
        lda #CMD_FILL_ROUND_RECT
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    fill_screen_: {
        lda #CMD_FILL_SCREEN
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    draw_line_: {
        lda #CMD_DRAW_LINE 
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }

    draw_char_: {
        lda #CMD_DRAW_CHAR
        EXECUTE_DISPLAY_COMMAND_A()
        rts
    }
}