// Engine.h

#ifndef _ENGINE_h
#define _ENGINE_h

#include "c:\Program Files (x86)\Arduino\libraries\ArduinoJson\ArduinoJson.h"
#include "Enums.h"
#include "DisplayCore.h"
#include "HardwareCore.h"
#include "AudioCore.h"
#include "Mixer.h"
#include "WavePlayer.h"



typedef struct {
	int editMode = 0;	
} BaseSettings;

typedef struct : BaseSettings {
	float masterVolume = 0.6f;
} MasterSettings;

typedef struct : BaseSettings {
	float volume = 1.0f;
	float balance = 0.0f;
	float frequency = 12000.0f;
	float q = 0.707f;
} ChannelSettings;



typedef struct : ChannelSettings {	
	float roomsize = 0.1f;
	float damping = 1.0f;	
} FxReverbChannelSettings;

enum edit_channel { //todo расширить
	EDIT_CHANNEL_MASTER = 0,
	EDIT_CHANNEL_FX_REVERB = 1,
	EDIT_CHANNEL_WAV = 2,
	EDIT_CHANNEL_LEFT_CHANNEL = 3,
	EDIT_CHANNEL_RIGHT_CHANNEL = 4,
};

enum edit_cnannel_mode {
	EDIT_CHANNEL_MODE_EQ = 0, //Еквалайзер 
	EDIT_CHANNEL_MODE_BALANCE = 1, //Баланс
};

enum edit_fx_reverb_mode {
	EDIT_FX_REVERB_MODE_EQ = 0, //Редактирование эквалайзера
	EDIT_FX_REVERB_MODE_BALANCE = 1, //Редактирование баланса
	EDIT_FX_REVERB_MODE_ROOM = 2 //Редактирование остального
};

enum current_view_mode {
	MAIN_MIXER = 0, //Режим микшера
	EDIT_PARAMETERS = 1, //Настройки канала
	EDIT_CHANNEL = 2 //Редактирование инструмента
};



class EngineClass
{
 protected:
	 elapsedMillis _hardwareTimer;
	


public:
	
	static void updateModeLinks();	
	static JsonObject& saveChannelPart(JsonObject& mixer, String channelName,  ChannelSettings& setting);
	static int getCurrentMode();
	static void saveChannelPartFxReverb(JsonObject& mixer, String channelName, FxReverbChannelSettings& setting);	
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
	static void setReverbDamping(int encoder, int value);
	static void setReverbRoomsize(int encoder, int value);
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

