// DisplayCore.h

#ifndef _DISPLAYCORE_h
#define _DISPLAYCORE_h

#include <ILI9341_t3.h>
#include <font_Arial.h>
#include "AudioCore.h"
#include "base.c" 
#include "knobs.c" 
#include "buttons.c" 

class DisplayCoreClass
{
 protected:
	 static uint16_t getMixerChannelXcoord(uint8_t channel);

 public:
	static void init();
	static void drawSequenceButton(uint8_t pin, bool value);
	static void drawEncoder(uint8_t encoder, int32_t value, int32_t max, bool isBoth = false);
	static void drawEncoderTitle(uint8_t encoder, String title, bool isActive);
	static uint8_t countDigits(int num);
	static void drawMeterSide(float l, uint16_t x, uint16_t y);	
	static void drawMixerMeter(uint16_t channel, float l, float r);
	static void drawMixerMeterTitle(uint8_t channel, bool isActive);
	static void drawMixerButtons(uint8_t channel, uint16_t x);
	static void printLn(const char* msg, bool isError);
	static void drawUsage(double usage, uint16_t memory);
	static void drawText(const String& song, uint16_t x, uint16_t y);
	static void drawTextOpacity(const String& song, uint16_t x, uint16_t y, uint16_t color);
	static void drawSongDetails(const String& song);	
	static void drawSongStatus(bool wav_is_playing);	
	static void drawMuteMaster(bool b);
	static void clearAll();
	static void drawStandartBackground();
	static void drawFileloadBackground();	
	static void drawMixerBackground();
	static void disaplaySubMenu();
};

extern DisplayCoreClass DisplayCore;

#endif

