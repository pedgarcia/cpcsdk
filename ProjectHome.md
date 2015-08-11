The Amstrad CPC/Plus is an old 8-bit microcomputer. It's still used nowadays by some people to create demos. However, there are almost no tools to do that under Linux. This project aims to collect the various bit of existing sourcecode in one common place, add the missing features, and make life easier for all developpers.

Available tools include :
  * The Caprice Reloaded emulator, with integrated assembler and debugger,
  * gfx2crtc, a tool to convert pictures to the amstrad sceen format
  * An imporved version of Ramlaid's cpctools, now running under linux, with (limited) support for usb floppy drives
  * A special version of STSound from Leonard, modified to emulate an AY3 more accurately (the original emulates the slightly different YM chip used in the Atari ST)
  * "Hideur Maikeur" from Downwater for handling AMSDOS headers
  * iDSK from sid for manipulating dsk images and files inside.

The goal is to provide easy-to-use cross development tools for the Amstrad under Linux, to speed up development of your demos and games. Most of these tools are designed to be used from a makefile and are only useable from the command line. Amongst other things, you will find an image converter, an image viewer, the first tool for reading and writting floppies from an usb drive (limited to romdos d1 disks), a new version of Caprice with some improvements, and a port of ramlaid's Cpctools to Linux.
You can find the dependicies in the following repository:
  * deb http://simon.addareyss.free.fr/debian/cpctoolsdeps  ./
  * deb-src http://simon.addareyss.free.fr/debian/cpctoolsdeps ./



Most of them should also compile under Windows, or wathever OS you are using, if you're lucky enough.

## Binary packages ##
We can't provide binaries for every linux distro out there. So here's a list of people doing it for us :
  * Arch Linux :
> > http://aur.archlinux.org/packages.php?ID=38853 ; http://aur.archlinux.org/packages.php?ID=38854 (compiled by CalimeroTeknik)
[![](http://cpc-live.com/topsites/button.php?u=reloaded&uselessparam=.png)](http://cpc-live.com/topsites/)