class CCImage: public CCObject
{
	#define kCCImageFormatJPEG @ JPG
	#define kCCImageFormatPNG @ PNG
	tolua_readonly tolua_property__common float width;
	tolua_readonly tolua_property__common float height;
};
