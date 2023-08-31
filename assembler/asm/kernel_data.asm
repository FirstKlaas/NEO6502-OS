/* ============================================================================
                KERNAL DATA
   ----------------------------------------------------------------------------
*/
                * = $f000 "Kernel Data"

hex_chars:      .text "0123456789ABCDEF"
msg_01:         .encoding "ascii"
                .text "NE/OS v0.2 by FirstKlaas 2023"
                .byte 0

welcome:        .encoding "ascii"
                .text "NE/OS v0.1 - FirstKlaas Experience"
                .byte 0

txt_frame:      .encoding "ascii"
                .text "FRAME:"
                .byte 0

txt_level:      .encoding "ascii"
                .text "LEVEL"
                .byte 0

txt_score:      .encoding "ascii"
                .text "SCORE"
                .byte 0

txt_menue_1:    .encoding "ascii"
                .text "1  Load program"
                .byte 0

txt_menue_2:    .encoding "ascii"
                .text "2  Play Space Invaders"
                .byte 0


