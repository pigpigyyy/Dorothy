class oEvent
{
	tolua_readonly tolua_property__common string name;

	static void addType @ add(const string& name);
	static bool removeType @ remove(const string& name);
	static void send(const string& name);
};