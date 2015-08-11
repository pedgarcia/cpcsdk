You need wxWidget headers, and portaudio library.
lib765 and libdsk can be used but they are optional.

# StSoundLib #
Don't use a version of StSoundLib you found somewhere else on the internet ! The one in our repository was fixed to sound more like a real CPC. The volume tables in he original are strange and the mixing is weird too.
```
cd libstsound
./build_config.sh && ./configure && make && sudo make install
```

# wxFormBuilder #
This is not needed if you just want to build and use caprice, it is the tool we use to create the windows in caprice. Unfortunately we had to patch it to make it do some special things, so you will have to build it from source if you want to help us. Get the latest svn version :
**WARNING: if you don't aply the patch, wxFormBuilder will run and work fine, however the generated code will be wrong and you won't be able to use it!**
```
svn co https://wxformbuilder.svn.sourceforge.net/svnroot/wxformbuilder/3.x/trunk wxformbuilder
```

Now patch the files as follow (or get the [patch](http://cpcsdk.googlecode.com/files/wxformbuilder_r2024.patch) and apply it) :
|file|line|change|
|:---|:---|:-----|
|output/xml/default.xml|20  |property use\_enum should be type "text" instead of "bool"|
|src/codegen/cppcg.cpp|471 |useEnum should be int instead of bool and initialized to 0 intead of false|
|src/codegen/cppcg.cpp|474 |useEnum should be set to useEnumProperty->GetValueAsInteger() instead of true|
|src/codegen/cppcg.cpp|662 |replace if(!useEnum) with if(useEnum==0)|
|src/codegen/cppcg.cpp|673 |replace useEnum with useEnum==1 in the call to GenClassDeclaration|
Note the exact line numbers may change as the code may be updated by the devs. A patch was sent to them but they chose not to apply it as our needs are really specific.

The purpose of this change is to allow us to use keyboard scancodes that can be sent to the emulator without the need for a lookup table.

You can now proceed and build wxFormBuilder :
```
./create_build_files.sh
make
```

The executable is put in output/bin/ . I know no way to install it to a more practical place (the usual 'make install' does not work).

# Caprice itself (finally !) #
This is the recommended setting if you want to use caprice as a CPC emulator. Lib765 gives troubles and don't add extra functionality. Debug is useless unless you want to help us clean our code...
You can use other options for ./configure if you want to try things. But it will probably break things or make them run slower.

```
./build_config.sh
./configure
make
make install
```