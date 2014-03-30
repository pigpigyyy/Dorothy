class oLine: public CCNode
{
	void set(oVec2 vecs[tolua_len]);
	tolua_property__bool bool acceptOpacity;
	static oLine* create(oVec2 vecs[tolua_len], const ccColor4B& color);
};
