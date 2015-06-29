/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "physics/oJoint.h"
#include "physics/oJointDef.h"
#include "physics/oBody.h"
#include "physics/oWorld.h"
#include "physics/oSensor.h"

NS_DOROTHY_BEGIN

oJoint::~oJoint()
{
	oJoint::destroy();
}

b2Joint* oJoint::getB2Joint()
{
	return _joint;
}

oWorld* oJoint::getWorld()
{
	return _world;
}

void oJoint::destroy()
{
	if (_world && _joint)
	{
		_world->getB2World()->DestroyJoint(_joint);
		_world = nullptr;
		_joint = nullptr;
	}
}

oJoint* oJoint::create(oJointDef* def, CCDictionary* itemDict)
{
	return def->toJoint(itemDict);
}

oJoint* oJoint::distance(
	bool collideConnected,
	oBody* bodyA, oBody* bodyB,
	const oVec2& anchorA, const oVec2& anchorB,
	float frequency, float damping)
{
	if (bodyA->getWorld() != bodyB->getWorld())
	{
		return nullptr;
	}
	b2Body* bA = bodyA->getB2Body();
	b2Body* bB = bodyB->getB2Body();
	b2Vec2 aA = oWorld::b2Val(anchorA);
	b2Vec2 aB = oWorld::b2Val(anchorB);
	b2DistanceJointDef jointDef;
	jointDef.Initialize(bA, bB,
		bA->GetWorldPoint(aA),
		bB->GetWorldPoint(aB));
	jointDef.frequencyHz = frequency;
	jointDef.dampingRatio = damping;
	jointDef.collideConnected = collideConnected;
	oJoint* joint = new oJoint();
	CC_INIT(joint);
	joint->_world = bodyA->getWorld();
	joint->_joint = joint->_world->getB2World()->CreateJoint(&jointDef);
	joint->_joint->SetUserData((void*)joint);
	joint->autorelease();
	return joint;
}

oJoint* oJoint::friction(
	bool collideConnected,
	oBody* bodyA,
	oBody* bodyB,
	const oVec2& worldAnchor,
	float maxForce,
	float maxTorque)
{
	if (bodyA->getWorld() != bodyB->getWorld())
	{
		return nullptr;
	}
	b2Body* bA = bodyA->getB2Body();
	b2Body* bB = bodyB->getB2Body();
	b2Vec2 a = oWorld::b2Val(worldAnchor);
	b2FrictionJointDef jointDef;
	jointDef.Initialize(bA, bB, a);
	jointDef.maxForce = maxForce;
	jointDef.maxTorque = maxTorque;
	jointDef.collideConnected = collideConnected;
	oJoint* joint = new oJoint();
	CC_INIT(joint);
	joint->_world = bodyA->getWorld();
	joint->_joint = joint->_world->getB2World()->CreateJoint(&jointDef);
	joint->_joint->SetUserData((void*)joint);
	joint->autorelease();
	return joint;
}

oJoint* oJoint::gear(
	bool collideConnected,
	oJoint* jointA,
	oJoint* jointB,
	float ratio)
{
	if (jointA->getWorld() != jointA->getWorld())
	{
		return nullptr;
	}
	b2GearJointDef jointDef;
	jointDef.joint1 = jointA->getB2Joint();
	jointDef.joint2 = jointB->getB2Joint();
	jointDef.bodyA = jointDef.joint1->GetBodyB();
	jointDef.bodyB = jointDef.joint2->GetBodyB();
	jointDef.ratio = ratio;
	jointDef.collideConnected = collideConnected;
	oJoint* joint = new oJoint();
	CC_INIT(joint);
	joint->_world = jointA->getWorld();
	joint->_joint = joint->_world->getB2World()->CreateJoint(&jointDef);
	joint->_joint->SetUserData((void*)joint);
	joint->autorelease();
	return joint;
}

