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
    jsr draw_horizonal_line_
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
    jsr fill_rect_
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
    jsr draw_rect_
    pla 
}

.macro DRAW_SPRITES() {
    jsr draw_sprites_
}

.macro EXECUTE_DISPLAY_COMMAND_A() {
    sta DISCMD
    lda DISCR
    ora #$80
    sta DISCR               // Raise the IRQ flag
wait_for_ready:
    bit DISCR               // Check, if the excecution/irg flag is cleared
    bmi wait_for_ready      // No! Let's wait
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


