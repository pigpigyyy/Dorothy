#ifndef __OMUSIC_PLAYER_H__
#define __OMUSIC_PLAYER_H__

class oMusicPlayer
{
public:
	oMusicPlayer();
	~oMusicPlayer();
	bool Play(const char* filename, bool bLoop);
	void Stop();
	void SetVolume(float volume);
	float GetVolume();
	bool isPlaying();
	static bool isAvailable();
	static oMusicPlayer& Instance();
private:
	float _volume;
};

#endif
