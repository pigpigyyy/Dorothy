class oContent
{
	tolua_property__bool bool usingGameFile @ useGameFile;
	void setGameFile(const string& filename);
	void setPassword(const string& password);
	void saveToFile(const string& filename, const string& content);
	static oContent* shared @ create();
};
