class oEffect: public CCObject
{
	tolua_readonly tolua_property__bool bool playing;
	void start();
	void stop();
	oEffect* setOffset(oVec2& pos);
	oEffect* attachTo(CCNode* parent, int zOrder = 0);
	oEffect* autoRemove();
	static oEffect* create(const char* name);
	static tolua_outside void oEffect_update @ update(oEffect* effect, tolua_table table_idx);
};
