class CCMenuItem: public CCNode
{
	enum
	{
		TapBegan,
		Tapped,
		TapEnded
	};

	tolua_readonly tolua_property__qt CCRect rect @ hitArea;
	tolua_readonly tolua_property__bool bool selected;
	tolua_property__bool bool enabled;
	
	void registerScriptTapHandler @ registerTapHandler(LUA_FUNCTION funcID);
	void unregisterScriptTapHandler @ unregisterTapHandler();

    static CCMenuItem* create();
};

class CCMenuItemLabel: public CCMenuItem
{
	void setText(const char* label);

	tolua_property__common ccColor3B disabledColor;
	tolua_property__common CCNode* label;

	static CCMenuItemLabel* create(CCNode* label);
};

class CCMenuItemAtlasFont: public CCMenuItemLabel
{
	static CCMenuItemAtlasFont* create(const char* value,
										const char* charMapFile,
										int itemWidth,
										int itemHeight,
										char startCharMap);
};

class CCMenuItemFont: public CCMenuItemLabel
{
	static tolua_property__common unsigned int fontSize @ defaultFontSize;
	static tolua_property__common char* fontName @ defaultFontName;

	tolua_property__common unsigned int fontSizeObj @ fontSize;
	tolua_property__common char* fontNameObj @ fontName;

	static CCMenuItemFont* create(const char* value);
};

class CCMenuItemSprite: public CCMenuItem
{
	tolua_property__common CCNode* normalImage @ normalSprite;
	tolua_property__common CCNode* selectedImage @ selectedSprite;
	tolua_property__common CCNode* disabledImage @ disabledSprite;

	static CCMenuItemSprite* create(CCNode* normalSprite,
									CCNode* selectedSprite);
	static CCMenuItemSprite* create(CCNode* normalSprite,
									CCNode* selectedSprite,
									CCNode* disabledSprite);
};

class CCMenuItemImage: public CCMenuItemSprite
{
	static CCMenuItemImage* create(const char* normalImage,
									const char* selectedImage);
	static CCMenuItemImage* create(const char* normalImage,
									const char* selectedImage,
									const char* disabledImage);
};

class CCMenuItemToggle: public CCMenuItem
{
	tolua_property__common unsigned int selectedIndex;
	tolua_property__common CCArray* subItems;

	void addSubItem(CCMenuItem* item);
	tolua_readonly tolua_property__qt CCMenuItem* selectedItem;

	static CCMenuItemToggle* create(CCMenuItem *item);
};
