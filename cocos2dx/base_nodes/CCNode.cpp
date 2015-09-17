/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Valentin Milea
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
#include "cocoa/CCString.h"
#include "CCNode.h"
#include "support/CCPointExtension.h"
#include "support/TransformUtils.h"
#include "basics/CCCamera.h"
#include "effects/CCGrid.h"
#include "basics/CCDirector.h"
#include "basics/CCScheduler.h"
#include "touch_dispatcher/CCTouch.h"
#include "actions/CCActionManager.h"
#include "script_support/CCScriptSupport.h"
#include "shaders/CCGLProgram.h"
// externals
#include "kazmath/GL/matrix.h"


#if CC_NODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL (__ARGS__) (ceil(__ARGS__))
#endif

NS_CC_BEGIN

CCNode::CCNode()
: m_fRotation(0.0f)
, m_fScaleX(1.0f)
, m_fScaleY(1.0f)
, m_fPositionZ(0.0f)
, m_obPosition(CCPoint::zero)
, m_fSkewX(0.0f)
, m_fSkewY(0.0f)
, m_obAnchorPointInPoints(CCPoint::zero)
, m_obAnchorPoint(0.5f,0.5f)
, m_obContentSize(CCSize::zero)
, m_pCamera(NULL)
// children (lazy allocs)
// lazy alloc
, m_pGrid(NULL)
, m_nZOrder(0)
, m_pChildren(NULL)
, m_pParent(NULL)
, m_nTag(0)
, m_pUserObject(NULL)
, m_pUserData(NULL)
, m_pHelperObject(NULL)
, m_pShaderProgram(NULL)
, m_eGLServerState(ccGLServerState(0))
, m_bRunning(false)
, m_bTransformDirty(true)
, m_bInverseDirty(true)
, m_bVisible(true)
, m_bReorderChildDirty(false)
, m_nUpdateScriptHandler(0)
, _displayedOpacity(1.0f)
, _realOpacity(1.0f)
, _displayedColor(ccWHITE)
, _realColor(ccWHITE)
, _cascadeOpacity(true)
, _cascadeColor(true)
, _transformTargetRef(NULL)
, _isScheduled(false)
{
	// set default scheduler and actionManager
	CCDirector* director = CCDirector::sharedDirector();
	m_pScheduler = director->getScheduler();
	m_pScheduler->retain();
}

CCNode::~CCNode()
{
	CCLOGINFO("cocos2d: deallocing");

	// callbacks
	if (m_nUpdateScriptHandler)
	{
		CCScriptEngine::sharedEngine()->removeScriptHandler(m_nUpdateScriptHandler);
	}

	// attributes
	CC_SAFE_RELEASE(m_pScheduler);
	CC_SAFE_RELEASE(m_pCamera);
	CC_SAFE_RELEASE(m_pGrid);
	CC_SAFE_RELEASE(m_pShaderProgram);
	CC_SAFE_RELEASE(m_pUserObject);
	CC_SAFE_RELEASE(m_pHelperObject);
	CC_SAFE_RELEASE(_transformTargetRef);
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* child;
		CCARRAY_FOREACH(m_pChildren, child)
		{
			CCNode* pChild = (CCNode*)child;
			if (pChild)
			{
				pChild->m_pParent = NULL;
			}
		}
	}

	// children
	CC_SAFE_RELEASE(m_pChildren);
}

float CCNode::getSkewX()
{
	return m_fSkewX;
}

void CCNode::setSkewX(float newSkewX)
{
	m_fSkewX = newSkewX;
	m_bTransformDirty = m_bInverseDirty = true;
}

float CCNode::getSkewY()
{
	return m_fSkewY;
}

void CCNode::setSkewY(float newSkewY)
{
	m_fSkewY = newSkewY;

	m_bTransformDirty = m_bInverseDirty = true;
}

/// zOrder getter
int CCNode::getZOrder()
{
	return m_nZOrder;
}

void CCNode::setZOrder(int z)
{
	if (m_pParent)
	{
		m_pParent->reorderChild(this, z);
	}
	m_nZOrder = z;
}

void CCNode::setZOrderValue(int zOrder)
{
	m_nZOrder = zOrder;
}

/// vertexZ getter
float CCNode::getPositionZ()
{
	return m_fPositionZ;
}

/// vertexZ setter
void CCNode::setPositionZ(float var)
{
	m_fPositionZ = var;
}

