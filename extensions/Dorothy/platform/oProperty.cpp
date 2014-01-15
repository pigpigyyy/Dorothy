#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oProperty.h"

NS_DOROTHY_PLATFORM_BEGIN

oProperty::oProperty( oUnit* owner, float data ):
_owner(owner),
_data(data)
{ }

void oProperty::reset( float value )
{
	_data = value;
}

void oProperty::operator=( float value )
{
	if (_data != value)
	{
		float oldValue = _data;
		_data = value;
		if (changed)
		{
			changed(_owner, oldValue, value);
		}
	}
}

void oProperty::operator+=( float value )
{
	float oldValue = _data;
	_data += value;
	if (changed)
	{
		changed(_owner, oldValue, _data);
	}
}

void oProperty::operator-=( float value )
{
	float oldValue = _data;
	_data -= value;
 	if (changed)
	{
		changed(_owner, oldValue, _data);
	}
}

oProperty::operator float() const
{
	return _data;
}

oUnit* oProperty::getOwner() const
{
	return _owner;
}

oProperty::oProperty( const oProperty& prop )
{
	_data = prop._data;
}

void oProperty::operator=( const oProperty& prop )
{
	//Self assign is not a problem here.
	*this = prop._data;
}

void oProperty::operator+=( const oProperty& prop )
{
	*this += prop._data;
}

void oProperty::operator-=( const oProperty& prop )
{
	*this -= prop._data;
}

bool oProperty::operator==( const oProperty& prop )
{
	return _data == prop._data;
}

bool oProperty::operator!=( const oProperty& prop )
{
	return _data != prop._data;
}

NS_DOROTHY_PLATFORM_END
