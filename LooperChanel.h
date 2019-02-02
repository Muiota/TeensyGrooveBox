// LooperChannel.h

#ifndef _LOOPERCHANNEL_h
#define _LOOPERCHANNEL_h


class LooperChanelClass
{
public:
	static void handle();	
	static void onShow();
	static void startTrack();
	static void stopTrack();	
protected:
	static void loadWaves();
	static void selectSong(int encoder, int value);
	static void drawTexts();
};
extern LooperChanelClass LooperChanel;


#endif