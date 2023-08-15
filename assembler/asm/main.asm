.macro EnableCursorAutoAdjustment() {
    lda DISCR   // Set the auto adjust 
    ora #$0C    // and wrap flag
    sta DISCR                
}

.macro EnableFrameIRQ() {
    lda #(CIA_SET_FLAGS | FRAME_INTERRUPT_FLAG)
    sta $dc0d
}

.macro DisableCursorAutoAdjustment() {
    lda DISCR   // Clear the auto adjust 
    and #$fd    // flag>
    sta DISCR                
}

.macro PrintText(addr) {
    lda #<addr
    sta zpRegE0
    lda #>addr
    sta zpRegE1
    jsr print_text_
}

// Colors
.const AMBER                    = 32

// CIA Contants
.const TIMER_A_INTERRUPT_FLAG   = $01
.const TIMER_B_INTERRUPT_FLAG   = $02
.const FRAME_INTERRUPT_FLAG     = $04
.const KBD_INTERRUPT_FLAG       = $08

.const CIA_SET_FLAGS            = $80


/* ============================================================================
                MAIN PROGRAM
   ----------------------------------------------------------------------------
*/
                * = $0800 "Main Program"
start:          ldx #$ff    // Set the stackpointer to
                txs         // highest possible position.

                // Sett isr vector for IRQ
                lda #<main_isr
                sta $fffe 
                lda #>main_isr
                sta $ffff

                // Setting isr vector for NMI 
                lda #<main_isr
                sta $fffa 
                lda #>main_isr
                sta $fffb
                
                EnableCursorAutoAdjustment()
                EnableFrameIRQ()                

                SetForgroundColorI(AMBER)
                SetCursorI(2,1)
                PrintText(welcome)

                
                // Spritetest
                jsr init_sprites_
!end:
                jmp !end-
            

setup_timer:
                // -----------------------------------------------------
                // Timer Test
                // Setting counter start value to 10 aka $000A
                // -----------------------------------------------------
                lda #$f0
                sta $dc05       // Set hi-byte of timer A latch
                lda #$00
                sta $dc04       // Set low-byte of timer A latch
                lda #$81        // Bit 0: Timer A / Bit 7: Set bits
                sta $dc0d       // Enable timer A interrupt
                lda #%00010001  // Bit 4: 1 = Load values from latch
                                // Bit 0: 1 = Start timer 
                                // Bit 3: 1 = Stop Timer after IRQ 
                sta $dc0e       // Load values and start timer
                // End Test. Timer should now be running and trigger 
                // an interrupt to enter the ISR           
                rts
border_top:     .byte $c8,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc
                .byte $cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$ba,$00

border_bottom:  .byte $c7,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc
                .byte $cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$cc,$bb,$00

text_bar:       .fill 37,$da 
                .byte 0

welcome:        .encoding "ascii"
                .text "NE/OS v0.1 - Kernel Size 974 bytes"
                .byte 0

                * = $0A00 "ISR"
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
main_isr:  { 
            pha
            txa 
            pha 
            tya 
            pha
            DRAW_HLINE_I(5,0,180,250,0,23)
            FILL_RECT_I(5,0,20,250,0,160,55)
            FILL_RECT_I(5,0,181,250,0,59,42)
            SetForgroundColorI(43)
            SetCursorI(2,23)
            lda $d0fd
            sta HTD_IN
            lda $d0fe
            sta HTD_IN+1
            jsr bcd_convert_word_
            lda HTD_OUT+2
            jsr print_hex_
            lda HTD_OUT+1
            jsr print_hex_
            lda HTD_OUT
            jsr print_hex_

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
            lda #$ff 
            sta operation+1
go_down:    // Check, if we have reached the "bottom". If so,
            // Reset the y position. Otherwise decrease the 
            // y position for each sprite.
            lda SPRITE_YPOS
            cmp #100
            bmi decrease         // if SPRITE ypos < 100 decrease ypos

            // -------------------------------------------------------
            // Bring all sprites back up again
            // -------------------------------------------------------
reset_ypos:
            // Row One / Sprite 0-7
            ldy #8
            lda #$20              // Start Y position
!loop:            
            sta SPRITE_YPOS,y 
            dey
            bpl !loop-

            // Row Two
            ldy #8
            lda #$30              // Start Y position
!loop:            
            sta SPRITE_YPOS+8,y 
            dey
            bpl !loop-
            
            // Row Three
            ldy #8
            lda #$40              // Start Y position
!loop:            
            sta SPRITE_YPOS+16,y 
            dey
            bpl !loop-
            jmp move    

decrease:
            ldy #24             // Calculate position fpr 24 sprites
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
operation:  adc #1               // Add the speed
            sta SPRITE_XPOS,y    // save the new xpos 
            sta SPRITE_XPOS+8,y  // Also for the second row
            sta SPRITE_XPOS+16,y // Also for the second row
            dey
            bpl !loop-
exit:
            lda $dc0d            // Acknowledge the IRQ            
            pla
            tay 
            pla 
            tax 
            pla
            rti
}