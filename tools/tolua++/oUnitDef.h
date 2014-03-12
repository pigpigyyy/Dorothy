class oUnitDef: public CCObject
{
	static oUnitDef* create(
		const string& modelFile,
		const CCSize& size,
		float density = 0,
		float friction = 0,
		float restitution = 0);
	tolua_readonly tolua_property__common oBodyDef* bodyDef;
	tolua_readonly tolua_property__common CCSize size;
	tolua_readonly tolua_property__bool bool static;
	oUnit* toUnit(oWorld* world, int group, float x, float y, bool faceRight = true);
	enum {GroundSensorTag = 0, DetectSensorTag = 1, AttackSensorTag = 2};
	enum {BulletKey = 0, AttackKey = 1, HitKey = 2};
	int type;
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
	unsigned short damageType;
	unsigned short defenceType;
	int bulletType;
	int attackEffect;
	int hitEffect;
	string name;
	string desc;
	string sndAttack;
	string sndDeath;
	tolua_outside void oUnitDef_setActions @ setActions(int actions[tolua_len]);
	tolua_outside void oUnitDef_setInstincts @ setInstincts(int instincts[tolua_len]);
};
