/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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
#include "CCMenu.h"
#include "basics/CCDirector.h"
#include "CCApplication.h"
#include "support/CCPointExtension.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "touch_dispatcher/CCTouch.h"
#include "CCStdC.h"
#include "cocoa/CCInteger.h"

#include <vector>
#include <stdarg.h>

using namespace std;

NS_CC_BEGIN

//
//CCMenu
//

CCMenu* CCMenu::create()
{
	return CCMenu::createWithArray(nullptr);
}

CCMenu* CCMenu::create(CCMenuItem* item, ...)
{
	va_list args;
	va_start(args, item);
	CCArray* pArray = nullptr;
	if (item)
	{
		pArray = CCArray::create(item, nullptr);
		CCMenuItem *i = va_arg(args, CCMenuItem*);
		while (i)
		{
			pArray->addObject(i);
			i = va_arg(args, CCMenuItem*);
		}
	}
	va_end(args);
	return CCMenu::createWithArray(pArray);
}

CCMenu* CCMenu::createWithArray(CCArray* pArrayOfItems)
{
	CCMenu* pRet = new CCMenu();
	if (pRet && pRet->initWithArray(pArrayOfItems))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

CCMenu* CCMenu::createWithItem(CCMenuItem* item)
{
	return CCMenu::createWithArray(CCArray::create(item, nullptr));
}

bool CCMenu::init()
{
	return initWithArray(NULL);
}

bool CCMenu::initWithArray(CCArray* pArrayOfItems)
{
	if (CCLayer::init())
	{
		setTouchPriority(kCCMenuHandlerPriority);
		setTouchEnabled(true);

		m_bEnabled = true;
		// menu in the center of the screen
		CCSize s = CCDirector::sharedDirector()->getWinSize();

		this->setAnchorPoint(ccp(0.5f, 0.5f));
		this->setContentSize(s);

		if (pArrayOfItems != NULL)
		{
			int z = 0;
			CCObject* pObj = NULL;
			CCARRAY_FOREACH(pArrayOfItems, pObj)
			{
				CCMenuItem* item = (CCMenuItem*)pObj;
				this->addChild(item, z);
				z++;
			}
		}

		//    [self alignItemsVertically];
		m_pSelectedItem = NULL;
		m_eState = kCCMenuStateWaiting;
		return true;
	}
	return false;
}

void CCMenu::onExit()
{
	if (m_eState == kCCMenuStateTrackingTouch)
	{
		if (m_pSelectedItem)
		{
			m_pSelectedItem->unselected();
			m_pSelectedItem = NULL;
		}

		m_eState = kCCMenuStateWaiting;
	}

	CCLayer::onExit();
}

void CCMenu::removeChild(CCNode* child, bool cleanup)
{
	CCMenuItem* pMenuItem = dynamic_cast<CCMenuItem*>(child);

	if (pMenuItem && m_pSelectedItem == pMenuItem)
	{
		m_pSelectedItem = NULL;
	}

	CCNode::removeChild(child, cleanup);
}

void CCMenu::moveAndCullItems(const CCPoint& delta)
{
	CCRect contentRect(CCPoint::zero, getContentSize());
	CCObject* child;
	CCARRAY_FOREACH(m_pChildren, child)
	{
		CCNode* item = (CCNode*)child;
		item->setPosition(ccpAdd(item->getPosition(), delta));
		const CCPoint& pos = item->getPosition();
		const CCSize& size = item->getContentSize();
		const CCPoint& anchor = item->getAnchorPoint();
		CCRect itemRect(
			pos.x - size.width * anchor.x,
			pos.y - size.height * anchor.y,
			size.width,
			size.height);
		if (itemRect.size != CCSize::zero)
		{
			item->setVisible(contentRect.intersectsRect(itemRect));
		}
	}
}

//Menu - Events
void CCMenu::registerWithTouchDispatcher()
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	if (m_bMultiTouches)
	{
		pDispatcher->addStandardDelegate(this, m_nTouchPriority);
	}
	else
	{
		pDispatcher->addTargetedDelegate(this, m_nTouchPriority, true);
	}
}

bool CCMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	if (m_eState != kCCMenuStateWaiting || !m_bVisible || !m_bEnabled)
	{
		return false;
	}

	for (CCNode* c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}

	m_pSelectedItem = this->itemForTouch(touch);
	if (m_pSelectedItem)
	{
		m_eState = kCCMenuStateTrackingTouch;
		m_pSelectedItem->selected();
		return true;
	}
	if (m_bSwallowTouches && CCRect(CCPoint::zero, this->getContentSize()).containsPoint(this->convertToNodeSpace(touch->getLocation())))
	{
		m_eState = kCCMenuStateTrackingTouch;
		return true;
	}
	return false;
}

void CCMenu::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
	if (!m_bEnabled)
	{
		if (m_pSelectedItem)
		{
			m_pSelectedItem->unselected();
		}
		m_eState = kCCMenuStateWaiting;
		return;
	}
	if (m_pSelectedItem)
	{
		CCMenuItem* selectedItem = m_pSelectedItem;
		selectedItem->activate();
		selectedItem->unselected();
	}
	m_eState = kCCMenuStateWaiting;
}

void CCMenu::ccTouchCancelled(CCTouch *touch, CCEvent* event)
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchCancelled] -- invalid state");
	if (m_pSelectedItem)
	{
		m_pSelectedItem->unselected();
	}
	m_eState = kCCMenuStateWaiting;
}

void CCMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
	CCMenuItem *currentItem = this->itemForTouch(touch);
	if (!m_bEnabled)
	{
		if (currentItem && currentItem == m_pSelectedItem)
		{
			m_pSelectedItem->unselected();
			m_pSelectedItem = NULL;
		}
		return;
	}
	if (currentItem != m_pSelectedItem)
	{
		if (m_pSelectedItem)
		{
			m_pSelectedItem->unselected();
		}
		m_pSelectedItem = currentItem;
		if (m_pSelectedItem)
		{
			m_pSelectedItem->selected();
		}
	}
}

//Menu - Alignment

CCSize CCMenu::alignItemsVerticallyWithPadding(float padding)
{
	float width = getContentSize().width;
	float y = getContentSize().height - padding;
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = (CCNode*)pObject;
			float realWidth = pChild->getContentSize().width * pChild->getScaleX();
			float realHeight = pChild->getContentSize().height * pChild->getScaleY();
			if (realWidth == 0.0f || realHeight == 0.0f) continue;
			float realPosY = (1.0f - pChild->getAnchorPoint().y) * realHeight;
			y -= realPosY;
			pChild->setPositionX(width*0.5f - (0.5f - pChild->getAnchorPoint().x) * realWidth);
			pChild->setPositionY(y);
			y -= pChild->getAnchorPoint().y * realHeight;
			y -= padding;
		}
		return CCSize(getWidth(),getContentSize().height - y);
	}
	return CCSize::zero;
}

CCSize CCMenu::alignItemsHorizontallyWithPadding(float padding)
{
	float height = getContentSize().height;
	float x = padding;
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = (CCNode*)pObject;
			float realWidth = pChild->getContentSize().width * pChild->getScaleX();
			float realHeight = pChild->getContentSize().height * pChild->getScaleY();
			if (realWidth == 0.0f || realHeight == 0.0f) continue;
			float realPosX = pChild->getAnchorPoint().x * realWidth;
			x += realPosX;
			pChild->setPositionX(x);
			pChild->setPositionY(height*0.5f - (0.5f - pChild->getAnchorPoint().y) * realHeight);
			x += (1.0f - pChild->getAnchorPoint().x) * realWidth;
			x += padding;
		}
		return CCSize(x, getHeight());
	}
	return CCSize::zero;
}

CCSize CCMenu::alignItemsWithPadding(float padding)
{
	float height = getContentSize().height;
	float width = getContentSize().width;
	float x = padding;
	float y = getContentSize().height - padding;
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		int rows = 0;
		float curY = y;
		float maxX = 0;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = (CCNode*)pObject;

			float realWidth = pChild->getContentSize().width * pChild->getScaleX();
			float realHeight = pChild->getContentSize().height * pChild->getScaleY();

			if (realWidth == 0.0f || realHeight == 0.0f) continue;

			if (x + realWidth + padding > width)
			{
				x = padding;
				rows++;
				y = curY - padding;
			}
			float realPosX = pChild->getAnchorPoint().x * realWidth;
			x += realPosX;

			float realPosY = (1.0f - pChild->getAnchorPoint().y) * realHeight;

			pChild->setPositionX(x);
			pChild->setPositionY(y - realPosY);

			x += (1.0f - pChild->getAnchorPoint().x) * realWidth;
			x += padding;
			
			maxX = MAX(maxX, x);

			if (curY > y - realHeight)
			{
				curY = y - realHeight;
			}
		}
		return CCSize(maxX, height - curY + 10);
	}
	return CCSize::zero;
}

static CCMenuItem* getTouchedItem(CCMenuItem* parentItem, const CCPoint& loc)
{
	CCArray* children = parentItem->getChildren();
	if (children && children->count() > 0)
	{
		for (int i = (int)children->count() - 1; i >= 0; i--)
		{
			CCMenuItem* childItem = dynamic_cast<CCMenuItem*>(children->objectAtIndex(i));
			if (childItem && childItem->isVisible() && childItem->isEnabled())
			{
				CCPoint local = childItem->convertToNodeSpace(loc);
				if (CCRect(CCPoint::zero, childItem->getContentSize()).containsPoint(local))
				{
					CCMenuItem* targetItem = getTouchedItem(childItem, loc);
					return targetItem ? targetItem : childItem;
				}
			}
		}
	}
	return parentItem;
}

CCMenuItem* CCMenu::itemForTouch(CCTouch* touch)
{
	CCPoint touchLocation = touch->getLocation();
	if (this->getContentSize() != CCSize::zero)
	{
		CCPoint loc = this->convertToNodeSpace(touchLocation);
		if (!CCRect(CCPoint::zero, this->getContentSize()).containsPoint(loc))
		{
			return NULL;
		}
	}
	if (m_pChildren && m_pChildren->count() > 0)
	{
		for (int i = (int)m_pChildren->count() - 1; i >= 0; i--)
		{
			CCMenuItem* childItem = dynamic_cast<CCMenuItem*>(m_pChildren->objectAtIndex(i));
			if (childItem && childItem->isVisible() && childItem->isEnabled())
			{
				CCPoint local = childItem->convertToNodeSpace(touchLocation);
				if (CCRect(CCPoint::zero, childItem->getContentSize()).containsPoint(local))
				{
					return getTouchedItem(childItem, touchLocation);
				}
			}
		}
	}
	return NULL;
}

NS_CC_END
