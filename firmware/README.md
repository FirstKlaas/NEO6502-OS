# The Firmware

I am using Arduino IDE 2 for development, as I struggled to setup a smooth development with PlatformIO in vscode, which
would have been my preferred environment.

The Firmware initialises the hardware (keyboard,display, 
...) and serves as a bridge bewteen the hardware and the
kernal. Communication is done by registers that are mapped 
to defined addresses.
 