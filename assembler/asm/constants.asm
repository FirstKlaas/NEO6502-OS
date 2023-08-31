.cpu _65c02

// Colors
.const AMBER                    = 32

// CIA Contants
.const TIMER_A_INTERRUPT_FLAG   = $01
.const TIMER_B_INTERRUPT_FLAG   = $02
.const FRAME_INTERRUPT_FLAG     = $04
.const KBD_INTERRUPT_FLAG       = $08

.const CIA_SET_FLAGS            = $80

.const STD_BACKGROUND_COLOR     =  41
.const STD_FOREGROUND_COLOR     =  31
.const TITLE_FG_COLOR           =  46
.const FONT_CHAR_WIDTH          =   6
.const FONT_CHAR_HEIGHT         =   8
.const SCREEN_WIDTH             = 320
.const SCREEN_HEIGHT            = 240
.const LINECHARS                =  52
.const LINES                    = SCREEN_HEIGHT / (FONT_CHAR_HEIGHT + 1)


.const KBD    = $d010       // Keyboard regster
.const KBDCR  = $d011       // Keyboard control register
.const DIS    = $d012       // Display register
.const DISCR  = $d013       // Display control register
                            // Bit 7 $80: Execute Command
                            // Bit 6 $40: undefined
                            // Bit 5 $20: undefined
                            // Bit 4 $10: Autoclean screen
                            // Bit 3 $08: Text and colorbuf
                            // Bit 2 $04: Autoadjust Cursor
                            // Bit 1 $02: Show Cursor
                            // Bit 0 $01: Sprite activation 

.const DISCMD = $d014       // Display command register
.const DIS00 = $d015        // Data exchange register 
.const DIS01 = $d016        // Data exchange register 
.const DIS02 = $d017        // Data exchange register 
.const DIS03 = $d018        // Data exchange register 
.const DIS04 = $d019        // Data exchange register 
.const DIS05 = $d01A        // Data exchange register 
.const DIS06 = $d01B        // Data exchange register 
.const DIS07 = $d01C        // Data exchange register
.const DIS08 = $d01D        // Data exchange register
.const DIS09 = $d01E        // Data exchange register

.const DISFL = $d0fd        // Frame number lo
.const DISFH = $d0fe        // Frame number hi
.const DEBUG = $d0ff        // Debug register

// CIA register and constants
.const REG_CIA_ICR  = $dc0d
.const CIA_IRQ_MASK = %01111111
.const KBD_IRQ_FLAG = $80
.const DIS_IRQ_FLAG = $80

.const KEY_MOD_MASK = %01110000  // Mask for the modifiers

.const CMD_GET_CURSOR_X     = $01
.const CMD_GET_CURSOR_Y     = $02
.const CMD_SET_CURSOR_X     = $03
.const CMD_SET_CURSOR_Y     = $04
.const CMD_GET_FG_COLOR     = $05
.const CMD_GET_BG_COLOR     = $06
.const CMD_SET_FG_COLOR     = $07
.const CMD_SET_BG_COLOR     = $08
.const CMD_GET_X_OFFSET     = $09
.const CMD_GET_Y_OFFSET     = $0a
.const CMD_SET_X_OFFSET     = $0b
.const CMD_SET_Y_OFFSET     = $0c
.const CMD_WRITE_CHAR       = $0d
.const CMD_FILL_SCREEN      = $0e
.const CMD_CLEAR_SCREEN     = $0f
.const CMD_SCROLL_UP        = $10
.const CMD_SCROLL_DOWN      = $11
.const CMD_SHOW_CURSOR      = $12
.const CMD_HIDE_CURSOR      = $13
// Graphics Commands
.const CMD_DRAW_LINE        = $14
.const CMD_DRAW_HLINE       = $15
.const CMD_DRAW_VLINE       = $16
.const CMD_SET_SDB          = $17
.const CMD_GET_BGCOLOR      = $18
.const CMD_SET_BGCOLOR      = $19
.const CMD_DRAW_RECT        = $1A
.const CMD_FILL_RECT        = $1B
.const CMD_DRAW_CIRCLE      = $1C
.const CMD_FILL_CIRCLE      = $1D
.const CMD_DrawSprites     = $1E

.const CMD_DRAW_BITMAP      = $1F
.const CMD_DRAW_PIXEL       = $20
.const CMD_DRAW_TRIANGLE    = $21
.const CMD_FILL_TRIANGLE    = $22
.const CMD_DRAW_ROUND_RECT  = $23
.const CMD_FILL_ROUND_RECT  = $24
.const CMD_DRAW_CHAR        = $25

.const CMD_GET_CLOCK_CYCLE  = $30
.const CMD_GET_MILLIS       = $31
.const CMD_GET_FRAME_TIME   = $32
