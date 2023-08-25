.cpu _65c02

.namespace SpaceInvaders {
    // Zero Page Variables
    .const SPRITE_ENABLE_FLAG       = $C0
    .const BULLET_COUNT             =   5
    .const MAX_BULLET_COUNT         =  20
    .const BULLET_MAX_HEIGHT        = 170
    .const BULLET_MIN_HEIGHT        =  20
    .const BULLET_COLOR             =  23
    .const BULLET_LENGTH            =   4
    .const BULLET_ENABLE_FLAG       = $80

    // GAME_STATES
    .const GAME_STATE_INTRO         =   1
    .const GAME_STATE_LEVEL_START   =   2
    .const GAME_STATE_FIGHT         =   3
    .const GAME_STATE_WIN           =   4
    .const GAME_STATE_LOST          =   5

    .const ALIEN_ANIM_SPEED         = %00010000

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

    .macro UpdateAlienAnimationFrame() {
        lda ALIEN_ANIM_FRAME_LO
        clc
        adc #%01000000
        sta ALIEN_ANIM_FRAME_LO
        lda ALIEN_ANIM_FRAME_HI
        adc #00
        and #3
        sta ALIEN_ANIM_FRAME_HI
    }

    .macro PrintScore(sx,sy) {
        SetCursorI(sx,sy)
        lda SCORE_LO       
        sta HTD_IN
        lda SCORE_HI       
        sta HTD_IN+1
        jsr bcd_convert_word_
        lda HTD_OUT+2
        HexPrintA()
        lda HTD_OUT+1
        HexPrintA()
        lda HTD_OUT
        HexPrintA()
    }

    *=$02 "Game Variables" virtual
    .zp {
        SCORE_LO:               .byte $00
        SCORE_HI:               .byte $00
        GAME_STATE:             .byte $00
        ALIEN_ANIM_FRAME_LO:    .byte $00 // Subpixel Animation Frame
        ALIEN_ANIM_FRAME_HI:    .byte $00 // Animation Frame
        CURRENT_GAME_STATE:     .byte $00
        CURRENT_LEVEL:          .byte $00
        ALIENS_ALIVE:           .byte $18
    } 

        * = $1000 "Space Invaders"

        .import source "game_loop_isr.asm"


    dummy_isr: {
        pha
        phx
        phy
        // Printing the frame numer to the screen
        FILL_RECT_I(0,0,22*FONT_CHAR_HEIGHT,0,100,3*FONT_CHAR_HEIGHT,4)
        PrintFrameNumber(9,23)
        SetCursorI(2,26)
        PrintText(txt_frame)
        AcknowledgeIRQ()
        ply 
        plx 
        pla 
        rti
    }


    /* ########################################################################
       # Initialisation of the Space Invader Game
       #
       # 1) Disable interrupts
       # 2) Install new ISR routine for the game
       # 3) Draw Base Screen
       # 4) Initialize Sprite
       # 5) Initialize Sprite Definition Block
       # 5) Enable interrupts
       ########################################################################
    */
    run: {

        // Disable all interrupts        
        DisableAllIRQ()
        
        // Fill Screen
        FILL_SCREEN_I(STD_BACKGROUND_COLOR)

        sei
        // Set isr vector for IRQ
        SetVectorIRQ(main_isr)
        //SetVectorIRQ(dummy_isr)

        // Setting isr vector for NMI 
        SetVectorNMI(main_isr)
        //SetVectorNMI(dummy_isr)
        cli

        jsr init_alien_animation
        jsr initialize_sprite_definition_block

        EnableFrameIRQ()
        WriteDebugNumberI(255)
!loop:  jmp * // Loop endless instead of getting back.
        WriteDebugNumberI(254)
        
    }

    animate_aliens: {
        ldx ALIEN_ANIM_FRAME_HI
        // Alien A
        lda ALIEN_A_SPRITE_ANIMATION_LO,x
        .for (var i=0; i<8; i++) {
            sta SPRITE_DATA_LO+i    
        }
        lda ALIEN_A_SPRITE_ANIMATION_HI,x
        .for (var i=0; i<8; i++) {
            sta SPRITE_DATA_HI+i    
        }
        // Alien B
        lda ALIEN_B_SPRITE_ANIMATION_LO,x
        .for (var i=8; i<16; i++) {
            sta SPRITE_DATA_LO+i    
        }
        lda ALIEN_B_SPRITE_ANIMATION_HI,x
        .for (var i=8; i<16; i++) {
            sta SPRITE_DATA_HI+i    
        }
        rts
    }          

    .import source "spin_sprites.asm"

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

    ALIEN_A_SPRITE_ANIMATION_LO:    .fill 4, 0
    ALIEN_A_SPRITE_ANIMATION_HI:    .fill 4, 0
    ALIEN_B_SPRITE_ANIMATION_LO:    .fill 4, 0
    ALIEN_B_SPRITE_ANIMATION_HI:    .fill 4, 0

    initialize_sprite_definition_block: {
        // Initialize Sprites
        .for (var i=0; i<8; i++) {
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
    }

    // -----------------------------------------
    // Init Alien Animation
    // The Sprite Adress for each frame sprite 
    // is stored in a table
    // -----------------------------------------
    init_alien_animation: {
        // Alien A
        // Frame 0 and 2
        lda #<SPACE_ALIEN_A
        sta ALIEN_A_SPRITE_ANIMATION_LO
        sta ALIEN_A_SPRITE_ANIMATION_LO+2
        lda #>SPACE_ALIEN_A
        sta ALIEN_A_SPRITE_ANIMATION_HI
        sta ALIEN_A_SPRITE_ANIMATION_HI+2
        // Frame 1
        lda #<SPACE_ALIEN_A1
        sta ALIEN_A_SPRITE_ANIMATION_LO+1
        lda #>SPACE_ALIEN_A1
        sta ALIEN_A_SPRITE_ANIMATION_HI+1
        // Frame 3
        lda #<SPACE_ALIEN_A2
        sta ALIEN_A_SPRITE_ANIMATION_LO+3
        lda #>SPACE_ALIEN_A2
        sta ALIEN_A_SPRITE_ANIMATION_HI+3

        // Alien B
        lda #<SPACE_ALIEN_B
        sta ALIEN_B_SPRITE_ANIMATION_LO
        sta ALIEN_B_SPRITE_ANIMATION_LO+2
        lda #>SPACE_ALIEN_B
        sta ALIEN_B_SPRITE_ANIMATION_HI
        sta ALIEN_B_SPRITE_ANIMATION_HI+2
        // Frame 1
        lda #<SPACE_ALIEN_B1
        sta ALIEN_B_SPRITE_ANIMATION_LO+1
        lda #>SPACE_ALIEN_B1
        sta ALIEN_B_SPRITE_ANIMATION_HI+1
        // Frame 1
        lda #<SPACE_ALIEN_B2
        sta ALIEN_B_SPRITE_ANIMATION_LO+3
        lda #>SPACE_ALIEN_B2
        sta ALIEN_B_SPRITE_ANIMATION_HI+3
        rts
    }

    /* ===============================================================================
        Look for the next "invisible" bullet in the table. A invisible bullet is 
        marked with the bit 7 set to zero in the stat byte. The carry bit is used 
        to signal success or failure.

        If successful, the correct index is available in the x register and the carry
        bit is set. Not no free slot is availabe, the carry bit is cleared.
    */
    find_next_invisible_bullet: {
        ldx #(BULLET_COUNT-1)
    !loop:
        lda ALIEN_BULLETS_STAT,x 
        bmi !next+ // Visible. Next.
        // Make this bullet visible
        ora #BULLET_ENABLE_FLAG
        sta ALIEN_BULLETS_STAT,x
        sec // Set carry flag (inicating we found a slot)
        jmp !end+
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
        jsr move_bullets
        jsr check_bullets
        jsr draw_bullets
        rts
    }

    /* =======================================================================
    Move every (visible) bullet down by the defined speed
    -----------------------------------------------------------------------
    */
    move_bullets: {
        ldx #(BULLET_COUNT)
    !loop:
        lda ALIEN_BULLETS_STAT,x
        bpl !next+
        lda ALIEN_BULLETS_Y,x 
        clc 
        adc ALIEN_BULLETS_SPEED,x
        sta ALIEN_BULLETS_Y,x
    !next:
        dex
        bpl !loop- 
        rts
    }

    /* =======================================================================
    Check the visible bullets, whether they are in the visible range or 
    not. If not, the bullet's state is set to "hidden" 
    -----------------------------------------------------------------------
    */
    check_bullets: {
        ldx #(BULLET_COUNT-1)
    !loop:
        lda ALIEN_BULLETS_STAT,x
        bpl !next+
        lda ALIEN_BULLETS_Y,x
        cmp #BULLET_MAX_HEIGHT    // if ypos > BULLET_MAX_HEIGHT hide bullet 
        bmi !next+
        // hide bullet
    hide_bullet:
        lda ALIEN_BULLETS_STAT,x 
        and #(~BULLET_ENABLE_FLAG)
        sta ALIEN_BULLETS_STAT,x
    !next:
        dex
        bpl !loop-
        rts
    }

    /* =======================================================================
    Draw every (visible) bullet to the screen
    -----------------------------------------------------------------------
    */
    draw_bullets: {

        lda #0
        sta DIS01                   // xpos high
        lda #BULLET_LENGTH          // Length Low
        sta DIS03
        lda #0                      // Length High
        sta DIS04   
        lda #BULLET_COLOR           // Color
        sta DIS05
        ldx #(BULLET_COUNT-1)
    !loop:
        lda ALIEN_BULLETS_STAT,x 
        bpl !next+
        lda ALIEN_BULLETS_X,x       // X-Pos low
        sta DIS00
        lda ALIEN_BULLETS_Y,x 
        sta DIS02                   // ypos 
        jsr GFX.draw_vertical_line_
    !next:
        dex 
        bpl !loop-
        rts
    }


    ALIEN_BULLETS_STAT:     .fill BULLET_COUNT, $04  // Bit 0..3 length
                                                    // Bit 7: Visibility. 1 = Visible
                                                    // Bit 6: High Bit Xpos: 1 = Xpos > 255
    ALIEN_BULLETS_X:        .fill BULLET_COUNT, $00  // xpos. If xpos > 255; stat bit 6 = 1
    ALIEN_BULLETS_Y:        .fill BULLET_COUNT, $20  // ypos of the top
    ALIEN_BULLETS_SPEED:    .fill BULLET_COUNT, $02
}