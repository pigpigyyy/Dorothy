enum tCCImageFormat{};

class CCRenderTexture @ CCRenderTarget: public CCNode
{
	void begin @ beginPaint();
	void beginWithClear @ beginPaint(const ccColor4B& color);
	void render @ draw(CCNode* target);
	void end @ endPaint();
	bool saveToFile @ save(const char *name, tCCImageFormat format = kCCImageFormatJPEG);
	static CCRenderTexture* create(int w, int h);
};
