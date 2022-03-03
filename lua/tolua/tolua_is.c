/* tolua: functions to check types.
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
#include <string.h>

/* a fast check if a is b, without parameter validation
 i.e. if b is equal to a or a superclass of a. */
TOLUA_API int tolua_fast_isa(lua_State *L, int mt_indexa, int mt_indexb)
{
	int result = 1;
	if (!lua_rawequal(L, mt_indexa, mt_indexb))
	{
		lua_rawgeti(L, mt_indexa, MT_SUPER);// super
		lua_pushvalue(L, mt_indexb);// super mtb
		lua_rawget(L, LUA_REGISTRYINDEX);// super typeb
		lua_rawget(L, -2);// super[typeb], super flag
		result = lua_toboolean(L, -1);
		lua_pop(L, 2);
	}
	return result;
}

/* Push and returns the corresponding object typename */
TOLUA_API const char* tolua_typename(lua_State* L, int lo)
{
	int tag = lua_type(L, lo);
	if (tag == LUA_TNONE)
	{
		lua_pushstring(L, "[no object]");
	}
	else if (tag != LUA_TUSERDATA && tag != LUA_TTABLE)
	{
		lua_pushstring(L, lua_typename(L, tag));
	}
	else if (tag == LUA_TUSERDATA)
	{
		if (!lua_getmetatable(L, lo))// mt
		{
			lua_pop(L, 1);// empty
			lua_pushstring(L, lua_typename(L, tag));// result
		}
		else
		{
			lua_rawget(L, LUA_REGISTRYINDEX);// reg[mt], name
			if (!lua_isstring(L, -1))
			{
				lua_pop(L, 1);// empty
				lua_pushstring(L, "[undefined]");// result
			}
		}
	}
	else// is table
	{
		lua_pushvalue(L, lo);// tb
		lua_rawget(L, LUA_REGISTRYINDEX);//reg[tb], name
		if (!lua_isstring(L, -1))// name is string
		{
			lua_pop(L, 1);// empty
			lua_pushstring(L, "table");// result
		}
		else
		{
			lua_pushstring(L, "class ");// name "class "
			lua_insert(L, -2);// "class " name
			lua_concat(L, 2);// "class "..name
		}
	}
	return lua_tostring(L, -1);
}

TOLUA_API void tolua_error(lua_State* L, const char* msg, tolua_Error* err)
{
	if (msg[0] == '#')
	{
		const char* expected = err->type;
		const char* provided = tolua_typename(L, err->index);
		if (msg[1] == 'f')
		{
			int narg = err->index;
			if (err->array)
			{
				luaL_error(L, "%s\nargument #%d is array of '%s', array of '%s' expected",
				msg + 2, narg, provided, expected);
			}
			else
			{
				luaL_error(L, "%s\nargument #%d is '%s', '%s' expected",
				msg + 2, narg, provided, expected);
			}
		}
		else if (msg[1] == 'v')
		{
			if (err->array)
			{
				luaL_error(L, "%s\nvalue is array of '%s', array of '%s' expected",
				msg + 2, provided, expected);
			}
			else
			{
				luaL_error(L, "%s\nvalue is '%s', '%s' expected",
				msg + 2, provided, expected);
			}
		}
	}
	else luaL_error(L, msg);
}

/* the equivalent of lua_is* for usertable */
static int lua_isusertable(lua_State* L, int lo, const char* type)
{
	int r = 0;
	if (lo < 0) lo = lua_gettop(L) + lo + 1;
	lua_pushvalue(L, lo);
	lua_rawget(L, LUA_REGISTRYINDEX);  /* get registry[t] */
	if (lua_isstring(L, -1))
	{
		r = strcmp(lua_tostring(L, -1), type) == 0;
	}
	lua_pop(L, 1);
	return r;
}

/* the equivalent of lua_is* for usertype */
TOLUA_API int tolua_istype(lua_State* L, int lo, const char* type)
{
	if (!lua_isuserdata(L, lo)) return 0;
	/* check if it is of the same type */
	int r;
	const char* tn;
	if (lua_getmetatable(L, lo))/* if metatable? */
	{
		lua_rawget(L, LUA_REGISTRYINDEX);/* get registry[mt] */
		tn = lua_tostring(L, -1);
		r = tn && (strcmp(tn, type) == 0);
		lua_pop(L, 1);
		if (r) return 1;
		else
		{
			/* check if it is a specialized class */
			lua_getmetatable(L, lo);// mt
			lua_rawgeti(L, -1, MT_SUPER);// mt tb
			if (lua_istable(L, -1))
			{
				int b;
				lua_pushstring(L, type);// mt tb type
				lua_rawget(L, -2);// tb[type], mt tb flag
				b = lua_toboolean(L, -1);
				lua_pop(L, 3);
				if (b) return 1;
			}
		}
	}
	return 0;
}

