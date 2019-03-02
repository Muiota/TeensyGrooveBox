// LooperChannel.h

#ifndef _LOOPERCHANNEL_h
#define _LOOPERCHANNEL_h


class LooperChannelClass
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
extern LooperChannelClass LooperChannel;


#endif