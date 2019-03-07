#include "DrumChannel.h"



void DrumChannelClass::onShow()
{
	Engine.assignDefaultButtons();
	HardwareCore.setSeqButtonParam(seqPressedHandler);
	HardwareCore.setEncoderParam(0, setCurrentLine, "Line", 0, 7, 1, currentLine);
	HardwareCore.setEncoderParam(1, setCurrentDrumPattern, "Line", 0, 15, 1, Engine.songSettings.currentDrumPattern);
	refreshSeqLeds();


}


void DrumChannelClass::setCurrentLine(int encoder, int value)
{
	currentLine = static_cast<uint8_t>(value / 100);
	DisplayCore.drawDrumPatternTitles(currentLine);
	refreshSeqLeds();
}

void DrumChannelClass::setCurrentDrumPattern(int encoder, int value)
{
	Engine.songSettings.currentDrumPattern = static_cast<uint8_t>(value / 100);	
	currentDrumPattern = &Engine.songSettings.drumPattern[Engine.songSettings.currentDrumPattern];
	DisplayCore.drawPatternPanel(Engine.songSettings.currentDrumPattern);
	refreshSeqLeds();	

}

void DrumChannelClass::updateStatus()
{
	refreshSeqLeds();
}

void DrumChannelClass::seqPressedHandler(bool pressed, int button)
{	
	uint8_t* string = currentDrumPattern->shots[button];
	if (pressed)
	{
		string[currentLine] = !string[currentLine];		
		refreshSeqLeds();
	}
}

void DrumChannelClass::handle()
{
	bool _fullRedraw = false;
	if (!Engine.isValidScreen)
	{
		DisplayCore.drawDrumPatternBackground();
		DisplayCore.drawDrumPatternTitles(currentLine);
		DisplayCore.drawPatternPanel(Engine.songSettings.currentDrumPattern);
		_fullRedraw = true;
		Engine.isValidScreen = true;
	}	
	
	DisplayCore.drawDrumPattern(currentDrumPattern->shots,
		Engine.songSettings.isPlaying ? Engine.songSettings.pattern.currentStep : -1, _fullRedraw);
}
const char* const string = "BD_01.RAW";
const char* const string2 = "SN_01.RAW";
const char* const string3 = "CL_HH_01.RAW";
void DrumChannelClass::midiUpdate()
{

	volatile uint8_t* drums = currentDrumPattern->shots[Engine.songSettings.pattern.currentStep];
	if (drums[0] > 0)
	{
		float velocity = Engine.songSettings.pattern.isAccent ? 1.0 : random(150)/200.0 + 0.2; //todo humanizer		
		AudioCore.playRawDrum(string, velocity,  0);
	}
	if (drums[1] > 0)
	{
		float velocity = Engine.songSettings.pattern.isAccent ? 1.0 : random(150) / 200.0 + 0.2;
		AudioCore.playRawDrum(string2, velocity,  1);
	}
	if (drums[2] > 0)
	{
		float velocity = Engine.songSettings.pattern.isAccent ? 1.0 : random(150) / 200.0 + 0.2;
		AudioCore.playRawDrum(string3, velocity, 2);
	}

	if (drums[4] > 0)
	{		
		
		AudioCore.drum1On();
	}
	if (drums[5] > 0)
	{	
		AudioCore.drum2On();
	}
	if (drums[6] > 0)
	{
		AudioCore.drum3On();
	}
	if (drums[7] > 0)
	{
		AudioCore.drum4On();
	}

	for (int i = 0; i <= 15; i++) {		
		bool _state = cacheLedStates[i];
		if (Engine.songSettings.isPlaying && Engine.songSettings.pattern.currentStep == i)
		{
			_state = !_state;
		}
		HardwareCore.ledStates[i] = _state;
	}
	
}

void DrumChannelClass::refreshSeqLeds()
{
	
	for (int i = 0; i <= 15; i++) {
		uint8_t* drums = currentDrumPattern->shots[i];
		auto b = drums[currentLine] > 0;
		cacheLedStates[i] = b;
		HardwareCore.ledStates[i] = b;
	}
	
}

bool DrumChannelClass::cacheLedStates[16];
DrumPattern* DrumChannelClass::currentDrumPattern = &Engine.songSettings.drumPattern[Engine.songSettings.currentDrumPattern];
uint8_t DrumChannelClass::currentLine = 0;
