/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_PLATFORM_OUNIT_H__
#define __DOROTHY_PLATFORM_OUNIT_H__

#include "Dorothy/model/oModel.h"
#include "Dorothy/physics/oBody.h"
#include "Dorothy/platform/oUnitDef.h"
#include "Dorothy/platform/oProperty.h"
#include "Dorothy/platform/oAINode.h"
#include "Dorothy/platform/oBulletDef.h"

NS_DOROTHY_BEGIN
class oSensor;
NS_DOROTHY_END

NS_DOROTHY_PLATFORM_BEGIN
class oAction;
class oProperty;
class oInstinct;

class oUnit: public oBody
{
	typedef unordered_map<string, oOwn<oAction>> oActionMap;
	typedef unordered_map<string, oProperty*> oPropertyMap;
public:
	//Class properties
	PROPERTY_NAME(oModel*, Model);
	PROPERTY(float, _detectDistance, DetectDistance);
	PROPERTY_REF(CCSize, _attackRange, AttackRange);
	PROPERTY_BOOL(_isFaceRight, FaceRight);
	PROPERTY_READONLY(oSensor*, GroundSensor);
	PROPERTY_READONLY(oSensor*, DetectSensor);
	PROPERTY_READONLY(oSensor*, AttackSensor);
	PROPERTY_READONLY(oUnitDef*, UnitDef);
	PROPERTY_READONLY(oAction*, CurrentAction);
	PROPERTY_NAME(oBulletDef*, BulletDef);
	PROPERTY_READONLY(float, Width);
	PROPERTY_READONLY(float, Height);
	//
	virtual bool init();
	virtual void setGroup( int group );
	virtual void update( float dt );
	//Actions
	oAction* attachAction(const string& name);
	void removeAction(const string& name);
	void removeAllActions();
	oAction* getAction(const string& name) const;

	bool start(const string& name);
	void stop();
	bool isDoing(const string& name);
	//
	bool isOnSurface() const;
	void onActionEnd(oAction* action);
	static oUnit* create(oWorld* world, oUnitDef* unitDef);
	//Named properties
	class oPropertySet
	{
	public:
		~oPropertySet();
		oProperty& operator[](const string& name);
		const oProperty& operator[](const string& name) const;
		oProperty* add(const string& name);
		oProperty* get(const string& name) const;
		void remove(const string& name);
		void clear();
	private:
		void operator()(oUnit* owner);
		oUnit* _owner;
		oPropertyMap _items;
		friend class oUnit;
	} properties;
	//Methods for script to use properties
	void set(const char* name, float value);
	float get(const char* name);
	void remove(const char* name);
	void clear();
	//Dynamic properties
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
	uint16 damageType;
	uint16 defenceType;
	//Instinct for script
	void attachInstinct(int id);
	void removeInstinct(int id);
	void removeAllInstincts();
	//Conditioned Reflex
	void setReflexArc(const string& name);
	const string& getReflexArc() const;
	oAILeaf* getReflexArcNode();

	static oUnit* create(oUnitDef* unitDef, oWorld* world, const oVec2& pos = oVec2::zero, float rot = 0);
protected:
	oUnit(oUnitDef* unitDef, oWorld* world);
	//Instinct
	class oInstinctSet
	{
	public:
		void add(oInstinct* instinct);
		void remove(oInstinct* instinct);
		void reinstall();
		void clear();
	private:
		void operator()(oUnit* owner);
		oUnit* _owner;
		oRefVector<oInstinct> _instincts;
		friend class oUnit;
	} _instincts;
private:
	string _reflexArcName;
	oRef<oUnitDef> _unitDef;
	oRef<oAILeaf> _reflexArc;
	oRef<oBulletDef> _bulletDef;
	oRef<oModel> _model;
	CCSize _size;
	oSensor* _groundSensor;
	oSensor* _detectSensor;
	oSensor* _attackSensor;
	oAction* _currentAction;
	oActionMap _actions;
	CC_LUA_TYPE(oUnit)
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OUNIT_H__