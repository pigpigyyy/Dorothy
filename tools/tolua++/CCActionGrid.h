module CCGrid
{
	CCFiniteTimeAction* CCStopGrid::create @ stop();

	CCFiniteTimeAction* CCReuseGrid::create @ reuse(int times);

	CCActionInterval* CCWaves3D::create @ waves3D(float duration, CCSize gridSize, unsigned int waves, float amplitude);

	CCActionInterval* CCFlipX3D::create @ flipX3D(float duration);

	CCActionInterval* CCFlipY3D::create @ flipY3D(float duration);

	CCActionInterval* CCLens3D::create @ lens3D(float duration, CCSize gridSize, oVec2 position, float radius);

	CCActionInterval* CCRipple3D::create @ ripple3D(float duration, CCSize gridSize, oVec2 position, float radius, unsigned int waves, float amplitude);

	CCActionInterval* CCShaky3D::create @ shaky3D(float duration, CCSize gridSize, int range, bool shakeZ);

	CCActionInterval* CCLiquid::create @ liquid(float duration, CCSize gridSize, unsigned int waves, float amplitude);

	CCActionInterval* CCWaves::create @ waves(float duration, CCSize gridSize, unsigned int waves, float amplitude, bool horizontal, bool vertical);

	CCActionInterval* CCTwirl::create @ twirl(float duration, CCSize gridSize, oVec2 position, unsigned int twirls, float amplitude);
}