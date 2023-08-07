.const SPRITE_ENABLE_FLAG = $40

init_sprites_:  lda DISCR
                ora #SPRITE_ENABLE_FLAG
                sta DISCR               // Enable sprites                    
                ldx #0                  // Set pixel data pointer for sprite 0
                lda #<SPACE_ALIEN_A
                sta SPRITE_DATA_LO, x
                lda #>SPACE_ALIEN_A
                sta SPRITE_DATA_HI, x
                lda #<SPRITE_DEFINITON_BLOCK // Set sprite definiton block data
.macro SetSpriteAddress(index, address) {
    ldx #index
    lda #<address
    sta SPRITE_DATA_LO, x
    lda #>address
    sta SPRITE_DATA_HI, x                
}

init_sprites_:  SetSpriteAddress(0, SPACE_ALIEN_A)
                SetSpriteAddress(1, SPACE_ALIEN_B)

                // Init the sprite definition block
                lda #<SPRITE_DEFINITON_BLOCK
                sta DIS_00
                lda #>SPRITE_DEFINITON_BLOCK
                sta DIS_01
                lda #32                 // Set number of sprites
                sta DIS_02
                lda #CMD_SET_SDB        // Set command
                sta DISCMD              // Write the command. Will raise the irq                                         
                lda DISCR
                ora #$80
                sta DISCR               // Raise the IRQ flag
!wait:
                bit DISCR               // Check, if the irg flag is cleared
                bmi !wait-              // No! Let's wait
                rts
                    
                    
SPACE_ALIEN_A:      .byte %00000010, %01000000
                    .byte %00000111, %11100000
                    .byte %00001111, %11110000
                    .byte %00011101, %10111000
                    .byte %00010111, %11101000
                    .byte %00010111, %11101000
                    .byte %00000010, %01000000
                    .byte %00000110, %01100000

SPACE_ALIEN_B:      .byte %00000000, %00000000
                    .byte %00000100, %01000000
                    .byte %00000011, %10000000
                    .byte %00000111, %11000000
                    .byte %00000101, %01000000
                    .byte %00000111, %11000000
                    .byte %00001010, %10100000
                    .byte %00001010, %10100000

SPRITE_DEFINITON_BLOCK:
SPRITE_FLAGS:       .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 00-07
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 08-15
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32
                    
SPRITE_XPOS:        .byte $10, $10, $00, $00, $00, $00, $00, $00  // Sprite 00-07
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 08-15
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32
                    
SPRITE_COLOR:       .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 00-07
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 08-15
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32
                    
SPRITE_WIDTH:       .byte $10, $10, $00, $00, $00, $00, $00, $00  // Sprite 00-07
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 08-15
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32
                    
SPRITE_HEIGHT:      .byte $08, $08, $00, $00, $00, $00, $00, $00  // Sprite 00-07
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 08-15
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32

SPRITE_DATA_LO:     .fill 32, 0
SPRITE_DATA_HI:     .fill 32, 0
