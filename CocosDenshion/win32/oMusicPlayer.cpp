#include "oMusicPlayer.h"
#include <conio.h>
#include <DShow.h>

#define SAFE_RELEASE(p) { if (p) {(p)->Release();(p)=NULL;} }
#define V_RETURN(x) { if (FAILED(x)) {return false;} }

static REFTIME g_fDuration;
static IBasicAudio* g_pAudio;
static IGraphBuilder* g_pBuilder;
static IMediaControl* g_pControl;
static IMediaPosition* g_pPos;
static bool g_bLoop;
static bool g_bIsPlaying;
static HANDLE g_hTimer;
static oMusicPlayer* g_pInstance;

void StartTimer();
void StopTimer();
void CALLBACK MyTimerProc(PVOID lpParameter, BOOLEAN TimerOrWaitFired)
{
	if (g_bLoop)
	{
		g_pControl->Stop();
		g_pPos->put_CurrentPosition(0);
		g_pControl->Run();
		StartTimer();
	}
	else
	{
		StopTimer();
		g_bIsPlaying = false;
	}
}

void StartTimer()
{
	if (g_hTimer)
	{
		DeleteTimerQueueTimer(NULL, g_hTimer, NULL);
	}
	CreateTimerQueueTimer(&g_hTimer, NULL, MyTimerProc, NULL, (UINT)(g_fDuration*1000.0+0.5), 0, WT_EXECUTEDEFAULT);
}

void StopTimer()
{
	if (g_hTimer)
	{
		DeleteTimerQueueTimer(NULL, g_hTimer, NULL);
		g_hTimer = NULL;
	}
}

oMusicPlayer::oMusicPlayer():
_volume(1.0f)
{
	CoInitialize(NULL);
	g_pInstance = this;
}

oMusicPlayer::~oMusicPlayer()
{
	CoUninitialize();
}

bool oMusicPlayer::Play(const char* filename, bool bLoop)
{
	g_fDuration = 0.0;
	SAFE_RELEASE(g_pAudio);
	SAFE_RELEASE(g_pControl);
	SAFE_RELEASE(g_pPos);
	SAFE_RELEASE(g_pBuilder);

	CoCreateInstance(CLSID_FilterGraph, NULL,
		CLSCTX_INPROC, IID_IGraphBuilder, (void**)&g_pBuilder);
	V_RETURN(g_pBuilder->QueryInterface(IID_IMediaControl, (void**)&g_pControl));
	V_RETURN(g_pBuilder->QueryInterface(IID_IMediaPosition, (void**)&g_pPos));
	V_RETURN(g_pBuilder->QueryInterface(IID_IBasicAudio, (void**)&g_pAudio));
	WCHAR wfilename[MAX_PATH] = {0};
	MultiByteToWideChar(CP_ACP, 0, filename, -1, wfilename, MAX_PATH);
	V_RETURN(g_pBuilder->RenderFile(wfilename, NULL));
	g_pPos->put_CurrentPosition(0);
	g_pPos->get_Duration(&g_fDuration);
	g_pPos->put_CurrentPosition(0);
	g_pControl->Run();
	g_bIsPlaying = true;
	g_bLoop = bLoop;
	StartTimer();
	return true;
}

void oMusicPlayer::Stop()
{
	g_bIsPlaying = false;
	g_pControl->Stop();
	StopTimer();
}

void oMusicPlayer::SetVolume( float volume )
{
	_volume = volume;
	g_pAudio->put_Volume(volume == 0.0f ? -10000 : (long)(-30*(100*volume)));
}

oMusicPlayer& oMusicPlayer::Instance()
{
	static oMusicPlayer musicPlayer;
	return musicPlayer;
}

bool oMusicPlayer::isPlaying()
{
	return g_bIsPlaying;
}

float oMusicPlayer::GetVolume()
{
	return _volume;
}

bool oMusicPlayer::isAvailable()
{
	return g_pInstance ? true : false;
}
