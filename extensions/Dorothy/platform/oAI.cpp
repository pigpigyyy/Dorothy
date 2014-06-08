#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oAI.h"
#include "Dorothy/platform/oUnit.h"
#include "Dorothy/platform/oData.h"
#include "Dorothy/physics/oSensor.h"

NS_DOROTHY_PLATFORM_BEGIN

oUnit* oAI::_self = nullptr;
oUnit* oAI::_nearestUnit = nullptr;
oUnit* oAI::_nearestFriend = nullptr;
oUnit* oAI::_nearestEnemy = nullptr;
oUnit* oAI::_nearestNeutral = nullptr;

float oAI::_nearestUnitDistance;
float oAI::_nearestFriendDistance;
float oAI::_nearestEnemyDistance;
float oAI::_nearestNeutralDistance;

oRef<CCArray> oAI::_friends(CCArray::create());
oRef<CCArray> oAI::_enemies(CCArray::create());
oRef<CCArray> oAI::_neutrals(CCArray::create());
oRef<CCArray> oAI::_detectedUnits(CCArray::create());

float oAI::_oldInstinctValue = 0;
float oAI::_newInstinctValue = 0;

unordered_map<int, oRef<oAILeaf>> oAI::_reflexArcs;

oUnit* oAI::getSelf()
{
	return _self;
}

bool oAI::conditionedReflex(oUnit* unit)
{	
	oAILeaf* reflexArc = unit->getReflexArcNode();
	if (!reflexArc)
	{
		return false;
	}

	_self = unit;

	_nearestUnit = nullptr;
	_nearestFriend = nullptr;
	_nearestEnemy = nullptr;
	_nearestNeutral = nullptr;

	float minUnitDistance = 0;
	float minFriendDistance = 0;
	float minEnemyDistance = 0;
	float minNeutralDistance = 0;

	_friends->removeAllObjects();
	_enemies->removeAllObjects();
	_neutrals->removeAllObjects();
	_detectedUnits->removeAllObjects();

	oSensor* seneor = unit->getDetectSensor();
	if (seneor)
	{
		CCARRAY_START(oBody, body, seneor->getSensedBodies())
		{
			oUnit* aroundUnit = (oUnit*)body;
			_detectedUnits->addObject(aroundUnit);

			float newDistance = ccpDistanceSQ(unit->getPosition(), aroundUnit->getPosition());

			if (!_nearestUnit || newDistance < minUnitDistance)
			{
				minUnitDistance = newDistance;
				_nearestUnit = aroundUnit;
			}
			oRelation relation = oSharedData.getRelation(_self, aroundUnit);
			switch (relation)
			{
			case oRelation::Friend:
				_friends->addObject(aroundUnit);
				if (!_nearestFriend || newDistance < minFriendDistance)
				{
					minFriendDistance = newDistance;
					_nearestFriend = aroundUnit;
				}
				break;
			case oRelation::Enemy:
				_enemies->addObject(aroundUnit);
				if (!_nearestEnemy || newDistance < minEnemyDistance)
				{
					minEnemyDistance = newDistance;
					_nearestEnemy = aroundUnit;
				}
				break;
			case oRelation::Neutral:
				_neutrals->addObject(aroundUnit);
				if (!_nearestNeutral || newDistance < minNeutralDistance)
				{
					minNeutralDistance = newDistance;
					_nearestNeutral = aroundUnit;
				}
				break;
			}
		}
		CCARRAY_END
		_nearestUnitDistance = sqrtf(minUnitDistance);
		_nearestFriendDistance = sqrtf(minFriendDistance);
		_nearestEnemyDistance = sqrtf(minEnemyDistance);
		_nearestNeutralDistance = sqrtf(minNeutralDistance);
	}
	//Do the Conditioned Reflex
	return reflexArc->doAction();
}

CCArray* oAI::getUnitsByRelation( oRelation relation )
{
	CCArray* units = _detectedUnits;
	switch (relation)
	{
	case oRelation::Friend:
		units = _friends;
		break;
	case oRelation::Enemy:
		units = _enemies;
		break;
	case oRelation::Neutral:
		units = _neutrals;
		break;
	}
	return units;
}

CCArray* oAI::getDetectedUnits()
{
	return _detectedUnits;
}

oUnit* oAI::getNearestUnit( oRelation relation )
{
	switch (relation)
	{
	case oRelation::Friend:
		return _nearestFriend;
	case oRelation::Enemy:
		return _nearestEnemy;
	case oRelation::Neutral:
		return _nearestNeutral;
	}
	return _nearestUnit;
}

float oAI::getNearestUnitDistance( oRelation relation )
{
	switch (relation)
	{
	case oRelation::Friend:
		return _nearestFriendDistance;
	case oRelation::Enemy:
		return _nearestEnemyDistance;
	case oRelation::Neutral:
		return _nearestNeutralDistance;
	}
	return _nearestUnitDistance;
}

float oAI::getOldInstinctValue()
{
	return _oldInstinctValue;
}

float oAI::getNewInstinctValue()
{
	return _newInstinctValue;
}

void oAI::add( int id, oAILeaf* leaf )
{
	if (id != oAI::None)
	{
		_reflexArcs[id] = leaf;
	}
}

void oAI::clear()
{
	_reflexArcs.clear();
}

oAILeaf* oAI::get( int id )
{
	if (id != oAI::None)
	{
		auto it = _reflexArcs.find(id);
		if (it != _reflexArcs.end())
		{
			return it->second;
		}
	}
	return nullptr;
}

NS_DOROTHY_PLATFORM_END
