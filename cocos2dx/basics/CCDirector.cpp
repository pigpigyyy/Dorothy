/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
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
#include "CCDirector.h"
#include "ccFPSImages.h"
#include "draw_nodes/CCDrawingPrimitives.h"
#include "CCConfiguration.h"
#include "cocoa/CCNS.h"
#include "layers_scenes_transitions_nodes/CCScene.h"
#include "cocoa/CCArray.h"
#include "CCScheduler.h"
#include "ccMacros.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "support/CCPointExtension.h"
#include "support/CCNotificationCenter.h"
#include "layers_scenes_transitions_nodes/CCTransition.h"
#include "textures/CCTextureCache.h"
#include "cocoa/CCAutoreleasePool.h"
#include "platform/platform.h"
#include "platform/CCFileUtils.h"
#include "platform/CCImage.h"
#include "CCApplication.h"
#include "label_nodes/CCLabelBMFont.h"
#include "label_nodes/CCLabelAtlas.h"
#include "actions/CCActionManager.h"
#include "CCConfiguration.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"
#include "CCAccelerometer.h"
#include "touch_dispatcher/CCTouch.h"
#include "support/user_default/CCUserDefault.h"
#include "shaders/ccGLStateCache.h"
#include "shaders/CCShaderCache.h"
#include "kazmath/kazmath.h"
#include "kazmath/GL/matrix.h"
#include "support/CCProfiling.h"
#include "script_support/CCScriptSupport.h"
#include "CCEGLView.h"
#include <string>
#include <ctime>
#include <cstdlib>

/**
 Position of the FPS

 Default: 0,0 (bottom-left corner)
 */
#ifndef CC_DIRECTOR_STATS_POSITION
#define CC_DIRECTOR_STATS_POSITION CCDirector::sharedDirector()->getVisibleOrigin()
#endif

using namespace std;

unsigned int g_uNumberOfDraws = 0;

NS_CC_BEGIN
// XXX it should be a Director ivar. Move it there once support for multiple directors is added

// singleton stuff
static CCDisplayLinkDirector *s_SharedDirector = NULL;

/* last time the main loop was updated */
static cc_timeval s_obLastUpdate;
static cc_timeval s_obTickStart;

#define kDefaultFPS 60  // 60 frames per second
extern const char* cocos2dVersion();

CCDirector* CCDirector::sharedDirector()
{
	if (!s_SharedDirector)
	{
		s_SharedDirector = new CCDisplayLinkDirector();
		s_SharedDirector->init();
	}

	return s_SharedDirector;
}

CCDirector::CCDirector()
{ }

bool CCDirector::init()
{
	if (!CCObject::init()) return false;
	srand((unsigned int)time(nullptr));
	CCLOG("cocos2d: %s", cocos2dVersion());
	// scenes
	m_pRunningScene = NULL;
	m_pNextScene = NULL;

	m_pNotificationNode = NULL;

	m_dOldAnimationInterval = m_dAnimationInterval = 1.0 / kDefaultFPS;
	m_pobScenesStack = new CCArray();
	m_pobScenesStack->init();

	// Set default projection (3D)
	m_eProjection = kCCDirectorProjectionDefault;

	// projection delegate if "Custom" projection is used
	m_pProjectionDelegate = NULL;

	// FPS
	m_fAccumDt = 0.0f;
	m_fAccumUpdateDt = 0.0f;
	m_fAccumDrawDt = 0.0f;
	m_fFrameRate = 0.0f;
	m_pFPSLabel = NULL;
	m_pUSPFLabel = NULL;
	m_pDSPFLabel = NULL;
	m_pDrawsLabel = NULL;
	m_pObjectLabel = NULL;
	m_bDisplayStats = false;
	m_uTotalFrames = m_uFrames = 0;
	m_pszFPS = new char[10];
	
	m_fDeltaTime = 0.0f;
	m_fRealDeltaTime = 0.0f;
	m_fUpdateInterval = 0.0f;
	m_fDrawInterval = 0.0f;
	CCTime::gettimeofdayCocos2d(&s_obTickStart, NULL);

	// paused ?
	m_bPaused = false;

	// purge ?
	m_bPurgeDirecotorInNextLoop = false;

	m_obWinSizeInPoints = CCSize::zero;

	m_pobOpenGLView = NULL;

	m_fContentScaleFactor = 1.0f;

	m_nHandler = 0;

	// scheduler
	m_pScheduler = new CCScheduler();

	// touchDispatcher
	m_pTouchDispatcher = new CCTouchDispatcher();
	m_pTouchDispatcher->init();

	// KeypadDispatcher
	m_pKeypadDispatcher = new CCKeypadDispatcher();

	// Accelerometer
	m_pAccelerometer = new CCAccelerometer();

	// create autorelease pool
	CCPoolManager::sharedPoolManager()->push();

	return true;
}

