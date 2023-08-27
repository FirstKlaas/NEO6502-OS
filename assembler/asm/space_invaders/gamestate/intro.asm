.cpu _65c02
.namespace SpaceInvaders {


    // This ist the state with the intro scene. From here you can start the screen#
    // or go back to the main menu
    .namespace Intro {

        START_DELAY: .byte 00

        init: {
            DisableFrameIRQ()
            SetCursorI(10,2)
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
            AcknowledgeIRQ()
            SetCursorI(10,6)
            PrintText(intro_message)
            SetCursorI(10,9)
            PrintText(men_start_game)
            SetCursorI(10,11)
            PrintText(men_sback_to_main)

            SetCursorI(10,13)
            HexPrintM(START_DELAY)
            PrintFrameNumber(14,13)

            dec START_DELAY
            bne !exit_isr+
            SwitchGameStateA(GAME_STATE_DEBUG)
            jmp !exit_isr+

        !exit_isr:

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