/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_MODEL_OCLIP__
#define __DOROTHY_MODEL_OCLIP__

#include "Dorothy/misc/oXmlItemCache.h"

NS_DOROTHY_BEGIN

/** @brief Clips are different rectangle areas on textures.
 This is the data for clips from a single texture.
*/
class oClipDef: public CCObject
{
public:
	/** The only method to create a clip define. */
	static oClipDef* create();
	/** Name of the texture file. Name only, not file path. */
	string textureFile;
	/** Different areas on this texture. */
	hash_strmap<oOwn<CCRect>> rects;
	/** Get a sprite instance with an name. */
	CCSprite* toSprite(const string& name);
	string toXml();
protected:
	oClipDef();
};

/** @brief Load frame animations from ".frame" files and cache them. */
class oClipCache: public oXmlItemCache<oClipDef>
{
public:
	/** A clip str is like "loli.clip|0", file name + "|" + clip index.
	 Load a new clip file or get it from cache,
	 then create a new CCsprite instance with certain clip.
	*/
	CCSprite* loadSprite(const char* clipStr);
	/** Singleton method as oClipCache::sharedCache(). */
	SHARED_FUNC(oClipCache);
protected:
	oClipCache(){}
	virtual void beforeParse( const char* filename );
	virtual void afterParse( const char* filename );
	virtual void textHandler( void *ctx, const char *s, int len );
	virtual void startElement( void *ctx, const char *name, const char **atts );
	virtual void endElement( void *ctx, const char *name );
};

#define oSharedClipCache (*oClipCache::shared())

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OCLIP__