# NEOS65 - NEO6502 Operating System

The basic idea is to have a simple OS that will
start after pluggin in the board. There will be no support for BASIC. Only programms written in assembler are supported. To make life a little bit easier, kernel routines are
provided. We have text and graphics routines.

Also part of the OS will be an option to "load and start" programs. Currently my idea would be tu use an sd card. I  think it would be a cool retro feature. Alternatively we could use an USB drive. But that's something for the later stage.

The kernel and os routines are written assember language using [KickAssember](http://theweb.dk/KickAssembler/Main.html#frontpage) for assembling. KickAssembler has a neat feature to assemble into multiple prg files. Each for every segment. This avoid large chunks of zeros and results in smaller arrays. To convert the prg files, I wrote a little python script, whcih is located under the "TOOLS" folder.

# Memory Layout
The main routine for the operating system starts at `$0800`. 

The first memory page (Addresses from `$0000-$00ff`) are called the zero page.

The second page is the stack.

Address `$d000-$d0ff` should be used carefully as this is the space that is also used by registers. In other words. Avoid these adresses for storing code or data. 

## Known registers
### Display registers
| Address | Name | Description |
| --- | --- | --- |
| `$d010` | `KBD` | The beyboard register, where you will find the keycode of the last pressed key. |
| `$d011` | `KBDCR` | The keyboard control register. |
| `$d011` | `KBDCR` | The keyboard control register. |
| `$d012` | `DIS` | Display register (currently not used) |
| `$d013` | `DISCR` | Display control register |
| `$d014` | `DISCMD` | This register contains the display command that you want to perform.  For details, see the section commands |
| `$d015` | `DIS_00` | Multipurpose exchange register used by certain commands |
| `$d016` | `DIS_01` | Multipurpose exchange register used by certain commands |
| `$d017` | `DIS_02` | Multipurpose exchange register used by certain commands |
| `$d018` | `DIS_04` | Multipurpose exchange register used by certain commands |
| `$d019` | `DIS_04` | Multipurpose exchange register used by certain commands |
| `$d01a` | `DIS_05` | Multipurpose exchange register used by certain commands |
| `$d01b` | `DIS_06` | Multipurpose exchange register used by certain commands |
| `$d01c` | `DIS_07` | Multipurpose exchange register used by certain commands |

### CIA register
The firmware emulates something that is close to an CIA chip. It is not the intention ti really emulate the chip. Therefore the name might be irritating and needs to be changed in the future. But the register addresses and most of the logic is used for my implementation.

The CIA uses 16 bytes starting from `$dc00`. My implementation is (not strict) based on the documenation of the CIA6526 chip on [C64 Wiki](https://www.c64-wiki.de/wiki/CIA).

| Address | Label | Name | Description |
| --- | --- | --- | --- |
| `$dc00` | `REG_CIA_PRA` | Port A Data | *Not implemented* |
| `$dc01` | `REG_CIA_PRB` | Port B Data | *Not implemented* |
| `$dc02` | `REG_CIA_DDRA` | Data Direction Port A | *Not implemented* |
| `$dc03` | `REG_CIA_DDRB` | Data Direction Port B | *Not implemented* |
| `$dc04` | `REG_CIA_TA_LO` | Timer A - Low byte | Reading: get the current value. Writing: Write the value to a "latch". Means th is the value to be taken for the next initialisation of the timer. |
| `$dc05` | `REG_CIA_TA_HI` | Timer A - High byte | Reading: get the current value. Writing: Write the value to a "latch". Means th is the value to be taken for the next initialisation of the timer. |
| `$dc06` | `REG_CIA_TB_LO` | Timer B - Low byte | Reading: get the current value. Writing: Write the value to a "latch". Means th is the value to be taken for the next initialisation of the timer. |
| `$dc07` | `REG_CIA_TB_HI` | Timer B - High byte | Reading: get the current value. Writing: Write the value to a "latch". Means th is the value to be taken for the next initialisation of the timer. |
| `$dc08` | `REG_CIA_TOD_10THSEC` | Realtime clock 1/10 seconds | *Not implemented* |
| `$dc09` | `REG_CIA_TOD_SEC` | Realtime clock seconds | *Not implemented* |
| `$dc0a` | `REG_CIA_TOD_MIN` | Realtime clock minutes | *Not implemented* |
| `$dc0d` | `REG_CIA_TOD_HR` | Realtime clock hours | *Not implemented* |
| `$dc0c` | `REG_CIA_SDR` | Serial shift register | *Not implemented* |
| `$dc0d` | `REG_CIA_ICR` | Interrupt and control register | Get the source of the interrupt and the flag, if an interrupt occurred. On reading, all flags will be reset. This is the way to acknowledge an interrupt. When writing you can enable or disable certain interrupts.  |
| `$dc0e` | `REG_CIA_CRA` | Control timer A | Control the status and behaviour of timer A |
| `$dc0f` | `REG_CIA_CRB` | Control Timer B | Control the status and behaviour of timer A |


### Timers

> [!NOTE]
> Timers currently are not using real time. This is something for the future. Currently it counts down on every clock cycle. So be aware, that is may change the effect dramatically. A normal cycle takes something liek ~1us. But when a screenupdate happens, it can take up to 17 ms (= 17.000 us). In a future implementation I will use the rp2040 timers for the implementation. 

#### Interrupt Flags

| Binary | Hex | Description |
| --- | --- | --- |
| `00000001` | `$01` | Timer A Interrupt |
| `00000010` | `$02` | Timer B Interrupt |
| `00000100` | `$04` | Frame Interrupt |
| `00001000` | `$08` | *unused* |
| `00010000` | `$10` | *unused* |
| `00100000` | `$20` | *unused* |
| `01000000` | `$40` | *unused* |

# Sprite support
