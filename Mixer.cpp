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
	Engine.assignDefaultButtons();
	HardwareCore.setButtonParam(BTN_BROWN, subMenuShow);
	HardwareCore.setButtonParam(BTN_ENCODER0, encoder0press);
	HardwareCore.setButtonParam(BTN_ENCODER1, encoder1press);
	HardwareCore.setButtonParam(BTN_ENCODER2, encoder2press);	
	HardwareCore.setEncoderParam(0, selectChanel, "selectChannel", 0, 11, 1, Engine.songSettings.currentChannel);
	HardwareCore.setEncoderParam(1, setChannelVolume, "VOLUME", 0, 1, 0.02, Engine.curentSettings->volume);
	HardwareCore.setEncoderParam(2, setChannelBalance, "VOLUME", -1, 1, 0.05, Engine.curentSettings->balance);
}

void MixerClass::selectChanel(int encoder, int value)
{
	Engine.songSettings.currentChannel = static_cast<edit_channel>(value / 100);
	Engine.selectChannel();
	HardwareCore.setEncoderValue(1, Engine.curentSettings->volume);
	HardwareCore.setEncoderValue(2, Engine.curentSettings->balance);

	
}

void MixerClass::switchToChannel()
{
	switch (Engine.songSettings.currentChannel)
	{
		case EDIT_CHANNEL_LOOPER:
			Engine.switchWindow(VIEW_MODE_EDIT_LOOPER_CHANNEL);
			break;
		case EDIT_CHANNEL_INPUT_MIC: break;
		case EDIT_CHANNEL_INPUT_GUITAR: break;
		case EDIT_CHANNEL_DRUMS:
			Engine.switchWindow(VIEW_MODE_EDIT_DRUM_PATTERN);			
		break;
		case EDIT_CHANNEL_BASS: break;
		case EDIT_CHANNEL_STRINGS: break;
		case EDIT_CHANNEL_PIANO: break;
		case EDIT_CHANNEL_FM: break;
		case EDIT_CHANNEL_SEND_FX_REVERB: break;
		case EDIT_CHANNEL_SEND_FX_CHORUS: break;
		case EDIT_CHANNEL_SEND_FX_DELAY: break;
		case EDIT_CHANNEL_MASTER: 
			Engine.switchWindow(VIEW_MODE_SEQUENCER);
		break;
	}
}

void MixerClass::encoder0press(bool pressed)
{
	if (pressed)
	{
		HardwareCore.setLedEncoder(0, false);

		if (_subMenuPressed)
		{
			Engine.switchWindow(VIEW_MODE_OPEN_SONG);
		}
		else
		{
			Engine.songSettings.currentView = EDIT_CHANNEL_MODE_MAIN;
			switchToChannel();		
		}
	}
}

void MixerClass::encoder1press(bool pressed)
{	
	Engine.switchWindow(VIEW_MODE_EQUALIZER);
}

void MixerClass::encoder2press(bool pressed)
{
	Engine.songSettings.currentView = EDIT_CHANNEL_MODE_SETTINGS;
	switchToChannel();
}

void MixerClass::subMenuShow(bool pressed)
{	
	HardwareCore.setLedEncoder(0, pressed);
	HardwareCore.setLedEncoder(1, pressed);
	if (_subMenuPressed != pressed)
	{
		_subMenuPressed = pressed;
		if (pressed)
		{
			DisplayCore.disaplaySubMenu();
		}
		else
		{
			DisplayCore.clearAll(); //todo clear only needed with lines
			Engine.isValidScreen = false;
		}
	}
}

void MixerClass::setChannelVolume(int encoder, int value)
{
	Engine.curentSettings->volume = static_cast<float>(value) / 100;	
	ChannelSettings* channel = Engine.getChannelByNum(static_cast<edit_channel>(Engine.songSettings.currentChannel));
	DisplayCore.drawMixerButtons(Engine.songSettings.currentChannel, channel->volume, channel->balance, true);
	AudioCore.setBalancedVolume(Engine.songSettings.currentChannel, channel->volume, channel->balance);
}


void MixerClass::setChannelBalance(int encoder, int value)
{
	Engine.curentSettings->balance = static_cast<float>(value) / 100;
	ChannelSettings* channel = Engine.getChannelByNum(static_cast<edit_channel>(Engine.songSettings.currentChannel));
	DisplayCore.drawMixerButtons(Engine.songSettings.currentChannel, channel->volume, channel->balance, true);
	AudioCore.setBalancedVolume(Engine.songSettings.currentChannel, channel->volume, channel->balance);
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

/*	bool brownButtonPressed = HardwareCore.panelButtonRead(BTN_BROWN);
	
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



	DisplayCore.drawMixerMeter(EDIT_CHANNEL_MASTER, AudioCore.getPeakL(), AudioCore.getPeakR());
	DisplayCore.drawMixerMeter(EDIT_CHANNEL_SEND_FX_REVERB, AudioCore.getReverbFxPeakL(), AudioCore.getReverbFxPeakR());

	auto wavPeakL = AudioCore.getWavPeakL();

	bool isWavPeakLed = wavPeakL > 0.2;
	if (_lastIsWavPeakLed != isWavPeakLed)
	{
		_lastIsWavPeakLed = isWavPeakLed;
		HardwareCore.seqLedWrite(12, isWavPeakLed);
	}

	DisplayCore.drawMixerMeter(EDIT_CHANNEL_LOOPER, wavPeakL, AudioCore.getWavPeakR());

	auto leftCh = AudioCore.getPeakAudioInputL();

	bool isLeftChPeakLed = leftCh > 0.2;
	if (_lastIsLeftChPeakLed != isLeftChPeakLed)
	{
		_lastIsLeftChPeakLed = isLeftChPeakLed;
		HardwareCore.seqLedWrite(13, isLeftChPeakLed);
	}

	DisplayCore.drawMixerMeter(EDIT_CHANNEL_INPUT_MIC, leftCh, leftCh);
	auto rightCh = AudioCore.getPeakAudioInputR();

	bool isRightChPeakLed = rightCh > 0.2;
	if (_lastIsRightChPeakLed != isRightChPeakLed)
	{
		_lastIsRightChPeakLed = isRightChPeakLed;
		HardwareCore.seqLedWrite(11, isRightChPeakLed);
	}

	DisplayCore.drawMixerMeter(EDIT_CHANNEL_INPUT_GUITAR, rightCh, rightCh);


	DisplayCore.drawSongStatus(AudioCore.wavIsPlaying());
	if (_lastCurrentMode != Engine.songSettings.currentChannel || _fullRedraw)
	{
		for (uint8_t i = 0; i <= 11; i++) {
			{
				auto is_active = Engine.songSettings.currentChannel == i;
				DisplayCore.drawMixerMeterTitle(i, is_active);
				ChannelSettings* channel = Engine.getChannelByNum(static_cast<edit_channel>(i));
				DisplayCore.drawMixerButtons(i, channel->volume, channel->balance, is_active);
		
			}

			_lastCurrentMode = Engine.songSettings.currentChannel;
		}
		//	DisplayCore.drawRecordStatus(AudioCore.getRecorderStatus(), 0);
		//DisplayCore.drawRecordStatus(_recordStatus, 20);

	}

}


