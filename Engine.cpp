// 
// 
// 

#include "Engine.h"

String songs[60];
uint8_t SONG_COUNT = 0;
uint8_t CURRENT_SONG = 0;
uint8_t _lastSong = -1;
bool _pressed[40];
float _wavFrequency = 12000;
float _wavQ = 0.707;
enum edit_mode {
	MASTER,
	WAV,
	LEFT_CHANNEL,
	RIGHT_CHANNEL
};
edit_mode _mode = MASTER;
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
	AudioCore.setWavLowpass(_wavFrequency, _wavQ);
}

void EngineClass::update()
{
	if (_hardwareTimer >= 100) {
		_hardwareTimer = 0;
		auto usageCPU = AudioProcessorUsageMax();
		auto usageMemory = AudioMemoryUsageMax();
		AudioProcessorUsageMaxReset();
		AudioMemoryUsageMaxReset();
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
		for (uint8_t i = 0; i <= 2; i++) {
			int32_t encoderValue = HardwareCore.readEncoder(i);	
			bool needUpdate = false;
			if (encoderValue < 0)
			{
				encoderValue = 0;
				needUpdate = true;

			}
			else if (encoderValue > 400)
			{
				encoderValue = 400;
				needUpdate = true;
			}

			if (needUpdate)
			{
				HardwareCore.writeEncoder(i, encoderValue);
				Serial.write("update " + i);				
			}
			uint8_t one_value_r = encoderValue / 4;

			if (one_value_r != _currentEncoder[i])
			{

				switch (i)
				{
				case 0:
					

					break;
				case 1:
					AudioCore.setWavLowpass(static_cast<float>(one_value_r * 200), _wavQ);
					break;
				case 2:
					AudioCore.setVolume(static_cast<float>(one_value_r) / 100);
					break;
				}

				DisplayCore.drawEncoder(i, one_value_r, "MASTER");
				//digitalWrite(39, one_value_r);
				//		seqLedWrite(8, two_value);
				//	seqLedWrite(15, three_value);
				_currentEncoder[i] = one_value_r;
			}
		}


		for (int i = 31; i <= 36; i++) {
			uint8_t value = digitalRead(i);
				if (value == 0)
				{
					
					if (!_pressed[i])
					{
						_pressed[i] = true;
						switch (i)
						{
						case 31:
							if (AudioCore.wavIsPlaying())
							{
								Serial.print("Stop");
								AudioCore.stopWav();
							}
							break;
						case 32:
							if (!AudioCore.wavIsPlaying())
							{
								CURRENT_SONG = (CURRENT_SONG + 1) % SONG_COUNT;
							}

							break;
						case 33:
							if (!AudioCore.wavIsPlaying())
							{
								Serial.print("Start");
								auto song = songs[CURRENT_SONG];
								AudioCore.playWav(("/DATA/TRACKS/" + song).c_str());
							}
							break;
						}
					}
					
				}
				else
				{					
					_pressed[i] = false;
				}
		}

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

