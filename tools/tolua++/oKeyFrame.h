class oKeyPos: public CCActionInterval
{
	void setEase(unsigned char easeId);
	void setValue(float endX, float endY);
	static oKeyPos* create(float duration, float posX, float posY, unsigned char easeId = 0);
};

class oKeyScale: public CCActionInterval
{
	void setEase(unsigned char easeId);
	void setValue(float endScaleX, float endScaleY);
	static oKeyScale* create(float duration, float scaleX, float scaleY, unsigned char easeId = 0);
};

class oKeyRotate: public CCActionInterval
{
	void setEase(unsigned char easeId);
	void setValue(float endRotate);
	static oKeyRotate* create(float duration, float rotate, unsigned char easeId = 0);
};

class oKeyOpacity: public CCActionInterval
{
	void setEase(unsigned char easeId);
	void setValue(float endOpacity);
	static oKeyOpacity* create(float duration, float opacity, unsigned char easeId = 0);
};

class oKeySkew: public CCActionInterval
{
	void setEase(unsigned char easeId);
	void setValue(float endSkewX, float endSkewY);
	static oKeySkew* create(float duration, float skewX, float skewY, unsigned char easeId = 0);
};

class oKeyRoll: public CCActionInterval
{
	void setEase(unsigned char easeId);
	void setValue(float endRoll);
	static oKeyRoll* create(float duration, float roll, unsigned char easeId = 0);
};
