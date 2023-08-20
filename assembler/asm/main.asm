.cpu _65c02
.macro EnableCursorAutoAdjustment() {
    lda DISCR   // Set the auto adjust 
    ora #$0C    // and wrap flag
    sta DISCR                
}

.macro EnableFrameIRQ() {
    lda #(CIA_SET_FLAGS | FRAME_INTERRUPT_FLAG)
    sta $dc0d
}

.macro DisableCursorAutoAdjustment() {
    lda DISCR   // Clear the auto adjust 
    and #$fd    // flag>
    sta DISCR                
}

.macro PrintText(addr) {
    lda #<addr
    sta zpRegE0
    lda #>addr
    sta zpRegE1
    jsr print_text_
}

.macro PrintFrameNumber(sx,sy) {
    SetCursorI(sx,sy)
    lda $d0fd       // Framecounter LO Byte
    sta HTD_IN
    lda $d0fe       // Framecounter HI Byte
    sta HTD_IN+1
    jsr bcd_convert_word_
    lda HTD_OUT+2
    HexPrintA()
    lda HTD_OUT+1
    HexPrintA()
    lda HTD_OUT
    HexPrintA()
}

// Colors
.const AMBER                    = 32

// CIA Contants
.const TIMER_A_INTERRUPT_FLAG   = $01
.const TIMER_B_INTERRUPT_FLAG   = $02
.const FRAME_INTERRUPT_FLAG     = $04
.const KBD_INTERRUPT_FLAG       = $08

.const CIA_SET_FLAGS            = $80


/* ============================================================================
                MAIN PROGRAM
   ----------------------------------------------------------------------------
*/
                * = $0800 "Main Program"
start:          ldx #$ff    // Set the stackpointer to
                txs         // highest possible position.

                jsr SpaceInvaders.init
                
                EnableCursorAutoAdjustment()
                EnableFrameIRQ()                

                SetForgroundColorI(AMBER)
                SetCursorI(2,1)
                PrintText(welcome)
                
!end:
                jmp !end-
            
setup_timer:
                // -----------------------------------------------------
                // Timer Test
                // Setting counter start value to 10 aka $000A
                // -----------------------------------------------------
                lda #$f0
                sta $dc05       // Set hi-byte of timer A latch
                lda #$00
                sta $dc04       // Set low-byte of timer A latch
                lda #$81        // Bit 0: Timer A / Bit 7: Set bits
                sta $dc0d       // Enable timer A interrupt
                lda #%00010001  // Bit 4: 1 = Load values from latch
                                // Bit 0: 1 = Start timer 
                                // Bit 3: 1 = Stop Timer after IRQ 
                sta $dc0e       // Load values and start timer
                // End Test. Timer should now be running and trigger 
                // an interrupt to enter the ISR           
                rts

// ########################################################################################

welcome:        .encoding "ascii"
                .text "NE/OS v0.1 - FirstKlaas Experience"
                .byte 0

txt_frame:      .encoding "ascii"
                .text "FRAME:"
                .byte 0

txt_level:      .encoding "ascii"
                .text "LEVEL"
                .byte 0

txt_score:      .encoding "ascii"
                .text "SCORE"
                .byte 0


