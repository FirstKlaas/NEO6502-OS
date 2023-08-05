debug_register_:    lda #40
                    jsr set_cursor_x
                    lda #1
                    jsr set_cursor_y
                    lda #$fe
                    jsr print_hex_
                    rts
