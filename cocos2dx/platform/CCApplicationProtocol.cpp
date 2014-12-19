#include "CCCommon.h"
#include "CCApplicationProtocol.h"
#include "script_support/CCScriptSupport.h"

NS_CC_BEGIN

CCApplicationProtocol::CCApplicationProtocol():
_handler(0)
{ }

CCApplicationProtocol::~CCApplicationProtocol()
{
	CCApplicationProtocol::unregisterScriptHandler();
}

void CCApplicationProtocol::registerScriptHandler(int handler)
{
	CCApplicationProtocol::unregisterScriptHandler();
	_handler = handler;
}

void CCApplicationProtocol::unregisterScriptHandler()
{
	if (_handler)
	{
		CCScriptEngine::sharedEngine()->removeScriptHandler(_handler);
		_handler = 0;
	}
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
