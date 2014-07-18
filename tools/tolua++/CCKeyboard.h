class CCKeyboard
{
	bool isKeyDown(unsigned char key);
	bool isKeyUp(unsigned char key);
	bool isKeyPressed(unsigned char key);
	static CCKeyboard* shared @ create();
};
