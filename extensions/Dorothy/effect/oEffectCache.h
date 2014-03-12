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
	static oEffect* create(uint32 index);
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
private:
	oRef<oParticleSystemQuad> _particle;
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
private:
	bool _isAutoRemoved;
	oRef<oSprite> _sprite;
	oRef<CCSequence> _action;
};

/** @brief Data define type for effect. */
class oEffectType
{
public:
	enum {None = -1, Particle = 0, Frame = 1};
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
	oEffect* create(uint32 type);
	/** Singleton method. */
	static oEffectCache* shared();
private:
	oEffectCache();
	virtual void textHandler( void *ctx, const char *s, int len );
	virtual void startElement( void *ctx, const char *name, const char **atts );
	virtual void endElement( void *ctx, const char *name );
	unordered_map<int, oOwn<oEffectType>> _effects;
	CCSAXParser _parser;
};

//** Use it for short. */
#define oSharedEffectCache (*oEffectCache::shared())

NS_DOROTHY_END

#endif // __DOROTHY_OEFFECT_H__
