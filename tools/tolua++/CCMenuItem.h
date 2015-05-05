class CCMenuItem: public CCNode
{
	enum
	{
		TapBegan,
		Tapped,
		TapEnded
	};

	tolua_readonly tolua_property__qt CCRect rect @ hitArea;
	tolua_property__bool bool enabled;
	tolua_property__common tolua_function scriptTapHandler @ tapHandler;

	static CCMenuItem* create();
};
