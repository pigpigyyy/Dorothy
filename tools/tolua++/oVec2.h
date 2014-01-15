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
	static const oVec2 zero;
};

class vector
{
    TOLUA_TEMPLATE_BIND(T, oVec2, int)

	vector();
	vector(int capacity);
    ~vector();
	
    void clear();
    tolua_readonly tolua_property__qt int size;

    const T& operator[](int index) const;
    T& operator[](int index);
    void push_back @ add(T val);
};

$renaming vector<oVec2> @ oVec2s
$renaming vector<int> @ oInts
