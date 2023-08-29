.cpu _65c02

.namespace Color {

    /* ----------------------------------------------------------------------------
    converting a three byte color value (r,g,b) to a compressed two byte value
    (5-6-5).

    The input values are stored in the zeropage addresses

    @param: zpRegE0: Red Value 
    @param: zpRegE1: Green Value 
    @param: zpRegE2: Blue Value

    @return: 16bit color value. Highbyte in zpRegE0 und low byte in zpRegE1

    
    Since         : 31.07.2023
    Last modified : 31.07.2023
    ----------------------------------------------------------------------------
    */
    convert565: {
        lda zpRegE0             // red value
        asl                     // shift three to the left as we
        asl                     // need to move the lower 5 bits of red
        asl                     // to the bits 7-5
        sta zpRegE0             // Save as the High Byte of the compressed color
        lda zpRegE1             // load green. We need the bits 3-5 to be the 
        lsr                     // lower bits of the output highbyte
        lsr
        lsr
        and #%00000111          // Only the lower three bits.
        ora zpRegE0             // combine this with the compressed red
        sta zpRegE0             // Store the final high byte
        lda zpRegE1             // Load green again. We need the lower three bits
        asl                     // Shift everything 5 bits to the left and fill
        asl                     // it with zeros
        asl
        asl
        asl
        sta zpRegE1             // Store the green part in the lowbyte of the result
        lda zpRegE2             // Load blue
        and #%00011111          // Only need the 5 lower bits.
        ora zpRegE1             // Combine it with the green fraction
        sta zpRegE1             // Store the final low byte of the compressed color
        rts
    }


}