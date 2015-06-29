/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "model/oAnimation.h"
#include "const/oXml.h"
#include "model/oActionDuration.h"
#include "misc/oContent.h"
#include "model/oSequence.h"

NS_DOROTHY_BEGIN

#define oCase case oFrameXml

oFrameActionDef::oFrameActionDef():
duration(0.0f)
{ }

oFrameAction* oFrameActionDef::toAction()
{
	return oFrameAction::create(this);
}

oActionDuration* oFrameAnimationDef::toAction()
{
	return oSequence::create(
		CCDelayTime::create(delay),
		_def->toAction(),
		nullptr);
}

oFrameAnimationDef::oFrameAnimationDef():
delay(0.0f)
{ }

void oFrameAnimationDef::setFile( const char* filename )
{
	_file = filename;
	_def = oSharedAnimationCache.load(filename);
}

const string& oFrameAnimationDef::getFile() const
{
	return _file;
}

string oFrameAnimationDef::toXml()
{
	ostringstream stream;
	stream << '<' << char(oModelXml::FrameAnimation) << ' '
		<< char(oModelXml::File) << "=\"" << _file << '\"';
	if (delay != 0.0f)
	{
		stream << ' ' << char(oModelXml::Delay) << "=\"" << delay << '\"';
	}
	stream << "/>";
	return stream.str();
}

void oFrameAction::update( float time )
{
	int current = (int)(time/_interval);
	if (current != _lastFrameIndex && current < (int)_def->rects.size())
	{
		_lastFrameIndex = current;
		((CCSprite*)m_pTarget)->setTextureRect(*_def->rects[current]);
	}
}

void oFrameAction::startWithTarget( CCNode *pTarget )
{
	oActionDuration::startWithTarget(pTarget);
	_lastFrameIndex = 0;
	((CCSprite*)m_pTarget)->setTextureRect(*_def->rects[0]);
}

oActionDuration* oFrameAction::reverse()
{
	return nullptr;
}

CCObject* oFrameAction::copyWithZone( CCZone* pZone )
{
	CCZone* pNewZone = NULL;
	oFrameAction* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (oFrameAction*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new oFrameAction();
		pZone = pNewZone = new CCZone(pCopy);
	}
	oActionDuration::copyWithZone(pZone);
	CC_SAFE_DELETE(pNewZone);
	pCopy->initWithDuration(m_fDuration);
	return pCopy;
}

oFrameAction* oFrameAction::create( oFrameActionDef* def )
{
	oFrameAction* frame = new oFrameAction();
	frame->_def = def;
	frame->_interval = 1.0f / def->rects.size();//in update() total time is 1.0f
	frame->initWithDuration(def->duration);
	frame->autorelease();
	return frame;
}

oFrameAction* oFrameAction::create( const char* filename )
{
	oFrameActionDef* frameActionDef = oSharedAnimationCache.load(filename);
	return frameActionDef->toAction();
}

string oFrameActionDef::toXml()
{
	ostringstream stream;
	stream << '<' << char(oFrameXml::Texture) << ' '
		<< char(oFrameXml::File) << "=\"" << textureFile << "\" "
		<< char(oFrameXml::Duration) << "=\"" << (int)(duration*60.0f+0.5f) << "\">";
	for (CCRect* rect: rects)
	{
		stream << '<' << char(oFrameXml::Clip) << ' '
			<< char(oFrameXml::Rect) << "=\""
			<< (int)rect->origin.x << ',' << (int)rect->origin.y << ','
			<< (int)rect->size.width << ',' << (int)rect->size.height
			<< "\"/>";
	}
	stream << "</" << char(oFrameXml::Texture) << '>';
	return stream.str();
}

void oAnimationCache::textHandler( void *ctx, const char *s, int len )
{ }

void oAnimationCache::startElement( void *ctx, const char *name, const char **atts )
{
	switch (name[0])
	{
	oCase::Texture:
		for (int i = 0;atts[i] != nullptr;i++)
		{
			switch (atts[i][0])
			{
			oCase::File:
				_item->textureFile = atts[++i];
				break;
			oCase::Duration:
				_item->duration = (float)atof(atts[++i]);
				break;
			}
		}
		break;
	oCase::Clip:
		for (int i = 0;atts[i] != nullptr;i++)
		{
			switch (atts[i][0])
			{
			oCase::Rect:
				{
					char rectStr[4*4+3];//四位数×4 + 3个","号
					strcpy(rectStr, atts[1]);
					char* token = strtok(rectStr, ",");
					int x = atoi(token);
					token = strtok(nullptr, ",");
					int y = atoi(token);
					token = strtok(nullptr, ",");
					int w = atoi(token);
					token = strtok(nullptr, ",");
					int h = atoi(token);
					_item->rects.push_back(new CCRect((float)x, (float)y, (float)w, (float)h));
				}
				break;
			}
		}
		break;
	}
}

void oAnimationCache::endElement( void *ctx, const char *name )
{ }

void oAnimationCache::beforeParse( const char* filename )
{
	_item = oFrameActionDef::create();
}

void oAnimationCache::afterParse( const char* filename )
{ }

NS_DOROTHY_END