/// rotation getter
float CCNode::getRotation()
{
	return m_fRotation;
}

/// rotation setter
void CCNode::setRotation(float newRotation)
{
	m_fRotation = newRotation;
	m_bTransformDirty = m_bInverseDirty = true;
}

/// scale setter
void CCNode::setScale(float scale)
{
	m_fScaleX = m_fScaleY = scale;
	m_bTransformDirty = m_bInverseDirty = true;
}

/// scaleX getter
float CCNode::getScaleX()
{
	return m_fScaleX;
}

/// scaleX setter
void CCNode::setScaleX(float newScaleX)
{
	m_fScaleX = newScaleX;
	m_bTransformDirty = m_bInverseDirty = true;
}

/// scaleY getter
float CCNode::getScaleY()
{
	return m_fScaleY;
}

/// scaleY setter
void CCNode::setScaleY(float newScaleY)
{
	m_fScaleY = newScaleY;
	m_bTransformDirty = m_bInverseDirty = true;
}

/// position getter
const CCPoint& CCNode::getPosition()
{
	return m_obPosition;
}

/// position setter
void CCNode::setPosition(const CCPoint& newPosition)
{
	m_obPosition = newPosition;
	m_bTransformDirty = m_bInverseDirty = true;
}

void CCNode::getPosition(float* x, float* y)
{
	*x = m_obPosition.x;
	*y = m_obPosition.y;
}

void CCNode::setPosition(float x, float y)
{
	setPosition(ccp(x, y));
}

float CCNode::getPositionX()
{
	return getPosition().x;
}

float CCNode::getPositionY()
{
	return  getPosition().y;
}

void CCNode::setPositionX(float x)
{
	const CCPoint& pos = getPosition();
	setPosition(ccp(x, pos.y));
}

void CCNode::setPositionY(float y)
{
	const CCPoint& pos = getPosition();
	setPosition(ccp(pos.x, y));
}

/// children getter
CCArray* CCNode::getChildren()
{
	return m_pChildren;
}

unsigned int CCNode::getChildrenCount()
{
	return m_pChildren ? m_pChildren->count() : 0;
}

/// camera getter: lazy alloc
CCCamera* CCNode::getCamera()
{
	if (!m_pCamera)
	{
		m_pCamera = new CCCamera();
	}

	return m_pCamera;
}

/// grid getter
CCGridBase* CCNode::getGrid()
{
	return m_pGrid;
}

/// grid setter
void CCNode::setGrid(CCGridBase* pGrid)
{
	CC_SAFE_RETAIN(pGrid);
	CC_SAFE_RELEASE(m_pGrid);
	m_pGrid = pGrid;
}


/// isVisible getter
bool CCNode::isVisible()
{
	return m_bVisible;
}

/// isVisible setter
void CCNode::setVisible(bool var)
{
	m_bVisible = var;
}

const CCPoint& CCNode::getAnchorPointInPoints()
{
	return m_obAnchorPointInPoints;
}

/// anchorPoint getter
const CCPoint& CCNode::getAnchorPoint()
{
	return m_obAnchorPoint;
}

void CCNode::setAnchorPoint(const CCPoint& point)
{
	if (point != m_obAnchorPoint)
	{
		m_obAnchorPoint = point;
		m_obAnchorPointInPoints = ccp(m_obContentSize.width * m_obAnchorPoint.x, m_obContentSize.height * m_obAnchorPoint.y);
		m_bTransformDirty = m_bInverseDirty = true;
	}
}

/// contentSize getter
const CCSize& CCNode::getContentSize()
{
	return m_obContentSize;
}

void CCNode::setContentSize(const CCSize & size)
{
	if (size != m_obContentSize)
	{
		m_obContentSize = size;

		m_obAnchorPointInPoints = ccp(m_obContentSize.width * m_obAnchorPoint.x, m_obContentSize.height * m_obAnchorPoint.y);
		m_bTransformDirty = m_bInverseDirty = true;
	}
}

void CCNode::setWidth(float w)
{
	setContentSize(CCSize(w, getContentSize().height));
}
float CCNode::getWidth()
{
	return getContentSize().width;
}
void CCNode::setHeight(float h)
{
	setContentSize(CCSize(getContentSize().width, h));
}
float CCNode::getHeight()
{
	return getContentSize().height;
}

