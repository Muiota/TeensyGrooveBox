// 
// 
// 

#include "SongLoader.h"
#include "HardwareCore.h"
#include "DisplayCore.h"
#include "Engine.h"


const char * filepathA = "/DATA/TRACKS/";  // "/DATA/SONGS_A/";
const char * filepathB = "/DATA/SONGS_B/";
const char * filepathC = "/DATA/SONGS_C/";
const char * filepathD = "/DATA/SONGS_D/";
String loadedSongs[250];
uint8_t songCount = 0;
uint8_t selectedSong = 0;
uint16_t MAIN_COLOR_OPACITY[4] = { 0xF487, 0xDD03,0xBCA7,0x9C2B };
uint16_t LIGHT_PANEL_COLOR_OPACITY[4] = {0x7BCF,0x630B,0x4A28, 0x3164};

void SongLoaderClass::handle()
{
	bool _fullRedraw = false;
	if (!Engine.isValidScreen)
	{
		DisplayCore.drawFileloadBackground();
		_fullRedraw = true;
		Engine.isValidScreen = true;
	}


	if (_fullRedraw)
	{
		for (int i = 0; i < 12; i++) //songCount
		{
			auto songName = loadedSongs[i];
			auto itemString = String(1000 + i).substring(1, 4) + " " + songName.substring(0, songName.length() - 4);


			auto color = (i== selectedSong ? MAIN_COLOR_OPACITY[0] : LIGHT_PANEL_COLOR_OPACITY[0]);

			DisplayCore.drawTextOpacity(itemString, 20, 36 + i * 16, color);
		}
	}

	
	

}

void SongLoaderClass::onShow()
{
	HardwareCore.setButtonParam(BROWN, backToMixer);
	loadSongs();
}

void SongLoaderClass::backToMixer(bool pressed)
{
	if (pressed)
	{
		Engine.switchWindow(VIEW_MODE_MAIN_MIXER);
	}
}

void SongLoaderClass::loadSongs()
{
	Serial.println("Load loadedSongs");
	auto filepath = filepathA;
	if (!SD.exists(filepath))
	{
		SD.mkdir(filepath);
	}
	songCount = 0;
	File rootdir = SD.open(filepath);
	while (1) {
		// open a file from the SD card
		File f = rootdir.openNextFile();
		if (!f) break;
		loadedSongs[songCount] = f.name();
		songCount++;
		f.close();
	}
	rootdir.close();	

	for (int i = 0; i< songCount; i++)
	{
		Serial.println("song: " + loadedSongs[i]);
	}

}