#include "Dorothy/const/oDefine.h"
#include "Dorothy/event/oEvent.h"
#include "Dorothy/event/oEventType.h"
#include "Dorothy/event/oListener.h"

NS_DOROTHY_BEGIN

oEvent oEvent::_event;

oEvent::oEvent()
{}

oEvent::oEvent( const string& name ):
_name(name)
{ }

const string& oEvent::getName() const
{
	return _name;
}

hash_strmap<oOwn<oEventType>> oEvent::_eventMap;

void oEvent::addType( const string& name )
{
	auto it = _eventMap.find(name);
	if (it == _eventMap.end())
	{
		_eventMap[name] = oOwnMake(new oEventType(name));
	}
}

bool oEvent::removeType( const string& name )
{
	auto it = _eventMap.find(name);
	if (it != _eventMap.end())
	{
		_eventMap.erase(it);
		return true;
	}
	return false;
}

void oEvent::unreg( oListener* listener )
{
	auto it = _eventMap.find(listener->getName());
	if (it != _eventMap.end())
	{
		it->second->remove(listener);
	}
}

void oEvent::reg( oListener* listener )
{
	auto it = _eventMap.find(listener->getName());
	if (it != _eventMap.end())
	{
		it->second->add(listener);
	}
	else
	{
		oEventType* type = new oEventType(listener->getName());
		_eventMap[listener->getName()] = oOwnMake(type);
		type->add(listener);
	}
}

void oEvent::send( oEvent* e )
{
	auto it = _eventMap.find(e->getName());
	if (it != _eventMap.end())
	{
		it->second->handle(e);
	}
}

oListener* oEvent::addListener( const string& name, const oEventHandler& handler )
{
	oListener* listener = oListener::create(name, handler);
	return listener;
}

void oEvent::send(const string& name)
{
	_event._name = name;
	oEvent::send(&_event);
}

NS_DOROTHY_END