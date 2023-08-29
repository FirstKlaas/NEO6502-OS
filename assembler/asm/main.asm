.cpu _65c02
/* ============================================================================
                MAIN PROGRAM
   ----------------------------------------------------------------------------
*/
                * = $0800 "Main Program"
start:          ldx #$ff    // Set the stackpointer to
                txs         // highest possible position.

                DisableAllIRQ()
                EnableCursorAutoAdjustment()
                FillScreen_I(STD_BACKGROUND_COLOR)
                SetForgroundColor_I(TITLE_FG_COLOR)
                SetCursor_I(2,1)
                PrintText(welcome)
                SetForgroundColor_I(STD_FOREGROUND_COLOR)

                // Print the main menu
                FillCircle_I(63,0,84,8,27)                
                SetCursor_I(10,10)
                PrintText(txt_menue_1)
                SetCursor_I(10,12)
                PrintText(txt_menue_2)

                //jsr TestPrimitives.all
                // Set isr vector for IRQ and NMI
                // As IRQ currently does not work,
                // we install the ISR on both. 
                // NMI and IRQ
                SetVectorNMI(test_isr)
                SetVectorIRQ(test_isr)
                //SetVectorNMI(kernel_isr)

                EnableFrameIRQ()   
                //EnableKeyboardIRQ()             
endless:        
                lda PROGRAM_ADR_CR
                bpl endless
                DisableAllIRQ()
                jsr SpaceInvaders.run
                jmp *
                //jmp (PROGRAM_ADR_LO)
            
PROGRAM_ADR_LO: .byte 0
PROGRAM_ADR_HI: .byte 0
PROGRAM_ADR_CR: .byte 0

.import source "asm/test_primitives.asm"

test_isr: {
        pha
        phx
        phy

        AcknowledgeIRQ()
        // Printing the frame numer to the screen
        FillRect_I(0,0,22*FONT_CHAR_HEIGHT,0,100,3*FONT_CHAR_HEIGHT,4)
        PrintFrameNumber(9,23)
        SetCursor_I(2,26)
        PrintText(txt_frame)

        dec GAME_COUNTDOWN
        bne exit
        lda #<SpaceInvaders.run
        sta PROGRAM_ADR_LO
        lda #>SpaceInvaders.run
        sta PROGRAM_ADR_HI
        lda #$80
        sta PROGRAM_ADR_CR
exit:        
        ply 
        plx 
        pla 
        rti
    }

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

// Default kernel interrupt routine.

IRQ_DATA:       .byte $00
GAME_COUNTDOWN: .byte $ff


kernel_isr: {
    pha
    phx
    phy
    AcknowledgeIRQ()
    dec GAME_COUNTDOWN
    bne exit
    lda #$80
    sta PROGRAM_ADR_CR
    jmp exit

    //bpl exit           // No IRQ. Should never happen. Only relevant, when polling            
start_isr:
    sta IRQ_DATA
    sta DEBUG
test_frame_irq:
    lda #FRAME_INTERRUPT_FLAG
    bit IRQ_DATA
    beq test_keyboard
    // We have a frame intterrupt
    jmp exit

test_keyboard:
    lda #KBD_INTERRUPT_FLAG
    bit IRQ_DATA
    beq test_timer_a 
    jsr handle_key_event
    jmp exit

test_timer_a:
    lda #TIMER_A_INTERRUPT_FLAG
    bit IRQ_DATA
    beq test_timer_b
    jmp exit

test_timer_b:
    lda #TIMER_B_INTERRUPT_FLAG
    bit IRQ_DATA
    beq exit

exit:  
    ply 
    plx 
    pla 
    rti
}


handle_key_event: {
    lda KBD
    cmp #$32    // Key 2
    bne exit
    // Clear IRQs
    WriteDebugNumberI($ea) 
    lda #CIA_IRQ_MASK
    sta REG_CIA_ICR
    FillScreen_I(AMBER)
    // Start Game
    FillScreen_I(63)
    //jsr SpaceInvaders.init
    lda #$80
    sta PROGRAM_ADR_CR

exit:
    rts
}

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

txt_menue_1:    .encoding "ascii"
                .text "1  Load program"
                .byte 0

txt_menue_2:    .encoding "ascii"
                .text "2  Play Space Invaders"
                .byte 0


