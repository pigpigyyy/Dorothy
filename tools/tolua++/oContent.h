class oContent
{
	tolua_property__bool bool usingGameFile @ useGameFile;
	void setGameFile(const char* filename);
	void setPassword(const char* password);
	void saveToFile(const char* filename, const char* content);
	tolua_outside void oContent_getDirEntries @ getDirEntries(const char* path, bool isFolder);
	static oContent* shared @ create();
};
