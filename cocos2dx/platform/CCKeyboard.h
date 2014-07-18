#ifndef __DOROTHY_MISC_CCKEYBOARD_H__
#define __DOROTHY_MISC_CCKEYBOARD_H__

class CC_DLL CCKeyboard
{
public:
	enum {MAX_KEY = 256};
	void updateKey(unsigned char key, bool isDown);
	bool isKeyDown(unsigned char key);
	bool isKeyUp(unsigned char key);
	bool isKeyPressed(unsigned char key);
	void clear();
	static CCKeyboard* shared();
private:
	CCKeyboard();
	bool _oldKeyState[MAX_KEY];
	bool _newKeyState[MAX_KEY];
};

#endif // __DOROTHY_MISC_CCKEYBOARD_H__
