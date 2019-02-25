// DisplayCore.h

#ifndef _DISPLAYCORE_h
#define _DISPLAYCORE_h

#include <ILI9341_t3.h>
#include <font_Arial.h>
#include "AudioCore.h"
#include "base.c" 
#include "knobs.c" 
#include "buttons.c" 
#include "Engine.h"


enum song_load_buttons
{
	song_load_buttons_new = 0,
	song_load_buttons_edit = 1,
	song_load_buttons_yes_no = 2	
};

class DisplayCoreClass
{
 protected:
	 static uint16_t getMixerChannelXcoord(uint8_t channel);
	 static void drawChannelIcon(uint8_t channel, bool isActive, uint16_t x);
	 static ILI9341_t3 _tft;
public:
	static uint16_t MAIN_COLOR;// 0xD320; //    /* 255, 165,   0 */
	static uint16_t BORDER_COLOR ; //    /* 255, 165,   0 */
	static uint16_t BORDER_COLOR_DARK; //    /* 255, 165,   0 */
	static uint16_t OFF_COLOR;
	static uint16_t INFO_COLOR;
	static uint16_t SUCCESS_COLOR;
	static uint16_t ACTIVE_COLOR;
	static uint16_t DARK_PANEL_COLOR;
	static uint16_t LIGHT_PANEL_COLOR;

	static uint16_t NONE_COLOR_WAV;
	static uint16_t UNSELECTED_COLOR_WAV;

	static void init();
	static void drawSequenceButton(uint8_t pin, bool value);
	static void drawEncoder(uint8_t encoder, int32_t value, int32_t max, bool isBoth = false);
	static void drawEncoderTitle(uint8_t encoder, String title, bool isActive);
	static uint8_t countDigits(int num);
	static void drawMeterSide(float l, uint16_t x, uint16_t y);	
	static void drawMixerMeter(uint16_t channel, float l, float r);
	static void drawMixerMeterTitle(uint8_t channel, bool isActive);
	static void drawMixerButtons(uint8_t channel, float volume, float balance, bool isActive);
	static void printLn(const char* msg, bool isError);
	static void drawUsage(double usage, uint16_t memory);
	static void drawEqChart(uint16_t x, uint16_t y, double ymin, double ymax, uint16_t len, double fq, double* data);
	static void drawText(const String& song, uint16_t x, uint16_t y, bool isClear = false);
	static void drawTextOpacity(const String& song, uint16_t x, uint16_t y, uint16_t color);
	static void setCursor(uint16_t x, uint16_t y);
	static void drawColoredChar(const char& val, uint16_t color);
	static void drawSongDetails(const String& song);	
	static void drawSongStatus(bool wav_is_playing);	
	static void drawMuteMaster(bool b);
	static void clearAll();
	static void drawStandartBackground();
	static void drawFileListBackground();
	static void drawFileLoadBackground();
	static void drawFileloadPanel(bool withField, uint8_t selectedPart);
	static void drawFileloadButtons(song_load_buttons type);
	static void drawMixerBackground();
	static void disaplaySubMenu();
	static void disaplayLooperTape(uint8_t channel);
	static void drawTapeFrame(uint8_t l, uint8_t r);
	static void drawEqType(uint8_t equalizer);
};

extern DisplayCoreClass DisplayCore;

#endif

