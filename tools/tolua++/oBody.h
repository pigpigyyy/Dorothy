class oBody: public CCNode
{
	tolua_readonly tolua_property__common oWorld* world;
	tolua_readonly tolua_property__common oBodyDef* bodyDef;
	tolua_property__common float velocityX;
	tolua_property__common float velocityY;
	tolua_property__common oVec2 velocity;
	tolua_property__common int group;
	//void setPosition(float x, float y);
	oSensor* getSensorByTag(int tag);
	bool removeSensorByTag(int tag);
	bool removeSensor(oSensor* sensor);
	void attach(oFixtureDef* fixtureDef);
	oSensor* attachSensor(int tag, oFixtureDef* fixtureDef);
	void destroy();
};
