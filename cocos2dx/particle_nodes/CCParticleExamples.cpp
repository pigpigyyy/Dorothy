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
#include "CCParticleExamples.h"
#include "CCDirector.h"
#include "textures/CCTextureCache.h"
#include "support/CCPointExtension.h"
#include "platform/CCImage.h"

NS_CC_BEGIN

//
// ParticleFire
//
CCParticleFire* CCParticleFire::create(unsigned int numberOfParticles)
{
    CCParticleFire* pRet = new CCParticleFire();
    if (pRet && pRet->initWithTotalParticles(numberOfParticles))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool CCParticleFire::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( CCParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        m_fDuration = kCCParticleDurationInfinity;

        // Gravity Mode
        this->m_nEmitterMode = kCCParticleModeGravity;

        // Gravity Mode: gravity
        this->modeA.gravity = ccp(0,0);

        // Gravity Mode: radial acceleration
        this->modeA.radialAccel = 0;
        this->modeA.radialAccelVar = 0;

        // Gravity Mode: speed of particles
        this->modeA.speed = 60;
        this->modeA.speedVar = 20;        

        // starting angle
        m_fAngle = 90;
        m_fAngleVar = 10;

        // emitter position
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        this->setPosition(ccp(winSize.width/2, 60));
        this->m_tPosVar = ccp(40, 20);

        // life of particles
        m_fLife = 3;
        m_fLifeVar = 0.25f;


        // size, in pixels
        m_fStartSize = 54.0f;
        m_fStartSizeVar = 10.0f;
        m_fEndSize = kCCParticleStartSizeEqualToEndSize;

        // emits per frame
        m_fEmissionRate = m_uTotalParticles/m_fLife;

        // color of particles
        m_tStartColor.r = 0.76f;
        m_tStartColor.g = 0.25f;
        m_tStartColor.b = 0.12f;
        m_tStartColor.a = 1.0f;
        m_tStartColorVar.r = 0.0f;
        m_tStartColorVar.g = 0.0f;
        m_tStartColorVar.b = 0.0f;
        m_tStartColorVar.a = 0.0f;
        m_tEndColor.r = 0.0f;
        m_tEndColor.g = 0.0f;
        m_tEndColor.b = 0.0f;
        m_tEndColor.a = 1.0f;
        m_tEndColorVar.r = 0.0f;
        m_tEndColorVar.g = 0.0f;
        m_tEndColorVar.b = 0.0f;
        m_tEndColorVar.a = 0.0f;

        CCTexture2D* pTexture = getDefaultTexture();
        if (pTexture != NULL)
        {
            setTexture(pTexture);
        }
        
        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}

NS_CC_END
