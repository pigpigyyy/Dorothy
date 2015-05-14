/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

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
	INIT(scriptHandler);
	scriptHandler->autorelease();
	return scriptHandler;
}

void oScriptHandler::set(int handler)
{
	if (_handler)
	{
		CCScriptEngine::sharedEngine()->removeScriptHandler(_handler);
	}
	_handler = handler;
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