TOLUA_API int tolua_isnoobj(lua_State* L, int lo, tolua_Error* err)
{
	if (lua_gettop(L) < abs(lo)) return 1;
	err->index = lo;
	err->array = 0;
	err->type = "[no object]";
	return 0;
}

TOLUA_API int tolua_isboolean(lua_State* L, int lo, int def, tolua_Error* err)
{
	if (def && lua_gettop(L) < abs(lo)) return 1;
	if (lua_isnil(L, lo) || lua_isboolean(L, lo)) return 1;
	err->index = lo;
	err->array = 0;
	err->type = "boolean";
	return 0;
}

TOLUA_API int tolua_isnumber(lua_State* L, int lo, int def, tolua_Error* err)
{
	if (def && lua_gettop(L) < abs(lo)) return 1;
	if (lua_isnumber(L, lo)) return 1;
	err->index = lo;
	err->array = 0;
	err->type = "number";
	return 0;
}

TOLUA_API int tolua_isinteger(lua_State* L, int lo, int def, tolua_Error* err)
{                                                                                                                                                                                                                                                                                                                                                                                        
	if (def && lua_gettop(L) < abs(lo)) return 1;
	if (lua_isnumber(L, lo)) return 1;
	err->index = lo;
	err->array = 0;
	err->type = "integer";
	return 0;
}

TOLUA_API int tolua_isstring(lua_State* L, int lo, int def, tolua_Error* err)
{
	if (def && lua_gettop(L) < abs(lo)) return 1;
	if (lua_isnil(L, lo) || lua_isstring(L, lo)) return 1;
	err->index = lo;
	err->array = 0;
	err->type = "string";
	return 0;
}

TOLUA_API int tolua_istable(lua_State* L, int lo, int def, tolua_Error* err)
{
	if (def && lua_gettop(L) < abs(lo)) return 1;
	if (lua_istable(L, lo)) return 1;
	err->index = lo;
	err->array = 0;
	err->type = "table";
	return 0;
}

TOLUA_API int tolua_isusertable(lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
	if (def && lua_gettop(L) < abs(lo)) return 1;
	if (lua_isusertable(L, lo, type)) return 1;
	err->index = lo;
	err->array = 0;
	err->type = type;
	return 0;
}


TOLUA_API int tolua_isuserdata(lua_State* L, int lo, int def, tolua_Error* err)
{
	if (def && lua_gettop(L) < abs(lo)) return 1;
	if (lua_isnil(L, lo) || lua_isuserdata(L, lo)) return 1;
	err->index = lo;
	err->array = 0;
	err->type = "userdata";
	return 0;
}

TOLUA_API int tolua_isvaluenil(lua_State* L, int lo, tolua_Error* err)
{
	if (lua_gettop(L) < abs(lo)) return 0; // somebody else should check this
	if (!lua_isnil(L, lo)) return 0;
	err->index = lo;
	err->array = 0;
	err->type = "value";
	return 1;
};

TOLUA_API int tolua_isvalue(lua_State* L, int lo, int def, tolua_Error* err)
{
	if (def || abs(lo) <= lua_gettop(L)) return 1; // any valid index
	err->index = lo;
	err->array = 0;
	err->type = "value";
	return 0;
}

TOLUA_API int tolua_isusertype(lua_State* L, int lo, const char* type, int def, tolua_Error* err)
{
	if (def && lua_gettop(L) < abs(lo)) return 1;
	if (lua_isnil(L, lo) || tolua_istype(L, lo, type)) return 1;
	err->index = lo;
	err->array = 0;
	err->type = type;
	return 0;
}

TOLUA_API int tolua_isvaluearray(lua_State* L, int lo, int dim, int def, tolua_Error* err)
{
	if (!tolua_istable(L, lo, def, err)) return 0;
	else return 1;
}

