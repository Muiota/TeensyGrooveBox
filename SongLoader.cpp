// 
// 
// 

#include "SongLoader.h"
#include "HardwareCore.h"
#include "DisplayCore.h"
#include "Engine.h"



const String filePathPrefix = "/DATA/SONGS_";
const String newAlias = "NEW";

String loadedSongs[250];
uint8_t songCount = 0;
song_load_part selectedPart = SONGS_PART_A;
uint8_t lastPage = 0;
uint8_t selectedSong = 0;
uint8_t loadedSong = -1;

bool isCreatingSong;
bool isRewriting;
char currentSongName[8] = { 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A' };
uint8_t currentSongNameLength = 8;
uint8_t currentSongNameIndex = 0;
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
		String songName = loadedSongs[i];
		String itemString = (i == 0 ? "***" : String(1000 + i).substring(1, 4)) + " " + songName.substring(0, songName.length() - 4);

		uint16_t color;
		if (i == selectedSong)
		{
			if (i == 0)
			{
				color = isCreatingSong ? ILI9341_WHITE : ILI9341_CYAN;
			} else
			{
				color = SELECTED_COLOR_OPACITY;
			}
		} else if (i == loadedSong)
		{
			color = ILI9341_WHITE;
		} else if (i == 0)
		{
			color = ILI9341_DARKCYAN;
		} else
		{
			color = UNSELECTED_COLOR_OPACITY;
		}
	
		DisplayCore.drawTextOpacity(itemString, 16, 30 + (i - start) * 16, color);
	}
	if (lastPage != page)
	{
		lastPage = page;
		Engine.isValidScreen = false;
	}
}

void SongLoaderClass::drawNewSongName()
{
	DisplayCore.drawFileloadPanel(true,selectedPart);
	uint16_t x = 156;
	DisplayCore.setCursor(136, 150);
	
		DisplayCore.drawColoredChar('<',ILI9341_PURPLE);		
		DisplayCore.drawColoredChar(' ', ILI9341_BLUE);
	for (uint8_t i = 0; i < currentSongNameLength; i++)
	{
		DisplayCore.drawColoredChar(currentSongName[i], currentSongNameIndex == i ? ILI9341_YELLOW : ILI9341_PINK) ;
	}	
}

void SongLoaderClass::drawButtons()
{
	song_load_buttons type;
	if (selectedSong == 0)
	{
		if (isCreatingSong)
		{ type = song_load_buttons_yes_no; }
		else { type = song_load_buttons_new; }
		
	} else
	{
		type = song_load_buttons_edit;
	}

	DisplayCore.drawFileloadButtons(type);
}

void SongLoaderClass::handle()
{
	bool _fullRedraw = false;
	if (!Engine.isValidScreen)
	{
		DisplayCore.drawFileListBackground();
		DisplayCore.drawFileLoadBackground();
		DisplayCore.drawFileloadPanel(false, selectedPart);
		_fullRedraw = true;
		Engine.isValidScreen = true;
	}


	if (_fullRedraw)
	{
		drawTexts();
		drawButtons();
	}
}

void SongLoaderClass::onShow()
{
	isCreatingSong = false;
	isRewriting = false;
	Engine.assignDefaultButtons();
	HardwareCore.setButtonParam(BLACK, switchPart);
	HardwareCore.setButtonParam(ENCODER0, pressEncoder0);
	HardwareCore.setButtonParam(ENCODER1, pressEncoder1);
	loadSongs();
}


void SongLoaderClass::switchPart(bool pressed)
{
	if (pressed)
	{
		isCreatingSong = false;
		isRewriting = false;
		selectedPart = (song_load_part)((selectedPart + 1) % 8);
		loadSongs();
		Engine.isValidScreen = false;
	}
}



void SongLoaderClass::pressEncoder0(bool pressed)
{
	if (pressed)
	{
		if (selectedSong == 0)
		{
			if (!isCreatingSong)
			{
				isCreatingSong = true;
				drawButtons();
				drawTexts();
				HardwareCore.setEncoderParam(2, selectSongLength, "selectSongLength", 3, 8, 1, currentSongNameLength);
				drawNewSongName();
			}
			else
			{
				saveCurrentSongToFile();
				//file create
			}
		}
		else if (selectedSong > 0 && selectedSong < songCount)
		{
			saveSettings();
			loadSelectedSong(selectedSong);
			Engine.switchWindow(VIEW_MODE_MAIN_MIXER);
		}
	}
}

void SongLoaderClass::pressEncoder1(bool pressed)
{
	if (pressed)
	{
		if (isCreatingSong)
		{
			isCreatingSong = false;
			isRewriting = false;
			loadSongs();
			DisplayCore.drawFileloadPanel(false, selectedPart);
			drawButtons();
			drawTexts();
		}		
	}
}

