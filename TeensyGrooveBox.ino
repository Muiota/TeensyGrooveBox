#include "Audio.h"
#include "AudioCoreClass.h"
#include <i2c_t3.h>
#include "Adafruit_MCP23017.h"
#include "Encoder.h"
#include <ILI9341_t3.h>
#include <font_Arial.h>

#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


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

#define TFT_DC      20
#define TFT_CS      21
#define TFT_RST    255  // 255 = unused, connect to 3.3V
#define TFT_MOSI     7
#define TFT_SCLK    14
#define TFT_MISO    12
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);







bool isDebug = true;
uint16_t MAIN_COLOR = 0xD320; //    /* 255, 165,   0 */
uint16_t BORDER_COLOR = 0x7A84; //    /* 255, 165,   0 */
uint16_t BORDER_COLOR_DARK = 0x5180; //    /* 255, 165,   0 */
uint16_t OFF_COLOR = 0x20A1;
uint16_t INFO_COLOR = ILI9341_CYAN;
uint16_t SUCCESS_COLOR = ILI9341_GREEN;
  


void log(const char* msg, uint16_t color)
{
	if (isDebug) {
		tft.setTextColor(color);
		tft.println(msg);
	}
	if (Serial.available() > 0) {
		Serial.println(msg);
	}
}

void drawSequenceButton(uint8_t pin, bool value)
{
	tft.drawRect(0 + 32 + pin * 18, 240 - 20, 16, 16, BORDER_COLOR);
	tft.fillRect(2 + 32 + pin * 18, 240 - 18, 12, 12, value ? MAIN_COLOR :OFF_COLOR);	
}

void drawEncoder(uint8_t encoder, uint8_t value)
{
	uint16_t x = 148 + 64 * encoder;
	uint16_t y = 32;
	
	tft.fillCircle(x, y, 14, OFF_COLOR);
	tft.setTextColor(MAIN_COLOR);
	tft.drawRect(x- 16, 66, 32, 15, BORDER_COLOR);
	tft.fillRect(x - 14, 68, 28, 11, OFF_COLOR);


	auto radians = value * PI / 62+ PI/6*4;
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

void setup() {  
	

 tft.begin();
  tft.setRotation(1); 
  tft.invertDisplay(false);
  tft.fillScreen(ILI9341_BLACK);
  
  tft.setFont(Arial_9);
  //tft.setTextSize(3);
  tft.setScroll(0);  
  log("TFT success", ILI9341_GREEN); 
   
  for (uint8_t i = 0; i <= 15; i++) {
	  drawSequenceButton(i, false);
  }


  
 // tft.drawBitmap();
  mcp.begin(0);      // use default address 0
  mcp2.begin(1);    


  for (int i=0; i <= 15; i++){     
       mcp.pinMode(i, INPUT);
       mcp.pullUp(i, HIGH);  // turn on a 100K pullup internally
   }

  
  for (int i=0; i <= 15; i++){
     mcp2.pinMode(i, OUTPUT);
   }
  
  mcp2.pullUp(0, HIGH);  // turn on a 100K pullup internally
 
	if (true)
  {
	  log("MCP success", ILI9341_GREEN);
  }
	else
	{
		log("MCP error", ILI9341_RED);
	}



 pinMode(31, INPUT_PULLUP);   
  pinMode(32, INPUT_PULLUP); 
  pinMode(33, INPUT_PULLUP); 
  pinMode(34, INPUT_PULLUP); 
  pinMode(35, INPUT_PULLUP); 
  pinMode(36, INPUT_PULLUP); 
  pinMode(24, INPUT_PULLUP); 
  
  pinMode(13, OUTPUT);  // use the p13 LED as debugging
  pinMode(39, OUTPUT);
    pinMode(15, OUTPUT);
     pinMode(8, OUTPUT);
  uint8_t inc = 0;
  while (!Serial && inc < 20) {
    delay(50);
    inc++;
  }
  delay(50);
  Serial.begin(9600);
  if (Serial.available() > 0)
  {
	  log("Serial success", ILI9341_GREEN);
  }
  else
  {
	  log("Serial error", ILI9341_RED);
  }
  digitalWrite(13, LOW);

 
  enc_one.write(0.6*400);

  
    SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (true) //todo
  {
	  log("SPI success", ILI9341_GREEN);
  }
  else
  {
	  log("SPI error", ILI9341_RED);
  }

  if (SD.begin(SDCARD_CS_PIN))
  {
	  log("SD success", ILI9341_GREEN);
  }
  else
  {
	  log("SD error", ILI9341_RED);
  }

  drawEncoder(0, 0);
  drawEncoder(1, 0);
  drawEncoder(2, 0);
}

bool current[16]; 
uint8_t currentEncoder[3];

void loop() {
  // The LED will 'echo' the button


for (int i=0; i <= 15; i++){

	uint8_t buttonPin = i < 8 ? 7 - i : 23-i ;
     bool value = mcp.digitalRead(buttonPin) == 0;
    if (current[i] != value)
     {
		drawSequenceButton(i, value);
      if ( value)
      {
 switch(i)
    {
      case 0:
		  AudioCore.drumc1();        
        break;
         case 1:
			 AudioCore.drumc2();
        
        break;
         case 2:
			 AudioCore.drumc3();
     
        break;
         case 3:
			 AudioCore.drumc4();        
        break;
           case 4:
      //   playFlashRaw1.play("LIBS/DRUMS/KIT_1_ACOUSTIC_CLOSE/K1CLOSE_CIHAT_01.RAW");
        break;
    }
        
        
      }
     current[i] = value; 
	 uint8_t ledPin = 15 - i;
	 mcp2.digitalWrite(ledPin, value);
    }
     
	
   }
 

 

    Serial.print(" ");
	for (int i = 0; i <= 2; i++) {
		int32_t one_value;
		switch (i)
		{
		case 0:
			one_value = enc_one.read();		
			break;
		case 1:
			one_value = enc_two.read();
			break;
		case 2:
			one_value = enc_three.read();
			break;
		}

		bool needUpdate = false;
		if (one_value < 0)
		{
			one_value = 0;
			needUpdate = true;

		}
		else if (one_value > 400)
		{
			one_value = 400;
			needUpdate = true;
		}
		
		if (needUpdate)
		{
			switch (i)
			{
			case 0:
					enc_one.write(one_value);
				break;
			case 1:
				enc_two.write(one_value);
				break;
			case 2:
					enc_three.write(one_value);
				break;
			}
		}
		uint8_t one_value_r = one_value / 4;

		if (one_value_r != currentEncoder[i])
		{

			switch (i)
			{
			case 0:
				//sgtl5000_1.volume(static_cast<float>(one_value_r) / 100);
		
				break;
			case 1:
				//drum2.frequency(30 + one_value_r);
				break;
			case 2:
			
				break;
			}

			drawEncoder(i, one_value_r);
			digitalWrite(39, one_value_r);
	//		digitalWrite(8, two_value);
		//	digitalWrite(15, three_value);
			currentEncoder[i] = one_value_r;
		}
	}


     for (int i=31; i <= 36; i++){
     uint8_t value = digitalRead(i);
     Serial.print(value);      
   }
    
     Serial.print(digitalRead(24));  
  Serial.println("----------");
  
  
  delay(10);
}
