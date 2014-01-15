#include "Dorothy/const/oDefine.h"
#include "Dorothy/misc/oScriptHandler.h"

NS_DOROTHY_BEGIN

oScriptHandler::oScriptHandler(int handler)
:_handler(handler)
{ }

oScriptHandler::~oScriptHandler()
{
	CCScriptEngine::sharedEngine()->removeScriptHandler(_handler);
}

oScriptHandler* oScriptHandler::create(int handler)
{
	oScriptHandler* scriptHandler = new oScriptHandler(handler);
	scriptHandler->autorelease();
	return scriptHandler;
}

int oScriptHandler::get() const
{
	return _handler;
}

oHandlerWrapper::oHandlerWrapper( int handler ):
	_handler(oScriptHandler::create(handler))
{ }

bool oHandlerWrapper::operator==( const oHandlerWrapper& handler ) const
{
	return CCScriptEngine::sharedEngine()->scriptHandlerEqual(_handler->get(), handler._handler->get());
}

int oHandlerWrapper::getHandler() const
{
	return _handler->get();
}

NS_DOROTHY_END
