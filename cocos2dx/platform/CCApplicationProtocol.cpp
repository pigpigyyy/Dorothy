#include "CCCommon.h"
#include "CCApplicationProtocol.h"
#include "script_support/CCScriptSupport.h"

NS_CC_BEGIN

CCApplicationProtocol::CCApplicationProtocol():
_handler(0)
{ }

CCApplicationProtocol::~CCApplicationProtocol()
{
	CCApplicationProtocol::setScriptHandler(0);
}

void CCApplicationProtocol::setScriptHandler(int handler)
{
	if (_handler)
	{
		CCScriptEngine::sharedEngine()->removeScriptHandler(_handler);
	}
	_handler = handler;
}
int CCApplicationProtocol::getScriptHandler() const
{
	return _handler;
}

void CCApplicationProtocol::applicationDidEnterBackground()
{
	if (_handler)
	{
		CCScriptEngine::sharedEngine()->executeApplicationEvent(_handler, CCApplicationProtocol::EnterBackground);
	}
}

void CCApplicationProtocol::applicationWillEnterForeground()
{
	if (_handler)
	{
		CCScriptEngine::sharedEngine()->executeApplicationEvent(_handler, CCApplicationProtocol::EnterForeground);
	}
}

void CCApplicationProtocol::applicationDidReceiveMemoryWarning()
{
	if (_handler)
	{
		CCScriptEngine::sharedEngine()->executeApplicationEvent(_handler, CCApplicationProtocol::LowMemoryWarning);
	}
}

NS_CC_END
