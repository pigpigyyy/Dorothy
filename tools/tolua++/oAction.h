class oAction
{
	enum { Start, End };
	float reaction;
	tolua_readonly tolua_property__common int id;
	tolua_readonly tolua_property__common int priority;
	tolua_readonly tolua_property__bool bool doing;
	tolua_readonly tolua_property__common oUnit* owner;
	void stop();
	void addHandler(int type, LUA_FUNCTION handler);
	void removeHandler(int type, LUA_FUNCTION handler);
	void clearHandler(int type);
	static void add(
		int id,
		int priority,
		float reaction,
		LUA_FUNCTION available,
		LUA_FUNCTION run,
		LUA_FUNCTION update,
		LUA_FUNCTION stop);
	static void clear();
	static const int UserID;
};
