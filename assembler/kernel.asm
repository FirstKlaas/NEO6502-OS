// --------------------------------
// NEO6502 OS V0.0.1
// --------------------------------
// @author: <klaas.nebuhr@gmal.com>
// @version: 0.0.1

                .const KBD    = $d010    // Keyboard regster
                .const KBDCR  = $d011    // Keyboard control register
                .const DIS    = $d012    // Display register
                .const DISCR  = $d013    // Display control register

                .const DIS_00 = $d014    // Data exchange register 
                .const DIS_01 = $d015    // Data exchange register 
                .const DIS_02 = $d016    // Data exchange register 
                .const DIS_03 = $d017    // Data exchange register 
                .const DIS_04 = $d018    // Data exchange register 
                .const DIS_05 = $d019    // Data exchange register 
                .const DIS_06 = $d01A    // Data exchange register 
                .const DIS_07 = $d01B    // Data exchange register 

                .const KBD_IRQ_FLAG = $80
                .const DIS_IRQ_FLAG = $80

                .const KEY_MOD_MASK = %01110000  // Mask for the modifiers



/* ----------------------------------------------------------------------------
                ZERO PAGE 
                The kernel uses some space in the zero page for internal stuff.
                The addresses from E0 up FF (32 bytes) may not be used by other
                routines other than documented.

                By definition, the addresses F0-FF are volatile and can be used
                temporarily by any subroutine. (also by main programm).
                So these parameters should not be used for parameters or 
                Returnvalues.
   ----------------------------------------------------------------------------
*/
*=$E0 virtual 
.zp {
                zpRegE0: .byte 0
                zpRegE1: .byte 0
                zpRegE2: .byte 0
                zpRegE3: .byte 0
                zpRegE4: .byte 0
                zpRegE5: .byte 0
                zpRegE6: .byte 0
                zpRegE7: .byte 0
                zpRegE8: .byte 0
                zpRegE9: .byte 0
                zpRegEA: .byte 0
                zpRegEB: .byte 0
                zpRegEC: .byte 0
                zpRegED: .byte 0
                zpRegEE: .byte 0
                zpRegEF: .byte 0
                zpRegF0: .byte 0
                zpRegF1: .byte 0
                zpRegF2: .byte 0
                zpRegF3: .byte 0
                zpRegF4: .byte 0
                zpRegF5: .byte 0
                zpRegF6: .byte 0
                zpRegF7: .byte 0
                zpRegF8: .byte 0
                zpRegF9: .byte 0
                zpRegFA: .byte 0
                zpRegFB: .byte 0
                zpRegFC: .byte 0
                zpRegFD: .byte 0
                zpRegFE: .byte 0
                zpRegFF: .byte 0
}

/* ============================================================================
                MAIN PROGRAM
   ----------------------------------------------------------------------------
*/
                * = $0800 "Main Program"
start:          ldx #$ff    // Set the stackpointer to
                txs         // highest possible position.
loop:           txa
                sta $d014   // Store to DIS01
                dex
                jmp loop


/* ============================================================================
                KERNAL ROUTINES
   ----------------------------------------------------------------------------
*/
                * = $E000 "Kernel Routines Entry Points"

get_key:        jmp next_key

/* ----------------------------------------------------------------------------
    Display Routines.
    For most operations, we don't need a subroutine, as writing to the the 
    right register is all we need. For all one-byte operations writing to
    the register is enough. Setting the color takes two bytes. But the 16bit
    value is written to the display as we write the high byte. So just write
    first the low and then the hih byte and we are good to go.

    Same for reading. 
  
    Since         : 31.07.2023
    Last modified : 31.07.2023
    ----------------------------------------------------------------------------
*/


                * = $E100 "Kernel Routines"
/*  ----------------------------------------------------------------------------
    Wait for the next character from the Keyboard and store it in the accu.
    Modifiers are stored in the X register
  
    Since         : 31.07.2023
    Last modified : 31.07.2023
    ----------------------------------------------------------------------------
*/
next_key:       lda KBDCR               // Load the keyboard control register
                                        // to check the irq flag
                bpl next_key            // lda affects the negative flag, 
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
byte_to_hex:    pha                     // Save value to stack.
                and #%00001111
                sta zpRegE0             // store the lower nibble
                pla                     // Load the original value
                pha                     // and save it again
                lsr                     // shift the higher nibbel to the lower nibble
                lsr
                lsr
                lsr
                sta zpRegE1             // store the higher nibble
                pla                     // restore the accu
                rts



/* ----------------------------------------------------------------------------
   converting a three byte color value (r,g,b) to a compressed two byte value
   (5-6-5).

   The input values are stored in the zeropage addresses

   @param: zpRegE0: Red Value 
   @param: zpRegE1: Green Value 
   @param: zpRegE2: Blue Value

   @return: 16bit color value. Highbyte in zpRegE0 und low byte in zpRegE1

  
   Since         : 31.07.2023
   Last modified : 31.07.2023
   ----------------------------------------------------------------------------
*/
convert565:     lda zpRegE0             // red value
                asl                     // shift three to the left as we
                asl                     // need to move the lower 5 bits of red
                asl                     // to the bits 7-5
                sta zpRegE0             // Save as the High Byte of the compressed color
                lda zpRegE1             // load green. We need the bits 3-5 to be the 
                lsr                     // lower bits of the output highbyte
                lsr
                lsr
                and #%00000111          // Only the lower three bits.
                ora zpRegE0             // combine this with the compressed red
                sta zpRegE0             // Store the final high byte
                lda zpRegE1             // Load green again. We need the lower three bits
                asl                     // Shift everything 5 bits to the left and fill
                asl                     // it with zeros
                asl
                asl
                asl
                sta zpRegE1             // Store the green part in the lowbyte of the result
                lda zpRegE2             // Load blue
                and #%00011111          // Only need the 5 lower bits.
                ora zpRegE1             // Combine it with the green fraction
                sta zpRegE1             // Store the final low byte of the compressed color
                rts


/* ============================================================================
                KERNAL DATA
   ----------------------------------------------------------------------------
*/
                * = $f000 "Kernel Data"

hex_chars:      .text "0123456789ABCDEF"
msg_01:         .text "Welcome to FirstKlaas OS v0.1"
