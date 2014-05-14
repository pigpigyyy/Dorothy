#ifndef __DOROTHY_PLATFORM_OBULLET_DEF_H__
#define __DOROTHY_PLATFORM_OBULLET_DEF_H__

#include "Dorothy/physics/oBodyDef.h"
#include "Dorothy/model/oFace.h"

NS_DOROTHY_BEGIN
class oWorld;
NS_DOROTHY_END

NS_DOROTHY_PLATFORM_BEGIN
class oBullet;
class oUnit;

class oBulletDef: public CCObject
{
public:
	enum { NoneType = -1 };
	void setVelocity(float angle, float speed);
	PROPERTY_REF(oVec2, _velocity, Velocity);
	void setHighSpeedFix(bool var);
	bool isHighSpeedFix() const;
	PROPERTY_NAME(float, GravityScale);
	PROPERTY_NAME(oFace*, Face);
	int type;
	int endEffect;
	float lifeTime;
	float damageRadius;
	static oBulletDef* create();
	void setAsCircle(float radius);
	oBodyDef* getBodyDef() const;
	oBullet* toBullet(oWorld* world, oUnit* unit);
	static const int SensorTag;
protected:
	oBulletDef();
	oRef<oBodyDef> _bodyDef;
	oRef<oFace> _face;
	CC_LUA_TYPE(oBulletDef)
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OBULLET_DEF_H__