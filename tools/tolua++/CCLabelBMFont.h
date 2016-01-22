class CCLabelBMFont: public CCSpriteBatchNode
{
	#define kCCLabelAutomaticWidth @ AutomaticWidth
    tolua_property__common char* text;
	tolua_property__common char* fntFile;
	tolua_property__common CCTextAlignment alignment @ horizontalAlignment;
	tolua_property__common float textWidth;
	tolua_property__bool bool lineBreakWithoutSpace;

	tolua_outside CCSprite* CCLabelBMFont_getChar @ getChar(int index);
	static void purgeCachedData();

	static CCLabelBMFont* create(const char* str, const char* fntFile, float width = kCCLabelAutomaticWidth, CCTextAlignment alignment = kCCTextAlignmentLeft, oVec2 imageOffset = oVec2::zero);
	static CCLabelBMFont* create();
};
