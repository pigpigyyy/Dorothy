/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

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

bool oActionDuration::isDone()
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

oActionDuration* oActionDuration::reverse()
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
