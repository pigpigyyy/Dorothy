#ifndef __TESTCPP__BOX2DNODESTEST__
#define __TESTCPP__BOX2DNODESTEST__

#include "cocos2d.h"
using namespace cocos2d;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include "cocos-ext.h"
using namespace cocos2d::extension;
#include "Dorothy.h"
using namespace Dorothy;
using namespace Dorothy::Platform;

class MyWorld: public oWorld
{
public:
	~MyWorld();
	virtual bool init();
	void toExtensionsMainLayer(cocos2d::CCObject *sender);
	void onBodyEnter(oSensor* sensor, oBody* body);
	CREATE_FUNC(MyWorld);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
private:
	oRef<oBodyDef> _characterDef;
	oRef<oBody> _character;
	oRef<oModel> _model;
};

#endif // __TESTCPP__BOX2DNODESTEST__