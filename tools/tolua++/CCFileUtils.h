class CCFileUtils
{
    tolua_readonly tolua_property__common string writablePath;
    tolua_property__bool bool popupNotify;
	
    string fullPathForFilename @ getFullPath(char *pszFileName);
    const char* fullPathFromRelativeFile @ getRelativeFullPath(char *pszFilename, char *pszRelativeFile);
    void loadFilenameLookupDictionaryFromFile @ loadFileLookupInfo(const char* filename);

    void addSearchPath(const char* path);
    void addSearchResolutionsOrder(const char* order);
    void purgeCachedEntries();
	
	static CCFileUtils* sharedFileUtils @ create();
};
