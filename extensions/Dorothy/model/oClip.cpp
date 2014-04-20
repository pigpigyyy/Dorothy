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

CCSprite* oClipDef::toSprite( const string& name )
{
	auto it = rects.find(name);
	if (it != rects.end())
	{
		CCTexture2D* texture = oSharedContent.loadTexture(textureFile.c_str());
		CCSprite* sprite = CCSprite::createWithTexture(texture, *it->second);
		return sprite;
	}
	return nullptr;
}

string oClipDef::toXml()
{
	ostringstream stream;
	stream << '<' << char(oClipXml::Texture) << ' ' << char(oClipXml::File) << "=\""
		<< textureFile << "\">";
	for (const auto& rect : rects)
	{
		stream << '<' << char(oClipXml::Clip) << ' '
			<< char(oClipXml::Name) << "=\"" << rect.first.c_str() << "\" "
			<< char(oClipXml::Rect) << "=\""
			<< rect.second->origin.x << ',' << rect.second->origin.y << ','
			<< rect.second->size.width << ',' << rect.second->size.height
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
	auto it = clipDef->rects.find(token);
	if (it != clipDef->rects.end())
	{
		CCTexture2D* texture = oSharedContent.loadTexture(clipDef->textureFile.c_str());
		CCSprite* sprite = CCSprite::createWithTexture(texture, *it->second);
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
		{
			for (int i = 0; atts[i] != nullptr; i++)
			{
				switch (atts[i][0])
				{
					oCase::File:
					_item->textureFile = _path + atts[++i];
					break;
				}
			}
		}
		break;
		oCase::Clip:
		{
			const char* name = nullptr;
			for (int i = 0; atts[i] != nullptr; i++)
			{
				switch (atts[i][0])
				{
					oCase::Name:
					{
						name = atts[++i];
					}
					break;
					oCase::Rect:
					{
						char rectStr[4 * 4 + 3];//四位数×4 + 3个","号
						strcpy(rectStr, atts[++i]);
						char* token = strtok(rectStr, ",");
						int x = atoi(token);
						token = strtok(nullptr, ",");
						int y = atoi(token);
						token = strtok(nullptr, ",");
						int w = atoi(token);
						token = strtok(nullptr, ",");
						int h = atoi(token);
						_item->rects[name] = oOwnMake(new CCRect((float)x, (float)y, (float)w, (float)h));
					}
					break;
				}
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
