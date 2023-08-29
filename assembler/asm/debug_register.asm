


debug_register_:    SetCursor_I(40,1)
                    SetForgroundColor_I(152)
                    lda #<debug_txt_01
                    sta zpRegE0
                    lda #>debug_txt_01
                    sta zpRegE1
                    jsr print_text_

                    SetForgroundColor_I(COLOR_YELLOW)
                    SetCursor_I(46,1)
                    HexPrintM(DISCMD)    // command register
                    PrintCharI(' ')
                    HexPrintM(DISCR)     // Print the control register
                    SetCursor_I(40,2)
                    HexPrintM(DIS00)
                    PrintCharI(' ')
                    HexPrintM(DIS01)
                    PrintCharI(' ')
                    HexPrintM(DIS02)
                    PrintCharI(' ')
                    HexPrintM(DIS03)
                    SetCursor_I(40,3)
                    HexPrintM(DIS04)
                    PrintCharI(' ')
                    HexPrintM(DIS05)
                    PrintCharI(' ')
                    HexPrintM(DIS06)
                    PrintCharI(' ')
                    HexPrintM(DIS07)
                    rts

debug_txt_01:       .encoding "ascii"
                    .text "DISPL"
                    .byte 0