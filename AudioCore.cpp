// 
// 
// 

#include "AudioCore.h"


// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drum2;          //xy=235.0130157470703,148.24999856948853
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=259.0130157470703,354.2499985694885
AudioSynthSimpleDrum     drum3;          //xy=260.0130157470703,214.24999856948853
AudioSynthSimpleDrum     drum1;          //xy=267.0130157470703,101.24999856948853
AudioSynthSimpleDrum     drum4;          //xy=300.0130157470703,278.2499985694885
AudioInputI2S            audioInput;     //xy=319.0130157470703,589.2499985694885
AudioMixer4              mixer2;         //xy=441.0130157470703,362.2499985694885
AudioMixer4              mixer1;         //xy=466.0130157470703,184.24999856948853
AudioAnalyzePeak         peakAudioInputR;          //xy=555.1770858764648,630.010332107544
AudioAnalyzePeak         peakAudioInputL;          //xy=556.0104446411133,588.0104856491089
AudioAnalyzePeak         peakAudio01;          //xy=595.1771011352539,329.0104064941406
AudioMixer4              mixerGroupL0;   //xy=760.0130157470703,159.24999856948853
AudioMixer4              mixerGroupL1;   //xy=760.0130157470703,226.24999856948853
AudioMixer4              mixerGroupL2;   //xy=760.0130157470703,293.2499985694885
AudioMixer4              mixerGroupL3;   //xy=760.0130157470703,362.2499985694885
AudioMixer4              mixerGroupR0;   //xy=760.0130157470703,433.2499985694885
AudioMixer4              mixerGroupR1;   //xy=760.0130157470703,501.2499985694885
AudioMixer4              mixerGroupR2;   //xy=760.0130157470703,570.2499985694885
AudioMixer4              mixerGroupR3;   //xy=760.0130157470703,637.2499985694885
AudioMixer4              masterMixerL;   //xy=997.0130157470703,367.2499985694885
AudioMixer4              masterMixerR;   //xy=997.0130157470703,438.2499985694885
AudioAnalyzePeak         peakAudioOutputR;          //xy=1174.1772994995117,616.0104351043701
AudioAnalyzePeak         peakAudioOutputL;          //xy=1175.177604675293,574.0103740692139
AudioOutputI2S           audioOutput;    //xy=1184.0130157470703,400.2499985694885
AudioConnection          patchCord1(drum2, 0, mixer1, 1);
AudioConnection          patchCord2(playFlashRaw1, 0, mixer2, 0);
AudioConnection          patchCord3(drum3, 0, mixer1, 2);
AudioConnection          patchCord4(drum1, 0, mixer1, 0);
AudioConnection          patchCord5(drum4, 0, mixer1, 3);
AudioConnection          patchCord6(audioInput, 0, mixerGroupL0, 0);
AudioConnection          patchCord7(audioInput, 0, mixerGroupR0, 0);
AudioConnection          patchCord8(audioInput, 0, peakAudioInputL, 0);
AudioConnection          patchCord9(audioInput, 1, mixerGroupL0, 1);
AudioConnection          patchCord10(audioInput, 1, mixerGroupR0, 1);
AudioConnection          patchCord11(audioInput, 1, peakAudioInputR, 0);
AudioConnection          patchCord12(mixer1, 0, mixerGroupL0, 2);
AudioConnection          patchCord13(mixer1, 0, mixerGroupR0, 2);
AudioConnection          patchCord14(mixer1, peakAudio01);
AudioConnection          patchCord15(mixerGroupL0, 0, masterMixerL, 0);
AudioConnection          patchCord16(mixerGroupL1, 0, masterMixerL, 1);
AudioConnection          patchCord17(mixerGroupL2, 0, masterMixerL, 2);
AudioConnection          patchCord18(mixerGroupL3, 0, masterMixerL, 3);
AudioConnection          patchCord19(mixerGroupR0, 0, masterMixerR, 0);
AudioConnection          patchCord20(mixerGroupR1, 0, masterMixerR, 1);
AudioConnection          patchCord21(mixerGroupR2, 0, masterMixerR, 2);
AudioConnection          patchCord22(mixerGroupR3, 0, masterMixerR, 3);
AudioConnection          patchCord23(masterMixerL, 0, audioOutput, 0);
AudioConnection          patchCord24(masterMixerL, peakAudioOutputL);
AudioConnection          patchCord25(masterMixerR, 0, audioOutput, 1);
AudioConnection          patchCord26(masterMixerR, peakAudioOutputR);
AudioControlSGTL5000     audioShield;    //xy=1180.0130157470703,447.2499985694885
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

float AudioCoreClass::getPeakL() //to Array
{
	if (peakAudioOutputL.available())
	{
		return peakAudioOutputL.read();
	}
	return 0;
}

float AudioCoreClass::getPeakR()
{
	if (peakAudioOutputR.available())
	{
		return peakAudioOutputR.read();
	}
	return 0;
}

AudioCoreClass AudioCore;

