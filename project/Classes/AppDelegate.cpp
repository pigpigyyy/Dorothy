#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "DorothyXml.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include "Dorothy.h"
using namespace Dorothy;
using namespace Dorothy::Platform;

USING_NS_CC;

AppDelegate::AppDelegate()
{ }

AppDelegate::~AppDelegate()
{
	SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
	CCDirector::sharedDirector()->setOpenGLView(CCEGLView::sharedOpenGLView());
	/*
	oSharedContent.setGameFile("Resources.zip");
	oSharedContent.setPassword("pigyypigy");
	oSharedContent.setUsingGameFile(true);
	*/
	// register lua engine
	CCScriptEngine::setEngine(CCLuaEngine::sharedEngine());
	string entry = CCUserDefault::sharedUserDefault()->getStringForKey("ScriptEntry");
	if (entry.empty())
	{
		CCUserDefault::sharedUserDefault()->setStringForKey("ScriptEntry", "main");
		entry = "main";
	}
	CCLOG("%s",oSharedXMLLoader.load("codes.xml").c_str());
	CCScriptEngine::sharedEngine()->executeScriptFile(entry.c_str());
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->pause();
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	CCApplication::applicationDidEnterBackground();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->resume();
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	CCApplication::applicationWillEnterForeground();
}
