// 
// 
// 

#include "Engine.h"
#include "LooperChanel.h"

// Load drivers


String songs[50];
uint8_t SONG_COUNT = 0;
uint8_t _currentSong = 0;
uint8_t _lastViewMode = 128;


//BaseSettings* _currenctSettings = &_songSettings.mixer.master;
/*
void EngineClass::updateModeLinks()
{
	HardwareCore.resetEncoders();
	DisplayCore.drawEncoderTitle(0, "", false);
	DisplayCore.drawEncoderTitle(1, "", false);
	DisplayCore.drawEncoderTitle(2, "", false);
	
	switch (_currentMode)
	{
		case EDIT_CHANNEL_MASTER:
		_currenctSettings = &_songSettings.mixer.master;
		DisplayCore.drawEncoderTitle(2, "MASTER", true);
		HardwareCore.setEncoderParam(2, setMasterVolume, "MASTER", 0, 1, 0.01, _songSettings.mixer.master.masterVolume);
		break;
		case EDIT_CHANNEL_WAV:
		
			_currenctSettings = &_songSettings.mixer.wav;
			switch (_songSettings.mixer.wav.editMode)
			{
			case EDIT_CHANNEL_MODE_EQ:

				DisplayCore.drawEncoderTitle(1, "LP FQ", true);
				HardwareCore.setEncoderParam(1, setWavLowpass, "LP FQ", 100, 20000, 50, _songSettings.mixer.wav.frequency);
				break;
			case EDIT_CHANNEL_MODE_BALANCE:

				DisplayCore.drawEncoderTitle(1, "BAL", true);
				HardwareCore.setEncoderParam(1, setWavBalance, "BAL", -1, 1, 0.05, _songSettings.mixer.wav.balance);
				break;
			}
			
		
		DisplayCore.drawEncoderTitle(2, "W VOL", true);
			HardwareCore.setEncoderParam(2, setWavVolume, "W VOL", 0, 1, 0.01, _songSettings.mixer.wav.volume);
			break;
		case EDIT_CHANNEL_LEFT_CHANNEL:
			_currenctSettings = &_songSettings.mixer.leftInput;
			switch (_songSettings.mixer.leftInput.editMode)
			{
			case EDIT_CHANNEL_MODE_EQ:

				DisplayCore.drawEncoderTitle(1, "HP FQ", true);
				HardwareCore.setEncoderParam(1, setLeftInputHighpass, "HP FQ", 100, 20000, 50, _songSettings.mixer.leftInput.frequency);
				break;
			case EDIT_CHANNEL_MODE_BALANCE:

				DisplayCore.drawEncoderTitle(1, "BAL", true);
				HardwareCore.setEncoderParam(1, setLeftInputBalance, "BAL", -1, 1, 0.05, _songSettings.mixer.leftInput.balance);
				break;
			}

			DisplayCore.drawEncoderTitle(2, "L VOL", true);
			HardwareCore.setEncoderParam(2, setLeftInputVolume, "L VOL", 0, 1, 0.01, _songSettings.mixer.leftInput.volume);
			break;
		case EDIT_CHANNEL_RIGHT_CHANNEL:
			_currenctSettings = &_songSettings.mixer.rightInput;
			switch (_songSettings.mixer.rightInput.editMode)
			{
			case EDIT_CHANNEL_MODE_EQ:

				DisplayCore.drawEncoderTitle(1, "HP FQ", true);
				HardwareCore.setEncoderParam(1, setRightInputHighpass, "HP FQ", 100, 20000, 50, _songSettings.mixer.rightInput.frequency);
				break;
			case EDIT_CHANNEL_MODE_BALANCE:

				DisplayCore.drawEncoderTitle(1, "BAL", true);
				HardwareCore.setEncoderParam(1, setRightInputBalance, "BAL", -1, 1, 0.05, _songSettings.mixer.rightInput.balance);
				break;
			}


			DisplayCore.drawEncoderTitle(2, "R VOL", true);
			HardwareCore.setEncoderParam(2, setRightInputVolume, "R VOL", 0, 1, 0.01, _songSettings.mixer.rightInput.volume);
			break;
		case EDIT_CHANNEL_FX_REVERB:
			_currenctSettings = &_songSettings.mixer.fxReverb;
			
			switch (_songSettings.mixer.fxReverb.editMode)
			{
			case EDIT_FX_REVERB_MODE_EQ:
				DisplayCore.drawEncoderTitle(1, "HP FQ", true);
				HardwareCore.setEncoderParam(1, setReverbHighpass, "HP FQ", 100, 20000, 50, _songSettings.mixer.fxReverb.frequency);
				break;
			case EDIT_FX_REVERB_MODE_BALANCE:

				DisplayCore.drawEncoderTitle(1, "BAL", true);
				HardwareCore.setEncoderParam(1, setReverbBalance, "BAL", -1, 1, 0.05, _songSettings.mixer.fxReverb.balance);
				break;
			case EDIT_FX_REVERB_MODE_ROOM:
				DisplayCore.drawEncoderTitle(0, "DAMP", true);
				HardwareCore.setEncoderParam(0, setReverbDamping, "DAMP", 0, 1, 0.01, _songSettings.mixer.fxReverb.damping);
				DisplayCore.drawEncoderTitle(1, "ROOM", true);
				HardwareCore.setEncoderParam(1, setReverbRoomsize, "ROOM", 0, 1, 0.01, _songSettings.mixer.fxReverb.roomsize);
				break;
			}
				
	    	DisplayCore.drawEncoderTitle(2, "REVER", true);
			HardwareCore.setEncoderParam(2, setReverbVolume, "R VOL", 0, 1, 0.01, _songSettings.mixer.fxReverb.volume);
			break;
	}

	


}
*/
JsonObject& EngineClass::saveChannelPart(JsonObject& mixer, String channelName, ChannelSettings& setting)
{
	JsonObject& channel = mixer.createNestedObject(channelName);
	channel["volume"] = setting.volume;
	channel["balance"] = setting.balance;
	channel["frequency"] = setting.frequency;
	channel["q"] = setting.q;
	return channel;
}


