#include "platform/CCCommon.h"
#include "CCKeyboard.h"
#include "CCDirector.h"
#include "CCScheduler.h"
#include <string.h>

NS_CC_BEGIN

CCKeyboard::CCKeyboard():
_needUpdate(false)
{
	CCKeyboard::clear();
	CCKeyboard::init();
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this,0);
}

void CCKeyboard::updateKey( unsigned char key, bool isDown )
{
	_oldKeyState[key] = _newKeyState[key];
	_newKeyState[key] = isDown;
	_needUpdate = true;
}

bool CCKeyboard::isKeyDown( unsigned char key )
{
	return !_oldKeyState[key] && _newKeyState[key];
}

bool CCKeyboard::isKeyUp( unsigned char key )
{
	return _oldKeyState[key] && !_newKeyState[key];
}

bool CCKeyboard::isKeyPressed( unsigned char key )
{
	return _newKeyState[key];
}

void CCKeyboard::update(float dt)
{
	if (_needUpdate)
	{
    	_needUpdate = false;
		memcpy(_oldKeyState, _newKeyState, sizeof(bool)*MAX_KEY);
	}
}

void CCKeyboard::clear()
{
	memset(_oldKeyState, 0, sizeof(bool)*MAX_KEY);
	memset(_newKeyState, 0, sizeof(bool)*MAX_KEY);
}

CCKeyboard* CCKeyboard::sharedKeyboard()
{
	static CCKeyboard keyboard;
	return &keyboard;
}

NS_CC_END
