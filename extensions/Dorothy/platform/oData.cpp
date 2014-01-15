#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oUnit.h"
#include "Dorothy/platform/oData.h"
#include "Dorothy/platform/oPlatformWorld.h"
#include "Dorothy/physics/oBody.h"

NS_DOROTHY_PLATFORM_BEGIN

//Group [0] for hide
//Group [1,2,3,4,5,6,7,8,9,10,11,12] for player
//Group [13] for player sensor
//Group [14] for terrain
//Group [15] for sense all
#define Hide 0
#define P1 1
#define P12 12
#define PSensor 13
#define Terrain 14
#define SenseAll 15

void oData::apply( oPlatformWorld* world )
{
	for (int p = P1;p <= P12;p++)
	{
		world->setShouldContact(PSensor, p, true);
		world->setShouldContact(Terrain, p, true);
		world->setShouldContact(SenseAll, p, true);
	}
	world->setShouldContact(SenseAll, Terrain, true);
}

void oData::setRelation( int groupA, int groupB, oRelation relation )
{
	int key = groupA<<16 | groupB;
	_relationMap[key] = relation;
	key = groupB | groupA<<16;
	_relationMap[key] = relation;
}

oRelation oData::getRelation( int groupA, int groupB ) const
{
	int key = groupA<<16 | groupB;
	auto it = _relationMap.find(key);
	return it != _relationMap.end() ? it->second : oRelation::Unkown;
}

oRelation oData::getRelation( oUnit* unitA, oUnit* unitB ) const
{
	return oData::getRelation(unitA->getGroup(), unitB->getGroup());
}

int oData::getGroupDetectPlayer() const
{
	return PSensor;
}

int oData::getGroupTerrain() const
{
	return Terrain;
}

int oData::getGroupDetect() const
{
	return SenseAll;
}

int oData::getGroupHide() const
{
	return Hide;
}

oData* oData::shared()
{
	static oData g_data;
	return &g_data;
}

void oData::setDamageFactor( uint16 damageType, uint16 defenceType, float bounus )
{
	uint32 key = damageType | defenceType<<16;
	_damageBounusMap[key] = bounus;
}

float oData::getDamageFactor( uint16 damageType, uint16 defenceType ) const
{
	uint32 key = damageType | defenceType<<16;
	unordered_map<uint32, float>::const_iterator it = _damageBounusMap.find(key);
	if (it != _damageBounusMap.end())
	{
		return it->second;
	}
	return 0.0f;
}

bool oData::isPlayerUnit( oBody* body )
{
	int16 index = body->getGroup();
	return P1 <= index && index <= P12;
}

bool oData::isTerrain( oBody* body )
{
	return body->getGroup() == oData::getGroupTerrain();
}

NS_DOROTHY_PLATFORM_END
