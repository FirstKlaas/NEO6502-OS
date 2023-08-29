.cpu _65c02
.namespace SpaceInvaders {


    COLOR_OFFSET: .byte 0
    WORST_TIME:   .fill 4,0

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
            // Draw lines in different colors starting with offset
            ldy #100 // We 100 Lines
            ldx COLOR_OFFSET

        !loop:
            lda #0
            sta DIS00       // Xpos Low
            sta DIS01       // Xpos High
            sta DIS04       // Width High
            tya 
            sta DIS02       // Ypos 
            lda #255        // Width low
            sta DIS03       // 255 pixel long line
            txa 
            and #%00111111  // Only 64 colors (0..63)
            sta DIS05       // Color
            inx             // Next line next color
            dey             // Next line ypos
            bne !loop-
            inc COLOR_OFFSET // Next frame we start with a higher index
            
            FILL_RECT_I(0,0,0,50,0,240,STD_BACKGROUND_COLOR)
            AcknowledgeIRQ()
            PrintFrameNumber(0,0)
            GetClockCyleDelta() // The delta is in zpRegFC...zpRegFF
            lda WORST_TIME
            sta zpRegE0
            lda WORST_TIME+1
            sta zpRegE1
            lda WORST_TIME+2
            sta zpRegE2
            lda WORST_TIME+3
            sta zpRegE3
            // Second long for comparison
            lda zpRegFC
            sta zpRegE4
            lda zpRegFD
            sta zpRegE5
            lda zpRegFE
            sta zpRegE6
            lda zpRegFF
            sta zpRegE5
            jsr Math.compare_long
            bpl print_delta 
            lda zpRegFC
            sta WORST_TIME 
            lda zpRegFD
            sta WORST_TIME+1 
            lda zpRegFE
            sta WORST_TIME+2 
            lda zpRegFF
            sta WORST_TIME+3 
            
            
        print_delta:
            SetCursorI(0,3)
            HexPrintM(WORST_TIME+3)
            HexPrintM(WORST_TIME+2)
            HexPrintM(WORST_TIME+1)
            HexPrintM(WORST_TIME)

            ply 
            plx 
            pla
            rti
        }
    }
}