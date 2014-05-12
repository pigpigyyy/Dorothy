#include "tolua_fix.h"
#include <stdlib.h>

TOLUA_API int alloc_ref_id();
TOLUA_API void collect_ref_id(int refid);

TOLUA_API void toluafix_open(lua_State* L)
{
	lua_pushlightuserdata(L, TOLUA_CALLBACK);
    lua_newtable(L);
    lua_rawset(L, LUA_REGISTRYINDEX);
}

TOLUA_API int toluafix_ref_function(lua_State* L, int lo)
{
	/* function at lo */
	int refid;
    if (!lua_isfunction(L, lo)) return 0;
	refid = alloc_ref_id();
	lua_pushlightuserdata(L, TOLUA_CALLBACK);
    lua_rawget(L, LUA_REGISTRYINDEX);// funcMap
    lua_pushvalue(L, lo);// funcMap fun
    lua_rawseti(L, -2, refid);// funcMap[refid] = fun, funcMap
	lua_pop(L, 1);// empty
    return refid;
}

TOLUA_API void toluafix_get_function_by_refid(lua_State* L, int refid)
{
	lua_pushlightuserdata(L, TOLUA_CALLBACK);
	lua_rawget(L, LUA_REGISTRYINDEX);// funcMap
    lua_rawgeti(L, -1, refid);// funcMap fun
    lua_remove(L, -2);// fun
}

TOLUA_API void toluafix_remove_function_by_refid(lua_State* L, int refid)
{
	lua_pushlightuserdata(L, TOLUA_CALLBACK);
	lua_rawget(L, LUA_REGISTRYINDEX);// funcMap
	lua_pushnil(L);// funcMap nil
	lua_rawseti(L, -2, refid);// funcMap[refid] = nil, funcMap
	lua_pop(L, 1);// empty

	collect_ref_id(refid);
}

// check lua value is funciton
TOLUA_API int toluafix_isfunction(lua_State* L, int lo, tolua_Error* err)
{
    if (lua_gettop(L) >= abs(lo) && lua_isfunction(L, lo))
    {
        return 1;
    }
    err->index = lo;
    err->array = 0;
    err->type = "[not function]";
    return 0;
}

TOLUA_API void toluafix_stack_dump(lua_State* L, const char* label)
{
    int i;
    int top = lua_gettop(L);
    printf("Total [%d] in lua stack: %s\n", top, label != 0 ? label : "");
    for (i = -1; i >= -top; i--)
    {
        int t = lua_type(L, i);
        switch (t)
        {
            case LUA_TSTRING:
                printf("  [%02d] string %s\n", i, lua_tostring(L, i));
                break;
            case LUA_TBOOLEAN:
                printf("  [%02d] boolean %s\n", i, lua_toboolean(L, i) ? "true" : "false");
                break;
            case LUA_TNUMBER:
                printf("  [%02d] number %g\n", i, lua_tonumber(L, i));
                break;
            default:
                printf("  [%02d] %s\n", i, lua_typename(L, t));
        }
    }
    printf("\n");
}
