// 
// 
// 

#include "Engine.h"

String songs[60];
bool _muteMaster;
uint8_t SONG_COUNT = 0;
uint8_t CURRENT_SONG = 0;
uint8_t _lastSong = -1;





typedef struct {
	MasterSettings master;	
	ChannelSettings wav;
	ChannelSettings leftInput;
	ChannelSettings rightInput;
	ChannelSettings fxReverb;
} MixerSettings;


enum edit_channel {
	EDIT_CHANNEL_MASTER = 0,
	EDIT_CHANNEL_FX_REVERB = 1,
	EDIT_CHANNEL_WAV = 2,
	EDIT_CHANNEL_LEFT_CHANNEL = 3,
	EDIT_CHANNEL_RIGHT_CHANNEL = 4,
};

enum edit_cnannel_mode {
	EDIT_CHANNEL_MODE_EQ = 0,
	EDIT_CHANNEL_MODE_BALANCE = 1,	
};


MixerSettings _mixerSettings;
int _currentMode = EDIT_CHANNEL_MASTER;
int _currentEditType = EDIT_CHANNEL_MODE_EQ;

void EngineClass::updateModeLinks()
{
	HardwareCore.resetEncoders();
	DisplayCore.drawEncoderTitle(0, "", false);
	DisplayCore.drawEncoderTitle(1, "", false);
	DisplayCore.drawEncoderTitle(2, "", false);
	
	switch (_currentMode)
	{
		case EDIT_CHANNEL_MASTER:
		DisplayCore.drawEncoderTitle(2, "MASTER", true);
		HardwareCore.setEncoderParam(2, setMasterVolume, "MASTER", 0, 1, 0.01, _mixerSettings.master.masterVolume);
		break;
		case EDIT_CHANNEL_WAV:
		

			switch (_currentEditType)
			{
			case EDIT_CHANNEL_MODE_EQ:

				DisplayCore.drawEncoderTitle(1, "LP FQ", true);
				HardwareCore.setEncoderParam(1, setWavLowpass, "LP FQ", 100, 20000, 100, _mixerSettings.wav.frequency);
				break;
			case EDIT_CHANNEL_MODE_BALANCE:

				DisplayCore.drawEncoderTitle(1, "BAL", true);
				HardwareCore.setEncoderParam(1, setWavBalance, "BAL", -1, 1, 0.05, _mixerSettings.wav.balance);
				break;
			}
			
		
		DisplayCore.drawEncoderTitle(2, "W VOL", true);
			HardwareCore.setEncoderParam(2, setWavVolume, "W VOL", 0, 1, 0.01, _mixerSettings.wav.volume);
			break;
		case EDIT_CHANNEL_LEFT_CHANNEL:

			switch (_currentEditType)
			{
			case EDIT_CHANNEL_MODE_EQ:

				DisplayCore.drawEncoderTitle(1, "HP FQ", true);
				HardwareCore.setEncoderParam(1, setLeftInputHighpass, "HP FQ", 100, 20000, 100, _mixerSettings.leftInput.frequency);
				break;
			case EDIT_CHANNEL_MODE_BALANCE:

				DisplayCore.drawEncoderTitle(1, "BAL", true);
				HardwareCore.setEncoderParam(1, setLeftInputBalance, "BAL", -1, 1, 0.05, _mixerSettings.leftInput.balance);
				break;
			}

			DisplayCore.drawEncoderTitle(2, "L VOL", true);
			HardwareCore.setEncoderParam(2, setLeftInputVolume, "L VOL", 0, 1, 0.01, _mixerSettings.leftInput.volume);
			break;
		case EDIT_CHANNEL_RIGHT_CHANNEL:
			
			switch (_currentEditType)
			{
			case EDIT_CHANNEL_MODE_EQ:

				DisplayCore.drawEncoderTitle(1, "HP FQ", true);
				HardwareCore.setEncoderParam(1, setRightInputHighpass, "HP FQ", 100, 20000, 100, _mixerSettings.rightInput.frequency);
				break;
			case EDIT_CHANNEL_MODE_BALANCE:

				DisplayCore.drawEncoderTitle(1, "BAL", true);
				HardwareCore.setEncoderParam(1, setRightInputBalance, "BAL", -1, 1, 0.05, _mixerSettings.rightInput.balance);
				break;
			}


			DisplayCore.drawEncoderTitle(2, "R VOL", true);
			HardwareCore.setEncoderParam(2, setRightInputVolume, "R VOL", 0, 1, 0.01, _mixerSettings.rightInput.volume);
			break;
		case EDIT_CHANNEL_FX_REVERB:
			
			
			switch (_currentEditType)
			{
			case EDIT_CHANNEL_MODE_EQ:
				DisplayCore.drawEncoderTitle(1, "HP FQ", true);
				HardwareCore.setEncoderParam(1, setReverbHighpass, "HP FQ", 100, 20000, 100, _mixerSettings.fxReverb.frequency);
				break;
			case EDIT_CHANNEL_MODE_BALANCE:

				DisplayCore.drawEncoderTitle(1, "BAL", true);
				HardwareCore.setEncoderParam(1, setReverbBalance, "BAL", -1, 1, 0.05, _mixerSettings.fxReverb.balance);
				break;
			}
		
		
		DisplayCore.drawEncoderTitle(2, "REVER", true);
			HardwareCore.setEncoderParam(2, setReverbVolume, "R VOL", 0, 1, 0.01, _mixerSettings.fxReverb.volume);
			break;
	}

	

	DisplayCore.drawMeterTitle(8, _currentMode == EDIT_CHANNEL_MASTER);
	DisplayCore.drawMeterTitle(2, _currentMode == EDIT_CHANNEL_FX_REVERB);
	DisplayCore.drawMeterTitle(4, _currentMode == EDIT_CHANNEL_WAV);
	DisplayCore.drawMeterTitle(5, _currentMode == EDIT_CHANNEL_LEFT_CHANNEL);
	DisplayCore.drawMeterTitle(6, _currentMode == EDIT_CHANNEL_RIGHT_CHANNEL);
}

