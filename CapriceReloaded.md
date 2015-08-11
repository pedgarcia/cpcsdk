# Introduction #

Caprice Reloaded is a fork of Caprice 32, rewritten in C++ and modified to work under linux in a more friendly way. We are in the process of writing the new GUI for it.


# Details #

Caprice is useful for testing your Amstrad code without transferring it to the CPC. It is also a great help when debugging, as it allows you to set breakpoints, explore and alter the hardware registers (gate array, z80, crtc, ...) and the memory.

However, it may have differences with a real CPC in some cases and your code should always be tested on the real hardware before release :)

Caprice Reloaded is still work in progress, the emulation is quite good but the user interface is a great mess. We are working on it.

# Installation under Windows #

As of now, there is no automated setup, so here are some hints :
  * Most of the data is stored in Document and settings/your\_user/application data/reloaded/
In this folder you need Keymap.cfg, and a folder called roms with the roms you want to use (usually cpc6128.rom and amsdos.rom, but you can add more). That should set you up, you can place all the other files anywhere on your harddisk.