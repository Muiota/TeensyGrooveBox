// 
// 
// 

#include "Mixer.h"
#include "HardwareCore.h"
#include "DisplayCore.h"
#include "Engine.h"

bool _current[16];
record_status _recordStatus = RECORD_STATUS_NONE;
bool _lastIsWavPeakLed;
bool _lastIsLeftChPeakLed;
bool _lastIsRightChPeakLed;
int _lastCurrentMode = -1;
bool _isInvalidScreen;
void MixerClass::handle()
{	
	if (!_isInvalidScreen)
	{
		DisplayCore.drawMixerBackground();
		_isInvalidScreen = true;
	}

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
				case 5:
					//
					_recordStatus = static_cast<record_status>((_recordStatus + 1) % 3);
					break;
				case 6:
					//AudioCore.stopRecording();
					break;
				case 15:

					break;
				}


			}
			_current[i] = value;
			HardwareCore.seqLedWrite(i, value);
		}
	}




	DisplayCore.drawMeter(11, AudioCore.getPeakL(), AudioCore.getPeakR());
	DisplayCore.drawMeter(3, AudioCore.getReverbFxPeakL(), AudioCore.getReverbFxPeakR());


	auto wavPeakL = AudioCore.getWavPeakL();

	bool isWavPeakLed = wavPeakL > 0.2;
	if (_lastIsWavPeakLed != isWavPeakLed)
	{
		_lastIsWavPeakLed = isWavPeakLed;
		HardwareCore.seqLedWrite(12, isWavPeakLed);
	}

	DisplayCore.drawMeter(2, wavPeakL, AudioCore.getWavPeakR());

	auto leftCh = AudioCore.getPeakAudioInputL();

	bool isLeftChPeakLed = leftCh > 0.2;
	if (_lastIsLeftChPeakLed != isLeftChPeakLed)
	{
		_lastIsLeftChPeakLed = isLeftChPeakLed;
		HardwareCore.seqLedWrite(13, isLeftChPeakLed);
	}

	DisplayCore.drawMeter(0, leftCh, leftCh);
	auto rightCh = AudioCore.getPeakAudioInputR();

	bool isRightChPeakLed = rightCh > 0.2;
	if (_lastIsRightChPeakLed != isRightChPeakLed)
	{
		_lastIsRightChPeakLed = isRightChPeakLed;
		HardwareCore.seqLedWrite(11, isRightChPeakLed);
	}

	DisplayCore.drawMeter(1, rightCh, rightCh);


	DisplayCore.drawSongStatus(AudioCore.wavIsPlaying());


	auto current_mode = Engine.getCurrentMode();
	if (_lastCurrentMode != current_mode)
	{		
		DisplayCore.drawMeterTitle(0, current_mode == EDIT_CHANNEL_LEFT_CHANNEL);
		DisplayCore.drawMeterTitle(1, current_mode == EDIT_CHANNEL_RIGHT_CHANNEL);

	
		DisplayCore.drawMeterTitle(2, current_mode == EDIT_CHANNEL_WAV);
		DisplayCore.drawMeterTitle(3, current_mode == EDIT_CHANNEL_FX_REVERB);
		DisplayCore.drawMeterTitle(4, false);
		DisplayCore.drawMeterTitle(5, false);
		DisplayCore.drawMeterTitle(6, false);
		DisplayCore.drawMeterTitle(7, false);

		DisplayCore.drawMeterTitle(8, false);
		DisplayCore.drawMeterTitle(9, false);
		DisplayCore.drawMeterTitle(10, false);

		DisplayCore.drawMeterTitle(11, current_mode == EDIT_CHANNEL_MASTER);
		

		_lastCurrentMode = current_mode;
	}
	//	DisplayCore.drawRecordStatus(AudioCore.getRecorderStatus(), 0);
	//DisplayCore.drawRecordStatus(_recordStatus, 20);



}


