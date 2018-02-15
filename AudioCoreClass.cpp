// 
// 
// 

#include "AudioCoreClass.h"





AudioCoreClass::AudioCoreClass()
{

	AudioConnection          patchCord1(drum2, 0, mixer1, 1);
	AudioConnection          patchCord2(drum3, 0, mixer1, 2);
	AudioConnection          patchCord3(drum1, 0, mixer1, 0);
	AudioConnection          patchCord4(drum4, 0, mixer1, 3);
	AudioConnection          patchCord5(playFlashRaw1, 0, mixer2, 0);
	AudioConnection          patchCord6(mixer1, 0, mixer3, 0);
	AudioConnection          patchCord7(mixer2, 0, mixer3, 1);
	AudioConnection          patchCord8(mixer3, 0, i2s1, 0);
	AudioConnection          patchCord9(mixer3, 0, i2s1, 1);

	// audio library init
	AudioMemory(15);

	//next = millis() + 1000;

	AudioNoInterrupts(); //todo what is it

	drum1.frequency(60);
	drum1.length(1500);
	drum1.secondMix(0.0);
	drum1.pitchMod(0.55);

	drum2.frequency(60);
	drum2.length(300);
	drum2.secondMix(0.0);
	drum2.pitchMod(1.0);

	drum3.frequency(550);
	drum3.length(400);
	drum3.secondMix(1.0);
	drum3.pitchMod(0.5);

	drum4.frequency(1200);
	drum4.length(150);
	drum4.secondMix(0.0);
	drum4.pitchMod(0.0);

	sgtl5000_1.enable();
	sgtl5000_1.volume(0.6);

	AudioInterrupts(); //todo what is it
}

void AudioCoreClass::init()
{


	

}

void AudioCoreClass::drumc1()
{
	drum1.noteOn();
}

void AudioCoreClass::drumc2()
{
	drum2.noteOn();
}

void AudioCoreClass::drumc3()
{
	drum3.noteOn();
}

void AudioCoreClass::drumc4()
{
	drum4.noteOn();
}


AudioCoreClass AudioCore;

