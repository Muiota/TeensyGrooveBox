// SongLoader.h

#ifndef _SONGLOADER_h
#define _SONGLOADER_h


enum song_load_part
{
	SONGS_PART_A = 0, 
	SONGS_PART_B = 1, 
	SONGS_PART_C = 2, 
	SONGS_PART_D = 3, 
	SONGS_PART_E = 4, 
	SONGS_PART_F = 5
};


class SongLoaderClass
{
public:
	static void drawTexts();
	static void handle();
	static void onShow();
	static void backToMixer(bool pressed);
	static void loadSelectedSong(bool pressed);
	static void selectSong(int encoder, int value);
	static void loadSongs();
	static void saveSettings();
};
extern SongLoaderClass SongLoader;


#endif

