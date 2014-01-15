#ifndef __DOROTHY_MODEL_OKEYFRAME_H__
#define __DOROTHY_MODEL_OKEYFRAME_H__

#include "Dorothy/model/oEase.h"

NS_DOROTHY_BEGIN

class oKeyFrameDef;
class oKeyReset: public CCActionInstant
{
public:
	virtual void update(float time);
	virtual CCFiniteTimeAction* reverse();
	virtual CCObject* copyWithZone(CCZone* zone);
	static oKeyReset* create(oKeyFrameDef* def);
private:
	bool _visible;
	GLubyte _opacity;
	float _x;
	float _y;
	float _scaleX;
	float _scaleY;
	float _rotation;
	float _skewX;
	float _skewY;
};

class oKeyPos: public CCActionInterval
{
public:
	void setEase(uint8 easeId);
	bool initWithDuration(float duration, float posX, float posY);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);
	virtual void update(float time);
	void setValue(float endX, float endY);
public:
	static oKeyPos* create(float duration, float posX, float posY, uint8 easeId = 0);
protected:
	oEaseFunc _ease;
	float _startPosX;
	float _startPosY;
	float _endPosX;
	float _endPosY;
	float _deltaPosX;
	float _deltaPosY;
};

class oKeyScale: public CCActionInterval
{
public:
	void setEase(uint8 easeId);
	bool initWithDuration(float duration, float scaleX, float scaleY);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);
	virtual void update(float time);
	void setValue(float endScaleX, float endScaleY);
public:
	static oKeyScale* create(float duration, float scaleX, float scaleY, uint8 easeId = 0);
protected:
	oEaseFunc _ease;
	float _startScaleX;
	float _startScaleY;
	float _endScaleX;
	float _endScaleY;
	float _deltaScaleX;
	float _deltaScaleY;
};

class oKeyRotate: public CCActionInterval
{
public:
	void setEase(uint8 easeId);
	bool initWithDuration(float duration, float rotate);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);
	virtual void update(float time);
	void setValue(float endRotate);
public:
	static oKeyRotate* create(float duration, float rotate, uint8 easeId = 0);
protected:
	oEaseFunc _ease;
	float _startRotate;
	float _endRotate;
	float _deltaRotate;
};

class oKeyOpacity: public CCActionInterval
{
public:
	void setEase(uint8 easeId);
	bool initWithDuration(float duration, GLubyte opacity);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);
	virtual void update(float time);
	void setValue(GLubyte endOpacity);
	void setValue(float endOpacity);
public:
	static oKeyOpacity* create(float duration, GLubyte opacity, uint8 easeId = 0);
	static oKeyOpacity* create(float duration, float opacity, uint8 easeId = 0);
protected:
	oEaseFunc _ease;
	GLubyte _startOpacity;
	GLubyte _endOpacity;
	short _deltaOpacity;
};

class oKeySkew: public CCActionInterval
{
public:
	void setEase(uint8 easeId);
	bool initWithDuration(float duration, float skewX, float skewY);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);
	virtual void update(float time);
	void setValue(float endSkewX, float endSkewY);
public:
	static oKeySkew* create(float duration, float skewX, float skewY, uint8 easeId = 0);
protected:
	oEaseFunc _ease;
	float _startSkewX;
	float _startSkewY;
	float _endSkewX;
	float _endSkewY;
	float _deltaSkewX;
	float _deltaSkewY;
};

class oKeyRoll: public CCActionInterval
{
public:
	void setEase(uint8 easeId);
	bool initWithDuration(float duration, float roll);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);
	virtual void update(float time);
	void setValue(float endRoll);
public:
	static oKeyRoll* create(float duration, float roll, uint8 easeId = 0);
protected:
	oEaseFunc _ease;
	float _startRoll;
	float _endRoll;
	float _deltaRoll;
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OKEYFRAME_H__