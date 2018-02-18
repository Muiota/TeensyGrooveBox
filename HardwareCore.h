// HardwareCore.h

#ifndef _HARDWARECORE_h
#define _HARDWARECORE_h

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
	int32_t readEncoder(uint8_t encoder);	
	void writeEncoder(uint8_t encoder, int32_t value);	
};

extern HardwareCoreClass HardwareCore;

#endif

