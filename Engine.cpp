// 
// 
// 

#include "Engine.h"
#include "LooperChannel.h"
#include "Equalizer.h"
#include "DrumChannel.h"

// Load drivers



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
		
			_currenctSettings = &_songSettings.mixer.looper;
			switch (_songSettings.mixer.looper.editMode)
			{
			case EDIT_CHANNEL_MODE_EQ:

				DisplayCore.drawEncoderTitle(1, "LP FQ", true);
				HardwareCore.setEncoderParam(1, setWavLowpass, "LP FQ", 100, 20000, 50, _songSettings.mixer.looper.frequency);
				break;
			case EDIT_CHANNEL_MODE_BALANCE:

				DisplayCore.drawEncoderTitle(1, "BAL", true);
				HardwareCore.setEncoderParam(1, setWavBalance, "BAL", -1, 1, 0.05, _songSettings.mixer.looper.balance);
				break;
			}
			
		
		DisplayCore.drawEncoderTitle(2, "W VOL", true);
			HardwareCore.setEncoderParam(2, setLooperVolume, "W VOL", 0, 1, 0.01, _songSettings.mixer.looper.volume);
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
byte testbit1 = 0x01;

void EngineClass::spiShotsHandler()
{
	if (songSettings.isPlaying)
	{
		if (_hardwareTimer >= _nextMidiTick) {


			long shift = 0;
			songSettings.pattern.isAccent = songSettings.pattern.currentStep & testbit1;
			if (songSettings.pattern.shuffle != 0)
			{
				if (songSettings.pattern.isAccent) //todo low bit check optimize
				{
					shift = songSettings.pattern.shuffle;					
				}
				else
				{
					shift = -songSettings.pattern.shuffle;					
				}
			}

			_nextMidiTick = _hardwareTimer + 150+ shift;
			volatile uint8_t proposed = songSettings.pattern.currentStep + 1;
			if (proposed >= 16)
			{
				proposed = proposed - 16;
			}
			songSettings.pattern.currentStep = proposed;
			HardwareCore.setRingLedColor(songSettings.pattern.currentStep, static_cast<int>(12)); //todo
			DrumChannel.midiUpdate();
		}
	}
	else
	{
		if (songSettings.pattern.currentStep < 15)
		{
			songSettings.pattern.currentStep = 15;
		}
	}
}


JsonObject& EngineClass::saveChannelPart(JsonObject& mixer, String channelName, ChannelSettings& setting)
{
	JsonObject& channel = mixer.createNestedObject(channelName);
	channel["volume"] = setting.volume;
	channel["balance"] = setting.balance;
	channel["frequency"] = setting.eqFc;
	channel["q"] = setting.eqQ;
	return channel;
}


void EngineClass::saveChannelPartFxReverb(JsonObject& mixer, String channelName, Efeect1Settings& setting)
{
	JsonObject& channel =  saveChannelPart(mixer, channelName, setting);	
	channel["damping"] = setting.damping;
	channel["roomsize"] = setting.roomsize;	
}

void EngineClass::startTrack(bool pressed)
{	
	songSettings.isPlaying = true;
	LooperChannel.updateStatus();
	DrumChannel.updateStatus();
}

