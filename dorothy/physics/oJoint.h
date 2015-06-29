/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_PHYSICS_OJOINT_H__
#define __DOROTHY_PHYSICS_OJOINT_H__

class b2Joint;

NS_DOROTHY_BEGIN

class oBody;
class oWorld;
class oJointDef;
class oMoveJoint;
class oMotorJoint;

class oJoint: public CCObject
{
public:
	virtual ~oJoint();
	static oJoint* distance(
		bool collideConnected,
		oBody* bodyA,
		oBody* bodyB,
		const oVec2& anchorA,
		const oVec2& anchorB,
		float frequency = 0.0f,
		float damping = 0.0f);
	static oJoint* friction(
		bool collideConnected,
		oBody* bodyA,
		oBody* bodyB,
		const oVec2& worldPos,
		float maxForce,
		float maxTorque);
	static oJoint* gear(
		bool collideConnected,
		oJoint* jointA,
		oJoint* jointB,
		float ratio = 1.0f);
	static oJoint* spring(
		bool collideConnected,
		oBody* bodyA,
		oBody* bodyB,
		oVec2 linearOffset,
		float angularOffset,
		float maxForce,
		float maxTorque,
		float correctionFactor = 1.0f);
	static oMoveJoint* move(
		bool collideConnected,
		oBody* bodyA,
		oBody* bodyB,
		const oVec2& targetPos,
		float maxForce,
		float frequency = 5.0f,
		float damping = 0.7f);
	static oMotorJoint* prismatic(
		bool collideConnected,
		oBody* bodyA,
		oBody* bodyB,
		const oVec2& worldPos,
		const oVec2& axis,
		float lowerTranslation = 0.0f,
		float upperTranslation = 0.0f,
		float maxMotorForce = 0.0f,
		float motorSpeed = 0.0f);
	static oJoint* pulley(
		bool collideConnected,
		oBody* bodyA,
		oBody* bodyB,
		const oVec2& anchorA,
		const oVec2& anchorB,
		const oVec2& groundAnchorA,
		const oVec2& groundAnchorB,
		float32 ratio = 1.0f);
	static oMotorJoint* revolute(
		bool collideConnected,
		oBody* bodyA,
		oBody* bodyB,
		const oVec2& worldPos,
		float lowerAngle = 0.0f,
		float upperAngle = 0.0f,
		float maxMotorTorque = 0.0f,
		float motorSpeed = 0.0f);
	static oJoint* rope(
		bool collideConnected,
		oBody* bodyA,
		oBody* bodyB,
		const oVec2& anchorA,
		const oVec2& anchorB,
		float maxLength);
	static oJoint* weld(
		bool collideConnected,
		oBody* bodyA,
		oBody* bodyB,
		const oVec2& worldPos, 
		float frequency = 0.0f,
		float damping = 0.0f);
	static oMotorJoint* wheel(
		bool collideConnected,
		oBody* bodyA,
		oBody* bodyB,
		const oVec2& worldPos,
		const oVec2& axis,
		float maxMotorTorque = 0.0f,
		float motorSpeed = 0.0f,
		float frequency = 2.0f,
		float damping = 0.7f);
	b2Joint* getB2Joint();
	oWorld* getWorld();
	void destroy();
	static oJoint* create(oJointDef* def, CCDictionary* itemDict);
protected:
	oWRef<oWorld> _world;
	b2Joint* _joint;
	friend class oDestructionListener;
	CC_LUA_TYPE(oJoint)
};

class oMoveJoint: public oJoint
{
public:
	PROPERTY_REF(oVec2, _position, Position);
	CC_LUA_TYPE(oMoveJoint)
};

class oMotorJoint: public oJoint
{
public:
	PROPERTY_NAME(float, Force);
	PROPERTY_NAME(float, Speed);
	PROPERTY_BOOL_NAME(Enabled);
	void reversePower();
	CC_LUA_TYPE(oMotorJoint)
};

NS_DOROTHY_END

#endif // __DOROTHY_PHYSICS_OJOINT_H__
