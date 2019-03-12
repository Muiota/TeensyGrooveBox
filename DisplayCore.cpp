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






//0xFD80, 0x5A65



void DisplayCoreClass::init()
{
	_tft.begin();
	_tft.setRotation(1);
	//_tft.invertDisplay(false);
	_tft.fillScreen(ILI9341_BLACK);

	_tft.setFont(Arial_9);
	//_tft.setTextSize(3);
	_tft.setScroll(0);
	

}

void DisplayCoreClass::drawSequenceButton(uint8_t pin, bool value)
{
	_tft.drawRect(0 + 32 + pin * 18, 240 - 20, 16, 16, BORDER_COLOR);
	_tft.fillRect(2 + 32 + pin * 18, 240 - 18, 12, 12, value ? MAIN_COLOR : OFF_COLOR);
}



void DisplayCoreClass::drawEncoderTitle(uint8_t encoder, String title, bool isActive)
{
	uint16_t x = 148 + 64 * encoder;
	uint16_t y = 68;

	_tft.fillRect(x - 32, y - 48, 63, 104, ILI9341_BLACK);

	if (!isActive)
	{
		return;
	}

	_tft.fillRect(x - 32, y - 45, 63, 14, OFF_COLOR);
	_tft.setCursor(x - 24, y - 44);
	_tft.setTextColor(INFO_COLOR);
	_tft.print(title);

	_tft.drawRect(x - 26, y + 34, 52, 15, BORDER_COLOR);

	_tft.drawCircle(x, y, 21, ILI9341_BLACK);
	_tft.drawCircle(x, y, 20, ILI9341_BLACK);
	_tft.drawCircle(x, y, 19, BORDER_COLOR_DARK);
	_tft.drawCircle(x, y, 30, BORDER_COLOR_DARK);

}


