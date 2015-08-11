# Requirements #

  * Visual Studio express 2013 for Desktop (CMake can also generate projects for older versions, but I didn't try that).
  * cmake


# Dependencies #
## LibDSK ##
Unfortunately, the binary releases for windows lack the import library, so it's not possible to use them. Get the source release and import the provided Visual C++ 6 project in Visual C++ express 2013. The project is automatically converted to the new format.

  * The solution to generate is **libdsk**. atlibdsk will not compile,
  * Add missing files to the solution: comptlzh.c, drvydsk.c, drvsimh.c
  * generate the solution.

You will get the needed libdsk.dll and libdsk.lib files.

# Compiling CPCTools #
  * Open the cmake gui wizard
  * Select the source dir and build dir. It is a good idea to select different dirs.
  * set LIBDSK\_HEADERS\_DIR to point to the libdsk include/ folder, **before configuring for the first time**. If this fails, delete the build directory and start over.
  * configure and generate the project with CMake
  * Open the solution in Visual Studio (CPCTools.sln in the build folder) and build it (press F7).