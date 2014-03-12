/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

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

#include "CCLuaEngine.h"
#include "cocos2d.h"
#include "cocoa/CCArray.h"
#include "CCScheduler.h"

NS_CC_BEGIN

CCLuaEngine* CCLuaEngine::defaultEngine(void)
{
	static CCLuaEngine engine;
    return &engine;
}

CCLuaEngine::~CCLuaEngine(void)
{
    CC_SAFE_RELEASE(m_stack);
}

void CCLuaEngine::addSearchPath(const char* path)
{
    m_stack->addSearchPath(path);
}

void CCLuaEngine::addLuaLoader(lua_CFunction func)
{
    m_stack->addLuaLoader(func);
}

void CCLuaEngine::removeScriptObjectByCCObject(CCObject* pObj)
{
    m_stack->removeScriptObjectByCCObject(pObj);
}

void CCLuaEngine::removeScriptHandler(int nHandler)
{
    m_stack->removeScriptHandler(nHandler);
}

int CCLuaEngine::executeString(const char *codes)
{
    int ret = m_stack->executeString(codes);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeScriptFile(const char* filename)
{
    int ret = m_stack->executeScriptFile(filename);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeGlobalFunction(const char* functionName)
{
    int ret = m_stack->executeGlobalFunction(functionName);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeFunction( int nHandler, int paramCount, CCObject* params[], char* paramNames[] )
{
	for (int i = 0; i < paramCount; i++)
	{
		m_stack->pushCCObject(params[i], paramNames[i]);
	}
	int ret = m_stack->executeFunctionByHandler(nHandler, paramCount);
	m_stack->clean();
	return ret;
}

int CCLuaEngine::executeFunction( int nHandler, int paramCount, void* params[], char* paramNames[] )
{
	for (int i = 0; i < paramCount; i++)
	{
		m_stack->pushUserType(params[i], paramNames[i]);
	}
	int ret = m_stack->executeFunctionByHandler(nHandler, paramCount);
	m_stack->clean();
	return ret;
}

int CCLuaEngine::executeFunction( int nHandler )
{
	int ret = m_stack->executeFunctionByHandler(nHandler, 0);
	m_stack->clean();
	return ret;
}

int CCLuaEngine::executeActionUpdate( int nHandler, void* param, char* paramName, float deltaTime )
{
	if (!nHandler) return 0;
	m_stack->pushUserType(param, paramName);
	m_stack->pushFloat(deltaTime);
	int ret = m_stack->executeFunctionByHandler(nHandler, 2);
	m_stack->clean();
	return ret;
}

int CCLuaEngine::executeNodeEvent(CCNode* pNode, int nAction)
{
    int nHandler = pNode->getScriptHandler();
    if (!nHandler) return 0;
	m_stack->pushInt(nAction);
    int ret = m_stack->executeFunctionByHandler(nHandler, 1);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeMenuItemEvent(int eventType, CCMenuItem* pMenuItem)
{
    int nHandler = pMenuItem->getScriptTapHandler();
	if (!nHandler) return 0;
	m_stack->pushInt(eventType);
    m_stack->pushCCObject(pMenuItem, "CCMenuItem");
    int ret = m_stack->executeFunctionByHandler(nHandler, 2);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeCallFuncActionEvent(CCCallFunc* pAction, CCObject* pTarget/* = NULL*/)
{
    int nHandler = pAction->getScriptHandler();
    if (!nHandler) return 0;
    
    if (pTarget)
    {
        m_stack->pushCCObject(pTarget, "CCNode");
    }
    int ret = m_stack->executeFunctionByHandler(nHandler, pTarget ? 1 : 0);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeSchedule(int nHandler, float dt, CCNode* pNode/* = NULL*/)
{
    if (!nHandler) return 0;
    m_stack->pushFloat(dt);
    int ret = m_stack->executeFunctionByHandler(nHandler, 1);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeLayerTouchEvent(CCLayer* pLayer, int eventType, CCTouch *pTouch)
{
    CCTouchScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptTouchHandlerEntry();
    if (!pScriptHandlerEntry) return 0;
    int nHandler = pScriptHandlerEntry->getHandler();
	if (!nHandler) return 0;
	m_stack->pushInt(eventType);
	m_stack->pushCCObject(pTouch, "CCTouch");
    int ret = m_stack->executeFunctionByHandler(nHandler, 2);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeLayerTouchesEvent(CCLayer* pLayer, int eventType, CCSet *pTouches)
{
    CCTouchScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptTouchHandlerEntry();
    if (!pScriptHandlerEntry) return 0;
    int nHandler = pScriptHandlerEntry->getHandler();
	if (!nHandler) return 0;
	m_stack->pushInt(eventType);
    CCDirector* pDirector = CCDirector::sharedDirector();
    lua_State *L = m_stack->getLuaState();
    lua_newtable(L);
    int i = 1;
    for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
    {
		CCTouch* pTouch = (CCTouch*)*it;
		m_stack->pushCCObject(pTouch, "CCTouch");
        lua_rawseti(L, -2, i++);
    }
    int ret = m_stack->executeFunctionByHandler(nHandler, 2);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeLayerKeypadEvent(CCLayer* pLayer, int eventType)
{
    CCScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptKeypadHandlerEntry();
    if (!pScriptHandlerEntry)
        return 0;
    int nHandler = pScriptHandlerEntry->getHandler();
    if (!nHandler) return 0;
	m_stack->pushInt(eventType);
    int ret = m_stack->executeFunctionByHandler(nHandler, 1);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeAccelerometerEvent(CCLayer* pLayer, CCAcceleration* pAccelerationValue)
{
    CCScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptAccelerateHandlerEntry();
    if (!pScriptHandlerEntry)
        return 0;
    int nHandler = pScriptHandlerEntry->getHandler();
    if (!nHandler) return 0;
    
    m_stack->pushFloat(pAccelerationValue->x);
    m_stack->pushFloat(pAccelerationValue->y);
    m_stack->pushFloat(pAccelerationValue->z);
    m_stack->pushFloat(pAccelerationValue->timestamp);
    int ret = m_stack->executeFunctionByHandler(nHandler, 4);
    m_stack->clean();
    return ret;
}

int CCLuaEngine::executeEvent(int nHandler, const char* pEventName, CCObject* pEventSource /* = NULL*/, const char* pEventSourceClassName /* = NULL*/)
{
    m_stack->pushString(pEventName);
    if (pEventSource)
    {
        m_stack->pushCCObject(pEventSource, pEventSourceClassName ? pEventSourceClassName : "CCObject");
    }
    int ret = m_stack->executeFunctionByHandler(nHandler, pEventSource ? 2 : 1);
    m_stack->clean();
    return ret;
}

bool CCLuaEngine::executeAssert(bool cond, const char *msg/* = NULL */)
{
    bool ret = m_stack->executeAssert(cond, msg);
    m_stack->clean();
    return ret;
}

bool CCLuaEngine::scriptHandlerEqual( int nHandlerA, int nHandlerB )
{
	return m_stack->functionEqual(nHandlerA, nHandlerB);
}

CCLuaEngine::CCLuaEngine():
m_stack(CCLuaStack::create())
{
	m_stack->retain();
}

NS_CC_END
