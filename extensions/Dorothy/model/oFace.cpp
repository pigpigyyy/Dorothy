/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/model/oFace.h"
#include "Dorothy/model/oClip.h"
#include "Dorothy/effect/oParticleCache.h"
#include "Dorothy/model/oAnimation.h"
#include "Dorothy/misc/oContent.h"
#include "Dorothy/misc/oHelper.h"

NS_DOROTHY_BEGIN

bool disposeChildren( CCNode* parent )
{
	bool result = true;
	CCArray* children = parent->getChildren();
	CCObject* child;
	CCARRAY_FOREACH(children, child)
	{
		bool resultA = dynamic_cast<oIDisposable*>(child)->dispose();
		bool resultB = !disposeChildren((CCNode*)child);
		result = resultA && resultB && result;
	}
	return result;
}

bool initParticleWithDef( CCParticleSystemQuad* par, oParticleDef* type )
{
	bool bRet = false;
	BLOCK_START
	{
		if (par->initWithTotalParticles(type->maxParticles))
		{
			// angle
			par->setAngle(type->angle);
			par->setAngleVar(type->angleVariance);
			// duration
			par->setDuration(type->duration);
			// blend function 
			ccBlendFunc blendFunc;
			blendFunc.src = type->blendFuncSource;
			blendFunc.dst = type->blendFuncDestination;
			par->setBlendFunc(blendFunc);
			// color
			ccColor4F color;
			color.r = type->startColorRed;
			color.g = type->startColorGreen;
			color.b = type->startColorBlue;
			color.a = type->startColorAlpha;
			par->setStartColor(color);
			color.r = type->startColorVarianceRed;
			color.g = type->startColorVarianceGreen;
			color.b = type->startColorVarianceBlue;
			color.a = type->startColorVarianceAlpha;
			par->setStartColorVar(color);
			color.r = type->finishColorRed;
			color.g = type->finishColorGreen;
			color.b = type->finishColorBlue;
			color.a = type->finishColorAlpha;
			par->setEndColor(color);
			color.r = type->finishColorVarianceRed;
			color.g = type->finishColorVarianceGreen;
			color.b = type->finishColorVarianceBlue;
			color.a = type->finishColorVarianceAlpha;
			par->setEndColorVar(color);
			// particle size
			par->setStartSize(type->startParticleSize);
			par->setStartSizeVar(type->startParticleSizeVariance);
			par->setEndSize(type->finishParticleSize);
			par->setEndSizeVar(type->finishParticleSizeVariance);
			// position
			par->setPosition(type->sourcePositionx, type->sourcePositiony);
			par->setPosVar(ccp(type->sourcePositionVariancex, type->sourcePositionVariancey));
			// Spinning
			par->setStartSpin(type->rotationStart);
			par->setStartSpinVar(type->rotationStartVariance);
			par->setEndSpin(type->rotationEnd);
			par->setEndSpinVar(type->rotationEndVariance);
			par->setEmitterMode(type->emitterType);
			// Mode A: Gravity + tangential accel + radial accel
			if( par->getEmitterMode() == kCCParticleModeGravity ) 
			{
				// gravity
				par->setGravity(ccp(type->gravityx, type->gravityy));
				// speed
				par->setSpeed(type->speed);
				par->setSpeedVar(type->speedVariance);
				par->setRadialAccel(type->radialAcceleration);
				par->setRadialAccelVar(type->radialAccelVariance);
				// tangential acceleration
				par->setTangentialAccel(type->tangentialAcceleration);
				par->setTangentialAccelVar(type->tangentialAccelVariance);
			}
			// or Mode B: radius movement
			else if( par->getEmitterMode() == kCCParticleModeRadius ) 
			{
				par->setStartRadius(type->maxRadius);
				par->setStartRadiusVar(type->maxRadiusVariance);
				par->setEndRadius(type->minRadius);
				par->setEndRadiusVar(type->minRadiusVariance);
				par->setRotatePerSecond(type->rotatePerSecond);
				par->setRotatePerSecondVar(type->rotatePerSecondVariance);
			}
			else
			{
				CCAssert( false, "Invalid emitterType in config file");
				CC_BREAK_IF(true);
			}
			// life span
			par->setLife(type->particleLifespan);
			par->setLifeVar(type->particleLifespanVariance);
			// emission Rate
			par->setEmissionRate(type->emissionRate);
			// texture
			// Try to get the texture from the cache
			const char* textureName = type->textureFileName.c_str();
			CCTexture2D* tex = nullptr;
			if (type->textureFileName == "__firePngData")
			{
				tex = CCParticleSystem::getDefaultTexture();
			}
			else
			{
				tex = oSharedContent.loadTexture(textureName);
			}
			CCAssert(tex != NULL, "CCParticleSystem: error loading the texture");
			if (type->textureRect != CCRect::zero)
			{
				par->setTextureWithRect(tex, type->textureRect);
			}
			else par->setTexture(tex);
			bRet = true;
		}
	}
	BLOCK_END
	return bRet;
}

