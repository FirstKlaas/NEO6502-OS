// --------------------------------
// NEO6502 OS V0.0.1
// --------------------------------
// @author: <klaas.nebuhr@gmal.com>
// @version: 0.0.1


        * = $4000 "Kernal Routines"

start:  ldx #$ff    // Set the stackepointer to
        txs         // highest possible position.
