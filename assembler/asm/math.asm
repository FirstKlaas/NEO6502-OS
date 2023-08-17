.cpu _65c02
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
    phx
    pha
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
    pla
    plx 
    rts
}

// AX+ Tinyrand8
// A fast 8-bit random generator with an internal 16bit state
//
// Algorithm, implementation and evaluation by Wil
// This version stores the seed as arguments and uses self-modifying code
// The name AX+ comes from the ASL, XOR and addition operation
//
// Size: 15 Bytes (not counting the set_seed function)
// Execution time: 18 (without RTS)
// Period 59748
// Source: https://codebase64.org/doku.php?id=base:ax_tinyrand8

rand8:	
	lda rand8b1:#31
	asl
	eor rand8a1:#53
	sta rand8b1
	adc rand8a1
	sta rand8a1
	rts

// sets the seed based on the value in A
// always sets a1 and b1 so that a cycle with maximum period is chosen
// constants 217 and 21263 have been derived by simulation
set_seed:
	pha
	and #217
	clc
	adc #<21263
	sta rand8a1
	pla
	and #255-217
	adc #>21263
	sta rand8b1
	rts