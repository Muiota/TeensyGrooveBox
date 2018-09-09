// SongLoader.h

#ifndef _SONGLOADER_h
#define _SONGLOADER_h


class SongLoaderClass
{
public:
	static void handle();
	static void onShow();
	static void backToMixer(bool pressed);
	static void loadSongs();
};
extern SongLoaderClass SongLoader;


#endif

