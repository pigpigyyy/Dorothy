/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2011 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#include "CCMenuItem.h"
#include "support/CCPointExtension.h"
#include "actions/CCActionInterval.h"
#include "sprite_nodes/CCSprite.h"
#include "label_nodes/CCLabelAtlas.h"
#include "label_nodes/CCLabelTTF.h"
#include "script_support/CCScriptSupport.h"
#include <stdarg.h>
#include <cstring>

NS_CC_BEGIN

//
// CCMenuItem
//

CCMenuItem* CCMenuItem::create()
{
    return CCMenuItem::create(NULL, NULL);
}

CCMenuItem* CCMenuItem::create(CCObject *rec, SEL_MenuHandler selector)
{
    CCMenuItem *pRet = new CCMenuItem();
    pRet->initWithTarget(rec, selector);
    pRet->autorelease();
    return pRet;
}

bool CCMenuItem::initWithTarget(CCObject *rec, SEL_MenuHandler selector)
{
    setAnchorPoint(ccp(0.5f, 0.5f));
    m_pListener = rec;
    m_pfnSelector = selector;
    m_bEnabled = true;
    m_bSelected = false;
    return true;
}

CCMenuItem::~CCMenuItem()
{
    unregisterScriptTapHandler();
}

void CCMenuItem::selected()
{
	m_bSelected = true;
	CCScriptEngine::sharedEngine()->executeMenuItemEvent(CCMenuItem::TapBegan, this);
}

void CCMenuItem::unselected()
{
	m_bSelected = false;
	CCScriptEngine::sharedEngine()->executeMenuItemEvent(CCMenuItem::TapEnded, this);
}

void CCMenuItem::registerScriptTapHandler(int nHandler)
{
    unregisterScriptTapHandler();
    m_nScriptTapHandler = nHandler;
    LUALOG("[LUA] Add CCMenuItem script handler: %d", m_nScriptTapHandler);
}

void CCMenuItem::unregisterScriptTapHandler()
{
    if (m_nScriptTapHandler)
    {
        CCScriptEngine::sharedEngine()->removeScriptHandler(m_nScriptTapHandler);
        LUALOG("[LUA] Remove CCMenuItem script handler: %d", m_nScriptTapHandler);
        m_nScriptTapHandler = 0;
    }
}

void CCMenuItem::activate()
{
    if (m_bEnabled)
    {
        if (m_pListener && m_pfnSelector)
        {
            (m_pListener->*m_pfnSelector)(this);
        }
		CCScriptEngine::sharedEngine()->executeMenuItemEvent(CCMenuItem::Tapped, this);
    }
}

void CCMenuItem::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
}

bool CCMenuItem::isEnabled()
{
    return m_bEnabled;
}

CCRect CCMenuItem::rect()
{
    return CCRectMake( m_obPosition.x - m_obContentSize.width * m_obAnchorPoint.x,
                      m_obPosition.y - m_obContentSize.height * m_obAnchorPoint.y,
                      m_obContentSize.width, m_obContentSize.height);
}

bool CCMenuItem::isSelected()
{
    return m_bSelected;
}

void CCMenuItem::setTarget(CCObject *rec, SEL_MenuHandler selector)
{
    m_pListener = rec;
    m_pfnSelector = selector;
}

NS_CC_END
