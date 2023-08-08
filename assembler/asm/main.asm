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

.macro PrintText(addr) {
    lda #<addr
    sta zpRegE0
    lda #>addr
    sta zpRegE1
    jsr print_text_
}

                .const AMBER        = 178

/* ============================================================================
                MAIN PROGRAM
   ----------------------------------------------------------------------------
*/
                * = $0800 "Main Program"
start:          ldx #$ff    // Set the stackpointer to
                txs         // highest possible position.
                EnableCursorAutoAdjustment()

                // Timer Test
                // Setting counter start value to 10 aka $000A
                lda #$f0
                sta $dc05       // Set hi-byte of timer A latch
                lda #$00
                sta $dc04       // Set low-byte of timer A latch
                lda #$81        // Bit 0: Timer A / Bit 7: Set bits
                sta $dc0d       // Enable timer A interrupt
                lda #%00011001  // Bit 4: Load values / Bit 0: Start timer / Bit 3: Stop Timer after IRQ 
                sta $dc0e       // Load values and start timer
                // End Test. Timer should now be running            

                jsr debug_register_
                
                SetCursorI(0,0)
                SetForgroundColorI(208)
                PrintText(border_top)
                SetCursorI(0,2)
                SetForgroundColorI(208)
                PrintText(border_bottom)

                SetCursorI(1,1)
                SetForgroundColorI(233)
                PrintText(text_bar)

                SetForgroundColorI(AMBER)
                SetCursorI(2,1)
                PrintText(welcome)

                // Spritetest
                jsr init_sprites_
end:
                jmp end

border_top:     .byte $c8,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc
                .byte $cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$ba,$00

border_bottom:  .byte $c7,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc
                .byte $cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$bb,$00

text_bar:       .fill 37,$da 
                .byte 0

welcome:        .encoding "ascii"
                .text "NE/OS v0.1 - Kernel Size 974 bytes"
                .byte 0
