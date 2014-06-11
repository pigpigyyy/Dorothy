/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oAction.h"
#include "Dorothy/platform/oUnit.h"
#include "Dorothy/platform/oData.h"
#include "Dorothy/platform/oBulletDef.h"
#include "Dorothy/platform/oBullet.h"
#include "Dorothy/platform/oAI.h"
#include "Dorothy/model/oModelDef.h"
#include "Dorothy/model/oModel.h"
#include "Dorothy/physics/oSensor.h"
#include "Dorothy/physics/oWorld.h"
#include "Dorothy/effect/oEffectCache.h"
#include "Dorothy/misc/oScriptHandler.h"
#include "Dorothy/misc/oHelper.h"
#include "Dorothy/audio/oAudio.h"

NS_DOROTHY_PLATFORM_BEGIN

oAction* oActionDef::toAction(oUnit* unit)
{
	oScriptAction* action = new oScriptAction(id, priority, unit);
	action->_available = available;
	action->_run = run;
	action->_update = update;
	action->_stop = stop;
	return action;
}

// oAction
unordered_map<int, oOwn<oActionDef>> oAction::_actionDefs;

oAction::oAction(int id, int priority, oUnit* owner):
_id(id),
_priority(priority),
_isDoing(false),
_owner(owner),
reaction(0.0f)
{ }

oAction::~oAction()
{
	_owner = nullptr;
}

int oAction::getId() const
{
	return _id;
}

int oAction::getPriority() const
{
	return _priority;
}

bool oAction::isDoing() const
{
	return _isDoing;
}

oUnit* oAction::getOwner() const
{
	return _owner;
}

bool oAction::isAvailable()
{
	return true;
}

void oAction::run()
{
	_isDoing = true;
	_reflexDelta = 0.0f;
	if (actionStart)
	{
		actionStart(this);
	}
}

void oAction::update( float dt )
{
	_reflexDelta += dt;
	if (_reflexDelta >= _owner->sensity + oAction::reaction)
	{
		_reflexDelta = 0.0f;
		//Check AI here
		oAI::conditionedReflex(_owner);
	}
}

void oAction::stop()
{
	_isDoing = false;
	if (actionEnd)
	{
		actionEnd(this);
	}
}

const oAction::oActionFunc oAction::_createFuncs[] = 
{
	&oWalk::create,
	&oTurn::create,
	&oMeleeAttack::create,
	&oRangeAttack::create,
	&oIdle::create,
	&oStop::create,
	&oJump::create,
	&oHit::create,
	&oDie::create
};

const int oAction::UserID = sizeof(_createFuncs) / sizeof(oActionFunc);

oAction* oAction::create( int id, oUnit* unit )
{
	if (0 <= id && id < oAction::UserID)
	{
		return _createFuncs[id](unit);
	}
	auto it = _actionDefs.find(id);
	if (it != _actionDefs.end())
	{
		return it->second->toAction(unit);
	}
	return nullptr;
}

void oAction::add( int id, int priority, float reaction, int available, int run, int update, int stop )
{
	if (oAction::UserID <= id)
	{
		oActionDef* actionDef = new oActionDef();
		actionDef->id = id;
		actionDef->priority = priority;
		actionDef->reaction = reaction;
		actionDef->available = oScriptHandler::create(available);
		actionDef->run = oScriptHandler::create(run);
		actionDef->update = oScriptHandler::create(update);
		actionDef->stop = oScriptHandler::create(stop);
		_actionDefs[id] = oOwnMake(actionDef);
	}
}

void oAction::clear()
{
	_actionDefs.clear();
}

HANDLER_WRAP_START(oActionHandlerWrapper)
	void call(oAction* action) const
	{
		void* params[] = {action};
		const char* paramNames[] = {"oAction"};
		CCScriptEngine::sharedEngine()->executeFunction(getHandler(), 1, params, paramNames);
	}
HANDLER_WRAP_END

void oAction::addHandler( int type, int handler )
{
	switch (type)
	{
	case oAction::Start:
		actionStart += std::make_pair(oActionHandlerWrapper(handler), &oActionHandlerWrapper::call);
		break;
	case oAction::End:
		actionEnd += std::make_pair(oActionHandlerWrapper(handler), &oActionHandlerWrapper::call);
		break;
	}
}