void EngineClass::saveChannelPartFxReverb(JsonObject& mixer, String channelName, FxReverbChannelSettings& setting)
{
	JsonObject& channel =  saveChannelPart(mixer, channelName, setting);	
	channel["damping"] = setting.damping;
	channel["roomsize"] = setting.roomsize;	
}

void EngineClass::saveSettings(bool pressed)
{

	if (SD.exists("settings.mxr"))
	{
		SD.remove("settings.mxr");
	}

	StaticJsonBuffer<1000> jsonBuffer;	
	JsonObject& root = jsonBuffer.createObject();
	JsonObject& mixer = root.createNestedObject("mixerSettings");	
	JsonObject& master = mixer.createNestedObject("master");
	master["volume"] = Engine.songSettings.mixer.master.volume;
	
	saveChannelPart(mixer, "wav", Engine.songSettings.mixer.wav);
	saveChannelPart(mixer, "leftInput", Engine.songSettings.mixer.leftInput);
	saveChannelPart(mixer, "rightInput", Engine.songSettings.mixer.rightInput);
	saveChannelPartFxReverb(mixer, "fxReverb", Engine.songSettings.mixer.fxReverb);
	
	/*JsonArray& data = mixer.createNestedArray("data");
	data.add(48.756080);
	data.add(2.302038); */

	// Step 4	
	root.prettyPrintTo(Serial);
	File settings = SD.open("settings.mxr", FILE_WRITE);
	root.prettyPrintTo(settings);
	settings.close();

}

