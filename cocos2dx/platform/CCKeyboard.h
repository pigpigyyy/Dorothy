#ifndef __DOROTHY_MISC_CCKEYBOARD_H__
#define __DOROTHY_MISC_CCKEYBOARD_H__

NS_CC_BEGIN

class CC_DLL CCKeyboard
{
public:
	enum {MAX_KEY = 256};
	void updateKey(unsigned char key, bool isDown);
	bool isKeyDown(unsigned char key);
	bool isKeyUp(unsigned char key);
	bool isKeyPressed(unsigned char key);
	void clear();
	static CCKeyboard* sharedKeyboard();
private:
	CCKeyboard();
	bool _oldKeyState[MAX_KEY];
	bool _newKeyState[MAX_KEY];
};

NS_CC_END

#endif // __DOROTHY_MISC_CCKEYBOARD_H__
