#include "DorothyModule.h"
#include "CCLuaEngine.h"
#include "tolua++.h"

#define oSlotName(name) const char* oSlotList::name(#name);
//Node
oSlotName(Entering)
oSlotName(Entered)
oSlotName(Exiting)
oSlotName(Exited)
oSlotName(Cleanup)
//Touch
oSlotName(TouchBegan)
oSlotName(TouchCancelled)
oSlotName(TouchEnded)
oSlotName(TouchMoved)
//MenuItem
oSlotName(TapBegan)
oSlotName(TapEnded)
oSlotName(Tapped)
//Body
oSlotName(ContactEnd)
oSlotName(ContactStart)
//Sensor
oSlotName(BodyEnter)
oSlotName(BodyLeave)
//Keypad
oSlotName(KeyBack)
oSlotName(KeyMenu)
//Acceleration
oSlotName(Acceleration)
oSlotName(InputAttach)
oSlotName(InputDetach)
oSlotName(InputInserting)
oSlotName(InputInserted)
oSlotName(InputDeleting)
oSlotName(InputDeleted)
oSlotName(AnimationEnd)
oSlotName(ActionStart)
oSlotName(ActionEnd)
oSlotName(HitTarget)

class oSlotData : public CCObject
{
public:
	static const int MAX_SLOT_ARRAY;
	virtual ~oSlotData()
	{
		if (_gslotArray)
		{
			for (const auto& slot : *_gslotArray)
			{
				for (auto& item : *slot.second)
				{
					item->clearHandler();
				}
			}
		}
		else if (_gslot)
		{
			for (const auto& slot : *_gslot)
			{
				for (auto& item : *slot.second)
				{
					item->clearHandler();
				}
			}
		}
		if (_slotsArray)
		{
			for (const auto& item : *_slotsArray)
			{
				item.second->clear();
			}
		}
		else if (_slots)
		{
			for (const auto& item : *_slots)
			{
				item.second->clear();
			}
		}
	}
	oRefVector<oListener>* getGSlotItems(const char* name)
	{
		if (_gslotArray)
		{
			for (const auto& item : *_gslotArray)
			{
				if (item.first == name)
				{
					return item.second;
				}
			}
		}
		else if (_gslot)
		{
			auto it = _gslot->find(name);
			if (it != _gslot->end())
			{
				return it->second;
			}
		}
		return nullptr;
	}
	oListener* addGSlotItem(const char* name, int handler)
	{
		oListener* listener = oListener_create(name, handler);
		if (_gslot)
		{
			auto it = _gslot->find(name);
			if (it == _gslot->end())
			{
				auto vec = new oRefVector<oListener>();
				(*_gslot)[name] = oOwnMake(vec);
				vec->push_back(listener);
			}
			else it->second->push_back(listener);
			return listener;
		}
		else if (_gslotArray)
		{
			for (const auto& item : *_gslotArray)
			{
				if (item.first == name)
				{
					item.second->push_back(listener);
					return listener;
				}
			}
			if ((int)_gslotArray->size() < MAX_SLOT_ARRAY)
			{
				auto vec = new oRefVector<oListener>();
				_gslotArray->push_back(std::make_pair(string(name), oOwnMake(vec)));
				vec->push_back(listener);
				return listener;
			}
			else
			{
				_gslot = oOwnMake((new unordered_map<string,oOwn<oRefVector<oListener>>>()));
				for (auto& item : *_gslotArray)
				{
					(*_gslot)[item.first] = std::move(item.second);
				}
				_gslotArray.reset(nullptr);
				auto vec = new oRefVector<oListener>();
				(*_gslot)[name] = oOwnMake(vec);
				vec->push_back(listener);
				return listener;
			}
		}
		else
		{
			_gslotArray = oOwnMake((new vector<std::pair<string,oOwn<oRefVector<oListener>>>>()));
			auto vec = new oRefVector<oListener>();
			_gslotArray->push_back(std::make_pair(string(name), oOwnMake(vec)));
			vec->push_back(listener);
			return listener;
		}
	}
	void removeGSlotItems(const char* name)
	{
		if (_gslot)
		{
			auto it = _gslot->find(name);
			if (it != _gslot->end())
			{
				_gslot->erase(it);
			}
		}
		else if (_gslotArray)
		{
			for (auto it = _gslotArray->begin();it != _gslotArray->end();++it)
			{
				if (it->first == name)
				{
					_gslotArray->erase(it);
					break;
				}
			}
		}
	}
	void removeGSlotItem(oListener* listener)
	{
		oRefVector<oListener>* slotList = nullptr;
		if (_gslot)
		{
			auto it = _gslot->find(listener->getName());
			if (it != _gslot->end())
			{
				slotList = it->second;
			}
		}
		else if (_gslotArray)
		{
			for (auto it = _gslotArray->begin(); it != _gslotArray->end(); ++it)
			{
				if (it->first == listener->getName())
				{
					slotList = it->second;
					break;
				}
			}
		}
		if (slotList)
		{
			for (auto it = slotList->begin();it != slotList->end();++it)
			{
				if (*it == listener)
				{
					listener->clearHandler();
					slotList->erase(it);
					break;
				}
			}
		}
	}
	oSlotList* tryGetSlotList(const char* name)
	{
		if (_slots)
		{
			auto it = _slots->find(name);
			if (it != _slots->end()) return it->second;
		}
		else if (_slotsArray)
		{
			for (const auto& it : *_slotsArray)
			{
				if (it.first == name)
				{
					return it.second;
				}
			}
		}
		return nullptr;
	}
	oSlotList* getSlotList(const char* name)
	{
		if (_slots)
		{
			auto it = _slots->find(name);
			if (it == _slots->end())
			{
				oSlotList* slotList = oSlotList::create();
				(*_slots)[name] = slotList;
				return slotList;
			}
			else return it->second;
		}
		else if (_slotsArray)
		{
			for (const auto& it : *_slotsArray)
			{
				if (it.first == name)
				{
					return it.second;
				}
			}
			oSlotList* slotList = oSlotList::create();
			if ((int)_slotsArray->size() < MAX_SLOT_ARRAY)
			{
				_slotsArray->push_back(std::make_pair(string(name), oRefMake(slotList)));
			}
			else
			{
				_slots = oOwnMake((new unordered_map<string,oRef<oSlotList>>()));
				for (const auto& item : *_slotsArray)
				{
					(*_slots)[item.first] = item.second;
				}
				_slotsArray.reset(nullptr);
				(*_slots)[name] = slotList;
			}
			return slotList;
		}
		else
		{
			_slotsArray = oOwnMake((new vector<std::pair<string,oRef<oSlotList>>>()));
			oSlotList* slotList = oSlotList::create();
			_slotsArray->push_back(std::make_pair(string(name),oRefMake(slotList)));
			return slotList;
		}
	}
	void removeSlotList(const char* name)
	{
		if (_slotsArray)
		{
			for (auto it = _slotsArray->begin(); it != _slotsArray->end();++it)
			{
				if (it->first == name)
				{
					_slotsArray->erase(it);
				}
			}
		}
		else if (_slots)
		{
			auto it = _slots->find(name);
			if (it != _slots->end()) _slots->erase(it);
		}
	}
	CREATE_FUNC(oSlotData)
private:
	oOwn<unordered_map<string,oOwn<oRefVector<oListener>>>> _gslot;
	oOwn<vector<std::pair<string,oOwn<oRefVector<oListener>>>>> _gslotArray;
	oOwn<unordered_map<string,oRef<oSlotList>>> _slots;
	oOwn<vector<std::pair<string,oRef<oSlotList>>>> _slotsArray;
	CC_LUA_TYPE(oSlotData)
};
const int oSlotData::MAX_SLOT_ARRAY = 3;

oSlotList::oSlotList():_list()
{ }

oSlotList::~oSlotList()
{
	oSlotList::clear();
}

void oSlotList::add(int handler)
{
	_list.push_back(handler);
}

