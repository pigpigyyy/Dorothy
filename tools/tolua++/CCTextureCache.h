class CCTextureCache
{
	tolua_outside CCTexture2D* CCTextureCache_add @ add(CCRenderTexture* renderTexture, const char* key);
	
	CCTexture2D* addImage @ load(const char* fileimage);
	void removeAllTextures @ unload();
	static void reloadAllTextures @ reload();
	void removeUnusedTextures @ removeUnused();
	void removeTextureForKey @ remove(const char *textureKeyName);
	void removeTexture @ remove(CCTexture2D* texture);
	
	void dumpCachedTextureInfo @ dumpInfo();
	static CCTextureCache* sharedTextureCache @ create();
};
