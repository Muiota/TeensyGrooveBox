// AudioCore.h

#ifndef _AUDIOCORE_h
#define _AUDIOCORE_h

#include <Audio.h>
#include <i2c_t3.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
//#include <synth_simple_drum.h>



class AudioCoreClass
{
 protected:

 public:
	AudioCoreClass();
	void init();
	void drum1On();
	void drum2On();
	void drum3On();
	void drum4On();
	void setVolume(float x);
	float getPeakL();
	float getPeakR();
	float getWavPeakL();
	float getWavPeakR();
	float getPeakAudioInputL();
	float getPeakAudioInputR();
	bool wavIsPlaying();

	void playWav(const char * song);
	void stopWav();
};
extern AudioCoreClass AudioCore;

#endif

