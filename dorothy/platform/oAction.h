/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_PLATFORM_OACTION_H__
#define __DOROTHY_PLATFORM_OACTION_H__

NS_DOROTHY_BEGIN
class oModel;
class oBody;
class oEffect;
class oScriptHandler;
NS_DOROTHY_END

NS_DOROTHY_PLATFORM_BEGIN
class oUnit;
class oAction;
class oBullet;
typedef Delegate<void (oAction* action)> oActionHandler;
typedef Delegate<void (oUnit* source, oUnit* target, float damage)> oDamageHandler;

class oActionDef
{
public:
	string name;
	int priority;
	float reaction;
	float recovery;
	oRef<oScriptHandler> available;
	oRef<oScriptHandler> create;
	oRef<oScriptHandler> stop;
	oAction* toAction(oUnit* unit);
};

class oAction
{
public:
	oAction(const string& name, int priority, oUnit* owner);
	virtual ~oAction();
	float reaction;
	float recovery;
	const string& getName() const;
	int getPriority() const;
	bool isDoing() const;
	oUnit* getOwner() const;
	oActionHandler actionStart;
	oActionHandler actionEnd;
	virtual bool isAvailable();
	virtual void run();
	virtual void update(float dt);
	virtual void stop();
	static oAction* create(const string& name, oUnit* unit);
	static void add(
		const string& name,
		int priority,
		float reaction,
		float recovery,
		int available,
		int create,
		int stop);
	static void clear();
protected:
	oUnit* _owner;
private:
	bool _isDoing;
	string _name;
	int _priority;
	float _reflexDelta;
	static unordered_map<string, oOwn<oActionDef>> _actionDefs;
};

class oScriptAction: public oAction
{
public:
	oScriptAction(const string& name, int priority, oUnit* owner);
	virtual bool isAvailable();
	virtual void run();
	virtual void update(float dt);
	virtual void stop();
private:
	oRef<oScriptHandler> _available;
	oRef<oScriptHandler> _create;
	oRef<oScriptHandler> _update;
	oRef<oScriptHandler> _stop;
	friend class oActionDef;
};

struct oID
{
	static const char* AnimationWalk;
	static const char* AnimationAttack;
	static const char* AnimationIdle;
	static const char* AnimationJump;
	static const char* AnimationHit;
	static const char* AnimationDie;

	static const char* ActionWalk;
	static const char* ActionTurn;
	static const char* ActionMeleeAttack;
	static const char* ActionRangeAttack;
	static const char* ActionIdle;
	static const char* ActionCancel;
	static const char* ActionJump;
	static const char* ActionHit;
	static const char* ActionDie;

	static const int PriorityWalk;
	static const int PriorityTurn;
	static const int PriorityJump;
	static const int PriorityAttack;
	static const int PriorityIdle;
	static const int PriorityCancel;
	static const int PriorityHit;
	static const int PriorityDie;

	static const float ReactionWalk;
	static const float ReactionIdle;
	static const float ReactionJump;

	static const float RecoveryWalk;
	static const float RecoveryAttack;
	static const float RecoveryIdle;
	static const float RecoveryJump;
	static const float RecoveryHit;
	static const float RecoveryDie;

	static const char* LookHappy;
	static const char* LookFight;
	static const char* LookSad;
	static const char* LookDead;
};

class oWalk: public oAction
{
public:
	oWalk(oUnit* unit);
	virtual bool isAvailable();
	virtual void run();
	virtual void update(float dt);
	virtual void stop();
	static oAction* create(oUnit* unit);
private:
	float _eclapsed;
};

class oTurn: public oAction
{
public:
	oTurn(oUnit* unit);
	virtual void run();
	static oAction* create(oUnit* unit);
};

class oAttack: public oAction
{
public:
	oAttack(const string& name, oUnit* unit);
	virtual ~oAttack();
	virtual void run();
	virtual void update(float dt);
	virtual void stop();
	void onAnimationEnd(oModel* model);
	float getDamage(oUnit* target);
	virtual void onAttack() = 0;
	oDamageHandler damaged;
	static oVec2 getHitPoint(oBody* self, oBody* target, b2Shape* selfShape);
protected:
	float _current;
	float _attackDelay;
	float _attackEffectDelay;
};

class oMeleeAttack: public oAttack
{
public:
	oMeleeAttack(oUnit* unit);
	static oAction* create(oUnit* unit);
protected:
	virtual void onAttack();
	b2PolygonShape _polygon;
};

class oRangeAttack: public oAttack
{
public:
	oRangeAttack(oUnit* unit);
	static oAction* create(oUnit* unit);
	bool onHitTarget(oBullet* bullet, oUnit* target);
protected:
	virtual void onAttack();
};

class oIdle: public oAction
{
public:
	oIdle(oUnit* unit);
	virtual void run();
	virtual void update(float dt);
	virtual void stop();
	static oAction* create(oUnit* unit);
};

class oJump: public oAction
{
public:
	oJump(oUnit* unit);
	virtual bool isAvailable();
	virtual void run();
	virtual void update(float dt);
	virtual void stop();
	static oAction* create(oUnit* unit);
private:
	float _current;
};

class oCancel: public oAction
{
public:
	oCancel(oUnit* unit);
	virtual void run();
	static oAction* create(oUnit* unit);
};

class oHit: public oAction
{
public:
	oHit(oUnit* unit);
	virtual ~oHit();
	virtual void run();
	virtual void update( float dt );
	virtual void stop();
	void setHitInfo(const oVec2& hitPoint, const oVec2& attackPower, bool hitFromRight);
	void onAnimationEnd(oModel* model);
	static oAction* create(oUnit* unit);
protected:
	bool _hitFromRight;
	oEffect* _effect;
	oVec2 _hitPoint;
	oVec2 _attackPower;
};

class oDie: public oAction
{
public:
	oDie(oUnit* unit);
	virtual ~oDie();
	virtual void run();
	virtual void update(float dt);
	virtual void stop();
	static oAction* create(oUnit* unit);
	void onAnimationEnd(oModel* model);
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OACTION_H__
