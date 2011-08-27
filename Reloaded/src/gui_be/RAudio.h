/**
 * Reloaded, an Amstrad CPC emulator
 * Copyright (C) 2011  cpcsdk crew
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __RAUDIO_H__
#define __RAUDIO_H__

#include "audioPlugin.h"

#include <PushGameSound.h>
#include <GameSoundDefs.h>

class BeAudioPlugin : public AudioPlugin
{
    public:
        BeAudioPlugin() {}
        int init(t_CPC& cpc, t_PSG& psg)
		{
			gs_audio_format format;
			format.frame_rate = cpc.snd_playback_rate;
			format.channel_count = cpc.snd_stereo ? 2 : 1;
			format.format = gs_audio_format::B_GS_S16;
			switch(cpc.snd_bits)
			{
				case 8:
					format.format = gs_audio_format::B_GS_U8;
					break;
				case 16:
					format.format = gs_audio_format::B_GS_S16;
					break;
				case 32:
					format.format = gs_audio_format::B_GS_S32;
					break;
				default:
					WarningLogMessage("Wrong sound bits count in config. Falling back to 16-bits audio.");	
			}
			format.buffer_size = 0; // auto choose
			soundOutput = new BPushGameSound(1024, &format);

			if (soundOutput->InitCheck() != B_OK)
			{
				ErrorLogMessage("BPushGameSound init failed !");
				return -1;
			}

			status_t sta = soundOutput->LockForCyclic((void**)&outBuf, &outSize);

			if (sta == BPushGameSound::lock_failed) {
				ErrorLogMessage("unable to lock BPushGameSound sound buffer");
				return -2;
			}
			return 0;
		}

        void shutdown()
		{
			soundOutput->UnlockCyclic;
			delete soundOutput;
			soundOutput = NULL;
		}
		
        int update() {return 0;}
        void pause() {}
        void resume() {}
        uint8_t* getBuffer()
        {
        	if (++curWPos >= outSize)
        		curWPos = 0;
        	return outBuf + curWPos;
        }
	private:
		BPushGameSound* soundOutput;
		uint8_t* outBuf;
		size_t curWPos;
		size_t outSize;
};

#endif