void EngineClass::saveChannelPart(JsonObject& mixer, String channelName, ChannelSettings& setting)
{
	JsonObject& channel = mixer.createNestedObject(channelName);
	channel["volume"] = setting.volume;
	channel["balance"] = setting.balance;
	channel["frequency"] = setting.frequency;
	channel["q"] = setting.q;
}

void EngineClass::saveSettings()
{

	if (SD.exists("settings.mxr"))
	{
		SD.remove("settings.mxr");
	}

	StaticJsonBuffer<1000> jsonBuffer;	
	JsonObject& root = jsonBuffer.createObject();
	JsonObject& mixer = root.createNestedObject("mixerSettings");	
	JsonObject& master = mixer.createNestedObject("master");
	master["volume"] = _mixerSettings.master.masterVolume;
	
	saveChannelPart(mixer, "wav", _mixerSettings.wav);
	saveChannelPart(mixer, "leftInput", _mixerSettings.leftInput);
	saveChannelPart(mixer, "rightInput", _mixerSettings.rightInput);
	saveChannelPart(mixer, "fxReverb", _mixerSettings.fxReverb);
	
	/*JsonArray& data = mixer.createNestedArray("data");
	data.add(48.756080);
	data.add(2.302038); */

	// Step 4	
	root.prettyPrintTo(Serial);
	File settings = SD.open("settings.mxr", FILE_WRITE);
	root.prettyPrintTo(settings);
	settings.close();

}

