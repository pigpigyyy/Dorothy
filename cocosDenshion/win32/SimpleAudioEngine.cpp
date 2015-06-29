#include "SimpleAudioEngine.h"

#include "oMusicPlayer.h"
#include "oSound.h"
#include "oSoundPlayer.h"
#include <unordered_map>
using std::unordered_map;

using namespace std;

namespace CocosDenshion
{
static unordered_map<string, oSound*> g_sounds;
static float g_soundVolume = 1.0f;

SimpleAudioEngine::SimpleAudioEngine()
{
	HWND hWindow = FindWindow("Cocos2dx_Dorothy_Win32", NULL);
	oSoundPlayer::Instance().Initialize(hWindow);
}

SimpleAudioEngine::~SimpleAudioEngine()
{
	SimpleAudioEngine::end();
	oSoundPlayer::Instance().Release();
}

SimpleAudioEngine* SimpleAudioEngine::sharedEngine()
{
    static SimpleAudioEngine s_SharedEngine;
    return &s_SharedEngine;
}

void SimpleAudioEngine::end()
{
	if (oMusicPlayer::isAvailable())
	{
		oMusicPlayer::Instance().Stop();
	}
	for (auto it = g_sounds.begin();it != g_sounds.end();++it)
	{
		oSound* sound = it->second;
		sound->Release();
		delete sound;
	}
	g_sounds.clear();
}

//////////////////////////////////////////////////////////////////////////
// BackgroundMusic
//////////////////////////////////////////////////////////////////////////

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
	oMusicPlayer::Instance().Play(pszFilePath, bLoop);
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
	oMusicPlayer::Instance().Stop();
}

void SimpleAudioEngine::pauseBackgroundMusic(){}
void SimpleAudioEngine::resumeBackgroundMusic(){}
void SimpleAudioEngine::rewindBackgroundMusic(){}
void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath){}
bool SimpleAudioEngine::willPlayBackgroundMusic(){return false;}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    return oMusicPlayer::Instance().isPlaying();
}

// std::string SimpleAudioEngine::getStoragePath()
// {
// 	char pathBuffer[MAX_PATH];
// 	::GetTempPath(MAX_PATH, pathBuffer);
// 	return string(pathBuffer);
// }

//////////////////////////////////////////////////////////////////////////
// effect function
//////////////////////////////////////////////////////////////////////////

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop)
{
	auto it = g_sounds.find(pszFilePath);
	if (it == g_sounds.end())
	{
		oSound* sound = new oSound();
		if (sound->LoadFromFile(pszFilePath))
		{
			g_sounds[pszFilePath] = sound;
			sound->Play(bLoop);
			return (int)sound;
		}
		else
		{
			delete sound;
		}
	}
	else
	{
		it->second->Play(bLoop);
		return (int)it->second;
	}
    return 0;
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
	string name(pszFilePath);
	auto it = g_sounds.find(name);
	if (it == g_sounds.end())
	{
		oSound* sound = new oSound();
		sound->LoadFromFile(pszFilePath);
		g_sounds[name] = sound;
	}
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
	auto it = g_sounds.find(pszFilePath);
	if (it != g_sounds.end())
	{
		oSound* sound = it->second;
		sound->Release();
		delete sound;
		g_sounds.erase(it);
	}
}

void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
	oSound* sound = (oSound*)nSoundId;
	if (sound)
	{
		sound->Stop();
	}
}
void SimpleAudioEngine::pauseEffect(unsigned int nSoundId){}
void SimpleAudioEngine::pauseAllEffects(){}
void SimpleAudioEngine::resumeEffect(unsigned int nSoundId){}
void SimpleAudioEngine::resumeAllEffects(){}
void SimpleAudioEngine::stopAllEffects()
{
	for (auto it = g_sounds.begin();it != g_sounds.end();++it)
	{
		oSound* sound = it->second;
		sound->Stop();
	}
}

//////////////////////////////////////////////////////////////////////////
// volume interface
//////////////////////////////////////////////////////////////////////////

float SimpleAudioEngine::getBackgroundMusicVolume()
{
    return oMusicPlayer::Instance().GetVolume();
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
	oMusicPlayer::Instance().SetVolume(volume);
}

float SimpleAudioEngine::getEffectsVolume()
{
    return g_soundVolume;
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
	g_soundVolume = volume;
	for (auto it = g_sounds.begin();it != g_sounds.end();++it)
	{
		it->second->SetVolume(volume);
	}
}

} // end of namespace CocosDenshion
