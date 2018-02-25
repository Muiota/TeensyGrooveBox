// Engine.h

#ifndef _ENGINE_h
#define _ENGINE_h

#include "HardwareCore.h"
#include "DisplayCore.h"
#include "AudioCore.h"


class EngineClass
{
 protected:
	 elapsedMillis _hardwareTimer;
	 bool _current[16];
	 uint8_t _currentEncoder[3];
 public:
	void init();
	void update();
};

extern EngineClass Engine;

#endif

