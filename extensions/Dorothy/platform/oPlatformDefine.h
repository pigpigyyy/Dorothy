/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_PLATFORM_OPLATFORMDEFINE_H__
#define __DOROTHY_PLATFORM_OPLATFORMDEFINE_H__

#define NS_DOROTHY_PLATFORM_BEGIN namespace Dorothy { namespace Platform {
#define NS_DOROTHY_PLATFORM_END }}

NS_DOROTHY_PLATFORM_BEGIN

ENUM_START(oAttackType)
{
	Melee = 0,
	Range = 1
}
ENUM_END

ENUM_START(oAttackTarget)
{
	Single = 0,
	Multi = 1
}
ENUM_END

ENUM_START(oRelation)
{
	Unkown = 0,
	Friend = 1<<0,
	Neutral = 1<<1,
	Enemy = 1<<2,
	Any = Friend|Neutral|Enemy
}
ENUM_END

/*
Target Allow
	oRelation
		e_unkown 0
		e_friend 1<<0
		e_neutral 1<<1
		e_enemy 1<<2
	oGroup
		oSharedData.getTerrainGroup() 1<<3
*/
class oTargetAllow
{
public:
	oTargetAllow();
	void setTerrainAllowed(bool var);
	bool isTerrainAllowed() const;
	void allow(oRelation flag, bool allow);
	bool isAllow(oRelation flag);
protected:
	int _flag;
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OPLATFORMDEFINE_H__