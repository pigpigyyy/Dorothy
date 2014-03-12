#include "Dorothy/const/oDefine.h"
#include "Dorothy/event/oEventType.h"
#include "Dorothy/event/oEvent.h"
#include "Dorothy/event/oListener.h"

NS_DOROTHY_BEGIN

oEventType::oEventType( const string& name ):
_name(name)
{ }

const string& oEventType::getName() const
{
	return _name;
}

void oEventType::add( oListener* listener )
{
	if (listener->_order == oListener::INVALID_ORDER)
	{
		listener->_order = _listeners.size();
		_listeners.push_back(listener);
	}
}

void oEventType::remove( oListener* listener )
{
	if (listener->_order != oListener::INVALID_ORDER)
	{
		_listeners[listener->_order] = nullptr;
		listener->_order = oListener::INVALID_ORDER;
	}
}

void oEventType::handle( oEvent* e )
{
	for (int i = 0; i < (int)_listeners.size(); i++)
	{
		if (_listeners[i] == nullptr)
		{
			int last = _listeners.size() - 1;
			for (;last >= 0 && _listeners[last] == nullptr;_listeners.pop_back(), --last);
			if (i > last)
			{
				break;
			}
			if (_listeners.size() > 0)
			{
				_listeners[i] = _listeners[_listeners.size() - 1];
				_listeners[i]->_order = i;
				_listeners.pop_back();
			}
		}
		_listeners[i]->handle(e);
	}
}

NS_DOROTHY_END