oJoint* oJoint::spring(
	bool collideConnected,
	oBody* bodyA,
	oBody* bodyB,
	oVec2 linearOffset,
	float angularOffset,
	float maxForce,
	float maxTorque,
	float correctionFactor)
{
	if (bodyA->getWorld() != bodyB->getWorld())
	{
		return nullptr;
	}
	b2Body* bA = bodyA->getB2Body();
	b2Body* bB = bodyB->getB2Body();
	b2MotorJointDef jointDef;
	jointDef.Initialize(bA, bB);
	jointDef.linearOffset = oWorld::b2Val(linearOffset);
	jointDef.angularOffset = -CC_DEGREES_TO_RADIANS(angularOffset);
	jointDef.maxForce = maxForce;
	jointDef.maxTorque = maxTorque;
	jointDef.correctionFactor = correctionFactor;
	jointDef.collideConnected = collideConnected;
	oJoint* joint = new oJoint();
	CC_INIT(joint);
	joint->_world = bodyA->getWorld();
	joint->_joint = joint->_world->getB2World()->CreateJoint(&jointDef);
	joint->_joint->SetUserData((void*)joint);
	joint->autorelease();
	return joint;
}

oMoveJoint* oJoint::move(
	bool collideConnected,
	oBody* bodyA,
	oBody* bodyB,
	const oVec2& target,
	float maxForce,
	float frequency,
	float damping)
{
	if (bodyA->getWorld() != bodyB->getWorld())
	{
		return nullptr;
	}
	b2Body* bA = bodyA->getB2Body();
	b2Body* bB = bodyB->getB2Body();
	b2MouseJointDef jointDef;
	jointDef.bodyA = bA;
	jointDef.bodyB = bB;
	jointDef.target = oWorld::b2Val(target);
	jointDef.maxForce = maxForce;
	jointDef.frequencyHz = frequency;
	jointDef.dampingRatio = damping;
	jointDef.collideConnected = collideConnected;
	oMoveJoint* joint = new oMoveJoint();
	CC_INIT(joint);
	joint->_world = bodyA->getWorld();
	joint->_joint = joint->_world->getB2World()->CreateJoint(&jointDef);
	joint->_joint->SetUserData((void*)joint);
	joint->autorelease();
	return joint;
}

oMotorJoint* oJoint::prismatic(
	bool collideConnected,
	oBody* bodyA,
	oBody* bodyB,
	const oVec2& worldAnchor,
	const oVec2& axis,
	float lowerTranslation,
	float upperTranslation,
	float maxMotorForce,
	float motorSpeed)
{
	if (bodyA->getWorld() != bodyB->getWorld())
	{
		return nullptr;
	}
	b2Body* bA = bodyA->getB2Body();
	b2Body* bB = bodyB->getB2Body();
	b2Vec2 a = oWorld::b2Val(worldAnchor);
	b2PrismaticJointDef jointDef;
	jointDef.Initialize(bA, bB, a, axis);
	jointDef.lowerTranslation = oWorld::b2Val(lowerTranslation);
	jointDef.upperTranslation = oWorld::b2Val(upperTranslation);
	jointDef.enableLimit = (lowerTranslation || upperTranslation) && (lowerTranslation <= upperTranslation);
	jointDef.maxMotorForce = maxMotorForce;
	jointDef.motorSpeed = motorSpeed;
	jointDef.collideConnected = collideConnected;
	oMotorJoint* joint = new oMotorJoint();
	CC_INIT(joint);
	joint->_world = bodyA->getWorld();
	joint->_joint = joint->_world->getB2World()->CreateJoint(&jointDef);
	joint->_joint->SetUserData((void*)joint);
	joint->autorelease();
	return joint;
}

oJoint* oJoint::pulley(
	bool collideConnected,
	oBody* bodyA,
	oBody* bodyB,
	const oVec2& anchorA,
	const oVec2& anchorB,
	const oVec2& groundAnchorA,
	const oVec2& groundAnchorB,
	float32 ratio)
{
	if (bodyA->getWorld() != bodyB->getWorld())
	{
		return nullptr;
	}
	b2Body* bA = bodyA->getB2Body();
	b2Body* bB = bodyB->getB2Body();
	b2Vec2 aA = oWorld::b2Val(anchorA);
	b2Vec2 aB = oWorld::b2Val(anchorB);
	aA = bA->GetWorldPoint(aA);
	aB = bB->GetWorldPoint(aB);
	b2Vec2 gA = oWorld::b2Val(groundAnchorA);
	b2Vec2 gB = oWorld::b2Val(groundAnchorB);
	b2PulleyJointDef jointDef;
	jointDef.Initialize(bA, bB, gA, gB, aA, aB, ratio);
	jointDef.collideConnected = collideConnected;
	oJoint* joint = new oJoint();
	CC_INIT(joint);
	joint->_world = bodyA->getWorld();
	joint->_joint = joint->_world->getB2World()->CreateJoint(&jointDef);
	joint->_joint->SetUserData((void*)joint);
	joint->autorelease();
	return joint;
}

