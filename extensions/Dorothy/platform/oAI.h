/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

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
	static oRef<oUnit> _self;

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
