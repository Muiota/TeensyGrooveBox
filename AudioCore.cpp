// 
// 
// 

#include "AudioCore.h"


// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWavA;     //xy=140.47623443603516,429.76191902160645
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=156.15589904785156,284.2500114440918
AudioSynthSimpleDrum     drum2;          //xy=172.15588760375977,82.53572463989258
AudioInputI2S            audioInput;     //xy=180.44161987304688,583.535774230957
AudioSynthSimpleDrum     drum3;          //xy=197.15588760375977,148.53572463989258
AudioSynthSimpleDrum     drum1;          //xy=204.15588760375977,35.53572463989258
AudioSynthSimpleDrum     drum4;          //xy=237.15588760375977,212.53572463989258
AudioFilterBiquad        biquadWavAR;        //xy=310.0000228881836,458.57144927978516
AudioFilterBiquad        biquadWavAL;        //xy=311.6666793823242,423.33337783813477
AudioMixer4              mixer2;         //xy=338.15589904785156,292.2500114440918
AudioFilterBiquad        biquadInputR;        //xy=348.57143783569336,604.2857360839844
AudioFilterBiquad        biquadInputL;        //xy=350.0000057220459,561.4286289215088
AudioMixer4              mixer1;         //xy=403.15588760375977,118.53572463989258
AudioAnalyzePeak         peakWavL;          //xy=497.14290618896484,334.28572845458984
AudioAnalyzePeak         peakWavR;          //xy=512.8572540283203,392.85726737976074
AudioAnalyzePeak         peakAudioInputR;          //xy=576.6056785583496,681.4389171600342
AudioAnalyzePeak         peakAudioInputL;          //xy=577.4390640258789,640.867639541626
AudioAnalyzePeak         peakAudio01;          //xy=589.4628715515137,56.15328550338745
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
AudioConnection          patchCord1(playSdWavA, 0, biquadWavAL, 0);
AudioConnection          patchCord2(playSdWavA, 1, biquadWavAR, 0);
AudioConnection          patchCord3(playFlashRaw1, 0, mixer2, 0);
AudioConnection          patchCord4(drum2, 0, mixer1, 1);
AudioConnection          patchCord5(audioInput, 0, biquadInputL, 0);
AudioConnection          patchCord6(audioInput, 1, biquadInputR, 0);
AudioConnection          patchCord7(drum3, 0, mixer1, 2);
AudioConnection          patchCord8(drum1, 0, mixer1, 0);
AudioConnection          patchCord9(drum4, 0, mixer1, 3);
AudioConnection          patchCord10(biquadWavAR, 0, mixerGroupR0, 3);
AudioConnection          patchCord11(biquadWavAR, peakWavR);
AudioConnection          patchCord12(biquadWavAL, 0, mixerGroupL0, 3);
AudioConnection          patchCord13(biquadWavAL, peakWavL);
AudioConnection          patchCord14(biquadInputR, peakAudioInputR);
AudioConnection          patchCord15(biquadInputR, 0, mixerGroupL0, 1);
AudioConnection          patchCord16(biquadInputR, 0, mixerGroupR0, 1);
AudioConnection          patchCord17(biquadInputL, peakAudioInputL);
AudioConnection          patchCord18(biquadInputL, 0, mixerGroupL0, 0);
AudioConnection          patchCord19(biquadInputL, 0, mixerGroupR0, 0);
AudioConnection          patchCord20(mixer1, 0, mixerGroupL0, 2);
AudioConnection          patchCord21(mixer1, 0, mixerGroupR0, 2);
AudioConnection          patchCord22(mixer1, peakAudio01);
AudioConnection          patchCord23(mixerGroupL0, 0, masterMixerL, 0);
AudioConnection          patchCord24(mixerGroupL1, 0, masterMixerL, 1);
AudioConnection          patchCord25(mixerGroupL2, 0, masterMixerL, 2);
AudioConnection          patchCord26(mixerGroupL3, 0, masterMixerL, 3);
AudioConnection          patchCord27(mixerGroupR0, 0, masterMixerR, 0);
AudioConnection          patchCord28(mixerGroupR1, 0, masterMixerR, 1);
AudioConnection          patchCord29(mixerGroupR2, 0, masterMixerR, 2);
AudioConnection          patchCord30(mixerGroupR3, 0, masterMixerR, 3);
AudioConnection          patchCord31(masterMixerL, 0, audioOutput, 0);
AudioConnection          patchCord32(masterMixerL, peakAudioOutputL);
AudioConnection          patchCord33(masterMixerR, 0, audioOutput, 1);
AudioConnection          patchCord34(masterMixerR, peakAudioOutputR);
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
	

	biquadInputL.setHighpass(0, 100, 0.707);
	biquadInputR.setHighpass(0, 200, 0.707);
//	AudioInterrupts(); //swith on library
}

void AudioCoreClass::setWavLowpass(float frequency, float q) {

	biquadWavAL.setLowpass(0, frequency, q);
	biquadWavAR.setLowpass(0, frequency, q);
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

 void AudioCoreClass::setMasterVolume(float x)
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

float AudioCoreClass::getWavPeakL() //to Array
{
	if (peakWavL.available())
	{
		return peakWavL.read();
	}
	return 0;
}

float AudioCoreClass::getWavPeakR()
{
	if (peakWavR.available())
	{
		return peakWavR.read();
	}
	return 0;
}

float AudioCoreClass::getPeakAudioInputL() //to Array
{
	if (peakAudioInputL.available())
	{
		return peakAudioInputL.read();
	}
	return 0;
}

float AudioCoreClass::getPeakAudioInputR()
{
	if (peakAudioInputR.available())
	{
		return peakAudioInputR.read();
	}
	return 0;
}


void AudioCoreClass::playWav(const char * song)
{	
	playSdWavA.play(song);
}

void AudioCoreClass::stopWav()
{
	playSdWavA.stop();
}

bool AudioCoreClass::wavIsPlaying()
{
	return playSdWavA.isPlaying();
}

AudioCoreClass AudioCore;

