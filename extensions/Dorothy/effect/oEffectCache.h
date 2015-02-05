/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_OEFFECT_H__
#define __DOROTHY_OEFFECT_H__

#include "Dorothy/model/oFace.h"

NS_DOROTHY_BEGIN

class oEffect: public CCObject
{
public:
	virtual void start() = 0;
	virtual bool isPlaying() = 0;
	virtual void stop() = 0;
	virtual oEffect* setOffset(const oVec2& pos) = 0;
	virtual oEffect* attachTo(CCNode* parent, int zOrder = 0) = 0;
	virtual oEffect* autoRemove() = 0;
	static oEffect* create(const string& name);
	CC_LUA_TYPE(oEffect)
};

class oParticleEffect: public oEffect
{
public:
	virtual void start();
	virtual bool isPlaying();
	virtual void stop();
	virtual oEffect* setOffset( const oVec2& pos );
	virtual oEffect* attachTo( CCNode* parent, int zOrder = 0);
	virtual oEffect* autoRemove();
	static oParticleEffect* create(const char* filename);
	CCParticleSystemQuad* getParticle() const;
private:
	oRef<CCParticleSystemQuad> _particle;
};

class oSpriteEffect: public oEffect
{
public:
	virtual void start();
	virtual bool isPlaying();
	virtual void stop();
	virtual oEffect* setOffset( const oVec2& pos );
	virtual oEffect* attachTo( CCNode* parent, int zOrder = 0);
	virtual oEffect* autoRemove();
	void onDispose();
	static oSpriteEffect* create(const char* filename);
	oSprite* getSprite() const;
private:
	bool _isAutoRemoved;
	oRef<oSprite> _sprite;
	oRef<CCSequence> _action;
};

/** @brief Data define type for effect. */
class oEffectType
{
public:
	enum {Particle = 0, Frame = 1};
	oEffectType(const char* filename);
	/** Get a running effect instance of this effect type. */
	oEffect* toEffect();
private:
	string _file;
	uint32 _type;
};

/** @brief The effect interface class for loading and creating effect instance.
 There are two types of effects, particle and frame animation which is a sequence of image changes in a row.
 The particle file ends with ".particle" and the frame animation file ends with ".frame".
*/
class oEffectCache: public CCSAXDelegator
{
public:
	~oEffectCache();
	/** Load an effect file into memory. */
	bool load(const char* filename);
	bool update(const char* content);
	/** Clear all effect data from memory. */
	bool unload();
	/** Create a new effect instance. */
	oEffect* create(const string& name);
	/** Singleton method. */
	static oEffectCache* shared();
private:
	oEffectCache();
	virtual void textHandler( void *ctx, const char *s, int len );
	virtual void startElement( void *ctx, const char *name, const char **atts );
	virtual void endElement( void *ctx, const char *name );
	unordered_map<string, oOwn<oEffectType>> _effects;
	string _path;
	CCSAXParser _parser;
};

//** Use it for short. */
#define oSharedEffectCache (*oEffectCache::shared())

NS_DOROTHY_END

#endif // __DOROTHY_OEFFECT_H__
