.macro EnableCursorAutoAdjustment() {
    lda DISCR   // Set the auto adjust 
    ora #$0C    // and wrap flag
    sta DISCR                
}

.macro DisableCursorAutoAdjustment() {
    lda DISCR   // Clear the auto adjust 
    and #$fd    // flag
    sta DISCR                
}


/* ============================================================================
                MAIN PROGRAM
   ----------------------------------------------------------------------------
*/
                * = $0800 "Main Program"
start:          ldx #$ff    // Set the stackpointer to
                txs         // highest possible position.
                EnableCursorAutoAdjustment()

                jsr debug_register_
                
                lda #1
                jsr set_cursor_y_
                lda #0
                jsr set_cursor_x_
                lda #3
                jsr set_fg_color_
                ldx #60
loop:           
                lda #'A'
                jsr print_char_
                dex
                bne loop
end:
                jmp end
