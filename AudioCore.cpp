// 
// 
// 

#include "AudioCore.h"

File frecL;
File frecR;
bool _isRecording;

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
AudioInputI2S            audioInput;     //xy=87.5,785.1667623519897
AudioEffectGate          noiseGateR;          //xy=237.49998474121094,830.8333578109741
AudioEffectGate          noiseGateL;          //xy=239.16664123535156,745.8333425521851
AudioRecordQueue         queueRecordL;         //xy=329.4167060852051,655.5001573562622
AudioRecordQueue         queueRecordR;         //xy=368.41680908203125,935.5001344680786
AudioPlaySdWav           playSdWavA;     //xy=421.50008392333984,497.500093460083
AudioEffectWaveshaper    waveShapeInputR; //xy=446.5001220703125,832.5001640319824
AudioFilterBiquad        biquadInputR;   //xy=622.5002975463867,831.5001621246338
AudioFilterBiquad        biquadInputL;   //xy=624.0002975463867,748.0001583099365
AudioFilterBiquad        biquadWavAL;    //xy=647.5002212524414,459.0001335144043
AudioFilterBiquad        biquadWavAR;    //xy=649.0002212524414,519.0001358985901
AudioFilterBiquad        biquadfreeverbs; //xy=687.0001602172852,665.5001220703125
AudioSynthSimpleDrum     drum1;          //xy=689.5001525878906,217.50012397766113
AudioSynthSimpleDrum     drum2;          //xy=697.5001525878906,277.00014209747314
AudioSynthSimpleDrum     drum3;          //xy=700.0001602172852,330.5001220703125
AudioSynthSimpleDrum     drum4;          //xy=700.0001564025879,384.5001211166382
AudioPlaySdRaw           playTestRaw;     //xy=701.6667022705078,125.00000762939453
AudioAnalyzePeak         peakWavR;       //xy=836.0001754760742,578.0001616477966
AudioAnalyzePeak         peakWavL;       //xy=836.5001754760742,471.5001287460327
AudioEffectFreeverbStereo fxfreeverbs;    //xy=859.0001602172852,665.5001220703125
AudioMixer4              mixer1;         //xy=906.0001602172852,300.5001220703125
AudioAnalyzePeak         peakfreeverbsR; //xy=1088.000244140625,767.5001602172852
AudioAnalyzePeak         peakfreeverbsL; //xy=1090.0001602172852,722.5001220703125
AudioAnalyzePeak         peakAudio01;    //xy=1092.0001602172852,238.5001220703125
AudioAnalyzePeak         peakAudioInputL; //xy=1090.000244140625,820.0001630783081
AudioAnalyzePeak         peakAudioInputR; //xy=1094.000244140625,868.500165939331
AudioMixer4              mixerGroupL0;   //xy=1300.5002555847168,361.50012588500977
AudioMixer4              mixerGroupL1;   //xy=1300.5002555847168,428.50012588500977
AudioMixer4              mixerGroupL2;   //xy=1300.5002555847168,495.50012588500977
AudioMixer4              mixerGroupL3;   //xy=1300.5002555847168,564.5001258850098
AudioMixer4              mixerGroupR0;   //xy=1300.5002555847168,635.5001258850098
AudioMixer4              mixerGroupR1;   //xy=1300.5002555847168,703.5001258850098
AudioMixer4              mixerGroupR2;   //xy=1300.5002555847168,772.5001258850098
AudioMixer4              mixerGroupR3;   //xy=1300.5002555847168,839.5001258850098
AudioMixer4              masterMixerL;   //xy=1537.5002555847168,569.5001258850098
AudioMixer4              masterMixerR;   //xy=1537.5002555847168,640.5001258850098
AudioAnalyzePeak         peakAudioOutputR; //xy=1714.5002555847168,818.5001258850098
AudioAnalyzePeak         peakAudioOutputL; //xy=1715.5002555847168,776.5001258850098
AudioOutputI2S           audioOutput;    //xy=1724.5002555847168,602.5001258850098
AudioConnection          patchCord1(audioInput, 0, noiseGateL, 0);
AudioConnection          patchCord2(audioInput, 1, noiseGateR, 0);
AudioConnection          patchCord3(noiseGateR, waveShapeInputR);
AudioConnection          patchCord4(noiseGateR, queueRecordR);
AudioConnection          patchCord5(noiseGateL, biquadInputL);
AudioConnection          patchCord6(noiseGateL, queueRecordL);
AudioConnection          patchCord7(playSdWavA, 0, biquadWavAL, 0);
AudioConnection          patchCord8(playSdWavA, 1, biquadWavAR, 0);
AudioConnection          patchCord9(waveShapeInputR, biquadInputR);
AudioConnection          patchCord10(biquadInputR, peakAudioInputR);
AudioConnection          patchCord11(biquadInputR, 0, mixerGroupL0, 1);
AudioConnection          patchCord12(biquadInputR, 0, mixerGroupR0, 1);
AudioConnection          patchCord13(biquadInputR, biquadfreeverbs);
AudioConnection          patchCord14(biquadInputL, peakAudioInputL);
AudioConnection          patchCord15(biquadInputL, 0, mixerGroupL0, 0);
AudioConnection          patchCord16(biquadInputL, 0, mixerGroupR0, 0);
AudioConnection          patchCord17(biquadWavAL, 0, mixerGroupL0, 3);
AudioConnection          patchCord18(biquadWavAL, peakWavL);
AudioConnection          patchCord19(biquadWavAR, 0, mixerGroupR0, 3);
AudioConnection          patchCord20(biquadWavAR, peakWavR);
AudioConnection          patchCord21(biquadfreeverbs, fxfreeverbs);
AudioConnection          patchCord22(drum1, 0, mixer1, 0);
AudioConnection          patchCord23(drum2, 0, mixer1, 1);
AudioConnection          patchCord24(drum3, 0, mixer1, 2);
AudioConnection          patchCord25(drum4, 0, mixer1, 3);
AudioConnection          patchCord26(playTestRaw, 0, mixerGroupL1, 1);
AudioConnection          patchCord27(fxfreeverbs, 0, mixerGroupL1, 0);
AudioConnection          patchCord28(fxfreeverbs, 0, peakfreeverbsL, 0);
AudioConnection          patchCord29(fxfreeverbs, 1, mixerGroupR1, 0);
AudioConnection          patchCord30(fxfreeverbs, 1, peakfreeverbsR, 0);
AudioConnection          patchCord31(mixer1, 0, mixerGroupL0, 2);
AudioConnection          patchCord32(mixer1, 0, mixerGroupR0, 2);
AudioConnection          patchCord33(mixer1, peakAudio01);
AudioConnection          patchCord34(mixerGroupL0, 0, masterMixerL, 0);
AudioConnection          patchCord35(mixerGroupL1, 0, masterMixerL, 1);
AudioConnection          patchCord36(mixerGroupL2, 0, masterMixerL, 2);
AudioConnection          patchCord37(mixerGroupL3, 0, masterMixerL, 3);
AudioConnection          patchCord38(mixerGroupR0, 0, masterMixerR, 0);
AudioConnection          patchCord39(mixerGroupR1, 0, masterMixerR, 1);
AudioConnection          patchCord40(mixerGroupR2, 0, masterMixerR, 2);
AudioConnection          patchCord41(mixerGroupR3, 0, masterMixerR, 3);
AudioConnection          patchCord42(masterMixerL, 0, audioOutput, 0);
AudioConnection          patchCord43(masterMixerL, peakAudioOutputL);
AudioConnection          patchCord44(masterMixerR, 0, audioOutput, 1);
AudioConnection          patchCord45(masterMixerR, peakAudioOutputR);
AudioControlSGTL5000     audioShield;    //xy=1720.5002555847168,649.5001258850098
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
	
	//mixerGroupL1.gain(1, 0);
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


