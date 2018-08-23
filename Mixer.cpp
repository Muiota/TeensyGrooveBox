// 
// 
// 

#include "Mixer.h"
#include "HardwareCore.h"
#include "DisplayCore.h"
bool _current[16];
record_status _recordStatus = RECORD_STATUS_NONE;
void MixerClass::handle()
{
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
				case 5:
					//
					_recordStatus = static_cast<record_status>((_recordStatus + 1) % 3);
					break;
				case 6:
					//AudioCore.stopRecording();
					break;
				case 15:

					break;
				}


			}
			_current[i] = value;
			HardwareCore.seqLedWrite(i, value);
		}
	}
}