void EngineClass::stopTrack(bool pressed)
{	
	songSettings.isPlaying = false;
	LooperChannel.updateStatus();
	DrumChannel.updateStatus();
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
	
	saveChannelPart(mixer, "looper", Engine.songSettings.mixer.looper);
	saveChannelPart(mixer, "leftInput", Engine.songSettings.mixer.leftInput);
	saveChannelPart(mixer, "rightInput", Engine.songSettings.mixer.rightInput);
	saveChannelPartFxReverb(mixer, "fxReverb", Engine.songSettings.mixer.effect1);
	
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
	Engine.songSettings.mixer.looper.eqFc = 12000;
	Engine.songSettings.mixer.looper.eqQ = 0.707f;
	Engine.songSettings.mixer.leftInput.eqFc = 100;
	Engine.songSettings.mixer.leftInput.eqQ = 0.707f;
	Engine.songSettings.mixer.rightInput.eqFc = 200;
	Engine.songSettings.mixer.rightInput.eqQ = 0.707f;
	Engine.songSettings.mixer.effect1.eqFc = 300;
	Engine.songSettings.mixer.effect1.eqQ = 0.707f;


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
		JsonObject& wav = mixer["looper"];
		Engine.songSettings.mixer.looper.volume = wav["volume"];
		Engine.songSettings.mixer.looper.eqFc = wav["frequency"];
		Engine.songSettings.mixer.looper.eqQ = wav["q"];
		Engine.songSettings.mixer.looper.balance= wav["balance"];

		JsonObject& leftInput = mixer["leftInput"];
		Engine.songSettings.mixer.leftInput.volume = leftInput["volume"];
		Engine.songSettings.mixer.leftInput.eqFc = leftInput["frequency"];
		Engine.songSettings.mixer.leftInput.eqQ = leftInput["q"];
		Engine.songSettings.mixer.leftInput.balance = leftInput["balance"];

		JsonObject& rightInput = mixer["rightInput"];
		Engine.songSettings.mixer.rightInput.volume = rightInput["volume"];
		Engine.songSettings.mixer.rightInput.eqFc = rightInput["frequency"];
		Engine.songSettings.mixer.rightInput.eqQ = rightInput["q"];
		Engine.songSettings.mixer.rightInput.balance = rightInput["balance"];

		JsonObject& fxReverb = mixer["fxReverb"];
		Engine.songSettings.mixer.effect1.volume = fxReverb["volume"];
		Engine.songSettings.mixer.effect1.eqFc = fxReverb["frequency"];
		Engine.songSettings.mixer.effect1.eqQ = fxReverb["q"];
		Engine.songSettings.mixer.effect1.balance = fxReverb["balance"];
		Engine.songSettings.mixer.effect1.damping = fxReverb["damping"];
		Engine.songSettings.mixer.effect1.roomsize = fxReverb["roomsize"];

		Serial.println("Settings loaded");
	}
}


void EngineClass::calcBiquad(ChannelSettings& setting, int *coef)
{
	AudioFilterBiquad::calcBiquad(setting.eqType,
		setting.eqFc, setting.eqGain, setting.eqSlope, coef);
}

float eraseBytesPerSecond(const unsigned char *id) {
	if (id[0] == 0x20) return 152000.0; // Micron
	if (id[0] == 0x01) return 500000.0; // Spansion
	if (id[0] == 0xEF) return 419430.0; // Winbond
	if (id[0] == 0xC2) return 279620.0; // Macronix
	return 320000.0; // guess?
}

void EngineClass::initSerialFlashToDo()
{
	unsigned long startMillis = millis();
	unsigned char id[5];
	SerialFlash.readID(id);
	unsigned long size = SerialFlash.capacity(id);

	if (size > 0) {
		Serial.print("Flash Memory has ");
		Serial.print(size);
		Serial.println(" bytes.");
		Serial.println("Erasing ALL Flash Memory:");
		// Estimate the (lengthy) wait time.
		Serial.print("  estimated wait: ");
		int seconds = (float)size / eraseBytesPerSecond(id) + 0.5;
		Serial.print(seconds);
		Serial.println(" seconds.");
		Serial.println("  Yes, full chip erase is SLOW!");
		SerialFlash.eraseAll();
		unsigned long dotMillis = millis();
		unsigned char dotcount = 0;
		while (SerialFlash.ready() == false) {
			if (millis() - dotMillis > 1000) {
				dotMillis = dotMillis + 1000;
				Serial.print(".");
				dotcount = dotcount + 1;
				if (dotcount >= 60) {
					Serial.println();
					dotcount = 0;
				}
			}
		}
		if (dotcount > 0) Serial.println();
		Serial.println("Erase completed");
		unsigned long elapsed = millis() - startMillis;
		Serial.print("  actual wait: ");
		Serial.print(elapsed / 1000ul);
		Serial.println(" seconds.");
	}

	const char* const string = "/LIBS/DRUMS/ACC_CLS/CL_HH_01.RAW";
	AudioCore.loadRaw(string);

	const char* const string2 = "/LIBS/DRUMS/ACC_CLS/BD_01.RAW";
	AudioCore.loadRaw(string2);

	const char* const string3 = "/LIBS/DRUMS/ACC_CLS/SN_01.RAW";
	AudioCore.loadRaw(string3);
}

