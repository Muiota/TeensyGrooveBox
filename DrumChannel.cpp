#include "DrumChannel.h"




void DrumChannelClass::onShow()
{
	Engine.assignDefaultButtons();

///	HardwareCore.panelButtonRead()
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
