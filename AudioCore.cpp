// 
// 
// 

#include "AudioCore.h"

//File _fileRec;
//String _lastFileNameRec = "";

float WAVESHAPE_EXAMPLE[17] = {
	-0.588,
	-0.579,
	-0.549,
	-0.488,
	-0.396,
	-0.320,
	-0.228,
	-0.122,
	0,
	0.122,
	0.228,
	0.320,
	0.396,
	0.488,
	0.549,
	0.579,
	0.588
};



// GUItool: begin automatically generated code
AudioInputI2S            audioInput;     //xy=527.3334579467773,899.3333873748779
AudioEffectGate          noiseGateR;     //xy=707.3333129882812,949.3333129882812
AudioEffectGate          noiseGateL;     //xy=708.3333129882812,863.3333129882812
AudioPlaySdWav           playSdWavA;     //xy=867.3333129882812,615.3333129882812
AudioEffectWaveshaper    waveShapeInputR; //xy=892.3333129882812,950.3333129882812
AudioFilterBiquad        biquadInputR;   //xy=1068.3333129882812,949.3333129882812
AudioFilterBiquad        biquadInputL;   //xy=1070.3333129882812,866.3333129882812
AudioFilterBiquad        biquadWavAL;    //xy=1093.3333129882812,577.3333129882812
AudioFilterBiquad        biquadWavAR;    //xy=1095.3333129882812,637.3333129882812
AudioFilterBiquad        biquadfreeverbs; //xy=1133.3333129882812,783.3333129882812
AudioSynthSimpleDrum     drum1;          //xy=1135.3333129882812,335.33331298828125
AudioSynthSimpleDrum     drum2;          //xy=1143.3333129882812,395.33331298828125
AudioSynthSimpleDrum     drum3;          //xy=1146.3333129882812,448.33331298828125
AudioSynthSimpleDrum     drum4;          //xy=1146.3333129882812,502.33331298828125
AudioAnalyzePeak         peakWavL;       //xy=1282.3333129882812,589.3333129882812
AudioAnalyzePeak         peakWavR;       //xy=1282.3333129882812,696.3333129882812
AudioEffectFreeverbStereo fxfreeverbs;    //xy=1305.3333129882812,783.3333129882812
AudioMixer4              mixer1;         //xy=1352.3333129882812,418.33331298828125
AudioAnalyzePeak         peakfreeverbsR; //xy=1534.3333129882812,885.3333129882812
AudioAnalyzePeak         peakfreeverbsL; //xy=1536.3333129882812,840.3333129882812
AudioAnalyzePeak         peakAudio01;    //xy=1538.3333129882812,356.33331298828125
AudioAnalyzePeak         peakAudioInputL; //xy=1536.3333129882812,938.3333129882812
AudioAnalyzePeak         peakAudioInputR; //xy=1540.3333129882812,986.3333129882812
AudioMixer4              mixerGroupL0;   //xy=1746.3333129882812,479.33331298828125
AudioMixer4              mixerGroupL1;   //xy=1746.3333129882812,546.3333129882812
AudioMixer4              mixerGroupL2;   //xy=1746.3333129882812,613.3333129882812
AudioMixer4              mixerGroupL3;   //xy=1746.3333129882812,682.3333129882812
AudioMixer4              mixerGroupR0;   //xy=1746.3333129882812,753.3333129882812
AudioMixer4              mixerGroupR1;   //xy=1746.3333129882812,821.3333129882812
AudioMixer4              mixerGroupR2;   //xy=1746.3333129882812,890.3333129882812
AudioMixer4              mixerGroupR3;   //xy=1746.3333129882812,957.3333129882812
AudioMixer4              masterMixerL;   //xy=1983.3333129882812,687.3333129882812
AudioMixer4              masterMixerR;   //xy=1983.3333129882812,758.3333129882812
AudioAnalyzePeak         peakAudioOutputR; //xy=2160.3333129882812,936.3333129882812
AudioAnalyzePeak         peakAudioOutputL; //xy=2161.3333129882812,894.3333129882812
AudioOutputI2S           audioOutput;    //xy=2170.3333129882812,720.3333129882812
AudioConnection          patchCord1(audioInput, 0, noiseGateL, 0);
AudioConnection          patchCord2(audioInput, 1, noiseGateR, 0);
AudioConnection          patchCord3(noiseGateR, waveShapeInputR);
AudioConnection          patchCord4(noiseGateL, biquadInputL);
AudioConnection          patchCord5(playSdWavA, 0, biquadWavAL, 0);
AudioConnection          patchCord6(playSdWavA, 1, biquadWavAR, 0);
AudioConnection          patchCord7(waveShapeInputR, biquadInputR);
AudioConnection          patchCord8(biquadInputR, peakAudioInputR);
AudioConnection          patchCord9(biquadInputR, 0, mixerGroupL0, 1);
AudioConnection          patchCord10(biquadInputR, 0, mixerGroupR0, 1);
AudioConnection          patchCord11(biquadInputR, biquadfreeverbs);
AudioConnection          patchCord12(biquadInputL, peakAudioInputL);
AudioConnection          patchCord13(biquadInputL, 0, mixerGroupL0, 0);
AudioConnection          patchCord14(biquadInputL, 0, mixerGroupR0, 0);
AudioConnection          patchCord15(biquadWavAL, 0, mixerGroupL0, 3);
AudioConnection          patchCord16(biquadWavAL, peakWavL);
AudioConnection          patchCord17(biquadWavAR, 0, mixerGroupR0, 3);
AudioConnection          patchCord18(biquadWavAR, peakWavR);
AudioConnection          patchCord19(biquadfreeverbs, fxfreeverbs);
AudioConnection          patchCord20(drum1, 0, mixer1, 0);
AudioConnection          patchCord21(drum2, 0, mixer1, 1);
AudioConnection          patchCord22(drum3, 0, mixer1, 2);
AudioConnection          patchCord23(drum4, 0, mixer1, 3);
AudioConnection          patchCord24(fxfreeverbs, 0, mixerGroupL1, 0);
AudioConnection          patchCord25(fxfreeverbs, 0, peakfreeverbsL, 0);
AudioConnection          patchCord26(fxfreeverbs, 1, mixerGroupR1, 0);
AudioConnection          patchCord27(fxfreeverbs, 1, peakfreeverbsR, 0);
AudioConnection          patchCord28(mixer1, 0, mixerGroupL0, 2);
AudioConnection          patchCord29(mixer1, 0, mixerGroupR0, 2);
AudioConnection          patchCord30(mixer1, peakAudio01);
AudioConnection          patchCord31(mixerGroupL0, 0, masterMixerL, 0);
AudioConnection          patchCord32(mixerGroupL1, 0, masterMixerL, 1);
AudioConnection          patchCord33(mixerGroupL2, 0, masterMixerL, 2);
AudioConnection          patchCord34(mixerGroupL3, 0, masterMixerL, 3);
AudioConnection          patchCord35(mixerGroupR0, 0, masterMixerR, 0);
AudioConnection          patchCord36(mixerGroupR1, 0, masterMixerR, 1);
AudioConnection          patchCord37(mixerGroupR2, 0, masterMixerR, 2);
AudioConnection          patchCord38(mixerGroupR3, 0, masterMixerR, 3);
AudioConnection          patchCord39(masterMixerL, 0, audioOutput, 0);
AudioConnection          patchCord40(masterMixerL, peakAudioOutputL);
AudioConnection          patchCord41(masterMixerR, 0, audioOutput, 1);
AudioConnection          patchCord42(masterMixerR, peakAudioOutputR);
AudioControlSGTL5000     audioShield;    //xy=2166.3333129882812,767.3333129882812
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

	masterMixerL.gain(2, 0);
	masterMixerL.gain(3, 0);
	
	mixerGroupL1.gain(1, 0);
	mixerGroupL1.gain(2, 0);
	mixerGroupL1.gain(3, 0);

	mixerGroupL2.gain(0, 0);
	mixerGroupL2.gain(1, 0);
	mixerGroupL2.gain(2, 0);
	mixerGroupL2.gain(3, 0);

	mixerGroupL3.gain(0, 0);
	mixerGroupL3.gain(1, 0);
	mixerGroupL3.gain(2, 0);
	mixerGroupL3.gain(3, 0);
	
	masterMixerR.gain(2, 0);
	masterMixerR.gain(3, 0);

	mixerGroupR1.gain(1, 0);
	mixerGroupR1.gain(2, 0);
	mixerGroupR1.gain(3, 0);

	mixerGroupR2.gain(0, 0);
	mixerGroupR2.gain(1, 0);
	mixerGroupR2.gain(2, 0);
	mixerGroupR2.gain(3, 0);

	mixerGroupR3.gain(0, 0);
	mixerGroupR3.gain(1, 0);
	mixerGroupR3.gain(2, 0);
	mixerGroupR3.gain(3, 0);

	
	audioShield.enable();
	audioShield.inputSelect(AUDIO_INPUT_LINEIN);		
	audioShield.adcHighPassFilterDisable();

	biquadInputL.setHighpass(0, 100, 0.707);
	biquadInputR.setHighpass(0, 200, 0.707);

	biquadfreeverbs.setLowpass(0, 2000, 0.707);
	
	fxfreeverbs.update();
	waveShapeInputR.shape(WAVESHAPE_EXAMPLE, 17);
	noiseGateR.threshold(0.008);
	noiseGateL.threshold(0.008);
	//https://github.com/MarkzP/AudioEffectDynamics/blob/master/effect_dynamics.h
