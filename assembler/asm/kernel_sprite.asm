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

SPRITE_DEFINITON_BLOCK:
SPRITE_FLAGS:       .byte $80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
SPRITE_XPOS:        .byte $c8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
SPRITE_YPOS:        .byte $64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
SPRITE_COLOR:       .byte $06, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
SPRITE_WIDTH:       .byte $10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
SPRITE_HEIGHT:      .byte $08, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
SPRITE_DATA_LO:     .fill 32, 0
SPRITE_DATA_HI:     .fill 32, 0
