module oCache
{
	class oAnimationCache @ Animation
	{
		static tolua_outside bool oAnimationCache_load @ load( const char* filename );
		static tolua_outside bool oAnimationCache_update @ update(const char* name, const char* content);
		static tolua_outside bool oAnimationCache_unload @ unload( const char* filename = nullptr);
	};
	
	class oParticleCache @ Particle
	{
		static tolua_outside bool oParticleCache_load @ load( const char* filename );
		static tolua_outside bool oParticleCache_update @ update(const char* name, const char* content);
		static tolua_outside bool oParticleCache_unload @ unload( const char* filename = nullptr );
	};

	class oEffectCache @ Effect
	{
		static tolua_outside bool oEffectCache_load @ load( const char* filename );
		static tolua_outside bool oEffectCache_update @ update(const char* content);
		static tolua_outside bool oEffectCache_unload @ unload();
	};

	class oModelCache @ Model
	{
		static tolua_outside bool oModelCache_load @ load( const char* filename );
		static tolua_outside bool oModelCache_update @ update(const char* name, const char* content);
		static tolua_outside bool oModelCache_unload @ unload( const char* filename = nullptr );
	};

	class oClipCache @ Clip
	{
		static tolua_outside bool oClipCache_load @ load( const char* filename );
		static tolua_outside bool oClipCache_update @ update(const char* name, const char* content);
		static tolua_outside bool oClipCache_unload @ unload( const char* filename = nullptr );
	};
	
	void oCache_clear @ clear();
}
