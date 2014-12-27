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
	
	void registerScriptTapHandler @ registerTapHandler(tolua_function funcID);
	void unregisterScriptTapHandler @ unregisterTapHandler();

    static CCMenuItem* create();
};
