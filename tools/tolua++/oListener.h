class oListener: public CCObject
{
	tolua_property__bool bool enabled;

	static tolua_outside oListener* oListener_create @ create(string& name, tolua_function handler);
};