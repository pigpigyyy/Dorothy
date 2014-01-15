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

/*
Sensor flag:
	Enter = 0
	Leave = 1
*/
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

#endif // __DOROTHY_MODULE_H__
