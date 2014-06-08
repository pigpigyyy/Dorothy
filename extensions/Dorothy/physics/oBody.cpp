#include "Dorothy/const/oDefine.h"
#include "Dorothy/physics/oBody.h"
#include "Dorothy/physics/oBodyDef.h"
#include "Dorothy/physics/oWorld.h"
#include "Dorothy/physics/oSensor.h"

NS_DOROTHY_BEGIN

oBody::oBody(oBodyDef* bodyDef, oWorld* world):
_bodyB2(nullptr),
_bodyDef(bodyDef),
_world(world),
_group(0),
_isDestroyed(false)
{
	_bodyB2 = world->getB2World()->CreateBody(_bodyDef);
	_bodyB2->SetUserData((void*)this);
	for (b2FixtureDef* fixtureDef : _bodyDef->getFixtureDefs())
	{
		if (fixtureDef->isSensor)
		{
			oBody::attachSensor((int)fixtureDef->userData, fixtureDef);
		}
		else
		{
			oBody::attach(fixtureDef);
		}
	}
}

oBody::~oBody()
{
	if (_bodyB2)
	{
		_world->getB2World()->DestroyBody(_bodyB2);
		_bodyB2 = nullptr;
	}
}

void oBody::onEnter()
{
	CCNode::onEnter();
	_bodyB2->SetActive(true);
}

void oBody::onExit()
{
	CCNode::onExit();
	_bodyB2->SetActive(false);//Set active false to trigger sensor`s unit leave event.
}

oBodyDef* oBody::getBodyDef() const
{
	return _bodyDef;
}

oBody* oBody::create(oBodyDef* bodyDef, oWorld* world)
{
	oBody* body = new oBody(bodyDef, world);
	body->autorelease();
	return body;
}

oWorld* oBody::getWorld() const
{
	return _world;
}

b2Body* oBody::getB2Body() const
{
	return _bodyB2;
}

oSensor* oBody::getSensorByTag( int tag )
{
	CCObject* object;
	CCARRAY_FOREACH(_sensors, object)
	{
		oSensor* sensor = (oSensor*)object;
		if (sensor->getTag() == tag)
		{
			return sensor;
		}
	}
	return nullptr;
}

bool oBody::removeSensorByTag( int tag )
{
	oSensor* sensor = oBody::getSensorByTag(tag);
	return oBody::removeSensor(sensor);
}

bool oBody::removeSensor( oSensor* sensor )
{
	if (_sensors && sensor && sensor->getFixture()->GetBody() == _bodyB2)
	{
		_bodyB2->DestroyFixture(sensor->getFixture());
		_sensors->removeObject(sensor);
		return true;
	}
	return false;
}

void oBody::setVelocity( float x, float y )
{
	_bodyB2->SetLinearVelocity(b2Vec2(oWorld::b2Val(x), oWorld::b2Val(y)));
}

void oBody::setVelocity( const oVec2& velocity )
{
	_bodyB2->SetLinearVelocity(oWorld::b2Val(velocity));
}

oVec2 oBody::getVelocity() const
{
	return oWorld::oVal(_bodyB2->GetLinearVelocity());
}

void oBody::setAngularRate(float var)
{
	_bodyB2->SetAngularVelocity(CC_DEGREES_TO_RADIANS(var));
}

float oBody::getAngularRate() const
{
	return CC_RADIANS_TO_DEGREES(_bodyB2->GetAngularVelocity());
}

void oBody::setLinearDamping(float var)
{
	_bodyB2->SetLinearDamping(var);
}

float oBody::getLinearDamping() const
{
	return _bodyB2->GetLinearDamping();
}

void oBody::setAngularDamping(float var)
{
	_bodyB2->SetAngularDamping(var);
}

float oBody::getAngularDamping() const
{
	return _bodyB2->GetAngularDamping();
}

void oBody::setGroup( int group )
{
	_group = group;
	for (b2Fixture* f = _bodyB2->GetFixtureList();f;f = f->GetNext())
	{
		f->SetFilterData(_world->getFilter(group));
	}
}

int oBody::getGroup() const
{
	return _group;
}

void oBody::applyLinearImpulse(const oVec2& impulse, const oVec2& pos)
{
	_bodyB2->ApplyLinearImpulse(impulse, pos);
}

void oBody::applyAngularImpulse(float impulse)
{
	_bodyB2->ApplyAngularImpulse(impulse);
}

b2Fixture* oBody::attach( b2FixtureDef* fixtureDef )
{
	fixtureDef->filter = _world->getFilter(_group);
	b2Fixture* fixture = _bodyB2->CreateFixture(fixtureDef);
	return fixture;
}

oSensor* oBody::attachSensor( int tag, b2FixtureDef* fixtureDef )
{
	fixtureDef->filter = _world->getFilter(_group);
	fixtureDef->isSensor = true;
	b2Fixture* fixture = _bodyB2->CreateFixture(fixtureDef);
	oSensor* sensor = oSensor::create(this, tag, fixture);
	fixture->SetUserData((void*)sensor);
	if (!_sensors) _sensors = CCArray::create();
	_sensors->addObject(sensor);
	return sensor;
}

void oBody::setVelocityX( float x )
{
	_bodyB2->SetLinearVelocityX(oWorld::b2Val(x));
}

float oBody::getVelocityX() const
{
	return oWorld::oVal(_bodyB2->GetLinearVelocityX());
}

void oBody::setVelocityY( float y )
{
	_bodyB2->SetLinearVelocityY(oWorld::b2Val(y));
}

float oBody::getVelocityY() const
{
	return oWorld::oVal(_bodyB2->GetLinearVelocityY());
}

void oBody::setPosition( const CCPoint& var )
{
	if (var != CCNode::getPosition())
	{
		CCNode::setPosition(var);
		_bodyB2->SetTransform(oWorld::b2Val(var), _bodyB2->GetAngle());
	}
}

void oBody::setRotation( float var )
{
	if (var != CCNode::getRotation())
	{
		CCNode::setRotation(var);
		_bodyB2->SetTransform(_bodyB2->GetPosition(), -CC_DEGREES_TO_RADIANS(var));
	}
}

void oBody::setPosition( float x, float y )
{
	this->setPosition(CCPoint(x,y));
}

void oBody::updatePhysics()
{
	if (_bodyB2->IsAwake())
	{
		const b2Vec2& pos = _bodyB2->GetPosition();
		/* Here only CCNode::setPosition(const CCPoint& var) work for modify CCNode`s position.
		 Other positioning functions have been overridden by CCBody`s.
		*/
		CCNode::setPosition(CCPoint(oWorld::oVal(pos.x), oWorld::oVal(pos.y)));
		float angle = _bodyB2->GetAngle();
		CCNode::setRotation(-CC_RADIANS_TO_DEGREES(angle));
	}
}

void oBody::destroy()
{
	if (!_isDestroyed)
	{
		_isDestroyed = true;
		m_pParent->removeChild(this, true);
	}
}

NS_DOROTHY_END
