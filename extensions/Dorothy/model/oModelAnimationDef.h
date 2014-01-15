#ifndef __DOROTHY_MODEL_OMODELANIMATIONDEF_H__
#define __DOROTHY_MODEL_OMODELANIMATIONDEF_H__

#include "Dorothy/const/oDefine.h"

NS_DOROTHY_BEGIN

class oActionDuration;

class oModelAnimationDef
{
public:
	virtual ~oModelAnimationDef(){}
	virtual oActionDuration* toAction() = 0;
	virtual string toXml() = 0;
	virtual void restoreResetAnimation(CCObject* object){}
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OMODELANIMATIONDEF_H__