.cpu _65c02

.const BTN_STATE_NORMAL     = 0
.const BTN_STATE_SELECTED   = 1
.const BTN_STATE_PRESSED    = 2
.const BTN_STATE_DISABLED   = 3
.const BTN_ENABLED_FLAG     = %10000000

.macro ButtonRegister(index, xlo,xhi,y,w,label) {
    lda #xlo
    sta zpRegE0
    lda #xhi
    sta zpRegE1
    lda #y 
    sta zpRegE2                
    lda #w 
    sta zpRegE3
    lda #<label 
    sta zpRegE4
    lda #>label
    sta zpRegE5
    ldx #index
    jsr UI.Button.register
}


.macro SetButtonState_II(index, state) {
    lda #state 
    ldx #index
    jsr UI.Button.set_state
}

.macro DrawButtons() {
    jsr UI.Button.draw_all
} 

.macro SelectFirstButton() {
    jsr UI.Button.select_first
}

.macro SelectNextButton() {
    jsr UI.Button.select_next
}

.macro SelectPreviousButton() {
    jsr UI.Button.select_previous
}

.macro SetPadding_I(p) {
    lda #p
    sta UI.Button.PADDING
}

.namespace UI {
    .namespace Button {

        PADDING: .byte 0
        FGCOLOR: .byte 09, 42, 05, 06, 10, 10 // Foregroundcolor for all states
        BGCOLOR: .byte 43, 09, 32, 07, 43, 43 // Backgroundcolor for all states

        .const BTNCOUNT  = 10
        .const STATEMASK = %00000111

        BTNSTAT:    .fill BTNCOUNT, 0   // Bit 7: 1 = visible / 0 = invisible
                                        // Bit 0..2 = button state
                                        // Bit 3: Reserved for more states 
        BTNXLO:     .fill BTNCOUNT, 0
        BTNXHI:     .fill BTNCOUNT, 0
        BTNY:       .fill BTNCOUNT, 0
        BTN_WIDTH:  .fill BTNCOUNT, 0
        BTN_HEIGHT: .fill BTNCOUNT, 0
        TXTXPOSLO:  .fill BTNCOUNT, 0
        TXTXPOSHI:  .fill BTNCOUNT, 0
        TXTYPOS:    .fill BTNCOUNT, 0
        TXTLO:      .fill BTNCOUNT, 0   // Low Byte of Textadress in memory
        TXTHI:      .fill BTNCOUNT, 0   // High Byte of Textadress in memory
        TXTWIDTH:   .fill BTNCOUNT, 0   // Width of the text in pixel

        SELECTED_BUTTON_INDEX: .byte $f0 // Bit 7 = 1: No button selected

        register: {
            lda zpRegE0
            sta BTNXLO,x    // zpRegE0 = XPOS LO 
            lda zpRegE1  
            sta BTNXHI,x    // zpRegE1 = XPOS HI 
            lda zpRegE2
            sta BTNY,x      // zpRegE2 = YPOS
            lda zpRegE3
            sta BTN_WIDTH,x // zpRegE3 = WIDTH
            lda zpRegE4     
            sta TXTLO,x     // zpRegE4 = TXT LOW
            lda zpRegE5
            sta TXTHI,x     // zpRegE5 = TXT HI

            lda #(BTN_ENABLED_FLAG | BTN_STATE_NORMAL)
            sta BTNSTAT,x 

            // Calculated Values

            // Height = CHAR HEIGHT + 2 * PADDING
            lda #8
            clc 
            adc PADDING     // Add padding twice. For top and bottom.
            adc PADDING
            sta BTN_HEIGHT,x 

            // Text width in pixel
            ldy #0
            lda #0
            sta zpRegE6     // Save text width to zero page register
        !:
            lda (zpRegE4),y // Load character
            beq !+          // 0 means "end-of-string"
            clc
            lda zpRegE6     // restore sum
            adc #6          // Add Charwidth to it
            sta zpRegE6
            iny             // Check next character
            jmp !-          // Check next character
        !:
            lda zpRegE6     // load text width in pixel from zero page register
                            // TODO: Check, if text width > button width
                            //       In this case change button width to text width 
            sta TXTWIDTH,x  // and button info
            lda zpRegE3     // Button width
            sec
            sbc zpRegE6     // Subtract text width from button width
            lsr             // And divide by 2
            clc
            adc BTNXLO,x 
            sta TXTXPOSLO,x 
            lda #0
            rol             // If addition has overflow, store carry in hi byte
            sta TXTXPOSHI,x
            lda BTNY,x
            clc 
            adc PADDING
            sta TXTYPOS,x 
            rts  
        }

    /******************************************************************************

        Draw a Button.

        Draws a button with a label. The label is centered on the button.

        Params:
            x: Index of the button to draw

    ******************************************************************************/
        draw: {
                // Set the fill rect parameter, that are shared by every state
                lda BTNXLO,x 
                sta DIS00       // x lo
                lda BTNXHI,x      
                sta DIS01       // x hi
                lda BTNY,x      
                sta DIS02       // y
                lda BTN_WIDTH,x      
                sta DIS03       // width lo
                lda #0
                sta DIS04       // width hi
                lda BTN_HEIGHT,x 
                sta DIS05

                // Whate status are we in?
                lda BTNSTAT,x 
                bpl exit        // if bit 7 = 0, exit immediately         
                and #STATEMASK
                pha             // Save state
                tay 
                lda BGCOLOR,y 
                sta DIS06 
                jsr GFX.fill_rect_ 
                pla             // Restore state
                // Now draw the text
                lda TXTYPOS,x
                sta DIS02 
                lda FGCOLOR,y 
                sta DIS04 
                lda BGCOLOR,y 
                sta DIS05
                lda #1
                sta DIS06
                ldy #0
                lda TXTLO,x 
                sta zpRegE0
                lda TXTHI,x 
                sta zpRegE1
                lda TXTXPOSLO,x 
                sta zpRegE2
                lda TXTXPOSHI,x 
                sta zpRegE3
            !loop:
                lda (zpRegE0),y         // Testcharacter A
                beq exit
                sta DIS03
                lda zpRegE2             // xpos low
                sta DIS00
                lda zpRegE3             // xpos high
                sta DIS01            
                jsr GFX.draw_char_ 
                lda zpRegE2
                clc 
                adc #6 
                sta zpRegE2
                lda #0
                adc zpRegE3
                sta zpRegE3
                iny 
                jmp !loop-
            exit:
                rts
        }

        /*****************************************************
        // find the selected button index
        // The index is stored in the x register
        // If no button is selected, the carry flag is set
        //
        // @param:
        //  x: Button index
        //  a: State
        //
        // @clobbered_register:
        //  a
        //
        // @zero_page_register:
        //  zpRegE0
        //
        *****************************************************/
        set_state: {
                and #STATEMASK
                sta zpRegE0
                lda BTNSTAT,x 
                and #(~STATEMASK)
                ora zpRegE0
                sta BTNSTAT,x 
                rts
        }

        /*****************************************************
        // find the selected button index
        // The index is stored in the x register
        // If no button is selected, the carry flag is set
        //
        // @param:
        //  None
        //
        // @clobbered_register:
        //  x,y,a
        //
        // @zero_page_register:
        //  None
        //
        // @return:
        //  x: The index, if button is selected. Undefined else.
        //  c: 1 = no button selected; 0 = button selected
        *****************************************************/
        get_selected: {
                ldx SELECTED_BUTTON_INDEX
                bmi none_selected // Bit 7 = 1 => none is selected
                lda #(BTN_ENABLED_FLAG|BTN_STATE_SELECTED) 
                sta BTNSTAT,x 
                clc
                rts
            none_selected:
                sec 
                rts
        }

        /*****************************************************
        // Selects a button and automatically unselects the
        // currently selected (if any is selected)
        //
        // @param:
        //  x: The button index to be selected
        //
        // @clobbered_register:
        //  x,y,a
        //
        // @zero_page_register:
        //  None
        *****************************************************/
        set_selected: {
                ldy SELECTED_BUTTON_INDEX
                bmi !+  // None selected. Nothing to deselect
                // Set the currently selected button back to normal
                lda #(BTN_ENABLED_FLAG|BTN_STATE_NORMAL)
                sta BTNSTAT,y 
            !:  // Set the new selected button
                stx SELECTED_BUTTON_INDEX
                lda #(BTN_ENABLED_FLAG|BTN_STATE_SELECTED)
                sta BTNSTAT,x
                rts  
        }

        select_first: {
                ldx #0
            loop:
                lda BTNSTAT,x 
                bpl next
                // Found first selectable button
                jsr set_selected
                sec     // Carry = 1: We found one
                jmp exit
            next:
                inx 
                cpx BTNCOUNT
                bmi loop  
                clc     // Carry = 0: We found none
            exit:
                rts
        }

        select_previous: {
                ldx SELECTED_BUTTON_INDEX
                bpl search 
                // None is currently selected
                // So select the first selectable
                jsr select_first
                jmp exit 
            search:
                ldy #(BTNCOUNT-1)
            loop:
                dex 
                bpl !+
                ldx #(BTNCOUNT-1)
                cpx SELECTED_BUTTON_INDEX
                clc         // Carry = 0: We couldn't select one
                beq exit    // WE checked every index
            !:
                lda BTNSTAT,x 
                bmi loop 
                jsr set_selected
                sec         // Carry = 1: We selected one
                jmp exit
            !: 
                jmp loop
            exit:
                rts
        }


        select_next: {
                ldx SELECTED_BUTTON_INDEX
                bpl search 
                // None is currently selected
                // So select the first selectable
                jsr select_first
                jmp exit 
            search:
                ldy #(BTNCOUNT-1)
            loop:
                inx 
                cpx #BTNCOUNT
                bpl !+
                ldx #0
                cpx SELECTED_BUTTON_INDEX
                clc         // Carry = 0: We couldn't select one
                beq exit    // WE checked every index
            !:
                lda BTNSTAT,x 
                bmi loop 
                jsr set_selected
                sec         // Carry = 1: We selected one
                jmp exit
            !: 
                jmp loop
            exit:
                rts
        }

        /*****************************************************
        | Draw all buttons 
        *****************************************************/
        draw_all: {
                ldx #(BTNCOUNT-1)
            loop:
                lda BTNSTAT,x 
                bpl next            // If bit 7 is 0, skip this button
                jsr draw     // Draw this button 
            next:
                dex 
                bpl loop
                rts
        }

        /*****************************************************
        | Unregister button 
        *****************************************************/
        unregister: {
            lda BTNSTAT,x 
            and #$7f
            sta BTNSTAT,x 
            rts
        }
    }   
}