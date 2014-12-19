/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/model/oSequence.h"

NS_DOROTHY_BEGIN

class ExtraAction : public CCFiniteTimeAction
{
public:
	static ExtraAction* create()
	{
		ExtraAction* pRet = new ExtraAction();
		pRet->autorelease();
		return pRet;
	}
	virtual CCObject* copyWithZone(CCZone* pZone)
	{
		CC_UNUSED_PARAM(pZone);
		ExtraAction* pRet = new ExtraAction();
		return pRet;
	}
	virtual ExtraAction* reverse()
	{
		return ExtraAction::create();
	}
	virtual void update(float time)
	{
		CC_UNUSED_PARAM(time);
	}
	virtual void step(float dt)
	{
		CC_UNUSED_PARAM(dt);
	}
};

MEMORY_POOL(oSequence)

oSequence* oSequence::createWithTwoActions(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo)
{
	oSequence *pSequence = new oSequence();
	pSequence->initWithTwoActions(pActionOne, pActionTwo);
	pSequence->autorelease();

	return pSequence;
}

oSequence* oSequence::create(CCFiniteTimeAction *pAction1, ...)
{
	va_list args;

	CCFiniteTimeAction *pNow;
	CCFiniteTimeAction *pPrev = pAction1;
	bool bOneAction = true;

	va_start(args, pAction1);
	while (pAction1)
	{
		pNow = va_arg(args, CCFiniteTimeAction*);
		if (pNow)
		{
			pPrev = createWithTwoActions(pPrev, pNow);
			bOneAction = false;
		}
		else
		{
			// If only one action is added to oSequence, make up a oSequence by adding a simplest finite time action.
			if (bOneAction)
			{
				pPrev = createWithTwoActions(pPrev, ExtraAction::create());
			}
			break;
		}
	}
	va_end(args);

	oSequence* pRet = (oSequence*)pPrev;

	return pRet;
}

oSequence* oSequence::create(CCFiniteTimeAction* actions[], int count)
{
	oSequence* pRet = nullptr;
	BLOCK_START
	{
		BREAK_IF(count == 0);
		CCFiniteTimeAction* prev = actions[0];
		if (count > 1)
		{
			for (int i = 1; i < count; ++i)
			{
				prev = createWithTwoActions(prev, actions[i]);
			}
		}
		else
		{
			prev = createWithTwoActions(prev, ExtraAction::create());
		}
		pRet = (oSequence*)prev;
	}
	BLOCK_END
	return pRet;
}

oSequence* oSequence::create(CCArray* arrayOfActions)
{
	oSequence* pRet = NULL;
	do 
	{
		unsigned  int count = arrayOfActions->count();
		CC_BREAK_IF(count == 0);

		CCFiniteTimeAction* prev = (CCFiniteTimeAction*)arrayOfActions->objectAtIndex(0);

		if (count > 1)
		{
			for (unsigned int i = 1; i < count; ++i)
			{
				prev = createWithTwoActions(prev, (CCFiniteTimeAction*)arrayOfActions->objectAtIndex(i));
			}
		}
		else
		{
			// If only one action is added to oSequence, make up a oSequence by adding a simplest finite time action.
			prev = createWithTwoActions(prev, ExtraAction::create());
		}
		pRet = (oSequence*)prev;
	}while (0);
	return pRet;
}

bool oSequence::initWithTwoActions(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo)
{
	CCAssert(pActionOne != NULL, "");
	CCAssert(pActionTwo != NULL, "");

	float d = pActionOne->getDuration() + pActionTwo->getDuration();
	oActionDuration::initWithDuration(d);

	m_pActions[0] = pActionOne;
	pActionOne->retain();

	m_pActions[1] = pActionTwo;
	pActionTwo->retain();

	return true;
}