bool oSlotList::remove(int handler)
{
	for (auto it = _list.begin();it != _list.end();++it)
	{
		if (CCLuaEngine::sharedEngine()->scriptHandlerEqual(*it, handler))
		{
			CCLuaEngine::sharedEngine()->removeScriptHandler(*it);
			_list.erase(it);
			return true;
		}
	}
	return false;
}

void oSlotList::clear()
{
	for (int handler : _list)
	{
		CCLuaEngine::sharedEngine()->removeScriptHandler(handler);
	}
	_list.clear();
}

bool oSlotList::invoke(lua_State* L, int args)
{
	int top = lua_gettop(L);
	int result = 0;
	for (int i = 0;i < (int)_list.size();i++)
	{
		toluafix_get_function_by_refid(L, _list[i]);
		for (int index = top-args+1;index <= top;index++) lua_pushvalue(L, index);
		result = CCLuaEngine::execute(L, args);
	}
	return result != 0;
}

oSlotList* CCNode_getSlotList(CCNode* self, const char* name)
{
	CCAssert(self->getHelperObject() == 0 || CCLuaCast<oSlotData>(self->getHelperObject()), "Invalid slot object")
	oSlotData* slotData = (oSlotData*)self->getHelperObject();
	if (!slotData)
	{
		slotData = oSlotData::create();
		self->setHelperObject(slotData);
	}
	return slotData->getSlotList(name);
}

oSlotList* CCNode_tryGetSlotList(CCNode* self, const char* name)
{
	CCAssert(self->getHelperObject() == 0 || CCLuaCast<oSlotData>(self->getHelperObject()), "Invalid slot object")
	oSlotData* slotData = (oSlotData*)self->getHelperObject();
	if (slotData)
	{
		return slotData->tryGetSlotList(name);
	}
	return nullptr;
}

HANDLER_WRAP_START(oListenerHandlerWrapper)
void call(oEvent* event) const
{
	void* params[] = { event };
	int names[] = {CCLuaType<oEvent>()};
	CCLuaEngine::sharedEngine()->executeFunction(getHandler(), 1, params, names);
}
HANDLER_WRAP_END
oListener* oListener_create(const string& name, int handler)
{
	return oListener::create(name, std::make_pair(oListenerHandlerWrapper(handler), &oListenerHandlerWrapper::call));
}

int CCNode_gslot(lua_State* L)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(L, 1, "CCNode", 0, &tolua_err) ||
		!(tolua_isstring(L, 2, 0, &tolua_err) ||
			tolua_isusertype(L, 2, "oSlot", 0, &tolua_err)) ||
		!(toluafix_isfunction(L, 3, &tolua_err) ||
			lua_isnil(L, 3) ||
			tolua_isnoobj(L, 3, &tolua_err)) ||
		!tolua_isnoobj(L, 4, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		CCNode* self = (CCNode*)tolua_tousertype(L, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(L, "invalid 'self' in function 'CCNode_gslot'", NULL);
#endif
		CCAssert(self->getHelperObject() == 0 || CCLuaCast<oSlotData>(self->getHelperObject()), "Invalid slot object")
		oSlotData* slotData = (oSlotData*)self->getHelperObject();
		if (!slotData)
		{
			if (lua_isnil(L, 3) || tolua_isnoobj(L, 3, &tolua_err)) return 0;
			slotData = oSlotData::create();
			self->setHelperObject(slotData);
		}
		if (lua_isstring(L, 2))
		{
			const char* name = tolua_tostring(L, 2, 0);
			if (lua_isfunction(L, 3)) // set
			{
				int handler = toluafix_ref_function(L, 3);
				oListener* listener = slotData->addGSlotItem(name, handler);
				tolua_pushccobject(L, listener);
				return 1;
			}
			else if (tolua_isnoobj(L, 3, &tolua_err)) // get
			{
				oRefVector<oListener>* slotItems = slotData->getGSlotItems(name);
				if (slotItems)
				{
					lua_createtable(L, (int)slotItems->size(), 0);
					for (int i = 0; i < (int)slotItems->size(); i++)
					{
						tolua_pushccobject(L, (*slotItems)[i]);
						lua_rawseti(L, -2, i + 1);
					}
				}
				else lua_pushnil(L);
				return 1;
			}
			else if (lua_isnil(L, 3))// del
			{
				slotData->removeGSlotItems(name);
				return 0;
			}
		}
		else
		{
			oListener* listener = (oListener*)tolua_tousertype(L, 2, 0);
			slotData->removeGSlotItem(listener);
			return 0;
		}
	}
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(L, "#ferror in function 'gslot'.", &tolua_err);
	return 0;
#endif
}

