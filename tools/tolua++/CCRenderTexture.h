enum tCCImageFormat{};

class CCRenderTexture @ CCRenderTarget: public CCNode
{
	void beginWithClear @ beginPaint(const ccColor4B& color = ccColor4B());
	void render @ draw(CCNode* target);
	void end @ endPaint();
	bool saveToFile @ save(const char *name, tCCImageFormat format = kCCImageFormatJPEG);
	static tolua_outside CCRenderTexture* CCRenderTexture_create @ create(int w, int h, bool withDepthStencil = false);
};
