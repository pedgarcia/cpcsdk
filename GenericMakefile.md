# Makefile #
This makefile allows to build any project using cpcsdk tools.
Note it is still work in progress, so there are some rough edges.

```
# generic CPC-project makefile
# Copyright 2011 PulkoMandy - Shinra!

# TODO
# * I usually do incbin "something.exo" in my sourcecode, but this doesn't get 
#	in the makefile dependancies. Either add something equivalent to gcc -M in 
#	vasm, or find another way... (grep INCBIN + generate dependencies ?)

# USER SETTINGS ################################################################

# Enter your demo name here
NAME:=TESTDEMO

# Set disk contents
$(NAME).dsk:: $(NAME).BIN LOADER.BIN

# List the sourcefiles for your main code. This is linked
# at &300 and (hopefully) loaded there by the loader code.
$(NAME).exe:: main.o
$(NAME).BIN: START = 0x300

# List the dependancies for LOADER.BIN. Linked at &9000
LOADER.exe: loader.o deexo.o
LOADER.BIN: START = 0x9000

# define screenmode for each picture
shrlogo.scr: SCREENMODE = 1

# This adds shrlogo.exo to the dependancies of loader.o. Assumes it will be
# INCBIN there...
loader.o:: shrlogo.exo

# TODO - move everything below to a generic cpc.mk file...
# GENERIC RULES ###############################################################

.DEFAULT_GOAL := $(NAME).dsk

# Nice header for doing something
BECHO = @echo -e "\x1B[7m\t$(1)\t\x1B[0m"

# Build the DSK-File (main rule)
%.dsk:
	$(call BECHO, "Putting files in DSK...")
	cpcfs $@ f
	for i in $^;do cpcfs $@ p $$i;done;

# Run the emulator
emu: $(NAME).dsk
	$(call BECHO,"Running caprice...")
	caprice -a $< &

# Prepend header
# TODO entry point
%.BIN: %.exe
	hideur $< -o $@ -l $(START)

# Link the sources ($^ means "all dependencies", so all of them should be .o 
# files - which is good, since anything else should be incbined somewhere)
%.exe:
	$(call BECHO,"Linking $@")
	vlink -b rawbin1 -Ttext $(START) -M -o $@ $^

# Assemble the sources
%.o: %.z80
	$(call BECHO,"Assembling $<...")
	vasmz80_oldstyle -Fvobj -o $@ $<

# Crunch a screen
%.exo: %.scr
	$(call BECHO,"Crunching $<...")
	exoraw -o $@ $<

# convert png to cpc screen format
# SCREENMODE can force the screenmode, otherwise it's guessed from the png 
# bitdepth
%.scr: %.png
	$(call BECHO,"Converting $<...")
	png2crtc $< $@ 7 $(SCREENMODE)

clean:
	$(call BECHO,"Cleaning...")
	rm *.exo *.BIN *.dsk *.o *.exe
```

# Assembler #
some notes about vasm :
  * By default symbols are local to a file. To export a symbol 'ASymbol' you have to do this in your sourcefile :
```
    GLOBAL ASymbol
```

# More TODOs #
  * Generate a SNA file and run aft so it's ready to be sent
  * Allow to run the emulator from the makefile