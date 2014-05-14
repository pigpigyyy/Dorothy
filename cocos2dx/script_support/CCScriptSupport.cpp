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

#include "CCScriptSupport.h"
#include "CCScheduler.h"

void CC_DLL cc_assert_script_compatible(bool cond, const char *msg)
{
    cocos2d::CCScriptEngine* pEngine = cocos2d::CCScriptEngine::sharedEngine();
    if (!cond && pEngine && pEngine->executeAssert(cond, msg))
    {
        return;
    }
}

NS_CC_BEGIN

// #pragma mark -
// #pragma mark CCScriptHandlerEntry

CCScriptHandlerEntry* CCScriptHandlerEntry::create(int nHandler)
{
    CCScriptHandlerEntry* entry = new CCScriptHandlerEntry(nHandler);
    entry->autorelease();
    return entry;
}

CCScriptHandlerEntry::~CCScriptHandlerEntry()
{
    CCScriptEngine::sharedEngine()->removeScriptHandler(m_nHandler);
}

CCScriptHandlerEntry::CCScriptHandlerEntry( int nHandler )
	: m_nHandler(nHandler)
{ }

int CCScriptHandlerEntry::getHandler()
{
	return m_nHandler;
}

// #pragma mark -
// #pragma mark CCSchedulerScriptHandlerEntry

CCSchedulerScriptHandlerEntry* CCSchedulerScriptHandlerEntry::create(int nHandler, float fInterval, bool bPaused)
{
    CCSchedulerScriptHandlerEntry* pEntry = new CCSchedulerScriptHandlerEntry(nHandler);
    pEntry->init(fInterval, bPaused);
    pEntry->autorelease();
    return pEntry;
}

bool CCSchedulerScriptHandlerEntry::init(float fInterval, bool bPaused)
{
    m_pTimer = new CCTimer();
    m_pTimer->initWithScriptHandler(m_nHandler, fInterval);
    m_pTimer->autorelease();
    m_pTimer->retain();
    m_bPaused = bPaused;
    LUALOG("[LUA] ADD script schedule: %d, entryID: %d", m_nHandler, m_nEntryId);
    return true;
}

void CCSchedulerScriptHandlerEntry::markedForDeletion()
{
	m_bMarkedForDeletion = true;
}

CCSchedulerScriptHandlerEntry::CCSchedulerScriptHandlerEntry( int nHandler )
	: CCScriptHandlerEntry(nHandler)
	, m_pTimer(NULL)
	, m_bPaused(false)
	, m_bMarkedForDeletion(false)
{ }

CCSchedulerScriptHandlerEntry::~CCSchedulerScriptHandlerEntry()
{
	LUALOG("[LUA] REMOVE scheduler script handler: %d", m_nHandler);
}

CCTimer* CCSchedulerScriptHandlerEntry::getTimer()
{
	return m_pTimer;
}

bool CCSchedulerScriptHandlerEntry::isPaused()
{
	return m_bPaused;
}

bool CCSchedulerScriptHandlerEntry::isMarkedForDeletion()
{
	return m_bMarkedForDeletion;
}

// #pragma mark -
// #pragma mark CCTouchScriptHandlerEntry

CCTouchScriptHandlerEntry* CCTouchScriptHandlerEntry::create(int nHandler,
                                                             bool bIsMultiTouches,
                                                             int nPriority,
                                                             bool bSwallowsTouches)
{
    CCTouchScriptHandlerEntry* pEntry = new CCTouchScriptHandlerEntry(nHandler);
    pEntry->init(bIsMultiTouches, nPriority, bSwallowsTouches);
    pEntry->autorelease();
    return pEntry;
}

bool CCTouchScriptHandlerEntry::init(bool bIsMultiTouches, int nPriority, bool bSwallowsTouches)
{
    m_bIsMultiTouches = bIsMultiTouches;
    m_nPriority = nPriority;
    m_bSwallowsTouches = bSwallowsTouches;
    return true;
}

CCTouchScriptHandlerEntry::CCTouchScriptHandlerEntry( int nHandler )
	: CCScriptHandlerEntry(nHandler)
	, m_bIsMultiTouches(false)
	, m_nPriority(0)
	, m_bSwallowsTouches(false)
{ }

CCTouchScriptHandlerEntry::~CCTouchScriptHandlerEntry()
{
	LUALOG("[LUA] REMOVE touch script handler: %d", m_nHandler);
}

bool CCTouchScriptHandlerEntry::isMultiTouches()
{
	return m_bIsMultiTouches;
}

int CCTouchScriptHandlerEntry::getPriority()
{
	return m_nPriority;
}

bool CCTouchScriptHandlerEntry::getSwallowsTouches()
{
	return m_bSwallowsTouches;
}

CCScriptEngine CCScriptEngine::_none;

CCScriptEngine* CCScriptEngine::_engine = &CCScriptEngine::_none;

CCScriptEngine::~CCScriptEngine()
{ }

ccScriptType CCScriptEngine::getScriptType()
{
	return kScriptTypeNone;
}

void CCScriptEngine::setEngine( CCScriptEngine* engine )
{
	_engine = engine ? engine : &CCScriptEngine::_none;
}

CCScriptEngine* CCScriptEngine::sharedEngine()
{
	return _engine;
}

bool CCScriptEngine::executeAssert( bool cond, const char *msg ){return true;}
int CCScriptEngine::executeEvent( int nHandler, const char* pEventName, CCObject* pEventSource, const char* pEventSourceClassName ){return 0;}
int CCScriptEngine::executeAccelerometerEvent( CCLayer* pLayer, CCAcceleration* pAccelerationValue ){return 0;}
int CCScriptEngine::executeLayerKeypadEvent( CCLayer* pLayer, int eventType ){return 0;}
int CCScriptEngine::executeLayerTouchEvent( CCLayer* pLayer, int eventType, CCTouch *pTouch ){return 0;}
int CCScriptEngine::executeLayerTouchesEvent( CCLayer* pLayer, int eventType, CCSet *pTouches ){return 0;}
int CCScriptEngine::executeSchedule( int nHandler, float dt, CCNode* pNode ){return 0;}
int CCScriptEngine::executeNotificationEvent( CCNotificationCenter* pNotificationCenter, const char* pszName ){return 0;}
int CCScriptEngine::executeMenuItemEvent( int eventType, CCMenuItem* pMenuItem ){return 0;}
int CCScriptEngine::executeNodeEvent( CCNode* pNode, int nAction ){return 0;}
int CCScriptEngine::executeFunction( int nHandler, int paramCount, CCObject* params[] ){return 0;}
int CCScriptEngine::executeFunction( int nHandler, int paramCount, void* params[], char* paramNames[] ){return 0;}
int CCScriptEngine::executeFunction( int nHandler ){return 0;}
int CCScriptEngine::executeGlobalFunction( const char* functionName ){return 0;}
int CCScriptEngine::executeScriptFile( const char* filename ){return 0;}
int CCScriptEngine::executeString( const char* codes ){return 0;}
void CCScriptEngine::removeScriptHandler( int nHandler ){}
bool CCScriptEngine::scriptHandlerEqual( int nHandlerA, int nHandlerB ){return false;}
int CCScriptEngine::executeActionUpdate( int nHandler, void* param, char* paramName, float deltaTime ){return 0;}

NS_CC_END
