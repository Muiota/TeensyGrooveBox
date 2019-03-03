// HardwareCore.h

#ifndef _HARDWARECORE_h
#define _HARDWARECORE_h

typedef void(*EncoderCallback) (int, int);
typedef void(*ButtonCallback) (bool);
typedef void(*SeqButtonCallback) (bool, int);

enum button_type {
	BTN_BROWN = 0,
	BTN_BLACK = 1,
	BTN_GREEN = 2,
	BTN_RED = 3,
	BTN_ENCODER0 = 4,
	BTN_ENCODER1 = 5,
	BTN_ENCODER2 = 6,
	BTN_SEQUENCER = 7,

};

#include <i2c_t3.h>
#include "Adafruit_MCP23017.h"
#include "Encoder.h"

#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <WS2812Serial.h>


class HardwareCoreClass
{
 protected:
	 static bool _sdCardInitialized;	 	 
	 static Adafruit_MCP23017 _mcpButtons;
	 static Adafruit_MCP23017 _mcpLeds;
	 static Encoder _encOne;
	 static Encoder _encTwo;
	 static Encoder _encThree;
	 static bool _lastLedStates[16];

public:	
	static bool ledStates[16];
	static void init();
	static void setRingLedColor(uint8_t led, int color);
	static void resetButtons();
	static bool panelButtonRead(button_type button);
	static bool seqButtonRead(uint8_t button_pin);
	static void seqLedWrite(uint8_t led_pin, bool value);
	static void setLedEncoder(uint8_t encoder, bool value);
	static void resetEncoders();
	static void setEncoderParam(uint8_t encoder, EncoderCallback callback,
		String title, float min, float max, float step, float currenctValue);
	static void setEncoderValue(uint8_t encoder, float currentValue);
	static void setButtonParam(uint8_t button, ButtonCallback callback);
	static void setSeqButtonParam(SeqButtonCallback callback);
	static void update();
	static int32_t readEncoder(uint8_t encoder);
	static void writeEncoder(uint8_t encoder, int32_t value);
	static void updateLeds();
};

extern HardwareCoreClass HardwareCore;

#endif