void EngineClass::loadSettings(bool pressed)
{
	//Set default
	Engine.songSettings.currentChannel = EDIT_CHANNEL_MASTER;
	Engine.songSettings.viewMode = VIEW_MODE_MAIN_MIXER;
	Engine.songSettings.mixer.wav.frequency = 12000;
	Engine.songSettings.mixer.wav.q = 0.707f;
	Engine.songSettings.mixer.leftInput.frequency = 100;
	Engine.songSettings.mixer.leftInput.q = 0.707f;
	Engine.songSettings.mixer.rightInput.frequency = 200;
	Engine.songSettings.mixer.rightInput.q = 0.707f;
	Engine.songSettings.mixer.fxReverb.frequency = 300;
	Engine.songSettings.mixer.fxReverb.q = 0.707f;


	if (SD.exists("settings.mxr"))
	{
		SD.remove("settings.mxr");
		return;
	}

	if (!SD.exists("settings.mxr"))
	{
		return;
	}
	
	File settings = SD.open("settings.mxr", FILE_READ);	
	String json = settings.readString(1000);
	Serial.println(json);
	settings.close();
	StaticJsonBuffer<1000> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(json);

	if (!root.success()) {
		Serial.println("parseObject() failed");
		return;   //if parsing failed, this will exit the function and not change the values to 00

	}
	else
	{

		JsonObject& mixer = root["mixerSettings"];
		JsonObject& master = mixer["master"];
		Engine.songSettings.mixer.master.volume = master["volume"];
		JsonObject& wav = mixer["wav"];
		Engine.songSettings.mixer.wav.volume = wav["volume"];
		Engine.songSettings.mixer.wav.frequency = wav["frequency"];
		Engine.songSettings.mixer.wav.q = wav["q"];
		Engine.songSettings.mixer.wav.balance= wav["balance"];

		JsonObject& leftInput = mixer["leftInput"];
		Engine.songSettings.mixer.leftInput.volume = leftInput["volume"];
		Engine.songSettings.mixer.leftInput.frequency = leftInput["frequency"];
		Engine.songSettings.mixer.leftInput.q = leftInput["q"];
		Engine.songSettings.mixer.leftInput.balance = leftInput["balance"];

		JsonObject& rightInput = mixer["rightInput"];
		Engine.songSettings.mixer.rightInput.volume = rightInput["volume"];
		Engine.songSettings.mixer.rightInput.frequency = rightInput["frequency"];
		Engine.songSettings.mixer.rightInput.q = rightInput["q"];
		Engine.songSettings.mixer.rightInput.balance = rightInput["balance"];

		JsonObject& fxReverb = mixer["fxReverb"];
		Engine.songSettings.mixer.fxReverb.volume = fxReverb["volume"];
		Engine.songSettings.mixer.fxReverb.frequency = fxReverb["frequency"];
		Engine.songSettings.mixer.fxReverb.q = fxReverb["q"];
		Engine.songSettings.mixer.fxReverb.balance = fxReverb["balance"];
		Engine.songSettings.mixer.fxReverb.damping = fxReverb["damping"];
		Engine.songSettings.mixer.fxReverb.roomsize = fxReverb["roomsize"];

		Serial.println("Settings loaded");
	}
}

void EngineClass::init()
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

	for (int i = 0; i< SONG_COUNT; i++)
	{
		Serial.println("file: " + songs[i]);
	}


	loadSettings(true);
	AudioCore.setMasterVolume(Engine.songSettings.mixer.master.volume); //todo settings by channel
	AudioCore.setWavVolume(Engine.songSettings.mixer.wav.volume, Engine.songSettings.mixer.wav.balance);
	AudioCore.setWavBiquad(Engine.songSettings.mixer.wav.frequency, Engine.songSettings.mixer.wav.q);
	AudioCore.setLeftInputVolume(Engine.songSettings.mixer.leftInput.volume, Engine.songSettings.mixer.leftInput.balance);
	AudioCore.setLeftInputBiquad(Engine.songSettings.mixer.leftInput.frequency, Engine.songSettings.mixer.leftInput.q);
	AudioCore.setRightInputVolume(Engine.songSettings.mixer.rightInput.volume, Engine.songSettings.mixer.rightInput.balance);
	AudioCore.setRightInputBiquad(Engine.songSettings.mixer.rightInput.frequency, Engine.songSettings.mixer.rightInput.q);
	AudioCore.setReverbVolume(Engine.songSettings.mixer.fxReverb.volume, Engine.songSettings.mixer.fxReverb.balance);
	AudioCore.setReverbBiquad(Engine.songSettings.mixer.fxReverb.frequency, Engine.songSettings.mixer.fxReverb.q);
	AudioCore.setReverbRoom(Engine.songSettings.mixer.fxReverb.damping, Engine.songSettings.mixer.fxReverb.roomsize);
	//updateModeLinks();	

	/*
	HardwareCore.setButtonParam(GREEN, startWavTrack);
	HardwareCore.setButtonParam(BLACK, stopWavTrack);
	HardwareCore.setButtonParam(BROWN, changeWavTrack);
	*/
	HardwareCore.setButtonParam(RED, saveSettings);
	/*
	HardwareCore.setButtonParam(ENCODER2, changeMode);
	HardwareCore.setButtonParam(ENCODER1, changeEditType);
	HardwareCore.setButtonParam(ENCODER0, muteMaster);
	*/
	
}



