.const SPRITE_ENABLE_FLAG = $C0

.macro SetSpriteAddress_IM(index, address) {
    ldx #index
    lda #<address
    sta SPRITE_DATA_LO, x
    lda #>address
    sta SPRITE_DATA_HI, x                
}

.macro EnableSprite_I(index) {
    ldx #index
    lda SPRITE_FLAGS, x
    ora SPRITE_ENABLE_FLAG
    sta SPRITE_FLAGS, x
}

.macro DisableSprite_I(index) {
    ldx #index
    lda SPRITE_FLAGS, x
    and ~SPRITE_ENABLE_FLAG
    sta SPRITE_FLAGS, x
}

.macro GetSpriteYPos_I(index) {
    ldx #index
    lda SPRITE_YPOS, x
}

.macro SetSpriteYPos_II(index, ypos) {
    ldx #index
    lda #ypos
    sta SPRITE_YPOS, x
}

.macro SetSpriteColor_IA(index) {
    ldx #index
    sta SPRITE_COLOR, x
}

.macro SetSpriteColor_II(index, color) {
    lda #color
    SetSpriteColor_IA(index)
}

init_sprites_:  SetSpriteAddress_IM(0, SPACE_ALIEN_A)
                SetSpriteAddress_IM(1, SPACE_ALIEN_A)
                SetSpriteAddress_IM(2, SPACE_ALIEN_A)
                SetSpriteAddress_IM(3, SPACE_ALIEN_A)
                SetSpriteAddress_IM(4, SPACE_ALIEN_A)
                SetSpriteAddress_IM(5, SPACE_ALIEN_A)
                SetSpriteAddress_IM(6, SPACE_ALIEN_A)
                SetSpriteAddress_IM(7, SPACE_ALIEN_A)
                SetSpriteAddress_IM(8, SPACE_ALIEN_A)
                SetSpriteAddress_IM(9, SPACE_ALIEN_A)
                SetSpriteAddress_IM(10, SPACE_ALIEN_A)
                SetSpriteAddress_IM(11, SPACE_ALIEN_A)
                
                EnableSprite_I(0)
                EnableSprite_I(1)
                EnableSprite_I(2)
                EnableSprite_I(3)
                EnableSprite_I(4)
                EnableSprite_I(5)
                EnableSprite_I(6)
                EnableSprite_I(7)
                EnableSprite_I(8)
                EnableSprite_I(9)
                EnableSprite_I(10)
                EnableSprite_I(11)

                // Init the sprite definition block
                lda #<SPRITE_DEFINITON_BLOCK
                sta DIS_00
                lda #>SPRITE_DEFINITON_BLOCK
                sta DIS_01
                lda #32                 // Set number of sprites
                sta DIS_02
                lda #CMD_SET_SDB        // Set command
                sta DISCMD              //                                          
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

SPACE_ALIEN_A2:     .byte %00000000, %00001100, %00110000, %00000000
                    .byte %00000000, %00001100, %00110000, %00000000
                    .byte %00000000, %00111111, %11111100, %00000000
                    .byte %00000000, %00111111, %11111100, %00000000
                    .byte %00000000, %11111111, %11111111, %00000000
                    .byte %00000000, %11111111, %11111111, %00000000
                    .byte %00000011, %11110011, %11001111, %11000000
                    .byte %00000011, %11110011, %11001111, %11000000
                    .byte %00000011, %00111111, %11111100, %11000000
                    .byte %00000011, %00111111, %11111100, %11000000
                    .byte %00000011, %00111111, %11111100, %11000000
                    .byte %00000011, %00111111, %11111100, %11000000
                    .byte %00000000, %00001100, %00110000, %00000000
                    .byte %00000000, %00001100, %00110000, %00000000
                    .byte %00000000, %00111100, %00111100, %00000000
                    .byte %00000000, %00111100, %00111100, %00000000



SPACE_ALIEN_B:      .byte %00000000, %00000000
                    .byte %00000100, %01000000
                    .byte %00000011, %10000000
                    .byte %00000111, %11000000
                    .byte %00000101, %01000000
                    .byte %00000111, %11000000
                    .byte %00001010, %10100000
                    .byte %00001010, %10100000

SPRITE_DEFINITON_BLOCK:
SPRITE_FLAGS:       .byte $80, $80, $80, $80, $80, $80, $80, $80  // Sprite 00-07
                    .byte $80, $80, $80, $00, $00, $00, $00, $00  // Sprite 08-15
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32
                    
SPRITE_XPOS:        .byte $10, $10, $10, $10, $10, $10, $10, $10  // Sprite 00-07
                    .byte $10, $10, $10, $00, $00, $00, $00, $00  // Sprite 08-15
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32
                    
SPRITE_YPOS:        .byte $10, $20, $30, $40, $50, $60, $70, $80  // Sprite 00-07
                    .byte $90, $a0, $00, $00, $00, $00, $00, $00  // Sprite 08-15
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32
                    
SPRITE_COLOR:       .byte $0a, $0b, $0c, $0d, $0e, $0f, $10, $11  // Sprite 00-07
                    .byte $12, $13, $00, $00, $00, $00, $00, $00  // Sprite 08-15
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32
                    
SPRITE_WIDTH:       .byte $10, $10, $10, $10, $10, $10, $10, $10  // Sprite 00-07
                    .byte $10, $10, $00, $00, $00, $00, $00, $00  // Sprite 08-15
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32
                    
SPRITE_HEIGHT:      .byte $08, $08, $08, $08, $08, $08, $08, $08  // Sprite 00-07
                    .byte $08, $08, $00, $00, $00, $00, $00, $00  // Sprite 08-15
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32

SPRITE_DATA_LO:     .fill 32, 0
SPRITE_DATA_HI:     .fill 32, 0
