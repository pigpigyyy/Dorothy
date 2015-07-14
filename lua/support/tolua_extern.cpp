extern "C"
{
	#include "tolua++.h"
	#include "tolua_fix.h"
}
#include <stack>
using std::stack;
#include "cocos2d.h"
using namespace cocos2d;
#include "Dorothy.h"
using namespace Dorothy;
#include "CCLuaEngine.h"

static int g_ref_id = 0;
static stack<int> g_available_ref_ids;
extern "C" int toluafix_get_callback_ref_count()
{
	return g_ref_id - (unsigned int)g_available_ref_ids.size();
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

extern "C" void tolua_pushccobject(lua_State* L, void* ptr)
{
	if (!ptr)
	{
		lua_pushnil(L);
		return;
	}
	CCObject* object = (CCObject*)ptr;
	int refid = object->getLuaRef();

	lua_rawgeti(L, LUA_REGISTRYINDEX, TOLUA_UBOX);// ubox
	lua_rawgeti(L, -1, refid);// ubox ud

	if (lua_isnil(L, -1))// ud == nil
	{
		lua_pop(L, 1);// ubox
		*(void**)lua_newuserdata(L, sizeof(void*)) = ptr;// ubox newud
		lua_pushvalue(L, -1);// ubox newud newud
		lua_insert(L, -3);// newud ubox newud
		lua_rawseti(L, -2, refid);// ubox[refid] = newud, newud ubox
		lua_pop(L, 1);// newud
		lua_rawgeti(L, LUA_REGISTRYINDEX, object->getLuaType());// newud mt
		lua_setmetatable(L, -2);// newud<mt>, newud
		lua_pushvalue(L, TOLUA_NOPEER);
		lua_setfenv(L, -2);
		// register CCObject GC
		object->addLuaRef();
		object->retain();
	}
	else lua_remove(L, -2);// ud
}

extern "C" void tolua_typeid(lua_State* L, int typeId, const char* className)
{
	lua_getfield(L, LUA_REGISTRYINDEX, className);// mt 
	lua_rawseti(L, LUA_REGISTRYINDEX, typeId); // empty
}

extern "C" int tolua_isccobject(lua_State* L, int lo)
{
	if (lua_isuserdata(L, lo))
	{
		lua_getmetatable(L, lo);// mt
		lua_rawgeti(L, -1, MT_SUPER);// mt tb
		lua_rawgeti(L, LUA_REGISTRYINDEX, CCLuaType<CCObject>());// mt tb ccobjmt
		lua_rawget(L, LUA_REGISTRYINDEX);// mt tb "CCObject"
		lua_rawget(L, -2);// tb["CCObject"], mt tb flag
		int result = lua_toboolean(L, -1);
		lua_pop(L, 3);// empty
		return result;
	}
	return 0;
}

extern "C" void tolua_dobuffer(lua_State* L, char* codes, unsigned int size, const char* name)
{
		if (luaL_loadbuffer(L, codes, size, name) != 0)
		{
			luaL_error(L, "error loading module %s from %s :\n\t%s",
				lua_tostring(L, 1), name, lua_tostring(L, -1));
		}
		else CCLuaEngine::call(L, 0, 0);
}
