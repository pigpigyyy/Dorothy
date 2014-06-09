/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

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
