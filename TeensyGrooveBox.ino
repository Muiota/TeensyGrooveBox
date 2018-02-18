#include "HardwareCore.h"
#include "DisplayCore.h"
#include <i2c_t3.h>
#include "Adafruit_MCP23017.h"
#include "Encoder.h"

#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "AudioCore.h"

// Basic pin reading and pullup test for the MCP23017 I/O expander
// public domain!

// Connect pin #12 of the expander to Analog 5 (i2c clock)
// Connect pin #13 of the expander to Analog 4 (i2c data)
// Connect pins #15, 16 and 17 of the expander to ground (address selection)
// Connect pin #9 of the expander to 5V (power)
// Connect pin #10 of the expander to ground (common ground)
// Connect pin #18 through a ~10kohm resistor to 5V (reset pin, active low)

// Input #0 is on pin 21 so connect a button or switch from there to ground

Adafruit_MCP23017 mcp;
Adafruit_MCP23017 mcp2;
Encoder enc_one(30, 29);
Encoder enc_two(28, 27);
Encoder enc_three(26, 25);

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

bool isDebug = true;


void log(const char* msg, uint16_t color)
{
	if (isDebug) {
		DisplayCore.printLn(msg, color);		
	}
	if (Serial) {
		Serial.println(msg);
	}
}



void setup() {

	DisplayCore.init();
	log("TFT success", ILI9341_GREEN);

	Serial.begin(9600);

	if (Serial)
	{
		log("Serial success", ILI9341_GREEN);
	}
	else
	{
		log("Serial error", ILI9341_RED);
	}
	
	mcp.begin(0);      // use default address 0
	mcp2.begin(1);


	for (int i = 0; i <= 15; i++) {
		mcp.pinMode(i, INPUT);
		mcp.pullUp(i, HIGH);  // turn on a 100K pullup internally
	}


	for (int i = 0; i <= 15; i++) {
		mcp2.pinMode(i, OUTPUT);
	}

	mcp2.pullUp(0, HIGH);  // turn on a 100K pullup internally

	if (true)
	{
		log("MCP success", ILI9341_GREEN);
	}
	else
	{
		log("MCP error", ILI9341_RED);
	}


	pinMode(31, INPUT_PULLUP);
	pinMode(32, INPUT_PULLUP);
	pinMode(33, INPUT_PULLUP);
	pinMode(34, INPUT_PULLUP);
	pinMode(35, INPUT_PULLUP);
	pinMode(36, INPUT_PULLUP);
	pinMode(24, INPUT_PULLUP);

	//pinMode(13, OUTPUT);  // use the p13 LED as debugging
	pinMode(39, OUTPUT);
	pinMode(15, OUTPUT);
	pinMode(8, OUTPUT);

	//digitalWrite(13, LOW);

	
	enc_one.write(0.6 * 400);

	
	SPI.setMOSI(SDCARD_MOSI_PIN);
	SPI.setSCK(SDCARD_SCK_PIN);
	if (true) //todo
	{
		log("SPI success", ILI9341_GREEN);
	}
	else
	{
		log("SPI error", ILI9341_RED);
	}

	if (SD.begin(SDCARD_CS_PIN))
	{
		log("SD success", ILI9341_GREEN);
	}
	else
	{
		log("SD error", ILI9341_RED);
	}


	AudioCore.init();
	log("Audio success", ILI9341_GREEN);
	

	for (uint8_t i = 0; i <= 15; i++) {
		DisplayCore.drawSequenceButton(i, false);
	}
	DisplayCore.drawEncoder(0, 0);
	DisplayCore.drawEncoder(1, 0);
	DisplayCore.drawEncoder(2, 0);

}

bool current[16];
uint8_t currentEncoder[3];

void loop() {
	// The LED will 'echo' the button


	for (int i = 0; i <= 15; i++) {

		uint8_t buttonPin = i < 8 ? 7 - i : 23 - i;
		bool value = mcp.digitalRead(buttonPin) == 0;
		if (current[i] != value)
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
				}


			}
			current[i] = value;
			uint8_t ledPin = 15 - i;
			mcp2.digitalWrite(ledPin, value);
		}


	}




	//Serial.print(" ");
	for (int i = 0; i <= 2; i++) {
		int32_t one_value;
		switch (i)
		{
		case 0:
			one_value = enc_one.read();
			break;
		case 1:
			one_value = enc_two.read();
			break;
		case 2:
			one_value = enc_three.read();
			break;
		}

		bool needUpdate = false;
		if (one_value < 0)
		{
			one_value = 0;
			needUpdate = true;

		}
		else if (one_value > 400)
		{
			one_value = 400;
			needUpdate = true;
		}

		if (needUpdate)
		{
			switch (i)
			{
			case 0:
				enc_one.write(one_value);
				break;
			case 1:
				enc_two.write(one_value);
				break;
			case 2:
				enc_three.write(one_value);
				break;
			}
		}
		uint8_t one_value_r = one_value / 4;

		if (one_value_r != currentEncoder[i])
		{

			switch (i)
			{
			case 0:
				AudioCore.setVolume(static_cast<float>(one_value_r) / 100);
				
				break;
			case 1:
				//drum2.frequency(30 + one_value_r);
				break;
			case 2:

				break;
			}

			DisplayCore.drawEncoder(i, one_value_r);
			digitalWrite(39, one_value_r);
			//		digitalWrite(8, two_value);
			//	digitalWrite(15, three_value);
			currentEncoder[i] = one_value_r;
		}
	}


	for (int i = 31; i <= 36; i++) {
		uint8_t value = digitalRead(i);
	//	Serial.print(value);
	}

//	Serial.print(digitalRead(24));
//	Serial.println("----------");
	if (Serial) {
		Serial.println(AudioProcessorUsage());
	}

	delay(10);
}
