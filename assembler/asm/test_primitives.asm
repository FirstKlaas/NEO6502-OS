.namespace TestPrimitives {

    all: {
        jsr drawLine
        jsr drawHLine
        jsr drawVLine
        jsr fillRect
        jsr drawRect
        rts
    }

    drawLine: {
        lda #0     
        sta DIS00   // XPOS1 LO
        sta DIS01   // XPOS1 HI
        sta DIS02   // YPOS1
        sta DIS04   // XPOS2 HI
        lda #255    
        sta DIS03   // XPOS2 LO
        lda #240
        sta DIS05   // YPOS2
        lda #32
        sta DIS06   // COLOR
        jsr GFX.draw_line_
        rts
    }

    drawHLine: {
        lda #10
        sta DIS00   // XPOS LO
        lda #0  
        sta DIS01   // XPOS HI
        lda #25
        sta DIS02   // YPOS
        lda #100  
        sta DIS03   // LENGTH LO
        lda #0
        sta DIS04   // LENGTH HI
        lda #33
        sta DIS05   // COLOR
        jsr GFX.draw_horizonal_line_
        rts
    }

    drawVLine: {
        lda #10
        sta DIS00   // XPOS LO
        lda #0  
        sta DIS01   // XPOS HI
        lda #25
        sta DIS02   // YPOS
        lda #100  
        sta DIS03   // LENGTH LO
        lda #0
        sta DIS04   // LENGTH HI
        lda #34
        sta DIS05   // COLOR
        jsr GFX.draw_vertical_line_
        rts
    }

    drawRect: {
        lda #30
        sta DIS00   // XPOS LO
        lda #0
        sta DIS01   // XPOS HI
        lda #80
        sta DIS02   // YPOS
        lda #0
        sta DIS03   // WIDTH LO
        lda #100    
        sta DIS04   // WIDTH HI
        lda #100    
        sta DIS05   // HEIGHT
        lda #32
        sta DIS06   // COLOR
        jsr GFX.draw_rect_
        rts
    }

    fillRect: {
        lda #40
        sta DIS00   // XPOS LO
        lda #0
        sta DIS01   // XPOS HI
        lda #20
        sta DIS02   // YPOS
        lda #0
        sta DIS03   // WIDTH LO
        lda #100    
        sta DIS04   // WIDTH HI
        lda #100    
        sta DIS05   // HEIGHT
        lda #35
        sta DIS06   // COLOR
        jsr GFX.fill_rect_
        rts
    }

}