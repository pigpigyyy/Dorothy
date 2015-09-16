/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "physics/oJointDef.h"
#include "physics/oJoint.h"
#include "physics/oBody.h"

NS_DOROTHY_BEGIN

oJointDef::oJointDef(): angle(0) { }

oJointDef* oJointDef::distance(
	bool collision,
	const string& bodyA,
	const string& bodyB,
	const oVec2& anchorA,
	const oVec2& anchorB,
	float frequency,
	float damping)
{
	oDistanceDef* def = new oDistanceDef();
	def->collision = collision;
	def->bodyA = bodyA;
	def->bodyB = bodyB;
	def->anchorA = anchorA;
	def->anchorB = anchorB;
	def->frequency = frequency;
	def->damping = damping;
	def->autorelease();
	return def;
}

oJointDef* oJointDef::friction(
	bool collision,
	const string& bodyA,
	const string& bodyB,
	const oVec2& worldPos,
	float maxForce,
	float maxTorque)
{
	oFrictionDef* def = new oFrictionDef();
	def->collision = collision;
	def->bodyA = bodyA;
	def->bodyB = bodyB;
	def->worldPos = worldPos;
	def->maxForce = maxForce;
	def->maxTorque = maxTorque;
	def->autorelease();
	return def;
}

oJointDef* oJointDef::gear(
	bool collision,
	const string& jointA,
	const string& jointB,
	float ratio)
{
	oGearDef* def = new oGearDef();
	def->collision = collision;
	def->jointA = jointA;
	def->jointB = jointB;
	def->ratio = ratio;
	def->autorelease();
	return def;
}

oJointDef* oJointDef::spring(
	bool collision,
	const string& bodyA,
	const string& bodyB,
	const oVec2& linearOffset,
	float angularOffset,
	float maxForce,
	float maxTorque,
	float correctionFactor)
{
	oSpringDef* def = new oSpringDef();
	def->collision = collision;
	def->bodyA = bodyA;
	def->bodyB = bodyB;
	def->linearOffset = linearOffset;
	def->angularOffset = angularOffset;
	def->maxForce = maxForce;
	def->maxTorque = maxTorque;
	def->correctionFactor = correctionFactor;
	def->autorelease();
	return def;
}

oJointDef* oJointDef::prismatic(
	bool collision,
	const string& bodyA,
	const string& bodyB,
	const oVec2& worldPos,
	const oVec2& axis,
	float lowerTranslation,
	float upperTranslation,
	float maxMotorForce,
	float motorSpeed)
{
	oPrismaticDef* def = new oPrismaticDef();
	def->collision = collision;
	def->bodyA = bodyA;
	def->bodyB = bodyB;
	def->worldPos = worldPos;
	def->axis = axis;
	def->lowerTranslation = lowerTranslation;
	def->upperTranslation = upperTranslation;
	def->maxMotorForce = maxMotorForce;
	def->motorSpeed = motorSpeed;
	def->autorelease();
	return def;
}

oJointDef* oJointDef::pulley(
	bool collision,
	const string& bodyA,
	const string& bodyB,
	const oVec2& anchorA,
	const oVec2& anchorB,
	const oVec2& groundAnchorA,
	const oVec2& groundAnchorB,
	float ratio)
{
	oPulleyDef* def = new oPulleyDef();
	def->collision = collision;
	def->bodyA = bodyA;
	def->bodyB = bodyB;
	def->anchorA = anchorA;
	def->anchorB = anchorB;
	def->groundAnchorA = groundAnchorA;
	def->groundAnchorB = groundAnchorB;
	def->ratio = ratio;
	def->autorelease();
	return def;
}

oJointDef* oJointDef::revolute(
	bool collision,
	const string& bodyA,
	const string& bodyB,
	const oVec2& worldPos,
	float lowerAngle,
	float upperAngle,
	float maxMotorTorque,
	float motorSpeed)
{
	oRevoluteDef* def = new oRevoluteDef();
	def->collision = collision;
	def->bodyA = bodyA;
	def->bodyB = bodyB;
	def->worldPos = worldPos;
	def->lowerAngle = lowerAngle;
	def->upperAngle = upperAngle;
	def->maxMotorTorque = maxMotorTorque;
	def->motorSpeed = motorSpeed;
	def->autorelease();
	return def;
}

oJointDef* oJointDef::rope(
	bool collision,
	const string& bodyA,
	const string& bodyB,
	const oVec2& anchorA,
	const oVec2& anchorB,
	float maxLength)
{
	oRopeDef* def = new oRopeDef();
	def->collision = collision;
	def->bodyA = bodyA;
	def->bodyB = bodyB;
	def->anchorA = anchorA;
	def->anchorB = anchorB;
	def->maxLength = maxLength;
	def->autorelease();
	return def;
}

oJointDef* oJointDef::weld(
	bool collision,
	const string& bodyA,
	const string& bodyB,
	const oVec2& worldPos,
	float frequency,
	float damping)
{
	oWeldDef* def = new oWeldDef();
	def->collision = collision;
	def->bodyA = bodyA;
	def->bodyB = bodyB;
	def->worldPos = worldPos;
	def->frequency = frequency;
	def->damping = damping;
	def->autorelease();
	return def;
}

