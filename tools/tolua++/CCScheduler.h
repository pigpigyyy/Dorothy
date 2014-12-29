class CCScheduler: public CCObject
{
	tolua_property__common float timeScale;

	void scheduleUpdateForTarget @ shedule(CCScheduler* pTarget, int nPriority = 0);
	void scheduleScriptFunc @ shedule(tolua_function nHandler, float fInterval = 0);

    void unscheduleUpdateForTarget @ unshedule(CCScheduler* pTarget);
	void unscheduleScriptFunc @ unshedule(tolua_function nHandler);

	static CCScheduler* create();
};
