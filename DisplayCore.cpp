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

const uint16_t METER_HEIGHT = 90;

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


void DisplayCoreClass::drawEncoderTitle(uint8_t encoder, String title, bool isActive)
{
	uint16_t x = 148 + 64 * encoder;
	uint16_t y = 68;

	tft.fillRect(x - 32, y - 48, 63, 104, ILI9341_BLACK);

	if (!isActive)
	{
		return;
	}

	tft.fillRect(x - 32, y - 45, 63, 14, OFF_COLOR);
	tft.setCursor(x - 24, y - 44);
	tft.setTextColor(INFO_COLOR);
	tft.print(title);

	tft.drawRect(x - 26, y + 34, 52, 15, BORDER_COLOR);

	tft.drawCircle(x, y, 21, ILI9341_BLACK);
	tft.drawCircle(x, y, 20, ILI9341_BLACK);
	tft.drawCircle(x, y, 19, BORDER_COLOR_DARK);
	tft.drawCircle(x, y, 30, BORDER_COLOR_DARK);

}


void DisplayCoreClass::drawEncoder(uint8_t encoder, int32_t value, int32_t max, bool isBoth )
{

	uint16_t x = 148 + 64 * encoder;
	uint16_t y = 68;

	tft.fillCircle(x, y, 14, OFF_COLOR);
	tft.setTextColor(MAIN_COLOR);	
	tft.fillRect(x - 24, y+ 36, 48, 11, OFF_COLOR);
	auto valueGauge = value * 100 / max;

	if (isBoth)
	{
		int8_t positive = valueGauge > 0 ? 1: -1;
		auto radians = positive* valueGauge * PI / 124.0;
		auto px = x + 13 * sin(radians)* positive;
		auto py = y - 13 * cos(radians);
		tft.drawLine(x, y, px, py, MAIN_COLOR);


		for (int8_t i = -100; i < 100; i = i + 6)
		{
			bool pos = i >= 0 ? 1 : -1;
			auto r = pos * i * PI / 124.0;
			auto px1 = x + 20 * sin(r)*pos;
			auto py1 = y - 20 * cos(r);
			auto px2 = x + 28 * sin(r) *pos;
			auto py2 = y - 28 * cos(r);
			auto color = OFF_COLOR;
			if (positive == 1)
			{
				if (i >= 0 && i <= valueGauge)
				{
					color = MAIN_COLOR;
				}
			} else 
			{
				Serial.println(valueGauge);
				Serial.println("=");
				Serial.println(i);
				Serial.println("-");
				if (i <= 0 && i >= valueGauge)
				{
					color = MAIN_COLOR;
				}
			}

			
			tft.drawLine(px1, py1, px2, py2, color);
		}
	}
	else
	{

		auto radians =  valueGauge * PI / 62 + PI / 6 * 4;
		auto px = x + 13 * cos(radians);
		auto py = y + 13 * sin(radians);
		tft.drawLine(x, y, px, py, MAIN_COLOR);


		for (uint8_t i = 0; i < 100; i = i + 3)
		{
			auto r =  i * PI / 62 + PI / 6 * 4;
			auto px1 = x + 20 * cos(r);
			auto py1 = y + 20 * sin(r);
			auto px2 = x + 28 * cos(r);
			auto py2 = y + 28 * sin(r);
			auto color = i <= valueGauge ? MAIN_COLOR : OFF_COLOR;
			tft.drawLine(px1, py1, px2, py2, color);
		}
	}

	uint8_t shift = countDigits(value);	
	uint8_t exShift = 0;
	if (value < 0) {
		exShift = 4;
	}
	tft.setCursor(x  + 23 - shift * 7 - exShift, y+ 36);
	tft.setTextColor(INFO_COLOR);
	tft.print(value);
}

uint8_t DisplayCoreClass::countDigits(int num) {
	uint8_t count = 1;
	num = num / 10;
	while (num) {
		count++;
		num = num / 10;		
	}
	return count;
}