oJointDef* oJointDef::wheel(
	bool collision,
	const string& bodyA,
	const string& bodyB,
	const oVec2& worldPos,
	const oVec2& axis,
	float maxMotorTorque,
	float motorSpeed,
	float frequency,
	float damping)
{
	oWheelDef* def = new oWheelDef();
	def->collision = collision;
	def->bodyA = bodyA;
	def->bodyB = bodyB;
	def->worldPos = worldPos;
	def->axis = axis;
	def->maxMotorTorque = maxMotorTorque;
	def->motorSpeed = motorSpeed;
	def->frequency = frequency;
	def->damping = damping;
	def->autorelease();
	return def;
}

oVec2 oJointDef::r(const oVec2& target)
{
	if (angle)
	{
		float realAngle = -CC_DEGREES_TO_RADIANS(angle) + atan2f(target.y, target.x);
		float length = target.length();
		return oVec2(length * cosf(realAngle), length * sinf(realAngle));
	}
	return target;
}

oVec2 oJointDef::t(const oVec2& target)
{
	oVec2 pos = target - center;
	return r(pos) + position;
}

oJoint* oDistanceDef::toJoint(CCDictionary* itemDict)
{
	oBody* bodyA = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyA.c_str()));
	oBody* bodyB = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyB.c_str()));
	if (bodyA && bodyB)
	{
		return oJoint::distance(collision, bodyA, bodyB, anchorA, anchorB, frequency, damping);
	}
	return nullptr;
}

oJoint* oFrictionDef::toJoint(CCDictionary* itemDict)
{
	oBody* bodyA = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyA.c_str()));
	oBody* bodyB = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyB.c_str()));
	if (bodyA && bodyB)
	{
		return oJoint::friction(collision, bodyA, bodyB, t(worldPos), maxForce, maxTorque);
	}
	return nullptr;
}

oJoint* oGearDef::toJoint(CCDictionary* itemDict)
{
	oJoint* jointA = dynamic_cast<oJoint*>(itemDict->objectForKey(this->jointA.c_str()));
	oJoint* jointB = dynamic_cast<oJoint*>(itemDict->objectForKey(this->jointB.c_str()));
	if (jointA && jointB)
	{
		return oJoint::gear(collision, jointA, jointB, ratio);
	}
	return nullptr;
}

oJoint* oSpringDef::toJoint(CCDictionary* itemDict)
{
	oBody* bodyA = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyA.c_str()));
	oBody* bodyB = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyB.c_str()));
	if (bodyA && bodyB)
	{
		return oJoint::spring(collision, bodyA, bodyB, linearOffset, angularOffset, maxForce, maxTorque, correctionFactor);
	}
	return nullptr;
}

oJoint* oPrismaticDef::toJoint(CCDictionary* itemDict)
{
	oBody* bodyA = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyA.c_str()));
	oBody* bodyB = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyB.c_str()));
	if (bodyA && bodyB)
	{
		return oJoint::prismatic(collision, bodyA, bodyB, t(worldPos), r(axis), lowerTranslation, upperTranslation, maxMotorForce, motorSpeed);
	}
	return nullptr;
}

oJoint* oPulleyDef::toJoint(CCDictionary* itemDict)
{
	oBody* bodyA = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyA.c_str()));
	oBody* bodyB = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyB.c_str()));
	if (bodyA && bodyB)
	{
		return oJoint::pulley(collision, bodyA, bodyB, anchorA, anchorB, t(groundAnchorA), t(groundAnchorB), ratio);
	}
	return nullptr;
}

oJoint* oRevoluteDef::toJoint(CCDictionary* itemDict)
{
	oBody* bodyA = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyA.c_str()));
	oBody* bodyB = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyB.c_str()));
	if (bodyA && bodyB)
	{
		return oJoint::revolute(collision, bodyA, bodyB, t(worldPos), lowerAngle + angle, upperAngle + angle, maxMotorTorque, motorSpeed);
	}
	return nullptr;
}

oJoint* oRopeDef::toJoint(CCDictionary* itemDict)
{
	oBody* bodyA = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyA.c_str()));
	oBody* bodyB = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyB.c_str()));
	if (bodyA && bodyB)
	{
		return oJoint::rope(collision, bodyA, bodyB, anchorA, anchorB, maxLength);
	}
	return nullptr;
}

oJoint* oWeldDef::toJoint(CCDictionary* itemDict)
{
	oBody* bodyA = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyA.c_str()));
	oBody* bodyB = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyB.c_str()));
	if (bodyA && bodyB)
	{
		return oJoint::weld(collision, bodyA, bodyB, t(worldPos), frequency, damping);
	}
	return nullptr;
}

oJoint* oWheelDef::toJoint(CCDictionary* itemDict)
{
	oBody* bodyA = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyA.c_str()));
	oBody* bodyB = dynamic_cast<oBody*>(itemDict->objectForKey(this->bodyB.c_str()));
	if (bodyA && bodyB)
	{
		return oJoint::wheel(collision, bodyA, bodyB, t(worldPos), r(axis), maxMotorTorque, motorSpeed, frequency, damping);
	}
	return nullptr;
}

NS_DOROTHY_END
