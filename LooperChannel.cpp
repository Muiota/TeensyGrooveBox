
#include "LooperChannel.h"
#include "DisplayCore.h"
#include "HardwareCore.h"
#include "Engine.h"

static uint8_t left_tape_frame = 0;
static uint8_t right_tape_frame = 5;
String songs[64];
uint8_t WAVES_COUNT = 0;
uint8_t _lastWavPage = 0;
uint8_t _currentWave = 0;


void LooperChannelClass::handle()
{
	switch (Engine.songSettings.currentView)
	{
	case EDIT_CHANNEL_MODE_MAIN: 
		if (!Engine.isValidScreen)
		{
			DisplayCore.disaplaySubMenu();
			DisplayCore.disaplayLooperTape(EDIT_CHANNEL_LOOPER);
			Engine.isValidScreen = true;
		}
		left_tape_frame = (left_tape_frame + 1) % 10;
		right_tape_frame = (right_tape_frame + 1) % 10;
		DisplayCore.drawTapeFrame(left_tape_frame, right_tape_frame);
		
		break;
	case EDIT_CHANNEL_MODE_SETTINGS: 
		if (!Engine.isValidScreen)
		{
			DisplayCore.drawFileListBackground();		
			drawTexts();
			Engine.isValidScreen = true;
		}
	
		break;
	}
	
}


void LooperChannelClass::loadWaves()
{
	if (WAVES_COUNT == 0)
	{

		songs[WAVES_COUNT] = "NONE.WAV";
		WAVES_COUNT++;

		Serial.println("Load songs");
		File rootdir = SD.open("/DATA/TRACKS/");
		while (1) {
			// open a file from the SD card
			File f = rootdir.openNextFile();
			if (!f) break;
			songs[WAVES_COUNT] = f.name();
			WAVES_COUNT++;
			f.close();
		}
		rootdir.close();

		for (int i = 0; i < WAVES_COUNT; i++)
		{
			Serial.println("file: " + songs[i]);
		}
	}
}


void LooperChannelClass::onShow()
{
	Engine.assignDefaultButtons();
	loadWaves();

	switch (Engine.songSettings.currentView)
	{
	case EDIT_CHANNEL_MODE_MAIN:
	

		break;
	case EDIT_CHANNEL_MODE_SETTINGS:
		if (WAVES_COUNT > 0)
		{
			HardwareCore.setEncoderParam(0, selectSong, "selector", -WAVES_COUNT + 1, 0, 1, _currentWave);
		}
		break;
	}

	//HardwareCore.setButtonParam(BTN_ENCODER0, switchToSongLoader);
}

void LooperChannelClass::selectSong(int encoder, int value)
{
	bool needRedraw = _currentWave == 0;
	_currentWave = -static_cast<int>(value / 100);
	needRedraw = needRedraw || _currentWave == 0;
	drawTexts();
	if (needRedraw)
	{
		drawTexts();
	}
}



void LooperChannelClass::updateStatus()
{
	if (Engine.songSettings.isPlaying)
	{
		if (!AudioCore.wavIsPlaying() && _currentWave > 0)
		{
			loadWaves();
			Serial.print("Start");
			auto song = songs[_currentWave];
			AudioCore.playWav(("/DATA/TRACKS/" + song).c_str());
		}
	}
	else
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
}


void LooperChannelClass::drawTexts()
{
	uint8_t page = (_currentWave) / 13;
	uint8_t start = page * 13;
	uint8_t end = start + 13;
	if (end > WAVES_COUNT)
	{
		end = WAVES_COUNT;
	}
	for (uint8_t i = start; i < end; i++) //songCount
	{
		String songName = songs[i];
		String itemString = (String(1000 + i).substring(1, 4)) + " " + songName.substring(0, songName.length() - 4);

		uint16_t color;

		 if (i == _currentWave)
		{
			color = DisplayCore.MAIN_COLOR;
		}
		else if (i == 0)
		{
			color = DisplayCore.NONE_COLOR_WAV;
		}
		else
		{
			color = DisplayCore.UNSELECTED_COLOR_WAV;
		}
		 
		DisplayCore.drawTextOpacity(itemString, 16, 30 + (i - start) * 16, color);
	}
	if (_lastWavPage != page)
	{
		_lastWavPage = page;
		Engine.isValidScreen = false;
	}
}


