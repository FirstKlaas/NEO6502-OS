.macro DRAW_HLINE_I(xlo, xhi, y, lenlo, lenhi, col) {
    pha
    lda #xlo
    sta DIS00
    lda #xhi 
    sta DIS01
    lda y 
    sta DIS02
    lda lenlo 
    sta DIS03
    lda lenhi
    sta DIS04
    lda col
    sta DIS05
    jsr draw_horizonal_line_
    pla 
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
draw_horizonal_line_    : {
                lda #CMD_DRAW_HLINE
                sta DISCMD
                lda DISCR
                ora #$80
                sta DISCR               // Raise the IRQ flag
wait_for_ready:
                bit DISCR               // Check, if the excecution/irg flag is cleared
                bmi wait_for_ready      // No! Let's wait
}