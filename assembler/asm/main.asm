.macro EnableCursorAutoAdjustment() {
    lda DISCR   // Set the auto adjust 
    ora #$0C    // and wrap flag
    sta DISCR                
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

                // Enable Frame IRQ
                lda #(CIA_SET_FLAGS | FRAME_INTERRUPT_FLAG)
                sta $dc0d

                // jsr debug_register_
                // jsr setup_timer
                SetCursorI(0,0)
                SetForgroundColorI(AMBER)
                PrintText(border_top)
                SetCursorI(0,2)
                SetForgroundColorI(AMBER)
                PrintText(border_bottom)

                SetCursorI(1,1)
                SetForgroundColorI(AMBER)
                PrintText(text_bar)

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
main_isr:   
            pha
            txa 
            pha 
            tya 
            pha
            
            ldy #7              // Y is the sprite index. We have 8 sprites in a row 
!move_right:
            lda SPRITE_XPOS,y   // Load current x position of the sprite   
            clc
operation:  adc #1              // Add the speed
check_left: cmp #10             // 10 is the minimum value for the left side
            bpl check_right     // There is still room
            pha 
            lda #$69            // ADC command
            sta operation
            pla 
            jmp keep_op
check_right:
            cmp #125
            bmi keep_op
            pha 
            lda #$e9            // SBC command
            sta operation
            pla 
keep_op:    sta SPRITE_XPOS,y   // save the new xpos 
            sta SPRITE_XPOS+8,y // Also for the second row
            dey

            bpl !move_right-
!exit:      lda $dc0d           // Acknowledge the IRQ            
            pla
            tay 
            pla 
            tax 
            pla
            rti