void oParticleSystemQuad::draw()
{
	kmGLPushMatrix();
	float rotation = CCNode::getRotation();
	float scaleX = CCNode::getScaleX();
	float scaleY = CCNode::getScaleY();
	for (CCNode* parent = CCNode::getParent();parent;parent = parent->getParent())
	{
		rotation += parent->getRotation();
		scaleX *= parent->getScaleX();
		scaleY *= parent->getScaleY();
	}
	kmGLRotatef(rotation, 0.0f, 0.0f, 1.0f);
	scaleX = scaleX > 0.0f ? 1.0f : -1.0f;
	scaleY = scaleY > 0.0f ? 1.0f : -1.0f;
	if (scaleX == -1.0f || scaleY == -1.0f)
	{
		kmGLScalef(scaleX, scaleY, 1.0f);
	}
	CCParticleSystemQuad::draw();
	kmGLPopMatrix();
}

bool oParticleSystemQuad::dispose()
{
	CCParticleSystemQuad::setAutoRemoveOnFinish(true);
	CCParticleSystemQuad::stopSystem();
	if (_isFaceRoot)
	{
		disposeChildren(this);
		return false;
	}
	else
	{
		return true;
	}
}

void oParticleSystemQuad::childrenDisposed( oIDisposable* item )
{
	item->disposing.Clear();
	CCNode::getParent()->removeChild(this, true);
}

oParticleSystemQuad::oParticleSystemQuad()
{ }

oParticleSystemQuad::~oParticleSystemQuad()
{
	if (disposing)
	{
		disposing(this);
	}
}

oParticleSystemQuad* oParticleSystemQuad::createWithDef( oParticleDef* type )
{
	oParticleSystemQuad* pRet = new oParticleSystemQuad();
	if (pRet && initParticleWithDef(pRet, type))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return pRet;
}

bool oSprite::dispose()
{
	oSprite::setSelfVisible(false);
	if (_isFaceRoot)
	{
		if (disposeChildren(this))
		{
			CCSprite::getParent()->removeChild(this, true);
			return true;
		}
		return false;
	}
	else
	{
		return true;
	}
}

void oSprite::draw()
{
	if (_isSelfVisible)
	{
		CCSprite::draw();
	}
}

void oSprite::childrenDisposed( oIDisposable* item )
{
	item->disposing.Clear();
	CCNode::getParent()->removeChild(this, true);
}

void oSprite::setSelfVisible(bool var)
{
	_isSelfVisible = var;
}

bool oSprite::getSelfVisible() const
{
	return _isSelfVisible;
}

oSprite::oSprite():
_isSelfVisible(true),
_isFaceRoot(false)
{ }

oSprite::~oSprite()
{
	if (disposing)
	{
		disposing(this);
	}
}

oSprite* oSprite::create()
{
	oSprite* pobSprite = new oSprite();
	if (pobSprite && pobSprite->init())
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return nullptr;
}

oSprite* oSprite::createWithTexture( CCTexture2D *pTexture )
{
	oSprite* pobSprite = new oSprite();
	if (pobSprite && pobSprite->initWithTexture(pTexture))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return nullptr;
}

oSprite* oSprite::createWithTexture( CCTexture2D *pTexture, const CCRect& rect )
{
	oSprite *pobSprite = new oSprite();
	if (pobSprite && pobSprite->initWithTexture(pTexture, rect))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return nullptr;
}

