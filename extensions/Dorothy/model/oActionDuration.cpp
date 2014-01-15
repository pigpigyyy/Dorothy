#include "Dorothy/const/oDefine.h"
#include "Dorothy/model/oActionDuration.h"

NS_DOROTHY_BEGIN

oActionDuration::oActionDuration():
_pause(false),
_speed(1.0f)
{ }

oActionDuration* oActionDuration::create(float d)
{
	oActionDuration* action = new oActionDuration();
	action->initWithDuration(d);
	action->autorelease();
	return action;
}

bool oActionDuration::initWithDuration(float d)
{
	m_fDuration = MAX(d, FLT_EPSILON);
	_elapsed = -1;
	return true;
}

CCObject* oActionDuration::copyWithZone(CCZone* pZone)
{
	CCZone* pNewZone = nullptr;
	oActionDuration* pCopy = nullptr;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (oActionDuration*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new oActionDuration();
		pZone = pNewZone = new CCZone(pCopy);
	}
	CCFiniteTimeAction::copyWithZone(pZone);
	CC_SAFE_DELETE(pNewZone);
	pCopy->initWithDuration(m_fDuration);
	return pCopy;
}

bool oActionDuration::isDone(void)
{
	return _elapsed < 0 || _elapsed >= m_fDuration;
}

void oActionDuration::step(float dt)
{
	if (_pause)
	{
		return;
	}
	_elapsed += (dt * _speed);
	float time = _elapsed/m_fDuration;
	this->update(MIN(1.0f, time));
}

void oActionDuration::startWithTarget(CCNode* target)
{
	CCFiniteTimeAction::startWithTarget(target);
	_elapsed = 0.0f;
	_pause = false;
}

oActionDuration* oActionDuration::reverse(void)
{
	CCAssert(false, "oActionDuration: reverse not implemented.");
	return nullptr;
}

void oActionDuration::setSpeed( float speed )
{
	_speed = speed;
}

float oActionDuration::getSpeed() const
{
	return _speed;
}

void oActionDuration::setTime(float var)
{
	if (var > 1.0f)
	{
		var = 1.0f;
	}
	else if (var < 0)
	{
		var = 0;
	}
	_elapsed = m_fDuration * var;
	this->update(var);
}

float oActionDuration::getTime() const
{
	return _elapsed / m_fDuration;
}

float oActionDuration::getElapsed() const
{
	return _elapsed;
}

void oActionDuration::pause()
{
	_pause = true;
}

bool oActionDuration::isPaused() const
{
	return _pause;
}

void oActionDuration::resume()
{
	_pause = false;
}

NS_DOROTHY_END
