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
