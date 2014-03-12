#include "DorothyModule.h"

void CCDrawNode_drawPolygon(
	CCDrawNode* self,
	oVec2* verts,
	int count,
	const ccColor4B& fillColor, float borderWidth,
	const ccColor4B& borderColor)
{
	self->drawPolygon((CCPoint*)verts, count, fillColor, borderWidth, borderColor);
}

HANDLER_WRAP_START(oModelHandlerWrapper)
	void call( oModel* model ) const
	{
		CCObject* params[] = {model};
		char* paramNames[] = {"oModel"};
		CCScriptEngine::sharedEngine()->executeFunction(getHandler(), 1, params, paramNames);
	}
HANDLER_WRAP_END
void oModel_addHandler( oModel* model, const string& name, int nHandler )
{
	model->handlers[name] += std::make_pair(oModelHandlerWrapper(nHandler), &oModelHandlerWrapper::call);
}
void oModel_removeHandler( oModel* model, const string& name, int nHandler )
{
	model->handlers[name] -= std::make_pair(oModelHandlerWrapper(nHandler), &oModelHandlerWrapper::call);
}
void oModel_clearHandler( oModel* model, const string& name )
{
	model->handlers[name].Clear();
}
const oVec2& oModel_getKey(oModel* model, uint32 index)
{
	return model->getModelDef()->getKeyPoint(index);
}

HANDLER_WRAP_START(oSensorHandlerWrapper)
	void call( oSensor* sensor, oBody* body ) const
	{
		CCObject* params[] = { sensor, body };
		char* paramNames[] = { "oSensor", "oBody" };
		CCScriptEngine::sharedEngine()->executeFunction(getHandler(), 2, params, paramNames);
	}
HANDLER_WRAP_END

void oSensor_addHandler( oSensor* sensor, uint32 flag, int nHandler )
{
	switch (flag)
	{
	case oSensorFlag::Enter:
		sensor->bodyEnter += std::make_pair(oSensorHandlerWrapper(nHandler), &oSensorHandlerWrapper::call);
		break;
	case oSensorFlag::Leave:
		sensor->bodyLeave += std::make_pair(oSensorHandlerWrapper(nHandler), &oSensorHandlerWrapper::call);
		break;
	}
}
void oSensor_removeHandler( oSensor* sensor, uint32 flag, int nHandler )
{
	switch (flag)
	{
	case oSensorFlag::Enter:
		sensor->bodyEnter -= std::make_pair(oSensorHandlerWrapper(nHandler), &oSensorHandlerWrapper::call);
		break;
	case oSensorFlag::Leave:
		sensor->bodyLeave -= std::make_pair(oSensorHandlerWrapper(nHandler), &oSensorHandlerWrapper::call);
		break;
	}
}
void oSensor_clearHandler( oSensor* sensor, uint32 flag )
{
	switch (flag)
	{
	case oSensorFlag::Enter:
		sensor->bodyEnter.Clear();
		break;
	case oSensorFlag::Leave:
		sensor->bodyLeave.Clear();
		break;
	}
}

void oWorld_query( oWorld* world, const CCRect& rect, int nHandler )
{
	world->query(rect,
		[&](oBody* body)
	{
		CCObject* params[] = {body};
		char* paramNames[] = {"oBody"};
		return CCScriptEngine::sharedEngine()->executeFunction(nHandler, 1, params, paramNames) != 0;
	});
}

bool oAnimationCache_load(const char* filename)
{
	return oSharedAnimationCache.load(filename) != nullptr;
}
bool oAnimationCache_update(const char* name, const char* content)
{
	return oSharedAnimationCache.update(name, content) != nullptr;
}
bool oAnimationCache_unload(const char* filename)
{
	return filename ? oSharedAnimationCache.unload(filename) : oSharedAnimationCache.unload();
}

bool oClipCache_load(const char* filename)
{
	return oSharedClipCache.load(filename) != nullptr;
}
bool oClipCache_update(const char* name, const char* content)
{
	return oSharedClipCache.update(name, content) != nullptr;
}
bool oClipCache_unload(const char* filename)
{
	return filename ? oSharedClipCache.unload(filename) : oSharedClipCache.unload();
}

bool oEffectCache_load(const char* filename)
{
	return oSharedEffectCache.load(filename);
}
bool oEffectCache_update(const char* content)
{
	return oSharedEffectCache.update(content);
}
bool oEffectCache_unload()
{
	return oSharedEffectCache.unload();
}

bool oParticleCache_load(const char* filename)
{
	return oSharedParticleCache.load(filename) != nullptr;
}
bool oParticleCache_update(const char* name, const char* content)
{
	return oSharedAnimationCache.update(name, content) != nullptr;
}
bool oParticleCache_unload(const char* filename)
{
	return filename ? oSharedParticleCache.unload(filename) : oSharedParticleCache.unload();
}