// isRunning getter
bool CCNode::isRunning()
{
	return m_bRunning;
}

/// parent getter
CCNode * CCNode::getParent()
{
	return m_pParent;
}
/// parent setter
void CCNode::setParent(CCNode * var)
{
	m_pParent = var;
}

/// tag getter
int CCNode::getTag()
{
	return m_nTag;
}

/// tag setter
void CCNode::setTag(int var)
{
	m_nTag = var;
}

CCGLProgram* CCNode::getShaderProgram()
{
	return m_pShaderProgram;
}

ccGLServerState CCNode::getGLServerState()
{
	return m_eGLServerState;
}

void CCNode::setGLServerState(ccGLServerState glServerState)
{
	m_eGLServerState = glServerState;
}

CCObject* CCNode::getUserObject()
{
	return m_pUserObject;
}

void CCNode::setUserObject(CCObject* pUserObject)
{
	CC_SAFE_RETAIN(pUserObject);
	CC_SAFE_RELEASE(m_pUserObject);
	m_pUserObject = pUserObject;
}

CCObject* CCNode::getHelperObject()
{
	return m_pHelperObject;
}

void CCNode::setHelperObject(CCObject* pHelperObject)
{
	CC_SAFE_RETAIN(pHelperObject);
	CC_SAFE_RELEASE(m_pHelperObject);
	m_pHelperObject = pHelperObject;
}

void CCNode::setShaderProgram(CCGLProgram* pShaderProgram)
{
	CC_SAFE_RETAIN(pShaderProgram);
	CC_SAFE_RELEASE(m_pShaderProgram);
	m_pShaderProgram = pShaderProgram;
}

CCRect CCNode::boundingBox()
{
	CCRect rect(0, 0, m_obContentSize.width, m_obContentSize.height);
	return CCRectApplyAffineTransform(rect, nodeToParentTransform());
}

CCNode* CCNode::create()
{
	CCNode* pRet = new CCNode();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

void CCNode::cleanup()
{
	// trigger event
	CCScriptEngine::sharedEngine()->executeNodeEvent(this, CCNode::Cleanup);

	// clear actions
	CCNode::stopAllActions();
	CCNode::unscheduleAllSelectors();

	// clear lua callbacks
	CCNode::unscheduleUpdateLua();

	// clear user object
	CC_SAFE_RELEASE_NULL(m_pUserObject);
	CC_SAFE_RELEASE_NULL(m_pHelperObject);

	// remove peer data
	CCScriptEngine::sharedEngine()->removePeer(this);

	// cleanup children
	arrayMakeObjectsPerformSelector(m_pChildren, cleanup, CCNode*);
}


const char* CCNode::description()
{
	return CCString::createWithFormat("<CCNode | Tag = %d>", m_nTag)->getCString();
}

// lazy allocs
void CCNode::childrenAlloc()
{
	m_pChildren = CCArray::createWithCapacity(4);
	m_pChildren->retain();
}

CCNode* CCNode::getChildByTag(int aTag)
{
	CCObject* child;
	CCARRAY_FOREACH(m_pChildren, child)
	{
		CCNode* pNode = (CCNode*)child;
		if (pNode && pNode->m_nTag == aTag)
		{
			return pNode;
		}
	}
	return NULL;
}

/* "add" logic MUST only be on this method
* If a class want's to extend the 'addChild' behavior it only needs
* to override this method
*/
void CCNode::addChild(CCNode *child, int zOrder, int tag)
{
	CCAssert(child != NULL, "CCNode add child argument must be non-nil");
	CCAssert(child->m_pParent == NULL, "child already added. It can't be added again");

	if (!m_pChildren)
	{
		this->childrenAlloc();
	}

	this->insertChild(child, zOrder);

	child->m_nTag = tag;

	child->setParent(this);
	child->updateDisplayedColor(this->_displayedColor);
	child->updateDisplayedOpacity(this->_displayedOpacity);

	if (m_bRunning)
	{
		child->onEnter();
		child->onEnterTransitionDidFinish();
	}
}

void CCNode::addChild(CCNode *child, int zOrder)
{
	CCAssert(child != NULL, "CCNode add child argument must be non-nil");
	this->addChild(child, zOrder, child->m_nTag);
}

void CCNode::addChild(CCNode *child)
{
	CCAssert(child != NULL, "CCNode add child argument must be non-nil");
	this->addChild(child, child->m_nZOrder, child->m_nTag);
}

void CCNode::removeFromParent()
{
	this->removeFromParentAndCleanup(true);
}

void CCNode::removeFromParentAndCleanup(bool cleanup)
{
	if (m_pParent != NULL)
	{
		m_pParent->removeChild(this, cleanup);
	}
}

void CCNode::removeChild(CCNode* child)
{
	this->removeChild(child, true);
}

/* "remove" logic MUST only be on this method
* If a class want's to extend the 'removeChild' behavior it only needs
* to override this method
*/
void CCNode::removeChild(CCNode* child, bool cleanup)
{
	// explicit nil handling
	if (m_pChildren == NULL)
	{
		return;
	}

	if (m_pChildren->containsObject(child))
	{
		this->detachChild(child, cleanup);
	}
}

void CCNode::removeChildByTag(int tag)
{
	this->removeChildByTag(tag, true);
}

void CCNode::removeChildByTag(int tag, bool cleanup)
{
	CCNode* child = this->getChildByTag(tag);
	if (child)
	{
		this->removeChild(child, cleanup);
	}
}

void CCNode::removeAllChildren()
{
	this->removeAllChildrenWithCleanup(true);
}

void CCNode::removeAllChildrenWithCleanup(bool cleanup)
{
	// not using detachChild improves speed here
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* child;
		CCARRAY_FOREACH(m_pChildren, child)
		{
			CCNode* pNode = (CCNode*)child;
			if (pNode)
			{
				// IMPORTANT:
				//  -1st do onExit
				//  -2nd cleanup
				if (m_bRunning)
				{
					pNode->onExitTransitionDidStart();
					pNode->onExit();
				}

				if (cleanup)
				{
					pNode->cleanup();
				}
				// set parent nil at the end
				pNode->setParent(NULL);
			}
		}

		m_pChildren->removeAllObjects();
	}

}

