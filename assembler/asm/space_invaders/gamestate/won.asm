.cpu _65c02
.namespace SpaceInvaders {

    // This ist the state with the intro scene. From here you can start the screen#
    // or go back to the main menu
    .namespace Won {

        .const BG_COLOR = 4

        txt_you_won: 
            .encoding "ascii"
            .text "YOU WON"
            .byte 0

        init:
            rts

    }
}