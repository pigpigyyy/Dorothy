class oVec2
{
	oVec2(float x = 0.0f, float y = 0.0f);
	~oVec2();
	oVec2 operator+(const oVec2& vec) const;
	oVec2 operator-(const oVec2& vec) const;
	oVec2 operator*(float value) const;
	oVec2 operator*(const oVec2& vec) const;
	oVec2 operator/(float value) const;
	bool operator==(const oVec2& vec) const;
	float distance(const oVec2& vec) const;
	float distanceSquared(const oVec2& vec) const;
	tolua_readonly tolua_property__qt float length;
	tolua_readonly tolua_property__qt float lengthSquared;
	tolua_readonly tolua_property__qt float angle;
	void normalize();
	float x;
	float y;
	static tolua_readonly oVec2 zero;
};
