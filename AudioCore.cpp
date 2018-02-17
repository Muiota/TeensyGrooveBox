// 
// 
// 

#include "AudioCore.h"


// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drum2;          //xy=194.0104217529297,141.00000166893005
AudioSynthSimpleDrum     drum3;          //xy=219.0104217529297,207.00000166893005
AudioSynthSimpleDrum     drum1;          //xy=226.0104217529297,94.00000166893005
AudioSynthSimpleDrum     drum4;          //xy=259.0104217529297,271.00000166893005
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=278.0104217529297,415.00000166893005
AudioInputI2S            audioInput;             //xy=438.01043701171875,442.0104398727417
AudioMixer4              mixer1;         //xy=532.0104217529297,162.00000166893005
AudioMixer4              mixer2;         //xy=538.0104217529297,248.00000166893005
AudioMixer4              mixer3;         //xy=736.0104789733887,223.0000114440918
AudioOutputI2S           audioOutput;           //xy=900.0105819702148,151.00002670288086
AudioConnection          patchCord1(drum2, 0, mixer1, 1);
AudioConnection          patchCord2(drum3, 0, mixer1, 2);
AudioConnection          patchCord3(drum1, 0, mixer1, 0);
AudioConnection          patchCord4(drum4, 0, mixer1, 3);
AudioConnection          patchCord5(playFlashRaw1, 0, mixer2, 0);
AudioConnection          patchCord6(audioInput, 0, audioOutput, 0);
AudioConnection          patchCord7(audioInput, 1, mixer3, 3);
AudioConnection          patchCord8(mixer1, 0, mixer3, 0);
AudioConnection          patchCord9(mixer2, 0, mixer3, 1);
AudioConnection          patchCord10(mixer3, 0, audioOutput, 1);
AudioControlSGTL5000     audioShield;     //xy=526.0105514526367,506.00001335144043
										 // GUItool: end automatically generated code


AudioCoreClass::AudioCoreClass()
{


}

void AudioCoreClass::init()
{
	
	// audio library init
	AudioMemory(60);

	//next = millis() + 1000;

//	AudioNoInterrupts(); //swith off library

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

	//mixer3.gain(2, 1.0f);
	//mixer3.gain(3, 1.0f);

	audioShield.enable();
	audioShield.inputSelect(AUDIO_INPUT_LINEIN);
	audioShield.volume(0.6f);


//	AudioInterrupts(); //swith on library
}

void AudioCoreClass::drum1On()
{
	drum1.noteOn();
}

void AudioCoreClass::drum2On()
{
	drum2.noteOn();
}

void AudioCoreClass::drum3On()
{
	drum3.noteOn();
}

void AudioCoreClass::drum4On()
{
	drum4.noteOn();
}

void AudioCoreClass::setVolume(float x)
{
	audioShield.volume(x);
}

