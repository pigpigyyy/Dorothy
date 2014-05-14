/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 
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

#ifndef __SCRIPT_SUPPORT_H__
#define __SCRIPT_SUPPORT_H__

#include "platform/CCCommon.h"
#include "CCAccelerometer.h"
#include "touch_dispatcher/CCTouch.h"
#include "cocoa/CCSet.h"
#include "CCAccelerometer.h"
#include <map>
#include <string>
#include <list>

typedef struct lua_State lua_State;

NS_CC_BEGIN

class CCTimer;
class CCLayer;
class CCMenuItem;
class CCNotificationCenter;
class CCCallFunc;
class CCAcceleration;

enum ccScriptType
{
    kScriptTypeNone = 0,
    kScriptTypeLua
};

class CC_DLL CCScriptHandlerEntry : public CCObject
{
public:
    virtual ~CCScriptHandlerEntry();
	int getHandler();
	static CCScriptHandlerEntry* create(int nHandler);
protected:
    CCScriptHandlerEntry(int nHandler);
    int m_nHandler;
};

/**
 * @addtogroup script_support
 * @{
 */

class CC_DLL CCSchedulerScriptHandlerEntry: public CCScriptHandlerEntry
{
public:
    // nHandler return by tolua_ref_function(), called from LuaCocos2d.cpp
	static CCSchedulerScriptHandlerEntry* create(int nHandler, float fInterval, bool bPaused);
	virtual ~CCSchedulerScriptHandlerEntry();
    CCTimer* getTimer();
    bool isPaused();
    void markedForDeletion();
    bool isMarkedForDeletion();
private:
    CCSchedulerScriptHandlerEntry(int nHandler);
    bool init(float fInterval, bool bPaused);
    CCTimer* m_pTimer;
    bool m_bPaused;
    bool m_bMarkedForDeletion;
};

class CC_DLL CCTouchScriptHandlerEntry: public CCScriptHandlerEntry
{
public:
    static CCTouchScriptHandlerEntry* create(int nHandler, bool bIsMultiTouches, int nPriority, bool bSwallowsTouches);
	virtual ~CCTouchScriptHandlerEntry();
    bool isMultiTouches();
    int getPriority();
    bool getSwallowsTouches();
private:
    CCTouchScriptHandlerEntry(int nHandler);
    bool init(bool bIsMultiTouches, int nPriority, bool bSwallowsTouches);
    bool m_bIsMultiTouches;
    int m_nPriority;
    bool m_bSwallowsTouches;
};

// Don't make CCScriptEngineProtocol inherits from CCObject since setScriptEngine is invoked only once in AppDelegate.cpp,
// It will affect the lifecycle of ScriptCore instance, the autorelease pool will be destroyed before destructing ScriptCore.
// So a crash will appear on Win32 if you click the close button.
class CC_DLL CCScriptEngine
{
public:
    virtual ~CCScriptEngine();

    /** Get script type */
    virtual ccScriptType getScriptType();
    
    /** Remove script function handler, only CCLuaEngine class need to implement this function. */
    virtual void removeScriptHandler(int nHandler);
    
    /**
     @brief Execute script code contained in the given string.
     @param codes holding the valid script code that should be executed.
     @return 0 if the string is executed correctly.
     @return other if the string is executed wrongly.
     */
	virtual int executeString(const char* codes);

    /**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
     */
    virtual int executeScriptFile(const char* filename);
    
    /**
     @brief Execute a scripted global function.
     @brief The function should not take any parameters and should return an integer.
     @param functionName String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
     */
    virtual int executeGlobalFunction(const char* functionName);
    
	virtual int executeFunction(int nHandler, int paramCount, CCObject* params[]);
	virtual int executeFunction(int nHandler, int paramCount, void* params[], char* paramNames[]);
	virtual int executeFunction(int nHandler);

	virtual int executeActionUpdate(int nHandler, void* param, char* paramName, float deltaTime);
    /**
     @brief Execute a node event function
     @param pNode which node produce this event
     @param nAction kCCNodeOnEnter,kCCNodeOnExit,kCCMenuItemActivated,kCCNodeOnEnterTransitionDidFinish,kCCNodeOnExitTransitionDidStart
     @return The integer value returned from the script function.
     */
    virtual int executeNodeEvent(CCNode* pNode, int nAction);
    
    virtual int executeMenuItemEvent(int eventType, CCMenuItem* pMenuItem);
    /** Execute a notification event function */
    virtual int executeNotificationEvent(CCNotificationCenter* pNotificationCenter, const char* pszName);
    
    /** execute a schedule function */
    virtual int executeSchedule(int nHandler, float dt, CCNode* pNode = NULL);
    
    /** functions for executing touch event */
    virtual int executeLayerTouchesEvent(CCLayer* pLayer, int eventType, CCSet *pTouches);
    virtual int executeLayerTouchEvent(CCLayer* pLayer, int eventType, CCTouch *pTouch);

    /** functions for keypad event */
    virtual int executeLayerKeypadEvent(CCLayer* pLayer, int eventType);

    /** execute a accelerometer event */
    virtual int executeAccelerometerEvent(CCLayer* pLayer, CCAcceleration* pAccelerationValue);

    /** function for common event */
    virtual int executeEvent(int nHandler, const char* pEventName, CCObject* pEventSource = NULL, const char* pEventSourceClassName = NULL);
    /** function for assert test */
    virtual bool executeAssert(bool cond, const char *msg = NULL);

	virtual bool scriptHandlerEqual(int nHandlerA, int nHandlerB);
	static void setEngine(CCScriptEngine* engine);
	static CCScriptEngine* sharedEngine();
private:
	static CCScriptEngine _none;
	static CCScriptEngine* _engine;
};

// end of script_support group
/// @}

NS_CC_END

#endif // __SCRIPT_SUPPORT_H__
