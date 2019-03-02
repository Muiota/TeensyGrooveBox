#ifndef _DRUMPATTERN_H
#define _DRUMPATTERN_H

#include "AudioCore.h"
#include "Engine.h"


class DrumChannelClass
{
private:
	static uint8_t currentLine;
public:
	static void onShow();
	static void handle();
};

extern DrumChannelClass DrumChannel;

#endif
