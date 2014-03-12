module CCTile
{
	CCActionInterval* CCShakyTiles3D::create @ shaky3D(float duration, CCSize gridSize, int nRange, bool bShakeZ);

	CCActionInterval* CCShatteredTiles3D::create @ shattered3D(float duration, CCSize gridSize, int nRange, bool bShatterZ);

	CCActionInterval* CCShuffleTiles::create @ shuffle(float duration, CCSize gridSize);

	CCActionInterval* CCTile_createFadeOut @ fadeOut(float duration, CCSize gridSize, tOrientation orientation);

	CCActionInterval* CCTurnOffTiles::create @ turnOff(float duration, CCSize gridSize);

	CCActionInterval* CCWavesTiles3D::create @ waves3D(float duration, CCSize gridSize, unsigned int waves, float amplitude);

	CCActionInterval* CCJumpTiles3D::create @ jump3D(float duration, CCSize gridSize, unsigned int numberOfJumps, float amplitude);

	CCActionInterval* CCSplitRows::create @ splitRows(float duration, unsigned int nRows);

	CCActionInterval* CCSplitCols::create @ splitCols(float duration, unsigned int nCols);
}
