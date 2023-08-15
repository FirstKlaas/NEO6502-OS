// http://www.6502.org/source/integers/hex2dec.htm
// Converting byte and word to BCD code.


BCD_LOOKUP_TABLE:
    .byte    $00, $00, $01, $00, $00, $02, $00, $00, $04, $00, $00, $08
    .byte    $00, $00, $16, $00, $00, $32, $00, $00, $64, $00, $01, $28
    .byte    $00, $02, $56, $00, $05, $12, $00, $10, $24, $00, $20, $48
    .byte    $00, $40, $96, $00, $81, $92, $01, $63, $84, $03, $27, $68

HTD_IN:     .byte $00, $00
HTD_OUT:    .byte $00, $00, $00 

bcd_convert_word_: {
    sed 
    lda #0
    sta HTD_OUT
    sta HTD_OUT+1
    sta HTD_OUT+2
    ldx #$2d
!loop:
    asl HTD_IN 
    rol HTD_IN+1
    bcc htd1
    lda HTD_OUT
    clc 
    adc BCD_LOOKUP_TABLE+2,x
    sta HTD_OUT
    lda HTD_OUT+1
    adc BCD_LOOKUP_TABLE+1,x
    sta HTD_OUT+1
    lda HTD_OUT+2
    adc BCD_LOOKUP_TABLE,x
    sta HTD_OUT+2
htd1:
    dex
    dex 
    dex 
    bpl !loop- 
    cld 
    rts
}