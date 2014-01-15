#ifndef __DOROTHY_PLATFORM_OBULLET_H__
#define __DOROTHY_PLATFORM_OBULLET_H__

#include "Dorothy/physics/oBody.h"
#include "Dorothy/misc/oIDisposable.h"

NS_DOROTHY_BEGIN
class oWorld;
NS_DOROTHY_END

NS_DOROTHY_PLATFORM_BEGIN

class oUnit;
class oBulletDef;
class oBullet;

typedef Delegate<bool (oBullet* bullet, oUnit* target)> oBulletHandler;

class oBullet: public oBody
{
public:
	PROPERTY_READONLY(oUnit*, Owner);
	PROPERTY_BOOL(_isFaceRight, FaceRight);
	PROPERTY(CCNode*, _face, Face);
	PROPERTY_READONLY(oSensor*, DetectSensor);
	virtual void update(float dt);
	virtual void onExit();
	void onBodyEnter(oSensor* sensor, oBody* body);
	void onFaceDisposed(oIDisposable* item);
	oBulletDef* getBulletDef();
	static oBullet* create(oWorld* world, oBulletDef* def, oUnit* unit);
	oTargetAllow targetAllow;
	oBulletHandler hitTarget;
	void addHandler(int handler);
	void removeHandler(int handler);
	void clearHandler();
	int type;
	virtual void destroy();
protected:
	oBullet(oWorld* world, oBulletDef* def, oUnit* unit);
	virtual void updatePhysics();
private:
	oRef<oBulletDef> _bulletDef;
	oRef<oUnit> _owner;
	oSensor* _detectSensor;
	float _lifeTime;
	float _current;
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OBULLET_H__
