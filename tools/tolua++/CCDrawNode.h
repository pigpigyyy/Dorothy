class CCDrawNode: public CCNode
{
	void drawDot(const oVec2& pos, float radius, const ccColor4B& color);
	void drawSegment(const oVec2& from, const oVec2& to, float radius, const ccColor4B& color);
	tolua_outside void CCDrawNode_drawPolygon @ drawPolygon(oVec2 verts[tolua_len], const ccColor4B& fillColor, float borderWidth, const ccColor4B& borderColor);
	void clear();
	
	static CCDrawNode* create();
};
