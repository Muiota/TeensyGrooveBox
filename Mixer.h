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
	static void switchToSongLoader(bool pressed);
	static void subMenuShow(bool pressed);
};
extern MixerClass Mixer;

#endif

