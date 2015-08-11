# Why #
SNAMP load a snapshot file and plays the music from it.
This is a replacement for the older YM format.

Why changing the good old music format you're used to for your preferred CPC musics on PC ? Because YM is unable to render samples, sidvoices, or any other special effects. The ayc format was created to fix this, but on the CPC you can use the gate array interrupt delay to play music at rates different from 50Hz, so this is still not enough.

The only real solution is to emulate the whole CPC. By removing the display part of the Reloaded emulator, the program is much lighter and faster. This way you can leave SNAMP running in the background and listen to your preferred music.

# How #
Most of the code is shared with the Reloaded emulator. In fact, SNAMP is only 96 lines of code.

This way, it gets enhancements from Reloaded immediately. You can also have a look at the code to understand how to embed Reloaded in your own apps.

# Using it #

Just drag a snapshot file on the executable. Or you can associate .snamp files to it to listen to them with a simple double click.

# The future #

One feature we are thinking about is some Plus support for playing these frenzy DMA musics. This is impossible both with YM and other AY formats.

Another thing we may add is a way to have playlists (with title, artist, and duration).