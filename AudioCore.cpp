// 
// 
// 

#include "AudioCore.h"


// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drum2;          //xy=55,71.0000114440918
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=79.01042175292969,277.00000953674316
AudioSynthSimpleDrum     drum3;          //xy=80,137.0000114440918
AudioSynthSimpleDrum     drum1;          //xy=87,24.000011444091797
AudioSynthSimpleDrum     drum4;          //xy=120,201.0000114440918
AudioInputI2S            audioInput;     //xy=139.5,512.0000839233398
AudioMixer4              mixer2;         //xy=261.0104446411133,285.0000057220459
AudioMixer4              mixer1;         //xy=286.9999885559082,107.00001525878906
AudioMixer4              mixerGroupR0;         //xy=580.0000000000000,356.01044845581055
AudioMixer4              mixerGroupL0;         //xy=580.0000000000000,82.9999885559082
AudioMixer4              mixerGroupL2;         //xy=580.0000000000000,216.00001430511475
AudioMixer4              mixerGroupL1;         //xy=580.0000000000000,149
AudioMixer4              mixerGroupL3;         //xy=580.0000000000000,285.0000190734863
AudioMixer4              mixerGroupR1;         //xy=580.0000000000000,424.010440826416
AudioMixer4              mixerGroupR2;        //xy=580.0000000000000,493.01043128967285
AudioMixer4              mixerGroupR3;        //xy=580.0000000000000,560.0104598999023
AudioMixer4              masterMixerR;         //xy=817,361.0104761123657
AudioMixer4              masterMixerL;   //xy=817,290.0000219345093
AudioOutputI2S           audioOutput;    //xy=1004,323.0000114440918
AudioConnection          patchCord1(drum2, 0, mixer1, 1);
AudioConnection          patchCord2(playFlashRaw1, 0, mixer2, 0);
AudioConnection          patchCord3(drum3, 0, mixer1, 2);
AudioConnection          patchCord4(drum1, 0, mixer1, 0);
AudioConnection          patchCord5(drum4, 0, mixer1, 3);
AudioConnection          patchCord6(audioInput, 0, mixerGroupL0, 0);
AudioConnection          patchCord7(audioInput, 0, mixerGroupR0, 0);
AudioConnection          patchCord8(audioInput, 1, mixerGroupL0, 1);
AudioConnection          patchCord9(audioInput, 1, mixerGroupR0, 1);
AudioConnection          patchCord10(mixer1, 0, mixerGroupL0, 2);
AudioConnection          patchCord11(mixer1, 0, mixerGroupR0, 2);
AudioConnection          patchCord12(mixerGroupR0, 0, masterMixerR, 0);
AudioConnection          patchCord13(mixerGroupL0, 0, masterMixerL, 0);
AudioConnection          patchCord14(mixerGroupL2, 0, masterMixerL, 2);
AudioConnection          patchCord15(mixerGroupL1, 0, masterMixerL, 1);
AudioConnection          patchCord16(mixerGroupL3, 0, masterMixerL, 3);
AudioConnection          patchCord17(mixerGroupR1, 0, masterMixerR, 1);
AudioConnection          patchCord18(mixerGroupR2, 0, masterMixerR, 2);
AudioConnection          patchCord19(mixerGroupR3, 0, masterMixerR, 3);
AudioConnection          patchCord20(masterMixerR, 0, audioOutput, 1);
AudioConnection          patchCord21(masterMixerL, 0, audioOutput, 0);
AudioControlSGTL5000     audioShield;    //xy=1000.0104598999023,370.9999828338623
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

AudioCoreClass AudioCore;