CCObject* oSequence::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	oSequence* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (oSequence*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new oSequence();
		pZone = pNewZone = new CCZone(pCopy);
	}

	oActionDuration::copyWithZone(pZone);

	pCopy->initWithTwoActions((CCFiniteTimeAction*)(m_pActions[0]->copy()->autorelease()), 
		(CCFiniteTimeAction*)(m_pActions[1]->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

oSequence::~oSequence()
{
	CC_SAFE_RELEASE(m_pActions[0]);
	CC_SAFE_RELEASE(m_pActions[1]);
}

void oSequence::startWithTarget(CCNode *pTarget)
{
	oActionDuration::startWithTarget(pTarget);
	m_split = m_pActions[0]->getDuration() / (m_pActions[0]->getDuration() + m_pActions[1]->getDuration());
	m_last = -1;
}

void oSequence::stop()
{
	// Issue #1305
	if(m_last != -1)
	{
		m_pActions[m_last]->stop();
		m_last = -1;
	}
	oActionDuration::stop();
}

void oSequence::update(float t)
{
	int found = 0;
	float new_t = 0.0f;
	if(t < m_split)
	{
		// action[0]
		new_t = (m_split != 0.0f) ? (t/m_split) : 1.0f;
		if (m_last == 1) // restart
		{
			m_pActions[1]->update(0.0f);
			m_pActions[1]->stop();
		}
	}
	else
	{
		// action[1]
		found = 1;
		new_t = (m_split == 1.0f) ? 1.0f : ((t-m_split)/(1.0f-m_split));
		if (m_last == -1)
		{
			// action[0] was skipped, execute it.
			m_pActions[0]->startWithTarget(m_pTarget);
			m_pActions[0]->update(1.0f);
			m_pActions[0]->stop();
		}
		else if (m_last == 0)
		{
			// switching to action 1. stop action 0.
			m_pActions[0]->update(1.0f);
			m_pActions[0]->stop();
		}
	}
	if (found != m_last)
	{
		m_pActions[found]->startWithTarget(m_pTarget);
	}
	else if (m_pActions[found]->isDone()) // Last action found and it is done
	{
		return;
	}
	m_pActions[found]->update(new_t);
	m_last = found;
}

oActionDuration* oSequence::reverse()
{
	return oSequence::createWithTwoActions(m_pActions[1]->reverse(), m_pActions[0]->reverse());
}

MEMORY_POOL(oSpawn)

oSpawn* oSpawn::create(CCFiniteTimeAction *pAction1, ...)
{
	va_list args;
	va_start(args, pAction1);

	CCFiniteTimeAction *pNow;
	CCFiniteTimeAction *pPrev = pAction1;
	bool bOneAction = true;

	while (pAction1)
	{
		pNow = va_arg(args, CCFiniteTimeAction*);
		if (pNow)
		{
			pPrev = createWithTwoActions(pPrev, pNow);
			bOneAction = false;
		}
		else
		{
			// If only one action is added to oSpawn, make up a oSpawn by adding a simplest finite time action.
			if (bOneAction)
			{
				pPrev = createWithTwoActions(pPrev, ExtraAction::create());
			}
			break;
		}
	}
	oSpawn* pRet = (oSpawn*)pPrev;

	va_end(args);

	return pRet;
}

oSpawn* oSpawn::create(CCFiniteTimeAction* actions[], int count)
{
	oSpawn* pRet = nullptr;
	BLOCK_START
	{
		BREAK_IF(count == 0);
		CCFiniteTimeAction* prev = actions[0];
		if (count > 1)
		{
			for (int i = 1; i < count; ++i)
			{
				prev = createWithTwoActions(prev, actions[i]);
			}
		}
		else
		{
			prev = createWithTwoActions(prev, ExtraAction::create());
		}
		pRet = (oSpawn*)prev;
	}
	BLOCK_END
	return pRet;
}

oSpawn* oSpawn::create(CCArray *arrayOfActions)
{
	oSpawn* pRet = NULL;
	do
	{
		unsigned  int count = arrayOfActions->count();
		CC_BREAK_IF(count == 0);
		CCFiniteTimeAction* prev = (CCFiniteTimeAction*)arrayOfActions->objectAtIndex(0);
		if (count > 1)
		{
			for (unsigned int i = 1; i < arrayOfActions->count(); ++i)
			{
				prev = createWithTwoActions(prev, (CCFiniteTimeAction*)arrayOfActions->objectAtIndex(i));
			}
		}
		else
		{
			// If only one action is added to oSpawn, make up a oSpawn by adding a simplest finite time action.
			prev = createWithTwoActions(prev, ExtraAction::create());
		}
		pRet = (oSpawn*)prev;
	} while (0);

	return pRet;
}

oSpawn* oSpawn::createWithTwoActions(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2)
{
	oSpawn *pSpawn = new oSpawn();
	pSpawn->initWithTwoActions(pAction1, pAction2);
	pSpawn->autorelease();

	return pSpawn;
}

bool oSpawn::initWithTwoActions(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2)
{
	CCAssert(pAction1 != NULL, "");
	CCAssert(pAction2 != NULL, "");

	bool bRet = false;

	float d1 = pAction1->getDuration();
	float d2 = pAction2->getDuration();

	if (CCActionInterval::initWithDuration(MAX(d1, d2)))
	{
		m_pOne = pAction1;
		m_pTwo = pAction2;

		if (d1 > d2)
		{
			m_pTwo = CCSequence::createWithTwoActions(pAction2, CCDelayTime::create(d1 - d2));
		}
		else if (d1 < d2)
		{
			m_pOne = CCSequence::createWithTwoActions(pAction1, CCDelayTime::create(d2 - d1));
		}

		m_pOne->retain();
		m_pTwo->retain();

		bRet = true;
	}


	return bRet;
}

CCObject* oSpawn::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	oSpawn* pCopy = NULL;

	if (pZone && pZone->m_pCopyObject)
	{
		//in case of being called at sub class
		pCopy = (oSpawn*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new oSpawn();
		pZone = pNewZone = new CCZone(pCopy);
	}

	CCActionInterval::copyWithZone(pZone);

	pCopy->initWithTwoActions((CCFiniteTimeAction*)(m_pOne->copy()->autorelease()),
		(CCFiniteTimeAction*)(m_pTwo->copy()->autorelease()));

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

oSpawn::~oSpawn()
{
	CC_SAFE_RELEASE(m_pOne);
	CC_SAFE_RELEASE(m_pTwo);
}

void oSpawn::startWithTarget(CCNode *pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	m_pOne->startWithTarget(pTarget);
	m_pTwo->startWithTarget(pTarget);
}

void oSpawn::stop()
{
	m_pOne->stop();
	m_pTwo->stop();
	CCActionInterval::stop();
}

void oSpawn::update(float time)
{
	if (m_pOne)
	{
		m_pOne->update(time);
	}
	if (m_pTwo)
	{
		m_pTwo->update(time);
	}
}

CCActionInterval* oSpawn::reverse()
{
	return oSpawn::createWithTwoActions(m_pOne->reverse(), m_pTwo->reverse());
}

NS_DOROTHY_END
