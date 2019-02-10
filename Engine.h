// Engine.h

#ifndef _ENGINE_h
#define _ENGINE_h

#include "c:\Program Files (x86)\Arduino\libraries\ArduinoJson\ArduinoJson.h"
#include "DisplayCore.h"
#include "HardwareCore.h"
#include "AudioCore.h"
#include "Mixer.h"
#include "SongLoader.h"
#include "WavePlayer.h"
#include "Equalizer.h"


typedef struct
{
	float volume = 1.0f;
	bool isSolo = false;
	bool isOn = true;
} BaseSettings;

typedef struct : BaseSettings
{
} MasterSettings;

enum equalizer_type
{
	LOWPASS = 0,
	HIGHPASS = 1,
	BANDPASS = 2,
	NOTCH = 3,
	PEAK = 4,
	LOW_SHELF = 5,
	HIGH_SHELF = 6,
	//ONE_POLE_LP = 7,
	//ONE_POLE_HP = 8
};

/*
#define FILTER_LOPASS 0
#define FILTER_HIPASS 1
#define FILTER_BANDPASS 2
#define FILTER_NOTCH 3
#define FILTER_PARAEQ 4
#define FILTER_LOSHELF 5
#define FILTER_HISHELF 6
*/

typedef struct : BaseSettings
{
	float balance = 0.0f;
	float eqFc = 12000.0f;
	float eqSlope = 1.0f;
	float eqQ = 0.707f;
	float eqGain = -6;
	equalizer_type eqType = HIGH_SHELF;
} ChannelSettings;

//Настройки реквербератора
typedef struct : ChannelSettings
{
	float roomsize = 0.1f;
	float damping = 1.0f;
} FxReverbChannelSettings;

//Настройки лупера
typedef struct : ChannelSettings
{
	String wavName = "";
	bool isPlayWave = false;
} LooperSettings;

enum edit_channel
{
	EDIT_CHANNEL_INPUT_MIC = 0,
	EDIT_CHANNEL_INPUT_GUITAR = 1,
	EDIT_CHANNEL_DRUMS = 2,
	EDIT_CHANNEL_BASS = 3,
	EDIT_CHANNEL_STRINGS = 4,
	EDIT_CHANNEL_PIANO =5,
	EDIT_CHANNEL_FM = 6,
	EDIT_CHANNEL_LOOPER = 7,
	EDIT_CHANNEL_SEND_FX_REVERB = 8,
	EDIT_CHANNEL_SEND_FX_CHORUS = 9,
	EDIT_CHANNEL_SEND_FX_DELAY = 10,
	EDIT_CHANNEL_MASTER = 11
};

enum edit_cnannel_mode
{
	EDIT_CHANNEL_MODE_MAIN = 0,		//Основная 
	EDIT_CHANNEL_MODE_SETTINGS = 1, //Настройки
};


enum current_view_mode
{
	VIEW_MODE_MAIN_MIXER = 0, //Режим микшера
	VIEW_MODE_EDIT_PARAMETERS = 1, //Настройки канала
	VIEW_MODE_EDIT_LOOPER_CHANNEL = 2, //Редактирование инструмента,
	VIEW_MODE_SEQUENCER = 3, //Редактирование песни
	VIEW_MODE_OPEN_SONG = 4, //Открыть сохраненный файл,
	VIEW_MODE_EQUALIZER = 5 //Открыть сохраненный файл
};


//Каналы
typedef struct
{
	MasterSettings master;
	LooperSettings looper;
	ChannelSettings leftInput;
	ChannelSettings rightInput;
	FxReverbChannelSettings fxReverb;
} MixerSettings;


//Композиция
typedef struct
{
	current_view_mode viewMode; //По умолчанию режим микшера
	edit_channel currentChannel;
	edit_cnannel_mode currentView;
	MixerSettings mixer;
	String name;
	String path;
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
	void drawTopPanel() const;
	static void assignDefaultButtons();

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
	static void setLooperVolume(int encoder, int value);
	static void setLeftInputVolume(int encoder, int value);
	static void setRightInputVolume(int encoder, int value);
	static void setReverbVolume(int encoder, int value); */
	static void startTrack(bool pressed);
	static void stopTrack(bool pressed);
	void update();
	void switchWindow(current_view_mode current_view_mode);	
	static void backToMixer(bool pressed);
};

extern EngineClass Engine;

#endif

