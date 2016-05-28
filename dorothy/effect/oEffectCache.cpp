/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "effect/oEffectCache.h"
#include "effect/oParticleCache.h"
#include "model/oAnimation.h"
#include "misc/oContent.h"
#include "misc/oHelper.h"
#include "const/oXml.h"

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

const string& oEffectType::getFilename() const
{
	return _file;
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
	string fullPath = oSharedContent.getFullPath(filename);
	_path = oString::getFilePath(fullPath);
	return _parser.parse(data, (unsigned int)size);
}
bool oEffectCache::update(const char* content)
{
	if (!_effects.empty())
	{
		oEffectCache::unload();
	}
	unsigned long size = ::strlen(content);
	return _parser.parse(content, (unsigned int)size);
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
oEffect* oEffectCache::create( const string& name )
{
	auto it = _effects.find(name);
	if (it != _effects.end())
	{
		return it->second->toEffect();
	}
	return nullptr;
}
const string& oEffectCache::getFileByName(const string & name)
{
	auto it = _effects.find(name);
	if (it != _effects.end())
	{
		return it->second->getFilename();
	}
	return oString::Empty;
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
			const char* name = nullptr;
			string file;
			for (int i = 0; atts[i] != nullptr; i++)
			{
				switch (atts[i][0])
				{
				oCase::Name:
					name = atts[++i];
					break;
				oCase::File:
					file = _path + atts[++i];
					break;
				}
			}
			_effects[name] = oOwnMake(new oEffectType(file.c_str()));
		}
		break;
	}
}
void oEffectCache::endElement( void *ctx, const char *name )
{ }

//oParticleEffect
void oParticleEffect::start()
{
	if (_particle) _particle->resetSystem();
}
void oParticleEffect::stop()
{
	if (_particle) _particle->stopSystem();
}
void oParticleEffect::autoRemove()
{
	if (_particle) _particle->setAutoRemoveOnFinish(true);
}
oParticleEffect* oParticleEffect::create( const char* filename )
{
	auto effect = oWRefMake(new oParticleEffect());
	CC_INIT(effect);
	oParticleDef* particleDef = oSharedParticleCache.load(filename);
	oParticleSystemQuad* particle = oParticleSystemQuad::createWithDef(particleDef);
	particle->setPositionType(kCCPositionTypeFree);
	particle->setPosition(oVec2::zero);
	particle->stopSystem();
	particle->disposing += [effect](oIDisposable*)
	{
		if (effect && effect->getParent())
		{
			effect->getParent()->removeChild(effect);
		}
	};
	effect->addChild(particle);
	effect->_particle = particle;
	effect->autorelease();
	return effect;
}
bool oParticleEffect::isPlaying()
{
	if (_particle) return _particle->isActive();
	return false;
}
oParticleSystemQuad* oParticleEffect::getParticle() const
{
	return _particle;
}

//oSpriteEffect
void oSpriteEffect::start()
{
	if (_action->isDone())
	{
		_sprite->setVisible(true);
		_sprite->stopAllActions();
		_sprite->runAction(_action);
	}
}
void oSpriteEffect::stop()
{
	if (!_action->isDone())
	{	
		_sprite->setVisible(false);
		_sprite->stopAllActions();
	}
	if (_isAutoRemoved)
	{
		_sprite->stopAllActions();
		CCNode* parent = CCNode::getParent();
		if (parent) parent->removeChild(this, true);
	}
}
void oSpriteEffect::autoRemove()
{
	_isAutoRemoved = true;
}
void oSpriteEffect::onActionEnd()
{
	_sprite->setVisible(false);
	if (_isAutoRemoved)
	{
		CCNode* parent = CCNode::getParent();
		if (parent) parent->removeChild(this, true);
	}
}
oSpriteEffect* oSpriteEffect::create( const char* filename )
{
	oSpriteEffect* effect = new oSpriteEffect();
	CC_INIT(effect);
	effect->_isAutoRemoved = false;

	oFrameActionDef* frameActionDef = oSharedAnimationCache.load(filename);

	if (frameActionDef->textureFile.empty() || frameActionDef->rects.size() == 0)
	{
		effect->_sprite = oSprite::create();
		effect->_action = CCSequence::create(CCCallFunc::create(effect, callfunc_selector(oSpriteEffect::onActionEnd)),nullptr);
	}
	else
	{
		effect->_sprite = oSprite::createWithTexture(
			oSharedContent.loadTexture(frameActionDef->textureFile.c_str()),
			*frameActionDef->rects[0]);
		effect->_action = CCSequence::createWithTwoActions(
			frameActionDef->toAction(),
			CCCallFunc::create(effect, callfunc_selector(oSpriteEffect::onActionEnd)));
	}
	
	effect->addChild(effect->_sprite);
	effect->autorelease();
	return effect;
}
bool oSpriteEffect::isPlaying()
{
	return !_action->isDone();
}
oSprite* oSpriteEffect::getSprite() const
{
	return _sprite;
}

class oDummyEffect: public oEffect
{
public:
	oDummyEffect()
	: _node(CCNode::create())
	, _isAutoRemoved(false)
	{ }
	virtual void start() { stop(); }
	virtual bool isPlaying() { return false; }
	virtual void stop()
	{
		if (_isAutoRemoved)
		{
			CCNode* parent = CCNode::getParent();
			if (parent) parent->removeChild(this, true);
		}
	}
	virtual void autoRemove()
	{
		_isAutoRemoved = true;
	}
	static oDummyEffect* create()
	{
		oDummyEffect* effect = new oDummyEffect();
		effect->autorelease();
		return effect;
	}
private:
	bool _isAutoRemoved;
	oRef<CCNode> _node;
};

oEffect* oEffect::create( const string& name )
{
	oEffect* effect = oSharedEffectCache.create(name);
	if (!effect) effect = oDummyEffect::create();
	return effect;
}

NS_DOROTHY_END
