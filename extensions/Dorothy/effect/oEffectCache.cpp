#include "Dorothy/const/oDefine.h"
#include "Dorothy/effect/oEffectCache.h"
#include "Dorothy/effect/oParticleCache.h"
#include "Dorothy/model/oAnimation.h"
#include "Dorothy/misc/oContent.h"
#include "Dorothy/misc/oCallFunc.h"
#include "Dorothy/misc/oHelper.h"
#include "Dorothy/const/oXml.h"

NS_DOROTHY_BEGIN

#define oCase case oEffectXml

//oEffectType
oEffectType::oEffectType( const char* filename ):
_file(filename)
{
	if (oFileExt::check(_file, oFileExt::Frame))
	{
		_type = oEffectType::Frame;
	}
	else if (oFileExt::check(_file, oFileExt::Particle))
	{
		_type = oEffectType::Particle;
	}
}
oEffect* oEffectType::toEffect()
{
	switch (_type)
	{
	case oEffectType::Particle:
		return oParticleEffect::create(_file.c_str());
	case oEffectType::Frame:
		return oSpriteEffect::create(_file.c_str());
	}
	return nullptr;
}

//oEffectCache
oEffectCache::oEffectCache()
{
	_parser.setDelegator(this);
}
oEffectCache::~oEffectCache()
{
	oEffectCache::unload();
}
bool oEffectCache::load( const char* filename )
{
	if (!_effects.empty())
	{
		oEffectCache::unload();
	}
	unsigned long size;
	auto data = oSharedContent.loadFile(filename, size);
	if (!data)
	{
		return false;
	}
	return _parser.parse(data, size);
}
bool oEffectCache::unload()
{
	if (_effects.empty())
	{
		return false;
	}
	else
	{
		_effects.clear();
		return true;
	}
}
oEffect* oEffectCache::create( uint32 type )
{
	auto it = _effects.find(type);
	if (it != _effects.end())
	{
		return it->second->toEffect();
	}
	return nullptr;
}
oEffectCache* oEffectCache::shared()
{
	static oEffectCache effect;
	return &effect;
}
void oEffectCache::textHandler( void *ctx, const char *s, int len )
{ }
void oEffectCache::startElement( void *ctx, const char *name, const char **atts )
{
	switch (name[0])
	{
	oCase::Effect:
		{
			int index;
			const char* file;
			for (int i = 0;atts[i] != nullptr;i++)
			{
				switch (atts[i][0])
				{
				oCase::Index:
					index = atoi(atts[++i]);
					break;
				oCase::File:
					file = atts[++i];
					break;
				}
			}
			_effects[index] = oOwnMake(new oEffectType(file));
		}
		break;
	}
}
void oEffectCache::endElement( void *ctx, const char *name )
{ }

//oParticleEffect
void oParticleEffect::start()
{
	_particle->setVisible(true);
	_particle->resetSystem();
}
void oParticleEffect::stop()
{
	_particle->setVisible(false);
	_particle->stopSystem();
}
oEffect* oParticleEffect::attachTo( CCNode* parent, int zOrder )
{
	if (!parent)
	{
		return this;
	}
	CCNode* oldParent = _particle->getParent();
	if (oldParent == parent)
	{
		return this;
	}
	if (oldParent)
	{
		oldParent->removeChild(_particle, false);
	}
	parent->addChild(_particle, zOrder);
	return this;
}
oEffect* oParticleEffect::autoRemove()
{
	_particle->setAutoRemoveOnFinish(true);
	return this;
}
oParticleEffect* oParticleEffect::create( const char* filename )
{
	oParticleEffect* effect = new oParticleEffect();
	effect->_particle = (oParticleSystemQuad*)oSharedParticleCache.loadParticle(filename);
	effect->_particle->setPositionType(kCCPositionTypeFree);
	effect->_particle->setPosition(CCPointZero);
	effect->_particle->setVisible(false);
	effect->_particle->stopSystem();
	effect->autorelease();
	return effect;
}
oEffect* oParticleEffect::setOffset( const oVec2& pos )
{
	_particle->setPosition(pos);
	return this;
}
bool oParticleEffect::isPlaying()
{
	return _particle->isActive();
}

//oSpriteEffect
void oSpriteEffect::start()
{
	/* effect is retained by sprite, because sprite needs _isAutoRemoved flag */
	if (_action->isDone())
	{
		_sprite->setVisible(true);
		_sprite->stopAllActions();
		_sprite->runAction(_action);
		this->retain();
	}
}
void oSpriteEffect::stop()
{
	if (!_action->isDone())
	{	
		_sprite->setVisible(false);
		_sprite->stopAllActions();
		this->release();
	}
}
oEffect* oSpriteEffect::attachTo( CCNode* parent, int zOrder )
{
	CCNode* oldParent = _sprite->getParent();
	if (oldParent == parent)
	{
		return this;
	}
	if (oldParent)
	{
		oldParent->removeChild(_sprite, false);
	}
	parent->addChild(_sprite, zOrder);
	return this;
}
oEffect* oSpriteEffect::autoRemove()
{
	_isAutoRemoved = true;
	return this;
}
void oSpriteEffect::onDispose()
{
	_sprite->setVisible(false);
	if (_isAutoRemoved)
	{
		_sprite->stopAllActions();
		_sprite->getParent()->removeChild(_sprite, true);
		this->release();
	}
}
oSpriteEffect* oSpriteEffect::create( const char* filename )
{
	oSpriteEffect* effect = new oSpriteEffect();
	effect->_isAutoRemoved = false;

	oFrameActionDef* frameActionDef = oSharedAnimationCache.load(filename);

	effect->_sprite = oSprite::createWithTexture(
		oSharedContent.loadTexture(frameActionDef->textureFile.c_str()),
		*frameActionDef->rects[0]);

	effect->_action = CCSequence::createWithTwoActions(
		frameActionDef->toAction(),
	oCallFunc::create(effect, callfunc_selector(oSpriteEffect::onDispose)));

	effect->autorelease();
	return effect;
}
oEffect* oSpriteEffect::setOffset( const oVec2& pos )
{
	_sprite->setPosition(pos);
	return this;
}
bool oSpriteEffect::isPlaying()
{
	return !_action->isDone();
}

oEffect* oEffect::create( uint32 index )
{
	return oSharedEffectCache.create(index);
}

NS_DOROTHY_END
