#include <WS2812Serial.h>
#include "SongLoader.h"
#include "knobs.h"
#include "picture.h"
#include "Channel.h"
#include "Enums.h"
#include "InputLeft.h"
#include "WavePlayer.h"
#include "Mixer.h"
#include "Engine.h"

bool isDebug = true;


void log(const char* msg, bool isError)
{
	if (isDebug) {
		DisplayCore.printLn(msg, isError);
	}
	if (Serial) {
		Serial.println(msg);
	}
}

void setup() {	
	DisplayCore.init();
	log("TFT success", false);
	Serial.begin(9600);

	if (Serial)
	{
		log("Serial success", false);
	}
	else
	{
		log("Serial error", true);
	}
	
	HardwareCore.init();
	AudioCore.init();
	log("Audio success", false);	
	DisplayCore.clearAll();
	Engine.init();
}

void loop() {
	Engine.update();	
}
