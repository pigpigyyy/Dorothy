/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_AUDIO_OAUDIO_H__
#define __DOROTHY_AUDIO_OAUDIO_H__

NS_DOROTHY_BEGIN

class oSound
{
public:
	static void load(const char* filename);
	static void unload(const char* filename);
	static int play(const char* filename, bool loop = false);
	static void stop(int id);
	static void stop();
	static void setVolume(float volume);
	static float getVolume();
	static void setUseCache(bool cache);
	static bool isUseCache();
};

class oMusic
{
public:
	static void preload(const char* filename);
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
	virtual void unloadSound(const char* filename) = 0;
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