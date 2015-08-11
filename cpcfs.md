# Introduction #

cpcfs is a tool for reading and writing your floppies. It handles dsk files, but can also directly read and write directly on a physical floppy drive.

# Details #

The syntax is quite simple :
`cpcfs dskfile command file`
  * dskfile is the file to process. It can be mydisk.dsk, a:, b: if you are running under windows, /dev/fd0, /dev/fd1 if you are running under linux, and /dev/sdb for using with an usb floppydrive.
  * command is one letter to say what to do. For example, c will print the floppy's catalog, g will get a file, p will put a file on the dsk, h will print a file header. See the built-in help for more info.
  * file is needed by some commands. You can specify all files parameters here, in the format user:name.ext,s,p,load,exec where user is the user number, "s" and "p" are flags to say you want the file to be system or protected, load and exec are the loading and execution addresses. Here is an example:
`cpcfs myfloppy.dsk p 1:mydemo.bin,s,0x4000,0x4000`

# Notes about usb floppy drive #

This tool is able to read and write from an usb floppy drive. However, this support is very limited, due to the crappy hardware. You can only read and write on a Romdos D1 disk, wich can only be read on a cpc with the Parados ROM. It is not possible to do better. Big hacking and tweaking of the usb floppy controller parameters may or may not allow to get more done, see the [[ufitoolbox](ufitoolbox.md)] project for that.

# Known bugs #

  * No support for parados formats other than romdos d1. May need some modifications to libdsk.
  * Usb drive can only be /dev/sdb for now. Find a better way for identifying it. See what ufiformat does.