void EngineClass::loadSettings()
{
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
		_mixerSettings.master.masterVolume = master["volume"];
		JsonObject& wav = mixer["wav"];
		_mixerSettings.wav.volume = wav["volume"];
		_mixerSettings.wav.frequency = wav["frequency"];
		_mixerSettings.wav.q = wav["q"];
		_mixerSettings.wav.balance= wav["balance"];

		JsonObject& leftInput = mixer["leftInput"];
		_mixerSettings.leftInput.volume = leftInput["volume"];
		_mixerSettings.leftInput.frequency = leftInput["frequency"];
		_mixerSettings.leftInput.q = leftInput["q"];
		_mixerSettings.leftInput.balance = leftInput["balance"];

		JsonObject& rightInput = mixer["rightInput"];
		_mixerSettings.rightInput.volume = rightInput["volume"];
		_mixerSettings.rightInput.frequency = rightInput["frequency"];
		_mixerSettings.rightInput.q = rightInput["q"];
		_mixerSettings.rightInput.balance = rightInput["balance"];

		JsonObject& fxReverb = mixer["fxReverb"];
		_mixerSettings.fxReverb.volume = fxReverb["volume"];
		_mixerSettings.fxReverb.frequency = fxReverb["frequency"];
		_mixerSettings.fxReverb.q = fxReverb["q"];
		_mixerSettings.fxReverb.balance = fxReverb["balance"];

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

	_mixerSettings.wav.frequency = 12000;
	_mixerSettings.wav.q = 0.707f;
	_mixerSettings.leftInput.frequency = 100;
	_mixerSettings.leftInput.q = 0.707f;
	_mixerSettings.rightInput.frequency = 200;
	_mixerSettings.rightInput.q = 0.707f;
	_mixerSettings.fxReverb.frequency = 300;
	_mixerSettings.fxReverb.q = 0.707f;
	loadSettings();
	AudioCore.setMasterVolume(_mixerSettings.master.masterVolume);
	AudioCore.setWavVolume(_mixerSettings.wav.volume, _mixerSettings.wav.balance);
	AudioCore.setWavBiquad(_mixerSettings.wav.frequency, _mixerSettings.wav.q);
	AudioCore.setLeftInputVolume(_mixerSettings.leftInput.volume, _mixerSettings.leftInput.balance);
	AudioCore.setLeftInputBiquad(_mixerSettings.leftInput.frequency, _mixerSettings.leftInput.q);
	AudioCore.setRightInputVolume(_mixerSettings.rightInput.volume, _mixerSettings.rightInput.balance);
	AudioCore.setLeftInputBiquad(_mixerSettings.rightInput.frequency, _mixerSettings.rightInput.q);
	AudioCore.setReverbVolume(_mixerSettings.fxReverb.volume, _mixerSettings.fxReverb.balance);
	AudioCore.setReverbBiquad(_mixerSettings.fxReverb.frequency, _mixerSettings.fxReverb.q);
	updateModeLinks();	

	HardwareCore.setButtonParam(GREEN, startWavTrack);
	HardwareCore.setButtonParam(BLACK, stopWavTrack);
	HardwareCore.setButtonParam(BROWN, changeWavTrack);
	HardwareCore.setButtonParam(RED, saveSettings);
	HardwareCore.setButtonParam(ENCODER2, changeMode);
	HardwareCore.setButtonParam(ENCODER1, changeEditType);
	HardwareCore.setButtonParam(ENCODER0, muteMaster);
}




void EngineClass::muteMaster()
{
	_muteMaster = !_muteMaster;
	DisplayCore.drawMuteMaster(_muteMaster);
	if (_muteMaster)
	{
		AudioCore.setMasterVolume(_mixerSettings.master.masterVolume / 4);
	}
	else
	{
		AudioCore.setMasterVolume(_mixerSettings.master.masterVolume);
	}
}

void EngineClass::startWavTrack()
{
	if (!AudioCore.wavIsPlaying())
	{
		Serial.print("Start");
		auto song = songs[CURRENT_SONG];
		AudioCore.playWav(("/DATA/TRACKS/" + song).c_str());
	}
}

