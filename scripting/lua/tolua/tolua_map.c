/* tolua: functions to map features
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
#include "tolua_event.h"
#include "lauxlib.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int tolua_callback;
int tolua_ubox;

/* Create metatable
    * Create and register new metatable
*/
static int tolua_newmetatable (lua_State* L, const char* name)
{
    int r = luaL_newmetatable(L,name);
#ifdef LUA_VERSION_NUM /* only lua 5.1 */
    if (r)
	{
        lua_pushvalue(L, -1);
        lua_pushstring(L, name);
        lua_settable(L, LUA_REGISTRYINDEX);// reg[mt] = type_name
    };
#endif
	if (r)
	{
		tolua_classevents(L);// set meta events
	}
	lua_pop(L, 1);
    return r;
}

/* Map super classes
    * It sets 'name' as being also a 'base', mapping all super classes of 'base' in 'name'
*/
static void mapsuper(lua_State* L, const char* name, const char* base)
{
	luaL_getmetatable(L, name);// mt
	lua_rawgeti(L, -1, MT_SUPER);// mt super
	if (lua_isnil(L, -1))
	{
		lua_pop(L, 1);// mt
		lua_newtable(L);// mt tb
		lua_pushvalue(L, -1);// mt tb tb
		lua_rawseti(L, -3, MT_SUPER);// mt[MT_SUPER] = tb, mt tb
	}
	lua_pushstring(L, base);// mt tb base
	lua_pushboolean(L, 1);// mt tb base true
	lua_rawset(L, -3);// tb[base] = true, mt tb

	/* set all super class of base as super class of name */
	luaL_getmetatable(L, base);// mt tb basemt
	lua_rawgeti(L, -1, MT_SUPER);// mt tb basemt basetb
	
	if (lua_istable(L, -1))
	{
		/* traverse basetb */
		lua_pushnil(L);// mt tb basemt basetb nil
		while (lua_next(L, -2) != 0)// mt tb basemt basetb k v
		{
			/* mt tb basemt basetb k v */
			lua_pushvalue(L, -2);    // mt tb basemt basetb k v k
			lua_insert(L, -2);       // mt tb basemt basetb k k v
			lua_rawset(L, -6);       // tb[k] = v, mt tb basemt basetb k
		}// mt tb basemt basetb
	}
	lua_pop(L, 4);// empty
}

/* creates a 'tolua_ubox' table for base clases, and
// expects the metatable and base metatable on the stack */
static void set_ubox(lua_State* L)
{
    if (!lua_isnil(L, -1))// mt basemt
	{
		lua_rawgeti(L, -1, MT_UBOX);// mt basemt ubox
    }
	else
	{
        lua_pushnil(L);// mt basemt nil
    };
	if (!lua_isnil(L, -1))// mt basemt ubox
	{
		lua_rawseti(L, -3, MT_UBOX);// mt[MT_UBOX] = ubox, mt basemt
    }
	else// mt basemt nil
	{
		lua_pop(L, 1);// mt basemt
        lua_newtable(L);// mt basemt tb
        /* make weak value metatable for ubox table to allow userdata to be
        garbage-collected */
        lua_newtable(L);// mt basemt tb tb1
        lua_pushliteral(L, "__mode");
        lua_pushliteral(L, "v");
		lua_rawset(L, -3);// tb1["__mode"] = "v"
        lua_setmetatable(L, -2);// tb<tb1>, mt basemt tb
		lua_rawseti(L, -3, MT_UBOX);// mt[MT_UBOX] = tb, mt basemt
    };
};

/* Map inheritance
    * It sets 'name' as derived from 'base' by setting 'base' as metatable of 'name'
*/
static void mapinheritance(lua_State* L, const char* name, const char* base)
{
    /* set metatable inheritance */
	luaL_getmetatable(L, name);// mt
	if (base && *base)
	{
		luaL_getmetatable(L, base);// mt basemt
	}
    else
	{
		/* already has a mt, we don't overwrite it */
        if (lua_getmetatable(L, -1))// mt mtmt
		{
            lua_pop(L, 2);
            return;
		};
		luaL_getmetatable(L, "tolua_class");// mt basemt
		set_ubox(L);// mt basemt
    };
	lua_setmetatable(L, -2);// mt<basemt>, mt
	lua_pop(L, 1);// empty
}

