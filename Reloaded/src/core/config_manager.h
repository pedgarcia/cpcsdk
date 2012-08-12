//
// Caprice32 config manager
//

#ifndef _CONFIG_H_
#define _CONFIG_H_

class Emulator;


#include "cap32.h"
#include "cap32type.h"
#include "video.h"

class t_CPC;

#include "render.h"

class t_CPC
{
public:
    // System
   unsigned int model;
   unsigned int jumpers;
   unsigned int ram_size;
   unsigned int speed;
   unsigned int limit_speed;
   unsigned int paused;
   unsigned int breakpoint;
   unsigned int auto_pause;
   unsigned int keyboard_line;
   unsigned int tape_motor;
   unsigned int tape_play_button;
   unsigned int printer;
   unsigned int printer_port;
   unsigned int mf2;
   unsigned int keyboard;
   unsigned int joysticks;
   int cycle_count;

   // Sound
   unsigned int snd_enabled;
   unsigned int snd_playback_rate;
   unsigned int snd_bits;
   unsigned int snd_stereo;
   unsigned int snd_volume;
   unsigned int snd_pp_device;

   // Keyboard
   unsigned int kbd_layout;

   // Floppy
   unsigned int max_tracksize;

   // Files
   char snap_path[_MAX_PATH + 1];
   char snap_file[_MAX_PATH + 1];
   bool snap_zip;
   char drvA_path[_MAX_PATH + 1];
   char drvA_file[_MAX_PATH + 1];
   bool drvA_zip;
   unsigned int drvA_format;
   char drvB_path[_MAX_PATH + 1];
   char drvB_file[_MAX_PATH + 1];
   bool drvB_zip;
   unsigned int drvB_format;
   char tape_path[_MAX_PATH + 1];
   char tape_file[_MAX_PATH + 1];
   bool tape_zip;
   char printer_file[_MAX_PATH + 1];
   char sdump_file[_MAX_PATH + 1];

   char rom_path[_MAX_PATH + 1];
   char rom_file[16][_MAX_PATH + 1];
   char rom_mf2[_MAX_PATH + 1];

    // Video
    bool scr_fps ;
    int  scr_intensity ;
    bool scr_remanency ;
    bool fs;
    bool oglfilter;
    int vid_w,vid_h,vid_bpp;
    Renderer::MonitorMode scr_tube;
	unsigned int crtc;

public:
   void loadConfiguration ();
   void saveConfiguration();
    t_CPC(Emulator* emu);
	~t_CPC();

private:
	Emulator* emulator;
};

#endif
