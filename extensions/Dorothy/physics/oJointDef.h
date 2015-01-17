/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_PHYSICS_OJOINT_DEF_H__
#define __DOROTHY_PHYSICS_OJOINT_DEF_H__

struct b2JointDef;

NS_DOROTHY_BEGIN

class oJoint;

class oJointDef : public CCObject
{
public:
	oVec2 center;
	oVec2 position;
	float angle;
	oJointDef();
	static oJointDef* distance(
		bool collision,
		const string& bodyA,
		const string& bodyB,
		const oVec2& anchorA,
		const oVec2& anchorB,
		float frequency = 0.0f,
		float damping = 0.0f);
	static oJointDef* friction(
		bool collision,
		const string& bodyA,
		const string& bodyB,
		const oVec2& worldPos,
		float maxForce,
		float maxTorque);
	static oJointDef* gear(
		bool collision,
		const string& jointA,
		const string& jointB,
		float ratio = 1.0f);
	static oJointDef* spring(
		bool collision,
		const string& bodyA,
		const string& bodyB,
		const oVec2& linearOffset,
		float angularOffset,
		float maxForce,
		float maxTorque,
		float correctionFactor = 1.0f);
	static oJointDef* prismatic(
		bool collision,
		const string& bodyA,
		const string& bodyB,
		const oVec2& worldPos,
		const oVec2& axis,
		float lowerTranslation = 0.0f,
		float upperTranslation = 0.0f,
		float maxMotorForce = 0.0f,
		float motorSpeed = 0.0f);
	static oJointDef* pulley(
		bool collision,
		const string& bodyA,
		const string& bodyB,
		const oVec2& anchorA,
		const oVec2& anchorB,
		const oVec2& groundAnchorA,
		const oVec2& groundAnchorB,
		float ratio = 1.0f);
	static oJointDef* revolute(
		bool collision,
		const string& bodyA,
		const string& bodyB,
		const oVec2& worldPos,
		float lowerAngle = 0.0f,
		float upperAngle = 0.0f,
		float maxMotorTorque = 0.0f,
		float motorSpeed = 0.0f);
	static oJointDef* rope(
		bool collision,
		const string& bodyA,
		const string& bodyB,
		const oVec2& anchorA,
		const oVec2& anchorB,
		float maxLength);
	static oJointDef* weld(
		bool collision,
		const string& bodyA,
		const string& bodyB,
		const oVec2& worldPos,
		float frequency = 0.0f,
		float damping = 0.0f);
	static oJointDef* wheel(
		bool collision,
		const string& bodyA,
		const string& bodyB,
		const oVec2& worldPos,
		const oVec2& axis,
		float maxMotorTorque = 0.0f,
		float motorSpeed = 0.0f,
		float frequency = 2.0f,
		float damping = 0.7f);
	virtual oJoint* toJoint(CCDictionary* itemDict) = 0;
protected:
	oVec2 r(const oVec2& target);
	oVec2 t(const oVec2& target);
	CC_LUA_TYPE(oJointDef)
};

class oDistanceDef : public oJointDef
{
public:
	bool collision;
	string bodyA;
	string bodyB;
	oVec2 anchorA;
	oVec2 anchorB;
	float frequency;
	float damping;
	virtual oJoint* toJoint(CCDictionary* itemDict);
};

class oFrictionDef : public oJointDef
{
public:
	bool collision;
	string bodyA;
	string bodyB;
	oVec2 worldPos;
	float maxForce;
	float maxTorque;
	virtual oJoint* toJoint(CCDictionary* itemDict);
};

class oGearDef : public oJointDef
{
public:
	bool collision;
	string jointA;
	string jointB;
	float ratio;
	virtual oJoint* toJoint(CCDictionary* itemDict);
};

class oSpringDef : public oJointDef
{
public:
	bool collision;
	string bodyA;
	string bodyB;
	oVec2 linearOffset;
	float angularOffset;
	float maxForce;
	float maxTorque;
	float correctionFactor;
	virtual oJoint* toJoint(CCDictionary* itemDict);
};

class oPrismaticDef : public oJointDef
{
public:
	bool collision;
	string bodyA;
	string bodyB;
	oVec2 worldPos;
	oVec2 axis;
	float lowerTranslation;
	float upperTranslation;
	float maxMotorForce;
	float motorSpeed;
	virtual oJoint* toJoint(CCDictionary* itemDict);
};

class oPulleyDef : public oJointDef
{
public:
	bool collision;
	string bodyA;
	string bodyB;
	oVec2 anchorA;
	oVec2 anchorB;
	oVec2 groundAnchorA;
	oVec2 groundAnchorB;
	float ratio;
	virtual oJoint* toJoint(CCDictionary* itemDict);
};

class oRevoluteDef : public oJointDef
{
public:
	bool collision;
	string bodyA;
	string bodyB;
	oVec2 worldPos;
	float lowerAngle;
	float upperAngle;
	float maxMotorTorque;
	float motorSpeed;
	virtual oJoint* toJoint(CCDictionary* itemDict);
};

class oRopeDef : public oJointDef
{
public:
	bool collision;
	string bodyA;
	string bodyB;
	oVec2 anchorA;
	oVec2 anchorB;
	float maxLength;
	virtual oJoint* toJoint(CCDictionary* itemDict);
};

class oWeldDef : public oJointDef
{
public:
	bool collision;
	string bodyA;
	string bodyB;
	oVec2 worldPos;
	float frequency;
	float damping;
	virtual oJoint* toJoint(CCDictionary* itemDict);
};

class oWheelDef : public oJointDef
{
public:
	bool collision;
	string bodyA;
	string bodyB;
	oVec2 worldPos;
	oVec2 axis;
	float maxMotorTorque;
	float motorSpeed;
	float frequency;
	float damping;
	virtual oJoint* toJoint(CCDictionary* itemDict);
};

NS_DOROTHY_END

#endif // __DOROTHY_PHYSICS_OJOINT_DEF_H__