#ifndef __DOROTHY_MODEL_OSEQUENCE_H__
#define __DOROTHY_MODEL_OSEQUENCE_H__

#include "Dorothy/model/oActionDuration.h"

NS_DOROTHY_BEGIN

class oSequence: public oActionDuration
{
public:
	~oSequence(void);
	bool initWithTwoActions(CCFiniteTimeAction* pActionOne, CCFiniteTimeAction* pActionTwo);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);
	virtual void stop(void);
	virtual void update(float t);
	virtual oActionDuration* reverse(void);
	static oSequence* create(CCFiniteTimeAction* pAction1, ...);
	static oSequence* create(CCArray* arrayOfActions);
	static oSequence* createWithVariableList(CCFiniteTimeAction* pAction1, va_list args);
	static oSequence* createWithTwoActions(CCFiniteTimeAction* pActionOne, CCFiniteTimeAction* pActionTwo);
protected:
	CCFiniteTimeAction* m_pActions[2];
	float m_split;
	int m_last;
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OSEQUENCE_H__