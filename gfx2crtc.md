# Introduction #

gfx2crtc can convert any picture in any mode from png to scr for displaying on the CPC. It can handle values of CRTC register 9 different than the default of 7, that will allow your picture files to be somewhat smaller.


# How to use #

The command line is simple:
`png2crtc infile outfile r9 mode`
  * infile is the picture you want to convert. It must be a paletized png with 16 colors or less. png2crtc only converts the picture, it does not offers any color reduction feature.
  * outfile is the name of the file where you want the cpc data to be saved.
  * [r9](https://code.google.com/p/cpcsdk/source/detail?r=9) is the value you want to give to CRTC register 9. Default is 7. In most cases, you will not want to change that. If you want to convert a sprite, use value 0 to have the data stored in linear mode.
  * mode is the graphic mode you want to use. gfx2crtc will try to guess the mode from the number of colors. If there is one or two colors, it will be mode 2, less than 5, it will be mode 1, and mode 0 in any other cases. If that fails, you can force the mode to use.

gfx2crtc will process your file and show some informations it calculated.

# Known bugs #

_see the Issues tab for more information_
It is not possible to convert a big picture in sprite format (for example, many sprites put together in one single file). You are limited to a total of 1048 characters by picture.

# Planned features #

  * Support for graphOS format
  * Support for ASIC sprites format
  * Palette export
  * Real linear mode for sprites
  * "fontaligner"-like mode to convert fonts (rearrange the picture in columns before converting)