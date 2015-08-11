This is an example of how to use the cpcsdk tools in your projects. Actually its the makefile from the Znax game (still to be released).
You can get an idea of how to use the tools together to make a practical devkit and just type :make in vim.
This makefile supports :
  * Directly writing output files to an usb floppy drive using a parados formatted disk
  * Making a dsk then copying it to a 720k dos drive (to be put to a real disk with writedsk on a real cpc
  * Just output a dsk you can run in your emulator

Images are crunched automatically.
Improvements needed :
  * find a way to use datalinker for handling the alignment of data (i'm doing it with sjasm by hand). Need to define the addresses before the code is actually compiled ?
  * relocate compiled starkos musics so you don't have to bother about their address. work in progress, see the relsong tool.
  * output a snapshot and run it inside caprice

Note caps are used because of cpcfs bugs... If you use iDSK only it should be fine.


```
usbfloppy: OUT/ZNAX.BIN OUT/SPRTEST.BIN CRU/GAMEBIN.EXO
	@echo "### Writing files to romdos floppy... ###"
	cpcfs /dev/sdb p OUT/ZNAX.BIN,0x9000,0x9000 OUT/SPRTEST.BIN,0x800,0x800 -b -e

znax.dsk: OUT/ZNAX.BIN CRU/GAMEBIN.EXO
	echo "### Putting files in DSK..."
	cd OUT && iDSK ../znax.dsk -f -i SPRTEST.BIN -t 1 -e 800 -c 800
	cd OUT && iDSK ../znax.dsk -f -i ZNAX.BIN -t 1 -e 9000 -c 9000

dosflop: znax.dsk
	echo "### Writing to DOS floppy..."
	mcopy -i msdos.img znax.dsk ::
	dd if=msdos.img of=/dev/sdb

disk: znax.dsk
	echo "### Writing to disk ..."
	dskwrite znax.dsk

# Assemble the sources
OUT/SPRTEST.BIN: IMG/sprites.bin CRU/ZNXGAME.EXO
	@true #do nothing ;)

OUT/ZNAX.BIN: src/CPC.z80 src/EXOMIZE3.ASM src/font16.z80 src/GAME.z80 src/keyboard.z80 src/loader.z80 src/MENU.z80 src/SPRTEST.z80 src/znax.z80 src/Starkos.z80 CRU/ZNXGAME.EXO CRU/HISCORES.EXO OUT/SPRTEST.BIN ZIKs/menu.zik
	@echo "###Assembling sources..."
	cd src && sjasmplus znax.z80

# Creates the scr from png
IMG/znxgame.scr: res/znax-game.png
	png2crtc res/znax-game.png IMG/znxgame.scr

IMG/hiscores.scr: res/hiscores.png
	png2crtc res/hiscores.png IMG/hiscores.scr

# Crunch the data
CRU/ZNXGAME.EXO: IMG/znxgame.scr
	exoraw -c -o CRU/ZNXGAME.TMP IMG/znxgame.scr
	exoopt CRU/ZNXGAME.TMP CRU/ZNXGAME.EXO
	rm CRU/ZNXGAME.TMP

CRU/HISCORES.EXO: IMG/hiscores.scr
	exoraw -c -o CRU/HISCORES.TMP IMG/hiscores.scr
	exoopt CRU/HISCORES.TMP CRU/HISCORES.EXO
	rm CRU/HISCORES.TMP
```