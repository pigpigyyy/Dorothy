class oContent
{
	tolua_property__bool bool usingGameFile @ useGameFile;
	void setGameFile(const string& filename);
	void setPassword(const string& password);
	void saveToFile(const string& filename, const string& content);
	tolua_outside void oContent_getDirEntries @ getDirEntries(const char* path, bool isFolder);
	static oContent* shared @ create();
};