void AudioCoreClass::setWavBiquad(float frequency, float q) {

	biquadWavAL.setLowpass(0, frequency, q);
	biquadWavAR.setLowpass(0, frequency, q);
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

 void AudioCoreClass::setWavVolume(float vol, float balance)
 {	 
	 setBalancedVolume(3, vol, balance);
 }

 void AudioCoreClass::setLeftInputVolume(float vol, float balance)
 {
	 setBalancedVolume(0, vol, balance);
 }

void AudioCoreClass::setBalancedVolume(uint8_t channel,  float vol, float balance)
{
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

void AudioCoreClass::playRaw(const char * song)
{
	playTestRaw.play(song);
}

void AudioCoreClass::stopWav()
{
	playSdWavA.stop();
}

bool AudioCoreClass::wavIsPlaying()
{
	return playSdWavA.isPlaying();
}

bool AudioCoreClass::isRecording()
{
	return _isRecording;
}

bool AudioCoreClass::startRecording(const char * song) {
	if (_isRecording)
	{
		stopRecording();
	}
	Serial.println("startRecording");
	if (SD.exists(song)) {
		// The SD library writes new data to the end of the
		// file, so to start a new recording, the old file
		// must be deleted before new data is written.
		SD.remove(song);
	}
	frecL = SD.open(song, FILE_WRITE);
	if (frecL) {
		queueRecordR.begin();				
		_isRecording = true;
		return true;
	}
	return false;
}

void AudioCoreClass::continueRecording() {
	if (_isRecording &&  queueRecordR.available() >= 2) {
		byte buffer[512];
		// Fetch 2 blocks from the audio library and copy
		// into a 512 byte buffer.  The Arduino SD library
		// is most efficient when full 512 byte sector size
		// writes are used.
		memcpy(buffer, queueRecordR.readBuffer(), 256);
		queueRecordR.freeBuffer();
		memcpy(buffer + 256, queueRecordR.readBuffer(), 256);
		queueRecordR.freeBuffer();
		// write all 512 bytes to the SD card
		elapsedMicros usec = 0;
		frecL.write(buffer, 512);
		// Uncomment these lines to see how long SD writes
		// are taking.  A pair of audio blocks arrives every
		// 5802 microseconds, so hopefully most of the writes
		// take well under 5802 us.  Some will take more, as
		// the SD library also must write to the FAT tables
		// and the SD card controller manages media erase and
		// wear leveling.  The queue1 object can buffer
		// approximately 301700 us of audio, to allow time
		// for occasional high SD card latency, as long as
		// the average write time is under 5802 us.
		//Serial.print("SD write, us=");
		//Serial.println(usec);
	}
}

void AudioCoreClass::stopRecording() {
	Serial.println("stopRecording");
	queueRecordR.end();
	if (_isRecording) {
		while (queueRecordR.available() > 0) {
			frecL.write((byte*)queueRecordR.readBuffer(), 256);
			queueRecordR.freeBuffer();
		}
		frecL.close();
	}
	_isRecording = false;
}


AudioCoreClass AudioCore;

