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
	oOwnVector<CCRect> rects;
	/** Get a sprite instance with an area index. */
	CCSprite* toSprite(uint32 index);
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