/*
void EngineClass::muteMaster()
{
	_muteMaster = !_muteMaster;
	DisplayCore.drawMuteMaster(_muteMaster);
	if (_muteMaster)
	{
		AudioCore.setMasterVolume(_songSettings.mixer.master.masterVolume / 4);
	}
	else
	{
		AudioCore.setMasterVolume(_songSettings.mixer.master.masterVolume);
	}
}

void EngineClass::startWavTrack()
{
	if (!AudioCore.wavIsPlaying())
	{
		Serial.print("Start");
		auto song = songs[_currentSong];
		AudioCore.playWav(("/DATA/TRACKS/" + song).c_str());

	}
}

void EngineClass::stopWavTrack()
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

void EngineClass::changeWavTrack()
{
	if (!AudioCore.wavIsPlaying())
	{
		_currentSong = (_currentSong + 1) % SONG_COUNT;
	}
}
*/
/*
void EngineClass::changeMode()
{
	
	_currentMode = (_currentMode + 1) % 5;
	updateModeLinks();
}

void EngineClass::changeEditType()
{
	uint8_t maxMode = 2;
	switch (_currentMode)
	{
	case EDIT_CHANNEL_FX_REVERB:
		maxMode = 3;
		break;
	}
	
	_currenctSettings->editMode = (_currenctSettings->editMode + 1) % maxMode;
	updateModeLinks();
}




void EngineClass::setWavLowpass(int encoder, int value)
{
	_songSettings.mixer.wav.frequency = static_cast<float>(value / 100);
	DisplayCore.drawEncoder(encoder, _songSettings.mixer.wav.frequency, 20000);
	AudioCore.setWavBiquad(_songSettings.mixer.wav.frequency, _songSettings.mixer.wav.q);
}

void EngineClass::setLeftInputHighpass(int encoder, int value)
{
	_songSettings.mixer.leftInput.frequency = static_cast<float>(value / 100);
	DisplayCore.drawEncoder(encoder, _songSettings.mixer.leftInput.frequency, 20000);
	AudioCore.setLeftInputBiquad(_songSettings.mixer.leftInput.frequency, _songSettings.mixer.leftInput.q);
}

void EngineClass::setLeftInputBalance(int encoder, int value)
{
	_songSettings.mixer.leftInput.balance = static_cast<float>(value / 100.0);
	DisplayCore.drawEncoder(encoder, value, 100, true);
	AudioCore.setLeftInputVolume(_songSettings.mixer.leftInput.volume, _songSettings.mixer.leftInput.balance);
}

void EngineClass::setWavBalance(int encoder, int value)
{
	_songSettings.mixer.wav.balance = static_cast<float>(value / 100.0);
	DisplayCore.drawEncoder(encoder, value, 100, true);
	AudioCore.setWavVolume(_songSettings.mixer.wav.volume, _songSettings.mixer.wav.balance);
}


void EngineClass::setRightInputBalance(int encoder, int value)
{
	_songSettings.mixer.rightInput.balance = static_cast<float>(value / 100.0);
	DisplayCore.drawEncoder(encoder, value, 100, true);
	AudioCore.setRightInputVolume(_songSettings.mixer.rightInput.volume, _songSettings.mixer.rightInput.balance);
}

void EngineClass::setReverbBalance(int encoder, int value)
{
	_songSettings.mixer.fxReverb.balance = static_cast<float>(value / 100.0);
	DisplayCore.drawEncoder(encoder, value, 100, true);
	AudioCore.setReverbVolume(_songSettings.mixer.fxReverb.volume, _songSettings.mixer.fxReverb.balance);
}

void EngineClass::setReverbDamping(int encoder, int value)
{
	_songSettings.mixer.fxReverb.damping = static_cast<float>(value / 100.0);
	DisplayCore.drawEncoder(encoder, value, 100);
	AudioCore.setReverbRoom(_songSettings.mixer.fxReverb.damping, _songSettings.mixer.fxReverb.roomsize);
}

void EngineClass::setReverbRoomsize(int encoder, int value)
{
	_songSettings.mixer.fxReverb.roomsize = static_cast<float>(value / 100.0);
	DisplayCore.drawEncoder(encoder, value, 100);
	AudioCore.setReverbRoom(_songSettings.mixer.fxReverb.damping, _songSettings.mixer.fxReverb.roomsize);
}


void EngineClass::setRightInputHighpass(int encoder, int value)
{
	_songSettings.mixer.rightInput.frequency = static_cast<float>(value / 100);
	DisplayCore.drawEncoder(encoder, _songSettings.mixer.rightInput.frequency, 20000);
	AudioCore.setRightInputBiquad(_songSettings.mixer.rightInput.frequency, _songSettings.mixer.rightInput.q);
}

void EngineClass::setReverbHighpass(int encoder, int value)
{
	_songSettings.mixer.fxReverb.frequency = static_cast<float>(value / 100);
	DisplayCore.drawEncoder(encoder, _songSettings.mixer.fxReverb.frequency, 20000);
	AudioCore.setReverbBiquad(_songSettings.mixer.fxReverb.frequency, _songSettings.mixer.fxReverb.q);
}

void EngineClass::setMasterVolume(int encoder, int value)
{	
	_songSettings.mixer.master.masterVolume = static_cast<float>(value) / 100;
	DisplayCore.drawEncoder(encoder, value, 100);	
	if (_muteMaster)
	{
		AudioCore.setMasterVolume(_songSettings.mixer.master.masterVolume / 4);
	}
	else
	{
		AudioCore.setMasterVolume(_songSettings.mixer.master.masterVolume);
	}
}


void EngineClass::setWavVolume(int encoder, int value)
{
	_songSettings.mixer.wav.volume = static_cast<float>(value) / 100;
	DisplayCore.drawEncoder(encoder, value, 100);
	AudioCore.setWavVolume(_songSettings.mixer.wav.volume, _songSettings.mixer.wav.balance);
}

void EngineClass::setLeftInputVolume(int encoder, int value)
{
	_songSettings.mixer.leftInput.volume = static_cast<float>(value) / 100;
	DisplayCore.drawEncoder(encoder, value, 100);
	AudioCore.setLeftInputVolume(_songSettings.mixer.leftInput.volume, _songSettings.mixer.leftInput.balance);
}

void EngineClass::setRightInputVolume(int encoder, int value)
{
	_songSettings.mixer.rightInput.volume = static_cast<float>(value) / 100;
	DisplayCore.drawEncoder(encoder, value, 100);
	AudioCore.setRightInputVolume(_songSettings.mixer.rightInput.volume, _songSettings.mixer.rightInput.balance);
}

void EngineClass::setReverbVolume(int encoder, int value)
{
	_songSettings.mixer.fxReverb.volume = static_cast<float>(value) / 100;
	DisplayCore.drawEncoder(encoder, value, 100);
	AudioCore.setReverbVolume(_songSettings.mixer.fxReverb.volume, _songSettings.mixer.fxReverb.balance);
}

*/