void CCNode::detachChild(CCNode *child, bool doCleanup)
{
	// IMPORTANT:
	//  -1st do onExit
	//  -2nd cleanup
	if (m_bRunning)
	{
		child->onExitTransitionDidStart();
		child->onExit();
	}

	// If you don't do cleanup, the child's actions will not get removed and the
	// its scheduledSelectors_ dict will not get released!
	if (doCleanup)
	{
		child->cleanup();
	}

	// set parent nil at the end
	child->setParent(NULL);

	m_pChildren->removeObject(child);
}


// helper used by reorderChild & add
void CCNode::insertChild(CCNode* child, int z)
{
	m_bReorderChildDirty = true;
	ccArrayAppendObjectWithResize(m_pChildren->data, child);
	child->m_nZOrder = z;
}

void CCNode::reorderChild(CCNode *child, int zOrder)
{
	CCAssert(child != NULL, "Child must be non-nil");
	m_bReorderChildDirty = true;
	child->m_nZOrder = zOrder;
}

void CCNode::sortAllChildren()
{
	if (m_bReorderChildDirty)
	{
		int i, j, length = m_pChildren->data->num;
		CCNode ** x = (CCNode**)m_pChildren->data->arr;
		CCNode *tempItem;

		// insertion sort
		for (i = 1; i < length; i++)
		{
			tempItem = x[i];
			j = i - 1;

			//continue moving element downwards while zOrder is smaller or when zOrder is the same but mutatedIndex is smaller
			while (j >= 0 && tempItem->m_nZOrder < x[j]->m_nZOrder)
			{
				x[j + 1] = x[j];
				j = j - 1;
			}
			x[j + 1] = tempItem;
		}

		//don't need to check children recursively, that's done in visit of each child

		m_bReorderChildDirty = false;
	}
}


void CCNode::draw()
{
	//CCAssert(0);
	// override me
	// Only use- this function to draw your stuff.
	// DON'T draw your stuff outside this method
}

