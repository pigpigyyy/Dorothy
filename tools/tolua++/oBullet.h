class oBullet: public oBody
{
	int type;
	oTargetAllow targetAllow;
	tolua_readonly tolua_property__bool bool faceRight;
	tolua_readonly tolua_property__common oUnit* owner;
	tolua_readonly tolua_property__common oSensor* detectSensor;
	tolua_readonly tolua_property__common oBulletDef* bulletDef;
	tolua_property__common CCNode* face;
		
	void addHandler(tolua_function handler);
	void removeHandler(tolua_function handler);
	void clearHandler();

	void destroy();
	static oBullet* create(oWorld* world, oBulletDef* def, oUnit* unit);
};
