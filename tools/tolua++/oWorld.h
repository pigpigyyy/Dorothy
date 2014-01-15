class oWorld: public CCLayer
{
	tolua_property__common oVec2 gravity;
	tolua_outside void oWorld_query @ query(const CCRect& rect, LUA_FUNCTION nHandler);
	void setIterations(int velocityIter, int positionIter);
	void setShouldContact(int groupA, int groupB, bool contact);
	bool getShouldContact(int groupA, int groupB) const;
	static float b2Factor;
	static oWorld* create();
};