void EngineClass::stopWavTrack()
{
	if (AudioCore.wavIsPlaying())
	{
		Serial.print("Stop");
		AudioCore.stopWav();
	}
}

void EngineClass::changeWavTrack()
{
	if (!AudioCore.wavIsPlaying())
	{
		CURRENT_SONG = (CURRENT_SONG + 1) % SONG_COUNT;
	}
}


void EngineClass::changeMode()
{
	_currentMode = (_currentMode + 1) % 5;
	updateModeLinks();
}

void EngineClass::changeEditType()
{
	_currentEditType = (_currentEditType + 1) % 2;
	updateModeLinks();
}




void EngineClass::setWavLowpass(int encoder, int value)
{
	_mixerSettings.wav.frequency = static_cast<float>(value / 100);
	DisplayCore.drawEncoder(encoder, _mixerSettings.wav.frequency, 20000);
	AudioCore.setWavBiquad(_mixerSettings.wav.frequency, _mixerSettings.wav.q);
}

void EngineClass::setLeftInputHighpass(int encoder, int value)
{
	_mixerSettings.leftInput.frequency = static_cast<float>(value / 100);
	DisplayCore.drawEncoder(encoder, _mixerSettings.leftInput.frequency, 20000);
	AudioCore.setLeftInputBiquad(_mixerSettings.leftInput.frequency, _mixerSettings.leftInput.q);
}

void EngineClass::setLeftInputBalance(int encoder, int value)
{
	_mixerSettings.leftInput.balance = static_cast<float>(value / 100.0);
	DisplayCore.drawEncoder(encoder, value, 100, true);
	AudioCore.setLeftInputVolume(_mixerSettings.leftInput.volume, _mixerSettings.leftInput.balance);
}

void EngineClass::setWavBalance(int encoder, int value)
{
	_mixerSettings.wav.balance = static_cast<float>(value / 100.0);
	DisplayCore.drawEncoder(encoder, value, 100, true);
	AudioCore.setWavVolume(_mixerSettings.wav.volume, _mixerSettings.wav.balance);
}


void EngineClass::setRightInputBalance(int encoder, int value)
{
	_mixerSettings.rightInput.balance = static_cast<float>(value / 100.0);
	DisplayCore.drawEncoder(encoder, value, 100, true);
	AudioCore.setRightInputVolume(_mixerSettings.rightInput.volume, _mixerSettings.rightInput.balance);
}

void EngineClass::setReverbBalance(int encoder, int value)
{
	_mixerSettings.fxReverb.balance = static_cast<float>(value / 100.0);
	DisplayCore.drawEncoder(encoder, value, 100, true);
	AudioCore.setReverbVolume(_mixerSettings.fxReverb.volume, _mixerSettings.fxReverb.balance);
}


void EngineClass::setRightInputHighpass(int encoder, int value)
{
	_mixerSettings.rightInput.frequency = static_cast<float>(value / 100);
	DisplayCore.drawEncoder(encoder, _mixerSettings.rightInput.frequency, 20000);
	AudioCore.setRightInputBiquad(_mixerSettings.rightInput.frequency, _mixerSettings.rightInput.q);
}

void EngineClass::setReverbHighpass(int encoder, int value)
{
	_mixerSettings.fxReverb.frequency = static_cast<float>(value / 100);
	DisplayCore.drawEncoder(encoder, _mixerSettings.fxReverb.frequency, 20000);
	AudioCore.setReverbBiquad(_mixerSettings.fxReverb.frequency, _mixerSettings.fxReverb.q);
}

void EngineClass::setMasterVolume(int encoder, int value)
{	
	_mixerSettings.master.masterVolume = static_cast<float>(value) / 100;
	DisplayCore.drawEncoder(encoder, value, 100);	
	if (_muteMaster)
	{
		AudioCore.setMasterVolume(_mixerSettings.master.masterVolume / 4);
	}
	else
	{
		AudioCore.setMasterVolume(_mixerSettings.master.masterVolume);
	}
}

