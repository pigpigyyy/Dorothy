#ifndef __DOROTHY_PLATFORM_OAI_H__
#define __DOROTHY_PLATFORM_OAI_H__
#include "Dorothy/platform/oAINode.h"

NS_DOROTHY_PLATFORM_BEGIN

class oUnit;

class oAI
{
public:
	enum {None = -1};
	static bool conditionedReflex(oUnit* unit);

	static oUnit* getSelf();
	static float getOldInstinctValue();
	static float getNewInstinctValue();
	static CCArray* getUnitsByRelation(oRelation relation);
	static CCArray* getDetectedUnits();
	static oUnit* getNearestUnit(oRelation relation);
	static float getNearestUnitDistance(oRelation relation);

	static void add(int id, oAILeaf* leaf);
	static void clear();
	static oAILeaf* get(int id);
private:
	static oUnit* _self;

	static oUnit* _nearestUnit;
	static oUnit* _nearestFriend;
	static oUnit* _nearestEnemy;
	static oUnit* _nearestNeutral;

	static oRef<CCArray> _friends;
	static oRef<CCArray> _enemies;
	static oRef<CCArray> _neutrals;
	static oRef<CCArray> _detectedUnits;

	static float _nearestUnitDistance;
	static float _nearestFriendDistance;
	static float _nearestEnemyDistance;
	static float _nearestNeutralDistance;

	static float _oldInstinctValue;
	static float _newInstinctValue;

	static unordered_map<int, oRef<oAILeaf>> _reflexArcs;
	friend class oInstinct;
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OAI_H__
