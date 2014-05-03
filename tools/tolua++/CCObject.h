class CCObject
{
	tolua_readonly tolua_property__common int objectId @ id;
	static tolua_readonly tolua_property__common unsigned int objectCount @ count;
	static tolua_readonly tolua_property__common unsigned int luaRefCount;
};
