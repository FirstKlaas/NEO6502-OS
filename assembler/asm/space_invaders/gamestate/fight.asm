.cpu _65c02
.namespace SpaceInvaders {
    .namespace Fight {



        init: {
            DisableAllIRQ()
            SetVectorNMI(run)
            EnableFrameIRQ()
            rts
        }

        /*  ====================================================================================
            MAIN ISR ROUTINE

            @brief          : This is the main interrupt routine, that is called, when the IRQB
                            line is pulled low. It stays low, until the interrupt source has
                            been cleared. 

                            Currently this is for testing purpose. In a later stage, we might
                            add vectors for each type of interrupt. Maybe.

                            The address of this routine is stored in the address vector
                            $fffe/$ffff

                            Programm counter and status register have been stored, while
                            registers have not. So this routine will save the regsiters
                            and restores them at the end, so they don't have any side affect
                            th the main code.


            @author         : Klaas Nebuhr
            @since          : 08.08.2023
            @last modified  : 08.08.2023 
            ------------------------------------------------------------------------------------
        */

        shot_delay: .byte $04

        run:  { 
            pha
            phx 
            phy 
            AcknowledgeIRQ()
            FILL_SCREEN_I(STD_BACKGROUND_COLOR)
            FILL_RECT_I(5,0,20,250,0,160,55)

            UpdateAlienAnimationFrame()
            jsr SpaceInvaders.animate_aliens
            DRAW_SPRITES()
            FILL_RECT_I(5,0,180,250,0,60,42)
            DRAW_RECT_I(5,0,20,250,0,160,23)
            SetForgroundColorI(43)

            // Printing the frame numer to the screen
            SetCursorI(2,26)
            PrintText(txt_frame)
            PrintFrameNumber(9,23)
            
            // Print Level
            SetCursorI(2,23)
            PrintText(txt_level)

            // Print Score
            SetCursorI(2,24)
            PrintText(txt_score)
            PrintScore(9,24)
            
            
            // Random Delay Triggered Shot
            dec shot_delay      // Shot delay countdown
            bne draw_bullets    // Still positive. No Shot
            jsr rand8           // New delay in frames ( 0..255)
            and #7
            adc #7              // Increase to at least 7 frames. 
            sta shot_delay      // Store new delay
            jsr find_next_invisible_bullet
            bcc draw_bullets    // We couln't find any free slot. So just draw.    

            // Found a new free bullet slot.
            // X contains the free bullet index
            // Now lets find a random alien monster
            // that shoots.
            // TODO: I take just the n-th alien and do not 
            //       consider, that aliens may be dead. So
            //       actually we are looking for the n-th
            //       alien, that's alive.
            jsr rand8  // Random value to accu
            and #15    // One of the first sixteen aliens
            tay        // Using y as alien index
            lda SPRITE_XPOS,y
            clc
            adc #8
            sta ALIEN_BULLETS_X,x
            lda SPRITE_YPOS,y
            clc
            adc #4
            sta ALIEN_BULLETS_Y,x
            
        draw_bullets:            
            jsr update_alien_bullets

            // Now let's check the position of the
            // Aliens and update it properly

        check_left:           
            lda SPRITE_XPOS     // Get the x position of the leftmost sprite
            cmp #10             // 10 is the minimum x position
            bpl check_right     // xpos - 10 >= 0 => check right border 
        left_underflow:                 
            lda #$01
            sta operation+1
            jmp go_down 
        
        check_right:
            lda SPRITE_XPOS+7   // get the xpos position of the rightmost sprite
            cmp #$ef            // Max xpos = 239
            bmi move            // if xpos - 239 < 0 => move
        
        right_overflow:
            lda #$ff            // By adding -1, we move left.
            sta operation+1     // Write the new speed to the code (self modified)    
        
        go_down:    
            // Check, if we have reached the "bottom". If so,
            // Reset the y position. Otherwise decrease the 
            // y position for each sprite.
            lda SPRITE_YPOS
            cmp #150
            bmi decrease         // if SPRITE ypos < 100 decrease ypos

            // -------------------------------------------------------
            // Bring all sprites back up again
            // -------------------------------------------------------
        
        reset_ypos:
            ResetAlienYPosition()
            jmp move
        
        decrease:
            ldy #23             // Calculate position fpr 24 sprites
        
        !loop:                  
            lda SPRITE_YPOS,y 
            clc
            adc #4
            sta SPRITE_YPOS,y 
            dey
            bpl !loop-

            // Moving sprites to the left or to the right
            //
        move:       
            ldy #7               // Y is the sprite index. We have 8 sprites in a row 
        !loop:
            lda SPRITE_XPOS,y    // Load current x position of the sprite   
            clc
        operation:  
            adc #1               // Add the speed
            sta SPRITE_XPOS,y    // save the new xpos 
            sta SPRITE_XPOS+8,y  // Also for the second row
            sta SPRITE_XPOS+16,y // Also for the second row
            dey
            bpl !loop-
        exit:
            lda $dc0d            // Acknowledge the IRQ            
            ply
            plx  
            pla
            rti
        }

        .macro ResetAlienYPosition() {
                // Row One / Sprite 0-7
                ldy #7
                lda #$20              // Start Y position
            !loop:            
                sta SPRITE_YPOS,y 
                dey
                bpl !loop-

                // Row Two
                ldy #7
                lda #$30              // Start Y position
            !loop:            
                sta SPRITE_YPOS+8,y 
                dey
                bpl !loop-
                
                // Row Three
                ldy #7
                lda #$40              // Start Y position
            !loop:            
                sta SPRITE_YPOS+16,y 
                dey
                bpl !loop-
        }
    }
}