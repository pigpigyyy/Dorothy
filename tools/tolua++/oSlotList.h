class oSlotList : public CCObject
{
	void add(tolua_function handler);
	bool remove(tolua_function handler);
	void clear();
};