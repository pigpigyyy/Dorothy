class CCEase
{
public:
	static CCActionInterval* holdIn(CCActionInterval* pAction, float fRate);
	static CCActionInterval* holdOut(CCActionInterval* pAction, float fRate);
	static CCActionInterval* holdInOut(CCActionInterval* pAction, float fRate);
	static CCActionInterval* exponentialIn(CCActionInterval* pAction);
	static CCActionInterval* exponentialOut(CCActionInterval* pAction);
	static CCActionInterval* exponentialInOut(CCActionInterval* pAction);
	static CCActionInterval* sineIn(CCActionInterval* pAction);
	static CCActionInterval* sineOut(CCActionInterval* pAction);
	static CCActionInterval* sineInOut(CCActionInterval* pAction);
	static CCActionInterval* elasticIn(CCActionInterval *pAction, float fPeriod = 0.3);
	static CCActionInterval* elasticOut(CCActionInterval *pAction, float fPeriod = 0.3);
	static CCActionInterval* elasticInOut(CCActionInterval *pAction, float fPeriod = 0.3);
	static CCActionInterval* bounceIn(CCActionInterval* pAction);
	static CCActionInterval* bounceOut(CCActionInterval* pAction);
	static CCActionInterval* bounceInOut(CCActionInterval* pAction);
	static CCActionInterval* backIn(CCActionInterval* pAction);
	static CCActionInterval* backOut(CCActionInterval* pAction);
	static CCActionInterval* backInOut(CCActionInterval* pAction);
};
