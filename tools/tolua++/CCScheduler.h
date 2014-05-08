class CCScheduler: public CCObject
{
	tolua_property__common float timeScale;
	
	void scheduleScriptFunc @ shedule(tolua_function nHandler, float fInterval);
	void unscheduleScriptFunc @ unshedule(tolua_function nHandler);
	
	static CCScheduler* create();
};
