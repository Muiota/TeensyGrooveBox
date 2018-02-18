// 
// 
// 

#include "AudioCore.h"


// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drum2;          //xy=155.0104217529297,139.00000166893005
AudioSynthSimpleDrum     drum3;          //xy=180.0104217529297,205.00000166893005
AudioSynthSimpleDrum     drum1;          //xy=187.0104217529297,92.00000166893005
AudioSynthSimpleDrum     drum4;          //xy=220.0104217529297,269.00000166893005
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=239.0104217529297,413.00000166893005
AudioInputI2S            audioInput;     //xy=399.0104217529297,440.00000166893005
AudioMixer4              mixer1;         //xy=493.0104217529297,160.00000166893005
AudioMixer4              mixer2;         //xy=499.0104217529297,246.00000166893005
AudioMixer4              masterMixerL;         //xy=718.0104827880859,255.00001907348633
AudioOutputI2S           audioOutput;    //xy=861.0104217529297,149.00000166893005
AudioConnection          patchCord1(drum2, 0, mixer1, 1);
AudioConnection          patchCord2(drum3, 0, mixer1, 2);
AudioConnection          patchCord3(drum1, 0, mixer1, 0);
AudioConnection          patchCord4(drum4, 0, mixer1, 3);
AudioConnection          patchCord5(playFlashRaw1, 0, mixer2, 0);
AudioConnection          patchCord6(audioInput, 0, masterMixerL, 2);
AudioConnection          patchCord7(audioInput, 1, masterMixerL, 3);
AudioConnection          patchCord8(mixer1, 0, masterMixerL, 0);
AudioConnection          patchCord9(mixer2, 0, masterMixerL, 1);
AudioConnection          patchCord10(masterMixerL, 0, audioOutput, 1);
AudioConnection          patchCord11(masterMixerL, 0, audioOutput, 0);
AudioControlSGTL5000     audioShield;    //xy=487.0104217529297,504.00000166893005
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

