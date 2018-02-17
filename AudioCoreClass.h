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

class AudioCoreClass2
{
 protected:
					

 public:
	AudioCoreClass();
	static void init();
	void drumc1();
	void drumc2();
	void drumc3();
	void drumc4();
};


#endif

