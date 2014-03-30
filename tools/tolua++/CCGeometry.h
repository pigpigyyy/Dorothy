class CCSize
{
    CCSize();
    CCSize(float width, float height);
	~CCSize();
	
    float width;
    float height;
    
	bool operator==(const CCSize & target) const;
	
	static tolua_readonly CCSize zero;
};

class CCRect
{
	CCRect();
	CCRect(const oVec2& origin, const CCSize& size);
    CCRect(float x, float y, float width, float height);
	~CCRect();
	
    oVec2 origin;
    CCSize size;
	tolua_readonly tolua_property__common float minX @ left;
	tolua_readonly tolua_property__common float maxX @ right;
	tolua_readonly tolua_property__common float minY @ bottom;
	tolua_readonly tolua_property__common float maxY @ up;
	tolua_readonly tolua_property__common float midX;
	tolua_readonly tolua_property__common float midY;

	bool operator==(const CCRect & rect) const;
	bool containsPoint(const oVec2 & point) const;
	bool intersectsRect(const CCRect & rect) const;

	static tolua_readonly CCRect zero;
};
