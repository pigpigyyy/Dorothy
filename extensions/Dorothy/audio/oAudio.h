#ifndef __DOROTHY_AUDIO_OAUDIO_H__
#define __DOROTHY_AUDIO_OAUDIO_H__

NS_DOROTHY_BEGIN

class oSound
{
public:
	static void load(const char* filename);
	static int play(const char* filename, bool loop = false);
	static void stop(int id);
	static void stop();
	static void setVolume(float volume);
	static float getVolume();
};

class oMusic
{
public:
	static void load(const char* filename);
	static void play(const char* filename, bool loop = false);
	static void pause();
	static void resume();
	static void stop();
	static void setVolume(float volume);
	static float getVolume();
};

class oAudioEngine
{
public:
	virtual void loadSound(const char* filename) = 0;
	virtual int playSound(const char* filename, bool loop = false) = 0;
	virtual void stopSound(int id) = 0;
	virtual void stopSound() = 0;
	virtual void setSoundVolume(float var) = 0;
	virtual float getSoundVolume() = 0;

	virtual void loadMusic(const char* filename) = 0;
	virtual void playMusic(const char* filename, bool loop = false) = 0;
	virtual void pauseMusic() = 0;
	virtual void resumeMusic() = 0;
	virtual void stopMusic() = 0;
	virtual void setMusicVolume(float var) = 0;
	virtual float getMusicVolume() = 0;

	virtual void unload() = 0;
	static void setEngine(oAudioEngine* engine);
	static oAudioEngine* shared();
private:
	static oAudioEngine* _engine;
};

#define oShareAudioEngine (*oAudioEngine::shared())

NS_DOROTHY_END

#endif // __DOROTHY_AUDIO_OAUDIO_H__