// Engine.h

#ifndef _ENGINE_h
#define _ENGINE_h

#include "c:\Program Files (x86)\Arduino\libraries\ArduinoJson\ArduinoJson.h"
#include "Enums.h"
#include "DisplayCore.h"
#include "HardwareCore.h"
#include "AudioCore.h"
#include "Mixer.h"
#include "SongLoader.h"
#include "WavePlayer.h"


typedef struct
{
	float volume = 1.0f;
	bool isSolo = false;
	bool isOn = true;
} BaseSettings;

typedef struct : BaseSettings
{
} MasterSettings;

typedef struct : BaseSettings
{
	float balance = 0.0f;
	float frequency = 12000.0f;
	float q = 0.707f;
} ChannelSettings;

typedef struct : ChannelSettings
{
	float roomsize = 0.1f;
	float damping = 1.0f;
} FxReverbChannelSettings;

enum edit_channel
{
	EDIT_CHANNEL_INPUT_MIC = 0,
	EDIT_CHANNEL_INPUT_GUITAR = 1,
	EDIT_CHANNEL_DRUMS = 2,
	EDIT_CHANNEL_BASS = 3,
	EDIT_CHANNEL_STRINGS = 4,
	EDIT_CHANNEL_PIANO =5,
	EDIT_CHANNEL_FM = 6,
	EDIT_CHANNEL_WAVE = 7,
	EDIT_CHANNEL_SEND_FX_REVERB = 8,
	EDIT_CHANNEL_SEND_FX_CHORUS = 9,
	EDIT_CHANNEL_SEND_FX_DELAY = 10,
	EDIT_CHANNEL_MASTER = 11
};

enum edit_cnannel_mode
{
	EDIT_CHANNEL_MODE_EQ = 0, //Еквалайзер 
	EDIT_CHANNEL_MODE_BALANCE = 1, //Баланс
};

enum edit_fx_reverb_mode
{
	EDIT_FX_REVERB_MODE_EQ = 0, //Редактирование эквалайзера
	EDIT_FX_REVERB_MODE_BALANCE = 1, //Редактирование баланса
	EDIT_FX_REVERB_MODE_ROOM = 2 //Редактирование остального
};

enum current_view_mode
{
	VIEW_MODE_MAIN_MIXER = 0, //Режим микшера
	VIEW_MODE_EDIT_PARAMETERS = 1, //Настройки канала
	VIEW_MODE_EDIT_CHANNEL = 2, //Редактирование инструмента,
	VIEW_MODE_SEQUENCER = 3, //Редактирование песни
	VIEW_MODE_OPEN_SONG = 4 //Открыть сохраненный файл
};


//Каналы
typedef struct
{
	MasterSettings master;
	ChannelSettings wav;
	ChannelSettings leftInput;
	ChannelSettings rightInput;
	FxReverbChannelSettings fxReverb;
} MixerSettings;


//Композиция
typedef struct
{
	current_view_mode viewMode; //По умолчанию режим микшера
	edit_channel currentChannel;
	MixerSettings mixer;
	String name;
} SongSettings;


class EngineClass
{
protected:
	elapsedMillis _hardwareTimer;
	uint8_t _tickCounter;
public:
	//static void updateModeLinks();	
	SongSettings songSettings;
	bool isValidScreen;	
	static JsonObject& saveChannelPart(JsonObject& mixer, String channelName, ChannelSettings& setting);

	static void saveSettings(bool pressed);
	static void loadSettings(bool pressed);
	static void init();

	static void saveChannelPartFxReverb(JsonObject& mixer, String channelName, FxReverbChannelSettings& setting);
	//static void changeMode();
	//static void changeEditType();
	//static void muteMaster();
	//static void startWavTrack();
	//static void stopWavTrack();
	//static void changeWavTrack();
	/*static void setWavLowpass(int encoder, int value);
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
	static void setReverbVolume(int encoder, int value); */
	 void update();
	void switchWindow(current_view_mode current_view_mode);
	void saveSettings();
};

extern EngineClass Engine;

#endif

