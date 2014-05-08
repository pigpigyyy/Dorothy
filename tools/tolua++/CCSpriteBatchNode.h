class CCSpriteBatchNode: public CCNode
{
	static CCSpriteBatchNode* createWithTexture(CCTexture2D* tex);
	static CCSpriteBatchNode* createWithTexture(CCTexture2D* tex, unsigned int capacity);
	static CCSpriteBatchNode* create(const char* fileImage, unsigned int capacity);
	static CCSpriteBatchNode* create(const char* fileImage);
};
