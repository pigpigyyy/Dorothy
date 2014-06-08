#ifndef __DOROTHY_PHYSICS_OBODYDEF_H__
#define __DOROTHY_PHYSICS_OBODYDEF_H__

NS_DOROTHY_BEGIN

class oBody;
class oWorld;

class oBodyDef: public b2BodyDef, public CCObject
{
public:
	enum
	{
		Static = b2_staticBody,
		Dynamic = b2_dynamicBody,
		Kinematic = b2_kinematicBody
	};
	~oBodyDef();
	static b2FixtureDef* polygon(
		const oVec2& center,
		float width,
		float height,
		float angle = 0.0f,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachPolygon(
		const oVec2& center,
		float width,
		float height,
		float angle = 0.0f,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	static b2FixtureDef* polygon(
		float width,
		float height,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachPolygon(
		float width,
		float height,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	static b2FixtureDef* polygon(
		const vector<oVec2>& vertices,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachPolygon(
		const vector<oVec2>& vertices,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	static b2FixtureDef* polygon(
		const oVec2 vertices[],
		int count,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachPolygon(
		const oVec2 vertices[],
		int count,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	static b2FixtureDef* loop(
		const vector<oVec2>& vertices,
		float friction = 0.2f,
		float restitution = 0.0f);
	static b2FixtureDef* loop(
		const oVec2 vertices[],
		int count,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachLoop(
		const vector<oVec2>& vertices,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachLoop(
		const oVec2 vertices[],
		int count,
		float friction = 0.2f,
		float restitution = 0.0f);
	static b2FixtureDef* circle(
		const oVec2& center,
		float radius,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachCircle(
		const oVec2& center,
		float radius,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	static b2FixtureDef* circle(
		float radius,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachCircle(
		float radius,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	static b2FixtureDef* chain(
		const vector<oVec2>& vertices,
		float friction = 0.2f,
		float restitution = 0.0f);
	static b2FixtureDef* chain(
		const oVec2 vertices[],
		int count,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachChain(
		const vector<oVec2>& vertices,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachChain(
		const oVec2 vertices[],
		int count,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachPolygonSensor(
		int tag,
		float width,
		float height);
	void attachPolygonSensor(
		int tag,
		float width,
		float height,
		const oVec2& center,
		float angle = 0.0f);
	void attachPolygonSensor(
		int tag,
		const vector<oVec2>& vertices);
	void attachPolygonSensor(
		int tag,
		const oVec2 vertices[],
		int count);
	void attachCircleSensor(
		int tag,
		const oVec2& center,
		float radius);
	void attachCircleSensor(
		int tag,
		float radius);
	PROPERTY_READONLY_REF(oOwnVector<b2FixtureDef>, FixtureDefs);
	void clearFixtures();
	void setDensity(float var);
	void setFriction(float var);
	void setRestitution(float var);
	static oBodyDef* create();
protected:
	oBodyDef();
	static b2FixtureDef _fixtureDef;
	static b2PolygonShape _polygenShape;
	static b2CircleShape _circleShape;
	static b2ChainShape _chainShape;
private:
	oOwnVector<b2FixtureDef> _fixtureDefs;
	CC_LUA_TYPE(oBodyDef)
};

NS_DOROTHY_END

#endif // __DOROTHY_PHYSICS_OBODYDEF_H__
