class CCMenu: public CCLayer
{
	#define kCCMenuHandlerPriority @ DefaultHandlerPriority
	
	tolua_property__bool bool enabled;

	void alignItemsVertically();
	void alignItemsVerticallyWithPadding @ alignItemsVertically(float padding);
	void alignItemsHorizontally();
	void alignItemsHorizontallyWithPadding @ alignItemsHorizontally(float padding);

	void setHandlerPriority(int newPriority);

	static CCMenu* create(bool swallow = true);
	static CCMenu* createWithArray(CCArray* items, bool swallow = true);
};
