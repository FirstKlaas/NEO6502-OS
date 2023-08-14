> [!WARNING]
> This code is heavily under development and will change permanently. Most of the time, the code will not work. I commit quite often, as I work on different
> computers. SO USE IT AT YOUR OWN RISK.

# NEO6502-OS

This is my approach to write an "operating system" for the 65c02 processor living in the matrix of an rp2040. The code is based on the work of olimex.
I am not amining to emulate any existing (old) hardware like c64 or apple II. Therefore I have my own registers, modes, kernal routines and so on.

What I am working on:
- Sprite engine: Sprites are defined an manipulated in assembler, but drawn from the rp2040 code
- Text routines: Providing text support functions. The rp240 only offers a simple writeChar and cursor/color getters and setters. The rest is done in assembly
- Graphics roputines: Offering routines for lines, circles, etc.
- Performance: Always a topic. But you can find more experienced people working more speed. My goal is to have a cpu running at ~ 1MHz and a frame rate of 25 FPS 

## Kernel 
The kernal is written in assembler using KickAssembler to convert it to prg files. One nice commandline option for the Kick Assembler is, that it can
generate an prg file for each segment defined in the code.
The assembler files are located unter the folder assembler. It also includes the copy of KickAss.jar file I am using.

## Firmware rp2040
The firmware emulates the memory and all the hardware that the 65c02 thinks it is connect to. The code is located in the folder "firmware". I am
usind the arduino ide 2. Later I want to move to PlatformIO.

## Tools
### Firmware Converter
The kernel will be flashed as the "initial memory state" to the rp2040. Therefore the prg files have to be converted to c code. The little python tool 
takes all the prg files in the folder and created a single c file with a loader function.


