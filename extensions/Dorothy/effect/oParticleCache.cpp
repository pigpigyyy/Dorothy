#include "Dorothy/const/oDefine.h"
#include "Dorothy/effect/oParticleCache.h"
#include "Dorothy/model/oFace.h"
#include "Dorothy/misc/oContent.h"

NS_DOROTHY_BEGIN

oParticleType* oParticleCache::load( const char* filename )
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
		auto dictionary = CCDictionary::createWithContents(data, size);

		oParticleType* type = new oParticleType();
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
		const char * pszTmp = nullptr;
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

		_parDict[filename] = type;
		return type;
	}
}

CCParticleSystem* oParticleCache::loadParticle( const char* filename )
{
	oParticleType* type = oParticleCache::load(filename);
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

oParticleCache* oParticleCache::shared()
{
	static oParticleCache particleCache;
	return &particleCache;
}

CCParticleSystem* oParticleType::toParticle()
{
	return oParticleSystemQuad::createWithType(this);
}

NS_DOROTHY_END
