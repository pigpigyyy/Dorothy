/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

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
	static const char* BulletKey;
	static const char* AttackKey;
	static const char* HitKey;
	//Most are static properties below.
	PROPERTY_REF(string, _model, Model);
	PROPERTY_REF(CCSize, _size, Size);
	PROPERTY_NAME(float, Density);
	PROPERTY_NAME(float, Friction);
	PROPERTY_NAME(float, Restitution);
	PROPERTY(float, _scale, Scale);
	PROPERTY_BOOL_NAME(Static);
	PROPERTY_READONLY(oModelDef*, ModelDef);
	PROPERTY_READONLY(oBodyDef*, BodyDef);
	int tag;
	float sensity;
	float move;
	float jump;
	float detectDistance;
	float maxHp;
	float attackBase;
	float attackDelay;
	float attackEffectDelay;
	string reflexArc;
	CCSize attackRange;
	oVec2 attackPower;
	oAttackType attackType;
	oAttackTarget attackTarget;
	oTargetAllow targetAllow;
	uint16 damageType;
	uint16 defenceType;
	string bulletType;
	string attackEffect;
	string hitEffect;
	string name;
	string desc;
	string sndAttack;
	string sndDeath;
	vector<string> actions;
	vector<int> instincts;
	static bool usePreciseHit;
	static oUnitDef* create();
protected:
	oUnitDef();
	void updateBodyDef();
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