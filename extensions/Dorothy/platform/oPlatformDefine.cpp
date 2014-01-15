#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"

NS_DOROTHY_PLATFORM_BEGIN

oTargetAllow::oTargetAllow():
_flag(0)
{ }

void oTargetAllow::allow( oRelation flag, bool allow )
{
	if (allow)
	{
		_flag |= flag;
	}
	else
	{
		_flag &= ~flag;
	}
}

bool oTargetAllow::isAllow( oRelation flag )
{
	return (_flag & flag) != 0;
}

void oTargetAllow::setTerrainAllowed(bool var)
{
	if (var)
	{
		_flag |= (1<<3);
	}
	else
	{
		_flag &= ~(1<<3);
	}
}

bool oTargetAllow::isTerrainAllowed() const
{
	return (_flag & (1<<3)) != 0;
}

NS_DOROTHY_PLATFORM_END
