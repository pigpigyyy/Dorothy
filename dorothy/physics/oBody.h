/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_PHYSICS_OBODY_H__
#define __DOROTHY_PHYSICS_OBODY_H__

NS_DOROTHY_BEGIN

class oBody;
class oSensor;
class oWorld;
class oBodyDef;
class oContact;
typedef b2FixtureDef oFixtureDef;

typedef Delegate<void(oBody* body,const oVec2& point,const oVec2& normal)> oContactHandler;
typedef Delegate<void(oSensor* sensor,oBody* body)> oSensorHandler;

class oBody: public CCNode
{
public:
	virtual ~oBody();
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void cleanup();
	PROPERTY_NAME(float, LinearDamping);
	PROPERTY_NAME(float, AngularDamping);
	PROPERTY_NAME(float, AngularRate);
	PROPERTY_NAME(CCObject*, Owner);
	PROPERTY_READONLY(oWorld*, World);
	PROPERTY_READONLY(oBodyDef*, BodyDef);
	PROPERTY_READONLY(b2Body*, B2Body);
	PROPERTY_READONLY(oVec2, Velocity);
	PROPERTY_READONLY(float, Mass);
	PROPERTY_NAME(float, VelocityX);
	PROPERTY_NAME(float, VelocityY);
	PROPERTY_VIRTUAL(int, _group, Group);
	PROPERTY_BOOL(_receivingContact, ReceivingContact);
	oContactHandler contactStart;
	oContactHandler contactEnd;
	oSensorHandler sensorAdded;
	void applyLinearImpulse(const oVec2& impulse, const oVec2& pos);
	void applyAngularImpulse(float impulse);
	void setVelocity(float x, float y);
	void setVelocity(const oVec2& velocity);
	void setPosition(float x, float y);
	virtual void setRotation(float var); 
	virtual void setPosition(const CCPoint& var);
	virtual CCRect getBoundingBox();
	oSensor* getSensorByTag(int tag);
	void eachSensor(const oSensorHandler& func);
	bool removeSensorByTag(int tag);
	bool removeSensor(oSensor* sensor);
	b2Fixture* attach(b2FixtureDef* fixtureDef);
	oSensor* attachSensor(int tag, b2FixtureDef* fixtureDef);
	bool isSensor() const;
	virtual void destroy();
	static oBody* create(oBodyDef* bodyDef, oWorld* world, const oVec2& pos = oVec2::zero, float rot = 0);
protected:
	oBody(oBodyDef* bodyDef, oWorld* world);
	b2Fixture* attachFixture(b2FixtureDef* fixtureDef);
	virtual void updatePhysics();
	b2Body* _bodyB2;// weak reference
	oWorld* _world;
private:
	oRef<oBodyDef> _bodyDef;
	oRef<CCArray> _sensors;
	oWRef<CCObject> _owner;
	friend class oWorld;
	CC_LUA_TYPE(oBody)
};

NS_DOROTHY_END

#endif // __DOROTHY_PHYSICS_OBODY_H__