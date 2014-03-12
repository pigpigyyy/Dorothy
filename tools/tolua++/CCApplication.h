enum ccLanguageType {};
module CCLanguageType
{
    #define kLanguageEnglish @ English
    #define kLanguageChinese @ Chinese
    #define kLanguageFrench @ French
    #define kLanguageItalian @ Italian
    #define kLanguageGerman @ German
    #define kLanguageSpanish @ Spanish
    #define kLanguageRussian @ Russian
    #define kLanguageKorean @ Korean
    #define kLanguageJapanese @ Japanese
    #define kLanguageHungarian @ Hungarian
    #define kLanguagePortuguese @ Portuguese
    #define kLanguageArabic @ Arabic
}

enum TargetPlatform {};
module CCTargetPlatform
{
    #define kTargetWindows @ Windows
    #define kTargetLinux @ Linux
    #define kTargetMacOS @ MacOS
    #define kTargetAndroid @ Android
    #define kTargetIphone @ Iphone
    #define kTargetIpad @ Ipad
    #define kTargetBlackBerry @ BlackBerry
}

class CCApplication
{
	tolua_readonly tolua_property__common ccLanguageType currentLanguage;
	tolua_readonly tolua_property__common TargetPlatform targetPlatform;
	
	static CCApplication* sharedApplication @ create();
};
