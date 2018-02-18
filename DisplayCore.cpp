// 
// 
// 

#include "DisplayCore.h"


#define TFT_DC      20
#define TFT_CS      21
#define TFT_RST    255  // 255 = unused, connect to 3.3V
#define TFT_MOSI     7
#define TFT_SCLK    14
#define TFT_MISO    12
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);

uint16_t MAIN_COLOR = 0xD320; //    /* 255, 165,   0 */
uint16_t BORDER_COLOR = 0x7A84; //    /* 255, 165,   0 */
uint16_t BORDER_COLOR_DARK = 0x5180; //    /* 255, 165,   0 */
uint16_t OFF_COLOR = 0x20A1;
uint16_t INFO_COLOR = ILI9341_CYAN;
uint16_t SUCCESS_COLOR = ILI9341_GREEN;

void DisplayCoreClass::init()
{
	tft.begin();
	tft.setRotation(1);
	tft.invertDisplay(false);
	tft.fillScreen(ILI9341_BLACK);

	tft.setFont(Arial_9);
	//tft.setTextSize(3);
	tft.setScroll(0);

}

void DisplayCoreClass::drawSequenceButton(uint8_t pin, bool value)
{
	tft.drawRect(0 + 32 + pin * 18, 240 - 20, 16, 16, BORDER_COLOR);
	tft.fillRect(2 + 32 + pin * 18, 240 - 18, 12, 12, value ? MAIN_COLOR : OFF_COLOR);
}

void DisplayCoreClass::drawEncoder(uint8_t encoder, int value)
{
	uint16_t x = 148 + 64 * encoder;
	uint16_t y = 32;

	tft.fillCircle(x, y, 14, OFF_COLOR);
	tft.setTextColor(MAIN_COLOR);
	tft.drawRect(x - 16, 66, 32, 15, BORDER_COLOR);
	tft.fillRect(x - 14, 68, 28, 11, OFF_COLOR);


	auto radians = value * PI / 62 + PI / 6 * 4;
	auto px = x + 13 * cos(radians);
	auto py = y + 13 * sin(radians);
	tft.drawLine(x, y, px, py, MAIN_COLOR);


	for (uint8_t i = 0; i < 100; i = i + 3)
	{
		auto r = i * PI / 62 + PI / 6 * 4;
		auto px1 = x + 20 * cos(r);
		auto py1 = y + 20 * sin(r);
		auto px2 = x + 28 * cos(r);
		auto py2 = y + 28 * sin(r);
		auto color = i <= value ? MAIN_COLOR : OFF_COLOR;
		tft.drawLine(px1, py1, px2, py2, color);
	}
	tft.drawCircle(x, y, 21, ILI9341_BLACK);
	tft.drawCircle(x, y, 20, ILI9341_BLACK);
	tft.drawCircle(x, y, 19, BORDER_COLOR_DARK);
	tft.drawCircle(x, y, 30, BORDER_COLOR_DARK);

	uint8_t shift = 0;
	if (value >= 10)
	{
		shift = 1;
		if (value >= 100)
		{
			shift = 2;
		}
	}
	tft.setCursor(154 + 64 * encoder - shift * 7, 68);
	tft.setTextColor(INFO_COLOR);
	tft.print(value);
}

void DisplayCoreClass::printLn(const char * msg, bool isError)
{
	tft.setTextColor(isError ? ILI9341_RED : ILI9341_GREEN);
	tft.println(msg);
}


DisplayCoreClass DisplayCore;