void CCNode::visit()
{
	// quick return if not visible. children won't be drawn.
	if (!m_bVisible)
	{
		return;
	}
	kmGLPushMatrix();

	CCNode* transformTarget = CCNode::getTransformTarget();
	if (transformTarget)
	{
		CCDirector::sharedDirector()->projection();
		transformTarget->transformAncestors();
		transformTarget->transform();
	}

	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->beforeDraw();
	}

	this->transform();
	if (m_pChildren && m_pChildren->count() > 0)
	{
		this->sortAllChildren();
		CCObject** arr = m_pChildren->data->arr;
		unsigned int count = m_pChildren->data->num;
		unsigned int i = 0;
		for (; i < count; ++i)
		{
			CCNode* pNode = (CCNode*)arr[i];
			if (pNode && pNode->m_nZOrder < 0)
			{
				pNode->visit();
			}
			else break;
		}
		this->draw();
		for (; i < count; ++i)
		{
			CCNode* pNode = (CCNode*)arr[i];
			if (pNode)
			{
				pNode->visit();
			}
		}
	}
	else this->draw();
	
	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->afterDraw(this);
	}

	kmGLPopMatrix();
}

void CCNode::transformAncestors()
{
	if (m_pParent != NULL)
	{
		m_pParent->transformAncestors();
		m_pParent->transform();
	}
}

void CCNode::transform()
{
	kmMat4 transfrom4x4;

	// Convert 3x3 into 4x4 matrix
	CCAffineTransform tmpAffine = this->nodeToParentTransform();
	CGAffineToGL(&tmpAffine, transfrom4x4.mat);

	// Update Z vertex manually
	transfrom4x4.mat[14] = m_fPositionZ;

	kmGLMultMatrix(&transfrom4x4);

	// XXX: Expensive calls. Camera should be integrated into the cached affine matrix
	if (m_pCamera != NULL && !(m_pGrid != NULL && m_pGrid->isActive()))
	{
		bool translate = (m_obAnchorPointInPoints.x != 0.0f || m_obAnchorPointInPoints.y != 0.0f);

		if (translate)
		{
			kmGLTranslatef(RENDER_IN_SUBPIXEL(m_obAnchorPointInPoints.x), RENDER_IN_SUBPIXEL(m_obAnchorPointInPoints.y), 0);
		}
		m_pCamera->locate();
		if (translate)
		{
			kmGLTranslatef(RENDER_IN_SUBPIXEL(-m_obAnchorPointInPoints.x), RENDER_IN_SUBPIXEL(-m_obAnchorPointInPoints.y), 0);
		}
	}
}

void CCNode::onEnter()
{
	arrayMakeObjectsPerformSelector(m_pChildren, onEnter, CCNode*);

	this->resumeSchedulerAndActions();

	m_bRunning = true;

	CCScriptEngine::sharedEngine()->executeNodeEvent(this, CCNode::Enter);
}

void CCNode::onEnterTransitionDidFinish()
{
	arrayMakeObjectsPerformSelector(m_pChildren, onEnterTransitionDidFinish, CCNode*);

	CCScriptEngine::sharedEngine()->executeNodeEvent(this, CCNode::EnterTransitionDidFinish);
}

void CCNode::onExitTransitionDidStart()
{
	arrayMakeObjectsPerformSelector(m_pChildren, onExitTransitionDidStart, CCNode*);

	CCScriptEngine::sharedEngine()->executeNodeEvent(this, CCNode::ExitTransitionDidStart);
}

void CCNode::onExit()
{
	this->pauseSchedulerAndActions();

	m_bRunning = false;

	arrayMakeObjectsPerformSelector(m_pChildren, onExit, CCNode*);

	CCScriptEngine::sharedEngine()->executeNodeEvent(this, CCNode::Exit);
}

CCAction* CCNode::runAction(CCAction* action)
{
	CCAssert(action != NULL, "CCNode run action argument must be non-nil");
	m_pScheduler->getActionManager()->addAction(action, this, !m_bRunning);
	return action;
}

void CCNode::stopAllActions()
{
	m_pScheduler->getActionManager()->removeAllActionsFromTarget(this);
}

void CCNode::perform(CCAction* action)
{
	this->stopAllActions();
	this->runAction(action);
}

void CCNode::stopAction(CCAction* action)
{
	m_pScheduler->getActionManager()->removeAction(action);
}

void CCNode::stopActionByTag(int tag)
{
	CCAssert(tag != kCCActionTagInvalid, "Invalid tag");
	m_pScheduler->getActionManager()->removeActionByTag(tag, this);
}

CCAction * CCNode::getActionByTag(int tag)
{
	CCAssert(tag != kCCActionTagInvalid, "Invalid tag");
	return m_pScheduler->getActionManager()->getActionByTag(tag, this);
}