void DisplayCoreClass::drawMeterSide(float l, uint16_t x, uint16_t y)
{
	uint16_t levelHeight = METER_HEIGHT - 4;
	uint16_t levelL = l* levelHeight ; // bottom
	
	uint16_t xL = x + 2;
	uint16_t yB = y + 2;
	uint16_t hL = levelHeight - levelL;

	uint16_t levelHeightW = yB + 0.3 * levelHeight;
	uint16_t levelHeightD = yB + 0.1 * levelHeight;

	tft.fillRect(xL, yB, 4, hL, ILI9341_BLACK);
	uint16_t cursorL = yB + hL;
	if (cursorL < levelHeightD)
	{
		uint16_t hD = levelHeightD - cursorL;
		tft.fillRect(xL, cursorL, 4, hD, ILI9341_RED);
		cursorL = cursorL+ hD;
		hD = levelHeightW - levelHeightD;
				
		tft.fillRect(xL, cursorL, 4, hD, ILI9341_YELLOW);
		cursorL = cursorL + hD;
		hD = yB + levelHeight - levelHeightW;
		tft.fillRect(xL, cursorL, 4, hD, ILI9341_GREEN);
	} else if (cursorL < levelHeightW)
	{
		uint16_t hD = levelHeightW - cursorL;
		tft.fillRect(xL, cursorL, 4, hD, ILI9341_YELLOW);		
		cursorL = cursorL + hD;
		hD = yB + levelHeight - levelHeightW;
		tft.fillRect(xL, cursorL, 4, hD, ILI9341_GREEN);
	}  else
	{
		tft.fillRect(xL, cursorL, 4, levelL, ILI9341_GREEN);
	}
}


void DisplayCoreClass::drawMeterTitle(uint8_t channel, bool isActive)
{
	uint16_t x = channel * 32 + 15;
	uint16_t y = 128;
	tft.fillRect(x + 14, y + 2, 14, METER_HEIGHT - 4, OFF_COLOR);
	tft.drawRect(x, y, 30, METER_HEIGHT, isActive ? ILI9341_CYAN : BORDER_COLOR);	
}

void DisplayCoreClass::drawMeter(uint16_t channel,  float r, float l)
{
	uint16_t x = channel * 32 + 15;
	uint16_t y = 128;
	drawMeterSide(l, x, y);
	drawMeterSide(r, x + 6, y);
}

void DisplayCoreClass::printLn(const char * msg, bool isError)
{
	tft.setTextColor(isError ? ILI9341_RED : ILI9341_GREEN);
	tft.println(msg);
}

void DisplayCoreClass::drawUsage(double cpu, double memory)
{
	uint16_t x = 240;
	uint16_t y = 3;
	tft.fillRect(x, y, 86, 12, OFF_COLOR);
	tft.setCursor(x+1, y+1);
	tft.setTextColor(MAIN_COLOR);
	tft.print(cpu);

	tft.setCursor(x +44, y + 1);
	tft.setTextColor(MAIN_COLOR);
	tft.print(memory);
}

void DisplayCoreClass::drawSongName(const String& song)
{
	uint16_t x = 3;
	uint16_t y = 50;
	tft.fillRect(x, y, 107, 12, OFF_COLOR);
	tft.setCursor(x + 1, y + 1);
	tft.setTextColor(MAIN_COLOR);
	tft.print(song);
}

void DisplayCoreClass::drawSongStatus(bool wav_is_playing)
{
	uint16_t x = 100;
	uint16_t y = 52;
	tft.fillRect(x, y, 8, 8, wav_is_playing ? ILI9341_GREEN: OFF_COLOR);
}

void DisplayCoreClass::drawMuteMaster(bool isMute)
{
	uint16_t x = 307;
	uint16_t y = 105;
	tft.fillRect(x, y, 8, 8, isMute ? ILI9341_RED : OFF_COLOR);
}


DisplayCoreClass DisplayCore;

