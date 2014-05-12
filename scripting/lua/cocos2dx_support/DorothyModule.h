#ifndef __DOROTHY_MODULE_H__
#define __DOROTHY_MODULE_H__

#include "Dorothy.h"
using namespace Dorothy;
using namespace Dorothy::Platform;

void CCDrawNode_drawPolygon(
	CCDrawNode* self,
	oVec2* verts,
	int count,
	const ccColor4B& fillColor, float borderWidth,
	const ccColor4B& borderColor);
void CCDrawNode_drawPolygon(
	CCDrawNode* self,
	oVec2* verts,
	int count,
	const ccColor4B& fillColor);

void oModel_addHandler(oModel* model, const string& name, int nHandler);
void oModel_removeHandler(oModel* model, const string& name, int nHandler);
void oModel_clearHandler(oModel* model, const string& name);
const oVec2& oModel_getKey(oModel* model, uint32 index);

void oWorld_query(oWorld* world, const CCRect& rect, int nHandler);

ENUM_START(oSensorEvent)
{
	Enter,
	Leave
}
ENUM_END
void oSensor_addHandler(oSensor* sensor, uint32 flag, int nHandler);
void oSensor_removeHandler(oSensor* sensor, uint32 flag, int nHandler);
void oSensor_clearHandler(oSensor* sensor, uint32 flag);

bool oAnimationCache_load(const char* filename);
bool oAnimationCache_update(const char* name, const char* content);
bool oAnimationCache_unload(const char* filename = nullptr);

bool oClipCache_load(const char* filename);
bool oClipCache_update(const char* name, const char* content);
bool oClipCache_unload(const char* filename = nullptr);
void __oClipCache_getNames(const char* filename);
#define oClipCache_getNames(filename) {__oClipCache_getNames(filename);return 1;}

bool oEffectCache_load(const char* filename);
bool oEffectCache_update(const char* content);
bool oEffectCache_unload();

bool oParticleCache_load(const char* filename);
bool oParticleCache_update(const char* name, const char* content);
bool oParticleCache_unload(const char* filename = nullptr);

bool oModelCache_load(const char* filename);
bool oModelCache_update(const char* name, const char* content);
bool oModelCache_unload(const char* filename = nullptr);

void oCache_clear();

void oUnitDef_setActions(oUnitDef* def, int actions[], int count);
void oUnitDef_setInstincts(oUnitDef* def, int instincts[], int count);

oListener* oListener_create(const string& name, int handler);

void __oContent_getDirEntries(oContent* self, const char* path, bool isFolder);
#define oContent_getDirEntries(self,path,isFolder) {__oContent_getDirEntries(self,path,isFolder);return 1;}

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

CCCardinalSplineTo* CCCardinalSplineTo_create(float duration, const oVec2 points[], int count, float tension);
CCCardinalSplineBy* CCCardinalSplineBy_create(float duration, const oVec2 points[], int count, float tension);
CCCatmullRomTo* CCCatmullRomTo_create(float duration, const oVec2 points[], int count);
CCCatmullRomBy* CCCatmullRomBy_create(float duration, const oVec2 points[], int count);

CCActionInterval* CCTile_createFadeOut(float duration, CCSize gridSize, tOrientation orientation);

CCArray* CCArray_create(CCObject* object[], int count);
unsigned int CCArray_index(CCArray* array, CCObject* object);
CCObject* CArray_get(CCArray* array, unsigned int index);
void CArray_insert(CCArray* array, CCObject* object, unsigned int index);
void CArray_removeAt(CCArray* array, unsigned int index);
void CArray_exchange(CCArray* array, unsigned int index1, unsigned int index2);
void CArray_fastRemoveAt(CCArray* array, unsigned int index);
void CArray_set(CCArray* array, unsigned int uIndex, CCObject* pObject);

CCTexture2D* CCTextureCache_add(CCTextureCache* self, CCRenderTexture* renderTexture, const char* name);

void __oModelCache_getData(const char* filename);
#define oModelCache_getData(filename) {__oModelCache_getData(filename);return 1;}
oModelDef* oModelCache_loadData(const char* filename, int tableIndex);
void oModelCache_save(const char* itemName, const char* targetName);

inline ccBlendFunc* ccBlendFuncNew(GLenum src, GLenum dst)
{
	return new ccBlendFunc{ src, dst };
}

class CCCall: public CCActionInstant
{
public:
	CCCall():_scriptHandler(0){}
	virtual ~CCCall();
	static CCCall* create(int nHandler);
	virtual void execute();
	virtual void update(float time);
	CCObject* copyWithZone(CCZone *pZone);
private:
	int _scriptHandler;
};

ENUM_START(oTextFieldEvent)
{
	Attach,
	Detach,
	Insert,
	Inserted,
	Delete,
	Deleted
}
ENUM_END
CCTextFieldTTF* CCTextFieldTTF_create(const char* placeholder, const char* fontName, float fontSize);
void CCTextFieldTTF_registerInputHandler(CCTextFieldTTF* textField, int handler);
void CCTextFieldTTF_unregisterInputHandler(CCTextFieldTTF* textField);

CCRenderTexture* CCRenderTexture_create(int w, int h, bool withDepthStencil = false);

#endif // __DOROTHY_MODULE_H__
