/* tolua: event functions
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

#include <stdio.h>

#include "tolua++.h"

/* Store at ubox
	* It stores, creating the corresponding table if needed,
	* the pair key/value in the corresponding ubox table
	*/
static void storeatubox(lua_State* L, int lo)
{
	/* ud at lo */
	lua_getfenv(L, lo); // key value env
	if (lua_rawequal(L, -1, TOLUA_NOPEER)) // env == nopeer
	{
		lua_pop(L, 1); // key value
		lua_newtable(L); // key value tb
		lua_pushvalue(L, -1); // key value tb tb
		lua_setfenv(L, lo); // ud<tb>, key value tb
	}
	lua_insert(L, -3); // tb key value
	lua_settable(L, -3); // tb[key] = value, tb
	lua_pop(L, 1); // empty
}

/* Module index function
*/
static int module_index_event(lua_State* L)
{
	const char* name = lua_tostring(L, 2);
	/* 1 tb, 2 key */
	lua_pushvalue(L, 2); // tb key key
	lua_rawget(L, -3); // tb[key], tb key item
	if (!lua_isnil(L, -1)) // item != nil
	{
		if (lua_istable(L, -1)) // item is table
		{
			lua_rawgeti(L, -1, 1); // tb key item getter
			if (lua_iscfunction(L, -1)) // getter is table
			{
				lua_pushvalue(L, 1); // tb key item getter tb
				lua_call(L, 1, 1); // getter(tb), tb key item result
				return 1;
			}
			else lua_pop(L, 1); // tb key item
		}
		return 1;
	}
	else lua_pop(L, 1); // tb key
	/* call old index meta event */
	if (lua_getmetatable(L, 1)) // tb key mt
	{
		lua_pushstring(L, "__index"); // tb key mt "__index"
		lua_rawget(L, -2); // mt["__index"], tb key mt indexItem
		if (lua_isfunction(L, -1)) // indexItem is function
		{
			lua_pushvalue(L, 1); // tb key mt indexItem tb
			lua_pushvalue(L, 2); // tb key mt indexItem tb key
			lua_call(L, 2, 1); // tb key mt indexItem result
			return 1;
		}
		else if (lua_istable(L, -1)) // indexItem is table
		{
			lua_pushvalue(L, 2); // tb key mt indexItem key
			lua_gettable(L, -2); // indexItem[key], tb key mt indexItem result
			return 1;
		}
	}
	lua_pushnil(L);
	return 1;
}

/* Module newindex function
*/
static int module_newindex_event(lua_State* L)
{
	/* 1 tb, 2 key, 3 value */
	lua_pushvalue(L, 2); // tb key value key
	lua_rawget(L, 1); // tb[key], tb key value item
	if (!lua_isnil(L, -1)) // item != nil
	{
		if (lua_istable(L, -1)) // item is table
		{
			lua_rawgeti(L, -1, 2); // tb key value item setter
			if (lua_iscfunction(L, -1)) // setter is cfunction
			{
				lua_pushvalue(L, 1); // tb key value item setter tb
				lua_pushvalue(L, 3); // tb key value item setter tb value
				lua_call(L, 2, 0); // tb key value item
				return 0;
			}
			else lua_pop(L, 1); // tb key value item
		}
		lua_pop(L, 1); // tb key value
		lua_rawset(L, 1); // tb[key] = value, tb
		return 0;
	}
	/* call old newindex meta event */
	if (lua_getmetatable(L, 1) && lua_getmetatable(L, -1)) // tb key value item mt
	{
		lua_pushstring(L, "__newindex");
		lua_rawget(L, -2); // tb key value item mt func
		if (lua_isfunction(L, -1)) // func is function
		{
			lua_pushvalue(L, 1);
			lua_pushvalue(L, 2);
			lua_pushvalue(L, 3);
			lua_call(L, 3, 0);
			return 0;
		}
	}
	lua_settop(L, 3); // tb key value
	lua_rawset(L, -3); // tb[key] = value, tb
	return 0;
}