bool oModelCache_load(const char* filename)
{
	return oSharedModelCache.load(filename) != nullptr;
}
bool oModelCache_update(const char* name, const char* content)
{
	return oSharedAnimationCache.update(name, content) != nullptr;
}
bool oModelCache_unload(const char* filename)
{
	return filename ? oSharedModelCache.unload(filename) : oSharedModelCache.unload();
}

void oCache_clear()
{
	oSharedModelCache.unload();
	oSharedAnimationCache.unload();
	oSharedEffectCache.unload();
	oSharedParticleCache.unload();
	oSharedClipCache.unload();
}

void oUnitDef_setActions(oUnitDef* def, int actions[], int count)
{
	def->actions.clear();
	for (int i = 0; i < count; i++)
	{
		def->actions.push_back(i);
	}
}
void oUnitDef_setInstincts(oUnitDef* def, int instincts[], int count)
{
	def->instincts.clear();
	for (int i = 0; i < count; i++)
	{
		def->instincts.push_back(i);
	}
}

HANDLER_WRAP_START(oListenerHandlerWrapper)
	void call(oEvent* event) const
	{
		void* params[] = {event};
		char* names[] = {"oEvent"};
		CCScriptEngine::sharedEngine()->executeFunction(getHandler(), 1, params, names);
	}
HANDLER_WRAP_END
oListener* oListener_create(const string& name, int handler)
{
	return oListener::create(name, std::make_pair(oListenerHandlerWrapper(handler), &oListenerHandlerWrapper::call));
}

CCSprite* CCSprite_createWithClip(const char* clipStr)
{
	if (string(clipStr).find('|') == string::npos)
	{
		return CCSprite::create(clipStr);
	}
	else
	{
		return oSharedClipCache.loadSprite(clipStr);
	}
}

CCScene* CCScene_createOriented(float duration, CCScene* nextScene, tOrientation orientation)
{
	return CCTransitionSceneOriented::create(duration, nextScene, orientation);
}
CCScene* CCScene_createRotoZoom(float duration, CCScene* nextScene)
{
	return CCTransitionRotoZoom::create(duration, nextScene);
}
CCScene* CCScene_createJumpZoom(float duration, CCScene* nextScene)
{
	return CCTransitionJumpZoom::create(duration, nextScene);
}
CCScene* CCScene_createMove(float duration, CCScene* nextScene, tOrientation orientation)
{
	switch (orientation)
	{
	case kCCTransitionOrientationLeftOver:
		return CCTransitionMoveInL::create(duration, nextScene);
	case kCCTransitionOrientationRightOver:
		return CCTransitionMoveInR::create(duration, nextScene);
	case kCCTransitionOrientationUpOver:
		return CCTransitionMoveInT::create(duration, nextScene);
	case kCCTransitionOrientationDownOver:
		return CCTransitionMoveInB::create(duration, nextScene);
	}
	return nullptr;
}
CCScene* CCScene_createSlide(float duration, CCScene* nextScene, tOrientation orientation)
{
	switch (orientation)
	{
	case kCCTransitionOrientationLeftOver:
		return CCTransitionSlideInL::create(duration, nextScene);
	case kCCTransitionOrientationRightOver:
		return CCTransitionSlideInR::create(duration, nextScene);
	case kCCTransitionOrientationUpOver:
		return CCTransitionSlideInT::create(duration, nextScene);
	case kCCTransitionOrientationDownOver:
		return CCTransitionSlideInB::create(duration, nextScene);
	}
	return nullptr;
}
CCScene* CCScene_createShrinkGrow(float duration, CCScene* nextScene)
{
	return CCTransitionShrinkGrow::create(duration, nextScene);
}
CCScene* CCScene_createFlipX(float duration, CCScene* nextScene, tOrientation orientation)
{
	return CCTransitionFlipX::create(duration, nextScene);
}
CCScene* CCScene_createFlipY(float duration, CCScene* nextScene, tOrientation orientation)
{
	return CCTransitionFlipY::create(duration, nextScene);
}
CCScene* CCScene_createFlipAngular(float duration, CCScene* nextScene, tOrientation orientation)
{
	return CCTransitionFlipAngular::create(duration, nextScene);
}
CCScene* CCScene_createZoomFlipX(float duration, CCScene* nextScene, tOrientation orientation)
{
	return CCTransitionZoomFlipX::create(duration, nextScene, orientation);
}
CCScene* CCScene_createZoomFlipY(float duration, CCScene* nextScene, tOrientation orientation)
{
	return CCTransitionZoomFlipY::create(duration, nextScene, orientation);
}
CCScene* CCScene_createZoomFlipAngular(float duration, CCScene* nextScene, tOrientation orientation)
{
	return CCTransitionZoomFlipAngular::create(duration, nextScene, orientation);
}
CCScene* CCScene_createFade(float duration, CCScene* nextScene, const ccColor3B& color)
{
	return CCTransitionFade::create(duration, nextScene, color);
}
CCScene* CCScene_createCrossFade(float duration, CCScene* nextScene)
{
	return CCTransitionCrossFade::create(duration, nextScene);
}
CCScene* CCScene_createTurnOffTiles(float duration, CCScene* nextScene)
{
	return CCTransitionTurnOffTiles::create(duration, nextScene);
}
CCScene* CCScene_createSplitCols(float duration, CCScene* nextScene)
{
	return CCTransitionSplitCols::create(duration, nextScene);
}
CCScene* CCScene_createSplitRows(float duration, CCScene* nextScene)
{
	return CCTransitionSplitRows::create(duration, nextScene);
}
CCScene* CCScene_createFadeTiles(float duration, CCScene* nextScene, tOrientation orientation)
{
	switch (orientation)
	{
	case kCCTransitionOrientationLeftOver:
		return CCTransitionFadeBL::create(duration, nextScene);
	case kCCTransitionOrientationRightOver:
		return CCTransitionFadeTR::create(duration, nextScene);
	case kCCTransitionOrientationUpOver:
		return CCTransitionFadeUp::create(duration, nextScene);
	case kCCTransitionOrientationDownOver:
		return CCTransitionFadeDown::create(duration, nextScene);
	}
	return nullptr;
}
CCScene* CCScene_createPageTurn(float duration, CCScene* nextScene, bool backward)
{
	return CCTransitionPageTurn::create(duration, nextScene, backward);
}
CCScene* CCScene_createProgressCCW(float duration, CCScene* nextScene)
{
	return CCTransitionProgressRadialCCW::create(duration, nextScene);
}
CCScene* CCScene_createProgressCW(float duration, CCScene* nextScene)
{
	return CCTransitionProgressRadialCW::create(duration, nextScene);
}
CCScene* CCScene_createProgressH(float duration, CCScene* nextScene)
{
	return CCTransitionProgressHorizontal::create(duration, nextScene);
}
CCScene* CCScene_createProgressV(float duration, CCScene* nextScene)
{
	return CCTransitionProgressVertical::create(duration, nextScene);
}
CCScene* CCScene_createProgressIO(float duration, CCScene* nextScene)
{
	return CCTransitionProgressInOut::create(duration, nextScene);
}
CCScene* CCScene_createProgressOI(float duration, CCScene* nextScene)
{
	return CCTransitionProgressOutIn::create(duration, nextScene);
}

