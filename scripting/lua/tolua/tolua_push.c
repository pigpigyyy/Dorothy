/* tolua: functions to push C values.
** Support code for Lua bindings.
** Written by Waldemar Celes
** TeCGraf/PUC-Rio
** Apr 2003
** $Id: $
*/

/* This code is free software; you can redistribute it and/or modify it.
** The software provided hereunder is on an "as is" basis, and
** the author has no obligation to provide maintenance, support, updates,
** enhancements, or modifications.
*/

#include "tolua++.h"
#include "lauxlib.h"

#include <stdlib.h>

TOLUA_API void tolua_pushvalue (lua_State* L, int lo)
{
    lua_pushvalue(L,lo);
}

TOLUA_API void tolua_pushboolean (lua_State* L, int value)
{
    lua_pushboolean(L,value);
}

TOLUA_API void tolua_pushnumber (lua_State* L, lua_Number value)
{
    lua_pushnumber(L,value);
}

TOLUA_API void tolua_pushstring (lua_State* L, const char* value)
{
    if (value == NULL)
        lua_pushnil(L);
    else
        lua_pushstring(L,value);
}

TOLUA_API void tolua_pushuserdata (lua_State* L, void* value)
{
    if (value == NULL)
        lua_pushnil(L);
    else
        lua_pushlightuserdata(L,value);
}

TOLUA_API void tolua_pushusertype (lua_State* L, void* value, const char* type)
{
	if (value == NULL)
	{
		lua_pushnil(L);
	}
    else
    {
        luaL_getmetatable(L, type);// mt
        if (lua_isnil(L, -1))// mt == nil
		{
            lua_pop(L, 1);
			lua_pushnil(L);
            return;
		}
		lua_rawgeti(L, -1, MT_UBOX);// mt ubox
        if (lua_isnil(L, -1))// ubox == nil
		{
			lua_pop(L, 1);// mt
			lua_pushlightuserdata(L, TOLUA_UBOX);
            lua_rawget(L, LUA_REGISTRYINDEX);// mt ubox
        };

		lua_pushlightuserdata(L, value);// mt ubox key
		lua_rawget(L, -2);// ubox[key], mt ubox ud

        if (lua_isnil(L,-1))// ud == nil
        {
			lua_pop(L, 1);// mt ubox
			lua_pushlightuserdata(L, value);// mt ubox key
			*(void**)lua_newuserdata(L,sizeof(void *)) = value;// mt ubox key newud
			lua_pushvalue(L, -1);// mt ubox key newud newud
			lua_insert(L, -4);// mt newud ubox key newud
			lua_rawset(L, -3);// ubox[key] = newud, mt newud ubox
			lua_pop(L, 1);// mt newud
            lua_pushvalue(L, -2);// mt newud mt
            lua_setmetatable(L,-2);// newud<mt>, mt newud
#ifdef LUA_VERSION_NUM
            lua_pushvalue(L, TOLUA_NOPEER);
            lua_setfenv(L, -2);
#endif
        }
        else
        {
            /* check the need of updating the metatable to a more specialized class */
			lua_insert(L, -2);// mt ud ubox
			lua_pop(L, 1);// mt ud
			lua_getmetatable(L, -1);// mt ud udmt
			lua_rawgeti(L, -1, MT_SUPER);// mt ud udmt tb
			if (lua_istable(L, -1))
            {
				lua_pushstring(L, type);// mt ud udmt tb type
				lua_rawget(L, -2);// mt ud udmt tb flag
				if (lua_toboolean(L, -1) == 1)// flag == true
                {
					lua_pop(L, 3);// mt ud
                    lua_remove(L, -2);// ud
                    return;
                }
				else lua_pop(L, 1);// mt ud udmt tb
            }
            /* type represents a more specilized type */
            lua_pushvalue(L, -4);// mt ud udmt tb mt
			lua_setmetatable(L, -4);// ud<mt>, mt ud udmt tb
			lua_pop(L, 2);// mt ud
        }
        lua_remove(L, -2);// ud
    }
}

TOLUA_API void tolua_pushfieldvalue (lua_State* L, int lo, int index, int v)
{
    lua_pushnumber(L,index);
    lua_pushvalue(L,v);
    lua_settable(L,lo);
}

TOLUA_API void tolua_pushfieldboolean (lua_State* L, int lo, int index, int v)
{
    lua_pushnumber(L,index);
    lua_pushboolean(L,v);
    lua_settable(L,lo);
}


TOLUA_API void tolua_pushfieldnumber (lua_State* L, int lo, int index, lua_Number v)
{
    lua_pushnumber(L,index);
    tolua_pushnumber(L,v);
    lua_settable(L,lo);
}

TOLUA_API void tolua_pushfieldstring (lua_State* L, int lo, int index, const char* v)
{
    lua_pushnumber(L,index);
    tolua_pushstring(L,v);
    lua_settable(L,lo);
}

TOLUA_API void tolua_pushfielduserdata (lua_State* L, int lo, int index, void* v)
{
    lua_pushnumber(L,index);
    tolua_pushuserdata(L,v);
    lua_settable(L,lo);
}

TOLUA_API void tolua_pushfieldusertype (lua_State* L, int lo, int index, void* v, const char* type)
{
    lua_pushnumber(L,index);
    tolua_pushusertype(L,v,type);
    lua_settable(L,lo);
}
