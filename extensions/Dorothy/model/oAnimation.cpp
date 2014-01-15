#include "Dorothy/const/oDefine.h"
#include "Dorothy/model/oAnimation.h"
#include "Dorothy/const/oXml.h"
#include "Dorothy/model/oActionDuration.h"
#include "Dorothy/misc/oContent.h"
#include "Dorothy/model/oSequence.h"

NS_DOROTHY_BEGIN

#define oCase case oFrameXml

oFrameActionDef::oFrameActionDef():
duration(0.0f)
{ }

oFrameActionDef* oFrameActionDef::create()
{
	oFrameActionDef* def = new oFrameActionDef();
	def->autorelease();
	return def;
}

oFrameAction* oFrameActionDef::toAction()
{
	return oFrameAction::create(this);
}

oActionDuration* oFrameAnimationDef::toAction()
{
	return oSequence::create(
		CCDelayTime::create(begin),
		_def->toAction(),
		CCDelayTime::create(end),
		nullptr);
}

oFrameAnimationDef::oFrameAnimationDef():
begin(0.0f),
end(0.0f)
{ }

void oFrameAnimationDef::setFile( const char* filename )
{
	_file = filename;
	_def = oSharedAnimationCache.load(filename);
}

string oFrameAnimationDef::toXml()
{
	ostringstream stream;
	stream << '<' << char(oModelXml::FrameAnimation) << ' '
		<< char(oModelXml::File) << "=\"" << _file << '\"';
	if (begin != 0.0f)
	{
		stream << ' ' << char(oModelXml::Begin) << "=\"" << begin << '\"';
	}
	if (end != 0.0f)
	{
		stream << ' ' << char(oModelXml::End) << "=\"" << end << '\"';
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
	if (time == 1.0f && _loop)
	{
		oFrameAction::initWithDuration(oFrameAction::getDuration());
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
	frame->_loop = false;
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

void oFrameAction::setLoop( bool loop )
{
	_loop = loop;
}

string oFrameActionDef::toXml()
{
	ostringstream stream;
	stream << '<' << char(oFrameXml::Texture) << ' '
		<< char(oFrameXml::File) << "=\"" << textureFile << "\" "
		<< char(oFrameXml::Duration) << "=\"" << duration << "\">";
	for (CCRect* rect: rects)
	{
		stream << '<' << char(oFrameXml::Clip) << ' '
			<< char(oFrameXml::Rect) << "=\""
			<< rect->origin.x << ',' << rect->origin.y << ','
			<< rect->size.width << ',' << rect->size.height
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
