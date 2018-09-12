// 
// 
// 

#include "SongLoader.h"
#include "HardwareCore.h"
#include "DisplayCore.h"
#include "Engine.h"



const String filePathPrefix = "/DATA/SONGS_";

String loadedSongs[250];
uint8_t songCount = 0;
song_load_part selectedPart = SONGS_PART_A;
uint8_t lastPage = 0;
uint8_t selectedSong = 0;
uint16_t SELECTED_COLOR_OPACITY = 0xF487;
uint16_t UNSELECTED_COLOR_OPACITY = 0x4A28;

void SongLoaderClass::drawTexts()
{
	uint8_t page = (selectedSong) / 13;
	uint8_t start = page * 13;
	uint8_t end = start + 13;
	if (end > songCount)
	{
		end = songCount;
	}
	for (uint8_t i = start; i < end; i++) //songCount
	{
		auto songName = loadedSongs[i];
		auto itemString = String(1000 + i).substring(1, 4) + " " + songName.substring(0, songName.length() - 4);


		auto color = (i == selectedSong ? SELECTED_COLOR_OPACITY : (i == 5 ? ILI9341_WHITE : UNSELECTED_COLOR_OPACITY));

		DisplayCore.drawTextOpacity(itemString, 16, 30 + (i - start) * 16, color);
	}
	if (lastPage != page)
	{
		lastPage = page;
		Engine.isValidScreen = false;
	}
}

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
		drawTexts();
	}
}

void SongLoaderClass::onShow()
{
	HardwareCore.setButtonParam(BROWN, backToMixer);
	HardwareCore.setButtonParam(ENCODER0, loadSelectedSong);
	loadSongs();
}

void SongLoaderClass::backToMixer(bool pressed)
{
	if (pressed)
	{
		Engine.switchWindow(VIEW_MODE_MAIN_MIXER);
	}
}

void SongLoaderClass::loadSelectedSong(bool pressed)
{
	if (pressed && selectedSong >= 0 && selectedSong < songCount)
	{
		saveSettings();
		Engine.switchWindow(VIEW_MODE_MAIN_MIXER);
	}
}


void SongLoaderClass::selectSong(int encoder, int value)
{
	selectedSong = - static_cast<int>(value / 100);
	drawTexts();
}

void SongLoaderClass::loadSongs()
{	
	auto concatenated = (filePathPrefix + String(selectedPart)+ "/");
	Serial.println("Load loadedSongs from "+ concatenated);		
	const char* filepath = concatenated.c_str();
	if (!SD.exists(filepath))
	{
		SD.mkdir(filepath);
	}
	songCount = 0;
	File rootdir = SD.open(filepath);
	while (true)
	{
		// open a file from the SD card
		File f = rootdir.openNextFile();
		if (!f) break;
		loadedSongs[songCount] = f.name();
		songCount++;
		f.close();
	}
	rootdir.close();

	for (uint8_t i = 0; i < songCount; i++)
	{
		Serial.println("song: " + loadedSongs[i]);
	}

	if (songCount > 0)
	{
		HardwareCore.setEncoderParam(0, selectSong, "selector", -songCount + 1, 0, 1, selectedSong);
	}
}

void SongLoaderClass::saveSettings()
{
	if (SD.exists("settings.jsn"))
	{
		SD.remove("settings.jsn");
	}

	StaticJsonBuffer<1000> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();
	JsonObject& song = root.createNestedObject("song");

	song["selectedSong"] = loadedSongs[selectedSong];
	song["selectedPart"] = String(selectedPart);

	root.prettyPrintTo(Serial);
	File settings = SD.open("settings.jsn", FILE_WRITE);
	root.prettyPrintTo(settings);
	settings.close();
}

