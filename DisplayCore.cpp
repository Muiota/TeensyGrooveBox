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

uint16_t MAIN_COLOR = 0xF487;// 0xD320; //    /* 255, 165,   0 */
uint16_t BORDER_COLOR = 0x7A84; //    /* 255, 165,   0 */
uint16_t BORDER_COLOR_DARK = 0x5180; //    /* 255, 165,   0 */
uint16_t OFF_COLOR = 0x20A1;
uint16_t INFO_COLOR = ILI9341_CYAN;
uint16_t SUCCESS_COLOR = ILI9341_GREEN;
uint16_t ACTIVE_COLOR = 0xFD80;

uint16_t DARK_PANEL_COLOR = 0x3186;
uint16_t LIGHT_PANEL_COLOR = 0x9CD3;
//0xFD80, 0x5A65

const uint16_t METER_HEIGHT = 64;

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

	
	auto valueGauge = value * 100 / max;
	tft.fillRect(x - 24, y + 36, 48, 11, OFF_COLOR);
	if (isBoth)
	{
		tft.fillCircle(x, y, 14, OFF_COLOR);
		tft.setTextColor(MAIN_COLOR);
		
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
			tft.writeRect(x_knob, y_knob, 32, 32, (uint16_t*)knob_parts_top[0]); //knob_empty_top_left
			tft.writeRect(x, y_knob, 32, 32, (uint16_t*)knob_parts_top[1]); //knob_empty_top_right
			tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			tft.writeRect(x_knob, y, 32, 29, (uint16_t*)left_bottom[valueGauge]);	
		} else if (valueGauge <= 12) //11-12
		{
			tft.writeRect(x_knob, y_knob, 32, 28, (uint16_t*)knob_parts_top[0]); //knob_empty_top_left
			tft.writeRect(x_knob, y_knob + 28, 32, 4, (uint16_t*)left_threshold_half[valueGauge - 11]); //left_threshold single row
			tft.writeRect(x, y_knob, 32, 32, (uint16_t*)knob_parts_top[1]); //knob_empty_top_right
			tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			tft.writeRect(x_knob, y, 32, 29, (uint16_t*)left_bottom[valueGauge]); //left_bottom_range
		}
		else if (valueGauge <= 18) //13-18
		{
			tft.writeRect(x_knob, y_knob, 32, 28, (uint16_t*)knob_parts_top[0]); //knob_empty_top_left
			tft.writeRect(x_knob, y_knob + 28, 32, 8, (uint16_t*)left_threshold[valueGauge - 13]); //left_threshold single row
			tft.writeRect(x, y_knob, 32, 32, (uint16_t*)knob_parts_top[1]); //knob_empty_top_right
			tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			tft.writeRect(x_knob, y + 4, 32, 25, (uint16_t*)bottom_half[0]); //knob_full_bottom_left_half
		}
		else if (valueGauge <= 44) //19-44
		{
			tft.writeRect(x_knob, y_knob, 32, 32, (uint16_t*)left_top[valueGauge - 19]); //left_top_range			
			tft.writeRect(x, y_knob, 32, 32, (uint16_t*)knob_parts_top[1]); //knob_empty_top_right
			tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			tft.writeRect(x_knob, y , 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
		} else if (valueGauge <= 51) //45-51
		{
			tft.writeRect(x_knob, y_knob, 28, 32, (uint16_t*)knob_top_half[0]); //knob_full_top_left_half			
			tft.writeRect(x_knob + 28, y_knob, 8, 32, (uint16_t*)top_threshold[valueGauge - 45]); //top_threshold 
			tft.writeRect(x + 4, y_knob, 28, 32, (uint16_t*)knob_top_half[1]); //knob_empty_top_right_half
			tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			tft.writeRect(x_knob, y, 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
		}
		else if (valueGauge <= 53) //52-53
		{
			tft.writeRect(x_knob, y_knob, 28, 32, (uint16_t*)knob_top_half[0]); //knob_full_top_left_half			
			tft.writeRect(x_knob + 28, y_knob, 4, 32, (uint16_t*)threshold_top_half[valueGauge - 52]); //top_threshold half
			tft.writeRect(x , y_knob, 32, 32, (uint16_t*)top_right[valueGauge - 52]); //top right
			tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			tft.writeRect(x_knob, y, 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
		}
		else if (valueGauge <= 76) //54-76
		{
			tft.writeRect(x_knob, y_knob, 32, 32, (uint16_t*)knob_parts_top[2]); //knob_full_top_left					
			tft.writeRect(x, y_knob, 32, 32, (uint16_t*)top_right[valueGauge - 52]); //top right
			tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			tft.writeRect(x_knob, y, 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
		}
		else if (valueGauge <= 76) //54-76
		{
			tft.writeRect(x_knob, y_knob, 32, 32, (uint16_t*)knob_parts_top[2]); //knob_full_top_left					
			tft.writeRect(x, y_knob, 32, 32, (uint16_t*)top_right[valueGauge - 52]); //top right
			tft.writeRect(x, y, 32, 29, (uint16_t*)knob_parts_bottom[1]); //knob_empty_bottom_right
			tft.writeRect(x_knob, y, 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
		}
		else if (valueGauge <= 83) //54-76
		{
			tft.writeRect(x_knob, y_knob, 32, 32, (uint16_t*)knob_parts_top[2]); //knob_full_top_left					
			tft.writeRect(x, y_knob, 32, 28, (uint16_t*)knob_parts_top[3]); //top right
			tft.writeRect(x, y- 4, 32, 8, (uint16_t*)right_threshold[valueGauge - 77]); //right threshold
			tft.writeRect(x, y + 4, 32, 25, (uint16_t*)bottom_half[1]); //knob_empty_bottom_right_half
			tft.writeRect(x_knob, y, 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
		}
		else if (valueGauge <= 85) //84-85
		{
			tft.writeRect(x_knob, y_knob, 32, 32, (uint16_t*)knob_parts_top[2]); //knob_full_top_left					
			tft.writeRect(x, y_knob, 32, 28, (uint16_t*)knob_parts_top[3]); //top right
			tft.writeRect(x, y - 4, 32, 4, (uint16_t*)threshold_right_half[valueGauge - 84]); //right threshold half
			tft.writeRect(x, y , 32, 29, (uint16_t*)bottom_right[valueGauge - 84]); //knob_empty_bottom_right_half
			tft.writeRect(x_knob, y, 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
		}
		else
		{
			tft.writeRect(x_knob, y_knob, 32, 32, (uint16_t*)knob_parts_top[2]); //knob_full_top_left					
			tft.writeRect(x, y_knob, 32, 32, (uint16_t*)knob_parts_top[3]); //top right			
			tft.writeRect(x, y, 32, 29, (uint16_t*)bottom_right[valueGauge - 84]); //knob_empty_bottom_right_half
			tft.writeRect(x_knob, y, 32, 29, (uint16_t*)knob_parts_bottom[0]); //knob_full_bottom_left
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

void DisplayCoreClass::drawChannelIcon(uint8_t channel, bool isActive, uint16_t x)
{
	if (channel == 1)
	{
		tft.writeRect(x + 2, 221, 16, 16, isActive ? (uint16_t*)channels[3] : (uint16_t*)channels[2]);
	}
	else if (channel == 0)
	{
		tft.writeRect(x + 2, 221, 16, 16, isActive ? (uint16_t*)channels[1] : (uint16_t*)channels[0]);
	}
	else if (channel >=8 && channel <= 10)
	{
		tft.writeRect(x + 2, 221, 16, 16, isActive ? (uint16_t*)channels[7] : (uint16_t*)channels[6]);
	}
	else if (channel == 11)
	{
		tft.writeRect(x + 2, 221, 16, 16, isActive ? (uint16_t*)channels[9] : (uint16_t*)channels[8]);
	}
	else if (channel == 7)
	{
		tft.writeRect(x + 2, 221, 16, 16, isActive ? (uint16_t*)channels[11] : (uint16_t*)channels[10]);
	}
	else
	{
		tft.writeRect(x + 2, 221, 16, 16, isActive ? (uint16_t*)channels[5] : (uint16_t*)channels[4]);
	}
}

void DisplayCoreClass::drawMixerMeterTitle(uint8_t channel, bool isActive)
{
	uint16_t x = getMixerChannelXcoord(channel);
	uint16_t y = 154;
	tft.fillRect(x, y, 20, METER_HEIGHT , ILI9341_BLACK);
	tft.fillRect(x + 14, y + 2, 6, METER_HEIGHT - 4, OFF_COLOR);
	tft.drawRect(x, y, 20, METER_HEIGHT, isActive ? ACTIVE_COLOR : BORDER_COLOR);
	drawMixerButtons(channel, x);

	drawChannelIcon(channel, isActive, x);


	

}


void DisplayCoreClass::drawMixerButtons(uint8_t channel, uint16_t x)
{	
	uint16_t ix = x + 2;
	//tft.writeRect(ix, 102, 16, 8, true ? (uint16_t*)leds[1] : (uint16_t*)leds[0]);
	//tft.writeRect(ix, 102 + 9, 16, 8, true ? (uint16_t*)leds[3] : (uint16_t*)leds[2]);
	tft.writeRect(ix, 122, 16, 8, true ? (uint16_t*)leds[1] : (uint16_t*)leds[0]);
	tft.writeRect(ix, 131, 16, 8, true ? (uint16_t*)leds[3] : (uint16_t*)leds[2]);
	tft.writeRect(ix, 52, 16, 8, (uint16_t*)encoder_linear[3]);
	tft.writeRect(ix, 102, 16, 16, (uint16_t*)small_knob_negative[5]);
	//tft.writeRect(x , 124, 20, 20, isActive ? (uint16_t*)red_on : (uint16_t*)off);
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
	tft.setTextColor(isError ? ILI9341_RED : ILI9341_GREEN);
	tft.println(msg);
}

void DisplayCoreClass::drawUsage(double cpu, uint16_t memory)
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

void DisplayCoreClass::drawText(const String& song, uint16_t x, uint16_t y)
{
	//tft.fillRect(x, y, 107, 12, OFF_COLOR);
	tft.setCursor(x + 1, y + 1);
	tft.setTextColor(MAIN_COLOR);
	tft.print(song);
}

void DisplayCoreClass::drawTextOpacity(const String& song, uint16_t x, uint16_t y, uint16_t color)
{
	tft.setCursor(x, y);
	tft.setTextColor(color);	
	tft.print(song);
}

void DisplayCoreClass::setCursor(uint16_t x, uint16_t y)
{
	tft.setCursor(x, y);
}

void DisplayCoreClass::drawColoredChar(const char& val,  uint16_t color)
{		
	tft.setTextColor(color);
	tft.print(val);	
}


void DisplayCoreClass::drawSongDetails(const String& song)
{
	uint16_t x = 3;
	uint16_t y = 70;
	tft.fillRect(x, y, 107, 12, OFF_COLOR);
	tft.setCursor(x + 1, y + 1);
	tft.setTextColor(MAIN_COLOR);
	tft.print(song);	
}


void DisplayCoreClass::drawSongStatus(bool wav_is_playing)
{
	uint16_t x = 100;
	uint16_t y = 5;
	tft.fillRect(x, y, 8, 8, wav_is_playing ? ILI9341_GREEN: OFF_COLOR);
}

void DisplayCoreClass::drawMuteMaster(bool isMute)
{
	uint16_t x = 307;
	uint16_t y = 105;
	tft.fillRect(x, y, 8, 8, isMute ? ILI9341_RED : OFF_COLOR);
}

void DisplayCoreClass::clearAll()
{
	tft.fillScreen(ILI9341_BLACK);	
}

void DisplayCoreClass::drawStandartBackground()
{
	tft.fillRect(8, 20, 308, 74, LIGHT_PANEL_COLOR);
	tft.fillRect(8, 98, 308, 160, DARK_PANEL_COLOR);
}

void DisplayCoreClass::drawFileloadBackground()
{
	tft.fillRect(8, 20, 116, 230, OFF_COLOR);
	tft.fillRect(128, 20, 188, 74, LIGHT_PANEL_COLOR);
}

void DisplayCoreClass::drawFileloadPanel(bool withField, uint8_t selectedPart)
{	
	if (withField)
	{
		tft.fillRect(132, 148, 104, 14, OFF_COLOR);
	} else
	{
		tft.fillRect(128, 98, 188, 160, DARK_PANEL_COLOR);

		for (uint8_t i = 0; i < 8; i++)
		{
			auto selected = selectedPart == i;
			tft.writeRect(132 + 18 * i, 102, 16, 16, (uint16_t*)buttons[selected ? 2 : 7]); //knob_full_top_left		
			tft.setCursor(135 + 18 * i, 105);
			tft.setTextColor(selected ? ILI9341_BLACK : LIGHT_PANEL_COLOR);
			tft.print(char(65+ i));
		}
	}
}

void DisplayCoreClass::drawFileloadButtons(song_load_buttons type)
{
	uint8_t threshold = type == song_load_buttons_new ? 1 : 2;

	for (uint8_t i = 0; i <= 1; i++) {
		uint8_t i1 = i * 80;
		tft.writeRect(146 + i1, 26, 64, 64, (uint16_t*)encoder_background);
		bool active = i < threshold;
		tft.writeRect(148 + i1, 28, 8, 8, (uint16_t*)led_small[active ? 1 : 0]);
		if (active)
		{
			switch (type)
			{
			case song_load_buttons_new:
				tft.writeRect(146 + i1 + 16, 42, 32, 32, (uint16_t*)button_icons[i + 4]);
				break;
			case song_load_buttons_edit:
				tft.writeRect(146 + i1 + 16, 42, 32, 32, (uint16_t*)button_icons[i + 2]);
				break;
			case song_load_buttons_yes_no:
				tft.writeRect(146 + i1 + 16, 42, 32, 32, (uint16_t*)button_icons[i + 6]);
				break;
			}		
		}
	}

}


void DisplayCoreClass::drawMixerBackground()
{
	//tft.writeRect(2, 16, 64, 64, (uint16_t*)picture);
	//tft.fillRect(8, 124 , 308, 116, LIGHT_PANEL_COLOR);
	
	//Панель микшера снизу (метры)
	tft.fillRect(8, 150, 52, 90, DARK_PANEL_COLOR);
	tft.fillRect(64, 150, 140, 90, DARK_PANEL_COLOR);
	tft.fillRect(208, 150, 74, 90, DARK_PANEL_COLOR);
	tft.fillRect(286, 150, 30, 90, DARK_PANEL_COLOR);	

	//Панель микшера посередине (лампы)
	tft.fillRect(8, 98, 52, 48, DARK_PANEL_COLOR);
	tft.fillRect(64, 98, 140, 48, DARK_PANEL_COLOR);
	tft.fillRect(208, 98, 74, 48, DARK_PANEL_COLOR);
	tft.fillRect(286, 98, 30, 48, DARK_PANEL_COLOR);

	//Панель микшера вверху (громкость баланс)
	tft.fillRect(8, 20, 52, 74, LIGHT_PANEL_COLOR);
	tft.fillRect(64, 20, 140, 74, LIGHT_PANEL_COLOR);
	tft.fillRect(208, 20, 74, 74, LIGHT_PANEL_COLOR);
	tft.fillRect(286, 20, 30, 74, LIGHT_PANEL_COLOR);


/*	uint8_t r;
	uint8_t g;
	uint8_t b;
	Serial.println("ac");
	tft.color565toRGB(ACTIVE_COLOR, r, g, b);
	Serial.println(r);
	Serial.println(g);
	Serial.println(b);
	Serial.println("off");
	tft.color565toRGB(OFF_COLOR, r, g, b);
	Serial.println(r);
	Serial.println(g);
	Serial.println(b); */
	
	//Панель микшера вверху (громкость баланс)
	//tft.fillRect(8, 20, 52, 19, DARK_PANEL_COLOR);
	//tft.fillRect(64, 20, 140, 19, DARK_PANEL_COLOR);
	//tft.fillRect(208, 20, 74, 19, DARK_PANEL_COLOR);
	//tft.fillRect(286, 20, 30, 19, DARK_PANEL_COLOR);


	//tft.fillRect(0, 0, 320, 240, 0x2144);
	/*tft.writeRect(16, 66, 16, 16, (uint16_t*)buttons[0]); //knob_full_top_left		
	tft.writeRect(16+18, 66, 16, 16, (uint16_t*)buttons[1]); //knob_full_top_left		
	tft.writeRect(16 + 18*2, 66, 16, 16, (uint16_t*)buttons[2]); //knob_full_top_left			
	tft.writeRect(16 + 18 * 3, 66, 16, 16, (uint16_t*)buttons[3]); //knob_full_top_left			
	tft.writeRect(16 + 18 * 4, 66, 16, 16, (uint16_t*)buttons[4]); //knob_full_top_left			
	tft.writeRect(16 + 18 * 5, 66, 16, 16, (uint16_t*)buttons[5]); //knob_full_top_left			
	tft.writeRect(16 + 18 * 6, 66, 16, 16, (uint16_t*)buttons[6]); //knob_full_top_left			
	tft.writeRect(16 + 18 * 7, 66, 16, 16, (uint16_t*)buttons[7]); //knob_full_top_left			
	tft.setCursor(17, 69);
	tft.setTextColor(ILI9341_BLACK);
	tft.print(16);

	tft.setCursor(17+18, 69);
	tft.setTextColor(ILI9341_BLACK);
	tft.print(14);

	tft.setCursor(17 + 18*2, 69);
	tft.setTextColor(ILI9341_BLACK);
	tft.print(12);
	tft.setCursor(17 + 18 * 3, 69);
	tft.setTextColor(ILI9341_BLACK);
	tft.print(16);
	tft.setCursor(17 + 18 * 4, 69);
	tft.setTextColor(ILI9341_BLACK);
	tft.print(12);
	
	tft.setCursor(17 + 18 * 5, 69);
	tft.setTextColor(ILI9341_BLACK);
	tft.print(16);
	tft.setCursor(17 + 18 * 6, 69);
	tft.setTextColor(ACTIVE_COLOR);
		tft.print(12);
	tft.setCursor(17 + 18 * 7, 69);
	tft.setTextColor(ACTIVE_COLOR);
	tft.print(16); */
}

void DisplayCoreClass::disaplaySubMenu()
{
	tft.fillRect(8, 20, 308, 74, LIGHT_PANEL_COLOR);

	for (uint8_t i = 0; i <= 2; i++) {
		uint8_t i1 = i * 80;
		tft.writeRect(16 + i1, 26, 64, 64, (uint16_t*)encoder_background);
		bool active = i <2 ;
		tft.writeRect(18 + i1, 28, 8, 8, (uint16_t*)led_small[active ? 1 : 0]);
		if (active)
		{
			tft.writeRect(16 + i1 + 16, 42, 32, 32, (uint16_t*)button_icons[i]);
		} 
	}
}

void DisplayCoreClass::disaplayLooperTape(uint8_t channel)
{
	tft.fillRect(8, 100, 308, 119, DARK_PANEL_COLOR);
	tft.writeRect(16, 102, 214, 115, (uint16_t*)tape_back);
	uint16_t x = getMixerChannelXcoord(channel);
	drawChannelIcon(channel, true, x);
}

void DisplayCoreClass::drawTapeFrame(uint8_t l, uint8_t r)
{
	tft.writeRect(59, 151, 26, 26, (uint16_t*)tape_frames[l]);
	tft.writeRect(162, 151, 26, 26, (uint16_t*)tape_frames[r]);
}


DisplayCoreClass DisplayCore;

/*
 * 	for (uint8_t i = 0; i <= 15; i++) {
		DisplayCore.drawSequenceButton(i, false);
	}
 */