void EngineClass::setWavVolume(int encoder, int value)
{
	_mixerSettings.wav.volume = static_cast<float>(value) / 100;
	DisplayCore.drawEncoder(encoder, value, 100);
	AudioCore.setWavVolume(_mixerSettings.wav.volume, _mixerSettings.wav.balance);
}

void EngineClass::setLeftInputVolume(int encoder, int value)
{
	_mixerSettings.leftInput.volume = static_cast<float>(value) / 100;
	DisplayCore.drawEncoder(encoder, value, 100);
	AudioCore.setLeftInputVolume(_mixerSettings.leftInput.volume, _mixerSettings.leftInput.balance);
}

void EngineClass::setRightInputVolume(int encoder, int value)
{
	_mixerSettings.rightInput.volume = static_cast<float>(value) / 100;
	DisplayCore.drawEncoder(encoder, value, 100);
	AudioCore.setRightInputVolume(_mixerSettings.rightInput.volume, _mixerSettings.leftInput.balance);
}

void EngineClass::setReverbVolume(int encoder, int value)
{
	_mixerSettings.fxReverb.volume = static_cast<float>(value) / 100;
	DisplayCore.drawEncoder(encoder, value, 100);
	AudioCore.setReverbVolume(_mixerSettings.fxReverb.volume, _mixerSettings.fxReverb.balance);
}



void EngineClass::update()
{
	if (_hardwareTimer >= 100) {
		_hardwareTimer = 0;
		auto usageCPU = AudioProcessorUsageMax();
		auto usageMemory = AudioMemoryUsageMax();
		AudioProcessorUsageMaxReset();
		AudioMemoryUsageMaxReset();

		HardwareCore.update();

		for (uint8_t i = 0; i <= 15; i++) {
			auto value = HardwareCore.seqButtonRead(i);
			if (_current[i] != value)
			{
				DisplayCore.drawSequenceButton(i, value);
				if (value)
				{
					switch (i)
					{
					case 0:
						AudioCore.drum1On();

						break;
					case 1:
						AudioCore.drum2On();

						break;
					case 2:
						AudioCore.drum3On();

						break;
					case 3:
						AudioCore.drum4On();

						break;
					case 4:
						//   playFlashRaw1.play("LIBS/DRUMS/KIT_1_ACOUSTIC_CLOSE/K1CLOSE_CIHAT_01.RAW");
						break;
					}


				}
				_current[i] = value;
				HardwareCore.seqLedWrite(i, value);
			}
		}

		//Serial.print(" ");		
	


		

		//	Serial.print(seqButtonRead(24));
		//	Serial.println("----------");
	
		DisplayCore.drawUsage(usageCPU, usageMemory);

		DisplayCore.drawMeter(8, AudioCore.getPeakL(), AudioCore.getPeakR());
		DisplayCore.drawMeter(2, AudioCore.getReverbFxPeakL(), AudioCore.getReverbFxPeakR());
		DisplayCore.drawMeter(4, AudioCore.getWavPeakL(), AudioCore.getWavPeakR());

		auto leftCh = AudioCore.getPeakAudioInputL();
		DisplayCore.drawMeter(5, leftCh, leftCh);
		auto rightCh = AudioCore.getPeakAudioInputR();
		DisplayCore.drawMeter(6, rightCh, rightCh);

		

		
		DisplayCore.drawSongStatus(AudioCore.wavIsPlaying());
	
		if (CURRENT_SONG != _lastSong)
		{
			auto song = songs[CURRENT_SONG];
			DisplayCore.drawSongName(String(CURRENT_SONG)  + " " + song.substring(0, song.length() - 4));
			_lastSong = CURRENT_SONG;
		}
	}
}


EngineClass Engine;

