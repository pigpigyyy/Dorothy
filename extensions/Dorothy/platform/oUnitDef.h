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
	enum {GroundSensorTag = 0, DetectSensorTag = 1, AttackSensorTag = 2};
	enum {BulletKey = 0, AttackKey = 1, HitKey = 2};
	//Most are static properties below.
	PROPERTY_REF(string, _model, Model);
	PROPERTY_NAME(float, Density);
	PROPERTY_NAME(float, Friction);
	PROPERTY_NAME(float, Restitution);
	PROPERTY_BOOL_NAME(Static);
	PROPERTY_READONLY(oModelDef*, ModelDef);
	PROPERTY_READONLY(oBodyDef*, BodyDef);
	PROPERTY_READONLY_REF(CCSize, Size);
	int type;
	int reflexArc;
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
	int attackEffect;
	int hitEffect;
	string name;
	string desc;
	string sndAttack;
	string sndDeath;
	vector<int> actions;
	vector<int> instincts;
	static oUnitDef* create();
protected:
	oUnitDef();
	oRef<oBodyDef> _bodyDef;
	oRef<oModelDef> _modelDef;
	float _density;
	float _friction;
	float _restitution;
	static const float BOTTOM_OFFSET;
	static const float GROUND_SENSOR_HEIGHT;
	CC_LUA_TYPE(oUnitDef)
};
NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OUNIT_DEF_H__