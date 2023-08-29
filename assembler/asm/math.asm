.cpu _65c02

.namespace Math {

    // http://www.6502.org/source/integers/hex2dec.htm
    // Converting byte and word to BCD code.


    BCD_LOOKUP_TABLE:
        .byte    $00, $00, $01, $00, $00, $02, $00, $00, $04, $00, $00, $08
        .byte    $00, $00, $16, $00, $00, $32, $00, $00, $64, $00, $01, $28
        .byte    $00, $02, $56, $00, $05, $12, $00, $10, $24, $00, $20, $48
        .byte    $00, $40, $96, $00, $81, $92, $01, $63, $84, $03, $27, $68

    //HTD_IN:     .byte $00, $00        // zpRegE0, zpRegE1
    //HTD_OUT:    .byte $00, $00, $00   // zpRegE2..4

    /* ----------------------------------------------------------------------------
        convert a single byte to two hex values (not characters).
        The value to be converted has to be in the accu and is left unchanged
        after return.
    
        Params In:
            Accu    : Value to be converted

        Params Out:
            zpRegE0 : Hexvalue lowbyte
            zpRegE1 : Hex value highbyte

        Since         : 31.07.2023
        Last modified : 31.07.2023
    ----------------------------------------------------------------------------
    */
    byte_to_hex: {
        pha                     // Save value to stack.
        and #%00001111
        sta zpRegE0             // store the lower nibble
        pla                     // Load the original value
        pha                     // and save it again
        lsr                     // shift the higher nibbel to the lower nibble
        lsr
        lsr
        lsr
        sta zpRegE1             // store the higher nibble
        pla                     // restore the accu
        rts
    }

    bcd_convert_word_: {
        sed
        phx
        pha
        lda #0
        sta zpRegE2
        sta zpRegE3
        sta zpRegE4
        ldx #$2d
    !loop:
        asl zpRegE0 
        rol zpRegE1
        bcc htd1
        lda zpRegE2
        clc 
        adc BCD_LOOKUP_TABLE+2,x
        sta zpRegE2
        lda zpRegE3
        adc BCD_LOOKUP_TABLE+1,x
        sta zpRegE3
        lda zpRegE4
        adc BCD_LOOKUP_TABLE,x
        sta zpRegE4
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


    // Compares to long values (32bit)
    // Value A: zpRegE0..zpRegE3
    // Value B: zpRegE4..zpRegE7
    // Sets Zero and Negative flag accordingly in the
    // same way CMP does.
    compare_long: {
        lda zpRegE3
        cmp zpRegE7
        bne exit 
        lda zpRegE2
        cmp zpRegE6
        bne exit 
        lda zpRegE1
        cmp zpRegE5
        bne exit 
        lda zpRegE0
        cmp zpRegE4
    exit:
        rts
    }
}

        