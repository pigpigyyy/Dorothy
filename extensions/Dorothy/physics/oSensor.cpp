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
	sensor->autorelease();
	return sensor;
}

bool oSensor::isSensed() const
{
	return _sensedBodies->count() > 0;
}

NS_DOROTHY_END
