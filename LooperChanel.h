// LooperChannel.h

#ifndef _LOOPERCHANNEL_h
#define _LOOPERCHANNEL_h


class LooperChanelClass
{
public:
	static void handle();
	static void loadWaves();
	static void onShow();
	static void backToMixer(bool pressed);
	static void startTrack();
	static void stopTrack();
	static void changeWavTrack();
};
extern LooperChanelClass LooperChanel;


#endif