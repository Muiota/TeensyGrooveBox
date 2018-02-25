// 
// 
// 

#include "Engine.h"

void EngineClass::init()
{


}

void EngineClass::update()
{
	if (_hardwareTimer >= 100) {
		_hardwareTimer = 0;
		auto usage = AudioProcessorUsageMax();
		AudioProcessorUsageMaxReset();
		for (uint8_t i = 0; i <= 15; i++) {
			auto value = HardwareCore.seqButtonRead(i);
			if (_current[i] != value)
			{
				DisplayCore.drawSequenceButton(i, value);
				if (value)
				{
					switch (i)
					{
					case 0:
						AudioCore.drum1On();

						break;
					case 1:
						AudioCore.drum2On();

						break;
					case 2:
						AudioCore.drum3On();

						break;
					case 3:
						AudioCore.drum4On();

						break;
					case 4:
						//   playFlashRaw1.play("LIBS/DRUMS/KIT_1_ACOUSTIC_CLOSE/K1CLOSE_CIHAT_01.RAW");
						break;
					}


				}
				_current[i] = value;
				HardwareCore.seqLedWrite(i, value);
			}
		}

		//Serial.print(" ");
		for (uint8_t i = 0; i <= 2; i++) {
			auto one_value = HardwareCore.readEncoder(i);
			auto needUpdate = false;
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
				HardwareCore.writeEncoder(i, one_value);
			}
			uint8_t one_value_r = one_value / 4;

			if (one_value_r != _currentEncoder[i])
			{

				switch (i)
				{
				case 0:
					AudioCore.setVolume(static_cast<float>(one_value_r) / 100);

					break;
				case 1:
					//drum2.frequency(30 + one_value_r);
					break;
				case 2:

					break;
				}

				DisplayCore.drawEncoder(i, one_value_r);
				digitalWrite(39, one_value_r);
				//		seqLedWrite(8, two_value);
				//	seqLedWrite(15, three_value);
				_currentEncoder[i] = one_value_r;
			}
		}


		for (int i = 31; i <= 36; i++) {
			uint8_t value = digitalRead(i);
			//	Serial.print(value);
		}

		//	Serial.print(seqButtonRead(24));
		//	Serial.println("----------");
		if (Serial) {
			Serial.print(usage);
			Serial.print("   ");
			Serial.println();
		}

		DisplayCore.drawMeter(2, AudioCore.getPeakL(), AudioCore.getPeakR());
		DisplayCore.drawMeter(3, AudioCore.getPeakL(), AudioCore.getPeakR());

	}
}


EngineClass Engine;