void oAction::removeHandler( int type, int handler )
{
	switch (type)
	{
	case oAction::Start:
		actionStart -= std::make_pair(oActionHandlerWrapper(handler), &oActionHandlerWrapper::call);
		break;
	case oAction::End:
		actionEnd -= std::make_pair(oActionHandlerWrapper(handler), &oActionHandlerWrapper::call);
		break;
	}
}

void oAction::clearHandler(int type)
{
	switch (type)
	{
	case oAction::Start:
		actionStart.Clear();
		break;
	case oAction::End:
		actionEnd.Clear();
		break;
	}
}

oScriptAction::oScriptAction( int id, int priority, oUnit* owner ):
oAction(id, priority, owner)
{ }

bool oScriptAction::isAvailable()
{
	void* params[] = {this};
	const char* paramNames[] = {"oAction"};
	return CCScriptEngine::sharedEngine()->executeFunction(_available->get(), 1, params, paramNames) != 0;
}

void oScriptAction::run()
{
	void* params[] = {this};
	const char* paramNames[] = {"oAction"};
	CCScriptEngine::sharedEngine()->executeFunction(_run->get(), 1, params, paramNames);
	oAction::run();
}

void oScriptAction::update( float dt )
{
	CCScriptEngine::sharedEngine()->executeActionUpdate(_update->get(), this, "oAction", dt);
	oAction::update(dt);
}

void oScriptAction::stop()
{
	void* params[] = {this};
	const char* paramNames[] = {"oAction"};
	CCScriptEngine::sharedEngine()->executeFunction(_stop->get(), 1, params, paramNames);
	oAction::stop();
}

// oWalk
oWalk::oWalk( oUnit* unit ):
oAction(oID::ActionWalk, oID::PriorityWalk, unit)
{
	oAction::reaction = oID::ReactionWalk;
}

bool oWalk::isAvailable()
{
	return _owner->isOnSurface();
}

void oWalk::run()
{
	oModel* model = _owner->getModel();
	model->setSpeed(_owner->moveSpeed);
	model->setLoop(true);
	model->setLook(oID::LookHappy);
	model->setRecovery(0.1f);
	model->play(oID::AnimationWalk);
	float move = _owner->move * _owner->moveSpeed;
	_owner->setVelocityX(_owner->isFaceRight() ? move : -move);
	oAction::run();
}

void oWalk::update(float dt)
{
	if (_owner->isOnSurface())
	{
		float move = _owner->move * _owner->moveSpeed;
		_owner->setVelocityX(_owner->isFaceRight() ? move : -move);
	}
	else
	{
		oWalk::stop();
	}
	oAction::update(dt);
}

void oWalk::stop()
{
	oAction::stop();
	_owner->getModel()->stop();
}

oAction* oWalk::create(oUnit* unit)
{
	return new oWalk(unit);
}

// oTurn
oTurn::oTurn( oUnit* unit ):
oAction(oID::ActionTurn, oID::PriorityTurn, unit)
{ }

void oTurn::run()
{
	_owner->setFaceRight(!_owner->isFaceRight());
	if (actionStart)
	{
		actionStart(this);
	}
	if (actionEnd)
	{
		actionEnd(this);
	}
}

oAction* oTurn::create( oUnit* unit )
{
	return new oTurn(unit);
}

oIdle::oIdle( oUnit* unit ):
oAction(oID::ActionIdle, oID::PriorityIdle, unit)
{
	oAction::reaction = oID::ReactionIdle;
}

void oIdle::run()
{
	oModel* model = _owner->getModel();
	model->setSpeed(1.0f);
	model->setLoop(true);
	model->setLook(oID::LookHappy);
	model->setRecovery(0.2f);
	if (!_owner->isOnSurface())
	{
		oModel* model = _owner->getModel();
		model->resume(oID::AnimationJump);
	}
	else
	{
		model->resume(oID::AnimationIdle);
	}
	oAction::run();
}

void oIdle::update(float dt)
{
	oModel* model = _owner->getModel();
	if (!_owner->isOnSurface())
	{
		model->resume(oID::AnimationJump);
	}
	else if (_owner->getModel()->getCurrentAnimationName() != oID::AnimationIdle)
	{
		model->resume(oID::AnimationIdle);
	}
	oAction::update(dt);
}

void oIdle::stop()
{
	oAction::stop();
	_owner->getModel()->pause();
}

oAction* oIdle::create( oUnit* unit )
{
	return new oIdle(unit);
}

oJump::oJump( oUnit* unit ):
oAction(oID::ActionJump, oID::PriorityJump, unit)
{
	oAction::reaction = oID::ReactionJump;
}

