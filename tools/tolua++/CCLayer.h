class CCLayer: public CCNode
{
	enum
	{
		TouchesAllAtOnce,
		TouchesOneByOne
	};
	tolua_property__bool bool touchEnabled;
	tolua_property__bool bool accelerometerEnabled;
	tolua_property__bool bool keypadEnabled;
	tolua_property__common int touchMode;
	tolua_property__common int touchPriority;

	void registerScriptTouchHandler @ registerTouchHandler(LUA_FUNCTION nHandler,
									bool bIsMultiTouches = false,
									int nPriority = 0,
									bool bSwallowsTouches = false);
	void unregisterScriptTouchHandler @ unregisterTouchHandler();

	void registerScriptKeypadHandler @ registerKeypadHandler(LUA_FUNCTION nHandler);
	void unregisterScriptKeypadHandler @ unregisterKeypadHandler();

	void registerScriptAccelerateHandler @ registerAccelerateHandler(LUA_FUNCTION nHandler);
	void unregisterScriptAccelerateHandler @ unregisterAccelerateHandler();

	static CCLayer* create();
};

class CCLayerColor: public CCLayer
{
	tolua_property__common ccBlendFunc blendFunc;
	static CCLayerColor* create(ccColor4B color, float width, float height);
	static CCLayerColor* create(ccColor4B color);
};

class CCLayerGradient: public CCLayer
{
	tolua_property__common ccBlendFunc blendFunc;
	tolua_property__common ccColor3B startColor;
	tolua_property__common ccColor3B endColor;
	tolua_property__common float startOpacity;
	tolua_property__common float endOpacity;
	tolua_property__common oVec2 vector;
	tolua_property__bool bool compressedInterpolation;

	static CCLayerGradient* create(ccColor4B start, ccColor4B end, oVec2 v);
	static CCLayerGradient* create(ccColor4B start, ccColor4B end);
	static CCLayerGradient* create();
};
