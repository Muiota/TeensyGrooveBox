// 
// 
// 

#include "HardwareCore.h"

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

void HardwareCoreClass::init()
{
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

	enc_one.write(0.6 * 400);


	SPI.setMOSI(SDCARD_MOSI_PIN);
	SPI.setSCK(SDCARD_SCK_PIN);

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

	//seqLedWrite(13, LOW);

	_sdCardInitialized = SD.begin(SDCARD_CS_PIN);
}

bool HardwareCoreClass::seqButtonRead(uint8_t button_pin)
{
	return mcp.digitalRead(button_pin < 8 ? 7 - button_pin : 23 - button_pin) == 0;	
}

void HardwareCoreClass::seqLedWrite(uint8_t led_pin, bool value)
{
	mcp2.digitalWrite(15 - led_pin, value);
}

int32_t HardwareCoreClass::readEncoder(uint8_t encoder)
{
	switch (encoder)
	{
	case 0:
		return enc_one.read();
	case 1:
		return enc_two.read();
	case 2:
		return enc_three.read();
	}
}

void HardwareCoreClass::writeEncoder(uint8_t encoder, int32_t value)
{
	switch (encoder)
	{
	case 0:
		enc_one.write(value);
	case 1:
		enc_two.write(value);
	case 2:
		enc_three.write(value);
	}
}


HardwareCoreClass HardwareCore;

