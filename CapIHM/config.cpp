//
// Caprice32 config manager
//

#include "config.h"
#include <stdio.h>
#include "cap32type.h"
#include <string.h>
#include <stdlib.h>
#include "rom_mods.h"
#include "audio.h"
#include "dsk.h"
#include "render.h"
#include "emulator.h"
#include "c_inifile.h"

#ifdef WIN32
#include <direct.h>
#else
#include <linux/unistd.h>
#endif

#define MIN_SPEED_SETTING 2
#define MAX_SPEED_SETTING 32
#define DEF_SPEED_SETTING 4

extern t_disk_format disk_format[MAX_DISK_FORMAT];

unsigned int getConfigValueInt (const char* pchFileName, const char* pchSection, const char* pchKey, unsigned int iDefaultValue)
{
	C_Inifile_error err = C_INIFILE_NO_ERROR;
	int val = c_inifile_get_integer(pchSection,pchKey,&err);
	if (err!=C_INIFILE_NO_ERROR)
	{
	    return iDefaultValue;
	}
	else
	{
	    return val;
	}
}

void getConfigValueString (const char* pchFileName, const char* pchSection, const char* pchKey, char* pchValue, const char* pchDefaultValue)
{
    char* val;
    val = c_inifile_get_string(pchSection,pchKey,NULL);
    if(val==NULL)
    {
	strcpy(pchValue,pchDefaultValue);
    }
    else
    {
	strcpy(pchValue,val);
	free(val);
    }
    return;
}