CCDirector::~CCDirector()
{
	CCLOG("cocos2d: deallocing CCDirector %p", this);

	CC_SAFE_RELEASE(m_pFPSLabel);
	CC_SAFE_RELEASE(m_pUSPFLabel);
	CC_SAFE_RELEASE(m_pDSPFLabel);
	CC_SAFE_RELEASE(m_pDrawsLabel);
	CC_SAFE_RELEASE(m_pObjectLabel);

	CC_SAFE_RELEASE(m_pRunningScene);
	CC_SAFE_RELEASE(m_pNotificationNode);
	CC_SAFE_RELEASE(m_pobScenesStack);
	CC_SAFE_RELEASE(m_pScheduler);
	CC_SAFE_RELEASE(m_pTouchDispatcher);
	CC_SAFE_RELEASE(m_pKeypadDispatcher);
	CC_SAFE_DELETE(m_pAccelerometer);

	// pop the autorelease pool
	CCPoolManager::sharedPoolManager()->pop();
	CCPoolManager::purgePoolManager();

	// delete fps string
	CC_SAFE_DELETE_ARRAY(m_pszFPS);

	if (m_nHandler)
	{
		CCScriptEngine::sharedEngine()->removeScriptHandler(m_nHandler);
	}

	s_SharedDirector = NULL;
}

CCScene* CCDirector::getRunningScene() const
{
	CCScene* scene = m_pNextScene ? m_pNextScene : m_pRunningScene;
	CCTransitionScene* transitionScene = dynamic_cast<CCTransitionScene*>(scene);
	if (transitionScene)
	{
		scene = transitionScene->getTargetScene();
	}
	return scene;
}

void CCDirector::setDisplayStats(bool bDisplayStats)
{
	if (m_bDisplayStats == bDisplayStats) return;
	m_bDisplayStats = bDisplayStats;
	if (bDisplayStats)
	{
		CCImage* image = new CCImage();
		image->initWithImageData(cc_fps_images_png, cc_fps_images_len());
		CCTextureCache::sharedTextureCache()->addUIImage(image, "cc_fps_images");
    	CC_SAFE_DELETE(image);
		CCDirector::createStatsLabel();
	}
	else
	{
		CC_SAFE_RELEASE_NULL(m_pFPSLabel);
		CC_SAFE_RELEASE_NULL(m_pUSPFLabel);
		CC_SAFE_RELEASE_NULL(m_pDSPFLabel);
		CC_SAFE_RELEASE_NULL(m_pDrawsLabel);
		CC_SAFE_RELEASE_NULL(m_pObjectLabel);
		CCTextureCache::sharedTextureCache()->removeTextureForKey("cc_fps_images");
	}
}

void CCDirector::setGLDefaultValues()
{
	// This method SHOULD be called only after openGLView_ was initialized
	CCAssert(m_pobOpenGLView, "opengl view should not be null");

	setAlphaBlending(true);
	// XXX: Fix me, should enable/disable depth test according the depth format as cocos2d-iphone did
	// [self setDepthTest: view_.depthFormat];
	setDepthTest(false);
	setProjection(m_eProjection);

	// set other opengl default values
}

// Draw the Scene
void CCDirector::drawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* to avoid flickr, nextScene MUST be here: after tick and before draw.
	 XXX: Which bug is this one. It seems that it can't be reproduced with v0.9 */
	if (m_pNextScene)
	{
		setNextScene();
	}

	kmGLPushMatrix();

	// draw the scene
	if (m_pRunningScene)
	{
		m_pRunningScene->visit();
	}

	// draw the notifications node
	if (m_pNotificationNode)
	{
		m_pNotificationNode->visit();
	}

	if (m_bDisplayStats)
	{
		showStats();
	}

	kmGLPopMatrix();

	m_uTotalFrames++;

	// swap buffers
	if (m_pobOpenGLView)
	{
		m_pobOpenGLView->swapBuffers();
	}

	g_uNumberOfDraws = 0;
}

