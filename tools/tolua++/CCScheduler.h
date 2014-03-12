class CCScheduler: public CCObject
{
	tolua_property__common float timeScale;
	
	void scheduleScriptFunc @ shedule(LUA_FUNCTION nHandler, float fInterval);
	void unscheduleScriptFunc @ unshedule(LUA_FUNCTION nHandler);
	
	static CCScheduler* create();
};
