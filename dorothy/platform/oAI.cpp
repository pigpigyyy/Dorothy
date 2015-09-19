/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "platform/oPlatformDefine.h"
#include "platform/oAI.h"
#include "platform/oUnit.h"
#include "platform/oData.h"
#include "physics/oSensor.h"

NS_DOROTHY_PLATFORM_BEGIN

oAI::oAI():
_nearestUnit(nullptr),
_nearestFriend(nullptr),
_nearestEnemy(nullptr),
_nearestNeutral(nullptr),
_nearestUnitDistance(0),
_nearestFriendDistance(0),
_nearestEnemyDistance(0),
_nearestNeutralDistance(0),
_oldInstinctValue(0),
_newInstinctValue(0),
_friends(CCArray::create()),
_enemies(CCArray::create()),
_neutrals(CCArray::create()),
_detectedUnits(CCArray::create())
{ }

oAI& oAI::getAI()
{
	static oAI ai;
	return ai;
}

oUnit* oAI::getSelf()
{
	return oAI::getAI()._self;
}

bool oAI::conditionedReflex(oUnit* unit)
{	
	oAILeaf* reflexArc = unit->getReflexArcNode();
	if (!reflexArc)
	{
		return false;
	}

	oAI& ai = oAI::getAI();

	ai._self = unit;

	ai._nearestUnit = nullptr;
	ai._nearestFriend = nullptr;
	ai._nearestEnemy = nullptr;
	ai._nearestNeutral = nullptr;

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

			ai._detectedUnits->addObject(aroundUnit);

			float newDistance = ccpDistanceSQ(unit->getPosition(), aroundUnit->getPosition());

			if (!ai._nearestUnit || newDistance < minUnitDistance)
			{
				minUnitDistance = newDistance;
				ai._nearestUnit = aroundUnit;
			}
			oRelation relation = oSharedData.getRelation(ai._self, aroundUnit);
			switch (relation)
			{
			case oRelation::Friend:
				ai._friends->addObject(aroundUnit);
				if (!ai._nearestFriend || newDistance < minFriendDistance)
				{
					minFriendDistance = newDistance;
					ai._nearestFriend = aroundUnit;
				}
				break;
			case oRelation::Enemy:
				ai._enemies->addObject(aroundUnit);
				if (!ai._nearestEnemy || newDistance < minEnemyDistance)
				{
					minEnemyDistance = newDistance;
					ai._nearestEnemy = aroundUnit;
				}
				break;
			case oRelation::Neutral:
				ai._neutrals->addObject(aroundUnit);
				if (!ai._nearestNeutral || newDistance < minNeutralDistance)
				{
					minNeutralDistance = newDistance;
					ai._nearestNeutral = aroundUnit;
				}
				break;
			default:
				break;
			}
		}
		CCARRAY_END
		ai._nearestUnitDistance = sqrtf(minUnitDistance);
		ai._nearestFriendDistance = sqrtf(minFriendDistance);
		ai._nearestEnemyDistance = sqrtf(minEnemyDistance);
		ai._nearestNeutralDistance = sqrtf(minNeutralDistance);
	}
	//Do the Conditioned Reflex
	bool result = reflexArc->doAction();

	ai._friends->removeAllObjects();
	ai._enemies->removeAllObjects();
	ai._neutrals->removeAllObjects();
	ai._detectedUnits->removeAllObjects();
	ai._self = nullptr;

	return result;
}

CCArray* oAI::getUnitsByRelation( oRelation relation )
{
	oAI& ai = oAI::getAI();
	CCArray* units = ai._detectedUnits;
	switch (relation)
	{
	case oRelation::Friend:
		units = ai._friends;
		break;
	case oRelation::Enemy:
		units = ai._enemies;
		break;
	case oRelation::Neutral:
		units = ai._neutrals;
		break;
	default:
		break;
	}
	return units;
}

CCArray* oAI::getDetectedUnits()
{
	return oAI::getAI()._detectedUnits;
}

oUnit* oAI::getNearestUnit( oRelation relation )
{
	oAI& ai = oAI::getAI();
	switch (relation)
	{
	case oRelation::Friend:
		return ai._nearestFriend;
	case oRelation::Enemy:
		return ai._nearestEnemy;
	case oRelation::Neutral:
		return ai._nearestNeutral;
	default:
		return ai._nearestUnit;
	}
}

float oAI::getNearestUnitDistance( oRelation relation )
{
	oAI& ai = oAI::getAI();
	switch (relation)
	{
	case oRelation::Friend:
		return ai._nearestFriendDistance;
	case oRelation::Enemy:
		return ai._nearestEnemyDistance;
	case oRelation::Neutral:
		return ai._nearestNeutralDistance;
	default:
		return ai._nearestUnitDistance;
	}
}

float oAI::getOldInstinctValue()
{
	return oAI::getAI()._oldInstinctValue;
}

float oAI::getNewInstinctValue()
{
	return oAI::getAI()._newInstinctValue;
}

void oAI::add( const string& name, oAILeaf* leaf )
{
	if (!name.empty())
	{
		oAI::getAI()._reflexArcs[name] = leaf;
	}
}

void oAI::clear()
{
	oAI::getAI()._reflexArcs.clear();
}

oAILeaf* oAI::get( const string& id )
{
	if (!id.empty())
	{
		auto it = oAI::getAI()._reflexArcs.find(id);
		if (it != oAI::getAI()._reflexArcs.end())
		{
			return it->second;
		}
	}
	return nullptr;
}

NS_DOROTHY_PLATFORM_END
