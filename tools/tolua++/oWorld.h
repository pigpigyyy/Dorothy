class oWorld: public CCLayer
{
	tolua_property__common oVec2 gravity;
	tolua_outside void oWorld_query @ query(CCRect& rect, tolua_function nHandler);
	void setIterations(int velocityIter, int positionIter);
	void setShouldContact(int groupA, int groupB, bool contact);
	bool getShouldContact(int groupA, int groupB);
	static float b2Factor;
	static oWorld* create();
};
