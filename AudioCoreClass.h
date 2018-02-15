// AudioCoreClass.h

#ifndef _AUDIOCORE_h
#define _AUDIOCORE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Audio.h>
#include <synth_simple_drum.h>

class AudioCoreClass
{
 protected:
	 // GUItool: begin automatically generated code
	 AudioSynthSimpleDrum     drum2;          //xy=129,193
	 AudioSynthSimpleDrum     drum3;          //xy=154,259
	 AudioSynthSimpleDrum     drum1;          //xy=161,146
	 AudioSynthSimpleDrum     drum4;          //xy=194,323
	 AudioPlaySerialflashRaw  playFlashRaw1;  //xy=213.01045989990234,467.0104455947876
	 AudioMixer4              mixer1;         //xy=467,214
	 AudioMixer4              mixer2;         //xy=473.0104217529297,300.01042556762695
	 AudioMixer4              mixer3;         //xy=644.0106735229492,248.01044845581055
	 AudioOutputI2S           i2s1;           //xy=786.0000495910645,190.0000057220459
	 AudioControlSGTL5000     sgtl5000_1;     //xy=660,467
											  // GUItool: end automatically generated code

 public:
	AudioCoreClass();
	static void init();
	void drumc1();
	void drumc2();
	void drumc3();
	void drumc4();
};


extern AudioCoreClass AudioCore;

#endif