void EngineClass::init()
{
	loadSettings(true);
	
	for (uint8_t n = 0; n <=11; n++)
	{
		ChannelSettings* channel = Engine.getChannelByNum(static_cast<edit_channel>(n));
		AudioCore.setBalancedVolume(n, channel->volume, channel->balance);	
		int coef[5];
		calcBiquad(*channel, coef);
	
		
		AudioCore.setEqBiquad(n, coef);
	}
	
	//AudioCore.setWavBiquad(Engine.songSettings.mixer.looper.eqFc, Engine.songSettings.mixer.looper.eqQ);
	//AudioCore.setLeftInputVolume(Engine.songSettings.mixer.leftInput.volume, Engine.songSettings.mixer.leftInput.balance);
	//AudioCore.setLeftInputBiquad(Engine.songSettings.mixer.leftInput.eqFc, Engine.songSettings.mixer.leftInput.eqQ);
	//AudioCore.setRightInputVolume(Engine.songSettings.mixer.rightInput.volume, Engine.songSettings.mixer.rightInput.balance);
	//AudioCore.setRightInputBiquad(Engine.songSettings.mixer.rightInput.eqFc, Engine.songSettings.mixer.rightInput.eqQ);
	//AudioCore.setReverbVolume(0, Engine.songSettings.mixer.effect1.balance);
	//AudioCore.setReverbBiquad(Engine.songSettings.mixer.effect1.eqFc, Engine.songSettings.mixer.effect1.eqQ);
	//AudioCore.setReverbRoom(Engine.songSettings.mixer.effect1.damping, Engine.songSettings.mixer.effect1.roomsize);
	//updateModeLinks();	

	/*

	HardwareCore.setButtonParam(BTN_BROWN, changeWavTrack);
	*/
	HardwareCore.setButtonParam(BTN_RED, saveSettings);
	/*
	HardwareCore.setButtonParam(BTN_ENCODER2, changeMode);
	HardwareCore.setButtonParam(BTN_ENCODER1, changeEditType);
	HardwareCore.setButtonParam(BTN_ENCODER0, muteMaster);
	*/	
//	_midiClock.begin(checkMidiEvent, 100000);
	currentDrumPattern = &songSettings.drumPattern;

	if (false)
	{
		initSerialFlashToDo();
	}


	SPI.callback = spiShotsHandler;

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
	_songSettings.mixer.looper.frequency = static_cast<float>(value / 100);
	DisplayCore.drawEncoder(encoder, _songSettings.mixer.looper.frequency, 20000);
	AudioCore.setWavBiquad(_songSettings.mixer.looper.frequency, _songSettings.mixer.looper.q);
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
	_songSettings.mixer.looper.balance = static_cast<float>(value / 100.0);
	DisplayCore.drawEncoder(encoder, value, 100, true);
	AudioCore.setLooperVolume(_songSettings.mixer.looper.volume, _songSettings.mixer.looper.balance);
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


void EngineClass::setLooperVolume(int encoder, int value)
{
	_songSettings.mixer.looper.volume = static_cast<float>(value) / 100;
	DisplayCore.drawEncoder(encoder, value, 100);
	AudioCore.setLooperVolume(_songSettings.mixer.looper.volume, _songSettings.mixer.looper.balance);
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

ChannelSettings* EngineClass::getChannelByNum(edit_channel channel)
{
	switch (channel)
	{
	case EDIT_CHANNEL_LOOPER:
		return &Engine.songSettings.mixer.looper;		
	case EDIT_CHANNEL_INPUT_MIC:
		return  &Engine.songSettings.mixer.leftInput;		
	case EDIT_CHANNEL_INPUT_GUITAR:
		return &Engine.songSettings.mixer.rightInput;		
	case EDIT_CHANNEL_DRUMS:
		return  &Engine.songSettings.mixer.drums;		
	case EDIT_CHANNEL_BASS:
		return  &Engine.songSettings.mixer.bass;
	
	case EDIT_CHANNEL_STRINGS:
		return &Engine.songSettings.mixer.strings;
	case EDIT_CHANNEL_PIANO:
		return &Engine.songSettings.mixer.piano;
		break;
	case EDIT_CHANNEL_FM:
		return  &Engine.songSettings.mixer.fm;		
	case EDIT_CHANNEL_SEND_FX_REVERB:
		return &Engine.songSettings.mixer.effect1;
	case EDIT_CHANNEL_SEND_FX_CHORUS:
		return &Engine.songSettings.mixer.effect2;
	case EDIT_CHANNEL_SEND_FX_DELAY:
		return &Engine.songSettings.mixer.effect3;
	case EDIT_CHANNEL_MASTER:
		return &Engine.songSettings.mixer.master;		
	}
	return nullptr;
}

void EngineClass::selectChannel()
{
	curentSettings = getChannelByNum(Engine.songSettings.currentChannel);
}

void EngineClass::assignDefaultButtons()
{
	HardwareCore.setButtonParam(BTN_GREEN, startTrack);
	HardwareCore.setButtonParam(BTN_BLACK, stopTrack);
	HardwareCore.setButtonParam(BTN_BROWN, backToMixer);
}


void EngineClass::checkMidiEvent() {
	
	midiShotFired = true;
}

void EngineClass::update()
{
	spiShotsHandler();
	if (_hardwareTimer >= _nextUpdateTick) {
		
		if (_tickCounter++ >= 10 || !isValidScreen)
		{
			if (_hardwareTimer > 1000000)
			{
				_hardwareTimer = 0;
			}
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
			case VIEW_MODE_EDIT_LOOPER_CHANNEL:
				LooperChannel.onShow();
				break;
			case VIEW_MODE_EDIT_DRUM_PATTERN:
				DrumChannel.onShow();
				break;
			case VIEW_MODE_EQUALIZER:
				Equalizer.onShow();
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
		case VIEW_MODE_EDIT_LOOPER_CHANNEL:
			LooperChannel.handle();
			break;
		case VIEW_MODE_EQUALIZER:
			Equalizer.handle();
			break;
		case VIEW_MODE_EDIT_DRUM_PATTERN:
			DrumChannel.handle();
			break;
		default:
			DisplayCore.clearAll();
			DisplayCore.drawText("Not implemented " + songSettings.viewMode, 3 , 3);
			break;
		}
	//	DisplayCore.update();
		//	Serial.print(seqButtonRead(24));
		//	Serial.println("----------");

		if (needUpdatePanel)
		{
			drawTopPanel();
		}

		long _watchProposed = _hardwareTimer;
		if (_watchProposed > _watchTest)
		{
			_watchTest = _watchProposed;			
		}		
		HardwareCore.updateLeds();
		//long song = _hardwareTimer - _nextUpdateTick;
		//DisplayCore.drawText(song , 80, 3, true);
		//DisplayCore.drawText(spiShots, 100, 3);
		//spiShots = 0;
		_nextUpdateTick =_hardwareTimer + 100;
		
	}
	//AudioCore.continueRecording();
}

void EngineClass::switchWindow(current_view_mode current_view_mode)
{	
	if (songSettings.viewMode != current_view_mode)
	{
		songSettings.viewMode = current_view_mode;
		DisplayCore.clearAll();
		HardwareCore.resetEncoders();
		HardwareCore.resetButtons();
		isValidScreen = false;
	}
}

void EngineClass::backToMixer(bool pressed)
{
	if (pressed)
	{
		Engine.switchWindow(VIEW_MODE_MAIN_MIXER);		
	}
}
bool EngineClass::midiShotFired = false;
long EngineClass::_watchTest = 0;
elapsedMillis EngineClass::_hardwareTimer;
long EngineClass::_nextUpdateTick = 0;
long EngineClass::_nextMidiTick = 0;
uint8_t EngineClass::_tickCounter;

 SongSettings EngineClass::songSettings;
 ChannelSettings* EngineClass::curentSettings;
 bool EngineClass::isValidScreen = false;
 IntervalTimer EngineClass::_midiClock;
 uint8_t EngineClass::_lastViewMode = 128;

 DrumPattern* EngineClass::currentDrumPattern;

EngineClass Engine;

