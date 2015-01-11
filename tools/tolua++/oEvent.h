class oEvent
{
	tolua_readonly tolua_property__common string name;

	static void addType @ add(string& name);
	static bool removeType @ remove(string& name);
	static void clear();
	static void send(string& name);
};