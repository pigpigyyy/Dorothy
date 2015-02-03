/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/effect/oParticleCache.h"
#include "Dorothy/model/oFace.h"
#include "Dorothy/misc/oContent.h"
#include "Dorothy/misc/oHelper.h"

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
		auto dictionary = CCDictionary::createWithContents(data, (unsigned int)size);

		oParticleDef* type = new oParticleDef();
		type->autorelease();

		type->maxParticles = atoi(valueForKey("maxParticles", dictionary));
		type->angle = (float)atof(valueForKey("angle", dictionary));
		type->angleVariance = (float)atof(valueForKey("angleVariance", dictionary));
		type->duration = (float)atof(valueForKey("duration", dictionary));
		type->blendAdditive = atoi(valueForKey("blendAdditive", dictionary));
		type->blendFuncSource = atoi(valueForKey("blendFuncSource", dictionary));
		type->blendFuncDestination = atoi(valueForKey("blendFuncDestination", dictionary));
		type->startColorRed = (float)atof(valueForKey("startColorRed", dictionary));
		type->startColorGreen = (float)atof(valueForKey("startColorGreen", dictionary));
		type->startColorBlue = (float)atof(valueForKey("startColorBlue", dictionary));
		type->startColorAlpha = (float)atof(valueForKey("startColorAlpha", dictionary));
		type->startColorVarianceRed = (float)atof(valueForKey("startColorVarianceRed", dictionary));
		type->startColorVarianceGreen = (float)atof(valueForKey("startColorVarianceGreen", dictionary));
		type->startColorVarianceBlue = (float)atof(valueForKey("startColorVarianceBlue", dictionary));
		type->startColorVarianceAlpha = (float)atof(valueForKey("startColorVarianceAlpha", dictionary));
		type->finishColorRed = (float)atof(valueForKey("finishColorRed", dictionary));
		type->finishColorGreen = (float)atof(valueForKey("finishColorGreen", dictionary));
		type->finishColorBlue = (float)atof(valueForKey("finishColorBlue", dictionary));
		type->finishColorAlpha = (float)atof(valueForKey("finishColorAlpha", dictionary));
		type->finishColorVarianceRed = (float)atof(valueForKey("finishColorVarianceRed", dictionary));
		type->finishColorVarianceGreen = (float)atof(valueForKey("finishColorVarianceGreen", dictionary));
		type->finishColorVarianceBlue = (float)atof(valueForKey("finishColorVarianceBlue", dictionary));
		type->finishColorVarianceAlpha = (float)atof(valueForKey("finishColorVarianceAlpha", dictionary));
		type->startParticleSize = (float)atof(valueForKey("startParticleSize", dictionary));
		type->startParticleSizeVariance = (float)atof(valueForKey("startParticleSizeVariance", dictionary));
		type->finishParticleSize = (float)atof(valueForKey("finishParticleSize", dictionary));
		type->finishParticleSizeVariance = (float)atof(valueForKey("finishParticleSizeVariance", dictionary));
		type->sourcePositionx = (float)atof(valueForKey("sourcePositionx", dictionary));
		type->sourcePositiony = (float)atof(valueForKey("sourcePositiony", dictionary));		
		type->sourcePositionVariancex = (float)atof(valueForKey("sourcePositionVariancex", dictionary));
		type->sourcePositionVariancey = (float)atof(valueForKey("sourcePositionVariancey", dictionary));
		type->rotationStart = (float)atof(valueForKey("rotationStart", dictionary));
		type->rotationStartVariance = (float)atof(valueForKey("rotationStartVariance", dictionary));
		type->rotationEnd= (float)atof(valueForKey("rotationEnd", dictionary));
		type->rotationEndVariance= (float)atof(valueForKey("rotationEndVariance", dictionary));
		type->emitterType = atoi(valueForKey("emitterType", dictionary));
		type->gravityx = (float)atof(valueForKey("gravityx", dictionary));
		type->gravityy = (float)atof(valueForKey("gravityy", dictionary));
		type->speed = (float)atof(valueForKey("speed", dictionary));
		type->speedVariance = (float)atof(valueForKey("speedVariance", dictionary));
		const char* pszTmp = nullptr;
		pszTmp = valueForKey("radialAcceleration", dictionary);
		type->radialAcceleration = (pszTmp) ? (float)atof(pszTmp) : 0;
		pszTmp = valueForKey("radialAccelVariance", dictionary);
		type->radialAccelVariance = (pszTmp) ? (float)atof(pszTmp) : 0;
		pszTmp = valueForKey("tangentialAcceleration", dictionary);
		type->tangentialAcceleration = (pszTmp) ? (float)atof(pszTmp) : 0;
		pszTmp = valueForKey("tangentialAccelVariance", dictionary);
		type->tangentialAccelVariance = (pszTmp) ? (float)atof(pszTmp) : 0;
		type->maxRadius = (float)atof(valueForKey("maxRadius", dictionary));
		type->maxRadiusVariance = (float)atof(valueForKey("maxRadiusVariance", dictionary));
		type->minRadius = (float)atof(valueForKey("minRadius", dictionary));
		type->minRadiusVariance = 0;
		type->rotatePerSecond = (float)atof(valueForKey("rotatePerSecond", dictionary));
		type->rotatePerSecondVariance = (float)atof(valueForKey("rotatePerSecondVariance", dictionary));
		type->particleLifespan = (float)atof(valueForKey("particleLifespan", dictionary));
		type->particleLifespanVariance = (float)atof(valueForKey("particleLifespanVariance", dictionary));
		type->emissionRate = (float)(type->maxParticles) / type->particleLifespan;
		type->textureFileName = (char*)valueForKey("textureFileName", dictionary);
		const char* textRectStr = (char*)valueForKey("textureRect", dictionary);
		if (textRectStr)
		{
			int x, y, w, h;
			oHelper::getRectFromStr(textRectStr, x, y, w, h);
			type->textureRect = CCRectMake(x, y, w, h);
		}
		_parDict[filename] = type;
		return type;
	}
}

CCParticleSystem* oParticleCache::loadParticle( const char* filename )
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

CCParticleSystem* oParticleDef::toParticle()
{
	return oParticleSystemQuad::createWithDef(this);
}

NS_DOROTHY_END
