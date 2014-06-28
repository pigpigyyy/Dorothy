class CCDictionary : public CCObject
{
    unsigned int count();
    CCArray* allKeys();
    CCArray* allKeysForObject(CCObject* object);
    CCObject* objectForKey(const std::string& key);
    CCObject* objectForKey(int key);
    const CCString* valueForKey(const std::string& key);
    const CCString* valueForKey(int key);
    void setObject(CCObject* pObject, const std::string& key);
    void setObject(CCObject* pObject, int key);
    void removeObjectForKey(const std::string& key);
    void removeObjectForKey(int key);
    void removeObjectsForKeys(CCArray* pKeyArray);
    void removeAllObjects();
    CCObject* randomObject();
    static CCDictionary* create();
    static CCDictionary* createWithDictionary(CCDictionary* srcDict);
	static CCDictionary* createWithContentsOfFile(const char *pFileName);
	static CCDictionary* createWithContents(const char* data, unsigned int length);
	static CCDictionary* createWithContentsOfFileThreadSafe(const char *pFileName);
};
