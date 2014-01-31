#ifndef __DOROTHY_MODULE_H__
#define __DOROTHY_MODULE_H__

#include "Dorothy.h"
using namespace Dorothy;
using namespace Dorothy::Platform;

#define __CCEGLView (CCEGLView::sharedOpenGLView())
#define __CCFileUtils (CCFileUtils::sharedFileUtils())
#define __CCApplication (CCApplication::sharedApplication())
#define __CCDirector (CCDirector::sharedDirector())

#define __oContent (oContent::shared())
#define __oData (oData::shared())

void CCDrawNode_drawPolygon(
	CCDrawNode* self,
	unsigned int count, oVec2* verts,
	const ccColor4B& fillColor, float borderWidth,
	const ccColor4B& borderColor);

void oModel_addHandler(oModel* model, const string& name, int nHandler);
void oModel_removeHandler(oModel* model, const string& name, int nHandler);
void oModel_clearHandler(oModel* model, const string& name);
const oVec2& oModel_getKey(oModel* model, uint32 index);

void oWorld_query(oWorld* world, const CCRect& rect, int nHandler);

ENUM_START(oSensorFlag)
{
	Enter,
	Leave
}
ENUM_END
void oSensor_addHandler(oSensor* sensor, uint32 flag, int nHandler);
void oSensor_removeHandler(oSensor* sensor, uint32 flag, int nHandler);
void oSensor_clearHandler(oSensor* sensor, uint32 flag);

bool oAnimationCache_load(const char* filename);
bool oAnimationCache_unload(const char* filename = nullptr);

bool oClipCache_load(const char* filename);
bool oClipCache_unload(const char* filename = nullptr);

bool oEffectCache_load(const char* filename);
bool oEffectCache_unload();

bool oParticleCache_load(const char* filename);
bool oParticleCache_unload(const char* filename = nullptr);

bool oModelCache_load(const char* filename);
bool oModelCache_unload(const char* filename = nullptr);

void oCache_clear();

CCSprite* CCSprite_createWithClip(const char* clipStr);

CCScene* CCScene_createOriented(float duration, CCScene* nextScene, tOrientation orientation);
CCScene* CCScene_createRotoZoom(float duration, CCScene* nextScene);
CCScene* CCScene_createJumpZoom(float duration, CCScene* nextScene);
CCScene* CCScene_createMove(float duration, CCScene* nextScene, tOrientation orientation);
CCScene* CCScene_createSlide(float duration, CCScene* nextScene, tOrientation orientation);
CCScene* CCScene_createShrinkGrow(float duration, CCScene* nextScene);
CCScene* CCScene_createFlipX(float duration, CCScene* nextScene, tOrientation orientation);
CCScene* CCScene_createFlipY(float duration, CCScene* nextScene, tOrientation orientation);
CCScene* CCScene_createFlipAngular(float duration, CCScene* nextScene, tOrientation orientation);
CCScene* CCScene_createZoomFlipX(float duration, CCScene* nextScene, tOrientation orientation);
CCScene* CCScene_createZoomFlipY(float duration, CCScene* nextScene, tOrientation orientation);
CCScene* CCScene_createZoomFlipAngular(float duration, CCScene* nextScene, tOrientation orientation);
CCScene* CCScene_createFade(float duration, CCScene* nextScene, const ccColor3B& color);
CCScene* CCScene_createCrossFade(float duration, CCScene* nextScene);
CCScene* CCScene_createTurnOffTiles(float duration, CCScene* nextScene);
CCScene* CCScene_createSplitCols(float duration, CCScene* nextScene);
CCScene* CCScene_createSplitRows(float duration, CCScene* nextScene);
CCScene* CCScene_createFadeTiles(float duration, CCScene* nextScene, tOrientation orientation);
CCScene* CCScene_createPageTurn(float duration, CCScene* nextScene, bool backward);
CCScene* CCScene_createProgressCCW(float duration, CCScene* nextScene);
CCScene* CCScene_createProgressCW(float duration, CCScene* nextScene);
CCScene* CCScene_createProgressH(float duration, CCScene* nextScene);
CCScene* CCScene_createProgressV(float duration, CCScene* nextScene);
CCScene* CCScene_createProgressIO(float duration, CCScene* nextScene);
CCScene* CCScene_createProgressOI(float duration, CCScene* nextScene);

CCCardinalSplineTo* CCCardinalSplineTo_create(float duration, const vector<oVec2>& points, float tension);
CCCardinalSplineBy* CCCardinalSplineBy_create(float duration, const vector<oVec2>& points, float tension);
CCCatmullRomTo* CCCatmullRomTo_create(float duration, const vector<oVec2>& points);
CCCatmullRomBy* CCCatmullRomBy_create(float duration, const vector<oVec2>& points);

CCActionInterval* CCTile_createFadeOut(float duration, CCSize gridSize, tOrientation orientation);

inline ccBlendFunc* ccBlendFuncNew(GLenum src, GLenum dst)
{
	ccBlendFunc* func = new ccBlendFunc{ src, dst };
	return func;
}

#endif // __DOROTHY_MODULE_H__
