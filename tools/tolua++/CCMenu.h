class CCMenu: public CCLayer
{
	#define kCCMenuHandlerPriority @ DefaultHandlerPriority
	
	tolua_property__bool bool enabled;

	void alignItemsVertically();
	void alignItemsVerticallyWithPadding @ alignItemsVertically(float padding);
	void alignItemsHorizontally();
	void alignItemsHorizontallyWithPadding @ alignItemsHorizontally(float padding);

	static CCMenu* create();
};