void SongLoaderClass::selectSongLength(int encoder, int value)
{
	if (!isCreatingSong)
		return;
	currentSongNameLength = static_cast<int>(value / 100);	
	drawNewSongName();
	if (currentSongNameLength <= currentSongNameIndex)
	{
		currentSongNameIndex = currentSongNameLength - 1;
	}
	HardwareCore.setEncoderParam(1, selectSongIndex, "selectSongIndex", 0, currentSongNameLength - 1, 1, currentSongNameIndex);
}

void SongLoaderClass::selectSongIndex(int encoder, int value)
{
	if (!isCreatingSong)
		return;
	currentSongNameIndex = static_cast<int>(value / 100);	
	drawNewSongName();
	HardwareCore.setEncoderParam(0, selectSongSymbol, "selectSongSymbol", 65, 90, 1, currentSongName[currentSongNameIndex]);
}

void SongLoaderClass::selectSongSymbol(int encoder, int value)
{
	if (!isCreatingSong)
		return;
	currentSongName[currentSongNameIndex] = static_cast<int>(value / 100);
	drawNewSongName();	
}

void SongLoaderClass::selectSong(int encoder, int value)
{
	bool needRedraw = selectedSong == 0;
	selectedSong = - static_cast<int>(value / 100);
	needRedraw = needRedraw || selectedSong == 0;
	drawTexts();
	if (needRedraw)
	{
		drawButtons();
	}
}

StringSumHelper getCurrentLoadPath()
{
	return (filePathPrefix + char(selectedPart + 65) + "/");
}

void SongLoaderClass::loadSongs()
{	
	auto concatenated = getCurrentLoadPath();
	Serial.println("Load loadedSongs from "+ concatenated);		
	const char* filepath = concatenated.c_str();
	if (!SD.exists(filepath))
	{
		SD.mkdir(filepath);
	}
	songCount = 0;

	loadedSongs[songCount] = newAlias;
	songCount++;
	loadedSong = -1;
	File rootdir = SD.open(filepath);
	while (true)
	{
		// open a file from the SD card
		File f = rootdir.openNextFile();
		if (!f) break;
		loadedSongs[songCount] = f.name();
		String path = filepath + String(f.name());
		Serial.println(path);
		Serial.println(Engine.songSettings.path);
		if (path.equals(Engine.songSettings.path))
		{
			loadedSong = songCount;
		}
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

void SongLoaderClass::saveCurrentSongToFile()
{
	auto concatenated = getCurrentLoadPath();
	String songName = "";
	for (uint8_t i = 0; i < currentSongNameLength; i++)
	{
		songName = songName + currentSongName[i];
	}	
	concatenated = concatenated + songName + ".sng";
	Serial.println("Save song to " + concatenated);
	const char* filepath = concatenated.c_str();
	if (SD.exists(filepath))
	{
		if (isRewriting)
		{
			isRewriting = false;
			SD.remove(filepath);
		} else
		{
			isRewriting = true;
			DisplayCore.drawTextOpacity("Do you want to overwrite song?", 132, 180, ILI9341_RED);
			return;
		}
	}
	

	StaticJsonBuffer<65536> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();
	JsonObject& mixer = root.createNestedObject("mixerSettings");
	JsonObject& master = mixer.createNestedObject("master");
	master["volume"] = Engine.songSettings.mixer.master.volume;

	//saveChannelPart(mixer, "looper", Engine.songSettings.mixer.looper);
	//saveChannelPart(mixer, "leftInput", Engine.songSettings.mixer.leftInput);
	//saveChannelPart(mixer, "rightInput", Engine.songSettings.mixer.rightInput);
	//saveChannelPartFxReverb(mixer, "fxReverb", Engine.songSettings.mixer.fxReverb);

	/*JsonArray& data = mixer.createNestedArray("data");
	data.add(48.756080);
	data.add(2.302038); */

	// Step 4	
	root.prettyPrintTo(Serial);
	File settings = SD.open(filepath, FILE_WRITE);
	root.prettyPrintTo(settings);
	settings.close();

	Engine.songSettings.path = filepath;
	Engine.songSettings.name = songName;
	loadSongs();
	Engine.isValidScreen = false;
}

void SongLoaderClass::loadSelectedSong(int selected_song)
{
	auto loaded_song = loadedSongs[selected_song];
	auto concatenated = (getCurrentLoadPath()+ loaded_song).c_str();
	
	if (SD.exists(concatenated))
	{
		Engine.songSettings.path = concatenated;
		Engine.songSettings.name = loaded_song.substring(0, loaded_song.length() - 4);
	}
	loadSongs();
	Engine.isValidScreen = false;
}


