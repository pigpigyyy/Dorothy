/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/model/oClip.h"
#include "Dorothy/misc/oContent.h"
#include "Dorothy/misc/oHelper.h"
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
		<< oString::getFileName(textureFile) << "\">";
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
	char* token2 = strtok(nullptr, "|");
	oClipDef* clipDef = oClipCache::load(token);
	auto it = clipDef->rects.find(token2);
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
						int x, y, w, h;
						oHelper::getRectFromStr(atts[++i], x, y, w, h);
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
