// 
// 
// 

#include "Mixer.h"
#include "HardwareCore.h"
#include "DisplayCore.h"
#include "Engine.h"

bool _current[16];
bool _lastIsWavPeakLed;
bool _lastIsLeftChPeakLed;
bool _lastIsRightChPeakLed;
int _lastCurrentMode = -1;
bool _subMenuPressed;

void MixerClass::onShow()
{
	HardwareCore.setButtonParam(BROWN, subMenuShow);
	HardwareCore.setButtonParam(ENCODER0, switchToSongLoader);
}

void MixerClass::switchToSongLoader(bool pressed)
{
	if (pressed && _subMenuPressed)
	{
		HardwareCore.setLedEncoder(0, false);		
		Engine.switchWindow(VIEW_MODE_OPEN_SONG);
		
	}	
}

void MixerClass::subMenuShow(bool pressed)
{	
	HardwareCore.setLedEncoder(0, pressed);
	_subMenuPressed = pressed;	
	if (pressed)
	{
		DisplayCore.disaplaySubMenu();
	}
	else
	{
		DisplayCore.clearAll();
		Engine.isValidScreen = false;
	}
}

void MixerClass::handle()
{	
	if (_subMenuPressed)
	{
		return;
	}

	bool _fullRedraw = false;
	if (!Engine.isValidScreen)
	{
		DisplayCore.drawMixerBackground();
		_fullRedraw = true;
		Engine.isValidScreen = true;
	}

/*	bool brownButtonPressed = HardwareCore.panelButtonRead(BROWN);
	
	if (_lastBrownButtonPressed != brownButtonPressed)
	{		
		
		_lastBrownButtonPressed = brownButtonPressed;
	} */
	
	/*
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
	*/



	DisplayCore.drawMixerMeter(11, AudioCore.getPeakL(), AudioCore.getPeakR());
	DisplayCore.drawMixerMeter(3, AudioCore.getReverbFxPeakL(), AudioCore.getReverbFxPeakR());


	auto wavPeakL = AudioCore.getWavPeakL();

	bool isWavPeakLed = wavPeakL > 0.2;
	if (_lastIsWavPeakLed != isWavPeakLed)
	{
		_lastIsWavPeakLed = isWavPeakLed;
		HardwareCore.seqLedWrite(12, isWavPeakLed);
	}

	DisplayCore.drawMixerMeter(2, wavPeakL, AudioCore.getWavPeakR());

	auto leftCh = AudioCore.getPeakAudioInputL();

	bool isLeftChPeakLed = leftCh > 0.2;
	if (_lastIsLeftChPeakLed != isLeftChPeakLed)
	{
		_lastIsLeftChPeakLed = isLeftChPeakLed;
		HardwareCore.seqLedWrite(13, isLeftChPeakLed);
	}

	DisplayCore.drawMixerMeter(0, leftCh, leftCh);
	auto rightCh = AudioCore.getPeakAudioInputR();

	bool isRightChPeakLed = rightCh > 0.2;
	if (_lastIsRightChPeakLed != isRightChPeakLed)
	{
		_lastIsRightChPeakLed = isRightChPeakLed;
		HardwareCore.seqLedWrite(11, isRightChPeakLed);
	}

	DisplayCore.drawMixerMeter(1, rightCh, rightCh);


	DisplayCore.drawSongStatus(AudioCore.wavIsPlaying());
		
	if (_lastCurrentMode != Engine.songSettings.currentChannel || _fullRedraw)
	{
		for (uint8_t i = 0; i <= 11; i++) {
			{
				DisplayCore.drawMixerMeterTitle(i, Engine.songSettings.currentChannel == i);
			}

			_lastCurrentMode = Engine.songSettings.currentChannel;
		}
		//	DisplayCore.drawRecordStatus(AudioCore.getRecorderStatus(), 0);
		//DisplayCore.drawRecordStatus(_recordStatus, 20);

	}

}


