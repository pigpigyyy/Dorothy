#ifndef __DOROTHY_MODEL_OANIMATION_H__
#define __DOROTHY_MODEL_OANIMATION_H__

#include "Dorothy/misc/oXmlItemCache.h"
#include "Dorothy/model/oActionDuration.h"
#include "Dorothy/model/oModelAnimationDef.h"

NS_DOROTHY_BEGIN

class oClipDef;
class oFrameAction;

/** @brief Frame action define. Frame action is a sequence of images that show in a row. */
class oFrameActionDef: public CCObject
{
public:
	string textureFile;
	float duration;
	oOwnVector<CCRect> rects;
	virtual oFrameAction* toAction();
	string toXml();
	static oFrameActionDef* create();
protected:
	oFrameActionDef();
};

/** @brief The frame animation define for model.
 It implements interface oActionDef. 
 It`s component class of oSpriteDef. Do not use it alone.
*/
class oFrameAnimationDef: public oModelAnimationDef
{
public:
	oFrameAnimationDef();
	void setFile(const char* filename);
	float begin;
	float end;
	virtual oActionDuration* toAction();
	virtual string toXml();
private:
	oRef<oFrameActionDef> _def;
	string _file;
};

class oFrameAction : public oActionDuration
{
public:
	virtual void update( float time );
	virtual void startWithTarget( CCNode* pTarget );
	virtual CCObject* copyWithZone(CCZone* pZone);
	void setLoop(bool loop);
	virtual oActionDuration* reverse();
	static oFrameAction* create(oFrameActionDef* def);
	static oFrameAction* create(const char* filename);
private:
	bool _loop;
	int _lastFrameIndex;
	float _interval;
	oRef<oFrameActionDef> _def;
};

/** @brief Load frame animations from ".frame" files and cache them. */
class oAnimationCache: public oXmlItemCache<oFrameActionDef>
{
public:
	/** Singleton method as oAnimationCache::sharedCache(). */
	SHARED_FUNC(oAnimationCache);
protected:
	oAnimationCache(){}
	virtual void beforeParse( const char* filename );
	virtual void afterParse( const char* filename );
	virtual void textHandler( void *ctx, const char *s, int len );
	virtual void startElement( void *ctx, const char *name, const char **atts );
	virtual void endElement( void *ctx, const char *name );
};

#define oSharedAnimationCache (*oAnimationCache::shared())

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OANIMATION_H__
