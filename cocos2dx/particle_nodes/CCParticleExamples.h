/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __CCPARTICLE_EXAMPLE_H__
#define __CCPARTICLE_EXAMPLE_H__

#include "CCParticleSystemQuad.h"

NS_CC_BEGIN

/**
 * @addtogroup particle_nodes
 * @{
 */

//! @brief A fire particle system
class CC_DLL CCParticleFire : public CCParticleSystemQuad
{
public:
    CCParticleFire(){}
    virtual ~CCParticleFire(){}
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleFire* create(unsigned int numberOfParticles = 250);
};

//! @brief A fireworks particle system
class CC_DLL CCParticleFireworks : public CCParticleSystemQuad
{
public:
    CCParticleFireworks(){}
    virtual ~CCParticleFireworks(){}
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleFireworks* create(unsigned int numberOfParticles = 1500);
};

//! @brief A sun particle system
class CC_DLL CCParticleSun : public CCParticleSystemQuad
{
public:
    CCParticleSun(){}
    virtual ~CCParticleSun(){}
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    static CCParticleSun* create(unsigned int numberOfParticles = 350);
};

//! @brief A galaxy particle system
class CC_DLL CCParticleGalaxy : public CCParticleSystemQuad
{
public:
    CCParticleGalaxy(){}
    virtual ~CCParticleGalaxy(){}
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleGalaxy* create(unsigned int numberOfParticles = 200);
};

//! @brief A flower particle system
class CC_DLL CCParticleFlower : public CCParticleSystemQuad
{
public:
    CCParticleFlower(){}
    virtual ~CCParticleFlower(){}
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleFlower* create(unsigned int numberOfParticles = 250);
};

//! @brief A meteor particle system
class CC_DLL CCParticleMeteor : public CCParticleSystemQuad
{
public:
    CCParticleMeteor(){}
    virtual ~CCParticleMeteor(){}
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleMeteor* create(unsigned int numberOfParticles = 150);
};

//! @brief An spiral particle system
class CC_DLL CCParticleSpiral : public CCParticleSystemQuad
{
public:
    CCParticleSpiral(){}
    virtual ~CCParticleSpiral(){}
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleSpiral* create(unsigned int numberOfParticles = 500);
};

//! @brief An explosion particle system
class CC_DLL CCParticleExplosion : public CCParticleSystemQuad
{
public:
    CCParticleExplosion(){}
    virtual ~CCParticleExplosion(){}
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleExplosion* create(unsigned int numberOfParticles = 700);
};

//! @brief An smoke particle system
class CC_DLL CCParticleSmoke : public CCParticleSystemQuad
{
public:
    CCParticleSmoke(){}
    virtual ~CCParticleSmoke(){}
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleSmoke* create(unsigned int numberOfParticles = 200);
};

//! @brief An snow particle system
class CC_DLL CCParticleSnow : public CCParticleSystemQuad
{
public:
    CCParticleSnow(){}
    virtual ~CCParticleSnow(){}
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleSnow* create(unsigned int numberOfParticles = 700);
};

//! @brief A rain particle system
class CC_DLL CCParticleRain : public CCParticleSystemQuad
{
public:
    CCParticleRain(){}
    virtual ~CCParticleRain(){}
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	static CCParticleRain* create(unsigned int numberOfParticles = 1000);
};

// end of particle_nodes group
/// @}

NS_CC_END

#endif //__CCPARTICLE_EXAMPLE_H__