/* Object type
*/
static int tolua_bnd_type (lua_State* L)
{
    tolua_typename(L,lua_gettop(L));
    return 1;
}

/* Type casting
*/
static int tolua_bnd_cast(lua_State* L)
{
    void* v;
    const char* s;
	int ccobject_idx;
	int target_idx;
	int start_idx;
	int end_idx;
	int base_idx;
	int can_cast = 0;
	int is_ccobject = 0;
    if (lua_islightuserdata(L, 1))
	{
        v = tolua_touserdata(L, 1, NULL);
    }
	else
	{
        v = tolua_tousertype(L, 1, 0);
    };
	s = tolua_tostring(L, 2, NULL);
	if (v && s)
	{
		lua_getmetatable(L, 1);
		start_idx = lua_gettop(L);
		luaL_getmetatable(L, "tolua_class");
		base_idx = lua_gettop(L);
		luaL_getmetatable(L, "CCObject");
		ccobject_idx = lua_gettop(L);
		luaL_getmetatable(L, s);
		target_idx = lua_gettop(L);
		while (!lua_isnil(L, -1) && lua_rawequal(L, base_idx, -1) == 0)
		{
			if (lua_rawequal(L, start_idx, -1) != 0)
			{
				can_cast = 1;
			}
			if (lua_rawequal(L, ccobject_idx, -1) != 0)
			{
				is_ccobject = 1;
				break;
			}
			lua_getmetatable(L, -1);
		}
		end_idx = lua_gettop(L);
		if (can_cast)
		{
			lua_pop(L, end_idx - start_idx + 1);
			if (is_ccobject) tolua_pushccobject(L, v, s);
			else tolua_pushusertype(L, v, s);
		}
		else
		{
			lua_pop(L, end_idx - start_idx - 3);
			lua_getmetatable(L, start_idx);
			while (!lua_isnil(L, -1) && lua_rawequal(L, base_idx, -1) == 0)
			{
				if (lua_rawequal(L, target_idx, -1) != 0)
				{
					can_cast = 1;
					break;
				}
				lua_getmetatable(L, -1);
			}
			end_idx = lua_gettop(L);
			lua_pop(L, end_idx - start_idx + 1);
			if (can_cast)
			{
				if (is_ccobject) tolua_pushccobject(L, v, s);
				else tolua_pushusertype(L, v, s);
			}
			else
			{
				if (is_ccobject) tolua_pushccobject(L, v, s);
				else tolua_pushusertype(L, v, s);
			}
		}
	}
	else
	{
		lua_pushnil(L);
	}
    return 1;
}

/* Test userdata is null
*/
static int tolua_bnd_isnulluserdata (lua_State* L)
{
    void **ud = (void**)lua_touserdata(L, -1);
    tolua_pushboolean(L, ud == NULL || *ud == NULL);
    return 1;
}

/* Inheritance
*/
static int tolua_bnd_inherit(lua_State* L)
{
    /* stack: lua object, c object */
    lua_pushvalue(L, -1);
	lua_rawseti(L, -3, TOLUA_C_INSTANCE);// l_obj[TOLUA_C_INSTANCE] = c_obj
    return 0;
};

#ifdef LUA_VERSION_NUM /* lua 5.1 */
static int tolua_bnd_setpeer(lua_State* L)
{
    /* stack: userdata, table */
    if (!lua_isuserdata(L, -2))
	{
        lua_pushstring(L, "Invalid argument #1 to setpeer: userdata expected.");
        lua_error(L);
    };
    if (lua_isnil(L, -1))
	{
        lua_pop(L, 1);
        lua_pushvalue(L, TOLUA_NOPEER);
    };
    lua_setfenv(L, -2);
    return 0;
};

