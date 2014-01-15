class oModel: public CCNode
{
	tolua_property__common string look;
	tolua_property__common float speed;
	tolua_property__bool bool loop;
	tolua_property__common float time;
	tolua_readonly tolua_property__common float duration;
	tolua_property__common float recovery;
	tolua_property__bool bool faceRight;
	tolua_readonly tolua_property__bool bool playing;
	tolua_readonly tolua_property__bool bool paused;
	tolua_readonly tolua_property__common string currentAnimationName @ currentAnimation;
	tolua_outside void oModel_addHandler @ addHandler(const string& name, LUA_FUNCTION nHandler);
	tolua_outside void oModel_removeHandler @ removeHandler(const string& name, LUA_FUNCTION nHandler);
	tolua_outside void oModel_clearHandler @ clearHandler(const string& name);
	tolua_outside const oVec2& oModel_getKey @ getKey(unsigned int index);
	void play(const string& name);
	void pause();
	void resume();
	void resume(const string& name);
	void stop();
	CCNode* getNodeByName(const string& name);
	static oModel* create(const char* filename);
	static oModel* none();
};
