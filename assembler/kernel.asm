// --------------------------------
// NEO6502 OS V0.0.1
// --------------------------------
// @author: <klaas.nebuhr@gmal.com>
// @version: 0.0.1

        .const KBD   = $d010
        .const KBDCR = $d011

        * = $E000 "Kernal Routines"

start:  ldx #$ff    // Set the stackepointer to
        txs         // highest possible position.
loop:   
        txa
        sta KBD
        dex
        jmp loop
