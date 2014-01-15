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
	void attachLoop(
		const vector<oVec2>& vertices,
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
	void attachChain(
		const vector<oVec2>& vertices,
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
	void attachCircleSensor(
		int tag,
		const oVec2& center,
		float radius);
	void attachCircleSensor(
		int tag,
		float radius);
	PROPERTY_READONLY_REF(vector<b2FixtureDef*>, FixtureDefs);
	void clearFixtures();
	static oBodyDef* create();
	oBody* toBody(oWorld* world, int group, float x, float y, float angle = 0.0f);
protected:
	oBodyDef();
	static b2FixtureDef _fixtureDef;
	static b2PolygonShape _polygenShape;
	static b2CircleShape _circleShape;
	static b2ChainShape _chainShape;
private:
	vector<b2FixtureDef*> _fixtureDefs;
};

NS_DOROTHY_END

#endif // __DOROTHY_PHYSICS_OBODYDEF_H__
