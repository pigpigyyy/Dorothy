/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "audio/oAudio.h"
#include "misc/oContent.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

NS_DOROTHY_BEGIN

static unordered_map<string, string> g_extracted;

bool isExtractNeeded(const char* filename, string*& extractedName)
{
	auto it = g_extracted.find(filename);
	if (it == g_extracted.end())
	{
		extractedName = &(g_extracted[filename] = oSharedContent.getExtractedFullName(filename));
		return !oSharedContent.isFileExist(extractedName->c_str());
	}
	extractedName = &(it->second);
	return false;
}

static bool g_useCache = false;
void oSound::load( const char* filename )
{
	if (oSharedContent.isUsingGameFile())
	{
		string* extractedName;
		if (isExtractNeeded(filename, extractedName))
		{
			oSharedContent.extractGameFile(filename, extractedName->c_str());
			oShareAudioEngine.loadSound(extractedName->c_str());
			if (!g_useCache) oSharedContent.removeFile(extractedName->c_str());
		}
		else
		{
			oShareAudioEngine.loadSound(extractedName->c_str());
		}
	}
	else
	{
		oShareAudioEngine.loadSound(filename);
	}
}
void oSound::unload(const char* filename)
{
	if (oSharedContent.isUsingGameFile())
	{
		string* extractedName;
		if (isExtractNeeded(filename, extractedName))
		{
			oShareAudioEngine.unloadSound(extractedName->c_str());
		}
		else
		{
			oShareAudioEngine.unloadSound(extractedName->c_str());
		}
	}
	else
	{
		oShareAudioEngine.unloadSound(filename);
	}
}
int oSound::play( const char* filename, bool loop )
{
	if (oSharedContent.isUsingGameFile())
	{
		string* extractedName;
		if (isExtractNeeded(filename, extractedName))
		{
			oSharedContent.extractGameFile(filename, extractedName->c_str());
			oShareAudioEngine.loadSound(extractedName->c_str());
			if (!g_useCache) oSharedContent.removeFile(extractedName->c_str());
			return oShareAudioEngine.playSound(extractedName->c_str(), loop);
		}
		else
		{
			return oShareAudioEngine.playSound(extractedName->c_str(), loop);
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
void oSound::setUseCache(bool cache)
{
	g_useCache = cache;
}
bool oSound::isUseCache()
{
	return g_useCache;
}

void oMusic::preload( const char* filename )
{
	if (oSharedContent.isUsingGameFile())
	{
		string* extractedName;
		if (isExtractNeeded(filename, extractedName))
		{
			oSharedContent.extractGameFile(filename, extractedName->c_str());
			oShareAudioEngine.loadMusic(extractedName->c_str());
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
		string* extractedName;
		if (isExtractNeeded(filename, extractedName))
		{
			oSharedContent.extractGameFile(filename, extractedName->c_str());
			oShareAudioEngine.loadMusic(extractedName->c_str());
			oShareAudioEngine.playMusic(extractedName->c_str(), loop);
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
	virtual void unloadSound(const char* filename)
	{
		SimpleAudioEngine::sharedEngine()->unloadEffect(filename);
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
