#ifndef __DOROTHY_OPARTICLE_CACHE_H__
#define __DOROTHY_OPARTICLE_CACHE_H__

NS_DOROTHY_BEGIN

/** @brief Particle file is cached as a particle type. */
class oParticleType: public CCObject
{
public:
	float angle;
	float angleVariance;
	int blendAdditive;
	int blendFuncDestination;
	int blendFuncSource;
	float duration;
	int emitterType;
	float emissionRate;
	float finishColorAlpha;
	float finishColorBlue;
	float finishColorGreen;
	float finishColorRed;
	float finishColorVarianceAlpha;
	float finishColorVarianceBlue;
	float finishColorVarianceGreen;
	float finishColorVarianceRed;
	float rotationStart;
	float rotationStartVariance;
	float rotationEnd;
	float rotationEndVariance;
	float finishParticleSize;
	float finishParticleSizeVariance;
	float gravityx;
	float gravityy;
	int maxParticles;
	float maxRadius;
	float maxRadiusVariance;
	float minRadius;
	float minRadiusVariance;
	float particleLifespan;
	float particleLifespanVariance;
	float radialAccelVariance;
	float radialAcceleration;
	float rotatePerSecond;
	float rotatePerSecondVariance;
	float sourcePositionVariancex;
	float sourcePositionVariancey;
	float sourcePositionx;
	float sourcePositiony;
	float speed;
	float speedVariance;
	float startColorAlpha;
	float startColorBlue;
	float startColorGreen;
	float startColorRed;
	float startColorVarianceAlpha;
	float startColorVarianceBlue;
	float startColorVarianceGreen;
	float startColorVarianceRed;
	float startParticleSize;
	float startParticleSizeVariance;
	float tangentialAccelVariance;
	float tangentialAcceleration;
	string textureFileName;
	CCParticleSystem* toParticle();
};

/** @brief This class caches particle file in memory,
 so you won`t need to read the ".particle" file over again when you create a particle.
 In mostly the way of cocos2dx`s to load particle from .plist file.
 I`m not a perfectionist, so I do not replace the dirty way they load xml file with mine.
*/
class oParticleCache
{
public:
	/** Load a new particle file and cache it or get it from cache. */
	oParticleType* load(const char* filename);
	/** Load a new particle file and cache it or get it from cache and return a new instance. */
	CCParticleSystem* loadParticle(const char* filename);
	/** Purge cached file in memory with given filename. */
	bool unload(const char* filename);
	/** Purge all cached file in memory. */
	bool unload();
	/** Singleton method. */
	static oParticleCache* shared();
protected:
	hash_strmap<oRef<oParticleType>> _parDict;
private:
	inline const char* valueForKey(const char* key, CCDictionary* dict)
	{
		CCString* pString = (CCString*)dict->objectForKey(string(key));
		return pString ? pString->m_sString.c_str() : "";
	}
};

#define oSharedParticleCache (*oParticleCache::shared())

NS_DOROTHY_END

#endif