unsigned int CCNode::numberOfRunningActions()
{
	return m_pScheduler->getActionManager()->numberOfRunningActionsInTarget(this);
}

// CCNode - Callbacks

void CCNode::setScheduler(CCScheduler* scheduler)
{
	if (scheduler != m_pScheduler)
	{
		this->stopAllActions();
		this->unscheduleAllSelectors();
		CC_SAFE_RETAIN(scheduler);
		CC_SAFE_RELEASE(m_pScheduler);
		m_pScheduler = scheduler;
		if (_isScheduled)
		{
			CCNode::scheduleUpdate();
		}
	}
}

CCScheduler* CCNode::getScheduler()
{
	return m_pScheduler;
}

void CCNode::scheduleUpdate()
{
	scheduleUpdateWithPriority(0);
}

void CCNode::scheduleUpdateWithPriority(int priority)
{
	_isScheduled = true;
	m_pScheduler->scheduleUpdateForTarget(this, priority, !m_bRunning);
}

void CCNode::scheduleUpdateWithPriorityLua(int nHandler, int priority)
{
	unscheduleUpdate();
	m_nUpdateScriptHandler = nHandler;
	CCNode::scheduleUpdateWithPriority(priority);
}

void CCNode::unscheduleUpdate()
{
	_isScheduled = false;
	m_pScheduler->unscheduleUpdateForTarget(this);
	if (m_nUpdateScriptHandler)
	{
		CCScriptEngine::sharedEngine()->removeScriptHandler(m_nUpdateScriptHandler);
		m_nUpdateScriptHandler = 0;
	}
}

void CCNode::unscheduleUpdateLua()
{
	if (!_isScheduled)
	{
		m_pScheduler->unscheduleUpdateForTarget(this);
	}
	if (m_nUpdateScriptHandler)
	{
		CCScriptEngine::sharedEngine()->removeScriptHandler(m_nUpdateScriptHandler);
		m_nUpdateScriptHandler = 0;
	}
}

void CCNode::schedule(SEL_SCHEDULE selector)
{
	this->schedule(selector, 0.0f, kCCRepeatForever, 0.0f);
}

void CCNode::schedule(SEL_SCHEDULE selector, float interval)
{
	this->schedule(selector, interval, kCCRepeatForever, 0.0f);
}

void CCNode::schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay)
{
	CCAssert(selector, "CCNode schedule selector argument must be non-nil");
	CCAssert(interval >= 0, "Argument must be positive");

	m_pScheduler->scheduleSelector(selector, this, interval, repeat, delay, !m_bRunning);
}

void CCNode::scheduleOnce(SEL_SCHEDULE selector, float delay)
{
	this->schedule(selector, 0.0f, 0, delay);
}

void CCNode::unschedule(SEL_SCHEDULE selector)
{
	// explicit nil handling
	if (selector == 0)
		return;

	m_pScheduler->unscheduleSelector(selector, this);
}

void CCNode::unscheduleAllSelectors()
{
	m_pScheduler->unscheduleAllForTarget(this);
}

void CCNode::resumeSchedulerAndActions()
{
	m_pScheduler->resumeTarget(this);
	m_pScheduler->getActionManager()->resumeTarget(this);
}

void CCNode::pauseSchedulerAndActions()
{
	m_pScheduler->pauseTarget(this);
	m_pScheduler->getActionManager()->pauseTarget(this);
}

// override me
void CCNode::update(float fDelta)
{
	if (m_nUpdateScriptHandler)
	{
		if (CCScriptEngine::sharedEngine()->executeSchedule(m_nUpdateScriptHandler, fDelta) != 0)
		{
			CCNode::unscheduleUpdateLua();
		}
	}
}

