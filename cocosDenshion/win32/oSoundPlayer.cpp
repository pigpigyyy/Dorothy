#include "oSoundPlayer.h"
#include <dsound.h>

static LPDIRECTSOUND8 g_lpkDSound;

oSoundPlayer& oSoundPlayer::Instance()
{
	static oSoundPlayer soundPlayer;
	return soundPlayer;
}

oSoundPlayer::oSoundPlayer()
{
	g_lpkDSound = NULL;
}

oSoundPlayer::~oSoundPlayer()
{
	oSoundPlayer::Release();
}

bool oSoundPlayer::Initialize( HWND hWindow )
{
	/*创建DirectSound对象*/
	DirectSoundCreate8(NULL, &g_lpkDSound, NULL);
	if (NULL == g_lpkDSound)
	{
		return false;
	}
	/*设置协作级别*/
	if (FAILED(g_lpkDSound->SetCooperativeLevel(hWindow, DSSCL_NORMAL)))
	{
		return false;
	}
	return true;
}

void oSoundPlayer::Release()
{
	if (NULL != g_lpkDSound)
	{
		g_lpkDSound->Release();
		g_lpkDSound = NULL;
	}
}

void* oSoundPlayer::GetDevice()
{
	return (void*)g_lpkDSound;
}