static int tolua_bnd_getpeer(lua_State* L)
{
    /* stack: userdata */
    lua_getfenv(L, -1);
    if (lua_rawequal(L, -1, TOLUA_NOPEER))
	{
        lua_pop(L, 1);
        lua_pushnil(L);
    };
    return 1;
};
#endif

TOLUA_API void tolua_open(lua_State* L)
{
    int top = lua_gettop(L);
    lua_pushstring(L,"tolua_opened");
    lua_rawget(L,LUA_REGISTRYINDEX);
    if (!lua_isboolean(L,-1))
    {
        lua_pushstring(L,"tolua_opened");
        lua_pushboolean(L,1);
        lua_rawset(L,LUA_REGISTRYINDEX);
#ifndef LUA_VERSION_NUM /* only prior to lua 5.1 */
        /* create peer object table */
        lua_pushstring(L, "tolua_peers");
        lua_newtable(L);
        /* make weak key metatable for peers indexed by userdata object */
        lua_newtable(L);
        lua_pushliteral(L, "__mode");
        lua_pushliteral(L, "k");
        lua_rawset(L, -3);                /* stack: string peers mt */
        lua_setmetatable(L, -2);   /* stack: string peers */
        lua_rawset(L,LUA_REGISTRYINDEX);
#endif
        /* create object ptr -> udata mapping table */
		lua_pushlightuserdata(L, TOLUA_UBOX);
        lua_newtable(L);
        /* make weak value metatable for ubox table to allow userdata to be
           garbage-collected */
		lua_newtable(L);
        lua_pushliteral(L, "__mode");
        lua_pushliteral(L, "v");
        lua_rawset(L, -3);               // stack: string ubox mt
        lua_setmetatable(L, -2);  // stack: string ubox
		lua_rawset(L,LUA_REGISTRYINDEX);

		tolua_newmetatable(L, "tolua_class");

        tolua_module(L,NULL,0);
        tolua_beginmodule(L,NULL);
        tolua_module(L,"tolua",0);
        tolua_beginmodule(L,"tolua");
        tolua_function(L,"type",tolua_bnd_type);
        tolua_function(L,"cast",tolua_bnd_cast);
        tolua_function(L,"isnull",tolua_bnd_isnulluserdata);
        tolua_function(L,"inherit", tolua_bnd_inherit);
#ifdef LUA_VERSION_NUM /* lua 5.1 */
        tolua_function(L, "setpeer", tolua_bnd_setpeer);
        tolua_function(L, "getpeer", tolua_bnd_getpeer);
#endif
        tolua_endmodule(L);
        tolua_endmodule(L);
    }
    lua_settop(L,top);
}

/* Copy a C object
*/
TOLUA_API void* tolua_copy(lua_State* L, void* value, unsigned int size)
{
    void* clone = (void*)malloc(size);
    if (clone)
        memcpy(clone,value,size);
    else
        tolua_error(L,"insuficient memory",NULL);
    return clone;
}

/* Default collect function
*/
TOLUA_API int tolua_default_collect(lua_State* tolua_S)
{
    void* self = tolua_tousertype(tolua_S,1,0);
    free(self);
    return 0;
}

/* Register a usertype
    * It creates the correspoding metatable in the registry, for both 'type' and 'const type'.
    * It maps 'const type' as being also a 'type'
*/
TOLUA_API void tolua_usertype(lua_State* L, const char* type)
{
    char ctype[128] = "const ";
    strncat(ctype,type,120);

    /* create both metatables */
    if (tolua_newmetatable(L,ctype) && tolua_newmetatable(L,type))
        mapsuper(L,type,ctype);             /* 'type' is also a 'const type' */
}


/* Begin module
    * It pushes the module (or class) table on the stack
*/
TOLUA_API void tolua_beginmodule (lua_State* L, const char* name)
{
    if (name)
    {
        lua_pushstring(L,name);
        lua_rawget(L,-2);
    }
    else
        lua_pushvalue(L,LUA_GLOBALSINDEX);
}

