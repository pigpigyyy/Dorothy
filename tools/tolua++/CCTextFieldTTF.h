class CCTextFieldTTF: public CCLabelTTF
{
	#define oTextFieldEvent::Attach @ Attach
	#define oTextFieldEvent::Detach @ Detach
	#define oTextFieldEvent::Insert @ Insert
	#define oTextFieldEvent::Inserted @ Inserted
	#define oTextFieldEvent::Delete @ Delete
	#define oTextFieldEvent::Deleted @ Deleted

	bool attachWithIME();
	bool detachWithIME();

	tolua_property__common ccColor3B colorSpaceHolder;
	tolua_property__common char* text;
	tolua_property__common char* placeHolder;

	tolua_outside void CCTextFieldTTF_registerInputHandler @ registerInputHandler(tolua_function handler);
	
	tolua_outside void CCTextFieldTTF_unregisterInputHandler @ unregisterInputHandler();

	static tolua_outside CCTextFieldTTF* CCTextFieldTTF_create @ create(const char* placeholder, const char* fontName, float fontSize);
};
