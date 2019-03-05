// AudioCore.h

#ifndef _AUDIOCORE_h
#define _AUDIOCORE_h

#include <Audio.h>
#include <i2c_t3.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//#include <OpenAudio_ArduinoLibrary.h> 
//#include <synth_simple_drum.h>



class AudioCoreClass
{
 protected:
	 static void setupMixer(AudioMixer4& mixer, float gain);	 
 public:	
	AudioCoreClass();

	static void init();
	//static void setReverbRoom(float damping, float roomsize);
	static void setEqBiquad(uint8_t channel, int* coefs);
	static void setBalancedVolume(uint8_t channel, float vol, float balance);
	static void drum1On();
	static void drum2On();
	static void drum3On();
	static void drum4On();

	static void setMasterVolume(float x);
	static void enhanceBass(bool enable);
	//static void setLooperVolume(float vol, float balance);
//	static void setLeftInputVolume(float vol, float balance);

//	static void setRightInputVolume(float vol, float balance);
//	static void setReverbVolume(float vol, float balance);
	static float getPeakL();
	static float getPeakR();
	static float getWavPeakL();
	static float getWavPeakR();
	static float getReverbFxPeakL();
	static float getReverbFxPeakR();
	static float getPeakAudioInputL();
	static float getPeakAudioInputR();

	static bool wavIsPlaying();	
	static String getRecordFileName(String prefix, uint8_t songNum, uint16_t version);
	static uint16_t getMaxRecordedTracks(uint8_t songNum);
	static void stopRecording();
	
	static void playWav(const char *song);
	static void playRawDrum(const char *song, float gain, uint8_t channel);
	static void loadRaw(const char* song);
	static void stopWav();

	static void playLastRecorderInputRaw();


};
extern AudioCoreClass AudioCore;

#endif

