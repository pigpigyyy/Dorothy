#include "DorothyModule.h"

void CCDrawNode_drawPolygon(
	CCDrawNode* self,
	unsigned int count, oVec2* verts,
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
ENUM_START(oSensorFlag)
{
	Enter = 0,
	Leave = 1
}
ENUM_END
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
bool oAnimationCache_unload(const char* filename)
{
	return filename ? oSharedAnimationCache.unload(filename) : oSharedAnimationCache.unload();
}

bool oClipCache_load(const char* filename)
{
	return oSharedClipCache.load(filename) != nullptr;
}
bool oClipCache_unload(const char* filename)
{
	return filename ? oSharedClipCache.unload(filename) : oSharedClipCache.unload();
}

bool oEffectCache_load(const char* filename)
{
	return oSharedEffectCache.load(filename);
}
bool oEffectCache_unload()
{
	return oSharedEffectCache.unload();
}

bool oParticleCache_load(const char* filename)
{
	return oSharedParticleCache.load(filename) != nullptr;
}
bool oParticleCache_unload(const char* filename)
{
	return filename ? oSharedParticleCache.unload(filename) : oSharedParticleCache.unload();
}

bool oModelCache_load(const char* filename)
{
	return oSharedModelCache.load(filename) != nullptr;
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
