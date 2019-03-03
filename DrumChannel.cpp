#include "DrumChannel.h"



void DrumChannelClass::onShow()
{
	Engine.assignDefaultButtons();
	HardwareCore.setSeqButtonParam(seqPressedHandler);
}


void DrumChannelClass::seqPressedHandler(bool pressed, int button)
{
	uint8_t* string = Engine.currentDrumPattern->shots[button];
	string[0] = static_cast<uint8_t>(pressed);
	string[1] = static_cast<uint8_t>(pressed);	
}

void DrumChannelClass::handle()
{
	bool _fullRedraw = false;
	if (!Engine.isValidScreen)
	{
		DisplayCore.drawDrumPatternBackground();
		_fullRedraw = true;
		Engine.isValidScreen = true;
	}	
	
	DisplayCore.drawDrumPattern(Engine.currentDrumPattern->shots, _fullRedraw);
}

void DrumChannelClass::midiUpdate()
{

	uint8_t* drums =  Engine.currentDrumPattern->shots[Engine.songSettings.pattern.currentStep];
	if (drums[0] > 0)
	{
		Serial.println(Engine.songSettings.pattern.currentStep);
		AudioCore.drum1On();
	}
	
}

uint8_t DrumChannelClass::currentLine = 0;