int CCNode_slots(lua_State* L)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(L, 1, "CCNode", 0, &tolua_err) ||
		!tolua_isstring(L, 2, 0, &tolua_err) ||
		!(toluafix_isfunction(L, 3, &tolua_err) ||
			lua_isnil(L, 3) ||
			tolua_isnoobj(L, 3, &tolua_err)) ||
		!tolua_isnoobj(L, 4, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		CCNode* self = (CCNode*)tolua_tousertype(L, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(L, "invalid 'self' in function 'CCNode_slots'", NULL);
#endif
		const char* name = tolua_tostring(L, 2, 0);
		if (lua_isfunction(L, 3))
		{
			oSlotList* slotList = CCNode_getSlotList(self, name);
			int handler = toluafix_ref_function(L, 3);
			slotList->add(handler);
			return 0;
		}
		else if (lua_isnil(L, 3))
		{
			CCAssert(self->getHelperObject() == 0 || CCLuaCast<oSlotData>(self->getHelperObject()), "Invalid slot object")
			oSlotData* slotData = (oSlotData*)self->getHelperObject();
			if (slotData)
			{
				slotData->removeSlotList(name);
			}
			return 0;
		}
		else tolua_pushccobject(L, (void*)CCNode_getSlotList(self, name));
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(L, "#ferror in function 'slots'.", &tolua_err);
	return 0;
#endif
}

int CCNode_emit(lua_State* L)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(L, 1, "CCNode", 0, &tolua_err) ||
		!tolua_isstring(L, 2, 0, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		CCNode* self = (CCNode*)tolua_tousertype(L, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(L, "invalid 'self' in function 'CCNode_emit'", NULL);
#endif
		const char* name = tolua_tostring(L, 2, 0);
		oSlotList* list = CCNode_tryGetSlotList(self, name);
		if (list)
		{
			int top = lua_gettop(L);
			int args = top - 2;
			list->invoke(L, args);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(L, "#ferror in function 'emit'.", &tolua_err);
	return 0;
#endif
}

int CCNode_getChildren(lua_State* L)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(L, 1, "CCNode", 0, &tolua_err) ||
		!tolua_isnoobj(L, 2, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		CCNode* self = (CCNode*)tolua_tousertype(L, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(L, "invalid 'self' in function 'CCNode_getChildren'", NULL);
#endif
		CCArray* children = self->getChildren();
		if (children)
		{
			lua_createtable(L, children->count(), 0);
			for (unsigned int i = 0; i < children->count(); i++)
			{
				tolua_pushccobject(L, children->objectAtIndex(i));
				lua_rawseti(L, -2, i + 1);
			}
		}
		else lua_createtable(L, 0, 0);
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(L, "#ferror in function 'getChildren'.", &tolua_err);
	return 0;
#endif
}

int CCNode_traverse(lua_State* L)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(L, 1, "CCNode", 0, &tolua_err) ||
		!toluafix_isfunction(L, 2, &tolua_err) ||
		!tolua_isnoobj(L, 3, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		CCNode* self = (CCNode*)tolua_tousertype(L, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(L, "invalid 'self' in function 'CCNode_traverse'", NULL);
#endif
		self->traverse([L](CCNode* child)
		{
			int top = lua_gettop(L);
			lua_pushvalue(L, 2);
			tolua_pushccobject(L, child);
			CCLuaEngine::call(L, 1, 0);
			lua_settop(L, top);
		});
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(L, "#ferror in function 'traverse'.", &tolua_err);
	return 0;
#endif
}

int CCNode_eachChild(lua_State* L)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(L, 1, "CCNode", 0, &tolua_err) ||
		!toluafix_isfunction(L, 2, &tolua_err) ||
		!tolua_isnoobj(L, 3, &tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		CCNode* self = (CCNode*)tolua_tousertype(L, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(L, "invalid 'self' in function 'CCNode_eachChild'", NULL);
#endif
		CCArray* children = self->getChildren();
		CCObject* child;
		CCARRAY_FOREACH(children, child)
		{
			int top = lua_gettop(L);
			lua_pushvalue(L, 2);
			tolua_pushccobject(L, child);
			CCLuaEngine::call(L, 1, 0);
			lua_settop(L, top);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(L, "#ferror in function 'eachChild'.", &tolua_err);
	return 0;
#endif
}

CCNode* CCNode_getChildByIndex(CCNode* self, int index)
{
	index--;
	CCArray* children = self->getChildren();
	if (children && 0 <= index && index < (int)children->count())
	{
		return (CCNode*)children->objectAtIndex(index);
	}
	return nullptr;
}

void CCDrawNode_drawPolygon(
	CCDrawNode* self,
	oVec2* verts,
	int count,
	const ccColor4B& fillColor, float borderWidth,
	const ccColor4B& borderColor)
{
	self->drawPolygon((CCPoint*)verts, count, fillColor, borderWidth, borderColor);
}

void CCDrawNode_drawPolygon(
	CCDrawNode* self,
	oVec2* verts,
	int count,
	const ccColor4B& fillColor)
{
	self->drawPolygon((CCPoint*)verts, count, fillColor, 0, ccColor4B());
}

oModel* oModel_create(const char* filename)
{
	oModel* model = oModel::create(filename);
	model->handlers.each([](const char* name, oAnimationHandler& handler)
	{
		handler = [name](oModel* model)
		{
			oSlotList* slotList = CCNode_tryGetSlotList(model, oSlotList::AnimationEnd);
			if (slotList)
			{
				lua_State* L = CCLuaEngine::sharedEngine()->getState();
				lua_pushstring(L, name);
				tolua_pushccobject(L, model);
				slotList->invoke(L, 2);
				lua_pop(L, 2);
			}
		};
	});
	return model;
}

oVec2 oModel_getKey(oModel* model, const char* key)
{
	return model->getModelDef()->getKeyPoint(key);
}

inline void oHandleSensor(oSensor* sensor, oBody* other, const char* slotName)
{
	oSlotList* slotList = CCNode_tryGetSlotList(sensor->getOwner(), slotName);
	if (slotList)
	{
		lua_State* L = CCLuaEngine::sharedEngine()->getState();
		tolua_pushccobject(L, other);
		tolua_pushccobject(L, sensor);
		slotList->invoke(L, 2);
		lua_pop(L, 2);
	}
}

inline void oHandleContact(oBody* self, oBody* other, const oVec2& point, const oVec2& normal, const char* slotName)
{
	oSlotList* slotList = CCNode_tryGetSlotList(self, slotName);
	if (slotList)
	{
		lua_State* L = CCLuaEngine::sharedEngine()->getState();
		tolua_pushccobject(L, other);
		tolua_pushusertype(L, new oVec2(point), CCLuaType<oVec2>());
		tolua_pushusertype(L, new oVec2(normal), CCLuaType<oVec2>());
		slotList->invoke(L, 3);
		lua_pop(L, 3);
	}
}

oBody* oBody_create(oBodyDef* def, oWorld* world, oVec2 pos, float rot)
{
	oBody* body = oBody::create(def, world, pos, rot);
	auto sensorAddHandler = [](oSensor* sensor, oBody*)
	{
		sensor->bodyEnter = [](oSensor* sensor, oBody* other)
		{
			oHandleSensor(sensor, other, oSlotList::BodyEnter);
		};
		sensor->bodyLeave = [](oSensor* sensor, oBody* other)
		{
			oHandleSensor(sensor, other, oSlotList::BodyEnter);
		};
	};
	body->eachSensor(sensorAddHandler);
	body->sensorAdded = sensorAddHandler;
	body->contactStart = [body](oBody* other, const oVec2& point, const oVec2& normal)
	{
		oHandleContact(body, other, point, normal, oSlotList::ContactStart);
	};
	body->contactEnd = [body](oBody* other, const oVec2& point, const oVec2& normal)
	{
		oHandleContact(body, other, point, normal, oSlotList::ContactEnd);
	};
	return body;
}

inline void oHandleAction(oAction* action, const char* slotName)
{
	oSlotList* slotList = CCNode_tryGetSlotList(action->getOwner(), slotName);
	if (slotList)
	{
		lua_State* L = CCLuaEngine::sharedEngine()->getState();
		lua_pushlstring(L, action->getName().c_str(), action->getName().size());
		tolua_pushusertype(L, action, CCLuaType<oAction>());
		slotList->invoke(L, 2);
		lua_pop(L, 2);
	}
}

oUnit* oUnit_create(oUnitDef* unitDef, oWorld* world, const oVec2& pos, float rot)
{
	oUnit* unit = oUnit::create(unitDef, world, pos, rot);
	auto handleActionAdd = [](oAction* action)
	{
		action->actionStart = [](oAction* action)
		{
			oHandleAction(action, oSlotList::ActionStart);
		};
		action->actionEnd = [](oAction* action)
		{
			oHandleAction(action, oSlotList::ActionEnd);
		};
	};
	unit->eachAction(handleActionAdd);
	unit->actionAdded = handleActionAdd;
	return unit;
}

oBullet* oBullet_create(oBulletDef* def, oUnit* unit)
{
	oBullet* bullet = oBullet::create(def, unit);
	bullet->hitTarget = [](oBullet* bullet, oUnit* target)
	{
		oSlotList* slotList = CCNode_tryGetSlotList(bullet, oSlotList::HitTarget);
		if (slotList)
		{
			lua_State* L = CCLuaEngine::sharedEngine()->getState();
			tolua_pushccobject(L, target);
			tolua_pushccobject(L, bullet);
			bool ret = slotList->invoke(L, 2);
			lua_pop(L, 2);
			return ret;
		}
		return true;
	};
	return bullet;
}

void oWorld_query(oWorld* world, const CCRect& rect, int handler)
{
	lua_State* L = CCLuaEngine::sharedEngine()->getState();
	toluafix_get_function_by_refid(L, handler);
	int top = lua_gettop(L);
	world->query(rect, [&](oBody* body)
	{
		lua_pushvalue(L, top);
		tolua_pushccobject(L, body);
		CCLuaEngine::call(L, 1, 1);
		bool result = false;
		if (lua_isboolean(L, -1))
		{
			result = lua_toboolean(L, -1) != 0;
		}
		lua_settop(L, top);
		return result;
	});
	lua_pop(L, 1);
	CCLuaEngine::sharedEngine()->removeScriptHandler(handler);
}

void oWorld_cast(oWorld* world, const oVec2& start, const oVec2& end, bool closest, int handler)
{
	lua_State* L = CCLuaEngine::sharedEngine()->getState();
	toluafix_get_function_by_refid(L, handler);
	int top = lua_gettop(L);
	world->cast(start, end, closest,
		[&](oBody* body, const oVec2& point, const oVec2& normal)
	{
		lua_pushvalue(L, top);
		tolua_pushccobject(L, body);
		tolua_pushusertype(L, new oVec2(point), CCLuaType<oVec2>());
		tolua_pushusertype(L, new oVec2(normal), CCLuaType<oVec2>());
		CCLuaEngine::call(L, 3, 1);
		bool result = false;
		if (lua_isboolean(L, -1))
		{
			result = lua_toboolean(L, -1) != 0;
		}
		lua_settop(L, top);
		return result;
	});
	lua_pop(L, 1);
	CCLuaEngine::sharedEngine()->removeScriptHandler(handler);
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
void oAnimationCache_removeUnused()
{
	oSharedAnimationCache.removeUnused();
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
void oClipCache_removeUnused()
{
	oSharedClipCache.removeUnused();
}
void __oClipCache_getNames(lua_State* L, const char* filename)
{
	oClipDef* clipDef = oSharedClipCache.load(filename);
	lua_createtable(L, (int)clipDef->rects.size(), 0);
	int i = 1;
	for (const auto& item : clipDef->rects)
	{
		lua_pushstring(L,item.first.c_str());
		lua_rawseti(L, -2, i++);
	}
}
void __oClipCache_getTextureFile(lua_State* L, const char* filename)
{
	oClipDef* clipDef = oSharedClipCache.load(filename);
	lua_pushlstring(L, clipDef->textureFile.c_str(), clipDef->textureFile.size());
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
void oParticleCache_removeUnused()
{
	oSharedParticleCache.removeUnused();
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
void oModelCache_removeUnused()
{
	oSharedModelCache.removeUnused();
}

void oCache_removeUnused()
{
	oSharedModelCache.removeUnused();
	oSharedAnimationCache.removeUnused();
	oSharedParticleCache.removeUnused();
	oSharedClipCache.removeUnused();
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void oCache_clear()
{
	oSharedModelCache.unload();
	oSharedAnimationCache.unload();
	oSharedEffectCache.unload();
	oSharedParticleCache.unload();
	oSharedClipCache.unload();
	CCTextureCache::sharedTextureCache()->removeAllTextures();
	oSharedAudioEngine.unload();
}

int oCache_poolCollect()
{
	int collect = 0;
	collect += oVec2::poolCollect();
	collect += oKeyReset::poolCollect();
	collect += oKeyPos::poolCollect();
	collect += oKeyScale::poolCollect();
	collect += oKeyRotate::poolCollect();
	collect += oKeyOpacity::poolCollect();
	collect += oKeySkew::poolCollect();
	collect += oKeyRoll::poolCollect();
	collect += oSequence::poolCollect();
	collect += oSpawn::poolCollect();
	return collect;
}

int oCache_poolSize()
{
	int size = 0;
	size += oVec2::poolSize();
	size += oKeyReset::poolSize();
	size += oKeyPos::poolSize();
	size += oKeyScale::poolSize();
	size += oKeyRotate::poolSize();
	size += oKeyOpacity::poolSize();
	size += oKeySkew::poolSize();
	size += oKeyRoll::poolSize();
	size += oSequence::poolSize();
	size += oSpawn::poolSize();
	return size;
}

void oUnitDef_setActions(oUnitDef* def, char* actions[], int count)
{
	def->actions.clear();
	for (int i = 0; i < count; i++)
	{
		def->actions.push_back(actions[i]);
	}
}
void oUnitDef_setInstincts(oUnitDef* def, int instincts[], int count)
{
	def->instincts.clear();
	for (int i = 0; i < count; i++)
	{
		def->instincts.push_back(instincts[i]);
	}
}

void __oContent_getDirEntries(lua_State* L, oContent* self, const char* path, bool isFolder)
{
	auto dirs = self->getDirEntries(path, isFolder);
	lua_createtable(L, (int)dirs.size(), 0);
	for (int i = 0; i < (int)dirs.size(); i++)
	{
		lua_pushstring(L, dirs[i].c_str());
		lua_rawseti(L, -2, i+1);
	}
}

void oContent_copyFileAsync(oContent* self, const char* src, const char* dst, int handler)
{
	self->copyFileAsync(src, dst, [handler]()
	{
		CCLuaEngine::sharedEngine()->executeFunction(handler);
		CCLuaEngine::sharedEngine()->removeScriptHandler(handler);
	});
}
void oContent_setSearchPaths(oContent* self, char* paths[], int length)
{
	vector<string> searchPaths(length);
	for (int i = 0; i < length; i++)
	{
		searchPaths[i] = paths[i];
	}
	self->setSearchPaths(searchPaths);
}
void oContent_setSearchResolutionsOrder(oContent* self, char* paths[], int length)
{
	vector<string> searchOrders(length);
	for (int i = 0; i < length; i++)
	{
		searchOrders[i] = paths[i];
	}
	self->setSearchResolutionsOrder(searchOrders);
}

CCSprite* CCSprite_createWithClip(const char* clipStr)
{
	if (string(clipStr).find('|') != string::npos)
	{
		return oSharedClipCache.loadSprite(clipStr);
	}
	else if (oFileExt::check(clipStr,oFileExt::Clip))
	{
		oClipDef* def = oSharedClipCache.load(clipStr);
		return CCSprite::create(def->textureFile.c_str());
	}
	return CCSprite::create(clipStr);
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
CCScene* CCScene_createFlipAngular(float duration, CCScene* nextScene, bool rightOver)
{
	return CCTransitionFlipAngular::create(duration, nextScene, rightOver ? kCCTransitionOrientationRightOver : kCCTransitionOrientationLeftOver);
}
CCScene* CCScene_createFlip(float duration, CCScene* nextScene, tOrientation orientation)
{
	switch (orientation)
	{
	case kCCTransitionOrientationLeftOver:
		return CCTransitionFlipX::create(duration, nextScene, orientation);
	case kCCTransitionOrientationRightOver:
		return CCTransitionFlipX::create(duration, nextScene, orientation);
	case kCCTransitionOrientationUpOver:
		return CCTransitionFlipY::create(duration, nextScene, orientation);
	case kCCTransitionOrientationDownOver:
		return CCTransitionFlipY::create(duration, nextScene, orientation);
	}
	return nullptr;
}
CCScene* CCScene_createZoomFlip(float duration, CCScene* nextScene, tOrientation orientation)
{
	switch (orientation)
	{
	case kCCTransitionOrientationLeftOver:
		return CCTransitionZoomFlipX::create(duration, nextScene, orientation);
	case kCCTransitionOrientationRightOver:
		return CCTransitionZoomFlipX::create(duration, nextScene, orientation);
	case kCCTransitionOrientationUpOver:
		return CCTransitionZoomFlipY::create(duration, nextScene, orientation);
	case kCCTransitionOrientationDownOver:
		return CCTransitionZoomFlipY::create(duration, nextScene, orientation);
	}
	return nullptr;
}
CCScene* CCScene_createZoomFlipAngular(float duration, CCScene* nextScene, bool rightOver)
{
	return CCTransitionZoomFlipAngular::create(duration, nextScene, rightOver ? kCCTransitionOrientationRightOver : kCCTransitionOrientationLeftOver);
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
unsigned int CCArray_index(CCArray* array, CCObject* object)
{
	return array->indexOfObject(object) + 1;
}
CCObject* CArray_get(CCArray* array, unsigned int index)
{
	return array->objectAtIndex(index - 1);
}
void CArray_insert(CCArray* array, CCObject* object, unsigned int index)
{
	array->insertObject(object, index - 1);
}
void CArray_removeAt(CCArray* array, unsigned int index)
{
	array->removeObjectAtIndex(index - 1);
}
void CArray_exchange(CCArray* array, unsigned int index1, unsigned int index2)
{
	array->exchangeObjectAtIndex(index1 - 1, index2 - 1);
}
void CArray_fastRemoveAt(CCArray* array, unsigned int index)
{
	array->fastRemoveObjectAtIndex(index - 1);
}
void CArray_set(CCArray* array, unsigned int index, CCObject* object)
{
	array->replaceObjectAtIndex(index - 1, object);
}

CCTexture2D* CCTextureCache_add(CCTextureCache* self, CCRenderTexture* renderTexture, const char* name)
{
	CCImage* image = renderTexture->newCCImage();
	CCTexture2D* texture = self->addUIImage(image, name);
	delete image;
	return texture;
}

int CCDictionary_get(lua_State* L)
{
	/* 1 self, 2 key */
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "CCDictionary", 0, &tolua_err))
	{
		goto tolua_lerror;
	}
#endif
    {
	CCDictionary* self = (CCDictionary*)tolua_tousertype(L, 1, 0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(L, "invalid 'self' in function 'CCDictionary_get'", nullptr);
#endif
	CCObject* object = nullptr;
	if (lua_isnumber(L, 2))
	{
		int key = (int)lua_tonumber(L, 2);
		object = self->objectForKey(key);
	}
	else if (lua_isstring(L, 2))
	{
		const char* key = lua_tostring(L, 2);
		object = self->objectForKey(key);
	}
	if (object)
	{
		CCDouble* decimal64 = CCLuaCast<CCDouble>(object);
		if (decimal64)
		{
			lua_pushnumber(L, decimal64->getValue());
			return 1;
		}
		CCFloat* decimal32 = CCLuaCast<CCFloat>(object);
		if (decimal32)
		{
			lua_pushnumber(L, decimal32->getValue());
			return 1;
		}
		CCInteger* integer = CCLuaCast<CCInteger>(object);
		if (integer)
		{
			lua_pushnumber(L, integer->getValue());
			return 1;
		}
		CCBool* boolean = CCLuaCast<CCBool>(object);
		if (boolean)
		{
			lua_pushboolean(L, boolean->getValue() ? 1 : 0);
			return 1;
		}
		CCString* str = CCLuaCast<CCString>(object);
		if (str)
		{
			lua_pushstring(L, str->getCString());
			return 1;
		}
		tolua_pushccobject(L, object);
		return 1;
	}
	else
	{
		lua_pushnil(L);
		return 1;
	}
    }
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(L, "#ferror in function 'CCDictionary_get'.", &tolua_err);
	return 0;
#endif
}

int CCDictionary_set(lua_State* L)
{
	/* 1 self, 2 key, 3 value */
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "CCDictionary", 0, &tolua_err))
	{
		goto tolua_lerror;
	}
#endif
    {
	CCDictionary* self = (CCDictionary*)tolua_tousertype(L, 1, 0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(L, "invalid 'self' in function 'CCDictionary_set'", nullptr);
#endif
	CCObject* object = nullptr;
	if (!lua_isnil(L, 3))
	{
		if (lua_isnumber(L, 3))
		{
			object = CCDouble::create(lua_tonumber(L, 3));
		}
		else if (lua_isboolean(L, 3))
		{
			object = CCBool::create(lua_toboolean(L, 3) != 0);
		}
		else if (lua_isstring(L, 3))
		{
			object = CCString::create(lua_tostring(L, 3));
		}
		else if (tolua_isccobject(L, 3))
		{
			object = (CCObject*)tolua_tousertype(L, 3, 0);
		}
#ifndef TOLUA_RELEASE
		else
		{
			tolua_error(L, "CCDictionary can only store number, boolean, string and CCObject.", nullptr);
		}
#endif
	}
	if (lua_isnumber(L, 2))
	{
		int key = (int)lua_tonumber(L, 2);
		if (object) self->setObject(object, key);
		else self->removeObjectForKey(key);
	}
	else if (lua_isstring(L, 2))
	{
		const char* key = lua_tostring(L, 2);
		if (object) self->setObject(object, key);
		else self->removeObjectForKey(key);
	}
	return 0;
	}
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(L, "#ferror in function 'CCDictionary_set'.", &tolua_err);
	return 0;
#endif
}

int CCDictionary_getKeys(lua_State* L)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(L, 1, "CCDictionary", 0, &tolua_err) ||
		!tolua_isnoobj(L, 2, &tolua_err)
		)
	{
		goto tolua_lerror;
	}
#endif
	{
		CCDictionary* self = (CCDictionary*)tolua_tousertype(L, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(L, "invalid 'self' in function 'CCDictionary_getKeys'", nullptr);
#endif
		CCArray* keys = self->allKeys();
		lua_createtable(L, keys->count(), 0);
		int i = 1;
		CCARRAY_START(CCObject, key, keys)
		{
			if (key->getLuaType() == CCLuaType<CCString>())
			{
				lua_pushstring(L, ((CCString*)key)->getCString());
				lua_rawseti(L, -2, i++);
			}
			else if (key->getLuaType() == CCLuaType<CCInteger>())
			{
				lua_pushinteger(L, ((CCInteger*)key)->getValue());
				lua_rawseti(L, -2, i++);
			}
		}
		CCARRAY_END
	}
	return 1;
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(L, "#ferror in function 'getKeys'.", &tolua_err);
	return 0;
#endif
}

int CCDictionary_randomObject(lua_State* L)
{
	CCDictionary* self = (CCDictionary*)tolua_tousertype(L, 1, 0);
#ifndef TOLUA_RELEASE
	if (!self) tolua_error(L, "invalid 'self' in accessing variable 'randomObject'", nullptr);
#endif
	CCObject* object = self->randomObject();
	CCDouble* decimal64 = CCLuaCast<CCDouble>(object);
	if (decimal64)
	{
		lua_pushnumber(L, decimal64->getValue());
		return 1;
	}
	CCFloat* decimal32 = CCLuaCast<CCFloat>(object);
	if (decimal32)
	{
		lua_pushnumber(L, decimal32->getValue());
		return 1;
	}
	CCInteger* integer = CCLuaCast<CCInteger>(object);
	if (integer)
	{
		lua_pushnumber(L, integer->getValue());
		return 1;
	}
	CCBool* boolean = CCLuaCast<CCBool>(object);
	if (boolean)
	{
		lua_pushboolean(L, boolean->getValue() ? 1 : 0);
		return 1;
	}
	CCString* str = CCLuaCast<CCString>(object);
	if (str)
	{
		lua_pushstring(L, str->getCString());
		return 1;
	}
	tolua_pushccobject(L, object);
	return 1;
}

void __oModelCache_getData(lua_State* L, const char* filename)
{
	oModelDef* modelDef = oSharedModelCache.load(filename);
	if (!modelDef)
	{
		lua_pushnil(L);
		return;
	}
	auto lua_setFloat = [&](int index, float value)
	{
		lua_pushnumber(L, value);
		lua_rawseti(L, -2, index);
	};
	auto lua_setInt = [&](int index, int value)
	{
		lua_pushinteger(L, value);
		lua_rawseti(L, -2, index);
	};
	auto lua_setBool = [&](int index, bool value)
	{
		lua_pushboolean(L, value);
		lua_rawseti(L, -2, index);
	};
	auto lua_setString = [&](int index, const char* value)
	{
		lua_pushstring(L, value);
		lua_rawseti(L, -2, index);
	};
	auto lua_setUserType = [&](int index, void* value, int typeId)
	{
		tolua_pushusertype(L, value, typeId);
		lua_rawseti(L, -2, index);
	};
	function<void(oSpriteDef*)> visitSpriteDef = [&](oSpriteDef* parent)
	{
		lua_createtable(L, 16, 0);
		lua_setFloat(1, parent->anchorX);
		lua_setFloat(2, parent->anchorY);
		lua_setString(3, parent->clip.c_str());
		lua_setString(4, parent->name.c_str());
		lua_setFloat(5, parent->opacity);
		lua_setFloat(6, parent->rotation);
		lua_setFloat(7, parent->scaleX);
		lua_setFloat(8, parent->scaleY);
		lua_setFloat(9, parent->skewX);
		lua_setFloat(10, parent->skewY);
		lua_setFloat(11, parent->x);
		lua_setFloat(12, parent->y);
		/*["looks"]*/
		lua_createtable(L, (int)parent->looks.size(), 0);
		for (int i = 0; i <(int)parent->looks.size(); i++)
		{
			lua_pushinteger(L, parent->looks[i]);
			lua_rawseti(L, -2, i + 1);
		}
		lua_rawseti(L, -2, 13);
		/*["animationDefs"]*/
		lua_createtable(L, (int)parent->animationDefs.size(), 0);
		for (int defIndex = 0; defIndex <(int)parent->animationDefs.size(); defIndex++)
		{
			oModelAnimationDef* def = parent->animationDefs[defIndex];
			/* nullptr */
			if (!def)
			{
				lua_pushboolean(L, 0);
				lua_rawseti(L, -2, defIndex + 1);
				continue;
			}
			/* oKeyAnimationDef */
			oKeyAnimationDef* keyDef = dynamic_cast<oKeyAnimationDef*>(def);
			if (keyDef)
			{
				auto& frames = keyDef->getFrames();
				lua_createtable(L, (int)frames.size()+1, 0);
				lua_setInt(1, 1);
				for (int i = 0; i <(int)frames.size(); i++)
				{
					oKeyFrameDef* frame = frames[i];
					lua_createtable(L, 15, 0);
					lua_setFloat(1, frame->x);
					lua_setFloat(2, frame->y);
					lua_setFloat(3, frame->scaleX);
					lua_setFloat(4, frame->scaleY);
					lua_setFloat(5, frame->skewX);
					lua_setFloat(6, frame->skewY);
					lua_setFloat(7, frame->rotation);
					lua_setFloat(8, frame->opacity);
					lua_setBool(9, frame->visible);
					lua_setInt(10, frame->easeOpacity);
					lua_setInt(11, frame->easePos);
					lua_setInt(12, frame->easeRotation);
					lua_setInt(13, frame->easeScale);
					lua_setInt(14, frame->easeSkew);
					lua_setFloat(15, frame->duration);
					lua_rawseti(L, -2, i + 2);
				}
				lua_rawseti(L, -2, defIndex + 1);
				continue;
			}
			/* oFrameAnimationDef */
			oFrameAnimationDef* frameDef = dynamic_cast<oFrameAnimationDef*>(def);
			if (frameDef)
			{
				lua_createtable(L, 4, 0);
				lua_setInt(1, 2);
				lua_setString(2, frameDef->getFile().c_str());
				lua_setFloat(3, frameDef->delay);
				lua_rawseti(L, -2, defIndex + 1);
				continue;
			}
		}
		lua_rawseti(L, -2, 14);
		/*["children"]*/
		lua_createtable(L, (int)parent->children.size(), 0);
		for (int i = 0; i < (int)parent->children.size(); i++)
		{
			visitSpriteDef(parent->children[i]);
			lua_rawseti(L, -2, i + 1);
		}
		lua_rawseti(L, -2, 15);
		/*["front"]*/
		lua_setBool(16, parent->front);
	};

	oSpriteDef* root = modelDef->getRoot();
	if (root)
	{
		visitSpriteDef(root);
		lua_setBool(17, modelDef->isFaceRight());
		lua_setBool(18, modelDef->isBatchUsed());
		lua_setUserType(19, new CCSize(modelDef->getSize()), CCLuaType<CCSize>());
		lua_setString(20, modelDef->getClipFile().c_str());
		/*["keys"]*/
		lua_newtable(L);
		for (const auto& pair : modelDef->getKeyPoints())
		{
			lua_pushstring(L, pair.first.c_str());
			tolua_pushusertype(L, new oVec2(pair.second), CCLuaType<oVec2>());
			lua_rawset(L, -3);
		}
		lua_rawseti(L, -2, 21);
		/*["animationNames"]*/
		lua_newtable(L);
		for (const auto& pair : modelDef->getAnimationIndexMap())
		{
			lua_pushstring(L, pair.first.c_str());
			lua_pushinteger(L, pair.second);
			lua_rawset(L, -3);
		}
		lua_rawseti(L, -2, 22);
		/*["lookNames"]*/
		lua_newtable(L);
		for (const auto& pair : modelDef->getLookIndexMap())
		{
			lua_pushstring(L, pair.first.c_str());
			lua_pushinteger(L, pair.second);
			lua_rawset(L, -3);
		}
		lua_rawseti(L, -2, 23);
	}
	else lua_pushnil(L);
}

void oModelCache_save(const char* itemName, const char* targetName)
{
	oSharedContent.saveToFile(targetName, oSharedModelCache.load(itemName)->toXml());
}

oModelDef* __oModelCache_loadData(lua_State* L, const char* filename, int tableIndex)
{	
	auto lua_getFloat = [&](int index)->float
	{
		lua_rawgeti(L, -1, index);
		float v = (float)lua_tonumber(L, -1);
		lua_pop(L, 1);
		return v;
	};
	auto lua_getInt = [&](int index)->int
	{
		lua_rawgeti(L, -1, index);
		int v = (int)lua_tointeger(L, -1);
		lua_pop(L, 1);
		return v;
	};
	auto lua_getBool = [&](int index)->bool
	{
		lua_rawgeti(L, -1, index);
		bool v = (lua_toboolean(L, -1) != 0);
		lua_pop(L, 1);
		return v;
	};
	auto lua_getString = [&](int index)->const char*
	{
		lua_rawgeti(L, -1, index);
		const char* v = lua_tostring(L, -1);
		lua_pop(L, 1);
		return v;
	};
	auto lua_getUserType = [&](int index)->void*
	{
		lua_rawgeti(L, -1, index);
		void* v = (*(void**)(lua_touserdata(L, -1)));
		lua_pop(L, 1);
		return v;
	};
	lua_pushvalue(L, tableIndex);// push content

	bool isFaceRight = lua_getBool(17);
	bool isBatchUsed = lua_getBool(18);
	CCSize size = *(CCSize*)lua_getUserType(19);
	string clipFile = lua_getString(20);
	oClipDef* clipDef = oSharedClipCache.load(clipFile.c_str());
	CCTexture2D* texture = oSharedContent.loadTexture(clipDef->textureFile.c_str());
	/*["keys"]*/
	lua_rawgeti(L, -1, 21);// push keys
	unordered_map<string,oVec2> keys;
	int top = lua_gettop(L);
	for (lua_pushnil(L); lua_next(L, top) != 0; lua_pop(L, 1))
	{
		keys[lua_tostring(L, -2)] = *(oVec2*)(*(void**)(lua_touserdata(L, -1)));
	}
	lua_pop(L, 1);// pop keys
	/*["animationNames"]*/
	lua_rawgeti(L, -1, 22);// push animationNames
	unordered_map<string, int> animationNames;
	top = lua_gettop(L);
	for (lua_pushnil(L); lua_next(L, top) != 0; lua_pop(L, 1))
	{
		animationNames[lua_tostring(L, -2)] = (int)lua_tointeger(L, -1);
	}
	lua_pop(L, 1);// pop animationNames
	/*["lookNames"]*/
	lua_rawgeti(L, -1, 23);// push lookNames
	unordered_map<string, int> lookNames;
	top = lua_gettop(L);
	for (lua_pushnil(L); lua_next(L, top) != 0; lua_pop(L, 1))
	{
		lookNames[lua_tostring(L, -2)] = (int)lua_tointeger(L, -1);
	}
	lua_pop(L, 1);// pop lookNames
	/*oSpriteDef*/
	function<oSpriteDef*()> visitSpriteDef = [&]()->oSpriteDef*
	{
		oSpriteDef* spriteDef = new oSpriteDef();
		spriteDef->texture = texture;
		spriteDef->anchorX = lua_getFloat(1);
		spriteDef->anchorY = lua_getFloat(2);
		spriteDef->clip = lua_getString(3);
		spriteDef->rect = spriteDef->clip == "" ? CCRect::zero : *clipDef->rects[spriteDef->clip];
		spriteDef->name = lua_getString(4);
		spriteDef->opacity = lua_getFloat(5);
		spriteDef->rotation = lua_getFloat(6);
		spriteDef->scaleX = lua_getFloat(7);
		spriteDef->scaleY = lua_getFloat(8);
		spriteDef->skewX = lua_getFloat(9);
		spriteDef->skewY = lua_getFloat(10);
		spriteDef->x = lua_getFloat(11);
		spriteDef->y = lua_getFloat(12);
		/*["looks"]*/
		lua_rawgeti(L, -1, 13);// puah looks
		for (int i = 0, len = (int)lua_objlen(L, -1); i < len; i++)
		{
			lua_rawgeti(L, -1, i + 1);
			spriteDef->looks.push_back((int)lua_tointeger(L, -1));
			lua_pop(L, 1);
		}
		lua_pop(L, 1);// pop looks
		/*["animationDefs"]*/
		lua_rawgeti(L, -1, 14);// push animationDefs
		for (int defIndex = 0, len = (int)lua_objlen(L, -1); defIndex < len; defIndex++)
		{
			lua_rawgeti(L, -1, defIndex + 1);// push animationDef or boolean
			/* nullptr */
			if (lua_isboolean(L, -1))
			{
				spriteDef->animationDefs.push_back(nullptr);
				lua_pop(L, 1);// pop boolean
				continue;
			}
			int type = lua_getInt(1);
			/* oKeyAnimationDef */
			if (type == 1)
			{
				oKeyAnimationDef* keyAnimationDef = new oKeyAnimationDef();
				for (int i = 0, len = (int)lua_objlen(L, -1)-1; i < len; i++)
				{
					lua_rawgeti(L, -1, i + 2);// push frameDef
					oKeyFrameDef* frameDef = new oKeyFrameDef();
					frameDef->x = lua_getFloat(1);
					frameDef->y = lua_getFloat(2);
					frameDef->scaleX = lua_getFloat(3);
					frameDef->scaleY = lua_getFloat(4);
					frameDef->skewX = lua_getFloat(5);
					frameDef->skewY = lua_getFloat(6);
					frameDef->rotation = lua_getFloat(7);
					frameDef->opacity = lua_getFloat(8);
					frameDef->visible = lua_getBool(9);
					frameDef->easeOpacity = lua_getInt(10);
					frameDef->easePos = lua_getInt(11);
					frameDef->easeRotation = lua_getInt(12);
					frameDef->easeScale = lua_getInt(13);
					frameDef->easeSkew = lua_getInt(14);
					frameDef->duration = lua_getFloat(15);
					keyAnimationDef->add(frameDef);
					lua_pop(L, 1);// pop frameDef
				}
				spriteDef->animationDefs.push_back(keyAnimationDef);
			}
			/* oFrameAnimationDef */
			else if (type == 2)
			{
				oFrameAnimationDef* frameAnimationDef = new oFrameAnimationDef();
				frameAnimationDef->setFile(lua_getString(2));
				frameAnimationDef->delay = lua_getFloat(3);
				spriteDef->animationDefs.push_back(frameAnimationDef);
			}
			lua_pop(L, 1);// pop animationDef
		}
		lua_pop(L, 1);// pop animationDefs
		/* ["children"] */
		lua_rawgeti(L, -1, 15);// push children
		for (int i = 0, len = (int)lua_objlen(L, -1); i < len; i++)
		{
			lua_rawgeti(L, -1, i + 1);// push childDef
			spriteDef->children.push_back(visitSpriteDef());
			lua_pop(L, 1);// pop childDef
		}
		lua_pop(L, 1);// pop children
		/* ["front"] */
		spriteDef->front = lua_getBool(16);
		return spriteDef;
	};
	oSpriteDef* root = visitSpriteDef();
	oModelDef* modelDef = new oModelDef(isFaceRight, isBatchUsed, size, clipFile, texture, root, keys, animationNames, lookNames);
	modelDef->init();
	modelDef->autorelease();
	lua_pop(L, 1);// pop content
	return oSharedModelCache.update(filename, modelDef);
}

CCCall* CCCall::create(int nHandler)
{
	CCCall* pRet = new CCCall();
	CC_INIT(pRet);
	pRet->_scriptHandler = nHandler;
	pRet->autorelease();
	return pRet;
}
CCCall::~CCCall()
{
	if (_scriptHandler)
	{
		CCScriptEngine::sharedEngine()->removeScriptHandler(_scriptHandler);
	}
}
CCObject* CCCall::copyWithZone(CCZone* pZone)
{
	return nullptr;
}
void CCCall::update(float time)
{
	if (time > 0.0f)
	{
		this->execute();
	}
}
void CCCall::execute()
{
	if (_scriptHandler)
	{
		CCScriptEngine::sharedEngine()->executeFunction(_scriptHandler);
	}
}

class oTextFieldDelegate: public CCTextFieldDelegate
{
public:
	virtual bool onTextFieldAttachWithIME(CCTextFieldTTF* sender)
	{
		oSlotList* slotList = CCNode_tryGetSlotList(sender, oSlotList::InputAttach);
		if (slotList)
		{
			lua_State* L = CCLuaEngine::sharedEngine()->getState();
			tolua_pushccobject(L, sender);
			bool ret = slotList->invoke(L, 1);
			lua_pop(L, 1);
			return ret;
		}
		return true;
	}
	virtual bool onTextFieldDetachWithIME(CCTextFieldTTF* sender)
	{
		oSlotList* slotList = CCNode_tryGetSlotList(sender, oSlotList::InputDetach);
		if (slotList)
		{
			lua_State* L = CCLuaEngine::sharedEngine()->getState();
			tolua_pushccobject(L, sender);
			bool ret = slotList->invoke(L, 1);
			lua_pop(L, 1);
			return ret;
		}
		return true;
	}
	virtual bool onTextFieldInsertText(CCTextFieldTTF * sender, const char* text, int nLen)
	{
		oSlotList* slotList = CCNode_tryGetSlotList(sender, oSlotList::InputInserting);
		if (slotList)
		{
			lua_State* L = CCLuaEngine::sharedEngine()->getState();
			lua_pushlstring(L, text, nLen);
			tolua_pushccobject(L, sender);
			bool ret = !slotList->invoke(L, 2);
			lua_pop(L, 2);
			return ret;
		}
		return false;
	}
	virtual void onTextFieldInserted(CCTextFieldTTF* sender, const char* text)
	{
		oSlotList* slotList = CCNode_tryGetSlotList(sender, oSlotList::InputInserted);
		if (slotList)
		{
			lua_State* L = CCLuaEngine::sharedEngine()->getState();
			lua_pushstring(L, text);
			tolua_pushccobject(L, sender);
			slotList->invoke(L, 2);
			lua_pop(L, 2);
		}
	}
	virtual bool onTextFieldDeleteBackward(CCTextFieldTTF* sender, const char* delText, int nLen)
	{
		oSlotList* slotList = CCNode_tryGetSlotList(sender, oSlotList::InputDeleting);
		if (slotList)
		{
			lua_State* L = CCLuaEngine::sharedEngine()->getState();
			lua_pushlstring(L, delText, nLen);
			tolua_pushccobject(L, sender);
			bool ret = !slotList->invoke(L, 2);
			lua_pop(L, 2);
			return ret;
		}
		return false;
	}
	virtual void onTextFieldDeleted(CCTextFieldTTF* sender, const char* delText)
	{
		oSlotList* slotList = CCNode_tryGetSlotList(sender, oSlotList::InputDeleted);
		if (slotList)
		{
			lua_State* L = CCLuaEngine::sharedEngine()->getState();
			lua_pushstring(L, delText);
			tolua_pushccobject(L, sender);
			slotList->invoke(L, 2);
			lua_pop(L, 2);
		}
	}
};

CCTextFieldTTF* CCTextFieldTTF_create(const char* placeholder, const char* fontName, float fontSize)
{
	CCTextFieldTTF* textField = CCTextFieldTTF::textFieldWithPlaceHolder(placeholder, fontName, fontSize);
	oTextFieldDelegate* delegate = new oTextFieldDelegate();
	CC_INIT(delegate);
	delegate->autorelease();
	textField->setDelegate(delegate);
	return textField;
}

CCRenderTexture* CCRenderTexture_create(int w, int h, bool withDepthStencil)
{
	return CCRenderTexture::create(w, h, kCCTexture2DPixelFormat_RGBA8888, withDepthStencil ? GL_DEPTH24_STENCIL8 : 0);
}

class oImageAsyncLoader: public CCObject
{
public:
	void callback(CCObject* object)
	{
		if (_handler)
		{
			lua_State* L = CCLuaEngine::sharedEngine()->getState();
			lua_pushstring(L, _name.c_str());
			CCLuaEngine::sharedEngine()->executeFunction(_handler->get(), 1);
		}
	}
	static oImageAsyncLoader* create(const char* filename, int handler)
	{
		oImageAsyncLoader* loader = new oImageAsyncLoader();
		CC_INIT(loader);
		loader->_name = filename;
		if (handler)
		{
			loader->_handler = oScriptHandler::create(handler);
		}
		loader->autorelease();
		return loader;
	}
private:
	string _name;
	oRef<oScriptHandler> _handler;
};

int CCTextureCache_loadAsync(lua_State* L)
{
	/* 1 self, 2 filename, 3 function */
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(L, 1, "CCTextureCache", 0, &tolua_err) ||
		!tolua_isstring(L, 2, 0, &tolua_err) ||
		!(toluafix_isfunction(L, 3, &tolua_err) || tolua_isnoobj(L, 3, &tolua_err)) ||
		!tolua_isnoobj(L, 4, &tolua_err)
		)
	{
		goto tolua_lerror;
	}
#endif
    {
		CCTextureCache* self = (CCTextureCache*)tolua_tousertype(L, 1, 0);
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(L, "invalid 'self' in function 'CCTextureCache_loadAsync'", nullptr);
#endif
		const char* filename = ((const char*)tolua_tostring(L, 2, 0));
		int nHandler = lua_gettop(L) < 3 ? 0 : toluafix_ref_function(L, 3);
		oImageAsyncLoader* loader = oImageAsyncLoader::create(filename, nHandler);
		self->addImageAsync(filename, loader, callfuncO_selector(oImageAsyncLoader::callback));
		return 0;
    }
#ifndef TOLUA_RELEASE
tolua_lerror :
	tolua_error(L, "#ferror in function 'CCTextureCache_loadAsync'.", &tolua_err);
	return 0;
#endif
}

void __oEffect_update(lua_State* L, oEffect* self, int tableIndex)
{
	/* 1 oEffect 2 inst 3 table */
	oParticleEffect* effect = dynamic_cast<oParticleEffect*>(self);
	if (effect)
	{
		auto has = [L](const char* name)->bool
		{
			lua_getfield(L, -1, name);
			bool v = lua_isnil(L, -1) == 0;
			lua_pop(L, 1);
			return v;
		};
		auto getFloat = [L](const char* name)->float
		{
			lua_getfield(L, -1, name);
			float v = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
			return v;
		};
		auto getInt = [L](const char* name)->int
		{
			lua_getfield(L, -1, name);
			int v = (int)lua_tointeger(L, -1);
			lua_pop(L, 1);
			return v;
		};
		auto getBool = [L](const char* name)->bool
		{
			lua_getfield(L, -1, name);
			bool v = (lua_toboolean(L, -1) != 0);
			lua_pop(L, 1);
			return v;
		};
		auto getString = [L](const char* name)->const char*
		{
			lua_getfield(L, -1, name);
			const char* v = lua_tostring(L, -1);
			lua_pop(L, 1);
			return v;
		};
		CCParticleSystemQuad* particleSystem = effect->getParticle();
		lua_pushvalue(L, tableIndex);
		particleSystem->setTotalParticles(getInt("maxParticles"));
		particleSystem->setAngle(getFloat("angle"));
		particleSystem->setAngleVar(getFloat("angleVariance"));
		particleSystem->setBlendAdditive(getBool("blendAdditive"));
		particleSystem->setBlendFunc(ccBlendFunc{
			(GLenum)getInt("blendFuncSource"),
			(GLenum)getInt("blendFuncDestination") });
		particleSystem->setDuration(getFloat("duration"));
		particleSystem->setEmissionRate(getFloat("emissionRate"));
		particleSystem->setEndColor(ccc4f(
			getFloat("finishColorRed"),
			getFloat("finishColorGreen"),
			getFloat("finishColorBlue"),
			getFloat("finishColorAlpha")));
		particleSystem->setEndColorVar(ccc4f(
			getFloat("finishColorVarianceRed"),
			getFloat("finishColorVarianceGreen"),
			getFloat("finishColorVarianceBlue"),
			getFloat("finishColorVarianceAlpha")));
		particleSystem->setStartSpin(getFloat("rotationStart"));
		particleSystem->setStartSpin(getFloat("rotationStartVariance"));
		particleSystem->setStartSpin(getFloat("rotationEnd"));
		particleSystem->setStartSpin(getFloat("rotationEndVariance"));
		particleSystem->setEndSize(getFloat("finishParticleSize"));
		particleSystem->setEndSizeVar(getFloat("finishParticleSizeVariance"));
		particleSystem->setLife(getFloat("particleLifespan"));
		particleSystem->setLifeVar(getFloat("particleLifespanVariance"));
		particleSystem->setPosition(oVec2(
			getFloat("sourcePositionx"),
			getFloat("sourcePositiony")));
		particleSystem->setPosVar(oVec2(
			getFloat("sourcePositionVariancex"),
			getFloat("sourcePositionVariancey")));
		particleSystem->setStartColor(ccc4f(
			getFloat("startColorRed"),
			getFloat("startColorGreen"),
			getFloat("startColorBlue"),
			getFloat("startColorAlpha")));
		particleSystem->setStartColorVar(ccc4f(
			getFloat("startColorVarianceRed"),
			getFloat("startColorVarianceGreen"),
			getFloat("startColorVarianceBlue"),
			getFloat("startColorVarianceAlpha")));
		particleSystem->setStartSize(getFloat("startParticleSize"));
		particleSystem->setStartSizeVar(getFloat("startParticleSizeVariance"));
		particleSystem->setEmitterMode(getInt("emitterType"));
		if (particleSystem->getEmitterMode() == kCCParticleModeGravity)
		{
			particleSystem->setGravity(oVec2(
				getFloat("gravityx"),
				getFloat("gravityy")));
			particleSystem->setSpeed(getFloat("speed"));
			particleSystem->setSpeedVar(getFloat("speedVariance"));
			particleSystem->setRadialAccel(getFloat("radialAcceleration"));
			particleSystem->setRadialAccelVar(getFloat("radialAccelVariance"));
			particleSystem->setTangentialAccel(getFloat("tangentialAcceleration"));
			particleSystem->setTangentialAccelVar(getFloat("tangentialAccelVariance"));
			particleSystem->setRotationIsDir(getFloat("rotationIsDir") != 0);
		}
		else if (particleSystem->getEmitterMode() == kCCParticleModeRadius)
		{
			particleSystem->setStartRadius(getFloat("maxRadius"));
			particleSystem->setStartRadiusVar(getFloat("maxRadiusVariance"));
			particleSystem->setEndRadius(getFloat("minRadius"));
			particleSystem->setEndRadiusVar(getFloat("minRadiusVariance"));
			particleSystem->setRotatePerSecond(getFloat("rotatePerSecond"));
			particleSystem->setRotatePerSecondVar(getFloat("rotatePerSecondVariance"));
		}
		string textureName = getString("textureFileName");
		CCTexture2D* tex;
		if (textureName == "__firePngData")
		{
			tex = CCParticleSystem::getDefaultTexture();
		}
		else
		{
			tex = oSharedContent.loadTexture(textureName.c_str());
		}
		CCRect rect;
		if (has("textureRectx"))
		{
			rect = CCRect(getFloat("textureRectx"),
				getFloat("textureRecty"),
				getFloat("textureRectw"),
				getFloat("textureRecth"));
		}
		if (rect == CCRect::zero)
		{
			particleSystem->setTexture(tex);
		}
		else
		{
			particleSystem->setTextureWithRect(tex, rect);
		}
	}
}
