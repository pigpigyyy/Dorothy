class oAction
{
	enum { Start, End };
	float reaction;
	tolua_readonly tolua_property__common int id;
	tolua_readonly tolua_property__common int priority;
	tolua_readonly tolua_property__bool bool doing;
	tolua_readonly tolua_property__common oUnit* owner;
	void stop();
	void addHandler(int type, tolua_function handler);
	void removeHandler(int type, tolua_function handler);
	void clearHandler(int type);
	static void add(
		int id,
		int priority,
		float reaction,
		tolua_function available,
		tolua_function run,
		tolua_function update,
		tolua_function stop);
	static void clear();
	static tolua_readonly const int UserID;
};
