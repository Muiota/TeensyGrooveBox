// Engine.h

#ifndef _ENGINE_h
#define _ENGINE_h

#include "c:\Program Files (x86)\Arduino\libraries\ArduinoJson\ArduinoJson.h"
#include "DisplayCore.h"
#include "HardwareCore.h"
#include "AudioCore.h"

typedef struct {
	float masterVolume = 0.6f;
} MasterSettings;

typedef struct {
	float volume = 1.0f;
	float balance = 0.0f;
	float frequency = 12000.0f;
	float q = 0.707f;
} ChannelSettings;


class EngineClass
{
 protected:
	 elapsedMillis _hardwareTimer;
	 bool _current[16];
	
 public:
	static void updateModeLinks();	
	static void saveChannelPart(JsonObject& mixer, String channelName,  ChannelSettings& setting);
	static void saveSettings();
	static void loadSettings();
	static void init();
	static void muteMaster();
	static void startWavTrack();
	static void stopWavTrack();
	static void changeWavTrack();
	static void changeMode();
	static void changeEditType();
	static void setWavLowpass(int encoder, int value);
	static void setLeftInputHighpass(int encoder, int value);
	static void setLeftInputBalance(int encoder, int value);
	static void setWavBalance(int encoder, int value);	
	static void setRightInputBalance(int encoder, int value);
	static void setReverbBalance(int encoder, int value);	
	static void setRightInputHighpass(int encoder, int value);
	static void setReverbHighpass(int encoder, int value);
	static void setMasterVolume(int encoder, int value);
	static void setWavVolume(int encoder, int value);
	static void setLeftInputVolume(int encoder, int value);
	static void setRightInputVolume(int encoder, int value);
	static void setReverbVolume(int encoder, int value);
	void update();
};

extern EngineClass Engine;

#endif

