/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_MODEL_OSEQUENCE_H__
#define __DOROTHY_MODEL_OSEQUENCE_H__

#include "Dorothy/model/oActionDuration.h"

NS_DOROTHY_BEGIN

class oSequence: public oActionDuration
{
public:
	~oSequence();
	bool initWithTwoActions(CCFiniteTimeAction* pActionOne, CCFiniteTimeAction* pActionTwo);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);
	virtual void stop();
	virtual void update(float t);
	virtual oActionDuration* reverse();
	static oSequence* create(CCFiniteTimeAction* pAction1, ...);
	static oSequence* create(CCArray* arrayOfActions);
	static oSequence* createWithVariableList(CCFiniteTimeAction* pAction1, va_list args);
	static oSequence* createWithTwoActions(CCFiniteTimeAction* pActionOne, CCFiniteTimeAction* pActionTwo);
protected:
	CCFiniteTimeAction* m_pActions[2];
	float m_split;
	int m_last;
public:
	inline void* operator new(size_t size){ return _memory.alloc(); }
	inline void operator delete(void* ptr, size_t size) { _memory.free(ptr); }
private:
	static oMemoryPool<oSequence> _memory;
};

class oSpawn: public CCActionInterval
{
public:
	~oSpawn();
	bool initWithTwoActions(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode *pTarget);
	virtual void stop();
	virtual void update(float time);
	virtual CCActionInterval* reverse();
public:
	static oSpawn* create(CCFiniteTimeAction *pAction1, ...);
	static oSpawn* createWithVariableList(CCFiniteTimeAction *pAction1, va_list args);
	static oSpawn* create(CCArray *arrayOfActions);
	static oSpawn* createWithTwoActions(CCFiniteTimeAction *pAction1, CCFiniteTimeAction *pAction2);
protected:
	CCFiniteTimeAction* m_pOne;
	CCFiniteTimeAction* m_pTwo;
public:
	inline void* operator new(size_t size){ return _memory.alloc(); }
	inline void operator delete(void* ptr, size_t size) { _memory.free(ptr); }
private:
	static oMemoryPool<oSpawn> _memory;
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OSEQUENCE_H__