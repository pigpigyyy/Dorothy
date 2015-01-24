enum tCCImageFormat{};

class CCRenderTexture @ CCRenderTarget: public CCNode
{
	void beginWithClear @ beginPaint(ccColor4& color = ccColor4());
	void render @ draw(CCNode* target);
	void end @ endPaint();
	bool saveToFile @ save(char *name, tCCImageFormat format = kCCImageFormatJPEG);
	static tolua_outside CCRenderTexture* CCRenderTexture_create @ create(int w, int h, bool withDepthStencil = false);
};