void EngineClass::drawTopPanel()
{
	DisplayCore.drawText(songSettings.name, 8, 3);
}

void EngineClass::update()
{
	if (_hardwareTimer >= 100) {
		_hardwareTimer = 0;
		if (_tickCounter++ >= 10)
		{
			_tickCounter = 0;
			auto usageCPU = AudioProcessorUsageMax();
			uint16_t usageMemory = AudioMemoryUsageMax();
			AudioProcessorUsageMaxReset();
			AudioMemoryUsageMaxReset();
			DisplayCore.drawUsage(usageCPU, usageMemory);
		}
		
		HardwareCore.update(); //Обновить состояние кнопок
		bool needUpdatePanel = !isValidScreen; //Требуется обновить верхнюю панель
		if (_lastViewMode != songSettings.viewMode)
		{
			switch (songSettings.viewMode)
			{
			case VIEW_MODE_MAIN_MIXER:
				Mixer.onShow();
				break;
			case VIEW_MODE_OPEN_SONG:
				SongLoader.onShow();
				break;
			case VIEW_MODE_EDIT_CHANNEL:
				LooperChanel.onShow();
				break;
			default:
				
				break;
			}
			_lastViewMode = songSettings.viewMode;
			needUpdatePanel = true;
		}


	
		switch (songSettings.viewMode)
		{
		case VIEW_MODE_MAIN_MIXER:
			Mixer.handle();
			break;
		case VIEW_MODE_OPEN_SONG:
			SongLoader.handle();
			break;
		case VIEW_MODE_EDIT_CHANNEL:
			LooperChanel.handle();
			break;
		default:
			DisplayCore.clearAll();
			DisplayCore.drawText("Not implemented " + songSettings.viewMode, 3 , 3);
			break;
		}

		//	Serial.print(seqButtonRead(24));
		//	Serial.println("----------");

		if (needUpdatePanel)
		{
			drawTopPanel();
		}


	}
	//AudioCore.continueRecording();
}

void EngineClass::switchWindow(current_view_mode current_view_mode)
{	
	songSettings.viewMode = current_view_mode;	
	DisplayCore.clearAll();	
	HardwareCore.resetEncoders();
	HardwareCore.resetButtons();
	isValidScreen = false;
}


EngineClass Engine;

