class oListener: public CCObject
{
	tolua_property__bool bool enable;

	static tolua_outside oListener* oListener_create @ create(const string& name, LUA_FUNCTION handler);
};