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
oVec2 oModel_getKey(oModel* model, const char* key);

void oWorld_query(oWorld* world, const CCRect& rect, int nHandler);
void oWorld_cast(oWorld* world, const oVec2& start, const oVec2& end, bool closest, int handler);

ENUM_START(oSensorEvent)
{
	Enter,
	Leave
}
ENUM_END(oSensorEvent)
void oSensor_addHandler(oSensor* sensor, uint32 flag, int nHandler);
void oSensor_removeHandler(oSensor* sensor, uint32 flag, int nHandler);
void oSensor_clearHandler(oSensor* sensor, uint32 flag);

ENUM_START(oBodyEvent)
{
	ContactStart,
	ContactEnd
}
ENUM_END(oBodyEvent)
void oBody_addHandler(oBody* body, uint32 flag, int nHandler);
void oBody_removeHandler(oBody* body, uint32 flag, int nHandler);
void oBody_clearHandler(oBody* body, uint32 flag);

bool oAnimationCache_load(const char* filename);
bool oAnimationCache_update(const char* name, const char* content);
bool oAnimationCache_unload(const char* filename = nullptr);
void oAnimationCache_removeUnused();

bool oClipCache_load(const char* filename);
bool oClipCache_update(const char* name, const char* content);
bool oClipCache_unload(const char* filename = nullptr);
void oClipCache_removeUnused();
void __oClipCache_getNames(lua_State* L,  const char* filename);
#define oClipCache_getNames(filename) {__oClipCache_getNames(tolua_S,filename);return 1;}
void __oClipCache_getTextureFile(lua_State* L, const char* filename);
#define oClipCache_getTextureFile(filename) {__oClipCache_getTextureFile(tolua_S,filename);return 1;}

bool oEffectCache_load(const char* filename);
bool oEffectCache_update(const char* content);
bool oEffectCache_unload();

bool oParticleCache_load(const char* filename);
bool oParticleCache_update(const char* name, const char* content);
bool oParticleCache_unload(const char* filename = nullptr);
void oParticleCache_removeUnused();

bool oModelCache_load(const char* filename);
bool oModelCache_update(const char* name, const char* content);
bool oModelCache_unload(const char* filename = nullptr);
void oModelCache_removeUnused();

void oCache_removeUnused();
void oCache_clear();
// return collected memory size in bytes
int oCache_poolCollect();
// return current allocated memory size
int oCache_poolSize();

void oUnitDef_setActions(oUnitDef* def, char* actions[], int count);
void oUnitDef_setInstincts(oUnitDef* def, int instincts[], int count);

oListener* oListener_create(const string& name, int handler);

void __oContent_getDirEntries(lua_State* L, oContent* self, const char* path, bool isFolder);
#define oContent_getDirEntries(self,path,isFolder) {__oContent_getDirEntries(tolua_S,self,path,isFolder);return 1;}
void oContent_copyFileAsync(oContent* self, const char* src, const char* dst, int handler);
void oContent_setSearchPaths(oContent* self, char* paths[], int length);
void oContent_setSearchResolutionsOrder(oContent* self, char* paths[], int length);

CCSprite* CCSprite_createWithClip(const char* clipStr);

CCScene* CCScene_createMove(float duration, CCScene* nextScene, tOrientation orientation);
CCScene* CCScene_createSlide(float duration, CCScene* nextScene, tOrientation orientation);
CCScene* CCScene_createFadeTiles(float duration, CCScene* nextScene, tOrientation orientation);
CCScene* CCScene_createFlipAngular(float duration, CCScene* nextScene, bool rightOver = true);
CCScene* CCScene_createFlip(float duration, CCScene* nextScene, tOrientation orientation);
CCScene* CCScene_createZoomFlip(float duration, CCScene* nextScene, tOrientation orientation);
CCScene* CCScene_createZoomFlipAngular(float duration, CCScene* nextScene, bool rightOver = true);

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

int CCDictionary_get(lua_State* L);
int CCDictionary_set(lua_State* L);
int CCDictionary_keys(lua_State* L);
int CCDictionary_randomObject(lua_State* L);

void __oModelCache_getData(lua_State* L,  const char* filename);
#define oModelCache_getData(filename) {__oModelCache_getData(tolua_S,filename);return 1;}
oModelDef* __oModelCache_loadData(lua_State* L, const char* filename, int tableIndex);
#define oModelCache_loadData(filename,tableIndex) {__oModelCache_loadData(tolua_S,filename,tableIndex);}
void oModelCache_save(const char* itemName, const char* targetName);

#define ccBlendFuncNew(src, dst) new ccBlendFunc{ src, dst }

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
ENUM_END(oTextFieldEvent)
CCTextFieldTTF* CCTextFieldTTF_create(const char* placeholder, const char* fontName, float fontSize);
void CCTextFieldTTF_registerInputHandler(CCTextFieldTTF* textField, int handler);
void CCTextFieldTTF_unregisterInputHandler(CCTextFieldTTF* textField);

CCRenderTexture* CCRenderTexture_create(int w, int h, bool withDepthStencil = false);

int CCTextureCache_loadAsync(lua_State* L);

class ccColor3
{
public:
	ccColor3():r(255), g(255), b(255){}
	ccColor3(unsigned int value):
	r((value&0x00FF0000)>>16),
	g((value&0x0000FF00)>>8),
	b(value&0x000000FF){}
	ccColor3(GLubyte r, GLubyte g, GLubyte b):r(r), g(g), b(b){}
	ccColor3(const ccColor3B& c):r(c.r), g(c.g), b(c.b){}
	inline operator ccColor3B() const { return *(ccColor3B*)this; }
    GLubyte r;
    GLubyte g;
    GLubyte b;
};

class ccColor4
{
public:
	ccColor4():r(255), g(255), b(255), a(255){}
	ccColor4(unsigned int value):
	a(value >> 24),
	r((value & 0x00FF0000) >> 16),
	g((value & 0x0000FF00) >> 8),
	b(value & 0x000000FF){}
	ccColor4(GLubyte r, GLubyte g, GLubyte b, GLubyte a) :r(r), g(g), b(b), a(a){}
	ccColor4(const ccColor3B& c, GLubyte a = 255) :r(c.r), g(c.g), b(c.b), a(a){}
	ccColor4(const ccColor4B& c) :r(c.r), g(c.g), b(c.b), a(c.a){}
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
	inline operator ccColor4B() const { return *(ccColor4B*)this; }
};

void __oEffect_update(lua_State* L, oEffect* effect, int tableIndex);
#define oEffect_update(effect, tableIndex) {__oEffect_update(tolua_S,effect,tableIndex);}

#endif // __DOROTHY_MODULE_H__
