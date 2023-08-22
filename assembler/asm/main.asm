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

.macro EnableKeyboardIRQ() {
    lda #(CIA_SET_FLAGS | KBD_INTERRUPT_FLAG)
    sta $dc0d
}

.macro DisableAllIRQ() {
    lda #CIA_IRQ_MASK
    sta REG_CIA_ICR
}

.macro SetVectorNMI(label) {
    lda #<label
    sta $fffa 
    lda #>label
    sta $fffb
}

.macro SetVectorIRQ(label) {
    lda #<label
    sta $fffe 
    lda #>label
    sta $ffff
}

.macro AcknowledgeIRQ() {
    lda REG_CIA_ICR
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

.macro WriteDebugNumberI(code) {
    lda #code
    sta DEBUG
}

// Colors
.const AMBER                    = 32

// CIA Contants
.const TIMER_A_INTERRUPT_FLAG   = $01
.const TIMER_B_INTERRUPT_FLAG   = $02
.const FRAME_INTERRUPT_FLAG     = $04
.const KBD_INTERRUPT_FLAG       = $08

.const CIA_SET_FLAGS            = $80

.const STD_BACKGROUND_COLOR     =  41
.const STD_FOREGROUND_COLOR     =  31
.const TITLE_FG_COLOR           =  46
.const FONT_CHAR_WIDTH          =   6
.const FONT_CHAR_HEIGHT         =   8
.const SCREEN_WIDTH             = 320
.const SCREEN_HEIGHT            = 240
.const LINECHARS                =  52
.const LINES                    = SCREEN_HEIGHT / (FONT_CHAR_HEIGHT + 1)



/* ============================================================================
                MAIN PROGRAM
   ----------------------------------------------------------------------------
*/
                * = $0800 "Main Program"
start:          ldx #$ff    // Set the stackpointer to
                txs         // highest possible position.

                EnableCursorAutoAdjustment()
                FILL_SCREEN_I(STD_BACKGROUND_COLOR)
                SetForgroundColorI(TITLE_FG_COLOR)
                SetCursorI(2,1)
                PrintText(welcome)
                SetForgroundColorI(STD_FOREGROUND_COLOR)

                // Print the main menu                
                SetCursorI(10,10)
                PrintText(txt_menue_1)
                SetCursorI(10,12)
                PrintText(txt_menue_2)

                // Set isr vector for IRQ and NMI
                // As IRQ currently does not work,
                // we install the ISR on both. 
                // NMI and IRQ
                lda #<kernel_isr
                sta $fffe 
                sta $fffa 
                lda #>kernel_isr
                sta $ffff
                sta $fffb

                //EnableFrameIRQ()   
                EnableKeyboardIRQ()             
                //jsr SpaceInvaders.init
                
endless:        lda PROGRAM_ADR_CR
                bpl endless 
                WriteDebugNumberI($12)
                // Programm should be called
                lda #0
                sta PROGRAM_ADR_CR
                FILL_SCREEN_I(34)
                jmp SpaceInvaders.init
                jmp *
                jmp (PROGRAM_ADR_LO)
            
PROGRAM_ADR_LO: .byte 0
PROGRAM_ADR_HI: .byte 0
PROGRAM_ADR_CR: .byte 0

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

IRQ_DATA: .byte $00

kernel_isr: {
    pha
    phx
    phy
    WriteDebugNumberI($55)
    lda $dc0d            // Acknowledge the IRQ
    //bpl exit           // No IRQ. Should never happen. Only relevant, when polling            
    sta IRQ_DATA
    sta DEBUG
test_frame_irq:
    lda #FRAME_INTERRUPT_FLAG
    bit IRQ_DATA
    beq test_keyboard
    // We have a frame intterrupt
    WriteDebugNumberI($66)
    jmp exit

test_keyboard:
    lda #KBD_INTERRUPT_FLAG
    bit IRQ_DATA
    beq test_timer_a 
    // We have an keyboard interrupt.
    WriteDebugNumberI($77)
    jsr handle_key_event
    jmp exit

test_timer_a:
    lda #TIMER_A_INTERRUPT_FLAG
    bit IRQ_DATA
    beq test_timer_b
    // We have an timer a interrupt.
    WriteDebugNumberI($88)
    jmp exit

test_timer_b:
    lda #TIMER_B_INTERRUPT_FLAG
    bit IRQ_DATA
    beq exit
    // We have an timer b interrupt.
    WriteDebugNumberI($99)

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
    FILL_SCREEN_I(AMBER)
    // Start Game
    FILL_SCREEN_I(63)
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
                .text "[1] Load program"
                .byte 0

txt_menue_2:    .encoding "ascii"
                .text "[2] Play Space Invaders"
                .byte 0