oMotorJoint* oJoint::revolute(
	bool collideConnected,
	oBody* bodyA,
	oBody* bodyB,
	const oVec2& worldPos,
	float lowerAngle,
	float upperAngle,
	float maxMotorTorque,
	float motorSpeed)
{
	if (bodyA->getWorld() != bodyB->getWorld())
	{
		return nullptr;
	}
	b2Body* bA = bodyA->getB2Body();
	b2Body* bB = bodyB->getB2Body();
	b2Vec2 a = oWorld::b2Val(worldPos);
	lowerAngle = -CC_DEGREES_TO_RADIANS(lowerAngle);
	upperAngle = -CC_DEGREES_TO_RADIANS(upperAngle);
	motorSpeed = -CC_DEGREES_TO_RADIANS(motorSpeed);
	b2RevoluteJointDef jointDef;
	jointDef.Initialize(bA, bB, a);
	jointDef.lowerAngle = upperAngle;
	jointDef.upperAngle = lowerAngle;
	jointDef.enableLimit = (lowerAngle || upperAngle) && (lowerAngle >= upperAngle);
	jointDef.maxMotorTorque = maxMotorTorque;
	jointDef.motorSpeed = motorSpeed;
	jointDef.collideConnected = collideConnected;
	oMotorJoint* joint = new oMotorJoint();
	CC_INIT(joint);
	joint->_world = bodyA->getWorld();
	joint->_joint = joint->_world->getB2World()->CreateJoint(&jointDef);
	joint->_joint->SetUserData((void*)joint);
	joint->autorelease();
	return joint;
}

oJoint* oJoint::rope(
	bool collideConnected,
	oBody* bodyA,
	oBody* bodyB,
	const oVec2& anchorA,
	const oVec2& anchorB,
	float maxLength)
{
	if (bodyA->getWorld() != bodyB->getWorld())
	{
		return nullptr;
	}
	b2Body* bA = bodyA->getB2Body();
	b2Body* bB = bodyB->getB2Body();
	b2Vec2 aA = oWorld::b2Val(anchorA);
	b2Vec2 aB = oWorld::b2Val(anchorB);
	b2RopeJointDef jointDef;
	jointDef.bodyA = bA;
	jointDef.bodyB = bB;
	jointDef.localAnchorA = aA;
	jointDef.localAnchorB = aB;
	jointDef.maxLength = oWorld::b2Val(maxLength);
	jointDef.collideConnected = collideConnected;
	oJoint* joint = new oJoint();
	CC_INIT(joint);
	joint->_world = bodyA->getWorld();
	joint->_joint = joint->_world->getB2World()->CreateJoint(&jointDef);
	joint->_joint->SetUserData((void*)joint);
	joint->autorelease();
	return joint;
}

oJoint* oJoint::weld(
	bool collideConnected,
	oBody* bodyA,
	oBody* bodyB,
	const oVec2& worldPos,
	float frequency,
	float damping)
{
	if (bodyA->getWorld() != bodyB->getWorld())
	{
		return nullptr;
	}
	b2Body* bA = bodyA->getB2Body();
	b2Body* bB = bodyB->getB2Body();
	b2Vec2 a = oWorld::b2Val(worldPos);
	b2WeldJointDef jointDef;
	jointDef.Initialize(bA, bB, a);
	jointDef.frequencyHz = frequency;
	jointDef.dampingRatio = damping;
	jointDef.collideConnected = collideConnected;
	oJoint* joint = new oJoint();
	CC_INIT(joint);
	joint->_world = bodyA->getWorld();
	joint->_joint = joint->_world->getB2World()->CreateJoint(&jointDef);
	joint->_joint->SetUserData((void*)joint);
	joint->autorelease();
	return joint;
}