//	AudioInterrupts(); //swith on library
}

void AudioCoreClass::setReverbRoom(float damping, float roomsize)
{
	fxfreeverbs.damping(damping);
	fxfreeverbs.roomsize(roomsize);
}


void AudioCoreClass::setLooperEqBiquad(int* coefs) {

	biquadWavAL.setCoefficients(0, coefs);
	biquadWavAR.setCoefficients(0, coefs);
}

void AudioCoreClass::setLeftInputBiquad(float frequency, float q) {

	biquadInputL.setHighpass(0, frequency, q);	
}

void AudioCoreClass::setRightInputBiquad(float frequency, float q) {

	biquadInputR.setHighpass(0, frequency, q);
}

void AudioCoreClass::setReverbBiquad(float frequency, float q) {

	biquadfreeverbs.setLowpass(0, frequency, q);
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


 void AudioCoreClass::enhanceBass(bool enable)
 {
	
 }

 void AudioCoreClass::setLooperVolume(float vol, float balance)
 {	 
	 setBalancedVolume(3, vol, balance);
 }

 void AudioCoreClass::setLeftInputVolume(float vol, float balance)
 {
	 setBalancedVolume(0, vol, balance);
 }

void AudioCoreClass::setBalancedVolume(uint8_t channel,  float vol, float balance)
{
	Serial.println(String(channel)+" "+ String(vol)+" "+ String(balance));
	if (balance == 0)
	{
		mixerGroupL0.gain(channel, vol);
		mixerGroupR0.gain(channel, vol);
	}
	else if (balance > 0)
	{
		mixerGroupL0.gain(channel, vol);
		mixerGroupR0.gain(channel, vol * (1.0 - balance));

	}
	else
	{
		mixerGroupR0.gain(channel, vol);
		mixerGroupL0.gain(channel, vol * (1.0 + balance));
	}
}

 void AudioCoreClass::setRightInputVolume(float vol, float balance)
 {
	 setBalancedVolume(1, vol, balance);
}

 void AudioCoreClass::setReverbVolume(float vol, float balance)
 {
	 if (balance == 0)
	 {
		 mixerGroupL1.gain(0, vol);
		 mixerGroupR1.gain(0, vol);
	 }
	 else if (balance > 0)
	 {
		 mixerGroupL1.gain(0, vol);
		 mixerGroupR1.gain(0, vol * (1.0 - balance));

	 }
	 else
	 {
		 mixerGroupR1.gain(0, vol);
		 mixerGroupL1.gain(0, vol * (1.0 + balance));
	 }
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

float AudioCoreClass::getReverbFxPeakL() //to Array
{
	if (peakfreeverbsL.available())
	{
		return peakfreeverbsL.read();
	}
	return 0;
}

float AudioCoreClass::getReverbFxPeakR()
{
	if (peakfreeverbsR.available())
	{
		return peakfreeverbsR.read();
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

void AudioCoreClass::playLastRecorderInputRaw()
{

/*	if (!_lastFileNameRec.equals("") )
	{
		if (SD.exists(_lastFileNameRec.c_str()))
		{
			//playTestRawL.play(_lastFileNameRec.c_str());
			_recorderStatus = RECORD_STATUS_PLAY;
		}
		if (SD.exists(_lastFileNameRecR.c_str()))
		{
			playTestRawR.play(_lastFileNameRecR.c_str());
			_recorderStatus = RECORD_STATUS_PLAY;
		}
	} */
}


void AudioCoreClass::stopWav()
{
	playSdWavA.stop();
}

bool AudioCoreClass::wavIsPlaying()
{
	return playSdWavA.isPlaying();
}


String AudioCoreClass::getRecordFileName(String prefix, uint8_t songNum, uint16_t version)
{
	return "/DATA/" + prefix + "_" + String(songNum, DEC) + "_" + String(version, DEC) + ".RAW";
}

uint16_t AudioCoreClass::getMaxRecordedTracks(uint8_t songNum) {
	uint16_t _version = 0;
	/*do
	{
		_version++;
		//_lastFileNameRec = getRecordFileName("B", songNum, _version).c_str();
		Serial.println(_lastFileNameRec);		
	} while (SD.exists(_lastFileNameRec.c_str())); */
	return _version;
}


void AudioCoreClass::stopRecording() {
	Serial.println("StopRecording");
//	queueRecordL.end();
	/*queueRecordR.end();
	// flush buffer
	while ( queueRecordR.available() > 0) {
	//	queueRecordL.readBuffer();
	//	queueRecordL.freeBuffer();
		queueRecordR.readBuffer();
		queueRecordR.freeBuffer();
	}
	_fileRec.close(); // close file	
	_recorderStatus = RECORD_STATUS_NONE;
	*/
}


AudioCoreClass AudioCore;

