class CCTextFieldTTF: public CCLabelTTF
{
	bool attachWithIME();
	bool detachWithIME();

	tolua_readonly tolua_property__common int charCount;
	tolua_property__common ccColor3B colorSpaceHolder;
	tolua_property__common char* text;
	tolua_property__common char* placeHolder;

	static CCTextFieldTTF* textFieldWithPlaceHolder @ create(const char* placeholder, const char* fontName, float fontSize);
	static CCTextFieldTTF* textFieldWithPlaceHolder @ create(const char* placeholder, CCSize dimensions, CCTextAlignment alignment, const char* fontName, float fontSize);
};