oMotorJoint* oJoint::wheel(
	bool collideConnected,
	oBody* bodyA,
	oBody* bodyB,
	const oVec2& worldPos,
	const oVec2& axis,
	float maxMotorTorque,
	float motorSpeed,
	float frequency,
	float damping)
{
	if (bodyA->getWorld() != bodyB->getWorld())
	{
		return nullptr;
	}
	b2Body* bA = bodyA->getB2Body();
	b2Body* bB = bodyB->getB2Body();
	b2Vec2 a = oWorld::b2Val(worldPos);
	b2WheelJointDef jointDef;
	jointDef.Initialize(bA, bB, a, axis);
	jointDef.maxMotorTorque = maxMotorTorque;
	jointDef.motorSpeed = oWorld::b2Val(motorSpeed);
	jointDef.frequencyHz = frequency;
	jointDef.dampingRatio = damping;
	jointDef.collideConnected = collideConnected;
	oMotorJoint* joint = new oMotorJoint();
	CC_INIT(joint);
	joint->_world = bodyA->getWorld();
	joint->_joint = joint->_world->getB2World()->CreateJoint(&jointDef);
	joint->_joint->SetUserData((void*)joint);
	joint->autorelease();
	return joint;
}

void oMoveJoint::setPosition(const oVec2& targetPos)
{
	if (!_joint) return;
	_position = targetPos;
	b2MouseJoint* joint = (b2MouseJoint*)_joint;
	joint->SetTarget(oWorld::b2Val(targetPos));
}
const oVec2& oMoveJoint::getPosition() const
{
	return _position;
}

void oMotorJoint::setEnabled(bool var)
{
	if (!_joint) return;
	switch (_joint->GetType())
	{
	case e_prismaticJoint:
		((b2PrismaticJoint*)_joint)->EnableMotor(var);
		break;
	case e_revoluteJoint:
		((b2RevoluteJoint*)_joint)->EnableMotor(var);
		break;
	case e_wheelJoint:
		((b2WheelJoint*)_joint)->EnableMotor(var);
		break;
    default:
        break;
	}
}
bool oMotorJoint::isEnabled() const
{
	if (!_joint) return false;
	switch (_joint->GetType())
	{
	case e_prismaticJoint:
		return ((b2PrismaticJoint*)_joint)->IsMotorEnabled();
	case e_revoluteJoint:
		return ((b2RevoluteJoint*)_joint)->IsMotorEnabled();
	case e_wheelJoint:
		return ((b2WheelJoint*)_joint)->IsMotorEnabled();
    default:
        break;

	}
	return false;
}

void oMotorJoint::setForce(float var)
{
	if (!_joint) return;
	var = MAX(var, 0);
	switch (_joint->GetType())
	{
	case e_prismaticJoint:
		((b2PrismaticJoint*)_joint)->SetMaxMotorForce(var);
		break;
	case e_revoluteJoint:
		((b2RevoluteJoint*)_joint)->SetMaxMotorTorque(var);
		break;
	case e_wheelJoint:
		((b2WheelJoint*)_joint)->SetMaxMotorTorque(var);
        break;
    default:
        break;
	}
}
float oMotorJoint::getForce() const
{
	if (!_joint) return 0.0f;
	switch (_joint->GetType())
	{
	case e_prismaticJoint:
		return ((b2PrismaticJoint*)_joint)->GetMaxMotorForce();
	case e_revoluteJoint:
		return ((b2RevoluteJoint*)_joint)->GetMaxMotorTorque();
	case e_wheelJoint:
		return ((b2WheelJoint*)_joint)->GetMaxMotorTorque();
    default:
		return 0.0f;
	}
}

void oMotorJoint::setSpeed(float var)
{
	if (!_joint) return;
	var = -CC_DEGREES_TO_RADIANS(var);
	switch (_joint->GetType())
	{
	case e_prismaticJoint:
		((b2PrismaticJoint*)_joint)->SetMotorSpeed(var);
		break;
	case e_revoluteJoint:
		((b2RevoluteJoint*)_joint)->SetMotorSpeed(var);
		break;
	case e_wheelJoint:
		((b2WheelJoint*)_joint)->SetMotorSpeed(var);
        break;
    default:
        break;
	}
}
float oMotorJoint::getSpeed() const
{
	if (!_joint) return 0.0f;
	float speed = 0.0f;
	switch (_joint->GetType())
	{
	case e_prismaticJoint:
		speed = ((b2PrismaticJoint*)_joint)->GetMotorSpeed();
	case e_revoluteJoint:
		speed = ((b2RevoluteJoint*)_joint)->GetMotorSpeed();
	case e_wheelJoint:
		speed = ((b2WheelJoint*)_joint)->GetMotorSpeed();
    default:
        break;
	}
	return -CC_RADIANS_TO_DEGREES(speed);
}

void oMotorJoint::reversePower()
{
	oMotorJoint::setSpeed(-oMotorJoint::getSpeed());
}

NS_DOROTHY_END