bool oJump::isAvailable()
{
	return _owner->isOnSurface();
}

void oJump::run()
{
	oModel* model = _owner->getModel();
	model->setSpeed(1.0f);
	model->setLoop(true);
	model->setLook(oID::LookHappy);
	model->setRecovery(0.2f);
	model->resume(oID::AnimationJump);
	_current = 0.0f;
	_owner->setVelocityY(_owner->jump);
	oSensor* sensor = _owner->getGroundSensor();
	b2Body* self = _owner->getB2Body();
	b2Body* target = ((oBody*)sensor->getSensedBodies()->objectAtIndex(0))->getB2Body();
	b2DistanceInput input =
	{
		b2DistanceProxy(self->GetFixtureList()->GetShape(), 0),
		b2DistanceProxy(target->GetFixtureList()->GetShape(), 0),
		self->GetTransform(),
		target->GetTransform()
	};
	b2DistanceOutput output;
	b2Distance(&output, &input);
	target->ApplyLinearImpulse(
		b2Vec2(-self->GetMass() * self->GetLinearVelocityX(),
			-self->GetMass() * self->GetLinearVelocityY()),
			output.pointB);
	oAction::run();
}

void oJump::update(float dt)
{
	if (_current < 0.2f)//don`t check for ground for a while, for actor won`t lift immediately.
	{
		_current += dt;
		oJump::stop();
	}
	oAction::update(dt);
}

void oJump::stop()
{
	oAction::stop();
	_owner->getModel()->pause();
}

oAction* oJump::create( oUnit* unit )
{
	return new oJump(unit);
}

oStop::oStop( oUnit* unit ):
oAction(oID::ActionStop, oID::PriorityStop, unit)
{ }

void oStop::run()
{ }

oAction* oStop::create( oUnit* unit )
{
	return new oStop(unit);
}

// oAttack

oAttack::oAttack(int id, oUnit* unit ):
oAction(id, oID::PriorityAttack, unit)
{
	oModel* model = unit->getModel();
	model->handlers[oID::AnimationAttack] += std::make_pair(this, &oMeleeAttack::onAnimationEnd);
}

oAttack::~oAttack()
{
	oModel* model = _owner->getModel();
	model->handlers[oID::AnimationAttack] -= std::make_pair(this, &oMeleeAttack::onAnimationEnd);
}

void oAttack::run()
{
	_current = 0;
	_attackDelay = _owner->getUnitDef()->attackDelay / _owner->attackSpeed;
	_attackEffectDelay = _owner->getUnitDef()->attackEffectDelay / _owner->attackSpeed;
	oModel* model = _owner->getModel();
	model->setLoop(false);
	model->setLook(oID::LookFight);
	model->setRecovery(0.2f);
	model->setSpeed(_owner->attackSpeed);
	model->play(oID::AnimationAttack);
	oAction::run();
}

void oAttack::update( float dt )
{
	_current += dt;
	if (_attackDelay >= 0 && _current >= _attackDelay)
	{
		_attackDelay = -1;
		if (!_owner->getUnitDef()->sndAttack.empty())
		{
			oSound::play(_owner->getUnitDef()->sndAttack.c_str());
		}
		this->onAttack();
	}
	if (_attackEffectDelay >= 0 && _current >= _attackEffectDelay)
	{
		_attackEffectDelay = -1;
		int attackEffect = _owner->getUnitDef()->attackEffect;
		if (attackEffect != oEffectType::None)
		{
			oVec2 key = _owner->getModel()->getModelDef()->getKeyPoint(oUnitDef::AttackKey);
			if (_owner->getModel()->getModelDef()->isFaceRight() != _owner->isFaceRight())
			{
				key.x = -key.x;
			}
			oEffect* effect = oEffect::create(attackEffect);
			effect->setOffset(key)->attachTo(_owner)->autoRemove()->start();
		}
	}
}

void oAttack::stop()
{
	oAction::stop();
	_owner->getModel()->stop();
}

void oAttack::onAnimationEnd( oModel* model )
{
	if (oAction::isDoing())
	{
		this->stop();
	}
}

float oAttack::getDamage( oUnit* target )
{
	float factor = oSharedData.getDamageFactor(_owner->damageType, target->defenceType);
	float damage = (_owner->attackBase + _owner->attackBonus) * (_owner->attackFactor + factor);
	return damage;
}

