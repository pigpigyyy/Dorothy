class oCamera: public CCNode
{
	tolua_property__common CCRect boudary;
	tolua_property__common CCSize view;
	tolua_property__common oVec2 followRatio;
	void follow(CCNode* target);
};
