extern "C"
{
	#include "tolua++.h"
	#include "tolua_fix.h"
}
#include <stack>
using std::stack;
#include "cocos2d.h"
using namespace cocos2d;

static int g_ref_id = 0;
static stack<int> g_available_ref_ids;

extern "C" int alloc_ref_id()
{
	if (g_available_ref_ids.empty())
	{
		g_ref_id++;
		return g_ref_id;
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

extern "C" int tolua_collect_ccobject(lua_State* tolua_S)
{
	CCObject* object = (CCObject*)tolua_tousertype(tolua_S, 1, 0);
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
	int refid = object->getObjectId();

	luaL_getmetatable(L, type);// mt
	if (lua_isnil(L, -1))// no such type
	{
		lua_pop(L, 1);
		lua_pushnil(L);
		return;
	}
	lua_pushstring(L, "tolua_ubox");
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
		object->retain();
	}
	else
	{
		/* check the need of updating the metatable to a more specialized class */
		lua_insert(L, -2);// mt ud ubox
		lua_pop(L, 1);// mt ud
		lua_pushstring(L, "tolua_super");
		lua_rawget(L, LUA_REGISTRYINDEX);// mt ud super
		lua_getmetatable(L, -2);// mt ud super mt
		lua_rawget(L, -2);// mt ud super super[mt]
		if (lua_istable(L, -1))
		{
			lua_pushstring(L, type);// mt ud super super[mt] type
			lua_rawget(L, -2);// mt ud super super[mt] flag
			if (lua_toboolean(L, -1) == 1)// flag == true
			{
				lua_pop(L, 3);// mt ud
				lua_remove(L, -2);// ud
				return;
			}
		}
		// type represents a more specilized type
		lua_pushvalue(L, -5);// mt ud super super[mt] flag mt
		lua_setmetatable(L, -5);// mt<mt>, mt ud super super[mt] flag
		lua_pop(L, 3);// mt ud
	}
	lua_remove(L, -2);// ud
}
