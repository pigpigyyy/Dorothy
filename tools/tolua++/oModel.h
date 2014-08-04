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
	tolua_outside void oModel_addHandler @ addHandler(const char* name, tolua_function nHandler);
	tolua_outside void oModel_removeHandler @ removeHandler(const char* name, tolua_function nHandler);
	tolua_outside void oModel_clearHandler @ clearHandler(const char* name);
	tolua_outside oVec2& oModel_getKey @ getKey(unsigned int index);
	void play(const char* name);
	void pause();
	void resume();
	void resume(const char* name);
	void stop();
	void reset();
	CCNode* getNodeByName @ getChildByName(const char* name);
	static oModel* create(const char* filename);
	static oModel* none();
};
