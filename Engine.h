// Engine.h

#ifndef _ENGINE_h
#define _ENGINE_h

#include "DisplayCore.h"
#include "HardwareCore.h"
#include "AudioCore.h"


class EngineClass
{
 protected:
	 elapsedMillis _hardwareTimer;
	 bool _current[16];	
 public:
	void drawMode();
	void init();
	static void startWavTrack();
	static void stopWavTrack();
	static void changeWavTrack();
	static void setWavLowpass(int encoder, int value);
	static void setMasterVolume(int encoder, int value);
	void update();
};

extern EngineClass Engine;

#endif

