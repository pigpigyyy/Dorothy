#include "Box2DNodesTest.h"

int GROUP_TERRAIN;
int GROUP_ONE;
int GROUP_TWO;
int GROUP_TEST_SENSOR;
int TAG_GROUND_SENSOR;

MyWorld::~MyWorld()
{
	_character = nullptr;
}

bool MyWorld::init()
{
	if (!oWorld::init())
	{
		return false;
	}

	this->setTouchEnabled(true);

	// Create Back Menu
	CCPoint visibleOrigin = CCEGLView::sharedOpenGLView()->getVisibleOrigin();
	CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
	CCMenuItemFont *itemBack = CCMenuItemFont::create("Back", this, menu_selector(MyWorld::toExtensionsMainLayer));
	itemBack->setPosition(ccp(visibleOrigin.x+visibleSize.width - 50, visibleOrigin.y+25));
	CCMenu *menuBack = CCMenu::create(itemBack, NULL);
	menuBack->setPosition(CCPointZero);
	this->addChild(menuBack);

	// Set Contact Info
	/* By default all groups won`t collide each other.
	 You could set the contact info before game start or
	 change it later.
	 Group number can only be 0 to 15.
	*/
	GROUP_TERRAIN = 0;
	GROUP_ONE = 1;
	GROUP_TWO = 2;
	GROUP_TEST_SENSOR = 15;
	this->setShouldContact(GROUP_TERRAIN, GROUP_TERRAIN, true);
	this->setShouldContact(GROUP_TWO, GROUP_TERRAIN, true);
	this->setShouldContact(GROUP_TEST_SENSOR, GROUP_ONE, true);// Body from GROUP_ONE will be detected by test sensor.

	// Create Borders
	oBodyDef* bodyDef = oBodyDef::create();
	bodyDef->type = b2_staticBody;
	vector<oVec2> vertices(5);
	vertices[0].set(0, 0);
	vertices[1].set(visibleSize.width, 0);
	vertices[2].set(visibleSize.width, visibleSize.height);
	vertices[3].set(0, visibleSize.height);
	vertices[4].set(0, 0);
	bodyDef->attachChain(vertices, 0.4f, 0.4f);
	oBody* body = bodyDef->toBody(this, GROUP_TERRAIN, 0, 0, 0);
	CCSprite* sprite = CCSprite::create("Icon.png");
	sprite->setPosition(ccp(100,40));
	body->addChild(sprite);
	this->addChild(body);

	// Create Body
	sprite = CCSprite::create("Icon.png");
	CCSize size = sprite->getContentSize();
	bodyDef = oBodyDef::create();
	bodyDef->type = b2_dynamicBody;
	bodyDef->attachPolygon(size.width, size.height, 1.0f, 0.4f, 0.4f);//Body define use bodyDef->attach
	body = bodyDef->toBody(this, GROUP_ONE, visibleSize.width*0.5f-20.0f, visibleSize.height*0.5f+20.0f, 50.0f);
	//body->attach(CCBodyDef::polygon(size.width, size.height, 1.0f, 0.4f, 0.4f)); //Body instance use body->attach
	body->addChild(sprite);
	this->addChild(body);

	body = bodyDef->toBody(this, GROUP_TERRAIN, visibleSize.width*0.5f+50.0f, visibleSize.height*0.5f+20.0f);
	sprite = CCSprite::create("Icon.png");
	body->addChild(sprite);
	this->addChild(body);

	// Create Test Sensor
	int SENSOR_TAG = 1;
	bodyDef = oBodyDef::create();
	bodyDef->type = b2_staticBody;
	//bodyDef->attachPolygonSensor(SENSOR_TAG, visibleSize.width, 40.0f);
	body = bodyDef->toBody(this, GROUP_TEST_SENSOR, visibleSize.width*0.5f, 20.0f);
	//CCSensor* sensor = body->getSensorByTag(SENSOR_TAG);
	oSensor* sensor = body->attachSensor(SENSOR_TAG, oBodyDef::polygon(visibleSize.width, 40.0f));

	oSharedEffectCache.load("main.effect");

	sensor->bodyEnter += [&](oSensor* sensor, oBody* body)
	{
		// When body enters sensor area, remove the body
		//body->getParent()->removeChild(body);
		this->query(CCRect(0.0f,0.0f,100.0f,100.0f), [&](oBody* body)
		{
			if (body->getGroup() != GROUP_TERRAIN)
			{
				body->getParent()->removeChild(body);
				return true;
			}
			return false;
		});
		// Create a jumping character using its def
		_character = _characterDef->toBody(this, GROUP_TWO, 100.0f, 200.0f);
		oModel* model = oModel::create("jiandunA.model");
		model->setLook("happy");
		model->play("walk");
		model->setLoop(true);
		_character->addChild(model);
		//this->getCamera()->setFollowRatio(ccp(0.1f,0.1f));
		//this->getCamera()->follow(_character);
		this->addChild(_character);

		oEffect::create(1)->attachTo(_character)->autoRemove()->start();
	};
	//sensor->bodyEnter += std::make_pair(this, &MyWorld::onBodyEnter);
	this->addChild(body);

	/* Create a Platform Character`s Define
	 (The method to make a platform character will be included in
	 Box2D Nodes extension in the future)
	*/
	TAG_GROUND_SENSOR = 2;
	float BOTTOM_OFFSET = 4.0f;
	float GROUND_SENSOR_HEIGHT = 4.0f;
	size.setSize(65,116);//The physical size of our character
	_characterDef = oBodyDef::create();
	_characterDef->type = b2_dynamicBody;
	//_characterDef->fixedRotation = true;
	float hw = size.width * 0.5f;
	float hh = size.height * 0.5f;
	oVec2 verts[] =
	{
		oVec2(-hw, hh),
		oVec2(-hw + BOTTOM_OFFSET, -hh),
		oVec2(hw - BOTTOM_OFFSET, -hh),
		oVec2(hw, hh)
	};
	_characterDef->attachPolygon(verts, 4, 1.0f, 0.4f, 0.4f);
	_characterDef->attachPolygonSensor(
		TAG_GROUND_SENSOR,
		size.width - BOTTOM_OFFSET * 2,
		GROUND_SENSOR_HEIGHT,
		b2Vec2(0, -hh - GROUND_SENSOR_HEIGHT * 0.5f));

	sprite = CCSprite::create("Icon.png");
	//sprite->setOpacity(0);

	sprite->runAction(
		oSequence::create(
			CCSpawn::create(
				oKeyPos::create(2.0f, 300.0f, 300.0f, oEase::OutBack),
				oKeyScale::create(2.0f, 3.0f, 3.0f, oEase::InOutElastic),
				nullptr),
			CCSpawn::create(
				oKeyPos::create(2.0f, 100.0f, 100.0f, oEase::OutBack),
				oKeyScale::create(2.0f, 1.0f, 1.0f, oEase::InOutElastic),
				nullptr),
			nullptr));
	this->addChild(sprite);

	//this->getCamera()->setBoudary(CCRectMake(-1000, -1000, 2000, 2000));

	sprite = CCSprite::create("Icon.png");
	sprite->setScale(100.0f);
	this->addChild(sprite, -100);
	//this->setLayerRatio(-100, ccp(-1.5f, -1.5f));
/*
	CCSpriteBatchNode* batchNode = CCSpriteBatchNode::createWithTexture(CCTextureCache::sharedTextureCache()->addImage("Images/grossini.png"));
	sprite = CCSprite::create("Images/grossini.png");
	CCSprite* childSp = CCSprite::create("Images/grossini.png");
	childSp->setRotation(45.0f);
	childSp->setPosition(ccp(20,30));
	sprite->addChild(childSp);
	batchNode->addChild(sprite);
	this->addChild(batchNode);*/

	oModelDef* modelDef = oSharedModelCache.load("jixienv.model");
	_model = modelDef->toModel();
	_model->setPosition(ccp(200,200));
	_model->setRecovery(0.2f);
	_model->setFaceRight(false);
	_model->setLook("happy");
	_model->setLoop(true);
	_model->play("walk");
	this->addChild(_model);

	return true;
}

