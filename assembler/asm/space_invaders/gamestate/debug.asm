.cpu _65c02
.namespace SpaceInvaders {


    COLOR_OFFSET:   .byte 0
    WORST_TIME:     .fill 4,0
    TS:             .fill 4,0

    .namespace Debug {

        .macro GetMillisAndSave() {
            // Get current millis
            // Result in DIS00...DIS03
            jsr GFX.get_millis
            // Store to T0
            lda DIS00
            sta TS 
            lda DIS01
            sta TS+1
            lda DIS02
            sta TS+2
            lda DIS03
            sta TS+3
        }

        .macro GetMillisDelta() {
            jsr GFX.get_millis
            sec 
            lda DIS00 
            sbc TS
            sta TS 
            lda DIS01 
            sbc TS+1
            sta TS+1
            lda DIS02
            sbc TS+2
            sta TS+2 
            lda DIS03  
            sbc TS+3 
            sta TS+3 
        }

        .macro PrintFrameTime() {
            jsr GFX.get_frame_time
            SetCursor_I(0,5)
            HexPrintM(DIS03)
            HexPrintM(DIS02)
            HexPrintM(DIS01)
            HexPrintM(DIS00)
        }

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
            GetMillisAndSave()
            // Get clock cycle and store it 
            // in time_stamp
            GetClockCycleAndSave()
            // Draw lines in different colors starting with offset
            ldy #239 // We 239 Lines
            ldx COLOR_OFFSET

        !loop:
            lda #0
            sta DIS00       // Xpos Low
            sta DIS01       // Xpos High
            tya 
            sta DIS02       // Ypos 
            lda #1
            sta DIS03       // Width low
            lda #64
            sta DIS04       // Width high
            txa 
            and #%00111111  // Only 64 colors (0..63)
            sta DIS05       // Color
            jsr GFX.draw_horizonal_line_
            inx             // Next line next color
            dey             // Next line ypos
            bne !loop-
            inc COLOR_OFFSET // Next frame we start with a higher index
            
            FillRect_I(0,0,0,50,0,240,STD_BACKGROUND_COLOR)
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
            bpl print_delta  // No bigger  value. Just print.
            lda zpRegFC
            sta WORST_TIME 
            lda zpRegFD
            sta WORST_TIME+1 
            lda zpRegFE
            sta WORST_TIME+2 
            lda zpRegFF
            sta WORST_TIME+3 
            
            
        print_delta:
            SetCursor_I(0,3)
            HexPrintM(WORST_TIME+3)
            HexPrintM(WORST_TIME+2)
            HexPrintM(WORST_TIME+1)
            HexPrintM(WORST_TIME)

            GetMillisDelta()
            SetCursor_I(0,4)
            HexPrintM(TS+3)
            HexPrintM(TS+2)
            HexPrintM(TS+1)
            HexPrintM(TS+0)

            PrintFrameTime()
            AcknowledgeIRQ()
            ply 
            plx 
            pla
            rti
        }
    }
}