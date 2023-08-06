

.macro SetCursor(xpos, ypos) {
    lda #xpos
    jsr set_cursor_x_
    lda #ypos
    jsr set_cursor_y_    
}

.macro HexPrintAddr(addr) {
    lda addr
    jsr print_hex_
}

.macro SetForgroundColorI(color) {
    lda #color
    jsr set_fg_color_
}

.macro PrintCharI(char) {
    lda #char
    jsr print_char_
}

debug_register_:    SetCursor(40,1)
                    SetForgroundColorI(COLOR_GREEN)
                    lda #<debug_txt_01
                    sta zpRegE0
                    lda #>debug_txt_01
                    sta zpRegE1
                    jsr print_text_

                    SetForgroundColorI(COLOR_MAGENTA)
                    SetCursor(46,1)
                    HexPrintAddr(DISCMD)    // command register
                    PrintCharI(' ')
                    HexPrintAddr(DISCR)     // Print the control register
                    SetCursor(40,2)
                    HexPrintAddr(DIS_00)
                    PrintCharI(' ')
                    HexPrintAddr(DIS_01)
                    PrintCharI(' ')
                    HexPrintAddr(DIS_02)
                    PrintCharI(' ')
                    HexPrintAddr(DIS_03)
                    SetCursor(40,3)
                    HexPrintAddr(DIS_04)
                    PrintCharI(' ')
                    HexPrintAddr(DIS_05)
                    PrintCharI(' ')
                    HexPrintAddr(DIS_06)
                    PrintCharI(' ')
                    HexPrintAddr(DIS_07)
                    rts

debug_txt_01:       .encoding "ascii"
                    .text "DISPL"
                    .byte 0