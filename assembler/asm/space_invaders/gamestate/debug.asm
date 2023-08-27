.cpu _65c02
.namespace SpaceInvaders {

    .namespace Debug {

        init: {
            DisableAllIRQ()
            SetVectorNMI(run_debug)
            EnableFrameIRQ()
            rts
        }

        run_debug: {
            pha 
            phx 
            phy 
            FILL_RECT_I(0,0,0,100,0,10,STD_BACKGROUND_COLOR)
            AcknowledgeIRQ()
            PrintFrameNumber(0,0)
            EnableFrameIRQ()

            ply 
            plx 
            pla
            rti
        }
    }
}