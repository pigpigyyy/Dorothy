class CCMenu: public CCLayer
{
	#define kCCMenuHandlerPriority @ DefaultHandlerPriority
	
	tolua_property__bool bool enabled;

	void alignItemsVertically();
	void alignItemsVerticallyWithPadding @ alignItemsVertically(float padding);
	void alignItemsHorizontally();
	void alignItemsHorizontallyWithPadding @ alignItemsHorizontally(float padding);

	void setHandlerPriority(int newPriority);

	void addChild(CCMenuItem* child, int zOrder = 0, int tag = -1);

	static CCMenu* create();
	static CCMenu* createWithItem(CCMenuItem* item);
	static CCMenu* createWithArray(CCArray* items);
};
