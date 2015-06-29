#ifndef __OSOUND_H__
#define __OSOUND_H__

#include "oSoundPlayer.h"
class oSound
{
	typedef void oSoundBuffer;
public:
	oSound();
	~oSound();
	bool LoadFromFile(const char* filename);
	void SetVolume(float volume);
	void Play(bool bLoop);
	void Stop();
	void Release();
protected:
	oSoundBuffer* m_lpkSound;
};

#endif