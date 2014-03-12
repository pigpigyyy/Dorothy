class CCLabelBMFont: public CCSpriteBatchNode
{
	#define kCCLabelAutomaticWidth @ AutomaticWidth
    tolua_property__common char* text;
	tolua_property__common char* fntFile;

	void setAlignment(CCTextAlignment alignment);
	void setWidth(float width);
	void setLineBreakWithoutSpace(bool breakWithoutSpace);

	static void purgeCachedData();
	static CCLabelBMFont* create(const char *str, const char *fntFile, float width = kCCLabelAutomaticWidth, CCTextAlignment alignment = kCCTextAlignmentLeft, oVec2 imageOffset = oVec2::zero);
	static CCLabelBMFont* create();
};