void CCDirector::calculateDeltaTime()
{
	struct cc_timeval now;

	if (CCTime::gettimeofdayCocos2d(&now, NULL) != 0)
	{
		CCLOG("error in gettimeofday");
		m_fDeltaTime = m_fRealDeltaTime = 0;
		return;
	}

	// new delta time. Re-fixed issue #1277
	if (m_bNextDeltaTimeZero)
	{
		m_fDeltaTime = m_fRealDeltaTime = 0;
		m_bNextDeltaTimeZero = false;
	}
	else
	{
		m_fRealDeltaTime = (now.tv_sec - s_obLastUpdate.tv_sec)
		 + (now.tv_usec - s_obLastUpdate.tv_usec) / 1000000.0f;
		m_fRealDeltaTime = MAX(0, m_fRealDeltaTime);
		m_fDeltaTime = MIN(1.0f/30.0f, m_fRealDeltaTime);
	}
	s_obLastUpdate = now;
}

float CCDirector::getDeltaTime()
{
	return m_fDeltaTime;
}

void CCDirector::setOpenGLView(CCEGLView *pobOpenGLView)
{
	CCAssert(pobOpenGLView, "opengl view should not be null");

	if (m_pobOpenGLView != pobOpenGLView)
	{
		// EAGLView is not a CCObject
		delete m_pobOpenGLView; // [openGLView_ release]
		m_pobOpenGLView = pobOpenGLView;

		// set size
		m_obWinSizeInPoints = m_pobOpenGLView->getDesignResolutionSize();
		
		if (m_bDisplayStats) createStatsLabel();

		if (m_pobOpenGLView) setGLDefaultValues();

		CHECK_GL_ERROR_DEBUG();

		m_pobOpenGLView->setTouchDelegate(m_pTouchDispatcher);
		m_pTouchDispatcher->setDispatchEvents(true);
	}
}

void CCDirector::setViewport()
{
	if (m_pobOpenGLView)
	{
		m_pobOpenGLView->setViewPortInPoints(0, 0, m_obWinSizeInPoints.width, m_obWinSizeInPoints.height);
	}
}

void CCDirector::setNextDeltaTimeZero(bool bNextDeltaTimeZero)
{
	m_bNextDeltaTimeZero = bNextDeltaTimeZero;
}

void CCDirector::projection()
{
	CCDirector::setProjection(m_eProjection);
}

void CCDirector::setProjection(ccDirectorProjection kProjection)
{
	CCSize size = m_obWinSizeInPoints;

	setViewport();

	switch (kProjection)
	{
	case kCCDirectorProjection2D:
	{
		kmGLMatrixMode(KM_GL_PROJECTION);
		kmGLLoadIdentity();
		kmMat4 orthoMatrix;
		kmMat4OrthographicProjection(&orthoMatrix, 0, size.width, 0, size.height, -1024, 1024);
		kmGLMultMatrix(&orthoMatrix);
		kmGLMatrixMode(KM_GL_MODELVIEW);
		kmGLLoadIdentity();
	}
		break;

	case kCCDirectorProjection3D:
	{
		float zeye = this->getZEye();

		kmMat4 matrixPerspective, matrixLookup;

		kmGLMatrixMode(KM_GL_PROJECTION);
		kmGLLoadIdentity();

		// issue #1334
		kmMat4PerspectiveProjection(&matrixPerspective, 60, (GLfloat)size.width / size.height, 0.1f, zeye * 2);
		// kmMat4PerspectiveProjection( &matrixPerspective, 60, (GLfloat)size.width/size.height, 0.1f, 1500);

		kmGLMultMatrix(&matrixPerspective);

		kmGLMatrixMode(KM_GL_MODELVIEW);
		kmGLLoadIdentity();
		kmVec3 eye, center, up;
		kmVec3Fill(&eye, size.width / 2, size.height / 2, zeye);
		kmVec3Fill(&center, size.width / 2, size.height / 2, 0.0f);
		kmVec3Fill(&up, 0.0f, 1.0f, 0.0f);
		kmMat4LookAt(&matrixLookup, &eye, &center, &up);
		kmGLMultMatrix(&matrixLookup);
	}
		break;

	case kCCDirectorProjectionCustom:
		if (m_pProjectionDelegate)
		{
			m_pProjectionDelegate->updateProjection();
		}
		break;

	default:
		CCLOG("cocos2d: Director: unrecognized projection");
		break;
	}

	m_eProjection = kProjection;
	ccSetProjectionMatrixDirty();
}