/* Class index function
	* If the object is a userdata(ie, an object), it searches the field in
	* the alternative table stored in the corresponding "ubox" table.
	*/
static int class_index_event(lua_State* L)
{
	const char* key = lua_tostring(L, 2);
	// 1 ud, 2 key
	if (lua_isuserdata(L, 1)) // ud is userdata
	{
		lua_getfenv(L, 1); // ud key env
		if (!lua_rawequal(L, -1, TOLUA_NOPEER)) // env != nopeer
		{
			lua_pushvalue(L, 2); // ud key env key
			lua_gettable(L, -2); // env[key], ud key env item
			if (!lua_isnil(L, -1)) // item != nil
			{
				return 1;
			}
		}
		lua_settop(L, 2); // ud key
	}
	lua_getmetatable(L, 1); // ud key mt
	lua_pushvalue(L, 2); // ud key mt key
	lua_rawget(L, -2); // mt[key], ud key mt item
	if (lua_isnil(L, -1)) // item == nil
	{
		lua_pop(L, 1); // ud key mt
		int r = lua_getmetatable(L, -1); // ud key mt basemt
		while (r) // basemt exist
		{
			lua_pushvalue(L, 2); // ud key mt basemt key
			lua_rawget(L, -2); // basemt[key], ud key mt basemt item
			if (!lua_isnil(L, -1)) // item != nil
			{
				lua_remove(L, -2); // ud key mt item
				break;
			}
			else lua_pop(L, 1); // ud key mt basemt
			r = lua_getmetatable(L, -1); // ud key mt basemt basemt
			lua_remove(L, -2); // ud key mt basemt
		}
		/* ud key mt item */
		if (r) // item != nil
		{
			lua_pushvalue(L, 2); // ud key mt item key
			lua_pushvalue(L, -2); // ud key mt item key item
			lua_rawset(L, -4); // mt[key] = item, ud key mt item
		}
		else lua_pushnil(L);
		/* ud key mt item */
	}
	if (lua_istable(L, -1)) // item is table
	{
		lua_rawgeti(L, -1, 1); // item[1], ud key mt item getter
		if (lua_iscfunction(L, -1)) // getter is cfunction
		{
			lua_pushvalue(L, 1); // ud key mt item getter ud
			lua_call(L, 1, 1); // getter(ud), ud key mt item result
		}
		else lua_pop(L, 1); // ud key mt item
	}
	return 1;
}

/* Newindex function
	* It first searches for a C/C++ varaible to be set.
	* Then, it either stores it in the alternative ubox table(in the case it is
	* an object) or in the own table(that represents the class or module).
	*/
