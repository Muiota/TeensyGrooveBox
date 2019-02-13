// Mixer.h

#ifndef _MIXER_h
#define _MIXER_h
#include "AudioCore.h"


class MixerClass
{
protected:		
	

public:	
	static void handle();	
	static void onShow();
	static void selectChanel(int encoder, int value);
	static void switchToChannel();
	static void encoder0press(bool pressed);
	static void encoder1press(bool pressed);
	static void encoder2press(bool pressed);
	static void subMenuShow(bool pressed);
	static void setChannelVolume(int encoder, int value);
};
extern MixerClass Mixer;

#endif

