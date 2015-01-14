class oContent
{
	tolua_property__bool bool usingGameFile @ useGameFile;
	void setGameFile(const char* filename);
	void setPassword(const char* password);
	void saveToFile(const char* filename, const char* content);
	tolua_outside void oContent_getDirEntries @ getEntries(const char* path, bool isFolder);
	tolua_outside void oContent_copyFileAsync @ copyAsync(const char* src, const char* dst, tolua_function func);
	bool isFileExist @ exist(const char* path);
	bool mkdir(const char* path);
	bool removeFile @ remove(const char* path);

    tolua_readonly tolua_property__common string writablePath;
    tolua_property__bool bool popupNotify;
	
    string getFullPath(const char* pszFileName);
    const char* getRelativeFullPath(const char* pszFilename, const char* pszRelativeFile);
    void loadFileLookupInfo(const char* filename);

    void addSearchPath(const char* path);
    void addSearchResolutionsOrder(const char* order);
    void purgeCachedEntries();
	
	static oContent* shared @ create();
};
