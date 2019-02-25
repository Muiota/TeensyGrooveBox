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
AudioPlaySdWav           playSdWavA;     //xy=66.5,1820.4452514648438
AudioInputI2S            audioInput;     //xy=105.22221374511719,2865.5556640625
AudioFilterBiquad        biquadLooperAL;    //xy=249.0000762939453,1796.8891296386719
AudioFilterBiquad        biquadLooperAR;    //xy=249.88888549804688,1842.4447937011719
AudioEffectGate          noiseGateR;     //xy=357.4444580078125,2896.6670532226562
AudioEffectGate          noiseGateL;     //xy=359.55560302734375,2846.222412109375
AudioSynthKarplusStrong  string;        //xy=400.00006103515625,2228.5714111328125
AudioSynthKarplusStrong  piano;        //xy=400.00006103515625,2275.7140502929688
AudioSynthKarplusStrong  fm;        //xy=400,2324.2855224609375
AudioSynthKarplusStrong  bass;        //xy=402.22235107421875,2177.778076171875
AudioAnalyzePeak         peakLooperL;       //xy=453.5555419921875,1796.6669921875
AudioAnalyzePeak         peakLooperR;       //xy=453.5556640625,1841.4447326660156
AudioEffectWaveshaper    waveShapeInputR; //xy=524.6666259765625,2896.55615234375
AudioFilterBiquad        biquadBass;        //xy=562.8571428571428,2138.5714285714284
AudioFilterBiquad        biquadFm;        //xy=581.4285714285713,2365.7142857142853
AudioFilterBiquad        biquadPiano;        //xy=590,2308.5714285714284
AudioFilterBiquad        biquadString;        //xy=595.7142857142857,2235.7142857142853
AudioFilterBiquad        biquadInputL;   //xy=693.7777099609375,2847.0001220703125
AudioFilterBiquad        biquadInputR;   //xy=694,2896.666748046875
AudioSynthSimpleDrum     drum4;          //xy=729.7779541015625,1758.555419921875
AudioSynthSimpleDrum     drum3;          //xy=730.8888244628906,1713.4446411132812
AudioSynthSimpleDrum     drum2;          //xy=733.4442749023438,1676.0000915527344
AudioSynthSimpleDrum     drum1;          //xy=734.333251953125,1632.6670532226562
AudioAnalyzePeak         peakAudioInputR; //xy=981.5555419921875,2983.6663818359375
AudioAnalyzePeak         peakAudioInputL; //xy=982.0001220703125,2937.8892211914062
AudioMixer4              mixer1;         //xy=1022.4443359375,1657.8890991210938
AudioFilterBiquad        biquadfreeverbs; //xy=1016.77783203125,3220.666748046875
AudioEffectFreeverbStereo fxfreeverbs;    //xy=1175.444580078125,3219.5552978515625
AudioFilterBiquad        biquadDrums;        //xy=1212.857177734375,1727.1428833007812
AudioAnalyzePeak         peakAudio01;    //xy=1217.3333740234375,1659.2225646972656
AudioAnalyzePeak         peakfreeverbsR; //xy=1431.111083984375,3240.4447021484375
AudioAnalyzePeak         peakfreeverbsL; //xy=1432,3184.333465576172
AudioMixer4              mixerGroupL0;   //xy=1452,2240
AudioMixer4              mixerGroupL1;   //xy=1452,2307
AudioMixer4              mixerGroupL2;   //xy=1452,2374
AudioMixer4              mixerGroupR0;   //xy=1452,2514
AudioMixer4              mixerGroupR1;   //xy=1452,2582
AudioMixer4              mixerGroupR2;   //xy=1452,2651
AudioMixer4              masterMixerL;   //xy=1689,2448
AudioMixer4              masterMixerR;   //xy=1689,2519
AudioOutputI2S           audioOutput;    //xy=1920.4444580078125,2477.6665954589844
AudioAnalyzePeak         peakAudioOutputR; //xy=1931.5556030273438,2693.6668090820312
AudioAnalyzePeak         peakAudioOutputL; //xy=1938.1111450195312,2622.7786254882812
AudioConnection          patchCord1(playSdWavA, 0, biquadLooperAL, 0);
AudioConnection          patchCord2(playSdWavA, 1, biquadLooperAR, 0);
AudioConnection          patchCord3(audioInput, 0, noiseGateL, 0);
AudioConnection          patchCord4(audioInput, 1, noiseGateR, 0);
AudioConnection          patchCord5(biquadLooperAL, 0, mixerGroupL0, 3);
AudioConnection          patchCord6(biquadLooperAL, peakLooperL);
AudioConnection          patchCord7(biquadLooperAR, 0, mixerGroupR0, 3);
AudioConnection          patchCord8(biquadLooperAR, peakLooperR);
AudioConnection          patchCord9(noiseGateR, waveShapeInputR);
AudioConnection          patchCord10(noiseGateL, biquadInputL);
AudioConnection          patchCord11(string, biquadString);
AudioConnection          patchCord12(piano, biquadPiano);
AudioConnection          patchCord13(fm, biquadFm);
AudioConnection          patchCord14(bass, biquadBass);
AudioConnection          patchCord15(waveShapeInputR, biquadInputR);
AudioConnection          patchCord16(biquadBass, 0, mixerGroupL1, 1);
AudioConnection          patchCord17(biquadBass, 0, mixerGroupR1, 1);
AudioConnection          patchCord18(biquadFm, 0, mixerGroupL2, 0);
AudioConnection          patchCord19(biquadFm, 0, mixerGroupR2, 0);
AudioConnection          patchCord20(biquadPiano, 0, mixerGroupL1, 3);
AudioConnection          patchCord21(biquadPiano, 0, mixerGroupR1, 3);
AudioConnection          patchCord22(biquadString, 0, mixerGroupL1, 2);
AudioConnection          patchCord23(biquadString, 0, mixerGroupR1, 2);
AudioConnection          patchCord24(biquadInputL, peakAudioInputL);
AudioConnection          patchCord25(biquadInputL, 0, mixerGroupL0, 0);
AudioConnection          patchCord26(biquadInputL, 0, mixerGroupR0, 0);
AudioConnection          patchCord27(biquadInputR, peakAudioInputR);
AudioConnection          patchCord28(biquadInputR, 0, mixerGroupL0, 1);
AudioConnection          patchCord29(biquadInputR, 0, mixerGroupR0, 1);
AudioConnection          patchCord30(biquadInputR, biquadfreeverbs);
AudioConnection          patchCord31(drum4, 0, mixer1, 3);
AudioConnection          patchCord32(drum3, 0, mixer1, 2);
AudioConnection          patchCord33(drum2, 0, mixer1, 1);
AudioConnection          patchCord34(drum1, 0, mixer1, 0);
AudioConnection          patchCord35(mixer1, peakAudio01);
AudioConnection          patchCord36(mixer1, biquadDrums);
AudioConnection          patchCord37(biquadfreeverbs, fxfreeverbs);
AudioConnection          patchCord38(fxfreeverbs, 0, mixerGroupL1, 0);
AudioConnection          patchCord39(fxfreeverbs, 0, peakfreeverbsL, 0);
AudioConnection          patchCord40(fxfreeverbs, 1, mixerGroupR1, 0);
AudioConnection          patchCord41(fxfreeverbs, 1, peakfreeverbsR, 0);
AudioConnection          patchCord42(biquadDrums, 0, mixerGroupL0, 2);
AudioConnection          patchCord43(biquadDrums, 0, mixerGroupR0, 2);
AudioConnection          patchCord44(mixerGroupL0, 0, masterMixerL, 0);
AudioConnection          patchCord45(mixerGroupL1, 0, masterMixerL, 1);
AudioConnection          patchCord46(mixerGroupL2, 0, masterMixerL, 2);
AudioConnection          patchCord47(mixerGroupR0, 0, masterMixerR, 0);
AudioConnection          patchCord48(mixerGroupR1, 0, masterMixerR, 1);
AudioConnection          patchCord49(mixerGroupR2, 0, masterMixerR, 2);
AudioConnection          patchCord50(masterMixerL, 0, audioOutput, 0);
AudioConnection          patchCord51(masterMixerL, peakAudioOutputL);
AudioConnection          patchCord52(masterMixerR, 0, audioOutput, 1);
AudioConnection          patchCord53(masterMixerR, peakAudioOutputR);
AudioControlSGTL5000     audioShield;    //xy=1905.33349609375,2532.444580078125
										 // GUItool: end automatically generated code




