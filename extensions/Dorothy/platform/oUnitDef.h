#ifndef __DOROTHY_PLATFORM_OUNIT_DEF_H__
#define __DOROTHY_PLATFORM_OUNIT_DEF_H__

NS_DOROTHY_BEGIN
class oBodyDef;
class oModelDef;
class oWorld;
NS_DOROTHY_END

NS_DOROTHY_PLATFORM_BEGIN
class oUnit;
class oBulletDef;

class oUnitDef: public CCObject
{
public:
	static oUnitDef* create(
		const string& modelFile,
		const CCSize& size,
		float density = 0,
		float friction = 0,
		float restitution = 0);
	PROPERTY_READONLY(oBodyDef*, BodyDef);
	PROPERTY_READONLY_REF(CCSize, Size);
	PROPERTY_BOOL_NAME(Static);
	oUnit* toUnit(oWorld* world, int group, float x, float y, bool faceRight = true);
	enum {GroundSensorTag = 0, DetectSensorTag = 1, AttackSensorTag = 2};
	enum {BulletKey = 0, AttackKey = 1, HitKey = 2};
	//Most are static properties below.
	int type;//Type is hash code of name string.
	float sensity;
	float move;
	float jump;
	float detectDistance;
	float maxHp;
	float attackBase;
	float attackDelay;
	float attackEffectDelay;
	CCSize attackRange;
	oVec2 attackPower;
	oAttackType attackType;
	oAttackTarget attackTarget;
	oTargetAllow targetAllow;
	uint16 damageType;
	uint16 defenceType;
	int bulletType;
	PROPERTY_READONLY(oModelDef*, ModelDef);
	int attackEffect;
	int hitEffect;
	string name;
	string desc;
	string sndAttack;
	string sndDeath;
	vector<int> actions;
	vector<int> instincts;
protected:
	oUnitDef();
	oRef<oBodyDef> _bodyDef;
	oRef<oModelDef> _modelDef;
	CCSize _size;
	static const float BOTTOM_OFFSET;
	static const float GROUND_SENSOR_HEIGHT;
	CC_LUA_TYPE(oUnitDef)
};
NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OUNIT_DEF_H__