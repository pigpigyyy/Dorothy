class CCTouch: public CCObject
{
	enum
	{
		Began,
		Moved,
		Ended,
		Cancelled
	};
	tolua_readonly tolua_property__common oVec2 location;
    tolua_readonly tolua_property__common oVec2 previousLocation @ preLocation;
    tolua_readonly tolua_property__common oVec2 delta;
    tolua_readonly tolua_property__common oVec2 locationInView;
    tolua_readonly tolua_property__common oVec2 previousLocationInView @ preLocationInView;
    tolua_readonly tolua_property__common int iD @ id;
};
