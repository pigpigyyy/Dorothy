enum tOrientation{};
module CCOrientation
{
	#define kCCTransitionOrientationLeftOver @ Left
	#define kCCTransitionOrientationRightOver @ Right
	#define kCCTransitionOrientationUpOver @ Up
	#define kCCTransitionOrientationDownOver @ Down	
}

class CCScene: public CCNode
{
    static CCScene* create();
	static tolua_outside CCScene* CCScene_createOriented @ oriented(float duration, CCScene* nextScene, tOrientation orientation);
	static tolua_outside CCScene* CCScene_createRotoZoom @ rotoZoom(float duration, CCScene* nextScene);
	static tolua_outside CCScene* CCScene_createJumpZoom @ jumpZoom(float duration, CCScene* nextScene);
	static tolua_outside CCScene* CCScene_createMove @ move(float duration, CCScene* nextScene, tOrientation orientation);
	static tolua_outside CCScene* CCScene_createSlide @ slide(float duration, CCScene* nextScene, tOrientation orientation);
	static tolua_outside CCScene* CCScene_createShrinkGrow @ shrinkGrow(float duration, CCScene* nextScene);
	static tolua_outside CCScene* CCScene_createFlipX @ flipX(float duration, CCScene* nextScene, tOrientation orientation);
	static tolua_outside CCScene* CCScene_createFlipY @ flipY(float duration, CCScene* nextScene, tOrientation orientation);
	static tolua_outside CCScene* CCScene_createFlipAngular @ flipAngular(float duration, CCScene* nextScene, tOrientation orientation);
	static tolua_outside CCScene* CCScene_createZoomFlipX @ zoomFlipX(float duration, CCScene* nextScene, tOrientation orientation);
	static tolua_outside CCScene* CCScene_createZoomFlipY @ zoomFlipY(float duration, CCScene* nextScene, tOrientation orientation);
	static tolua_outside CCScene* CCScene_createZoomFlipAngular @ zoomFlipAngular(float duration, CCScene* nextScene, tOrientation orientation);
	static tolua_outside CCScene* CCScene_createFade @ fade(float duration, CCScene* nextScene, ccColor3B& color);
	static tolua_outside CCScene* CCScene_createCrossFade @ crossFade(float duration, CCScene* nextScene);
	static tolua_outside CCScene* CCScene_createTurnOffTiles @ turnOffTiles(float duration, CCScene* nextScene);
	static tolua_outside CCScene* CCScene_createSplitCols @ splitCols(float duration, CCScene* nextScene);
	static tolua_outside CCScene* CCScene_createSplitRows @ splitRows(float duration, CCScene* nextScene);
	static tolua_outside CCScene* CCScene_createFadeTiles @ fadeTiles(float duration, CCScene* nextScene, tOrientation orientation);
	static tolua_outside CCScene* CCScene_createPageTurn @ pageTurn(float duration, CCScene* nextScene, bool backward);
	static tolua_outside CCScene* CCScene_createProgressCCW @ progressCCW(float duration, CCScene* nextScene);
	static tolua_outside CCScene* CCScene_createProgressCW @ progressCW(float duration, CCScene* nextScene);
	static tolua_outside CCScene* CCScene_createProgressH @ progressH(float duration, CCScene* nextScene);
	static tolua_outside CCScene* CCScene_createProgressV @ progressV(float duration, CCScene* nextScene);
	static tolua_outside CCScene* CCScene_createProgressIO @ progressIO(float duration, CCScene* nextScene);
	static tolua_outside CCScene* CCScene_createProgressOI @ progressOI(float duration, CCScene* nextScene);
};