/* End module
    * It pops the module (or class) from the stack
*/
TOLUA_API void tolua_endmodule (lua_State* L)
{
    lua_pop(L,1);
}

/* Map module
    * It creates a new module
*/
#if 1
TOLUA_API void tolua_module (lua_State* L, const char* name, int hasvar)
{
    if (name)
    {
        /* tolua module */
        lua_pushstring(L,name);
        lua_rawget(L,-2);
        if (!lua_istable(L,-1))  /* check if module already exists */
        {
            lua_pop(L,1);
            lua_newtable(L);
            lua_pushstring(L,name);
            lua_pushvalue(L,-2);
            lua_rawset(L,-4);       /* assing module into module */
        }
    }
    else
    {
        /* global table */
        lua_pushvalue(L,LUA_GLOBALSINDEX);
    }
    if (hasvar)
    {
        if (!tolua_ismodulemetatable(L))  /* check if it already has a module metatable */
        {
            /* create metatable to get/set C/C++ variable */
            lua_newtable(L);
            tolua_moduleevents(L);
            if (lua_getmetatable(L,-2))
                lua_setmetatable(L,-2);  /* set old metatable as metatable of metatable */
            lua_setmetatable(L,-2);
        }
    }
    lua_pop(L,1);               /* pop module */
}
#else
TOLUA_API void tolua_module (lua_State* L, const char* name, int hasvar)
{
    if (name)
    {
        /* tolua module */
        lua_pushstring(L,name);
        lua_newtable(L);
    }
    else
    {
        /* global table */
        lua_pushvalue(L,LUA_GLOBALSINDEX);
    }
    if (hasvar)
    {
        /* create metatable to get/set C/C++ variable */
        lua_newtable(L);
        tolua_moduleevents(L);
        if (lua_getmetatable(L,-2))
            lua_setmetatable(L,-2);  /* set old metatable as metatable of metatable */
        lua_setmetatable(L,-2);
    }
    if (name)
        lua_rawset(L,-3);       /* assing module into module */
    else
        lua_pop(L,1);           /* pop global table */
}
#endif

static void push_collector(lua_State* L, const char* type, lua_CFunction col)
{
    /* push collector function, but only if it's not NULL. */
    if (!col) return;
    luaL_getmetatable(L,type);// mt
    lua_pushcfunction(L,col);// mt cfunc
	lua_rawseti(L, -2, MT_DEL);// mt[MT_DEL] = cfunc, mt
    lua_pop(L, 1);// pop mt
};

/* Map C class
    * It maps a C class, setting the appropriate inheritance and super classes.
*/
TOLUA_API void tolua_cclass (lua_State* L, const char* lname, const char* name, const char* base, lua_CFunction col)
{
    char cname[128] = "const ";
    char cbase[128] = "const ";
    strncat(cname,name,120);
    strncat(cbase,base,120);

    mapinheritance(L,name,base);
    mapinheritance(L,cname,name);

	if (base && *base)
	{
		mapsuper(L, cname, cbase);
		mapsuper(L, name, base);
	}

    push_collector(L, name, col);

	lua_pushstring(L, lname);
    luaL_getmetatable(L,name);
	/* assign class metatable to module*/
	lua_rawset(L, -3);

    /* now we also need to store the collector table for the const
       instances of the class */
    push_collector(L, cname, col);
}

/* Add base
    * It adds additional base classes to a class (for multiple inheritance)
    * (not for now)
    */
TOLUA_API void tolua_addbase(lua_State* L, char* name, char* base)
{
    char cname[128] = "const ";
    char cbase[128] = "const ";
    strncat(cname,name,120);
    strncat(cbase,base,120);

    mapsuper(L,cname,cbase);
    mapsuper(L,name,base);
};


