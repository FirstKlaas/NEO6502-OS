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
            // Get clock cycle and store it 
            // in time_stamp
            GetClockCycleAndSave()
            FILL_RECT_I(0,0,0,50,0,240,STD_BACKGROUND_COLOR)
            AcknowledgeIRQ()
            PrintFrameNumber(0,0)
            SetCursorI(0,3)
            PrintClockCycleDelta()
            ply 
            plx 
            pla
            rti
        }
    }
}