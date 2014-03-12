#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include "Dorothy.h"
using namespace Dorothy;
using namespace Dorothy::Platform;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

#if CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY
    std::vector<std::string> searchPaths;
    searchPaths.push_back("TestCppResources");
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
#endif
	/*
	oSharedContent.setGameFile("Resources.zip");
	oSharedContent.setPassword("pigyypigy");
	oSharedContent.setUsingGameFile(true);
	*/
	// register lua engine
	CCScriptEngine::setEngine(CCLuaEngine::defaultEngine());
	CCScriptEngine::sharedEngine()->executeScriptFile("luaScript/main.lua");

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
