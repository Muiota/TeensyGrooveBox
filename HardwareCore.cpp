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


void emptyEncoderCallback(int e, int x)
{
}

void emptyButtonCallback()
{
}


typedef struct {
	int32_t lastValue = 0;
	int32_t min = 0;
	int32_t max = 400;
	uint32_t step = 1;
	String title = "UNSIGN";
	EncoderCallback callback = emptyEncoderCallback;
} HardwareEncoder;


typedef struct {
	int8_t pin = 0;
	bool pressed = false;	
	ButtonCallback callback = emptyButtonCallback;
} HardwareButton;

HardwareEncoder _currentEncoder[3];
HardwareButton _currentButton[7];



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

	enc_three.write(0.6 * 400);


	SPI.setMOSI(SDCARD_MOSI_PIN);
	SPI.setSCK(SDCARD_SCK_PIN);

	pinMode(31, INPUT_PULLUP); //black button
	_currentButton[BLACK].pin = 31;
	pinMode(32, INPUT_PULLUP); //brown button
	_currentButton[BROWN].pin = 32;
	pinMode(33, INPUT_PULLUP); //green button
	_currentButton[GREEN].pin = 33;
	pinMode(34, INPUT_PULLUP); //red button
	_currentButton[RED].pin = 34;
	pinMode(35, INPUT_PULLUP); //encoder 0 button
	_currentButton[ENCODER0].pin = 35;
	pinMode(36, INPUT_PULLUP); //encoder 2 button
	_currentButton[ENCODER2].pin = 36;
	pinMode(24, INPUT_PULLUP);  //encoder 1 button
	_currentButton[ENCODER1].pin = 24;

	//pinMode(13, OUTPUT);  // use the p13 LED as debugging
	pinMode(39, OUTPUT); // encoder 0 led
	pinMode(15, OUTPUT); //encoder 2 led
	pinMode(8, OUTPUT); //encoder 1 led

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


void HardwareCoreClass::resetEncoders()
{
	for (uint8_t i = 0; i <= 2; i++) {
		HardwareEncoder* item = &_currentEncoder[i];
		item->callback = emptyEncoderCallback;
		item->title = "";
		item->lastValue = 0;
		writeEncoder(i, item->lastValue);
	}
}

void HardwareCoreClass::setEncoderParam(uint8_t encoder, 
	EncoderCallback callback, String title,
	float min, float max, float step, float currentValue)
{

	HardwareEncoder* item = &_currentEncoder[encoder];	
	item->step = static_cast<uint32_t>(step * 100);			
	item->title = title;
	item->min = static_cast<uint32_t>(min* 400 / item->step);
	item->max = static_cast<uint32_t>(max* 400 / item->step);
	item->lastValue = static_cast<uint32_t>(currentValue * 400 / item->step);
	writeEncoder(encoder, item->lastValue);
	item->callback = callback;
	item->callback(encoder, item->lastValue / 4 * item->step);
	Serial.print("enc max ");
	Serial.print(item->max);
	Serial.print("enc step ");
	Serial.print(item->step);
	Serial.print("enc last ");
	Serial.println(item->lastValue);	

}

void HardwareCoreClass::setButtonParam(uint8_t button, ButtonCallback callback)
{
	HardwareButton* item = &_currentButton[button];
	item->callback = callback;
}

//Tick of update cycle
void HardwareCoreClass::update()
{
	for (uint8_t i = 0; i <= 2; i++) {
		int32_t encoderValue = HardwareCore.readEncoder(i);
		HardwareEncoder* item = &_currentEncoder[i];
		bool needUpdate = false;
		if (encoderValue < item->min)
		{
			encoderValue = item->min;
			needUpdate = true;

		}
		else if (encoderValue > item->max)
		{
			encoderValue = item->max;
			needUpdate = true;
		}

		if (needUpdate)
		{
			HardwareCore.writeEncoder(i, encoderValue);
		}
		
	

		if (encoderValue != item->lastValue)
		{				
			int dispalyValue = encoderValue / 4 * item->step;			
			//digitalWrite(39, one_value_r);
			//		seqLedWrite(8, two_value);
			//	seqLedWrite(15, three_value);
			
			
		
			item->callback(i, dispalyValue);			
			item->lastValue = encoderValue;
		}
	}


	for (int i = 0; i < 7; i++) {
		HardwareButton* item = &_currentButton[i];
		uint8_t value = digitalRead(item->pin);
		if (value == 0)
		{

			if (!item->pressed)
			{
				item->pressed = true;
				item->callback();
			}
		}
		else
		{
			item->pressed = false;			
		}
	}

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
		break;
	case 1:
		enc_two.write(value);
		break;
	case 2:
		enc_three.write(value);
		break;
	}
}


HardwareCoreClass HardwareCore;

