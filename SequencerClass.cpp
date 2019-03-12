#include "SequencerClass.h"
#include "DrumChannel.h"


void SequencerClass::onShow()
{
	Engine.assignDefaultButtons();
}

void SequencerClass::updateStatus()
{
}

void SequencerClass::handle()
{
	bool _fullRedraw = false;
	if (!Engine.isValidScreen)
	{
		DisplayCore.drawSequencerBackground();		
		DisplayCore.drawSequencerIcons(2);
		_fullRedraw = true;
		Engine.isValidScreen = true;
	}

}

void SequencerClass::midiUpdate()
{
	DrumChannel.midiUpdate();
}
