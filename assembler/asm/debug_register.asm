debug_register_:    lda #40             // X Position
                    jsr set_cursor_x    
                    lda #1              // Y Position
                    jsr set_cursor_y
                    lda #$fe            // Testwert, der ausgegeben werden soll
                    jsr print_hex_
                    lda #' '
                    jsr print_char_
                    lda #$0b            // Testwert, der ausgegeben werden soll
                    jsr print_hex_
                    rts