void CCDirector::purgeCachedData()
{
	CCLabelBMFont::purgeCachedData();
	if (s_SharedDirector->getOpenGLView())
	{
		CCTextureCache::sharedTextureCache()->removeUnusedTextures();
	}
	CCFileUtils::sharedFileUtils()->purgeCachedEntries();
}

float CCDirector::getZEye()
{
	return (m_obWinSizeInPoints.height / 1.1566f);
}

void CCDirector::setAlphaBlending(bool bOn)
{
	if (bOn)
	{
		ccGLBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	}
	else
	{
		ccGLBlendFunc(GL_ONE, GL_ZERO);
	}

	CHECK_GL_ERROR_DEBUG();
}

void CCDirector::setDepthTest(bool bOn)
{
	if (bOn)
	{
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
	CHECK_GL_ERROR_DEBUG();
}

static void GLToClipTransform(kmMat4 *transformOut)
{
	kmMat4 projection;
	kmGLGetMatrix(KM_GL_PROJECTION, &projection);

	kmMat4 modelview;
	kmGLGetMatrix(KM_GL_MODELVIEW, &modelview);

	kmMat4Multiply(transformOut, &projection, &modelview);
}

CCPoint CCDirector::convertToGL(const CCPoint& uiPoint)
{
	kmMat4 transform;
	GLToClipTransform(&transform);

	kmMat4 transformInv;
	kmMat4Inverse(&transformInv, &transform);

	// Calculate z=0 using -> transform*[0, 0, 0, 1]/w
	kmScalar zClip = transform.mat[14] / transform.mat[15];

	CCSize glSize = m_pobOpenGLView->getDesignResolutionSize();
	kmVec3 clipCoord = { 2.0f*uiPoint.x / glSize.width - 1.0f, 1.0f - 2.0f*uiPoint.y / glSize.height, zClip };

	kmVec3 glCoord;
	kmVec3TransformCoord(&glCoord, &clipCoord, &transformInv);

	return ccp(glCoord.x, glCoord.y);
}

CCPoint CCDirector::convertToUI(const CCPoint& glPoint)
{
	kmMat4 transform;
	GLToClipTransform(&transform);

	kmVec3 clipCoord;
	// Need to calculate the zero depth from the transform.
	kmVec3 glCoord = { glPoint.x, glPoint.y, 0.0 };
	kmVec3TransformCoord(&clipCoord, &glCoord, &transform);

	CCSize glSize = m_pobOpenGLView->getDesignResolutionSize();
	return ccp(glSize.width*(clipCoord.x*0.5 + 0.5), glSize.height*(-clipCoord.y*0.5 + 0.5));
}

CCSize CCDirector::getWinSize()
{
	return m_obWinSizeInPoints;
}

CCSize CCDirector::getWinSizeInPixels()
{
	return CCSizeMake(m_obWinSizeInPoints.width * m_fContentScaleFactor, m_obWinSizeInPoints.height * m_fContentScaleFactor);
}

CCSize CCDirector::getVisibleSize()
{
	if (m_pobOpenGLView)
	{
		return m_pobOpenGLView->getVisibleSize();
	}
	else
	{
		return CCSize::zero;
	}
}

CCPoint CCDirector::getVisibleOrigin()
{
	if (m_pobOpenGLView)
	{
		return m_pobOpenGLView->getVisibleOrigin();
	}
	else
	{
		return CCPoint::zero;
	}
}

// scene management
void CCDirector::runWithScene(CCScene *pScene)
{
	CCAssert(pScene != NULL, "the scene should not be null");
	pushScene(pScene);
	if (m_pobScenesStack->count() == 1) startAnimation();
}

void CCDirector::replaceScene(CCScene *pScene)
{
	CCAssert(m_pRunningScene, "Use runWithScene: instead to start the director");
	CCAssert(pScene != NULL, "the scene should not be null");

	unsigned int index = m_pobScenesStack->count();

	m_bSendCleanupToScene = true;
	m_pobScenesStack->replaceObjectAtIndex(index - 1, pScene);

	m_pNextScene = pScene;
}

void CCDirector::pushScene(CCScene *pScene)
{
	CCAssert(pScene, "the scene should not null");

	m_bSendCleanupToScene = false;

	m_pobScenesStack->addObject(pScene);
	m_pNextScene = pScene;
}

void CCDirector::popScene()
{
	CCAssert(m_pRunningScene != NULL, "running scene should not null");

	m_pobScenesStack->removeLastObject();
	unsigned int c = m_pobScenesStack->count();

	if (c == 0)
	{
		end();
	}
	else
	{
		m_pNextScene = (CCScene*)m_pobScenesStack->objectAtIndex(c - 1);
		if (m_pRunningScene != m_pNextScene)
		{
			m_bSendCleanupToScene = true;
		}
		else
		{
			m_pNextScene = NULL;
		}
	}
}

void CCDirector::popToRootScene()
{
	CCAssert(m_pRunningScene != NULL, "A running Scene is needed");
	CCScene* rootScene = (CCScene*)m_pobScenesStack->objectAtIndex(0);
	while (m_pobScenesStack->count() > 1)
	{
		CCScene* current = (CCScene*)m_pobScenesStack->lastObject();
		if (current != rootScene)
		{
			if (current->isRunning())
			{
				current->onExitTransitionDidStart();
				current->onExit();
			}
			current->cleanup();
		}
		m_pobScenesStack->removeLastObject();
	}
	CCScene* nextScene = (CCScene*)m_pobScenesStack->lastObject();
	if (m_pRunningScene != nextScene)
	{
		m_pRunningScene->release();
		m_pRunningScene = NULL;
		m_pNextScene = nextScene;
		m_bSendCleanupToScene = false;
	}
}

void CCDirector::end()
{
	m_bPurgeDirecotorInNextLoop = true;
}

void CCDirector::purgeDirector()
{
	// cleanup scheduler
	getScheduler()->unscheduleAll();

	// don't release the event handlers
	// They are needed in case the director is run again
	m_pTouchDispatcher->removeAllDelegates();

	if (m_pRunningScene)
	{
		m_pRunningScene->onExitTransitionDidStart();
		m_pRunningScene->onExit();
		m_pRunningScene->cleanup();
		m_pRunningScene->release();
	}

	m_pRunningScene = NULL;
	m_pNextScene = NULL;

	// remove all objects, but don't release it.
	// runWithScene might be executed after 'end'.
	m_pobScenesStack->removeAllObjects();

	stopAnimation();

	CCDirector::setDisplayStats(false);

	// purge bitmap cache
	CCLabelBMFont::purgeCachedData();

	// purge all managed caches
	ccDrawFree();
	CCTextureCache::purgeSharedTextureCache();
	CCShaderCache::purgeSharedShaderCache();
	CCConfiguration::purgeConfiguration();

	ccGLInvalidateStateCache();

	CHECK_GL_ERROR_DEBUG();

	// OpenGL view
	m_pobOpenGLView->end();
	m_pobOpenGLView = NULL;

	// delete CCDirector
	release();
}

void CCDirector::setNextScene()
{
	bool runningIsTransition = dynamic_cast<CCTransitionScene*>(m_pRunningScene) != NULL;
	bool newIsTransition = dynamic_cast<CCTransitionScene*>(m_pNextScene) != NULL;

	// If it is not a transition, call onExit/cleanup
	if (!newIsTransition)
	{
		if (m_pRunningScene)
		{
			m_pRunningScene->onExitTransitionDidStart();
			m_pRunningScene->onExit();
		}

		// issue #709. the root node (scene) should receive the cleanup message too
		// otherwise it might be leaked.
		if (m_bSendCleanupToScene && m_pRunningScene)
		{
			m_pRunningScene->cleanup();
		}
	}

	if (m_pRunningScene)
	{
		m_pRunningScene->release();
	}
	m_pRunningScene = m_pNextScene;
	m_pNextScene->retain();
	m_pNextScene = NULL;

	if ((!runningIsTransition) && m_pRunningScene)
	{
		m_pRunningScene->onEnter();
		m_pRunningScene->onEnterTransitionDidFinish();
	}
}

void CCDirector::pause()
{
	if (m_bPaused)
	{
		return;
	}

	m_dOldAnimationInterval = m_dAnimationInterval;

	// when paused, don't consume CPU
	setAnimationInterval(1 / 4.0);
	m_bPaused = true;
}

void CCDirector::resume()
{
	if (!m_bPaused)
	{
		return;
	}

	setAnimationInterval(m_dOldAnimationInterval);

	if (CCTime::gettimeofdayCocos2d(&s_obLastUpdate, NULL) != 0)
	{
		CCLOG("cocos2d: Director: Error in gettimeofday");
	}

	m_bPaused = false;
	m_fDeltaTime = m_fRealDeltaTime = 0;
}

// display the FPS using a LabelAtlas
// updates the FPS every frame
void CCDirector::showStats()
{
	m_uFrames++;
	m_fAccumDt += m_fRealDeltaTime;
	m_fAccumUpdateDt += m_fUpdateInterval;
	m_fAccumDrawDt += m_fDrawInterval;

	if (m_fAccumDt > CC_DIRECTOR_STATS_INTERVAL)
	{
		sprintf(m_pszFPS, "%.3f", m_fAccumUpdateDt/m_uFrames);
		m_pUSPFLabel->setText(m_pszFPS);

		sprintf(m_pszFPS, "%.3f", m_fAccumDrawDt/m_uFrames);
		m_pDSPFLabel->setText(m_pszFPS);

		sprintf(m_pszFPS, "%.f", m_uFrames/m_fAccumDt);
		m_pFPSLabel->setText(m_pszFPS);

		sprintf(m_pszFPS, "%lu", (unsigned long)g_uNumberOfDraws);
		m_pDrawsLabel->setText(m_pszFPS);
		
		sprintf(m_pszFPS, "%d", CCObject::getObjectCount());
		m_pObjectLabel->setText(m_pszFPS);

		CCSize contentSize = m_pObjectLabel->getContentSize();
		m_pObjectLabel->setPosition(
			ccpAdd(ccp(contentSize.width * 0.5f, contentSize.height * 4.5f),
					CC_DIRECTOR_STATS_POSITION));
		contentSize = m_pDrawsLabel->getContentSize();
		m_pDrawsLabel->setPosition(
			ccpAdd(ccp(contentSize.width * 0.5f, contentSize.height * 3.5f),
					CC_DIRECTOR_STATS_POSITION));
		contentSize = m_pUSPFLabel->getContentSize();
		m_pUSPFLabel->setPosition(
			ccpAdd(ccp(contentSize.width * 0.5f, contentSize.height * 2.5f),
					CC_DIRECTOR_STATS_POSITION));
		contentSize = m_pDSPFLabel->getContentSize();
		m_pDSPFLabel->setPosition(
			ccpAdd(ccp(contentSize.width * 0.5f, contentSize.height * 1.5f),
					CC_DIRECTOR_STATS_POSITION));
		contentSize = m_pFPSLabel->getContentSize();
		m_pFPSLabel->setPosition(
			ccpAdd(ccp(contentSize.width * 0.5f, contentSize.height * 0.5f),
					CC_DIRECTOR_STATS_POSITION));
		
		m_uFrames = 0;
		m_fAccumDt = 0;
		m_fAccumUpdateDt = 0;
		m_fAccumDrawDt = 0;
	}
	
	m_pObjectLabel->visit();
	m_pDrawsLabel->visit();
	m_pUSPFLabel->visit();
	m_pDSPFLabel->visit();
	m_pFPSLabel->visit();
}

void CCDirector::createStatsLabel()
{
	if (!m_bDisplayStats) return;
	
	CC_SAFE_RELEASE_NULL(m_pFPSLabel);
	CC_SAFE_RELEASE_NULL(m_pDSPFLabel);
	CC_SAFE_RELEASE_NULL(m_pUSPFLabel);
	CC_SAFE_RELEASE_NULL(m_pDrawsLabel);
	CC_SAFE_RELEASE_NULL(m_pObjectLabel);

	int fontSize = 0;
	if (m_obWinSizeInPoints.width > m_obWinSizeInPoints.height)
	{
		fontSize = (int)(m_obWinSizeInPoints.height / 320.0f * 24);
	}
	else
	{
		fontSize = (int)(m_obWinSizeInPoints.width / 320.0f * 24);
	}

    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("cc_fps_images");

    m_pFPSLabel = new CCLabelAtlas();
    m_pFPSLabel->initWithString("FPS 00.0", texture, 12, 32 , '.');
	m_pFPSLabel->retain();

    m_pUSPFLabel = new CCLabelAtlas();
    m_pUSPFLabel->initWithString("0.000", texture, 12, 32, '.');
	m_pUSPFLabel->retain();

    m_pDSPFLabel = new CCLabelAtlas();
    m_pDSPFLabel->initWithString("0.000", texture, 12, 32, '.');
	m_pDSPFLabel->retain();

    m_pDrawsLabel = new CCLabelAtlas();
    m_pDrawsLabel->initWithString("000", texture, 12, 32, '.');
	m_pDrawsLabel->retain();

	m_pObjectLabel = new CCLabelAtlas();
    m_pObjectLabel->initWithString("000", texture, 12, 32, '.');
	m_pObjectLabel->retain();

	CCSize contentSize = m_pObjectLabel->getContentSize();
	m_pObjectLabel->setPosition(ccpAdd(ccp(contentSize.width * 0.5f, contentSize.height * 4.5f), CC_DIRECTOR_STATS_POSITION));
	contentSize = m_pDrawsLabel->getContentSize();
	m_pDrawsLabel->setPosition(ccpAdd(ccp(contentSize.width * 0.5f, contentSize.height * 3.5f), CC_DIRECTOR_STATS_POSITION));
	contentSize = m_pUSPFLabel->getContentSize();
	m_pUSPFLabel->setPosition(ccpAdd(ccp(contentSize.width * 0.5f, contentSize.height * 2.5f), CC_DIRECTOR_STATS_POSITION));
	contentSize = m_pDSPFLabel->getContentSize();
	m_pDSPFLabel->setPosition(ccpAdd(ccp(contentSize.width * 0.5f, contentSize.height * 1.5f), CC_DIRECTOR_STATS_POSITION));
	contentSize = m_pFPSLabel->getContentSize();
	m_pFPSLabel->setPosition(ccpAdd(ccp(contentSize.width * 0.5f, contentSize.height * 0.5f), CC_DIRECTOR_STATS_POSITION));
}

float CCDirector::getContentScaleFactor()
{
	return m_fContentScaleFactor;
}

void CCDirector::setContentScaleFactor(float scaleFactor)
{
	if (scaleFactor != m_fContentScaleFactor)
	{
		m_fContentScaleFactor = scaleFactor;
		if (m_bDisplayStats) createStatsLabel();
	}
}

CCNode* CCDirector::getNotificationNode()
{
	return m_pNotificationNode;
}

void CCDirector::setNotificationNode(CCNode *node)
{
	CC_SAFE_RELEASE(m_pNotificationNode);
	m_pNotificationNode = node;
	CC_SAFE_RETAIN(m_pNotificationNode);
}

CCDirectorDelegate* CCDirector::getDelegate() const
{
	return m_pProjectionDelegate;
}

void CCDirector::setDelegate(CCDirectorDelegate* pDelegate)
{
	m_pProjectionDelegate = pDelegate;
}

void CCDirector::setScheduler(CCScheduler* pScheduler)
{
	if (m_pScheduler != pScheduler)
	{
		CC_SAFE_RETAIN(pScheduler);
		CC_SAFE_RELEASE(m_pScheduler);
		m_pScheduler = pScheduler;
	}
}

CCScheduler* CCDirector::getScheduler()
{
	return m_pScheduler;
}

void CCDirector::setTouchDispatcher(CCTouchDispatcher* pTouchDispatcher)
{
	if (m_pTouchDispatcher != pTouchDispatcher)
	{
		CC_SAFE_RETAIN(pTouchDispatcher);
		CC_SAFE_RELEASE(m_pTouchDispatcher);
		m_pTouchDispatcher = pTouchDispatcher;
	}
}

CCTouchDispatcher* CCDirector::getTouchDispatcher()
{
	return m_pTouchDispatcher;
}

void CCDirector::setKeypadDispatcher(CCKeypadDispatcher* pKeypadDispatcher)
{
	CC_SAFE_RETAIN(pKeypadDispatcher);
	CC_SAFE_RELEASE(m_pKeypadDispatcher);
	m_pKeypadDispatcher = pKeypadDispatcher;
}

CCKeypadDispatcher* CCDirector::getKeypadDispatcher()
{
	return m_pKeypadDispatcher;
}

void CCDirector::setAccelerometer(CCAccelerometer* pAccelerometer)
{
	if (m_pAccelerometer != pAccelerometer)
	{
		CC_SAFE_DELETE(m_pAccelerometer);
		m_pAccelerometer = pAccelerometer;
	}
}

CCAccelerometer* CCDirector::getAccelerometer()
{
	return m_pAccelerometer;
}

float CCDirector::getInterval(const struct cc_timeval& begin)
{
	struct cc_timeval now;
	if (CCTime::gettimeofdayCocos2d(&now, NULL) != 0)
	{
		CCLOG("error in gettimeofday");
		return 0;
	}
	return (now.tv_sec - begin.tv_sec) + (now.tv_usec - begin.tv_usec) / 1000000.0f;
}

float CCDirector::getEclapsedInterval()
{
	return CCDirector::getInterval(s_obTickStart);
}

unsigned int CCDirector::getSceneStackSize()
{
	return m_pobScenesStack->count();
}

float CCDirector::getUpdateInterval()
{
	return m_fUpdateInterval;
}

float CCDirector::getDrawInterval()
{
	return m_fDrawInterval;
}

void CCDirector::scheduleUpdateLua(int handler)
{
	CCDirector::unscheduleUpdateLua();
	m_nHandler = handler;
}

void CCDirector::unscheduleUpdateLua()
{
	if (m_nHandler)
	{
		CCScriptEngine::sharedEngine()->removeScriptHandler(m_nHandler);
		m_nHandler = 0;
	}
}

/***************************************************
* implementation of DisplayLinkDirector
**************************************************/

// should we implement 4 types of director ??
// I think DisplayLinkDirector is enough
// so we now only support DisplayLinkDirector
void CCDisplayLinkDirector::startAnimation()
{
	if (m_bInvalid)
	{
		if (CCTime::gettimeofdayCocos2d(&s_obLastUpdate, NULL) != 0)
		{
			CCLOG("cocos2d: DisplayLinkDirector: Error on gettimeofday");
		}
		m_bInvalid = false;
		CCApplication::sharedApplication()->setAnimationInterval(m_dAnimationInterval);
	}
}

void CCDisplayLinkDirector::mainLoop()
{
	if (m_bPurgeDirecotorInNextLoop)
	{
		m_bPurgeDirecotorInNextLoop = false;
		purgeDirector();
	}
	else
	{
		if (!m_bPaused)
		{
			CCDirector::calculateDeltaTime();
			CCTime::gettimeofdayCocos2d(&s_obTickStart, NULL);
			if (m_nHandler)
			{
				if (CCScriptEngine::sharedEngine()->executeFunction(m_nHandler, 0) != 0)
				{
					CCDirector::unscheduleUpdateLua();
				}
			}
			if (!m_bInvalid)
			{
				m_pScheduler->update(m_fDeltaTime);
				m_fUpdateInterval = CCDirector::getInterval(s_obTickStart);
				CCDirector::drawScene();
				m_fDrawInterval = CCDirector::getInterval(s_obTickStart) - m_fUpdateInterval;
				// release the objects
				CCPoolManager::sharedPoolManager()->pop();
			}
		}
	}
}

void CCDisplayLinkDirector::stopAnimation()
{
	m_bInvalid = true;
}

void CCDisplayLinkDirector::setAnimationInterval(double dValue)
{
	m_dAnimationInterval = dValue;
	if (!m_bInvalid)
	{
		stopAnimation();
		startAnimation();
	}
}

NS_CC_END
