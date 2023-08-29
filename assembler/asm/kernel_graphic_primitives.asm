.macro DrawHLine_I(xlo, xhi, y, lenlo, lenhi, col) {
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


.macro FillRect_I(xlo, xhi, y, width_lo, width_hi, height,col) {
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

.macro DrawRect_I(xlo, xhi, y, width_lo, width_hi, height,col) {
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

.macro FillCircle_I(xlo,xhi,y,rad,color) {
    lda #xlo
    sta DIS00
    lda #xhi
    sta DIS01
    lda #y
    sta DIS02
    lda #rad
    sta DIS03
    lda #color 
    sta DIS04 
    jsr GFX.fill_circle_ 
}

.macro DrawSprites() {
    jsr GFX.draw_sprites_
}

.macro FillScreen_A() {
    sta DIS00
    jsr GFX.fill_screen_
}

.macro FillScreen_I(color) {
    lda #color 
    FillScreen_A()
}

.macro FillScreen_M(color) {
    lda color
    FillScreen_A()
}



.namespace GFX {

    .macro ExecuteDisplayCommand_A() {
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
        ExecuteDisplayCommand_A()
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

        Clobbered Register: A
        Used Zeropage Variables: None

        Since         : 15.08.2023
        Last modified : 15.08.2023
    ----------------------------------------------------------------------------
    */
    draw_vertical_line_: {
        lda #CMD_DRAW_VLINE
        ExecuteDisplayCommand_A()
        rts
    }

    clear_screen_: {
        lda #CMD_CLEAR_SCREEN
        ExecuteDisplayCommand_A()
        rts
    }

    draw_rect_: {
        lda #CMD_DRAW_RECT
        ExecuteDisplayCommand_A()
        rts
    }

    fill_rect_: {
        lda #CMD_FILL_RECT
        ExecuteDisplayCommand_A()
        rts
    }

    draw_sprites_: {
        lda #CMD_DrawSprites
        ExecuteDisplayCommand_A()
        rts
    }

    draw_pixel_: {
        lda #CMD_DRAW_PIXEL
        ExecuteDisplayCommand_A()
        rts
    }

    draw_bitmap_: {
        lda #CMD_DRAW_BITMAP
        ExecuteDisplayCommand_A()
        rts
    }

    draw_circle_: {
        lda #CMD_DRAW_CIRCLE
        ExecuteDisplayCommand_A()
        rts
    }

    fill_circle_: {
        lda #CMD_FILL_CIRCLE
        ExecuteDisplayCommand_A()
        rts
    }

    draw_triangle_: {
        lda #CMD_DRAW_TRIANGLE
        ExecuteDisplayCommand_A()
        rts
    }

    fill_triangle_: {
        lda #CMD_FILL_TRIANGLE
        ExecuteDisplayCommand_A()
        rts
    }

    draw_round_rect_: {
        lda #CMD_DRAW_ROUND_RECT
        ExecuteDisplayCommand_A()
        rts
    }

    fill_round_rect_: {
        lda #CMD_FILL_ROUND_RECT
        ExecuteDisplayCommand_A()
        rts
    }

    fill_screen_: {
        lda #CMD_FILL_SCREEN
        ExecuteDisplayCommand_A()
        rts
    }

    draw_line_: {
        lda #CMD_DRAW_LINE 
        ExecuteDisplayCommand_A()
        rts
    }

    draw_char_: {
        lda #CMD_DRAW_CHAR
        ExecuteDisplayCommand_A()
        rts
    }

    get_clock_cycle:
        lda #CMD_GET_CLOCK_CYCLE
        ExecuteDisplayCommand_A()
        rts

    get_millis: {
        lda #CMD_GET_MILLIS
        ExecuteDisplayCommand_A()
        rts
    }

    get_frame_time: {
        lda #CMD_GET_FRAME_TIME
        ExecuteDisplayCommand_A()
        rts
    }
}