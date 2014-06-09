/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_PLATFORM_ODATA_H__
#define __DOROTHY_PLATFORM_ODATA_H__

NS_DOROTHY_PLATFORM_BEGIN

class oUnit;
class oPlatformWorld;

class oData
{
public:
	void apply(oPlatformWorld* world);
	void setRelation(int groupA, int groupB, oRelation relation);
	oRelation getRelation(int groupA, int groupB) const;
	oRelation getRelation(oUnit* unitA, oUnit* unitB) const;
	PROPERTY_READONLY(int, GroupHide);
	PROPERTY_READONLY(int, GroupDetectPlayer);
	PROPERTY_READONLY(int, GroupTerrain);
	PROPERTY_READONLY(int, GroupDetect);
	void setDamageFactor(uint16 damageType, uint16 defenceType, float bounus);
	float getDamageFactor(uint16 damageType, uint16 defenceType) const;
	bool isPlayerUnit(oBody* body);
	bool isTerrain(oBody* body);
	static oData* shared();
private:
	unordered_map<int, oRelation> _relationMap;
	unordered_map<uint32, float> _damageBounusMap;
};

#define oSharedData (*oData::shared())

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_ODATA_H__