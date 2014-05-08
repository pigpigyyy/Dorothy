class oSensor: public CCObject
{
	#define oSensorEvent::Enter @ Enter
	#define oSensorEvent::Leave @ Leave
	tolua_property__bool bool enabled;
	tolua_readonly tolua_property__common int tag;
	tolua_readonly tolua_property__common oBody* owner;
	tolua_readonly tolua_property__bool bool sensed;
	tolua_readonly tolua_property__common CCArray* sensedBodies;
	tolua_outside void oSensor_addHandler @ addHandler(unsigned int flag, tolua_function nHandler);
	tolua_outside void oSensor_removeHandler @ removeHandler(unsigned int flag, tolua_function nHandler);
	tolua_outside void oSensor_clearHandler @ clearHandler(unsigned int flag);
	bool contains(oBody* body);
};
