


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
                    HexPrintAddr(DIS_00)
                    PrintCharI(' ')
                    HexPrintAddr(DIS_01)
                    PrintCharI(' ')
                    HexPrintAddr(DIS_02)
                    PrintCharI(' ')
                    HexPrintAddr(DIS_03)
                    SetCursorI(40,3)
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