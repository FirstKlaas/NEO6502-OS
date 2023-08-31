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

.macro DisableFrameIRQ() {
    lda #FRAME_INTERRUPT_FLAG
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
    sei
    lda #<label
    sta $fffa 
    lda #>label
    sta $fffb
    cli
}

.macro SetVectorIRQ(label) {
    sei
    lda #<label
    sta $fffe 
    lda #>label
    sta $ffff
    cli
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

// Lowbyte in DIS00 Highbyte in DIS03 (32 Bit)
.macro GetClockCycle() {
    jsr GFX.get_clock_cycle
}

.macro GetClockCycleAndSave() {
    GetClockCycle()
    // Data is in DIS00-DIS03
    ldx #3
!ccl:
    lda DIS00,x 
    sta zpRegFC,x
    dex 
    bpl !ccl-
}


// Get current clockcycle and subtract it
// from zpRegFC:zpRegFF 
// The result is stored back to zpRegFC:zpRegFF 
.macro GetClockCyleDelta() {
    GetClockCycle()
    sec 
    lda DIS00
    sbc zpRegFC
    sta zpRegFC
    lda DIS01
    sbc zpRegFD 
    sta zpRegFD
    lda DIS02 
    sbc zpRegFE 
    sta zpRegFE 
    lda DIS03 
    sbc zpRegFF
    sta zpRegFF 
}

.macro PrintClockCycleDelta() {
    GetClockCyleDelta()
    HexPrintM(zpRegFF)
    HexPrintM(zpRegFE)
    HexPrintM(zpRegFD)
    HexPrintM(zpRegFC)
}
.macro PrintFrameNumber(sx,sy) {
    SetCursor_I(sx,sy)
    lda $d0fd       // Framecounter LO Byte
    sta zpRegE0
    lda $d0fe       // Framecounter HI Byte
    sta zpRegE1
    jsr Math.bcd_convert_word_
    lda zpRegE4
    HexPrintA()
    lda zpRegE3
    HexPrintA()
    lda zpRegE2
    HexPrintA()
}

.macro WriteDebugNumberI(code) {
    lda #code
    sta DEBUG
}