TOLUA_API int tolua_isbooleanarray(lua_State* L, int lo, int dim, int def, tolua_Error* err)
{
	if (!tolua_istable(L, lo, def, err))
	{
		return 0;
	}
	else
	{
		int i;
		for (i = 1; i <= dim; ++i)
		{
			lua_pushnumber(L, i);
			lua_gettable(L, lo);
			if (!(lua_isnil(L, -1) || lua_isboolean(L, -1)) &&
				!(def && lua_isnil(L, -1)))
			{
				err->index = lo;
				err->array = 1;
				err->type = "boolean";
				return 0;
			}
			lua_pop(L, 1);
		}
	}
	return 1;
}

TOLUA_API int tolua_isnumberarray(lua_State* L, int lo, int dim, int def, tolua_Error* err)
{
	if (!tolua_istable(L, lo, def, err))
	{
		return 0;
	}
	else
	{
		int i;
		for (i = 1; i <= dim; ++i)
		{
			lua_pushnumber(L, i);
			lua_gettable(L, lo);
			if (!lua_isnumber(L, -1) &&
				!(def && lua_isnil(L, -1)))
			{
				err->index = lo;
				err->array = 1;
				err->type = "number";
				return 0;
			}
			lua_pop(L, 1);
		}
	}
	return 1;
}

TOLUA_API int tolua_isintegerarray(lua_State* L, int lo, int dim, int def, tolua_Error* err)
{
	if (!tolua_istable(L, lo, def, err))
	{
		return 0;
	}
	else
	{
		int i;
		for (i = 1; i <= dim; ++i)
		{
			lua_pushnumber(L, i);
			lua_gettable(L, lo);
			if (!lua_isnumber(L, -1) &&
				!(def && lua_isnil(L, -1)))
			{
				err->index = lo;
				err->array = 1;
				err->type = "integer";
				return 0;
			}
			lua_pop(L, 1);
		}
	}
	return 1;
}

TOLUA_API int tolua_isstringarray(lua_State* L, int lo, int dim, int def, tolua_Error* err)
{
	if (!tolua_istable(L, lo, def, err))
	{
		return 0;
	}
	else
	{
		int i;
		for (i = 1; i <= dim; ++i)
		{
			lua_pushnumber(L, i);
			lua_gettable(L, lo);
			if (!(lua_isnil(L, -1) || lua_isstring(L, -1)) &&
				!(def && lua_isnil(L, -1)))
			{
				err->index = lo;
				err->array = 1;
				err->type = "string";
				return 0;
			}
			lua_pop(L, 1);
		}
	}
	return 1;
}

TOLUA_API int tolua_istablearray(lua_State* L, int lo, int dim, int def, tolua_Error* err)
{
	if (!tolua_istable(L, lo, def, err))
	{
		return 0;
	}
	else
	{
		int i;
		for (i = 1; i <= dim; ++i)
		{
			lua_pushnumber(L, i);
			lua_gettable(L, lo);
			if (!lua_istable(L, -1) &&
				!(def && lua_isnil(L, -1)))
			{
				err->index = lo;
				err->array = 1;
				err->type = "table";
				return 0;
			}
			lua_pop(L, 1);
		}
	}
	return 1;
}

TOLUA_API int tolua_isuserdataarray(lua_State* L, int lo, int dim, int def, tolua_Error* err)
{
	if (!tolua_istable(L, lo, def, err))
	{
		return 0;
	}
	else
	{
		int i;
		for (i = 1; i <= dim; ++i)
		{
			lua_pushnumber(L, i);
			lua_gettable(L, lo);
			if (!(lua_isnil(L, -1) || lua_isuserdata(L, -1)) &&
				!(def && lua_isnil(L, -1)))
			{
				err->index = lo;
				err->array = 1;
				err->type = "userdata";
				return 0;
			}
			lua_pop(L, 1);
		}
	}
	return 1;
}

TOLUA_API int tolua_isusertypearray(lua_State* L, int lo, const char* type, int dim, int def, tolua_Error* err)
{
	if (!tolua_istable(L, lo, def, err))
	{
		return 0;
	}
	else
	{
		int i;
		for (i = 1; i <= dim; ++i)
		{
			lua_pushnumber(L, i);
			lua_gettable(L, lo);
			if (!(lua_isnil(L, -1) || lua_isuserdata(L, -1)) &&
				!(def && lua_isnil(L, -1)))
			{
				err->index = lo;
				err->type = type;
				err->array = 1;
				return 0;
			}
			lua_pop(L, 1);
		}
	}
	return 1;
}
