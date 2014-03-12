class oFixtureDef {};
enum b2BodyType {};

class oBodyDef: public CCObject
{
public:
	#define b2_staticBody @ Static
	#define b2_dynamicBody @ Dynamic
	#define b2_kinematicBody @ Kinematic
	b2BodyType type;
	float linearDamping;
	float angularDamping;
	bool fixedRotation;
	bool bullet;
	float gravityScale;
	static oFixtureDef* polygon(
		const oVec2& center,
		float width,
		float height,
		float angle = 0.0f,
		float density = 0.0f,
		float friction = 0.4f,
		float restitution = 0.0f);
	static oFixtureDef* polygon(
		float width,
		float height,
		float density = 0.0f,
		float friction = 0.4f,
		float restitution = 0.0f);
	static oFixtureDef* polygon(
		const oVec2 vertices[tolua_len],
		float density = 0.0f,
		float friction = 0.4f,
		float restitution = 0.0f);
	void attachPolygon(
		const oVec2& center,
		float width,
		float height,
		float angle = 0.0f,
		float density = 0.0f,
		float friction = 0.4f,
		float restitution = 0.0f);
	void attachPolygon(
		float width,
		float height,
		float density = 0.0f,
		float friction = 0.4f,
		float restitution = 0.0f);
	void attachPolygon(
		const oVec2 vertices[tolua_len],
		float density = 0.0f,
		float friction = 0.4f,
		float restitution = 0.0f);
	static oFixtureDef* loop(
		const oVec2 vertices[tolua_len],
		float friction = 0.4f,
		float restitution = 0.0f);
	void attachLoop(
		const oVec2 vertices[tolua_len],
		float friction = 0.4f,
		float restitution = 0.0f);
	static oFixtureDef* circle(
		const oVec2& center,
		float radius,
		float density = 0.0f,
		float friction = 0.4f,
		float restitution = 0.0f);
	static oFixtureDef* circle(
		float radius,
		float density = 0.0f,
		float friction = 0.4f,
		float restitution = 0.0f);
	void attachCircle(
		const oVec2& center,
		float radius,
		float density = 0.0f,
		float friction = 0.4f,
		float restitution = 0.0f);
	void attachCircle(
		float radius,
		float density = 0.0f,
		float friction = 0.4f,
		float restitution = 0.0f);
	static oFixtureDef* chain(
		const oVec2 vertices[tolua_len],
		float friction = 0.4f,
		float restitution = 0.0f);
	void attachChain(
		const oVec2 vertices[tolua_len],
		float friction = 0.4f,
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
		const oVec2 vertices[tolua_len]);
	void attachCircleSensor(
		int tag,
		const oVec2& center,
		float radius);
	void attachCircleSensor(
		int tag,
		float radius);
	static oBodyDef* create();
	oBody* toBody(oWorld* world, int group, float x, float y, float angle = 0.0f);
};