oVec2 oAttack::getHitPoint( oBody* self, oBody* target, b2Shape* selfShape )
{
	oVec2 hitPoint;
	float distance = -1;
	for (b2Fixture* f = target->getB2Body()->GetFixtureList();f;f = f->GetNext())
	{
		if (!f->IsSensor())
		{
			b2DistanceInput input =
			{
				b2DistanceProxy(selfShape, 0),
				b2DistanceProxy(f->GetShape(), 0),
				self->getB2Body()->GetTransform(),
				target->getB2Body()->GetTransform()
			};
			b2DistanceOutput output;
			b2Distance(&output, &input);
			if (distance == -1 || distance > output.distance)
			{
				distance = output.distance;
				hitPoint = oWorld::oVal(output.pointB);
			}
		}
	}
	return hitPoint;
}

// oMeleeAttack
oMeleeAttack::oMeleeAttack( oUnit* unit ):
oAttack(oID::ActionMeleeAttack, unit)
{
	_polygon.SetAsBox(oWorld::b2Val(_owner->getWidth()*0.5f), 0.0005f);
}

void oMeleeAttack::onAttack()
{
	oSensor* sensor = _owner->getAttackSensor();
	if (sensor)
	{
		CCARRAY_START(oBody, body, sensor->getSensedBodies())
		{
			oUnit* target = (oUnit*)body;
			BLOCK_START
			{
				bool attackRight = _owner->getPositionX() < target->getPositionX();
				bool faceRight = _owner->isFaceRight();
				BREAK_IF(attackRight != faceRight);//!(hitRight == faceRight || hitLeft == faceLeft)
				oRelation relation = oSharedData.getRelation(_owner, target);
				BREAK_IF(!_owner->targetAllow.isAllow(relation));
				/* Get hit point */
				oHit* hitAction = (oHit*)(target->getAction(oID::ActionHit));
				if (hitAction)
				{
					oVec2 hitPoint = oUnitDef::usePreciseHit ? oAttack::getHitPoint(_owner, target, &_polygon) : target->getPosition();
					hitAction->setHitInfo(hitPoint, _owner->attackPower, !attackRight);
				}
				/* Make damage */
				float damage = oAttack::getDamage(target);
				target->properties["hp"] -= damage;
				if (damaged)
				{
					damaged(_owner, target, damage);
				}
			}
			BLOCK_END
		}
		CCARRAY_END
	}
}

oAction* oMeleeAttack::create( oUnit* unit )
{
	return new oMeleeAttack(unit);
}

// oRangeAttack
oRangeAttack::oRangeAttack( oUnit* unit ):
oAttack(oID::ActionRangeAttack, unit)
{ }

oAction* oRangeAttack::create( oUnit* unit )
{
	return new oRangeAttack(unit);
}

void oRangeAttack::onAttack()
{
	oBulletDef* bulletDef = _owner->getBulletDef();
	if (bulletDef)
	{
		oBullet* bullet = oBullet::create(bulletDef, _owner);
		bullet->targetAllow = _owner->targetAllow;
		bullet->hitTarget = std::make_pair(this, &oRangeAttack::onHitTarget);
		_owner->getWorld()->addChild(bullet, _owner->getZOrder());
		//SimpleAudioEngine::sharedEngine()->playEffect("sound/d_att.wav");
	}
}

bool oRangeAttack::onHitTarget( oBullet* bullet, oUnit* target )
{
	/* Get hit point */
	oHit* hitAction = (oHit*)(target->getAction(oID::ActionHit));
	if (hitAction)
	{
		b2Shape* shape = bullet->getDetectSensor()->getFixture()->GetShape();
		oVec2 hitPoint = oUnitDef::usePreciseHit ? oAttack::getHitPoint(_owner, target, shape) : target->getPosition();
		bool attackRight = bullet->getVelocityX() > 0.0f;
		hitAction->setHitInfo(hitPoint, _owner->attackPower, !attackRight);
	}
	/* Make damage */
	float damage = oAttack::getDamage(target);
	target->properties["hp"] -= damage;
	if (damaged)
	{
		damaged(_owner, target, damage);
	}
	return true;
}

oHit::oHit( oUnit* unit ):
oAction(oID::ActionHit, oID::PriorityHit, unit),
_effect(nullptr),
_hitFromRight(true),
_attackPower(),
_hitPoint()
{
	int hitEffect = _owner->getUnitDef()->hitEffect;
	if (hitEffect != oEffectType::None)
	{
		_effect = oEffect::create(hitEffect);
		_effect->attachTo(_owner);
		_effect->retain();
	}
	oModel* model = unit->getModel();
	model->handlers[oID::AnimationHit] += std::make_pair(this, &oHit::onAnimationEnd);
}

