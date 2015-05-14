/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_OCALLFUNC_H__
#define __DOROTHY_OCALLFUNC_H__

#include "Dorothy/const/oDefine.h"

NS_DOROTHY_BEGIN

/** Use it to avoid circular references */
class oCallFunc: public CCActionInstant
{
public:
	static oCallFunc* create(CCObject* selectorTarget, SEL_CallFunc selector)
	{
		oCallFunc* ret = new oCallFunc();
		if (ret && ret->initWithTarget(selectorTarget))
		{
			ret->_callFunc = selector;
			ret->autorelease();
			return ret;
		}
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
	virtual bool initWithTarget(CCObject* selectorTarget)
	{
		if (!CCActionInstant::init()) return false;
		_selectorTarget = selectorTarget;
		return true;
	}
	virtual void execute()
	{
		(_selectorTarget->*_callFunc)();
	}
	virtual void update(float time)
	{
		if (time == 1.0f)
		{
			this->execute();
		}
	}
	CCObject* copyWithZone(CCZone* pZone)
	{
		return nullptr;
	}
protected:
	CCObject* _selectorTarget;
	SEL_CallFunc _callFunc;
};

class oCallFunction: public CCActionInstant
{
public:
	static oCallFunction* create(const function<void()>& func)
	{
		oCallFunction* ret = new oCallFunction();
		if (ret && ret->initWithTarget(nullptr))
		{
			ret->_func = func;
			ret->autorelease();
			return ret;
		}
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
	virtual bool initWithTarget(CCObject* selectorTarget)
	{
		if (!CCActionInstant::init()) return false;
		return true;
	}
	virtual void execute()
	{
		_func();
	}
	virtual void update(float time)
	{
		if (time == 1.0f)
		{
			this->execute();
		}
	}
	CCObject* copyWithZone(CCZone* pZone)
	{
		return nullptr;
	}
protected:
	function<void()> _func;
};

NS_DOROTHY_END

#endif // __DOROTHY_OCALLFUNC_H__
