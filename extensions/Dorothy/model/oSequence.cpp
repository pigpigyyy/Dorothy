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
	virtual ExtraAction* reverse(void)
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

oSequence* oSequence::createWithTwoActions(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo)
{
	oSequence *pSequence = new oSequence();
	pSequence->initWithTwoActions(pActionOne, pActionTwo);
	pSequence->autorelease();

	return pSequence;
}

oSequence* oSequence::create(CCFiniteTimeAction *pAction1, ...)
{
	va_list params;
	va_start(params, pAction1);

	oSequence *pRet = oSequence::createWithVariableList(pAction1, params);

	va_end(params);

	return pRet;
}

oSequence* oSequence::createWithVariableList(CCFiniteTimeAction *pAction1, va_list args)
{
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
			// If only one action is added to oSequence, make up a oSequence by adding a simplest finite time action.
			if (bOneAction)
			{
				pPrev = createWithTwoActions(pPrev, ExtraAction::create());
			}
			break;
		}
	}

	return ((oSequence*)pPrev);
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

oSequence::~oSequence(void)
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

void oSequence::stop(void)
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

oActionDuration* oSequence::reverse(void)
{
	return oSequence::createWithTwoActions(m_pActions[1]->reverse(), m_pActions[0]->reverse());
}

NS_DOROTHY_END