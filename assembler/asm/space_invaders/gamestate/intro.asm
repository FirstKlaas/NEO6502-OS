.cpu _65c02
.namespace SpaceInvaders {


    // This ist the state with the intro scene. From here you can start the screen#
    // or go back to the main menu
    .namespace Intro {

        START_DELAY: .byte 00

        init: {
            DisableFrameIRQ()
            FillScreen_I(38)        // Darkish green
            SetForgroundColor_I(10) // Light gray
            SetCursor_I(10,2)
            SetVectorNMI(run)
            lda #100
            sta START_DELAY
            EnableFrameIRQ()
            rts
        }

        run: {
            pha 
            phx
            phy  
            FillScreen_I(38)  // Darkish green
            SetForgroundColor_I(32)
            SetCursor_I(10,6)
            PrintText(intro_message)
            SetCursor_I(10,9)
            PrintText(men_start_game)
            SetCursor_I(10,11)
            PrintText(men_sback_to_main)

            FillRect_I(10*FONT_CHAR_WIDTH ,0, 13*FONT_CHAR_HEIGHT, 10*FONT_CHAR_WIDTH, 0, FONT_CHAR_HEIGHT, 39)
            SetForgroundColor_I(11) // Light Gray
            SetCursor_I(10,13)
            HexPrintM(START_DELAY)
            PrintFrameNumber(14,13)

            dec START_DELAY
            bne !exit_isr+
            SwitchGameStateA(GAME_STATE_DEBUG)
            jmp !exit_isr+

        !exit_isr:
            AcknowledgeIRQ()
            ply 
            plx 
            pla 
            rti
        }

        intro_message:      .encoding "ascii"
                            .text "SPACE INVADER ON NEOS65C02"
                            .byte 0

        men_start_game:     .encoding "ascii"
                            .text "A  START NEW GAME"
                            .byte 0       

        men_sback_to_main:  .encoding "ascii"
                            .text "B  BACK TO MAIN MENU"
                            .byte 0       
    }
}