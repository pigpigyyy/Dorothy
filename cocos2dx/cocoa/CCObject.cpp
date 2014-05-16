/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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


#include "CCObject.h"
#include "CCAutoreleasePool.h"
#include "ccMacros.h"
#include "script_support/CCScriptSupport.h"
#include <stack>
using std::stack;

static unsigned int g_maxObjectCount = 0;
static stack<unsigned int> g_availableObjectIds;

static unsigned int g_maxLuaCount = 0;
static stack<unsigned int> g_availableLuaIds;

static unsigned int g_luaRefCount = 0;

NS_CC_BEGIN

int g_luaType = 2;

CCObject* CCCopying::copyWithZone(CCZone *pZone)
{
    CC_UNUSED_PARAM(pZone);
    CCAssert(0, "not implement");
    return 0;
}

CCObject::CCObject()
: _isManaged(false)
, _ref(1) // when the object is created, the reference count of it is 1
, _luaRef(0)
, _weak(NULL)
{
	if (g_availableObjectIds.empty())
	{
		_id = ++g_maxObjectCount;
	}
	else
	{
		_id = g_availableObjectIds.top();
		g_availableObjectIds.pop();
	}
}

CCObject::~CCObject()
{
	CCAssert(!_isManaged, "object is still managed when destroyed");
	g_availableObjectIds.push(_id);
	if (_luaRef != 0)
	{
		g_availableLuaIds.push(_luaRef);
	}
}

CCObject* CCObject::copy()
{
    return copyWithZone(0);
}

void CCObject::release()
{
    CCAssert(_ref > 0, "reference count should greater than 0");
    --_ref;
    if (_ref == 0)
    {
		if (_weak)
		{
			_weak->target = NULL;
			_weak->release();
		}
        delete this;
    }
}

void CCObject::retain()
{
	CCAssert(_ref > 0, "reference count should greater than 0");
    ++_ref;
}

CCObject* CCObject::autorelease()
{
	CCAssert(!_isManaged, "object is already managed");
	_isManaged = true;
	CCPoolManager::sharedPoolManager()->addObject(this);
	return this;
}

bool CCObject::isSingleReference()
{
    return _ref == 1;
}

unsigned int CCObject::getRetainCount()
{
    return _ref;
}

bool CCObject::isEqual(const CCObject *pObject)
{
    return this == pObject;
}

void CCObject::update( float dt )
{
	CC_UNUSED_PARAM(dt);
}

unsigned int CCObject::getObjectId() const
{
	return _id;
}

unsigned int CCObject::getObjectCount()
{
	return g_maxObjectCount - g_availableObjectIds.size();
}

unsigned int CCObject::getLuaRefCount()
{
	return g_luaRefCount;
}

CCWeak* CCObject::getWeakRef()
{
	if (!_weak)
	{
		_weak = new CCWeak(this);
		return _weak;
	}
	return _weak;
}

void CCObject::addLuaRef()
{
	++g_luaRefCount;
}

void CCObject::removeLuaRef()
{
	--g_luaRefCount;
}

unsigned int CCObject::getLuaRef()
{
	if (_luaRef == 0)
	{
		if (g_availableLuaIds.empty())
		{
			_luaRef = ++g_maxLuaCount;
		}
		else
		{
			_luaRef = g_availableLuaIds.top();
			g_availableLuaIds.pop();
		}
	}
	return _luaRef;
}

void CCWeak::release()
{
	--_refCount;
	if (_refCount == 0)
	{
		delete this;
	}
}

void CCWeak::retain()
{
	++_refCount;
}

NS_CC_END
