/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_PLATFORM_OAI_H__
#define __DOROTHY_PLATFORM_OAI_H__
#include "platform/oAINode.h"

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

	static void add(const string& name, oAILeaf* leaf);
	static void clear();
	static oAILeaf* get(const string& name);
private:
	oAI();
	static oAI& getAI();

	oRef<oUnit> _self;

	oUnit* _nearestUnit;
	oUnit* _nearestFriend;
	oUnit* _nearestEnemy;
	oUnit* _nearestNeutral;

	oRef<CCArray> _friends;
	oRef<CCArray> _enemies;
	oRef<CCArray> _neutrals;
	oRef<CCArray> _detectedUnits;

	float _nearestUnitDistance;
	float _nearestFriendDistance;
	float _nearestEnemyDistance;
	float _nearestNeutralDistance;

	float _oldInstinctValue;
	float _newInstinctValue;

	unordered_map<string, oRef<oAILeaf>> _reflexArcs;
	friend class oInstinct;
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OAI_H__
