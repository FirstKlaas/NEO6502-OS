init_sprites_:  ldx #0
                lda #<SPACE_ALIEN_A
                sta SPRITE_DATA_LO, x
                lda #>SPACE_ALIEN_A
                sta SPRITE_DATA_HI, x
                lda #<SPRITE_DEFINITON_BLOCK
                sta DIS_00
                lda #>SPRITE_DEFINITON_BLOCK
                sta DIS_01
                lda #32
                sta DIS_02
                lda #CMD_SET_SDB
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

SPRITE_DEFINITON_BLOCK:
SPRITE_FLAGS:       .fill 32, 0
SPRITE_XPOS:        .fill 32, 0
SPRITE_YPOS:        .fill 32, 0
SPRITE_COLOR:       .fill 32, 0
SPRITE_WIDTH:       .byte 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
SPRITE_HEIGHT:      .byte  8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
SPRITE_DATA_LO:     .fill 32, 0
SPRITE_DATA_HI:     .fill 32, 0