oFace::oFace( const string& file, const oVec2& point ):
_file(file),
_pos(point)
{
	if (_file.find('|') != string::npos)
	{
		_type = oFace::Clip;
	}
	else if (oFileExt::check(_file, oFileExt::Texture))
	{
		_type = oFace::Image;
	}
	else if (oFileExt::check(_file, oFileExt::Frame))
	{
		_type = oFace::Frame;
	}
	else if (oFileExt::check(_file, oFileExt::Particle))
	{
		_type = oFace::Particle;
	}
}

void oFace::addChild( oFace* face )
{
	_children.push_back(face);
}

bool oFace::removeChild( oFace* face )
{
	auto it = _children.begin();
	for (;it != _children.end();it++)
	{
		if (*it == face)
		{
			_children.erase(it);
			return true;
		}
	}
	return false;
}

oFace* oFace::create( const string& file, const oVec2& point )
{
	oFace* face = new oFace(file, point);
	face->autorelease();
	return face;
}

CCNode* oFace::load(bool isRoot)
{
	CCNode* node = nullptr;
	switch (_type)
	{
	case oFace::Clip:
		{
			char name[256];
			strcpy(name, _file.c_str());
			char* filename = strtok(name, "|");
			char* nameStr = strtok(nullptr, "|");
			oClipDef* clipDef = oSharedClipCache.load(filename);
			CCTexture2D* texture = oSharedContent.loadTexture(clipDef->textureFile.c_str());
			oSprite* sprite = oSprite::createWithTexture(texture, *clipDef->rects[nameStr]);
			sprite->_isFaceRoot = isRoot;
			node = sprite;
		}
		break;
	case oFace::Image:
		{
			CCTexture2D* texture = oSharedContent.loadTexture(_file.c_str());
			oSprite* sprite = oSprite::createWithTexture(texture);
			sprite->_isFaceRoot = isRoot;
			node = sprite;
		}
		break;
	case oFace::Frame:
		{
			oFrameActionDef* frameActionDef = oSharedAnimationCache.load(_file.c_str());
			oSprite* sprite = oSprite::createWithTexture(
				oSharedContent.loadTexture(frameActionDef->textureFile.c_str()),
				*frameActionDef->rects[0]);
			sprite->runAction(frameActionDef->toAction());
			node = sprite;
		}
		break;
	case oFace::Particle:
		{
			oParticleSystemQuad* particle = (oParticleSystemQuad*)oSharedParticleCache.loadParticle(_file.c_str());
			particle->setPositionType(kCCPositionTypeFree);
			particle->_isFaceRoot = isRoot;
			node = particle;
		}
		break;
	}
	if (node)
	{
		node->setPosition(_pos);
	}
	return node;
}

CCNode* oFace::toNode()
{
	CCNode* node = oFace::load(true);
	oParticleSystemQuad* badChild = nullptr;
	if (_type == oFace::Particle)
	{
		badChild = (oParticleSystemQuad*)node;
	}
	visit(node, this, badChild);
	if (badChild != nullptr)
	{
		switch (_type)
		{
		case oFace::Image:
		case oFace::Clip:
		case oFace::Frame:
			((oIDisposable*)badChild)->disposing = std::make_pair((oSprite*)node, &oSprite::childrenDisposed);
			break;
		case oFace::Particle:
			((oIDisposable*)badChild)->disposing = std::make_pair((oParticleSystemQuad*)node, &oParticleSystemQuad::childrenDisposed);
			break;
		}
	}
	return node;
}

void oFace::visit( CCNode* parent, oFace* current, oParticleSystemQuad*& badChild )
{
	for (oFace* face : current->_children)
	{
		CCNode* node = face->load();
		if (face->getType() == oFace::Particle)
		{
			oParticleSystemQuad* newChild = (oParticleSystemQuad*)node;
			if (badChild)
			{
				float life = badChild->getLife() + badChild->getLifeVar();
				float newLife = newChild->getLife() + newChild->getLifeVar();
				if (newLife > life)
				{
					badChild = newChild;
				}
			}
			else
			{
				badChild = newChild;
			}
		}
		visit(node, face, badChild);
		parent->addChild(node);
	}
}

uint32 oFace::getType() const
{
	return _type;
}

NS_DOROTHY_END