oHit::~oHit()
{
	oModel* model = _owner->getModel();
	model->handlers[oID::AnimationHit] -= std::make_pair(this, &oHit::onAnimationEnd);
}

void oHit::run()
{
	oModel* model = _owner->getModel();
	model->setLook(oID::LookSad);
	model->setLoop(false);
	//model->setRecovery(0.05f);
	model->setSpeed(1.0f);
	model->play(oID::AnimationHit);
	oVec2 key = CCPointApplyAffineTransform(_hitPoint, _owner->parentToNodeTransform());
	if (_effect)
	{
		_effect->setOffset(key)->start();
	}
	_owner->setVelocityX(_hitFromRight ? -_attackPower.x : _attackPower.x);
	_owner->setVelocityY(_attackPower.y);
	_owner->setFaceRight(_hitFromRight);
	oAction::run();
}

void oHit::update( float dt )
{ }

void oHit::setHitInfo( const oVec2& hitPoint, const oVec2& attackPower, bool hitFromRight )
{
	_hitPoint = hitPoint;
	_hitFromRight = hitFromRight;
	_attackPower = attackPower;
}

void oHit::onAnimationEnd( oModel* model )
{
	if (oAction::isDoing())
	{
		this->stop();
	}
}

void oHit::stop()
{
	oAction::stop();
	_owner->getModel()->stop();
}

oAction* oHit::create( oUnit* unit )
{
	return new oHit(unit);
}

oDie::oDie( oUnit* unit ):
oAction(oID::ActionDie, oID::PriorityDie, unit)
{
	oModel* model = unit->getModel();
	model->handlers[oID::AnimationDie] += std::make_pair(this, &oDie::onAnimationEnd);
}

oDie::~oDie()
{
	oModel* model = _owner->getModel();
	model->handlers[oID::AnimationDie] -= std::make_pair(this, &oDie::onAnimationEnd);
}

void oDie::run()
{
	oModel* model = _owner->getModel();
	model->setLook(oID::LookDead);
	model->setLoop(false);
	//model->setRecovery(0.05f);
	model->setSpeed(1.0f);
	model->play(oID::AnimationDie);
	int hitEffect = _owner->getUnitDef()->hitEffect;
	if (hitEffect != oEffectType::None)
	{
		oEffect* effect = oEffect::create(hitEffect);
		effect->attachTo(_owner)->autoRemove()->start();
	}
	if (!_owner->getUnitDef()->sndDeath.empty())
	{
		oSound::play(_owner->getUnitDef()->sndDeath.c_str());
	}
	oAction::run();
}

void oDie::update( float dt )
{ }

void oDie::stop()
{
	oAction::stop();
	_owner->getModel()->stop();
}

void oDie::onAnimationEnd( oModel* model )
{
	if (oAction::isDoing())
	{
		this->stop();
	}
}

oAction* oDie::create( oUnit* unit )
{
	return new oDie(unit);
}

const string oID::AnimationWalk("walk");
const string oID::AnimationAttack("attack");
const string oID::AnimationIdle("idle");
const string oID::AnimationJump("jump");
const string oID::AnimationHit("hit");
const string oID::AnimationDie("die");

const int oID::ActionWalk = 0;
const int oID::ActionTurn = 1;
const int oID::ActionMeleeAttack = 2;
const int oID::ActionRangeAttack = 3;
const int oID::ActionIdle = 4;
const int oID::ActionStop = 5;
const int oID::ActionJump = 6;
const int oID::ActionHit = 7;
const int oID::ActionDie = 8;

const int oID::PriorityIdle = 0;
const int oID::PriorityWalk = 1;
const int oID::PriorityTurn = 2;
const int oID::PriorityJump = 2;
const int oID::PriorityAttack = 3;
const int oID::PriorityStop = 2147483647;
const int oID::PriorityHit = 4;
const int oID::PriorityDie = 5;

const float oID::ReactionWalk = 0.05f;
const float oID::ReactionIdle = 0.2f;
const float oID::ReactionJump = 0.05f;

const string oID::LookHappy("happy");
const string oID::LookFight("fight");
const string oID::LookSad("sad");
const string oID::LookDead("dead");

NS_DOROTHY_PLATFORM_END
