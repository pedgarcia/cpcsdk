# Introduction #

cpcVideo allows you to display an SCR, WIN or FON file easily on your PC. It also emulates a gate array and CRTC, and makes them available through lua scripts, for easy testing of your most crazy CPC demo effect ideas.

# How to use it #
## Running ##
cpcVideo takes a single parameter, which is the file to handle. On windows you can just drag a file over cpcVideo icon, or associate a file extension to it.

The recognized file extensions (case insensitive) are :
  * SCR: OCP format CPC screen
  * WIN: OCP window
  * FON: OCP font
  * LUA: lua script

A window will open and the file will be displayed inside. If there is an error, it will be printed on the standard output.

## Lua scripts ##

Lua scripts allows to easily play with the CPC video hardware and try out various things without having to mess with z80 code. This makes for a very fast prototyping development cycle. No need to assemble your code for each single change, to count cycles, or to watch out for free memory.

The available functions are:

  * `value = Peek(address)`: return the byte in memory at _address_
  * `Poke(address, value)`: sets the byte in memory at _address_ to _value_
  * `SetCRTC(register, value)`: sets the initial value of crtc register
  * `SetCRTC(register, value, line, nop)`: program a CRTC register change at _line,nop_
  * `SetInk(pen, ink)`: sets the initial value of pen to ink (hardware color number)
  * `SetInk(pen, ink, line, nop)`
  * `SetMode(mode)`: sets the video mode
  * `SetMode(mode, line, nop)`: sets the video mode at the given time. The Gate Array will only take it into account at the next wide enough HBL.