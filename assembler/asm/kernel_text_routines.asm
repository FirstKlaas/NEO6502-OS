/*  ----------------------------------------------------------------------------
    Wait for the next character from the Keyboard and store it in the accu.
    Modifiers are stored in the X register
  
    Since         : 31.07.2023
    Last modified : 31.07.2023
    ----------------------------------------------------------------------------
*/
get_key_:       lda KBDCR               // Load the keyboard control register
                                        // to check the irq flag
                bpl get_key_            // lda affects the negative flag, 
                                        // which is a copy of the highest bit
                                        // (irq flag)
                and #KEY_MOD_MASK
                tax                     // Save modifiers
                lda KBD                 // Current key code to accu
                rts                     // Return

/* ----------------------------------------------------------------------------
    Prints a 0 terminated text string out.
    x pos is incremented automatically. 
    Currently noch checks are performed, if the text fits on a line.
    Starting address of the text is stored in zpRegE0 (lowbyte) and
    zpRegE1 (highbyte).

    The text is printed starting at the current cursor position.

    Params:
        zpRegE0 : Text address in memory (lowbyte)
        zpRegE1 : Text address in memory (highbyte)
  
    Saved register:
        A,X,Y

    Since         : 31.07.2023
    Last modified : 31.07.2023
   ----------------------------------------------------------------------------
*/
print_string:   pha                     // Save accu
                txa
                pha
                tya
                pha                     // Save y register
!irq:
                lda DISCR
                and #$80
                bne !irq-               // IRQ still active. Wait until cleared
                ldx DIS_00              // Get initial xpos
                ldy #0
!loop:
                lda (zpRegE0),y         // Read character from memory
                beq !end+               // On 0 we are done
                sta DIS                 // Write character
                lda DISCR
                ora #$80
                sta DISCR               // Set IRQ Flag
                inx                     // Next xpos
                stx DIS_01              // Update xpos for the next character
                iny                     // Next character index
                jmp !loop-
!end:
                pla                     // restore y
                tay
                pla
                tax
                pla                     // restore accu
                rts
                
/* ----------------------------------------------------------------------------
    Sets the x cursor position.
  
    Params In:
        Accu    : the new cursor column

    Params Out:
        None

    Since         : 02.08.2023
    Last modified : 02.08.2023
   ----------------------------------------------------------------------------
*/
set_cursor_x_:  pha                     // Save accu
                sta DIS_00              // Save the xpos to the 
                                        // display register
                lda #CMD_SET_CURSOR_X
                sta DISCMD              // Write the command. Will raise the irq                                         
                lda DISCR
                ora #$80
                sta DISCR               // Raise the IRQ flag
!wait:
                bit DISCR               // Check, if the irg flag is cleared
                bmi !wait-              // No! Let's wait
                pla                     // Restore input parameter in accu
                rts                     // Return

/* ----------------------------------------------------------------------------
    Sets the y cursor position.
  
    Params In:
        Accu    : the new cursor row

    Params Out:
        None

    Since         : 02.08.2023
    Last modified : 02.08.2023
   ----------------------------------------------------------------------------
*/
set_cursor_y_:  pha                     // Save accu
                sta DIS_00              // Save the xpos to the 
                                        // display register
                lda #CMD_SET_CURSOR_Y
                sta DISCMD
                lda DISCR
                ora #$80
                sta DISCR               // Raise the IRQ flag
!wait:
                bit DISCR               // Check, if the irg flag is cleared
                bmi !wait-              // No! Let's wait
                pla                     // Restore input parameter in accu
                rts                     // Return

set_fg_color_:  pha                     // Save accu
                sta DIS_00              // Save the xpos to the 
                                        // display register
                lda #CMD_SET_FG_COLOR
                sta DISCMD
                lda DISCR
                ora #$80
                sta DISCR               // Raise the IRQ flag
!wait:
                bit DISCR               // Check, if the irg flag is cleared
                bmi !wait-              // No! Let's wait
                pla                     // Restore input parameter in accu
                rts                     // Return

set_bg_color_:  pha                     // Save accu
                sta DIS_00              // Save the xpos to the 
                                        // display register
                lda #CMD_SET_BG_COLOR
                sta DISCMD
                lda DISCR
                ora #$80
                sta DISCR               // Raise the IRQ flag
!wait:
                bit DISCR               // Check, if the irg flag is cleared
                bmi !wait-              // No! Let's wait
                pla                     // Restore input parameter in accu
                rts                     // Return

get_xpos_:      lda #CMD_GET_CURSOR_X
                sta DISCMD
                lda DISCR
                ora #$80
                sta DISCR               // Raise the IRQ flag
!wait:
                bit DISCR               // Check, if the irg flag is cleared
                bmi !wait-              // No! Let's wait
                lda DIS_00
                rts                     // Return

get_ypos_:      lda #CMD_GET_CURSOR_Y
                sta DISCMD
                lda DISCR
                ora #$80
                sta DISCR               // Raise the IRQ flag
!wait:
                bit DISCR               // Check, if the irg flag is cleared
                bmi !wait-              // No! Let's wait
                lda DIS_00
                rts                     // Return

print_char_:    pha                     // Save accu
                sta DIS_00              // Save the char to the 
                                        // display register
                lda #CMD_WRITE_CHAR
                sta DISCMD
                lda DISCR
                ora #$80
                sta DISCR               // Raise the IRQ flag
!wait:
                bit DISCR               // Check, if the irg flag is cleared
                bmi !wait-              // No! Let's wait
                pla                     // Restore input parameter in accu
                rts                     // Return


/* ----------------------------------------------------------------------------
    Print a 0 terminated string at the current cursor position.
  
    Params In:
        zpRegE0   : Low byte of the string address
        zpRegE1   : High byte of the string address

    Params Out:
        None

    Since         : 06.08.2023
    Last modified : 06.08.2023
   ----------------------------------------------------------------------------
*/
print_text_:    ldy #0              // Index for the char within the string
!next:          lda (zpRegE0),y     // load character
                beq !end+
                jsr print_char_
                iny
                jmp !next-
!end:           rts

/* ----------------------------------------------------------------------------
    convert a single byte to two hex values (not characters).
    The value to be converted has to be in the accu and is left unchanged
    after return.
  
    Params In:
        Accu    : Value to be converted

    Params Out:
        zpRegE0 : Hexvalue lowbyte
        zpRegE1 : Hex value highbyte

    Since         : 31.07.2023
    Last modified : 31.07.2023
   ----------------------------------------------------------------------------
*/
print_hex_:     pha
                lda #<hex_chars
                sta zpRegE0
                lda #>hex_chars
                sta zpRegE1
                pla
                pha
                lsr
                lsr
                lsr
                lsr
                and #$0f
                tay
                lda (zpRegE0),y
                jsr print_char_
                pla
                pha
                and #$0f
                tay
                lda (zpRegE0),y
                jsr print_char_
                pla
                rts
