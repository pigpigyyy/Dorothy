/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "effect/oParticleCache.h"
#include "model/oFace.h"
#include "misc/oContent.h"
#include "misc/oHelper.h"
#include "support/zip_support/ZipUtils.h"
#include "support/base64.h"

NS_DOROTHY_BEGIN

oParticleDef* oParticleCache::load( const char* filename )
{
	auto it = _parDict.find(filename);
	if (it != _parDict.end())
	{
		return it->second;
	}
	else
	{
		unsigned long size;
		auto data = oSharedContent.loadFile(filename, size);
		auto dict = CCDictionary::createWithContents(data, (unsigned int)size);

		oParticleDef* type = new oParticleDef();
		type->autorelease();

		type->maxParticles = (int)dict->numberForKey("maxParticles");
		type->angle = (float)dict->numberForKey("angle");
		type->angleVariance = (float)dict->numberForKey("angleVariance");
		type->duration = (float)dict->numberForKey("duration");
		type->blendFuncSource = (float)dict->numberForKey("blendFuncSource");
		type->blendFuncDestination = (float)dict->numberForKey("blendFuncDestination");
		type->startColorRed = (float)dict->numberForKey("startColorRed");
		type->startColorGreen = (float)dict->numberForKey("startColorGreen");
		type->startColorBlue = (float)dict->numberForKey("startColorBlue");
		type->startColorAlpha = (float)dict->numberForKey("startColorAlpha");
		type->startColorVarianceRed = (float)dict->numberForKey("startColorVarianceRed");
		type->startColorVarianceGreen = (float)dict->numberForKey("startColorVarianceGreen");
		type->startColorVarianceBlue = (float)dict->numberForKey("startColorVarianceBlue");
		type->startColorVarianceAlpha = (float)dict->numberForKey("startColorVarianceAlpha");
		type->finishColorRed = (float)dict->numberForKey("finishColorRed");
		type->finishColorGreen = (float)dict->numberForKey("finishColorGreen");
		type->finishColorBlue = (float)dict->numberForKey("finishColorBlue");
		type->finishColorAlpha = (float)dict->numberForKey("finishColorAlpha");
		type->finishColorVarianceRed = (float)dict->numberForKey("finishColorVarianceRed");
		type->finishColorVarianceGreen = (float)dict->numberForKey("finishColorVarianceGreen");
		type->finishColorVarianceBlue = (float)dict->numberForKey("finishColorVarianceBlue");
		type->finishColorVarianceAlpha = (float)dict->numberForKey("finishColorVarianceAlpha");
		type->startParticleSize = (float)dict->numberForKey("startParticleSize");
		type->startParticleSizeVariance = (float)dict->numberForKey("startParticleSizeVariance");
		type->finishParticleSize = (float)dict->numberForKey("finishParticleSize");
		type->finishParticleSizeVariance = (float)dict->numberForKey("finishParticleSizeVariance");
		type->sourcePositionx = (float)dict->numberForKey("sourcePositionx");
		type->sourcePositiony = (float)dict->numberForKey("sourcePositiony");
		type->sourcePositionVariancex = (float)dict->numberForKey("sourcePositionVariancex");
		type->sourcePositionVariancey = (float)dict->numberForKey("sourcePositionVariancey");
		type->rotationStart = (float)dict->numberForKey("rotationStart");
		type->rotationStartVariance = (float)dict->numberForKey("rotationStartVariance");
		type->rotationEnd = (float)dict->numberForKey("rotationEnd");
		type->rotationEndVariance = (float)dict->numberForKey("rotationEndVariance");
		type->emissionRate = (float)dict->numberForKey("emissionRate");
		type->emitterType = (int)dict->numberForKey("emitterType");
		type->gravityx = (float)dict->numberForKey("gravityx");
		type->gravityy = (float)dict->numberForKey("gravityy");
		type->speed = (float)dict->numberForKey("speed");
		type->speedVariance = (float)dict->numberForKey("speedVariance");
		type->radialAcceleration = (float)dict->numberForKey("radialAcceleration");
		type->radialAccelVariance = (float)dict->numberForKey("radialAccelVariance");
		type->tangentialAcceleration = (float)dict->numberForKey("tangentialAcceleration");
		type->tangentialAccelVariance = (float)dict->numberForKey("tangentialAccelVariance");
		type->rotationIsDir = dict->numberForKey("rotationIsDir") != 0;
		type->maxRadius = (float)dict->numberForKey("maxRadius");
		type->maxRadiusVariance = (float)dict->numberForKey("maxRadiusVariance");
		type->minRadius = (float)dict->numberForKey("minRadius");
		type->minRadiusVariance = (float)dict->numberForKey("minRadiusVariance");
		type->rotatePerSecond = (float)dict->numberForKey("rotatePerSecond");
		type->rotatePerSecondVariance = (float)dict->numberForKey("rotatePerSecondVariance");
		type->particleLifespan = (float)dict->numberForKey("particleLifespan");
		type->particleLifespanVariance = (float)dict->numberForKey("particleLifespanVariance");
		type->emissionRate = (float)(type->maxParticles) / type->particleLifespan;
		type->textureFileName = dict->stringForKey("textureFileName");
		const char* textureData = dict->stringForKey("textureImageData");
		if (textureData[0])
		{
			CCParticleSystem::dataToTexture(type->textureFileName.c_str(), textureData);
		}
		float textureRectx = (float)dict->numberForKey("textureRectx");
		float textureRecty = (float)dict->numberForKey("textureRecty");
		float textureRectw = (float)dict->numberForKey("textureRectw");
		float textureRecth = (float)dict->numberForKey("textureRecth");
		CCRect textureRect(textureRectx, textureRecty, textureRectw, textureRecth);
		type->textureRect = textureRect;
		_parDict[filename] = type;
		return type;
	}
}

CCParticleSystemQuad* oParticleCache::loadParticle( const char* filename )
{
	oParticleDef* type = oParticleCache::load(filename);
	return type->toParticle();
}

bool oParticleCache::unload( const char* filename )
{
	auto it = _parDict.find(filename);
	if (it != _parDict.end())
	{
		_parDict.erase(it);
		return true;
	}
	return false;
}

bool oParticleCache::unload()
{
	if (_parDict.empty())
	{
		return false;
	}
	else
	{
		_parDict.clear();
		return true;
	}
}

void oParticleCache::removeUnused()
{
	if (!_parDict.empty())
	{
		for (auto it = _parDict.begin(); it != _parDict.end();)
		{
			if (it->second->isSingleReference())
			{
				it = _parDict.erase(it);
			}
			else ++it;
		}
	}
}

oParticleCache* oParticleCache::shared()
{
	static oParticleCache particleCache;
	return &particleCache;
}

CCParticleSystemQuad* oParticleDef::toParticle()
{
	return oParticleSystemQuad::createWithDef(this);
}

NS_DOROTHY_END
