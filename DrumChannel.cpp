#include "DrumChannel.h"



void DrumChannelClass::onShow()
{
	Engine.assignDefaultButtons();
	HardwareCore.setSeqButtonParam(seqPressedHandler);
}


void DrumChannelClass::seqPressedHandler(bool pressed, int button)
{
	Engine.currentDrumPattern->shots[button][0] = pressed;
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

	DisplayCore.drawDrumPattern(Engine.currentDrumPattern->shots);
}

 uint8_t DrumChannelClass::currentLine = 0;