void DisplayCoreClass::drawEncoder(uint8_t encoder, int32_t value, int32_t max, bool isBoth )
{

	uint16_t x = 148 + 64 * encoder;
	uint16_t y = 68;

	
	auto valueGauge = value * 100 / max;
	_tft.fillRect(x - 24, y + 36, 48, 11, OFF_COLOR);
	if (isBoth)
	{
		_tft.fillCircle(x, y, 14, OFF_COLOR);
		_tft.setTextColor(MAIN_COLOR);
		
		int8_t positive = valueGauge > 0 ? 1: -1;
		auto radians = positive* valueGauge * PI / 124.0;
		auto px = x + 13 * sin(radians)* positive;
		auto py = y - 13 * cos(radians);
		_tft.drawLine(x, y, px, py, MAIN_COLOR);


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
				if (i <= 0 && i >= valueGauge)
				{
					color = MAIN_COLOR;
				}
			}

			
			_tft.drawLine(px1, py1, px2, py2, color);
		}
	}
	else
	{
		if (valueGauge > 100)
		{
			valueGauge = 100;
		} else if (valueGauge < 0)
		{
			valueGauge = 0;
		}
		uint16_t x_knob = x - 32;
		uint16_t y_knob = y - 32;


		if (valueGauge <= 10)  //0 -10
		{
			_tft.writeRect(x_knob, y_knob, 32, 32, (uint16_t*)knob_parts_top[0]); //knob_empty_top_left
			_tft.writeRect(x, y_knob, 32, 32, (uint16_t*)knob_parts_top[1]); //knob_empty_top_right
			_tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			_tft.writeRect(x_knob, y, 32, 29, (uint16_t*)left_bottom[valueGauge]);	
		} else if (valueGauge <= 12) //11-12
		{
			_tft.writeRect(x_knob, y_knob, 32, 28, (uint16_t*)knob_parts_top[0]); //knob_empty_top_left
			_tft.writeRect(x_knob, y_knob + 28, 32, 4, (uint16_t*)left_threshold_half[valueGauge - 11]); //left_threshold single row
			_tft.writeRect(x, y_knob, 32, 32, (uint16_t*)knob_parts_top[1]); //knob_empty_top_right
			_tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			_tft.writeRect(x_knob, y, 32, 29, (uint16_t*)left_bottom[valueGauge]); //left_bottom_range
		}
		else if (valueGauge <= 18) //13-18
		{
			_tft.writeRect(x_knob, y_knob, 32, 28, (uint16_t*)knob_parts_top[0]); //knob_empty_top_left
			_tft.writeRect(x_knob, y_knob + 28, 32, 8, (uint16_t*)left_threshold[valueGauge - 13]); //left_threshold single row
			_tft.writeRect(x, y_knob, 32, 32, (uint16_t*)knob_parts_top[1]); //knob_empty_top_right
			_tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			_tft.writeRect(x_knob, y + 4, 32, 25, (uint16_t*)bottom_half[0]); //knob_full_bottom_left_half
		}
		else if (valueGauge <= 44) //19-44
		{
			_tft.writeRect(x_knob, y_knob, 32, 32, (uint16_t*)left_top[valueGauge - 19]); //left_top_range			
			_tft.writeRect(x, y_knob, 32, 32, (uint16_t*)knob_parts_top[1]); //knob_empty_top_right
			_tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			_tft.writeRect(x_knob, y , 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
		} else if (valueGauge <= 51) //45-51
		{
			_tft.writeRect(x_knob, y_knob, 28, 32, (uint16_t*)knob_top_half[0]); //knob_full_top_left_half			
			_tft.writeRect(x_knob + 28, y_knob, 8, 32, (uint16_t*)top_threshold[valueGauge - 45]); //top_threshold 
			_tft.writeRect(x + 4, y_knob, 28, 32, (uint16_t*)knob_top_half[1]); //knob_empty_top_right_half
			_tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			_tft.writeRect(x_knob, y, 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
		}
		else if (valueGauge <= 53) //52-53
		{
			_tft.writeRect(x_knob, y_knob, 28, 32, (uint16_t*)knob_top_half[0]); //knob_full_top_left_half			
			_tft.writeRect(x_knob + 28, y_knob, 4, 32, (uint16_t*)threshold_top_half[valueGauge - 52]); //top_threshold half
			_tft.writeRect(x , y_knob, 32, 32, (uint16_t*)top_right[valueGauge - 52]); //top right
			_tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			_tft.writeRect(x_knob, y, 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
		}
		else if (valueGauge <= 76) //54-76
		{
			_tft.writeRect(x_knob, y_knob, 32, 32, (uint16_t*)knob_parts_top[2]); //knob_full_top_left					
			_tft.writeRect(x, y_knob, 32, 32, (uint16_t*)top_right[valueGauge - 52]); //top right
			_tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			_tft.writeRect(x_knob, y, 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
		}
		else if (valueGauge <= 76) //54-76
		{
			_tft.writeRect(x_knob, y_knob, 32, 32, (uint16_t*)knob_parts_top[2]); //knob_full_top_left					
			_tft.writeRect(x, y_knob, 32, 32, (uint16_t*)top_right[valueGauge - 52]); //top right
			_tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			_tft.writeRect(x_knob, y, 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
		}
		else if (valueGauge <= 83) //54-76
		{
			_tft.writeRect(x_knob, y_knob, 32, 32, (uint16_t*)knob_parts_top[2]); //knob_full_top_left					
			_tft.writeRect(x, y_knob, 32, 28, (uint16_t*)knob_parts_top[3]); //top right
			_tft.writeRect(x, y- 4, 32, 8, (uint16_t*)right_threshold[valueGauge - 77]); //right threshold
			_tft.writeRect(x, y + 4, 32, 25, (uint16_t*)bottom_half[1]); //knob_empty_bottom_right_half
			_tft.writeRect(x_knob, y, 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
		}
		else if (valueGauge <= 85) //84-85
		{
			_tft.writeRect(x_knob, y_knob, 32, 32, (uint16_t*)knob_parts_top[2]); //knob_full_top_left					
			_tft.writeRect(x, y_knob, 32, 28, (uint16_t*)knob_parts_top[3]); //top right
			_tft.writeRect(x, y - 4, 32, 4, (uint16_t*)threshold_right_half[valueGauge - 84]); //right threshold half
			_tft.writeRect(x, y , 32, 29, (uint16_t*)bottom_right[valueGauge - 84]); //knob_empty_bottom_right_half
			_tft.writeRect(x_knob, y, 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
		}
		else
		{
			_tft.writeRect(x_knob, y_knob, 32, 32, (uint16_t*)knob_parts_top[2]); //knob_full_top_left					
			_tft.writeRect(x, y_knob, 32, 32, (uint16_t*)knob_parts_top[3]); //top right			
			_tft.writeRect(x, y, 32, 29, (uint16_t*)bottom_right[valueGauge - 84]); //knob_empty_bottom_right_half
			_tft.writeRect(x_knob, y, 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
		}
		
	}

	uint8_t shift = countDigits(value);	
	uint8_t exShift = 0;
	if (value < 0) {
		exShift = 4;
	}
	_tft.setCursor(x  + 23 - shift * 7 - exShift, y+ 36);
	_tft.setTextColor(INFO_COLOR);
	_tft.print(value);
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

	_tft.fillRect(xL, yB, 4, hL, ILI9341_BLACK);
	uint16_t cursorL = yB + hL;
	if (cursorL < levelHeightD)
	{
		uint16_t hD = levelHeightD - cursorL;
		_tft.fillRect(xL, cursorL, 4, hD, ILI9341_RED);
		cursorL = cursorL+ hD;
		hD = levelHeightW - levelHeightD;
				
		_tft.fillRect(xL, cursorL, 4, hD, ILI9341_YELLOW);
		cursorL = cursorL + hD;
		hD = yB + levelHeight - levelHeightW;
		_tft.fillRect(xL, cursorL, 4, hD, ILI9341_GREEN);
	} else if (cursorL < levelHeightW)
	{
		uint16_t hD = levelHeightW - cursorL;
		_tft.fillRect(xL, cursorL, 4, hD, ILI9341_YELLOW);		
		cursorL = cursorL + hD;
		hD = yB + levelHeight - levelHeightW;
		_tft.fillRect(xL, cursorL, 4, hD, ILI9341_GREEN);
	}  else
	{
		_tft.fillRect(xL, cursorL, 4, levelL, ILI9341_GREEN);
	}
}


uint16_t DisplayCoreClass::getMixerChannelXcoord(uint8_t channel)
{
	uint16_t x = channel * 22 + 13;
	if (channel == 11)
	{
		x = x + 36;
	}
	else if (channel > 7)
	{
		x = x + 24;
	}
	else if (channel > 1)
	{
		x = x + 12;
	}
	return x;
}

void DisplayCoreClass::drawChannelIcon(uint8_t channel, bool isActive, uint16_t x, uint16_t y)
{
	if (channel == 1)
	{
		_tft.writeRect(x + 2, y, 16, 16, isActive ? const_cast<uint16_t*>(channels[3]) : const_cast<uint16_t*>(channels[2]));
	}
	else if (channel == 0)
	{
		_tft.writeRect(x + 2, y, 16, 16, isActive ? const_cast<uint16_t*>(channels[1]) : const_cast<uint16_t*>(channels[0]));
	}
	else if (channel == 2)
	{
		_tft.writeRect(x + 2, y, 16, 16, isActive ? const_cast<uint16_t*>(channels[13]) : const_cast<uint16_t*>(channels[12]));
	}
	else if (channel >=8 && channel <= 10)
	{
		_tft.writeRect(x + 2, y, 16, 16, isActive ? const_cast<uint16_t*>(channels[7]) : const_cast<uint16_t*>(channels[6]));
	}
	else if (channel == 11)
	{
		_tft.writeRect(x + 2, y, 16, 16, isActive ? const_cast<uint16_t*>(channels[9]) : const_cast<uint16_t*>(channels[8]));
	}
	else if (channel == 7)
	{
		_tft.writeRect(x + 2, y, 16, 16, isActive ? const_cast<uint16_t*>(channels[11]) : const_cast<uint16_t*>(channels[10]));
	}
	else
	{
		_tft.writeRect(x + 2, y, 16, 16, isActive ? const_cast<uint16_t*>(channels[5]) : const_cast<uint16_t*>(channels[4]));
	}
}

void DisplayCoreClass::drawMixerMeterTitle(uint8_t channel, bool isActive)
{
	uint16_t x = getMixerChannelXcoord(channel);
	uint16_t y = 154;
	_tft.fillRect(x, y, 20, METER_HEIGHT , ILI9341_BLACK);
	_tft.fillRect(x + 14, y + 2, 6, METER_HEIGHT - 4, OFF_COLOR);
	_tft.drawRect(x, y, 20, METER_HEIGHT, isActive ? ACTIVE_COLOR : BORDER_COLOR);


	drawChannelIcon(channel, isActive, x, 221);


	

}


void DisplayCoreClass::drawMixerButtons(uint8_t channel, float volume, float balance, bool isActive)
{	
	uint16_t x = getMixerChannelXcoord(channel);
	uint16_t ix = x + 2;
	//_tft.writeRect(ix, 102, 16, 8, true ? (uint16_t*)leds[1] : (uint16_t*)leds[0]);
	//_tft.writeRect(ix, 102 + 9, 16, 8, true ? (uint16_t*)leds[3] : (uint16_t*)leds[2]);
	_tft.writeRect(ix, 122, 16, 8, isActive ? const_cast<uint16_t*>(leds[5]) : const_cast<uint16_t*>(leds[4]));
	_tft.writeRect(ix, 131, 16, 8, false ? const_cast<uint16_t*>(leds[3]) : const_cast<uint16_t*>(leds[2]));
	//_tft.writeRect(ix, 52, 16, 8, (uint16_t*)encoder_linear[3]);
	uint16_t level = volume * 60;


	auto sliderIndex = 0 + (isActive ? 3 : 0);
	if (level == 0)
	{
		sliderIndex = sliderIndex+ 2;
	} else if (level == 60)
	{
		sliderIndex = sliderIndex + 1;
	}

	//_tft.writeRect(ix, 22, 16, 8, (uint16_t*)encoder_linear[3]);
	_tft.writeRect(ix, 82 - level, 16, 8, const_cast<uint16_t*>(encoder_linear[sliderIndex]));
	auto lineColor = (isActive ? 0x3186 : 0x4A69);
	auto topHeight = 59 - level;
	if (topHeight > 0)
	{
		_tft.fillRect(ix, 23, 6, topHeight, LIGHT_PANEL_COLOR); //LIGHT_PANEL_COLOR
		_tft.fillRect(ix + 10, 23, 6, topHeight, LIGHT_PANEL_COLOR); //LIGHT_PANEL_COLOR
		_tft.fillRect(ix + 6, 23, 4, topHeight, lineColor); //LIGHT_PANEL_COLOR
	}

	auto bottomHeight = level - 1;
	if (bottomHeight > 0)
	{
		_tft.fillRect(ix, 90 - level, 6, bottomHeight, LIGHT_PANEL_COLOR);
		_tft.fillRect(ix + 10, 90 - level, 6, bottomHeight, LIGHT_PANEL_COLOR);
		_tft.fillRect(ix + 6, 90 - level, 4, bottomHeight, lineColor);
	}

	
	
	
	
	if (balance == 0)
	{
		_tft.writeRect(ix, 102, 16, 16, const_cast<uint16_t*>(small_knob_center));
	} else if (balance < 0)
	{
		_tft.writeRect(ix, 102, 16, 16, const_cast<uint16_t*>(small_knob_negative[static_cast<uint8_t>(- balance * 9)]));
	} else
	{
		_tft.writeRect(ix, 102, 16, 16, const_cast<uint16_t*>(small_knob_positive[static_cast<uint8_t>(balance * 9)]));
	}

	
	//_tft.writeRect(x , 124, 20, 20, isActive ? (uint16_t*)red_on : (uint16_t*)off);
}

void DisplayCoreClass::drawMixerMeter(uint16_t channel,  float r, float l)
{
	uint16_t x = getMixerChannelXcoord(channel);
	uint16_t y = 154;
	drawMeterSide(l, x, y);
	drawMeterSide(r, x + 6, y);
}

void DisplayCoreClass::printLn(const char * msg, bool isError)
{
	_tft.setTextColor(isError ? ILI9341_RED : ILI9341_GREEN);
	_tft.println(msg);
}

void DisplayCoreClass::drawUsage(double cpu, uint16_t memory)
{
	//uint16_t x = 240;
	//uint16_t y = 3;

	_tft.drawRect(240 + 46, 3, 31, 12, BORDER_COLOR);
	_tft.fillRect(240 + 47, 4, 29, 10, OFF_COLOR);
	_tft.fillRect(240 + 47, 4, 29 * cpu / 100, 10, MAIN_COLOR);
	//_tft.setCursor(x+1, y+1);
	//_tft.setTextColor(MAIN_COLOR);
	//_tft.print(cpu);

	_tft.fillRect(240 + 20, 3, 22, 12, OFF_COLOR);
	_tft.setCursor(240 + 20, 4);
	_tft.setTextColor(MAIN_COLOR);
	_tft.print(memory);
}


void DisplayCoreClass::drawEqChart(uint16_t vx, uint16_t y, double ymin, 
	double ymax, uint16_t len, double fq, double *data)
{
	double scale = ymax - ymin;
	uint16_t height = 96;
	int16_t x = vx + 20;

	_tft.fillRect(vx, y - 2, 20, height + 12, ILI9341_BLACK);
	_tft.setCursor(vx + 1, y - 1);
	_tft.setTextColor(MAIN_COLOR);
	_tft.print(static_cast<int>(ymax));
	
	
	_tft.setCursor(vx + 1 + (ymin < 0 ? -3: 0), y+height - 1);
	_tft.setTextColor(MAIN_COLOR);
	_tft.print(static_cast<int>(ymin));

	_tft.fillRect(x, y - 1, len, height + 2, OFF_COLOR);

	int16_t ya = 0;


	double val = (- ymin) / (scale) * static_cast<double>(height);
	int16_t yb = y + height - static_cast<int>(val);
	_tft.drawLine(x, yb, x + len, yb, BORDER_COLOR_DARK);

	if (ymin < -2 && ymax > 2)
	{
		_tft.setCursor(vx + 8, yb - 4);
		_tft.setTextColor(MAIN_COLOR);
		_tft.print("0");
	}

	double koef = static_cast<double>(len) / 22050;
	int ix = x+ 5000 * koef;
	_tft.drawLine(ix, y, ix, y + height, BORDER_COLOR_DARK);
	 ix = x + 10000 * koef;
	_tft.drawLine(ix, y, ix, y + height, BORDER_COLOR_DARK);
	 ix = x + 15000 * koef;
	_tft.drawLine(ix, y, ix, y + height, BORDER_COLOR_DARK);
	ix = x + 20000 * koef;
	_tft.drawLine(ix, y, ix, y + height, BORDER_COLOR_DARK);

	ix = x + fq * koef;
	_tft.drawLine(ix, y, ix, y + height, BORDER_COLOR);


	for (uint16_t idx = 0; idx < len; idx++)
	{
		int16_t xa = x + idx - 1;
		int16_t xb = x + idx;

		double val = (data[idx] - ymin) / (scale)*  static_cast<double>(height);

		yb = y + height - static_cast<int>(val);
		if (ya > 0)
		{
			_tft.drawLine(xa, ya, xb, yb, MAIN_COLOR);
		}
		ya = yb;
	}
	
}

void DisplayCoreClass::drawText(const String& song, uint16_t x, uint16_t y, bool isClear)
{
	if (isClear)
	{
		_tft.fillRect(x, y, 107, 12, OFF_COLOR);
	}
	_tft.setCursor(x + 1, y + 1);
	_tft.setTextColor(MAIN_COLOR);
	_tft.print(song);
}

void DisplayCoreClass::drawTextOpacity(const String& song, uint16_t x, uint16_t y, uint16_t color)
{
	_tft.setCursor(x, y);
	_tft.setTextColor(color);	
	_tft.print(song);
}

void DisplayCoreClass::setCursor(uint16_t x, uint16_t y)
{
	_tft.setCursor(x, y);
}

void DisplayCoreClass::drawColoredChar(const char& val,  uint16_t color)
{		
	_tft.setTextColor(color);
	_tft.print(val);	
}


void DisplayCoreClass::drawSongDetails(const String& song)
{
	uint16_t x = 3;
	uint16_t y = 70;
	_tft.fillRect(x, y, 107, 12, OFF_COLOR);
	_tft.setCursor(x + 1, y + 1);
	_tft.setTextColor(MAIN_COLOR);
	_tft.print(song);	
}


void DisplayCoreClass::drawSongStatus(bool wav_is_playing)
{
	uint16_t x = 100;
	uint16_t y = 5;
	_tft.fillRect(x, y, 8, 8, wav_is_playing ? ILI9341_GREEN: OFF_COLOR);
}

void DisplayCoreClass::drawMuteMaster(bool isMute)
{
	uint16_t x = 307;
	uint16_t y = 105;
	_tft.fillRect(x, y, 8, 8, isMute ? ILI9341_RED : OFF_COLOR);
}

void DisplayCoreClass::clearAll()
{
	Serial.println("Clear screen");
	_tft.fillScreen(ILI9341_BLACK);	

	//clear drum pattern cache
	for (uint8_t s = 0; s < 16; s++) {
		uint8_t* line = drumPatternCache[s];		
		for (uint8_t d = 0; d < 8; d++) {
			line[d] = false;
		}
	}

}

void DisplayCoreClass::drawStandartBackground()
{
	_tft.fillRect(8, 20, 308, 74, LIGHT_PANEL_COLOR);
	_tft.fillRect(8, 98, 308, 160, DARK_PANEL_COLOR);
}

void DisplayCoreClass::drawFileListBackground()
{
	_tft.fillRect(8, 20, 116, 230, OFF_COLOR);
}

void DisplayCoreClass::drawFileLoadBackground()
{
	_tft.fillRect(128, 20, 188, 74, LIGHT_PANEL_COLOR);
}

void DisplayCoreClass::drawFileloadPanel(bool withField, uint8_t selectedPart)
{	
	if (withField)
	{
		_tft.fillRect(132, 148, 104, 14, OFF_COLOR);
	} else
	{
		_tft.fillRect(128, 98, 188, 160, DARK_PANEL_COLOR);

		for (uint8_t i = 0; i < 8; i++)
		{
			auto selected = selectedPart == i;
			_tft.writeRect(132 + 18 * i, 102, 16, 16, const_cast<uint16_t*>(buttons[selected ? 2 : 7])); //knob_full_top_left		
			_tft.setCursor(135 + 18 * i, 105);
			_tft.setTextColor(selected ? ILI9341_BLACK : LIGHT_PANEL_COLOR);
			_tft.print(char(65+ i));
		}
	}
}

void DisplayCoreClass::drawFileloadButtons(song_load_buttons type)
{
	uint8_t threshold = type == song_load_buttons_new ? 1 : 2;

	for (uint8_t i = 0; i <= 1; i++) {
		uint8_t i1 = i * 80;
		_tft.writeRect(146 + i1, 26, 64, 64, (uint16_t*)encoder_background);
		bool active = i < threshold;
		_tft.writeRect(148 + i1, 28, 8, 8, (uint16_t*)led_small[active ? 1 : 0]);
		if (active)
		{
			switch (type)
			{
			case song_load_buttons_new:
				_tft.writeRect(146 + i1 + 16, 42, 32, 32, (uint16_t*)button_icons[i + 4]);
				break;
			case song_load_buttons_edit:
				_tft.writeRect(146 + i1 + 16, 42, 32, 32, (uint16_t*)button_icons[i + 2]);
				break;
			case song_load_buttons_yes_no:
				_tft.writeRect(146 + i1 + 16, 42, 32, 32, (uint16_t*)button_icons[i + 6]);
				break;
			}		
		}
	}

}


void DisplayCoreClass::drawMixerBackground()
{
	//_tft.writeRect(2, 16, 64, 64, (uint16_t*)picture);
	//_tft.fillRect(8, 124 , 308, 116, LIGHT_PANEL_COLOR);
	
	//Панель микшера снизу (метры)
	_tft.fillRect(8, 150, 52, 90, DARK_PANEL_COLOR);
	_tft.fillRect(64, 150, 140, 90, DARK_PANEL_COLOR);
	_tft.fillRect(208, 150, 74, 90, DARK_PANEL_COLOR);
	_tft.fillRect(286, 150, 30, 90, DARK_PANEL_COLOR);	

	//Панель микшера посередине (лампы)
	_tft.fillRect(8, 98, 52, 48, DARK_PANEL_COLOR);
	_tft.fillRect(64, 98, 140, 48, DARK_PANEL_COLOR);
	_tft.fillRect(208, 98, 74, 48, DARK_PANEL_COLOR);
	_tft.fillRect(286, 98, 30, 48, DARK_PANEL_COLOR);

	//Панель микшера вверху (громкость баланс)
	_tft.fillRect(8, 20, 52, 74, LIGHT_PANEL_COLOR);
	_tft.fillRect(64, 20, 140, 74, LIGHT_PANEL_COLOR);
	_tft.fillRect(208, 20, 74, 74, LIGHT_PANEL_COLOR);
	_tft.fillRect(286, 20, 30, 74, LIGHT_PANEL_COLOR);


/*	uint8_t r;
	uint8_t g;
	uint8_t b;
	Serial.println("ac");
	_tft.color565toRGB(ACTIVE_COLOR, r, g, b);
	Serial.println(r);
	Serial.println(g);
	Serial.println(b);
	Serial.println("off");
	_tft.color565toRGB(OFF_COLOR, r, g, b);
	Serial.println(r);
	Serial.println(g);
	Serial.println(b); */
	
	//Панель микшера вверху (громкость баланс)
	//_tft.fillRect(8, 20, 52, 19, DARK_PANEL_COLOR);
	//_tft.fillRect(64, 20, 140, 19, DARK_PANEL_COLOR);
	//_tft.fillRect(208, 20, 74, 19, DARK_PANEL_COLOR);
	//_tft.fillRect(286, 20, 30, 19, DARK_PANEL_COLOR);


	//_tft.fillRect(0, 0, 320, 240, 0x2144);
	/*_tft.writeRect(16, 66, 16, 16, (uint16_t*)buttons[0]); //knob_full_top_left		
	_tft.writeRect(16+18, 66, 16, 16, (uint16_t*)buttons[1]); //knob_full_top_left		
	_tft.writeRect(16 + 18*2, 66, 16, 16, (uint16_t*)buttons[2]); //knob_full_top_left			
	_tft.writeRect(16 + 18 * 3, 66, 16, 16, (uint16_t*)buttons[3]); //knob_full_top_left			
	_tft.writeRect(16 + 18 * 4, 66, 16, 16, (uint16_t*)buttons[4]); //knob_full_top_left			
	_tft.writeRect(16 + 18 * 5, 66, 16, 16, (uint16_t*)buttons[5]); //knob_full_top_left			
	_tft.writeRect(16 + 18 * 6, 66, 16, 16, (uint16_t*)buttons[6]); //knob_full_top_left			
	_tft.writeRect(16 + 18 * 7, 66, 16, 16, (uint16_t*)buttons[7]); //knob_full_top_left			
	_tft.setCursor(17, 69);
	_tft.setTextColor(ILI9341_BLACK);
	_tft.print(16);

	_tft.setCursor(17+18, 69);
	_tft.setTextColor(ILI9341_BLACK);
	_tft.print(14);

	_tft.setCursor(17 + 18*2, 69);
	_tft.setTextColor(ILI9341_BLACK);
	_tft.print(12);
	_tft.setCursor(17 + 18 * 3, 69);
	_tft.setTextColor(ILI9341_BLACK);
	_tft.print(16);
	_tft.setCursor(17 + 18 * 4, 69);
	_tft.setTextColor(ILI9341_BLACK);
	_tft.print(12);
	
	_tft.setCursor(17 + 18 * 5, 69);
	_tft.setTextColor(ILI9341_BLACK);
	_tft.print(16);
	_tft.setCursor(17 + 18 * 6, 69);
	_tft.setTextColor(ACTIVE_COLOR);
		_tft.print(12);
	_tft.setCursor(17 + 18 * 7, 69);
	_tft.setTextColor(ACTIVE_COLOR);
	_tft.print(16); */
}


void DisplayCoreClass::drawDrumPatternBackground()
{
	//Панель микшера снизу (метры)
	_tft.fillRect(8, 94, 320, 132, DARK_PANEL_COLOR);	

}

void DisplayCoreClass::drawDrumPatternTitles(uint8_t currentLine)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		_tft.setCursor(11, 98 + 16 * i);
		auto isActive = currentLine == i;
		_tft.setTextColor(isActive ? MAIN_COLOR : BORDER_COLOR_DARK);
		_tft.print(DRUM_TYPES[i]);
	}
}

void DisplayCoreClass::disaplaySubMenu()
{
	_tft.fillRect(8, 20, 308, 74, LIGHT_PANEL_COLOR);

	for (uint8_t i = 0; i <= 2; i++) {
		uint8_t i1 = i * 80;
		_tft.writeRect(16 + i1, 26, 64, 64, const_cast<uint16_t*>(encoder_background));
		bool active = i <2 ;
		_tft.writeRect(18 + i1, 28, 8, 8, const_cast<uint16_t*>(led_small[active ? 1 : 0]));
		if (active)
		{
			_tft.writeRect(16 + i1 + 16, 42, 32, 32, const_cast<uint16_t*>(button_icons[i]));
		} 
	}
}

void DisplayCoreClass::disaplayLooperTape(uint8_t channel)
{
	_tft.fillRect(8, 100, 308, 121, DARK_PANEL_COLOR);
	_tft.writeRect(16, 103, 214, 115, const_cast<uint16_t*>(tape_back));
	uint16_t x = getMixerChannelXcoord(channel);
	drawChannelIcon(channel, true, x, 221);
}

void DisplayCoreClass::drawTapeFrame(uint8_t l, uint8_t r)
{
	_tft.writeRect(59, 152, 26, 26, const_cast<uint16_t*>(tape_frames[l]));
	_tft.writeRect(162, 152, 26, 26, const_cast<uint16_t*>(tape_frames[r]));
}

void DisplayCoreClass::drawEqType(uint8_t equalizer)
{
	_tft.fillRect(10, 24, 92, 87, DARK_PANEL_COLOR);
	for (uint8_t i = 0; i < 7; i++)
	{		
		_tft.setCursor(12, 26 + 12 * i);
		auto isActive = equalizer == i;
		_tft.setTextColor(isActive ? MAIN_COLOR : BORDER_COLOR_DARK);
		_tft.print(EQ_TYPES[i]);
	}
}

void DisplayCoreClass::drawDrumPattern(uint8_t data[16][8], int8_t currentPosition,  bool fullRedraw)
{
	for (uint8_t s = 0; s < 16; s++) {	
		bool isCurrent = currentPosition == s;
		uint8_t* proposedLine = data[s];
		uint8_t* previousLine = drumPatternCache[s];
		auto x = 58 + (s << 4);	
		for (uint8_t d = 0; d < 8; d++) {
			uint8_t proposedValue = proposedLine[d];
			auto isActive = proposedValue > 0;
			if (isCurrent)
			{
				proposedValue = proposedValue << 4;
			}

			uint8_t previousValue = previousLine[d];
			if (fullRedraw || proposedValue != previousValue)
			{			
				uint16_t* pcolors;
				if (isActive)
				{
					pcolors = isCurrent ? const_cast<uint16_t*>(leds[1]) : const_cast<uint16_t*>(leds[5]);
				}
				else
				{
					pcolors = const_cast<uint16_t*>(leds[4]);
				}
				_tft.writeRect(x, 100 + (d << 4), 16, 8, pcolors);
				previousLine[d] = proposedValue;
			}
		}
	}	
}

void DisplayCoreClass::drawPatternPanel(uint8_t selectedPart)
{
	uint8_t selectedValue = selectedPart + 1;
	for (uint8_t i = 1; i <= 8; i++)
	{
		auto selected = selectedValue == i;
		_tft.writeRect(150 + 18 * i, 22, 16, 16, const_cast<uint16_t*>(buttons[selected ? 2 : 7])); //knob_full_top_left		
		_tft.setCursor(155 + 18 * i, 25);
		_tft.setTextColor(selected ? ILI9341_BLACK : LIGHT_PANEL_COLOR);
		_tft.print(i);

	}

	for (uint8_t i = 9; i <= 16; i++)
	{
		auto selected = selectedValue == i;		
		_tft.writeRect(6 + 18 * i, 40, 16, 16, const_cast<uint16_t*>(buttons[selected ? 2 : 7])); //knob_full_top_left		
		uint8_t shift = i <= 9 ? 0 : 4;
		_tft.setCursor(11 + 18 * i - shift, 43);
		_tft.setTextColor(selected ? ILI9341_BLACK : LIGHT_PANEL_COLOR);
		_tft.print(i);

	}

}

void DisplayCoreClass::drawSequencerBackground()
{
	_tft.fillRect(8, 100, 300, 130, DARK_PANEL_COLOR);
}

void DisplayCoreClass::drawSequencerIcons(uint8_t channel)
{
	for (uint8_t i = 2; i <= 7; i++)
	{		
		drawChannelIcon(i, channel == i, 8, 70 + i * 18);
	}
}

ILI9341_t3 DisplayCoreClass::_tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);

uint16_t DisplayCoreClass::MAIN_COLOR = 0xF487;// 0xD320; //    /* 255, 165,   0 */
uint16_t DisplayCoreClass::BORDER_COLOR = 0x7A84; //    /* 255, 165,   0 */
uint16_t DisplayCoreClass::BORDER_COLOR_DARK = 0x5180; //    /* 255, 165,   0 */
uint16_t DisplayCoreClass::OFF_COLOR = 0x20A1;
uint16_t DisplayCoreClass::INFO_COLOR = ILI9341_CYAN;
uint16_t DisplayCoreClass::SUCCESS_COLOR = ILI9341_GREEN;
uint16_t DisplayCoreClass::ACTIVE_COLOR = 0xFD80;

uint16_t DisplayCoreClass::DARK_PANEL_COLOR = 0x3186;
uint16_t DisplayCoreClass::LIGHT_PANEL_COLOR = 0x9CD3;

uint16_t DisplayCoreClass::NONE_COLOR_WAV = 0x4A18;
uint16_t DisplayCoreClass::UNSELECTED_COLOR_WAV = 0x4A28;

String DisplayCoreClass::EQ_TYPES[7] = { "LOW PASS",
"HIGH PASS",
"BAND PASS",
"NOTCH",
"PEAK",
"LOW SHELF",
"HIGH SHELF" };

 String DisplayCoreClass::DRUM_TYPES[8] ={ "BASS",
"SNARE",
"HIHAT",
"CRASH",
"FX 1",
"FX 2",
"FX 3",
"FX 4" };;

uint8_t DisplayCoreClass::drumPatternCache[16][8];

DisplayCoreClass DisplayCore;

/*
 * 	for (uint8_t i = 0; i <= 15; i++) {
		DisplayCore.drawSequenceButton(i, false);
	}
 */
