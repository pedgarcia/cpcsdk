/* Caprice32 - Amstrad CPC Emulator
   (c) Copyright 1997-2004 Ulrich Doewich

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/*
   This file includes video filters from the SMS Plus/SDL 
   sega master system emulator :
   (c) Copyright Gregory Montoir
   http://membres.lycos.fr/cyxdown/smssdl/
*/

/*
   This file includes video filters from MAME
   (Multiple Arcade Machine Emulator) :
   (c) Copyright The MAME Team
   http://www.mame.net/
*/

#include "video.h"
#include <SDL_opengl.h>
#include "glfuncs.h"
#include <math.h>
#include <malloc.h>
#include <algorithm>
#include <iostream>

#ifndef min
#define min(a,b) (a<b ? a : b)
#endif

#ifndef max
#define max(a,b) (a>b ? a : b)
#endif

/* ------------------------------------------------------------------------------------ */
/* Generic video plugin --------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------ */
int VideoPlugin::CPCVisibleSCRWidth = 384; // visible width: 4+40+4 * 8
int VideoPlugin::CPCVisibleSCRHeight = 270;

VideoPlugin::VideoPlugin(const string name, const Uint32 format, const Uint8 halfPixels) :
_name(name),
_formats(format),
_halfPixels(halfPixels),
_postRenderCallBack(NULL)
{
}

VideoPlugin::~VideoPlugin()
{
}

/*VideoPlugin* VideoPlugin::Create(VideoPlugin *ptr)
{
	return ptr;
}*/

VideoPlugin* VideoPlugin::Create()
{
	cout << "Error: This VideoPlugin doesn't have Create() method" << endl;
	return NULL;
}

// checks for an OpenGL extension
bool VideoPlugin::HaveOpenGLExtension(const string &name_ext)
{
	const char *ext;
	ext = (const char *) (eglGetString (GL_EXTENSIONS));
	const char *f;
	if (ext == NULL)
		return false;
	f = ext + strlen (ext);
	while (ext < f)
	{
		unsigned int n = strcspn (ext, " ");
		if ((name_ext.size() == n) && (name_ext == string(ext)))
			return true;
		ext += (n + 1);
	}
	return false;
}

void VideoPlugin::SetOption(const string &/*optionName*/, bool /*val*/)
{
}
