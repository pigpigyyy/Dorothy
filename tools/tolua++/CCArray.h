class CCArray: public CCObject
{
	static CCArray* create();
	static CCArray* createWithArray(CCArray* otherArray);
	static CCArray* createWithCapacity(unsigned int capacity);
	static tolua_outside CCArray* CCArray_create @ create(CCObject* objects[tolua_len]);

	tolua_readonly tolua_property__qt unsigned int count;
	tolua_readonly tolua_property__qt unsigned int capacity;
	unsigned int indexOfObject @ index(CCObject* object);
	CCObject* objectAtIndex @ get(unsigned int index);
	tolua_readonly tolua_property__qt CCObject* lastObject @ last;
	tolua_readonly tolua_property__qt CCObject* randomObject;

	bool isEqualToArray @ equals(CCArray* pOtherArray);
	bool containsObject @ contains(CCObject* object);
	void addObject @ add(CCObject* object);
	void addObjectsFromArray @ join(CCArray* otherArray);
	void insertObject @ insert(CCObject* object, unsigned int index);
	void removeLastObject @ removeLast();
	void removeObject @ remove(CCObject* object);
	void removeObjectAtIndex @ removeAt(unsigned int index);
	void removeObjectsInArray @ removeFrom(CCArray* otherArray);
	void removeAllObjects @ clear();
	void fastRemoveObject @ fastRemove(CCObject* object);
	void fastRemoveObjectAtIndex @ fastRemoveAt(unsigned int index);
	void exchangeObject @ swap(CCObject* object1, CCObject* object2);
	void exchangeObjectAtIndex @ swap(unsigned int index1, unsigned int index2);
	void reverseObjects @ reverse();
	void reduceMemoryFootprint @ shrink();
	void replaceObjectAtIndex @ set(unsigned int uIndex, CCObject* pObject);
};
