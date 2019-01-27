
#include "LooperChanel.h"
#include "DisplayCore.h"
#include "HardwareCore.h"
#include "Engine.h"

static uint8_t left_tape_frame = 0;
static uint8_t right_tape_frame = 5;

void LooperChanelClass::handle()
{
	if (!Engine.isValidScreen)
	{
		DisplayCore.disaplaySubMenu();
		DisplayCore.disaplayLooper();
		Engine.isValidScreen = true;
	}
	left_tape_frame = (left_tape_frame + 1) % 10;
	right_tape_frame = (right_tape_frame + 1) % 10;
	DisplayCore.drawTapeFrame(left_tape_frame, right_tape_frame);
}



void LooperChanelClass::onShow()
{
	HardwareCore.setButtonParam(BROWN, backToMixer);
	//HardwareCore.setButtonParam(ENCODER0, switchToSongLoader);
}

void LooperChanelClass::backToMixer(bool pressed)
{
	if (pressed)
	{
		Engine.switchWindow(VIEW_MODE_MAIN_MIXER);
	}
}

