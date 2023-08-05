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
                lda #$80
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
                lda #$80
!wait:
                bit DISCR               // Check, if the irg flag is cleared
                bmi !wait-              // No! Let's wait
                pla                     // Restore input parameter in accu
                rts                     // Return