CCAffineTransform CCNode::nodeToParentTransform()
{
	if (m_bTransformDirty)
	{
		// Translate values
		float x = m_obPosition.x;
		float y = m_obPosition.y;

		// Rotation values
		// Change rotation code to handle X and Y
		// If we skew with the exact same value for both x and y then we're simply just rotating
		float c = 1, s = 0;
		if (m_fRotation)
		{
			float radians = -CC_DEGREES_TO_RADIANS(m_fRotation);
			c = cosf(radians);
			s = sinf(radians);
		}

		bool needsSkewMatrix = (m_fSkewX || m_fSkewY);


		// optimization:
		// inline anchor point calculation if skew is not needed
		// Adjusted transform calculation for rotational skew
		if (!needsSkewMatrix && m_obAnchorPointInPoints != CCPoint::zero)
		{
			x += c * -m_obAnchorPointInPoints.x * m_fScaleX + -s * -m_obAnchorPointInPoints.y * m_fScaleY;
			y += s * -m_obAnchorPointInPoints.x * m_fScaleX + c * -m_obAnchorPointInPoints.y * m_fScaleY;
		}


		// Build Transform Matrix
		// Adjusted transform calculation for rotational skew
		m_sTransform = CCAffineTransformMake(c * m_fScaleX, s * m_fScaleX,
			-s * m_fScaleY, c * m_fScaleY,
			x, y);

		// XXX: Try to inline skew
		// If skew is needed, apply skew and then anchor point
		if (needsSkewMatrix)
		{
			CCAffineTransform skewMatrix = CCAffineTransformMake(1.0f, tanf(CC_DEGREES_TO_RADIANS(m_fSkewY)),
				tanf(CC_DEGREES_TO_RADIANS(m_fSkewX)), 1.0f,
				0.0f, 0.0f);
			m_sTransform = CCAffineTransformConcat(skewMatrix, m_sTransform);

			// adjust anchor point
			if (m_obAnchorPointInPoints != CCPoint::zero)
			{
				m_sTransform = CCAffineTransformTranslate(m_sTransform, -m_obAnchorPointInPoints.x, -m_obAnchorPointInPoints.y);
			}
		}

		m_bTransformDirty = false;
	}

	return m_sTransform;
}
CCAffineTransform CCNode::parentToNodeTransform()
{
	if (m_bInverseDirty)
	{
		m_sInverse = CCAffineTransformInvert(this->nodeToParentTransform());
		m_bInverseDirty = false;
	}
	return m_sInverse;
}

CCAffineTransform CCNode::nodeToWorldTransform()
{
	CCAffineTransform t = this->nodeToParentTransform();
	for (CCNode* p = this->getTargetParent(); p != NULL; p = p->getTargetParent())
	{
		t = CCAffineTransformConcat(t, p->nodeToParentTransform());
	}
	return t;
}
CCAffineTransform CCNode::worldToNodeTransform()
{
	return CCAffineTransformInvert(this->nodeToWorldTransform());
}

CCAffineTransform CCNode::nodeToGameParentTransform(void)
{
	return CCNode::nodeToParentTransform();
}
CCAffineTransform CCNode::gameParentToNodeTransform(void)
{
	return CCAffineTransformInvert(this->nodeToGameParentTransform());
}

CCAffineTransform CCNode::nodeToGameTransform(void)
{
	CCAffineTransform t = this->nodeToGameParentTransform();
	for (CCNode* p = this->getTargetParent(); p != NULL; p = p->getTargetParent())
	{
		t = CCAffineTransformConcat(t, p->nodeToGameParentTransform());
	}
	return t;
}
CCAffineTransform CCNode::gameToNodeTransform(void)
{
	return CCAffineTransformInvert(this->nodeToGameTransform());
}

CCPoint CCNode::convertToNodeSpace(const CCPoint& worldPoint)
{
	CCPoint ret = CCPointApplyAffineTransform(worldPoint, worldToNodeTransform());
	return ret;
}

CCPoint CCNode::convertToWorldSpace(const CCPoint& nodePoint)
{
	CCPoint ret = CCPointApplyAffineTransform(nodePoint, nodeToWorldTransform());
	return ret;
}

CCPoint CCNode::convertToNodeSpaceAR(const CCPoint& worldPoint)
{
	CCPoint nodePoint = convertToNodeSpace(worldPoint);
	return ccpSub(nodePoint, m_obAnchorPointInPoints);
}

CCPoint CCNode::convertToWorldSpaceAR(const CCPoint& nodePoint)
{
	CCPoint pt = ccpAdd(nodePoint, m_obAnchorPointInPoints);
	return convertToWorldSpace(pt);
}

CCPoint CCNode::convertToWindowSpace(const CCPoint& nodePoint)
{
	CCPoint worldPoint = this->convertToWorldSpace(nodePoint);
	return CCDirector::sharedDirector()->convertToUI(worldPoint);
}

