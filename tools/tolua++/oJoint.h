class oJoint: public CCObject
{
	static oJoint* distance(
		oBody* bodyA,
		oBody* bodyB,
		oVec2 anchorA,
		oVec2 anchorB,
		float frequency = 0.0f,
		float damping = 0.0f);
	static oJoint* friction(
		oBody* bodyA,
		oBody* bodyB,
		oVec2 worldPos,
		float maxForce,
		float maxTorque);
	static oJoint* gear(
		oJoint* jointA,
		oJoint* jointB,
		float ratio = 1.0f);
	static oJoint* spring(
		oBody* bodyA,
		oBody* bodyB,
		oVec2 linearOffset,
		float angularOffset,
		float maxForce,
		float maxTorque,
		float correctionFactor = 1.0f);
	static oMoveJoint* move(
		oBody* bodyA,
		oBody* bodyB,
		oVec2 targetPos,
		float maxForce,
		float frequency = 5.0f,
		float damping = 0.7f);
	static oMotorJoint* prismatic(
		oBody* bodyA,
		oBody* bodyB,
		oVec2 worldPos,
		oVec2 axis,
		float lowerTranslation = 0.0f,
		float upperTranslation = 0.0f,
		float maxMotorForce = 0.0f,
		float motorSpeed = 0.0f);
	static oJoint* pulley(
		oBody* bodyA,
		oBody* bodyB,
		oVec2 anchorA,
		oVec2 anchorB,
		oVec2 groundAnchorA,
		oVec2 groundAnchorB,
		float ratio = 1.0f);
	static oMotorJoint* revolute(
		oBody* bodyA,
		oBody* bodyB,
		oVec2 worldPos,
		float lowerAngle = 0.0f,
		float upperAngle = 0.0f,
		float maxMotorTorque = 0.0f,
		float motorSpeed = 0.0f);
	static oJoint* rope(
		oBody* bodyA,
		oBody* bodyB,
		oVec2 anchorA,
		oVec2 anchorB,
		float maxLength);
	static oJoint* weld(
		oBody* bodyA,
		oBody* bodyB,
		oVec2 worldPos, 
		float frequency = 0.0f,
		float damping = 0.0f);
	static oMotorJoint* wheel(
		oBody* bodyA,
		oBody* bodyB,
		oVec2 worldPos,
		oVec2 axis,
		float maxMotorTorque = 0.0f,
		float motorSpeed = 0.0f,
		float frequency = 2.0f,
		float damping = 0.7f);
	tolua_readonly tolua_property__common oWorld* world;
	void destroy();
};

class oMoveJoint: public oJoint
{
	tolua_property__common oVec2 position;
};

class oMotorJoint: public oJoint
{
	tolua_property__bool bool enabled;
	tolua_property__common float speed;
};