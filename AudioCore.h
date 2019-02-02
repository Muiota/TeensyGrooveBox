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
	 static void setBalancedVolume(uint8_t channel, float vol, float balance);	
 public:	
	AudioCoreClass();
	void init();
	static void setReverbRoom(float damping, float roomsize);
	static void setLooperEqBiquad(int* coefs);
	static void setLeftInputBiquad(float frequency, float q);
	static void setRightInputBiquad(float frequency, float q);
	static void setReverbBiquad(float frequency, float q);
	static void drum1On();
	static void drum2On();
	static void drum3On();
	static void drum4On();
	static void setMasterVolume(float x);
	static void enhanceBass(bool enable);
	static void setLooperVolume(float vol, float balance);
	static void setLeftInputVolume(float vol, float balance);

	static void setRightInputVolume(float vol, float balance);
	static void setReverbVolume(float vol, float balance);
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
	static void playWav(const char * song);
	static void playLastRecorderInputRaw();
	static void stopWav();

};
extern AudioCoreClass AudioCore;

#endif