// convenience methods which take a CCTouch instead of CCPoint
CCPoint CCNode::convertTouchToNodeSpace(CCTouch *touch)
{
	CCPoint point = touch->getLocation();
	return this->convertToNodeSpace(point);
}
CCPoint CCNode::convertTouchToNodeSpaceAR(CCTouch *touch)
{
	CCPoint point = touch->getLocation();
	return this->convertToNodeSpaceAR(point);
}

CCPoint CCNode::convertToGameSpace(const CCPoint& nodePoint)
{
	return CCPointApplyAffineTransform(nodePoint, nodeToGameTransform());
}

void CCNode::updateTransform()
{
	// Recursively iterate over children
	arrayMakeObjectsPerformSelector(m_pChildren, updateTransform, CCNode*);
}

float CCNode::getOpacity()
{
	return _realOpacity;
}

float CCNode::getDisplayedOpacity()
{
	return _displayedOpacity;
}

void CCNode::setOpacity(float opacity)
{
	if (opacity < 0.0f) opacity = 0.0f;
	if (opacity > 1.0f) opacity = 1.0f;
	_displayedOpacity = _realOpacity = opacity;
	this->updateDisplayedOpacity(m_pParent ? m_pParent->getDisplayedOpacity() : 1.0f);
}

void CCNode::updateDisplayedOpacity(float parentOpacity)
{
	if (m_pParent && m_pParent->isCascadeOpacity())
	{
		_displayedOpacity = _realOpacity * parentOpacity;
	}
	else
	{
		_displayedOpacity = _realOpacity;
	}
	if (_cascadeOpacity)
	{
		CCObject* pObj;
		CCARRAY_FOREACH(m_pChildren, pObj)
		{
			CCNode* node = (CCNode*)pObj;
			node->updateDisplayedOpacity(_displayedOpacity);
		}
	}
}

void CCNode::setCascadeOpacity(bool var)
{
	_cascadeOpacity = var;
	this->setOpacity(_realOpacity);
	if (!var)
	{
		CCObject* pObj;
		CCARRAY_FOREACH(m_pChildren, pObj)
		{
			CCNode* node = (CCNode*)pObj;
			node->updateDisplayedOpacity(_realOpacity);
		}
	}
}

bool CCNode::isCascadeOpacity() const
{
	return _cascadeOpacity;
}

const ccColor3B& CCNode::getColor()
{
	return _realColor;
}

const ccColor3B& CCNode::getDisplayedColor()
{
	return _displayedColor;
}

void CCNode::setColor(const ccColor3B& color)
{
	_displayedColor = _realColor = color;
	this->updateDisplayedColor(m_pParent ? m_pParent->getDisplayedColor() : ccWHITE);
}

void CCNode::updateDisplayedColor(const ccColor3B& parentColor)
{
	if (m_pParent && m_pParent->isCascadeColor())
	{
		_displayedColor.r = _realColor.r * parentColor.r / 255.0f;
		_displayedColor.g = _realColor.g * parentColor.g / 255.0f;
		_displayedColor.b = _realColor.b * parentColor.b / 255.0f;
	}
	else
	{
		_displayedColor = _realColor;
	}
	if (_cascadeColor)
	{
		CCObject *obj = NULL;
		CCARRAY_FOREACH(m_pChildren, obj)
		{
			CCNode* node = (CCNode*)obj;
			node->updateDisplayedColor(_displayedColor);
		}
	}
}

void CCNode::setCascadeColor(bool var)
{
	_cascadeColor = var;
	this->setColor(_realColor);
	if (!var)
	{
		CCObject *obj = NULL;
		CCARRAY_FOREACH(m_pChildren, obj)
		{
			CCNode* node = (CCNode*)obj;
			node->updateDisplayedColor(_displayedColor);
		}
	}
}

bool CCNode::isCascadeColor() const
{
	return _cascadeColor;
}

void CCNode::setTransformTarget(CCNode* target)
{
	CCWeak* ref = NULL;
	if (target)
	{
		ref = target->getWeakRef();
		ref->retain();
	}
	if (_transformTargetRef)
	{
		_transformTargetRef->release();
	}
	_transformTargetRef = ref;
}

CCNode* CCNode::getTransformTarget() const
{
	if (_transformTargetRef)
	{
		return (CCNode*)_transformTargetRef->target;
	}
	return nullptr;
}

CCNode* CCNode::getTargetParent() const
{
	return _transformTargetRef ? (CCNode*)_transformTargetRef->target : m_pParent;
}

NS_CC_END
