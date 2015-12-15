class CCSize
{
    CCSize();
    CCSize(float width, float height);
	~CCSize();
	
    float width;
    float height;
    
	bool operator==(CCSize & target);
	
	static tolua_readonly CCSize zero;
};

class CCRect
{
	CCRect();
	CCRect(oVec2& origin, CCSize& size);
    CCRect(float x, float y, float width, float height);
	~CCRect();
	
    oVec2 origin;
    CCSize size;
	tolua_readonly tolua_property__common float minX @ left;
	tolua_readonly tolua_property__common float maxX @ right;
	tolua_readonly tolua_property__common float minY @ bottom;
	tolua_readonly tolua_property__common float maxY @ top;
	tolua_readonly tolua_property__common float midX;
	tolua_readonly tolua_property__common float midY;

	bool operator==(CCRect & rect);
	bool containsPoint(oVec2 & point);
	bool intersectsRect(CCRect & rect);
	void set(float x, float y, float width, float height);

	static tolua_readonly CCRect zero;
};
