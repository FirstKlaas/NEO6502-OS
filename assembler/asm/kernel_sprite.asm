.cpu _65c02
.const SPRITE_ENABLE_FLAG = $C0
.const BULLET_COUNT = 5

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

/* ===============================================================================
    Look for the next "invisible" bullet in the table. A invisible bullet is 
    marked with the bit 7 set to zero in the stat byte. The carry bit is used 
    to signal success or failure.

    If successful, the correct index is available in the x register and the carry
    bit is set. Not no free slot is availabe, the carry bit is cleared.
*/
find_next_invisible_bullet: {
    ldx #4
!loop:
    lda ALIEN_BULLETS_STAT,x 
    bmi !next+ // Visible. Next.
    // Make this bullet visible
    ora #$80
    sta ALIEN_BULLETS_STAT, x
    sec // Set carry flag (inicating we found a slot)
    rts // So we avoid a jump. But good practice?
!next:
    dex
    bpl !loop-
    // We didn't found one
    clc // Clear carry to indicate, we didn't found a free slot.
!end:    
    rts
}

/* ===============================================================================
    Update all "visible" bullets. A visible bullet is marked with the bit 7=1 in
    tha stat(us) byte.
*/
update_alien_bullets: {
    ldx #4
!loop:
    lda ALIEN_BULLETS_STAT,x // Get status info for bullet.
    bpl !next+               // If bit 7 = 0 => bullet is not visible
    
    // Draw bullet using a line
draw_bullet:
    lda ALIEN_BULLETS_X,x    // X-Pos low
    sta DIS00
    lda #0
    sta DIS01   // xpos high
    lda ALIEN_BULLETS_y,x 
    sta DIS02   // ypos 
    lda #4      // Length Low
    sta DIS03
    lda #0      // Length High
    sta DIS04   
    lda #23     // Color
    sta DIS05
    jsr draw_vertical_line_
    // Move the bullet. It adds the speed to the current y position
move_bullet:
    lda ALIEN_BULLETS_y,x 
    clc 
    //adc ALIEN_BULLETS_SPEED,x
    adc #2 
    sta ALIEN_BULLETS_y,x

    // Check ypos of bullet
check_bullet:
    // jmp !next+
    lda ALIEN_BULLETS_y,x
    cmp #190    // if ypos > 190 hide bullet 
    bmi !next+
    // hide bullet
hide_bullet:
    lda ALIEN_BULLETS_STAT,x 
    and #$7f
    sta ALIEN_BULLETS_STAT,x
!next:
    dex
    bpl !loop-
    rts
}

pure_draw_bullet: {

    ldx #4
!loop:
    lda ALIEN_BULLETS_X,x    // X-Pos low
    sta DIS00
    lda #0
    sta DIS01   // xpos high
    lda ALIEN_BULLETS_y,x 
    sta DIS02   // ypos 
    lda #4      // Length Low
    sta DIS03
    lda #0      // Length High
    sta DIS04   
    lda #23     // Color
    sta DIS05
    jsr draw_vertical_line_
    dex 
    bpl !loop-
    rts
}


ALIEN_BULLETS_STAT:     .fill BULLET_COUNT, $04  // Bit 0..3 length
                                                 // Bit 7: Visibility. 1 = Visible
                                                 // Bit 6: High Bit Xpos: 1 = Xpos > 255
ALIEN_BULLETS_X:        .byte $30, $40, $50, $60, $70  // xpos. If xpos > 255; stat bit 6 = 1
ALIEN_BULLETS_y:        .fill BULLET_COUNT, $20  // ypos of the top
ALIEN_BULLETS_SPEED:    .fill BULLET_COUNT, $02