class oBulletDef: public CCObject
{
	enum { NoneType = -1 };
	int type;
	int endEffect;
	float lifeTime;
	float damageRadius;
	tolua_property__bool bool highSpeedFix;
	tolua_property__common float gravityScale;
	tolua_property__common oFace* face;
	tolua_readonly tolua_property__common oBodyDef* bodyDef;
	tolua_readonly tolua_property__common oVec2 velocity;

	void setAsCircle(float radius);
	void setVelocity(float angle, float speed);
	oBullet* toBullet(oWorld* world, oUnit* unit);
	static tolua_readonly const int SensorTag;
	static oBulletDef* create();
};
