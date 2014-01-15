class oSensor: public CCObject
{
	/*
	enum
	{
		Enter = 0,
		Leave = 1
	};
	*/
	tolua_property__bool bool enabled;
	tolua_readonly tolua_property__common int tag;
	tolua_readonly tolua_property__common oBody* owner;
	tolua_readonly tolua_property__bool bool sensed;
	tolua_readonly tolua_property__common CCArray* sensedBodies;
	tolua_outside void oSensor_addHandler @ addHandler(unsigned int flag, LUA_FUNCTION nHandler);
	tolua_outside void oSensor_removeHandler @ removeHandler(unsigned int flag, LUA_FUNCTION nHandler);
	tolua_outside void oSensor_clearHandler @ clearHandler(unsigned int flag);
	bool contains(oBody* body);
};