/* Map function
    * It assigns a function into the current module (or class)
*/
TOLUA_API void tolua_function(lua_State* L, const char* name, lua_CFunction func)
{
    lua_pushstring(L,name);
    lua_pushcfunction(L,func);
    lua_rawset(L,-3);
}

TOLUA_API void tolua_call(lua_State* L, int index, lua_CFunction func)
{
	lua_pushcfunction(L, func);
	lua_rawseti(L, -2, index);
}

/* sets the __call event for the class (expects the class' main table on top) */
/*    never really worked :(
TOLUA_API void tolua_set_call_event(lua_State* L, lua_CFunction func, char* type) {

    lua_getmetatable(L, -1);
    //luaL_getmetatable(L, type);
    lua_pushstring(L,"__call");
    lua_pushcfunction(L,func);
    lua_rawset(L,-3);
    lua_pop(L, 1);
};
*/

/* Map constant number
    * It assigns a constant number into the current module (or class)
*/
TOLUA_API void tolua_constant(lua_State* L, const char* name, lua_Number value)
{
    lua_pushstring(L,name);
    tolua_pushnumber(L,value);
    lua_rawset(L,-3);
}

/* Map variable
    * It assigns a variable into the current module (or class)
*/
TOLUA_API void tolua_variable(lua_State* L, const char* name, lua_CFunction get, lua_CFunction set)
{
    /* get func */
    lua_rawgeti(L,-1, MT_GET);
    if (!lua_istable(L,-1))
    {
        /* create .get table, leaving it at the top */
        lua_pop(L,1);
        lua_newtable(L);
        lua_pushvalue(L,-1);
        lua_rawseti(L,-3,MT_GET);
    }
    lua_pushstring(L,name);
    lua_pushcfunction(L,get);
    lua_rawset(L,-3);                  /* store variable */
    lua_pop(L,1);                      /* pop .get table */

    /* set func */
    if (set)
    {
        lua_rawgeti(L,-1,MT_SET);
        if (!lua_istable(L,-1))
        {
            /* create .set table, leaving it at the top */
            lua_pop(L,1);
            lua_newtable(L);
            lua_pushvalue(L,-1);
            lua_rawseti(L,-3,MT_SET);
        }
        lua_pushstring(L,name);
        lua_pushcfunction(L,set);
        lua_rawset(L,-3);                  /* store variable */
        lua_pop(L,1);                      /* pop .set table */
    }
}

/* Access const array
    * It reports an error when trying to write into a const array
*/
static int const_array(lua_State* L)
{
    luaL_error(L,"value of const array cannot be changed");
    return 0;
}

/* Map an array
    * It assigns an array into the current module (or class)
*/
TOLUA_API void tolua_array(lua_State* L, const char* name, lua_CFunction get, lua_CFunction set)
{
    lua_rawgeti(L,-1,MT_GET);
    if (!lua_istable(L,-1))
    {
        /* create .get table, leaving it at the top */
        lua_pop(L,1);
        lua_newtable(L);
        lua_pushvalue(L,-1);
        lua_rawseti(L,-3,MT_GET);
    }
    lua_pushstring(L,name);

    lua_newtable(L);           /* create array metatable */
    lua_pushvalue(L,-1);
    lua_setmetatable(L,-2);    /* set the own table as metatable (for modules) */
    lua_pushstring(L,"__index");
    lua_pushcfunction(L,get);
    lua_rawset(L,-3);
    lua_pushstring(L,"__newindex");
    lua_pushcfunction(L,set?set:const_array);
    lua_rawset(L,-3);

    lua_rawset(L,-3);                  /* store variable */
    lua_pop(L,1);                      /* pop .get table */
}


TOLUA_API void tolua_dobuffer(lua_State* L, char* B, unsigned int size, const char* name) {

#ifdef LUA_VERSION_NUM /* lua 5.1 */
    if (!luaL_loadbuffer(L, B, size, name)) lua_pcall(L, 0, 0, 0);
#else
    lua_dobuffer(L, B, size, name);
#endif
};

