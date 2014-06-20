class oBody: public CCNode
{
	tolua_readonly tolua_property__common oWorld* world;
	tolua_readonly tolua_property__common oBodyDef* bodyDef;
	tolua_readonly tolua_property__common float mass;
	tolua_property__common float velocityX;
	tolua_property__common float velocityY;
	tolua_property__common oVec2 velocity;
	tolua_property__common float angularRate;
	tolua_property__common int group;
	tolua_property__common float linearDamping;
	tolua_property__common float angularDamping;
	tolua_property__common CCObject* owner;
	void applyLinearImpulse(oVec2 impulse, oVec2 pos);
	void applyAngularImpulse(float impulse);
	oSensor* getSensorByTag(int tag);
	bool removeSensorByTag(int tag);
	bool removeSensor(oSensor* sensor);
	void attach(oFixtureDef* fixtureDef);
	oSensor* attachSensor(int tag, oFixtureDef* fixtureDef);
	void destroy();
	static oBody* create(oBodyDef* def, oWorld* world, oVec2 pos = oVec2::zero, float rot = 0);
};
