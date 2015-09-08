class CCMenu: public CCLayer
{
	#define kCCMenuHandlerPriority @ DefaultHandlerPriority
	
	tolua_property__bool bool enabled;

	float alignItemsVerticallyWithPadding @ alignItemsVertically(float padding = 10);
	float alignItemsHorizontallyWithPadding @ alignItemsHorizontally(float padding = 10);
	CCSize alignItemsWithPadding @ alignItems(float padding = 10);

	static CCMenu* create();
};
