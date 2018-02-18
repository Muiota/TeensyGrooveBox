// 
// 
// 

#include "AudioCore.h"



// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drum2;          //xy=184.0104217529297,130.00000166893005
AudioSynthSimpleDrum     drum3;          //xy=209.0104217529297,196.00000166893005
AudioSynthSimpleDrum     drum1;          //xy=216.0104217529297,83.00000166893005
AudioSynthSimpleDrum     drum4;          //xy=249.0104217529297,260.00000166893005
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=268.0104217529297,404.00000166893005
AudioInputI2S            audioInput;     //xy=419.0104751586914,447.000009059906
AudioMixer4              mixer1;         //xy=522.0104217529297,151.00000166893005
AudioMixer4              mixer2;         //xy=528.0104217529297,237.00000166893005
AudioMixer4              masterMixerL;   //xy=813.0105476379395,286
AudioOutputI2S           audioOutput;    //xy=890.0104217529297,140.00000166893005
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
AudioControlSGTL5000     audioShield;    //xy=516.0104217529297,495.00000166893005
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

