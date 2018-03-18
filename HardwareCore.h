// HardwareCore.h

#ifndef _HARDWARECORE_h
#define _HARDWARECORE_h

typedef void(*EncoderCallback) (int, int);
typedef void(*ButtonCallback) ();

enum button_type {
	BROWN = 0,
	BLACK = 1,
	GREEN = 2,
	RED = 3,
	ENCODER0 = 4,
	ENCODER1 = 5,
	ENCODER2 = 6,

};

#include <i2c_t3.h>
#include "Adafruit_MCP23017.h"
#include "Encoder.h"

#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


class HardwareCoreClass
{
 protected:
	 boolean _sdCardInitialized;
 public:
	void init();
	bool seqButtonRead(uint8_t button_pin);
	void seqLedWrite(uint8_t led_pin, bool value);
	void setEncoderParam(uint8_t encoder, EncoderCallback callback,
		String title, float min, float max, float step, float currenctValue);
	void setButtonParam(uint8_t button, ButtonCallback callback);
	void update();	
	int32_t readEncoder(uint8_t encoder);	
	void writeEncoder(uint8_t encoder, int32_t value);	
};

extern HardwareCoreClass HardwareCore;

#endif