static int class_newindex_event(lua_State* L)
{
	const char* name = lua_tostring(L, 2);
	// 1 u, 2 k, 3 v
	int t = lua_type(L, 1);
	if (t == LUA_TUSERDATA)
	{
		lua_getfenv(L, 1); // u k v env
		if (!lua_rawequal(L, -1, TOLUA_NOPEER)) // env != nopeer
		{
			lua_pushvalue(L, 2); // u k v env k
			lua_pushvalue(L, 2); // u k v env k k
			lua_gettable(L, -3); // env[k], u k v env k item
			if (!lua_isnil(L, -1)) // item != nil
			{
				lua_pop(L, 1); // u k v env k
				lua_pushvalue(L, 3); // u k v env k v
				lua_settable(L, -3); // env[k] = v, u k v env
				return 0;
			}
		}
		lua_settop(L, 3); // u k v
	}
	else if (t == LUA_TTABLE)
	{
		lua_pushvalue(L, 2); // u k v k
		lua_rawget(L, 1); // u[k], u k v item
		if (!lua_isnil(L, -1))
		{
			lua_pop(L, 1); // u k v
			lua_rawset(L, 1); // u[k] = v, u
			return 0;
		}
	}
	lua_getmetatable(L, 1); // u k v mt
	lua_pushvalue(L, 2); // u k v mt k
	lua_rawget(L, -2); // mt[k], u k v mt item
	if (lua_isnil(L, -1)) // item == nil
	{
		lua_pop(L, 1); // u k v mt
		int r = lua_getmetatable(L, -1); // u k v mt basemt
		while (r) // basemt exist
		{
			lua_pushvalue(L, 2); // u k v mt basemt k
			lua_rawget(L, -2); // basemt[k], u k v mt basemt item
			if (!lua_isnil(L, -1)) // item != nil
			{
				lua_remove(L, -2); // u k v mt item
				break;
			}
			else lua_pop(L, 1); // u k v mt basemt
			r = lua_getmetatable(L, -1); // u k v mt basemt basemt
			lua_remove(L, -2); // u k v mt basemt
		}
		/* u k v mt item */
		if (r) // item != nil
		{
			lua_pushvalue(L, 2); // u k v mt item k
			lua_pushvalue(L, -2); // u k v mt item k item
			lua_rawset(L, -4); // mt[k] = item, u k v mt item
		}
		else lua_pushnil(L);
		/* u k v mt item */
	}
	if (lua_istable(L, -1)) // item is table
	{
		lua_rawgeti(L, -1, 2); // item[2], u k v mt item setter
		lua_pushvalue(L, 1); // u k v mt item setter u
		lua_pushvalue(L, 3); // u k v mt item setter u v
		lua_call(L, 2, 0); // ud key mt item
	}
	else
	{
		lua_pushvalue(L, 2); // u k v mt item k
		lua_pushvalue(L, 3); // u k v mt item k v
		if (t == LUA_TUSERDATA)
		{
			storeatubox(L, 1); // ubox[k] = v, u k v mt item
		}
		else if (t == LUA_TTABLE)
		{
			lua_rawset(L, 1); // u[k] = v, u k v mt item
		}
	}
	return 0;
}

static int class_call_event(lua_State* L)
{
	if (lua_istable(L, 1))
	{
		lua_rawgeti(L, 1, MT_CALL);
		if (lua_isfunction(L, -1))
		{
			lua_insert(L, 1);
			lua_call(L, lua_gettop(L) - 1, 1);
			return 1;
		};
	};
	tolua_error(L, "Attempt to call a non-callable object.", NULL);
	return 0;
}

static int do_operator(lua_State* L, int op)
{
	if (lua_isuserdata(L, 1))
	{
		/* Try metatables */
		lua_pushvalue(L, 1);                     /* stack: op1 op2 */
		while (lua_getmetatable(L, -1))
		{   /* stack: op1 op2 op1 mt */
			lua_remove(L, -2);                      /* stack: op1 op2 mt */
			lua_rawgeti(L, -1, op);                      /* stack: obj key mt func */
			if (lua_isfunction(L, -1))
			{
				lua_pushvalue(L, 1);
				lua_pushvalue(L, 2);
				lua_call(L, 2, 1);
				return 1;
			}
			lua_settop(L, 3);
		}
	}
	tolua_error(L, "Attempt to perform operation on an invalid operand", NULL);
	return 0;
}

static int class_add_event(lua_State* L)
{
	return do_operator(L, MT_ADD);
}

static int class_sub_event(lua_State* L)
{
	return do_operator(L, MT_SUB);
}

static int class_mul_event(lua_State* L)
{
	return do_operator(L, MT_MUL);
}

static int class_div_event(lua_State* L)
{
	return do_operator(L, MT_DIV);
}

static int class_lt_event(lua_State* L)
{
	return do_operator(L, MT_LT);
}

static int class_le_event(lua_State* L)
{
	return do_operator(L, MT_LE);
}

