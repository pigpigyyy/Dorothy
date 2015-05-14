/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/physics/oSensor.h"
#include "Dorothy/physics/oBody.h"
#include "Dorothy/physics/oWorld.h"

NS_DOROTHY_BEGIN

oSensor::oSensor(oBody* owner, int tag, b2Fixture* fixture):
_owner(owner),
_tag(tag),
_fixture(fixture),
_enabled(true),
_sensedBodies(CCArray::create())
{ }

oSensor::~oSensor()
{
	oSensor::clear();
	_fixture = nullptr;
}

void oSensor::add( oBody* body )
{
	_sensedBodies->addObject(body);
	if (bodyEnter)
	{
		bodyEnter(this, body);
	}
}

void oSensor::remove( oBody* body )
{
	if (_sensedBodies->fastRemoveObject(body) && bodyLeave)
	{
		bodyLeave(this, body);
	}
}

bool oSensor::contains( oBody* body )
{
	CCARRAY_START(oBody, item, _sensedBodies)
	{
		if (item == body)
		{
			return true;
		}
	}
	CCARRAY_END
	return false;
}

void oSensor::clear()
{
	_sensedBodies->removeAllObjects();
}

CCArray* oSensor::getSensedBodies() const
{
	return _sensedBodies;
}

void oSensor::setEnabled( bool enable )
{
	_enabled = enable;
	if (!enable)
	{
		oSensor::clear();
	}
}

bool oSensor::isEnabled() const
{
	return _enabled;
}

int oSensor::getTag() const
{
	return _tag;
}

void oSensor::setGroup(int var)
{
	_fixture->SetFilterData(_owner->getWorld()->getFilter(var));
}

int oSensor::getGroup() const
{
	return _fixture->GetFilterData().groupIndex;
}

oBody* oSensor::getOwner() const
{
	return _owner;
}

b2Fixture* oSensor::getFixture() const
{
	return _fixture;
}

oSensor* oSensor::create( oBody* owner, int tag, b2Fixture* fixture )
{
	oSensor* sensor = new oSensor(owner, tag, fixture);
	INIT(sensor);
	sensor->autorelease();
	return sensor;
}

bool oSensor::isSensed() const
{
	return _sensedBodies->count() > 0;
}

NS_DOROTHY_END
