class CCDrawNode: public CCNode
{
	void drawDot(oVec2& pos, float radius, ccColor4B& color);
	void drawSegment(oVec2& from, oVec2& to, float radius, ccColor4B& color);
	tolua_outside void CCDrawNode_drawPolygon @ drawPolygon(oVec2 verts[tolua_len], ccColor4B& fillColor, float borderWidth, ccColor4B& borderColor);
	void clear();
	
	static CCDrawNode* create();
};
