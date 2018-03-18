// 
// 
// 

#include "Engine.h"

String songs[60];
uint8_t SONG_COUNT = 0;
uint8_t CURRENT_SONG = 0;
uint8_t _lastSong = -1;


typedef struct {
	float masterVolume = 0.6f;
} MasterSettings;

typedef struct {
	float volume = 1.0f;
	float frequency = 12000.0f;
	float q = 0.707f;
} WavSettings;


typedef struct {
	MasterSettings master;	
	WavSettings wav;
} Settings;


Settings settings;
enum edit_mode {
	MASTER = 0,
	WAV = 1,
	LEFT_CHANNEL = 2,
	RIGHT_CHANNEL = 3
};
edit_mode _mode = MASTER;

void EngineClass::drawMode()
{
	DisplayCore.drawEncoderTitle(0, "", false);
	DisplayCore.drawEncoderTitle(1, "", false);
	DisplayCore.drawEncoderTitle(2, "", false);

	DisplayCore.drawEncoderTitle(1, "LP FQ", true);
	HardwareCore.setEncoderParam(1, setWavLowpass, "LP FQ", 100, 20000, 100, settings.wav.frequency);
	DisplayCore.drawEncoderTitle(2, "MASTER", true);
	HardwareCore.setEncoderParam(2, setMasterVolume, "MASTER", 0, 1, 0.01, settings.master.masterVolume);
	DisplayCore.drawMeterTitle(8, _mode == MASTER);
	DisplayCore.drawMeterTitle(4, _mode == WAV);
	DisplayCore.drawMeterTitle(5, _mode == LEFT_CHANNEL);
	DisplayCore.drawMeterTitle(6, _mode == RIGHT_CHANNEL);
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
	AudioCore.setMasterVolume(settings.master.masterVolume);
	drawMode();	

	HardwareCore.setButtonParam(GREEN, startWavTrack);
	HardwareCore.setButtonParam(BLACK, stopWavTrack);
	HardwareCore.setButtonParam(BROWN, changeWavTrack);
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


void EngineClass::setWavLowpass(int encoder, int value)
{
	settings.wav.frequency = static_cast<float>(value / 100);
	DisplayCore.drawEncoder(encoder, settings.wav.frequency, 20000);
	AudioCore.setWavLowpass(settings.wav.frequency, settings.wav.q);
}

void EngineClass::setMasterVolume(int encoder, int value)
{	
	settings.master.masterVolume = static_cast<float>(value) / 100;
	DisplayCore.drawEncoder(encoder, value, 100);
	AudioCore.setMasterVolume(settings.master.masterVolume);
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