static int class_eq_event(lua_State* L)
{
	/* copying code from do_operator here to return false when no operator is found */
	if (lua_isuserdata(L, 1))
	{
		/* Try metatables */
		lua_pushvalue(L, 1);                     /* stack: op1 op2 */
		while (lua_getmetatable(L, -1))
		{   /* stack: op1 op2 op1 mt */
			lua_remove(L, -2);                      /* stack: op1 op2 mt */
			lua_rawgeti(L, -1, MT_EQ);                      /* stack: obj key mt func */
			if (lua_isfunction(L, -1))
			{
				lua_pushvalue(L, 1);
				lua_pushvalue(L, 2);
				lua_call(L, 2, 1);
				return 1;
			}
			lua_settop(L, 3);
		}
	}
	lua_settop(L, 3);
	lua_pushboolean(L, 0);
	return 1;
}

TOLUA_API int class_gc_event(lua_State* L)
{
	lua_getmetatable(L, 1);
	lua_rawgeti(L, -1, MT_DEL); // stack: mt collector
	if (lua_isfunction(L, -1))
	{
		lua_pushvalue(L, 1); // stack: mt collector u
		lua_call(L, 1, 0);
	}
#ifdef __SHOW_NO_GC_COLLECTOR_MSG__
	else
	{
		char* typeName;
		lua_pop(L, 1);
		lua_rawget(L, LUA_REGISTRYINDEX);  /* get registry[mt] */
		typeName = lua_tostring(L, -1);
		luaL_error(L, "No gc collector founded in %s", typeName);
	}
#endif
	lua_pop(L, 1);
	return 0;
}

/* Register module events
	* It expects the metatable on the top of the stack
	*/
TOLUA_API void tolua_moduleevents(lua_State* L)
{
	lua_pushstring(L, "__index");
	lua_pushcfunction(L, module_index_event);
	lua_rawset(L, -3);
	lua_pushstring(L, "__newindex");
	lua_pushcfunction(L, module_newindex_event);
	lua_rawset(L, -3);
}

/* Check if the object on the top has a module metatable
*/
TOLUA_API int tolua_ismodulemetatable(lua_State* L)
{
	int r = 0;
	if (lua_getmetatable(L, -1))
	{
		lua_pushstring(L, "__index");
		lua_rawget(L, -2);
		r = (lua_tocfunction(L, -1) == module_index_event);
		lua_pop(L, 2);
	}
	return r;
}

/* Register class events
	* It expects the metatable on the top of the stack
	*/
TOLUA_API void tolua_classevents(lua_State* L)
{
	lua_pushstring(L, "__index");
	lua_pushcfunction(L, class_index_event);
	lua_rawset(L, -3);

	lua_pushstring(L, "__newindex");
	lua_pushcfunction(L, class_newindex_event);
	lua_rawset(L, -3);

	lua_pushstring(L, "__add");
	lua_pushcfunction(L, class_add_event);
	lua_rawset(L, -3);

	lua_pushstring(L, "__sub");
	lua_pushcfunction(L, class_sub_event);
	lua_rawset(L, -3);

	lua_pushstring(L, "__mul");
	lua_pushcfunction(L, class_mul_event);
	lua_rawset(L, -3);

	lua_pushstring(L, "__div");
	lua_pushcfunction(L, class_div_event);
	lua_rawset(L, -3);

	lua_pushstring(L, "__lt");
	lua_pushcfunction(L, class_lt_event);
	lua_rawset(L, -3);

	lua_pushstring(L, "__le");
	lua_pushcfunction(L, class_le_event);
	lua_rawset(L, -3);

	lua_pushstring(L, "__eq");
	lua_pushcfunction(L, class_eq_event);
	lua_rawset(L, -3);

	lua_pushstring(L, "__call");
	lua_pushcfunction(L, class_call_event);
	lua_rawset(L, -3);

	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, class_gc_event);
	lua_rawset(L, -3);
}

