class oEffect: public CCObject
{
	tolua_readonly tolua_property__bool bool playing;
	void start();
	void stop();
	oEffect* setOffset(const oVec2& pos);
	oEffect* attachTo(CCNode* parent, int zOrder = 0);
	oEffect* autoRemove();
	static oEffect* create(unsigned int index);
};
