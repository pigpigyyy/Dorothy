#include "platform/CCCommon.h"
#include "CCKeyboard.h"
#include <string.h>

CCKeyboard::CCKeyboard()
{
	CCKeyboard::clear();
}

void CCKeyboard::updateKey( unsigned char key, bool isDown )
{
	_oldKeyState[key] = _newKeyState[key];
	_newKeyState[key] = isDown;
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

void CCKeyboard::clear()
{
	memset(_oldKeyState, 0, sizeof(bool)*MAX_KEY);
	memset(_newKeyState, 0, sizeof(bool)*MAX_KEY);
}

CCKeyboard* CCKeyboard::shared()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	static CCKeyboard keyboard;
	return &keyboard;
#else
	return nullptr;
#endif
}
