/* tolua: functions to push C values.
** Support code for Lua bindings.
** Written by Waldemar Celes, modified by Jin Li
** TeCGraf/PUC-Rio
** Apr 2003, Apr 2014
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

TOLUA_API void tolua_pushvalue(lua_State* L, int lo)
{
    lua_pushvalue(L,lo);
}

TOLUA_API void tolua_pushboolean(lua_State* L, int value)
{
    lua_pushboolean(L,value);
}

TOLUA_API void tolua_pushnumber(lua_State* L, lua_Number value)
{
    lua_pushnumber(L,value);
}

TOLUA_API void tolua_pushstring(lua_State* L, const char* value)
{
    if(value == NULL)
        lua_pushnil(L);
    else
        lua_pushstring(L,value);
}

TOLUA_API void tolua_pushuserdata(lua_State* L, void* value)
{
    if(value == NULL)
        lua_pushnil(L);
    else
        lua_pushlightuserdata(L,value);
}

TOLUA_API void tolua_pushusertype(lua_State* L, void* value, const char* type)
{
	if(value == NULL)
	{
		lua_pushnil(L);
		return;
	}
	luaL_getmetatable(L, type);// mt
	if(lua_isnil(L, -1))// mt == nil
	{
		lua_pop(L, 1);
		lua_pushnil(L);
		return;
	}
	*(void**)lua_newuserdata(L, sizeof(void *)) = value;// mt newud
	lua_insert(L, -2);// newud mt
	lua_setmetatable(L, -2);// newud<mt>, newud
	lua_pushvalue(L, TOLUA_NOPEER);
	lua_setfenv(L, -2);
}

TOLUA_API void tolua_pushfieldvalue(lua_State* L, int lo, int index, int v)
{
    lua_pushnumber(L,index);
    lua_pushvalue(L,v);
    lua_settable(L,lo);
}

TOLUA_API void tolua_pushfieldboolean(lua_State* L, int lo, int index, int v)
{
    lua_pushnumber(L,index);
    lua_pushboolean(L,v);
    lua_settable(L,lo);
}

TOLUA_API void tolua_pushfieldnumber(lua_State* L, int lo, int index, lua_Number v)
{
    lua_pushnumber(L,index);
    tolua_pushnumber(L,v);
    lua_settable(L,lo);
}

TOLUA_API void tolua_pushfieldstring(lua_State* L, int lo, int index, const char* v)
{
    lua_pushnumber(L,index);
    tolua_pushstring(L,v);
    lua_settable(L,lo);
}

TOLUA_API void tolua_pushfielduserdata(lua_State* L, int lo, int index, void* v)
{
    lua_pushnumber(L,index);
    tolua_pushuserdata(L,v);
    lua_settable(L,lo);
}

TOLUA_API void tolua_pushfieldusertype(lua_State* L, int lo, int index, void* v, const char* type)
{
    lua_pushnumber(L,index);
    tolua_pushusertype(L,v,type);
    lua_settable(L,lo);
}