void t_CPC::loadConfiguration (Emulator &emulator)
{
	char chFileName[_MAX_PATH + 1];
	char chPath[_MAX_PATH + 1];
	FILE *pfileObject = NULL;
	C_Inifile_error err = C_INIFILE_NO_ERROR;

	char chAppPath[_MAX_PATH + 1];
	// get the location of the executable
#ifdef WIN32
	_getcwd(chAppPath, sizeof(chAppPath)-1);
#else
	getcwd (chAppPath, sizeof(chAppPath)-1);
#endif

	//strncpy(chFileName, chAppPath, sizeof(chFileName)-10);
	//strcat(chFileName, "/cap32.cfg");
	strcpy(chFileName, "cap32.cfg");
	c_inifile_init(chFileName,&err);
	if(err!=C_INIFILE_NO_ERROR)
	    printf("Error opening configfile !\n");
	else
	{
//	    memset(this, 0, sizeof(t_CPC)); // EUH ??!

	    // CPC 6128
	    model = getConfigValueInt(chFileName, "system", "model", 2);
	    if (model > 2)
	    {
		model = 2;
	    }

	    // OEM is Amstrad, video refresh is 50Hz
	    jumpers = getConfigValueInt(chFileName, "system", "jumpers", 0x1e) & 0x1e;
	    // 128KB RAM
	    ram_size = getConfigValueInt(chFileName, "system", "ram_size", 128) & 0x02c0;
	    if (ram_size > 576)
	    {
		ram_size = 576;
	    }
	    else if ((model == 2) && (ram_size < 128))
	    {
		// minimum RAM size for CPC 6128 is 128KB
		ram_size = 128;
	    }

	    // original CPC speed
	    speed = getConfigValueInt(chFileName, "system", "speed", DEF_SPEED_SETTING);
	    if ((speed < MIN_SPEED_SETTING) || (speed > MAX_SPEED_SETTING))
	    {
		speed = DEF_SPEED_SETTING;
	    }
	    limit_speed = 1;
	    auto_pause = getConfigValueInt(chFileName, "system", "auto_pause", 1) & 1;
	    printer = getConfigValueInt(chFileName, "system", "printer", 0) & 1;
	    mf2 = getConfigValueInt(chFileName, "system", "mf2", 0) & 1;
	    keyboard = getConfigValueInt(chFileName, "system", "keyboard", 0);
	    if (keyboard > MAX_ROM_MODS)
	    {
		keyboard = 0;
	    }
	    joysticks = getConfigValueInt(chFileName, "system", "joysticks", 0) & 1;

	    vid_w = getConfigValueInt(chFileName, "video", "scr_width", 800);
	    vid_h = getConfigValueInt(chFileName, "video", "scr_height", 600);
	    vid_bpp = getConfigValueInt(chFileName, "video", "scr_bpp", 24);
	    vid_style = (VideoPlugin::VideoType)getConfigValueInt(chFileName, "video", "scr_style", 1);
	    bool fs = (getConfigValueInt(chFileName, "video", "scr_window", 0) & 1) == 0;
	    bool oglfilter = getConfigValueInt(chFileName, "video", "scr_oglfilter", 1) & 1;

//	    emulator.GetRenderer().SetVideoMode((VideoPlugin::VideoType)style, w, h, bpp, fs);
	    emulator.GetRenderer().SetOpenGLFilter(oglfilter);


	    bool scr_fps = getConfigValueInt(chFileName, "video", "scr_fps", 0) & 1;
	    //	renderer.SetDisplayFPS(scr_fps);


	    bool color = scr_tube = (getConfigValueInt(chFileName, "video", "scr_tube", 0) & 1) == 0;
	    int intensity = scr_intensity = getConfigValueInt(chFileName, "video", "scr_intensity", 10);
	    bool remanency = scr_remanency = getConfigValueInt(chFileName, "video", "scr_remanency", 0) & 1;
	    if ((intensity < 5) || (intensity > 15))
	    {
		intensity = 10;
	    }
	    emulator.GetRenderer().SetMonitor(color, intensity, remanency);

	    //renderer.scr_vsync = getConfigValueInt(chFileName, "video", "scr_vsync", 1) & 1;
	    //renderer.scr_led = getConfigValueInt(chFileName, "video", "scr_led", 1) & 1;

	    snd_enabled = getConfigValueInt(chFileName, "sound", "enabled", 1) & 1;
	    snd_playback_rate = getConfigValueInt(chFileName, "sound", "playback_rate", 44100);
	    snd_bits = getConfigValueInt(chFileName, "sound", "bits", 16);
	    snd_stereo = getConfigValueInt(chFileName, "sound", "stereo", 1) & 1;
	    snd_volume = getConfigValueInt(chFileName, "sound", "volume", 100);
	    if (snd_volume > 100)
	    {
		snd_volume = 100;
	    }
	    snd_pp_device = getConfigValueInt(chFileName, "sound", "pp_device", 0) & 1;

	    kbd_layout = getConfigValueInt(chFileName, "control", "kbd_layout", 0);
	    if (kbd_layout > 3)
	    {
		kbd_layout = 0;
	    }

	    max_tracksize = getConfigValueInt(chFileName, "file", "max_track_size", 6144-154);
	    strncpy(chPath, chAppPath, sizeof(chPath)-7);
	    strcat(chPath, "/snap");
	    getConfigValueString(chFileName, "file", "snap_path", snap_path, chPath);
	    if (snap_path[0] == '\0')
	    {
		strcpy(snap_path, chPath);
	    }
	    getConfigValueString(chFileName, "file", "snap_file", snap_file, "");
	    snap_zip = getConfigValueInt(chFileName, "file", "snap_zip", 0) & 1;
	    strncpy(chPath, chAppPath, sizeof(chPath)-7);
	    strcat(chPath, "\\disk");
	    getConfigValueString(chFileName, "file", "drvA_path", drvA_path, chPath);
	    if (drvA_path[0] == '\0')
	    {
		strcpy(drvA_path, chPath);
	    }
	    getConfigValueString(chFileName, "file", "drvA_file", drvA_file, "");
	    drvA_zip = getConfigValueInt(chFileName, "file", "drvA_zip", 0) & 1;
	    drvA_format = getConfigValueInt(chFileName, "file", "drvA_format", DEFAULT_DISK_FORMAT);
	    getConfigValueString(chFileName, "file", "drvB_path", drvB_path, chPath);
	    if (drvB_path[0] == '\0')
	    {
		strcpy(drvB_path, chPath);
	    }
	    getConfigValueString(chFileName, "file", "drvB_file", drvB_file, "");
	    drvB_zip = getConfigValueInt(chFileName, "file", "drvB_zip", 0) & 1;
	    drvB_format = getConfigValueInt(chFileName, "file", "drvB_format", DEFAULT_DISK_FORMAT);
	    strncpy(chPath, chAppPath, sizeof(chPath)-7);
	    strcat(chPath, "/tape");
	    getConfigValueString(chFileName, "file", "tape_path", tape_path, chPath);
	    if (tape_path[0] == '\0')
	    {
		strcpy(tape_path, chPath);
	    }
	    getConfigValueString(chFileName, "file", "tape_file", tape_file, "");
	    tape_zip = getConfigValueInt(chFileName, "file", "tape_zip", 0) & 1;

#ifndef HAVE_LIB765_H
	    int iFmt = FIRST_CUSTOM_DISK_FORMAT;
	    {
		// loop through all user definable disk formats
		for (int i = iFmt; i < MAX_DISK_FORMAT; i++)
		{
		    dword dwVal;
		    char *pchTail;
		    char chFmtId[14];
		    // clear slot
		    disk_format[iFmt].label[0] = 0;
		    // build format ID
		    sprintf(chFmtId, "fmt%02d", i);
		    char chFmtStr[256];
		    getConfigValueString(chFileName, "file", chFmtId, chFmtStr, "");
		    // found format definition for this slot?
		    if (chFmtStr[0] != 0)
		    {
			char chDelimiters[] = ",";
			char *pchToken;
			// format label
			pchToken = strtok(chFmtStr, chDelimiters);
			strncpy((char *)disk_format[iFmt].label, pchToken, sizeof(disk_format[iFmt].label)-1);

			// number of tracks
			pchToken = strtok(NULL, chDelimiters);
			// value missing?
			if (pchToken == NULL)
			{
			    continue;
			}
			dwVal = strtoul(pchToken, &pchTail, 0);
			// invalid value?
			if ((dwVal < 1) || (dwVal > DSK_TRACKMAX))
			{
			    continue;
			}
			disk_format[iFmt].tracks = dwVal;

			// number of sides
			pchToken = strtok(NULL, chDelimiters);
			// value missing?
			if (pchToken == NULL)
			{
			    continue;
			}
			dwVal = strtoul(pchToken, &pchTail, 0);
			// invalid value?
			if ((dwVal < 1) || (dwVal > DSK_SIDEMAX))
			{
			    continue;
			}
			disk_format[iFmt].sides = dwVal;

			// number of sectors
			pchToken = strtok(NULL, chDelimiters);
			// value missing?
			if (pchToken == NULL)
			{
			    continue;
			}
			dwVal = strtoul(pchToken, &pchTail, 0);
			// invalid value?
			if ((dwVal < 1) || (dwVal > DSK_SECTORMAX))
			{
			    continue;
			}
			disk_format[iFmt].sectors = dwVal;

			// sector size as N value
			pchToken = strtok(NULL, chDelimiters);
			// value missing?
			if (pchToken == NULL)
			{
			    continue;
			}
			dwVal = strtoul(pchToken, &pchTail, 0);
			// invalid value?
			if ((dwVal < 1) || (dwVal > 6))
			{
			    continue;
			}
			disk_format[iFmt].sector_size = dwVal;

			// gap#3 length
			pchToken = strtok(NULL, chDelimiters);
			// value missing?
			if (pchToken == NULL)
			{
			    continue;
			}
			dwVal = strtoul(pchToken, &pchTail, 0);
			// invalid value?
			if ((dwVal < 1) || (dwVal > 255))
			{
			    continue;
			}
			disk_format[iFmt].gap3_length = dwVal;

			// filler byte
			pchToken = strtok(NULL, chDelimiters);
			// value missing?
			if (pchToken == NULL)
			{
			    continue;
			}
			dwVal = strtoul(pchToken, &pchTail, 0);
			disk_format[iFmt].filler_byte = (byte)dwVal;

			for (int iSide = 0; iSide < (int)disk_format[iFmt].sides; iSide++)
			{
			    for (int iSector = 0; iSector < (int)disk_format[iFmt].sectors; iSector++)
			    {
				// sector ID
				pchToken = strtok(NULL, chDelimiters);
				// value missing?
				if (pchToken == NULL)
				{
				    dwVal = iSector+1;
				}
				else
				{
				    dwVal = strtoul(pchToken, &pchTail, 0);
				}
				disk_format[iFmt].sector_ids[iSide][iSector] = (byte)dwVal;
			    }
			}
			// entry is valid
			iFmt++;
		    }
		}
	    }
#endif
	    strncpy(chPath, chAppPath, sizeof(chPath)-13);
	    strcat(chPath, "/printer.dat");
	    getConfigValueString(chFileName, "file", "printer_file", printer_file, chPath);
	    if (printer_file[0] == '\0')
	    {
		strcpy(printer_file, chPath);
	    }
	    strncpy(chPath, chAppPath, sizeof(chPath)-12);
	    strcat(chPath, "/screen.png");
	    getConfigValueString(chFileName, "file", "sdump_file", sdump_file, chPath);
	    if (sdump_file[0] == '\0')
	    {
		strcpy(sdump_file, chPath);
	    }

	    strncpy(chPath, chAppPath, sizeof(chPath)-5);
	    strcat(chPath, "/rom");
	    getConfigValueString(chFileName, "rom", "rom_path", rom_path, chPath);
	    // loop for ROMs 0-15
	    for (int iRomNum = 0; iRomNum < 16; iRomNum++)
	    {
		char chRomId[14];
		sprintf(chRomId, "slot%02d", iRomNum); // build ROM ID
		getConfigValueString(chFileName, "rom", chRomId, rom_file[iRomNum], "");
	    }
	    // if the path is empty, set it to the default
	    if (rom_path[0] == '\0')
	    {
		strcpy(rom_path, chPath);
	    }

	    if ((pfileObject = fopen(chFileName, "rt")) == NULL)
	    {
		// insert AMSDOS in slot 7 if the config file does not exist yet
		strcpy(rom_file[7], "amsdos.rom");
	    }
	    else
	    {
		fclose(pfileObject);
	    }
	    getConfigValueString(chFileName, "rom", "rom_mf2", rom_mf2, "");

	    c_inifile_close();
	}
}
