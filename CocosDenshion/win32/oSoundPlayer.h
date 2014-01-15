#ifndef __OSOUND_PLAYER_H__
#define __OSOUND_PLAYER_H__
#include <Windows.h>

class oSoundPlayer
{
	typedef void oSoundDevice;
public:
	oSoundPlayer();
	~oSoundPlayer();
	bool Initialize(HWND hWindow);
	void Release();
	oSoundDevice* GetDevice();
	static oSoundPlayer& Instance();
};

#endif
