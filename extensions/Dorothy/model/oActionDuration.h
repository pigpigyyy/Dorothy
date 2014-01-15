#ifndef __DOROTHY_MODEL_OACTIONDURATION_H__
#define __DOROTHY_MODEL_OACTIONDURATION_H__

NS_DOROTHY_BEGIN

class oActionDuration: public CCFiniteTimeAction
{
public:
	oActionDuration();
	PROPERTY_NAME(float, Time);
	PROPERTY(float, _speed, Speed);
	PROPERTY_READONLY(float, Elapsed);
	bool initWithDuration(float d);
	void pause();
	bool isPaused() const;
	void resume();
	virtual bool isDone(void);
	virtual CCObject* copyWithZone(CCZone* zone);
	virtual void step(float dt);
	virtual void startWithTarget(CCNode* target);
	virtual oActionDuration* reverse(void);
	static oActionDuration* create(float d);
protected:
	float _elapsed;
	bool _pause;
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OACTIONDURATION_H__