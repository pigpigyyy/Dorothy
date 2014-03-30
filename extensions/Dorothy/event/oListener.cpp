#include "Dorothy/const/oDefine.h"
#include "Dorothy/event/oEvent.h"
#include "Dorothy/event/oListener.h"
#include "Dorothy/misc/oScriptHandler.h"

NS_DOROTHY_BEGIN

const int oListener::INVALID_ORDER = -1;

void oListener::setEnabled( bool enable )
{
	if (enable)
	{
		oEvent::reg(this);
	}
	else
	{
		oEvent::unreg(this);
	}
}

bool oListener::isEnabled() const
{
	return _order != INVALID_ORDER;
}

void oListener::setHandler( const oEventHandler& handler )
{
	_handler = handler;
}

const oEventHandler& oListener::getHandler() const
{
	return _handler;
}

void oListener::handle( oEvent* e )
{
	if (_handler)
	{
		_handler(e);
	}
}

oListener* oListener::create( const string& name, const oEventHandler& handler )
{
	oListener* listener = new oListener(name, handler);
	listener->autorelease();
	listener->setEnabled(true);
	return listener;
}

oListener::oListener( const string& name, const oEventHandler& handler ):
_name(name),
_handler(handler),
_order(INVALID_ORDER)
{ }

const string& oListener::getName() const
{
	return _name;
}

oListener::~oListener()
{
	oListener::setEnabled(false);
}

NS_DOROTHY_END
