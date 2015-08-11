# Introduction #
In the past, Reloaded was built using the MSYS toolchain. This provides an environment similar to Linux, but generates executables for Windows. However, the executables are sub-optimal because they have to include a compatibility wrapper.

This page describes the steps to setup an environment using Microsoft Visual C++ compiler, to build something slightly closer to a navtive Windows application.

# Setting up the tools #

  * Download and install Visual C++ Express 2010 or newer. Older versions lack the stdint.h header which is part of the C99 stnadard and required by Reloaded.
  * Download ans install the Windows Platform SDK from Microsoft.

For Reloaded itself we won't be using the IDE, but the command-line tool NMake. It should be possible to generate a Visual C++ project as well, if you want so, but this is untested.

# Required libraries #

Reloaded uses several libraries that allows using the same code for Linux and Windows. You need to install them before you can try building.

## wxWidgets ##

Download, install and compile wxWidgets using nmake following this guide: http://wiki.wxwidgets.org/Compiling_Using_MSVC_On_The_Commandline

Build both release and debug versions if you need so (a debug build of Reloaded will use the debug version of wxWidgets libs).

You need the shared version of the libs, edit config.vc to set SHARED=1 (this is NOT the default).

**WARNING**:
If you need to build wxFormBuilder (see below), you need a RELEASE, NON-UNICODE, MONOLITHIC build. It should be possible to edit the VC++ projects for wxFormBuilder, if you want another kind of build.

## pthreads-win32 ##

Download and install pthreads-win32 ( http://sourceware.org/pthreads-win32/ )

you need the following files:
  * pthreadVC2.lib
  * pthreadVC2.dll
  * pthread.h
  * sched.h
  * semaphore.h

Put the lib file into a dir pointed by $LIB environment variable
Put the dll into a dir pointed by $PATH
Put the h into a dir pointed by $INCLUDE


## CMake ##
Download and install cmake

## PortAudio ##
Download and build PortAudio

**Note**
All command lines are meant to be typed into a Visual Studio prompt. You can get one from the VC++ IDE or open a regular CMD prompt and then run
```
"C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat"
```

The commands to build PortAudio using cmake and nmake are:

```
mkdir cmake
cd cmake
cmake .. -G"NMake Makefiles"
nmake
```


Copy the .h, .dll and .lib files as appropriate so the compiler can find them.

## wxFormBuilder ##
**note**
It is strongly recommended that you use the precompiled version available in our downloads page.

You don't ned wxFormBuilder if you only want to compile Reloaded. It is only needed to make changes to the UI.

These compiling steps are only for our internal use.

  * Get the 3.x/trunk from their SVN.
  * Use premake to generate Visual Studio solution file.
  * Set the WXWIN env var to C:\wxWidgets-2.8.12 (adapt version as needed) if it isn't already done. These projects depend on the var to find the includes and libs.

Most of the time you want a release build of wxFormBuilder.
For now, you need our patch to it (see BuildCaprice page), else you can't generate the input settings page right.
(we may want to rework that at a later point...)

# Building Reloaded #

## StSoundLibrary ##
StSoundLibrary comes with a Visual C++ project which you can use to build the dll. Then, install the dll, lib, and .h files as you did for the other libs.

## Reloaded emulator ##
We will be using cmake again to generate the build files.

```
mkdir build
cd build
cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release
nmake
```