AudioCoreClass::AudioCoreClass()
{


}

void AudioCoreClass::setupMixer(AudioMixer4& mixer, float gain)
{
	mixer.gain(0, gain);
	mixer.gain(1, gain);
	mixer.gain(2, gain);
	mixer.gain(3, gain);
}

void AudioCoreClass::init()
{
	
	// audio library init
	AudioMemory(60);

	//next = millis() + 1000;

//	AudioNoInterrupts(); //swith off library

	//todo other drums
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


	setupMixer(masterMixerL, 1);
	masterMixerL.gain(3, 0);
	setupMixer(masterMixerR, 1);
	masterMixerL.gain(3, 0);
	
	setupMixer(mixerGroupL0, 0);
	setupMixer(mixerGroupL1, 0);
	setupMixer(mixerGroupL2, 0);
	
	setupMixer(mixerGroupR0, 0);
	setupMixer(mixerGroupR1, 0);
	setupMixer(mixerGroupR2, 0);
	
	//todo good filter
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
/*
void AudioCoreClass::setReverbRoom(float damping, float roomsize)
{
	fxfreeverbs.damping(damping);
	fxfreeverbs.roomsize(roomsize);
}
*/




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

void AudioCoreClass::setEqBiquad(uint8_t channel, int* coefs) {
	Serial.print("eq-");
	Serial.print(channel);
	Serial.print("-");
	Serial.print(coefs[0]);
	Serial.print("-");
	Serial.print(coefs[1]);
	Serial.print("-");
	Serial.print(coefs[2]);
	Serial.print("-");
	Serial.print(coefs[3]);
	Serial.print("-");
	Serial.println(coefs[4]);
	switch (channel)
	{
	case 0: //EDIT_CHANNEL_INPUT_MIC
		biquadInputL.setCoefficients(0, coefs);
		break;
	case 1: //EDIT_CHANNEL_INPUT_GUITAR
		biquadInputR.setCoefficients(0, coefs);
		break;
	case 2: //EDIT_CHANNEL_DRUMS
		biquadDrums.setCoefficients(0, coefs);
		break;
	case 3: //EDIT_CHANNEL_BASS
		biquadBass.setCoefficients(0, coefs);
		break;
	case 4: //EDIT_CHANNEL_STRINGS
		biquadString.setCoefficients(0, coefs);
		break;
	case 5: //EDIT_CHANNEL_PIANO
		biquadPiano.setCoefficients(0, coefs);
		break;
	case 6: //EDIT_CHANNEL_FM
		biquadPiano.setCoefficients(0, coefs);
		break;
	case 7: //EDIT_CHANNEL_LOOPER
		biquadLooperAL.setCoefficients(0, coefs);
		biquadLooperAR.setCoefficients(0, coefs);
		break;
	case 8: //EDIT_CHANNEL_SEND_FX_REVERB
		//biquadPiano.setCoefficients(0, coefs); //todo
		break;
	case 9: //EDIT_CHANNEL_SEND_FX_CHORUS
		//todo
		break;
	case 10: //EDIT_CHANNEL_SEND_FX_DELAY
		//todo
		break;
	case 11: //EDIT_CHANNEL_MASTER
		//todo
		break;
	default: ;
	}

	
}

void AudioCoreClass::setBalancedVolume(uint8_t channel,  float vol, float balance)
{
//	Serial.println(String(channel)+" "+ String(vol)+" "+ String(balance));
	AudioMixer4* targetMixerGroupL = nullptr;
	AudioMixer4* targetMixerGroupR = nullptr;
	int targetChannel = 0;

	switch (channel)
	{
	case 0: //EDIT_CHANNEL_INPUT_MIC
		targetMixerGroupL = &mixerGroupL0;
		targetMixerGroupR = &mixerGroupR0;
		targetChannel = 0;
		break;
	case 1: //EDIT_CHANNEL_INPUT_GUITAR
		targetMixerGroupL = &mixerGroupL0;
		targetMixerGroupR = &mixerGroupR0;
		targetChannel = 1;
		break;
	case 2: //EDIT_CHANNEL_DRUMS
		targetMixerGroupL = &mixerGroupL0;
		targetMixerGroupR = &mixerGroupR0;
		targetChannel = 2;
		break;
	case 3: //EDIT_CHANNEL_BASS
		targetMixerGroupL = &mixerGroupL1;
		targetMixerGroupR = &mixerGroupR1;
		targetChannel = 1;
		break;
	case 4: //EDIT_CHANNEL_STRINGS
		targetMixerGroupL = &mixerGroupL1;
		targetMixerGroupR = &mixerGroupR1;
		targetChannel = 2;
		break;
	case 5: //EDIT_CHANNEL_PIANO
		targetMixerGroupL = &mixerGroupL1;
		targetMixerGroupR = &mixerGroupR1;
		targetChannel = 3;
		break;
	case 6: //EDIT_CHANNEL_FM
		targetMixerGroupL = &mixerGroupL2;
		targetMixerGroupR = &mixerGroupR2;
		targetChannel = 0;
		break;
	case 7: //EDIT_CHANNEL_LOOPER
		targetMixerGroupL = &mixerGroupL0;
		targetMixerGroupR = &mixerGroupR0;
		targetChannel = 3;
		break;
	case 8: //EDIT_CHANNEL_SEND_FX_REVERB
			//biquadPiano.setCoefficients(0, coefs); //todo
		break;
	case 9: //EDIT_CHANNEL_SEND_FX_CHORUS
			//todo
		break;
	case 10: //EDIT_CHANNEL_SEND_FX_DELAY
			 //todo
		break;
	case 11: //EDIT_CHANNEL_MASTER
		AudioCore.setMasterVolume(vol);

		if (balance == 0)
		{			
			setupMixer(masterMixerL, 1);			
			setupMixer(masterMixerR, 1);			
		}
		else if (balance > 0)
		{
			setupMixer(masterMixerL, 1);
			setupMixer(masterMixerR, (1.0 - balance));		
		}
		else
		{
			setupMixer(masterMixerR, 1);			
			setupMixer(masterMixerL, (1.0 + balance));			
		}
		masterMixerL.gain(3, 0);
		masterMixerR.gain(3, 0);
		break;
	default:;
	}

	if (targetMixerGroupL == nullptr || targetMixerGroupR == nullptr)
	{
		return;
	}

	if (balance == 0)
	{
		targetMixerGroupL->gain(targetChannel, vol);
		targetMixerGroupR->gain(targetChannel, vol);
	}
	else if (balance > 0)
	{
		targetMixerGroupL->gain(targetChannel, vol);
		targetMixerGroupR->gain(targetChannel, vol * (1.0 - balance));

	}
	else
	{
		targetMixerGroupR->gain(targetChannel, vol);
		targetMixerGroupL->gain(targetChannel, vol * (1.0 + balance));
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
	if (peakLooperL.available())
	{
		return peakLooperL.read();
	}
	return 0;
}

float AudioCoreClass::getWavPeakR()
{
	if (peakLooperR.available())
	{
		return peakLooperR.read();
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


