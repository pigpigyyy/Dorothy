/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

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
	const string& getFile() const;
	float delay;
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
	virtual oActionDuration* reverse();
	static oFrameAction* create(oFrameActionDef* def);
	static oFrameAction* create(const char* filename);
private:
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
