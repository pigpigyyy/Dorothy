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