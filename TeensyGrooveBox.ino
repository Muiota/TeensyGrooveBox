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
	
	for (uint8_t i = 0; i <= 15; i++) {
		DisplayCore.drawSequenceButton(i, false);
	}

	DisplayCore.drawEncoder(0, 0, "2");
	DisplayCore.drawEncoder(1, 0, "1");
	DisplayCore.drawEncoder(2, 0, "Master");
	Engine.init();

}

void loop() {
	Engine.update();	
}
