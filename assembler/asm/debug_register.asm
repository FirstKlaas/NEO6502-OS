


debug_register_:    SetCursorI(40,1)
                    SetForgroundColorI(152)
                    lda #<debug_txt_01
                    sta zpRegE0
                    lda #>debug_txt_01
                    sta zpRegE1
                    jsr print_text_

                    SetForgroundColorI(COLOR_YELLOW)
                    SetCursorI(46,1)
                    HexPrintAddr(DISCMD)    // command register
                    PrintCharI(' ')
                    HexPrintAddr(DISCR)     // Print the control register
                    SetCursorI(40,2)
                    HexPrintAddr(DIS00)
                    PrintCharI(' ')
                    HexPrintAddr(DIS01)
                    PrintCharI(' ')
                    HexPrintAddr(DIS02)
                    PrintCharI(' ')
                    HexPrintAddr(DIS03)
                    SetCursorI(40,3)
                    HexPrintAddr(DIS04)
                    PrintCharI(' ')
                    HexPrintAddr(DIS05)
                    PrintCharI(' ')
                    HexPrintAddr(DIS06)
                    PrintCharI(' ')
                    HexPrintAddr(DIS07)
                    rts

debug_txt_01:       .encoding "ascii"
                    .text "DISPL"
                    .byte 0