/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

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
	int id;
	int priority;
	float reaction;
	oRef<oScriptHandler> available;
	oRef<oScriptHandler> run;
	oRef<oScriptHandler> update;
	oRef<oScriptHandler> stop;
	oAction* toAction(oUnit* unit);
};

class oAction
{
	typedef oAction* (*oActionFunc)(oUnit* unit);
public:
	enum { Start, End };
	oAction(int id, int priority, oUnit* owner);
	virtual ~oAction();
	float reaction;
	int getId() const;
	int getPriority() const;
	bool isDoing() const;
	oUnit* getOwner() const;
	oActionHandler actionStart;
	oActionHandler actionEnd;
	void addHandler(int type, int handler);
	void removeHandler(int type, int handler);
	void clearHandler(int type);
	virtual bool isAvailable();
	virtual void run();
	virtual void update(float dt);
	virtual void stop();
	static oAction* create(int id, oUnit* unit);
	static void add(
		int id,
		int priority,
		float reaction,
		int available,
		int run,
		int update,
		int stop);
	static void clear();
	static const int UserID;
protected:
	oUnit* _owner;
private:
	bool _isDoing;
	int _id;
	int _priority;
	float _reflexDelta;
	static const oActionFunc _createFuncs[];
	static unordered_map<int, oOwn<oActionDef>> _actionDefs;
};

class oScriptAction: public oAction
{
public:
	oScriptAction(int id, int priority, oUnit* owner);
	virtual bool isAvailable();
	virtual void run();
	virtual void update(float dt);
	virtual void stop();
private:
	oRef<oScriptHandler> _available;
	oRef<oScriptHandler> _run;
	oRef<oScriptHandler> _update;
	oRef<oScriptHandler> _stop;
	friend class oActionDef;
};

struct oID
{
	static const string AnimationWalk;
	static const string AnimationAttack;
	static const string AnimationIdle;
	static const string AnimationJump;
	static const string AnimationHit;
	static const string AnimationDie;

	static const int ActionWalk;
	static const int ActionTurn;
	static const int ActionMeleeAttack;
	static const int ActionRangeAttack;
	static const int ActionIdle;
	static const int ActionStop;
	static const int ActionJump;
	static const int ActionHit;
	static const int ActionDie;

	static const int PriorityWalk;
	static const int PriorityTurn;
	static const int PriorityJump;
	static const int PriorityAttack;
	static const int PriorityIdle;
	static const int PriorityStop;
	static const int PriorityHit;
	static const int PriorityDie;

	static const float ReactionWalk;
	static const float ReactionIdle;
	static const float ReactionJump;

	static const string LookHappy;
	static const string LookFight;
	static const string LookSad;
	static const string LookDead;
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
	oAttack(int id, oUnit* unit);
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

class oStop: public oAction
{
public:
	oStop(oUnit* unit);
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
