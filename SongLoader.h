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
	SONGS_PART_F = 5,
	SONGS_PART_G = 6,
	SONGS_PART_H = 7
};


class SongLoaderClass
{
public:
	static void drawTexts();
	static void drawNewSongName();
	static void drawButtons();
	static void handle();
	static void onShow();
	static void switchPart(bool pressed);
	static void saveCurrentSongToFile();
	static void loadSelectedSong(int selected_song);
	static void pressEncoder0(bool pressed);
	static void pressEncoder1(bool pressed);
	static void selectSongLength(int encoder, int value);
	static void selectSongIndex(int encoder, int value);
	static void selectSongSymbol(int encoder, int value);
	static void selectSong(int encoder, int value);	
	static void loadSongs();
	static void saveSettings();	
};
extern SongLoaderClass SongLoader;


#endif

