#include "Dorothy/const/oDefine.h"
#include "Dorothy/audio/oAudio.h"
#include "Dorothy/misc/oContent.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

NS_DOROTHY_BEGIN

static unordered_set<string> g_extracted;

bool isExtractNeeded(const char* filename)
{
	if (g_extracted.find(filename) == g_extracted.end())
	{
		g_extracted.insert(filename);
		return true;
	}
	return false;
}

void oSound::load( const char* filename )
{
	if (oSharedContent.isUsingGameFile())
	{
		if (isExtractNeeded(filename))
		{
			string targetFile = oSharedContent.extractGameFile(filename);
			oShareAudioEngine.loadSound(targetFile.c_str());
			oSharedContent.removeExtractedFile(targetFile.c_str());
		}
	}
	else
	{
		oShareAudioEngine.loadSound(filename);
	}
}
int oSound::play( const char* filename, bool loop )
{
	if (oSharedContent.isUsingGameFile())
	{
		if (isExtractNeeded(filename))
		{
			string targetFile = oSharedContent.extractGameFile(filename);
			oShareAudioEngine.loadSound(targetFile.c_str());
			oSharedContent.removeExtractedFile(targetFile.c_str());
			return oShareAudioEngine.playSound(targetFile.c_str(), loop);
		}
		else
		{
			return oShareAudioEngine.playSound(oSharedContent.getExtractedFullName(filename).c_str(), loop);
		}
	}
	return oShareAudioEngine.playSound(filename, loop);
}
void oSound::stop( int id )
{
	oShareAudioEngine.stopSound(id);
}
void oSound::stop()
{
	oShareAudioEngine.stopSound();
}
void oSound::setVolume( float volume )
{
	oShareAudioEngine.setSoundVolume(volume);
}
float oSound::getVolume()
{
	return oShareAudioEngine.getSoundVolume();
}

void oMusic::load( const char* filename )
{
	if (oSharedContent.isUsingGameFile())
	{
		if (isExtractNeeded(filename))
		{
			string targetFile = oSharedContent.extractGameFile(filename);
			oShareAudioEngine.loadMusic(targetFile.c_str());
		}
	}
	else
	{
		oShareAudioEngine.loadMusic(filename);
	}
}
void oMusic::play( const char* filename, bool loop )
{
	if (oSharedContent.isUsingGameFile())
	{
		if (isExtractNeeded(filename))
		{
			string targetFile = oSharedContent.extractGameFile(filename);
			oShareAudioEngine.loadMusic(targetFile.c_str());
			oShareAudioEngine.playMusic(targetFile.c_str(), loop);
		}
		else
		{
			oShareAudioEngine.playMusic(oSharedContent.getExtractedFullName(filename).c_str(), loop);
		}
	}
	else
	{
		oShareAudioEngine.playMusic(filename, loop);
	}
}
void oMusic::pause()
{
	oShareAudioEngine.pauseMusic();
}
void oMusic::resume()
{
	oShareAudioEngine.resumeMusic();
}
void oMusic::stop()
{
	oShareAudioEngine.stopMusic();
}
void oMusic::setVolume( float volume )
{
	oShareAudioEngine.setMusicVolume(volume);
}
float oMusic::getVolume()
{
	return oShareAudioEngine.getMusicVolume();
}

class oSimpleAudioEngine: public oAudioEngine
{
public:
	virtual void loadSound( const char* filename )
	{
		SimpleAudioEngine::sharedEngine()->preloadEffect(filename);
	}
	virtual int playSound( const char* filename, bool loop = false )
	{
		return SimpleAudioEngine::sharedEngine()->playEffect(filename, loop);
	}
	virtual void stopSound( int id )
	{
		SimpleAudioEngine::sharedEngine()->stopEffect(id);
	}
	virtual void stopSound()
	{
		SimpleAudioEngine::sharedEngine()->stopAllEffects();
	}
	virtual void setSoundVolume( float var )
	{
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(var);
	}
	virtual float getSoundVolume()
	{
		return SimpleAudioEngine::sharedEngine()->getEffectsVolume();
	}
	virtual void loadMusic( const char* filename )
	{
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(filename);
	}
	virtual void playMusic( const char* filename, bool loop = false )
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(filename, loop);
	}
	virtual void pauseMusic()
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	virtual void resumeMusic()
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	virtual void stopMusic()
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}
	virtual void setMusicVolume( float var )
	{
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(var);
	}
	virtual float getMusicVolume()
	{
		return SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
	}

	virtual void unload()
	{
		SimpleAudioEngine::sharedEngine()->end();
		if (oSharedContent.isUsingGameFile())
		{
			for (const string& item : g_extracted)
			{
				oSharedContent.removeExtractedFile(item.c_str());
			}
			g_extracted.clear();
		}
	}
} g_defaultAudioEngine;

void oAudioEngine::setEngine( oAudioEngine* engine )
{
	if (engine)
	{
		_engine = engine;
	}
	else
	{
		_engine = &g_defaultAudioEngine;
	}
}

oAudioEngine* oAudioEngine::shared()
{
	return _engine;
}

oAudioEngine* oAudioEngine::_engine = &g_defaultAudioEngine;

NS_DOROTHY_END