void MyWorld::toExtensionsMainLayer( cocos2d::CCObject *sender )
{
	CCDirector::sharedDirector()->end();
}

void MyWorld::onBodyEnter( oSensor* sensor, oBody* body )
{
	// When body enters sensor area, remove the body
	body->getParent()->removeChild(body);

	// Create a jumping character using its def
	_character = _characterDef->toBody(this, GROUP_TWO, 100.0f, 200.0f);
	oModel* model = oModel::create("jiandunA.model");
	model->setLook("happy");
	model->play("walk");
	model->setLoop(true);
	_character->addChild(model);
	this->addChild(_character);
}

void MyWorld::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
	// Control the game`s time speed, 1.0f - normal, 2.0f - two times faster
	if (CCDirector::sharedDirector()->getUpdateRate() < 1.0f)
	{
		CCDirector::sharedDirector()->setUpdateRate(1.0f);
	}
	else
	{
		CCDirector::sharedDirector()->setUpdateRate(0.1f);
	}
	//_model->play("attack");
	if (!_character)
	{
		return;
	}
	//_character->setZOrder(-99999);
	//this->setShouldContact(GROUP_TWO, GROUP_TERRAIN, false); // Touch to make grossini fall in void
	// Touch the place over grossini to make him jump
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	CCPoint touchPos = touch->getLocation();
	oSensor* groundSensor = _character->getSensorByTag(TAG_GROUND_SENSOR);
	if (groundSensor->getSensedBodies()->count() > 0)
	{
		if (touchPos.x > _character->getPositionX())
		{
			_character->setVelocityX(400.0f);
		}
		else
		{
			_character->setVelocityX(-400.0f);
		}
		if (touchPos.y > _character->getPositionY() + 116*0.5f)
		{
			_character->setVelocityY(400.0f);
		}
	}
}

