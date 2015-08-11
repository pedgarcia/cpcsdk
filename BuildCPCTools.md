CPCtools are in the folder cpctools at the root of the trunk.

# Requirements #
Some requirements are needed in order to compile cpctools.

## Developement tools ##
  * make/compilator, ...
`apt-get install build-essential`

## Libraries ##
### For cpcvideo ###
  * SDL
`apt-get install libsdl1.2-dev`

  * xf86v
` apt-get install libxxf86vm-dev`

  * glfw
```
cd cpctools/lib/glfw
make x11-install
```
  * AntTweakBar (http://www.antisphere.com/Wiki/tools:anttweakbar)
```
cd cpctools/lib/AntTweakBar/src/
cp ../include/AntTweakBar.h /usr/local/include/
cp ../lib/libAntTweakBar.so /usr/local/lib/
```


### For cpcfs ###
  * libdsk
```
wget http://www.seasip.info/Unix/LibDsk/libdsk-1.2.1.tar.gz
tar  -xvzf libdsk-1.2.1.tar.gz 
cd libdsk-1.2.1/
./configure
make
make install
```

  * lib765
```
wget http://www.seasip.demon.co.uk/Unix/LibDsk/lib765-0.4.2.tar.gz
tar -xzf lib765-0.4.2.tar.gz
cd lib765-0.4.2/
./configure
make
make install
```

### For AFT ###
  * libserial
```
wget http://prdownloads.sourceforge.net/libserial/libserial-0.5.2.tar.gz?download
tar -xzf libserial-0.5.2.tar.gz 
cd libserial-0.5.2/
```
Add
```
#include <strings.h>
```
in src/SerialStreamBuf.h
and
```
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
```
in src/SerialPort.h and src/PosixSignalDispatcher.h
./configure && make && make install

and
```
include <errno.h>
#include <stdio.h>
#include <stdlib.h>
```
in example/read\_port.h and example/write\_port.h

# Installation #
```
cd cpctools
./configure
make
make install
```