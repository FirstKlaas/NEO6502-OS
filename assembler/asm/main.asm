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
                
                SetCursorI(0,0)
                SetForgroundColorI(COLOR_GREEN)
                lda #<border_top
                sta zpRegE0
                lda #>border_top
                sta zpRegE1
                jsr print_text_

                SetForgroundColorI(COLOR_AMBER)
                SetCursorI(2,1)
                lda #<welcome
                sta zpRegE0
                lda #>welcome
                sta zpRegE1
                jsr print_text_
end:
                jmp end

border_top:     .byte $c8,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc
                .byte $cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$ba,$00

welcome:        .encoding "ascii"
                .text "Welcome to the pleasure Dome!"
                .byte 0
