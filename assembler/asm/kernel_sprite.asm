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

init_sprites_:  .for (var i=0; i<8; i++) {
                    SetSpriteAddress_IM(i,    SPACE_ALIEN_A)
                    SetSpriteAddress_IM(i+8,  SPACE_ALIEN_B)
                    SetSpriteAddress_IM(i+16, SPACE_ALIEN_C)
                }
                
                .for (var i=0;i<24;i++) { 
                    EnableSprite_I(i)
                }

                // Init the sprite definition block
                lda #<SPRITE_DEFINITON_BLOCK
                sta DIS00
                lda #>SPRITE_DEFINITON_BLOCK
                sta DIS01
                lda #32                 // Set number of sprites
                sta DIS02
                lda #CMD_SET_SDB        // Command "Set Sprite Definition Block"
                sta DISCMD              //                                          
                lda DISCR               // Load Display command register
                ora #$80                // Set the "Command Exceution" Flag
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

SPACE_ALIEN_C:      .byte %00000000, %00000000
                    .byte %00000100, %01000000
                    .byte %00001111, %11100000
                    .byte %00011001, %00110000
                    .byte %00011111, %11110000
                    .byte %00011111, %11110000
                    .byte %00010101, %01010000
                    .byte %00001010, %10100000


SPRITE_DEFINITON_BLOCK:
SPRITE_FLAGS:       .byte $80, $80, $80, $80, $80, $80, $80, $80  // Sprite 00-07
                    .byte $80, $80, $80, $80, $80, $80, $80, $80  // Sprite 08-15
                    .byte $80, $80, $80, $80, $80, $80, $80, $80  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32
                    
SPRITE_XPOS:        .byte $10, $20, $30, $40, $50, $60, $70, $80  // Sprite 00-07
                    .byte $10, $20, $30, $40, $50, $60, $70, $80  // Sprite 08-15
                    .byte $10, $20, $30, $40, $50, $60, $70, $80  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32
                    
SPRITE_YPOS:        .byte $20, $20, $20, $20, $20, $20, $20, $20  // Sprite 00-07
                    .byte $30, $30, $30, $30, $30, $30, $30, $30  // Sprite 08-15
                    .byte $40, $40, $40, $40, $40, $40, $40, $40  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32
                    
SPRITE_COLOR:       .byte $1f, $1f, $1f, $1f, $1f, $1f, $1f, $1f  // Sprite 00-07
                    .byte $23, $23, $23, $23, $23, $23, $23, $23  // Sprite 08-15
                    .byte $2c, $2c, $2c, $2c, $2c, $2c, $2c, $2c  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32
                    
SPRITE_WIDTH:       .byte $10, $10, $10, $10, $10, $10, $10, $10  // Sprite 00-07
                    .byte $10, $10, $10, $10, $10, $10, $10, $10  // Sprite 08-15
                    .byte $10, $10, $10, $10, $10, $10, $10, $10  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32
                    
SPRITE_HEIGHT:      .byte $08, $08, $08, $08, $08, $08, $08, $08  // Sprite 00-07
                    .byte $08, $08, $08, $08, $08, $08, $08, $08  // Sprite 08-15
                    .byte $08, $08, $08, $08, $08, $08, $08, $08  // Sprite 16-23
                    .byte $00, $00, $00, $00, $00, $00, $00, $00  // Sprite 24-32

SPRITE_DATA_LO:     .fill 32, 0
SPRITE_DATA_HI:     .fill 32, 0

// ===============================================================================
find_next_free_bullet: {
    ldx ALIEN_BULLETS_COUNT
    sec // Set carry flag (inicating we found a slot)
!loop:
    lda ALIEN_BULLETS_STAT,x 
    bpl !end+ // We found a free slot. The index is in x register
    dex
    bpl !loop-
    // We didn't found one
    clc // Clear carry to indicate, we didn't found a free slot.
!end:    
    rts
}

// ===============================================================================
draw_alien_bullets: {
    ldx ALIEN_BULLETS_COUNT
!loop:
    lda ALIEN_BULLETS_STAT,x // Get status info for bullet.
    bpl !next+ // If bit 7 = 0 => bullet is not visible
// Draw bullet
draw_bullet:

// Move bullet
move_bullet:
    lda ALIEN_BULLETS_y,x 
    clc 
    adc ALIEN_BULLETS_SPEED,x 
    sta ALIEN_BULLETS_y,x 

// Check ypos of bullet
check_bullet:
    cmp #100    // if ypos > 100 free bullet 
    bmi !next+
// Free bullet
free_bullet:
    lda ALIEN_BULLETS_STAT,x 
    and #%01111111
    sta ALIEN_BULLETS_STAT,x
!next:
    dex
    bpl !loop-
    rts
}


ALIEN_BULLETS_COUNT: .byte $05 
ALIEN_BULLETS_STAT:  .fill $05, $04 // Bit 0..3 length
ALIEN_BULLETS_X:     .fill $05, $00 // xpos. If xpos > 255; stat bit 6 = 1
ALIEN_BULLETS_y:     .fill $05, $00 // ypos of the top
ALIEN_BULLETS_SPEED: .fill $05, $02