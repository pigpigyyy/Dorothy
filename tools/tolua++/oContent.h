class oContent
{
	tolua_property__bool bool usingGameFile @ useGameFile;
	void setGameFile(const string& filename);
	void setPassword(const string& password);
	
	static oContent* shared @ create();
};
