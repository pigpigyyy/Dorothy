/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oAI.h"
#include "Dorothy/platform/oUnit.h"
#include "Dorothy/platform/oData.h"
#include "Dorothy/physics/oSensor.h"

NS_DOROTHY_PLATFORM_BEGIN

oUnit* oAI::_nearestUnit = nullptr;
oUnit* oAI::_nearestFriend = nullptr;
oUnit* oAI::_nearestEnemy = nullptr;
oUnit* oAI::_nearestNeutral = nullptr;

float oAI::_nearestUnitDistance;
float oAI::_nearestFriendDistance;
float oAI::_nearestEnemyDistance;
float oAI::_nearestNeutralDistance;

oRef<oUnit> oAI::_self;
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

	oSensor* seneor = unit->getDetectSensor();
	if (seneor)
	{
		CCARRAY_START(oBody, body, seneor->getSensedBodies())
		{
			oUnit* aroundUnit = CCLuaCast<oUnit>(body->getOwner());
			if (!aroundUnit) continue;

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
			default:
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
	bool result = reflexArc->doAction();

	_friends->removeAllObjects();
	_enemies->removeAllObjects();
	_neutrals->removeAllObjects();
	_detectedUnits->removeAllObjects();
	_self = nullptr;

	return result;
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
	default:
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
	default:
		return _nearestUnit;
	}
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
	default:
		return _nearestUnitDistance;
	}
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
