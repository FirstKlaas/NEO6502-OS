.cpu _65c02

.namespace SpaceInvaders {

    .namespace LevelStart {

        CURRENT_VELOCITY: .word $0000
        TARGET_VELOCITY:  .word $0000

        /* 
        ##################################################################
        # Fly In animation for the aliens.
        # The aliens fly from left and from right. The odd rows from
        # left and the even rows from the right.
        ##################################################################
        */
        init: {
            DisableFrameIRQ()
            SetVectorNMI(animate)

            // First set the 32 alien sprites visible
            ldx #31
            lda #$80
        !loop:
            sta SPRITE_FLAGS,x 
            dex 
            bpl !loop- 
        
            // Now set the xpos for the odd sprites
            ldx #7
            lda #0
        !loop:
            sta SPRITE_YPOS,x 
            sta SPRITE_XPOS+16,x 
            dex 
            bpl !loop- 

            // Set the xpos for the even sprites
            ldx #7
            lda #255
        !loop: 
            sta SPRITE_YPOS+8,x 
            sta SPRITE_XPOS+24,x 
            dex 
            bpl !loop- 
        
            // Set the ypos for the first row
            ldx #7
            lda #$20
        !loop:
            sta SPRITE_YPOS,x 
            dex 
            bpl !loop-

            // Set the ypos for the second row
            ldx #7
            lda #$30
        !loop:
            sta SPRITE_YPOS+8,x 
            dex 
            bpl !loop-

            // Set the ypos for the thrid row
            ldx #7
            lda #$40
        !loop:
            sta SPRITE_YPOS+16,x 
            dex 
            bpl !loop-

            // Set the ypos for the fourth row
            ldx #7
            lda #$50
        !loop:
            sta SPRITE_YPOS+16,x 
            dex 
            bpl !loop-
            EnableFrameIRQ()
            rts
        }


        // This ist the animation routine for the fyin
        animate: {
            
        }
    }
}