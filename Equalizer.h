// Mixer.h

#ifndef _EQUALIZER_h
#define _EQUALIZER_h
#include "AudioCore.h"
#include "Engine.h"
class EqualizerClass
{

public:
	static void handle();
	static void onShow();
	

protected:
	static void setFc(int encoder, int value);
	static void setQ(int encoder, int value);
	static void setSlope(int encoder, int value);
	static void setGain(int encoder, int value);
	static void recalc();
};



extern EqualizerClass Equalizer;

#endif