CCCardinalSplineTo* CCCardinalSplineTo_create(float duration, const oVec2 points[], int count, float tension)
{
	CCPointArray* array = CCPointArray::create(count);
	for (int i = 0; i < count; i++)
	{
		array->addControlPoint(points[i]);
	}
	return CCCardinalSplineTo::create(duration, array, tension);
}
CCCardinalSplineBy* CCCardinalSplineBy_create(float duration, const oVec2 points[], int count, float tension)
{
	CCPointArray* array = CCPointArray::create(count);
	for (int i = 0; i < count; i++)
	{
		array->addControlPoint(points[i]);
	}
	return CCCardinalSplineBy::create(duration, array, tension);
}
CCCatmullRomTo* CCCatmullRomTo_create(float duration, const oVec2 points[], int count)
{
	CCPointArray* array = CCPointArray::create(count);
	for (int i = 0; i < count; i++)
	{
		array->addControlPoint(points[i]);
	}
	return CCCatmullRomTo::create(duration, array);
}
CCCatmullRomBy* CCCatmullRomBy_create(float duration, const oVec2 points[], int count)
{
	CCPointArray* array = CCPointArray::create(count);
	for (int i = 0; i < count; i++)
	{
		array->addControlPoint(points[i]);
	}
	return CCCatmullRomBy::create(duration, array);
}

CCActionInterval* CCTile_createFadeOut(float duration, CCSize gridSize, tOrientation orientation)
{
	switch (orientation)
	{
	case kCCTransitionOrientationLeftOver:
		return CCFadeOutBLTiles::create(duration, gridSize);
	case kCCTransitionOrientationRightOver:
		return CCFadeOutTRTiles::create(duration, gridSize);
	case kCCTransitionOrientationUpOver:
		return CCFadeOutUpTiles::create(duration, gridSize);
	case kCCTransitionOrientationDownOver:
		return CCFadeOutDownTiles::create(duration, gridSize);
	}
	return nullptr;
}

CCArray* CCArray_create(CCObject* object[], int count)
{
	CCArray* array = CCArray::createWithCapacity(count);
	for (int i = 0; i < count; i++)
	{
		array->addObject(object[i]);
	}
	return array;
}

