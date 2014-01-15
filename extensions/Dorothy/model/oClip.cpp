#include "Dorothy/const/oDefine.h"
#include "Dorothy/model/oClip.h"
#include "Dorothy/misc/oContent.h"
#include "Dorothy/const/oXml.h"

NS_DOROTHY_BEGIN

oClipDef::oClipDef()
{ }

oClipDef* oClipDef::create()
{
	oClipDef* clipDef = new oClipDef();
	clipDef->autorelease();
	return clipDef;
}

CCSprite* oClipDef::toSprite( uint32 index )
{
	if (index < rects.size())
	{
		CCTexture2D* texture = oSharedContent.loadTexture(textureFile.c_str());
		CCSprite* sprite = CCSprite::createWithTexture(texture, *rects[index]);
		return sprite;
	}
	return nullptr;
}

string oClipDef::toXml()
{
	ostringstream stream;
	stream << '<' << char(oClipXml::Texture) << ' ' << char(oClipXml::File) << "=\""
		<< textureFile << "\">";
	for (const CCRect* rect : rects)
	{
		stream << '<' << char(oClipXml::Clip) << ' '
			<< char(oClipXml::Rect) << "=\""
			<< rect->origin.x << ',' << rect->origin.y << ','
			<< rect->size.width << ',' << rect->size.height
			<< "\"/>";
	}
	stream << "</" << char(oClipXml::Texture) << '>';
	return stream.str();
}

CCSprite* oClipCache::loadSprite( const char* clipStr )
{
	char name[256];
	strcpy(name, clipStr);
	char* token = strtok(name, "|");
	oClipDef* clipDef = oClipCache::load(token);
	token = strtok(nullptr, "|");
	int index = atoi(token);
	if (0 <= index && index < (int)clipDef->rects.size())
	{
		CCTexture2D* texture = oSharedContent.loadTexture(clipDef->textureFile.c_str());
		CCSprite* sprite = CCSprite::createWithTexture(texture, *clipDef->rects[index]);
		return sprite;
	}
	return nullptr;
}

#define oCase case oClipXml

void oClipCache::textHandler( void *ctx, const char *s, int len )
{ }

void oClipCache::startElement( void *ctx, const char *name, const char **atts )
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

void oClipCache::endElement( void *ctx, const char *name )
{ }

void oClipCache::beforeParse( const char* filename )
{
	_item = oClipDef::create();
}

void oClipCache::afterParse( const char* filename )
{ }

NS_DOROTHY_END
