
#include "LooperChanel.h"
#include "DisplayCore.h"
#include "HardwareCore.h"
#include "Engine.h"

static uint8_t left_tape_frame = 0;
static uint8_t right_tape_frame = 5;
String songs[50];
uint8_t SONG_COUNT = 0;
uint8_t _currentSong = 0;

void LooperChanelClass::handle()
{
	if (!Engine.isValidScreen)
	{
		DisplayCore.disaplaySubMenu();
		DisplayCore.disaplayLooperTape(EDIT_CHANNEL_LOOPER);
		Engine.isValidScreen = true;
	}
	left_tape_frame = (left_tape_frame + 1) % 10;
	right_tape_frame = (right_tape_frame + 1) % 10;
	DisplayCore.drawTapeFrame(left_tape_frame, right_tape_frame);
}


void LooperChanelClass::loadWaves()
{
	if (SONG_COUNT == 0)
	{
		Serial.println("Load songs");
		File rootdir = SD.open("/DATA/TRACKS/");
		while (1) {
			// open a file from the SD card
			File f = rootdir.openNextFile();
			if (!f) break;
			songs[SONG_COUNT] = f.name();
			SONG_COUNT++;
			f.close();
		}
		rootdir.close();

		for (int i = 0; i < SONG_COUNT; i++)
		{
			Serial.println("file: " + songs[i]);
		}
	}
}


void LooperChanelClass::onShow()
{
	HardwareCore.setButtonParam(BROWN, backToMixer);
	loadWaves();
	//HardwareCore.setButtonParam(ENCODER0, switchToSongLoader);
}

void LooperChanelClass::backToMixer(bool pressed)
{
	if (pressed)
	{
		Engine.switchWindow(VIEW_MODE_MAIN_MIXER);
	}
}

void LooperChanelClass::startTrack()
{
	if (!AudioCore.wavIsPlaying())
	{
		loadWaves();
		Serial.print("Start");
		auto song = songs[_currentSong];
		AudioCore.playWav(("/DATA/TRACKS/" + song).c_str());
	}
}

void LooperChanelClass::stopTrack()
{
	if (AudioCore.wavIsPlaying())
	{
		Serial.print("Stop");
		AudioCore.stopWav();
		//		switch (_recordStatus)
		///	{
		//case RECORD_STATUS_RECORD:
		//	AudioCore.stopRecording();
		//			break;
		//	case RECORD_STATUS_PLAY:
		//		AudioCore.stopLastRecorderInputRaw();
		//		break;
		//	}
	}
}



void LooperChanelClass::changeWavTrack()
{
	if (!AudioCore.wavIsPlaying())
	{
		_currentSong = (_currentSong + 1) % SONG_COUNT;
	}
}


