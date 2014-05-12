extern "C"
{
	#include "tolua++.h"
	#include "tolua_fix.h"
}
#include <stack>
using std::stack;
#include <typeinfo>
#include "cocos2d.h"
using namespace cocos2d;
#include "Dorothy.h"
using namespace Dorothy;

static int g_ref_id = 0;
static stack<int> g_available_ref_ids;
extern "C" int toluafix_get_callback_ref_count()
{
	return g_ref_id - g_available_ref_ids.size();
}
extern "C" int alloc_ref_id()
{
	if (g_available_ref_ids.empty())
	{
		return ++g_ref_id;
	}
	else
	{
		int id = g_available_ref_ids.top();
		g_available_ref_ids.pop();
		return id;
	}
}

extern "C" void collect_ref_id(int refid)
{
	g_available_ref_ids.push(refid);
}

extern "C" int tolua_collect_ccobject(lua_State* L)
{
	CCObject* object = (CCObject*)tolua_tousertype(L, 1, 0);
	object->removeLuaRef();
	object->release();
	return 0;
}

extern "C" void tolua_pushccobject(lua_State* L, void* ptr, const char* type)
{
	if (!ptr)
	{
		lua_pushnil(L);
		return;
	}
	CCObject* object = (CCObject*)ptr;
	int refid = object->getLuaRef();

	luaL_getmetatable(L, type);// mt
	if (lua_isnil(L, -1))// no such type
	{
		lua_pop(L, 1);
		lua_pushnil(L);
		return;
	}
	lua_pushlightuserdata(L, TOLUA_UBOX);
	lua_rawget(L, LUA_REGISTRYINDEX);// mt ubox
	lua_rawgeti(L, -1, refid);// mt ubox ud

	if (lua_isnil(L, -1))// ud == nil
	{
		lua_pop(L, 1);// mt ubox
		*(void**)lua_newuserdata(L, sizeof(void *)) = ptr;// mt ubox newud
		lua_pushvalue(L, -1);// mt ubox newud newud
		lua_insert(L, -3);// mt newud ubox newud
		lua_rawseti(L, -2, refid);// ubox[refid] = newud, mt newud ubox
		lua_pop(L, 1);// mt newud
		lua_pushvalue(L, -2);// mt newud mt
		lua_setmetatable(L, -2);// newud<mt>, mt newud
#ifdef LUA_VERSION_NUM
		lua_pushvalue(L, TOLUA_NOPEER);
		lua_setfenv(L, -2);
#endif
		// register CCObject GC
		object->addLuaRef();
		object->retain();
	}
	else
	{
		/* check the need of updating the metatable to a more specialized class */
		lua_remove(L, -2);// mt ud
		lua_getmetatable(L, -1);// mt ud udmt
		lua_rawgeti(L, -1, MT_SUPER);// mt ud udmt tb
		lua_pushstring(L, type);// mt ud udmt tb type
		lua_rawget(L, -2);// tb[type], mt ud udmt tb flag
		if (lua_toboolean(L, -1))// flag == true
		{
			lua_pop(L, 3);// mt ud
			lua_remove(L, -2);// ud
			return;
		}
		lua_pop(L, 3);// mt ud
		// type represents a more specilized type
		lua_pushvalue(L, -2);// mt ud mt
		lua_setmetatable(L, -2);// ud<mt>, mt ud
	}
	lua_remove(L, -2);// ud
}

static unordered_map<unsigned int, const char*> g_typeinfo;
extern "C" void tolua_typeid(unsigned int hashCode, const char* className)
{
	g_typeinfo[hashCode] = className;
}
extern "C" const char* tolua_classname(void* ccobject)
{
	CCObject* object = (CCObject*)ccobject;
	return g_typeinfo[typeid(*object).hash_code()];
}
