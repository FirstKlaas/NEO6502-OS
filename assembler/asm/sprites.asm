.cpu _65c02

.macro RegisterSDB_MI(data, count) {
    lda #<data
    sta DIS00
    lda #>data
    sta DIS01
    lda #count                 // Set number of sprites
    sta DIS02
    lda #CMD_SET_SDB        // Command "Set Sprite Definition Block"
    sta DISCMD              //                                          
    lda DISCR               // Load Display command register
    ora #$80                // Set the "Command Exceution" Flag
    sta DISCR               // Raise the IRQ flag
!wait:
    bit DISCR               // Check, if the irg flag is cleared
    bmi !wait-              // No! Let's wait
}

.namespace Sprites {

}