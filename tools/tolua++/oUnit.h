class oUnit: public oBody
{
	float sensity;
	float move;
	float moveSpeed;
	float jump;
	float maxHp;
	float attackBase;
	float attackBonus;
	float attackFactor;
	float attackSpeed;
	oVec2 attackPower;
	oAttackType attackType;
	oAttackTarget attackTarget;
	oTargetAllow targetAllow;
	unsigned short damageType;
	unsigned short defenceType;
	
	tolua_property__common oModel* model;
	tolua_property__common float detectDistance;
	tolua_property__common const CCSize& attackRange;
	tolua_property__bool bool faceRight;
	tolua_property__common oBulletDef* bulletDef;
	
	tolua_readonly tolua_property__bool bool onSurface;
	
	tolua_readonly tolua_property__common oSensor* groundSensor;
	tolua_readonly tolua_property__common oSensor* detectSensor;
	tolua_readonly tolua_property__common oSensor* attackSensor;

	tolua_readonly tolua_property__common oUnitDef* unitDef;
	tolua_readonly tolua_property__common oAction* currentAction;
	
	tolua_readonly tolua_property__common float width;
	tolua_readonly tolua_property__common float height;
	
	oAction* attachAction(int id);
	void removeAction(int id);
	void removeAllActions();
	oAction* getAction(int id) const;
	bool doIt(int id);
	
	void attachInstinct(int id);
	void removeInstinct(int id);
	void removeAllInstincts();
	
	void setReflexArc(int id);
	
	void set(const char* name, float value);
	float get(const char* name);
	void remove(const char* name);
	void clear();
	
	static oUnit* create(oWorld* world, oUnitDef* unitDef);
};
