/****************************************************************************
 Copyright(c) 2011 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files(the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCLuaEngine.h"
#include "cocos2d.h"
#include "cocoa/CCArray.h"
#include "CCScheduler.h"
#include "LuaCocos2d.h"
#include "Cocos2dxLuaLoader.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "platform/ios/CCLuaObjcBridge.h"
#endif

NS_CC_BEGIN

static int lua_print(lua_State * luastate)
{
	int nargs = lua_gettop(luastate);
	string t;
	for (int i = 1; i <= nargs; i++)
	{
		if (lua_isnone(luastate, i)) t += "none";
		else if (lua_isnil(luastate, i)) t += "nil";
		else if (lua_isboolean(luastate, i))
		{
			if (lua_toboolean(luastate, i) != 0) t += "true";
			else t += "false";
		}
		else if (lua_isfunction(luastate, i)) t += "function";
		else if (lua_islightuserdata(luastate, i)) t += "lightuserdata";
		else if (lua_isthread(luastate, i)) t += "thread";
		else
		{
			const char * str = lua_tostring(luastate, i);
			if (str) t += lua_tostring(luastate, i);
			else t += tolua_typename(luastate, i);
		}
		if (i != nargs) t += "\t";
	}
	CCLOG("%s", t.c_str());
	return 0;
}

CCLuaEngine::CCLuaEngine() :
m_callFromLua(0)
{
	L = lua_open();
	luaL_openlibs(L);
	toluafix_open(L);
	tolua_Cocos2d_open(L);

	// Register our version of the global "print" function
	const luaL_reg global_functions[] =
	{
		{ "print", lua_print },
		{ NULL, NULL }
	};
	luaL_register(L, "_G", global_functions);
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	CCLuaObjcBridge::luaopen_luaoc(m_state);
#endif
	// add cocos2dx loader
	addLuaLoader(cocos2dx_lua_loader);

	tolua_beginmodule(L, 0);
	tolua_beginmodule(L, "CCDictionary");
	tolua_variable(L, "keys", CCDictionary_keys, nullptr);
	tolua_variable(L, "randomObject", CCDictionary_randomObject, nullptr);
	tolua_function(L, "set", CCDictionary_set);
	tolua_function(L, "get", CCDictionary_get);
	tolua_endmodule(L);
	tolua_endmodule(L);

	tolua_LuaCode_open(L);

	lua_settop(L, 0); // clear stack
}

CCLuaEngine* CCLuaEngine::sharedEngine()
{
	static CCLuaEngine engine;
	return &engine;
}

void CCLuaEngine::addSearchPath(const char* path)
{
	lua_getglobal(L, "package");/* L: package */
	lua_getfield(L, -1, "path");/* get package.path, L: package path */
	const char* cur_path = lua_tostring(L, -1);
	lua_pushfstring(L, "%s;%s/?.lua", cur_path, path);/* L: package path newpath */
	lua_setfield(L, -3, "path");/* package.path = newpath, L: package path */
	lua_pop(L, 2);/* L: - */
}

void CCLuaEngine::addLuaLoader(lua_CFunction func)
{
	if (!func) return;
	// stack content after the invoking of the function
	// get loader table
	lua_getglobal(L, "package");/* L: package */
	lua_getfield(L, -1, "loaders");/* L: package, loaders */
	// insert loader into index 2
	lua_pushcfunction(L, func);/* L: package, loaders, func */
	for (int i = lua_objlen(L, -2) + 1; i > 2; --i)
	{
		lua_rawgeti(L, -2, i - 1);/* L: package, loaders, func, function */
		// we call lua_rawgeti, so the loader table now is at -3
		lua_rawseti(L, -3, i);/* L: package, loaders, func */
	}
	lua_rawseti(L, -2, 2);/* L: package, loaders */
	// set loaders into package
	lua_setfield(L, -2, "loaders");/* L: package */
	lua_pop(L, 1);
}

void CCLuaEngine::removeScriptHandler(int nHandler)
{
	toluafix_remove_function_by_refid(L, nHandler);
}

void CCLuaEngine::removePeer(CCObject* object)
{
	if (object->isLuaRef())
	{
		int refid = object->getLuaRef();
		lua_rawgeti(L, LUA_REGISTRYINDEX, TOLUA_UBOX);// ubox
		lua_rawgeti(L, -1, refid);// ubox ud
		if (!lua_isnil(L, -1))
		{
			lua_pushvalue(L, TOLUA_NOPEER);// ubox ud nopeer
			lua_setfenv(L, -2);// ud<nopeer>, ubox ud
		}
		lua_pop(L, 2);// empty
	}
}

int CCLuaEngine::executeString(const char *codes)
{
	luaL_loadstring(L, codes);
	return lua_execute(0);
}

int CCLuaEngine::executeScriptFile(const char* filename)
{
	string code("require \"");
	code.append(filename);
	code.append("\"");
	return CCLuaEngine::executeString(code.c_str());
}

int CCLuaEngine::executeGlobalFunction(const char* functionName)
{
	lua_getglobal(L, functionName);/* query function by name, stack: function */
	if (!lua_isfunction(L, -1))
	{
		CCLOG("[LUA ERROR] name '%s' does not represent a Lua function", functionName);
		lua_pop(L, 1);
		return 0;
	}
	return lua_execute(0);
}

int CCLuaEngine::executeFunction(int nHandler, int paramCount, CCObject* params[])
{
	for (int i = 0; i < paramCount; i++)
	{
		tolua_pushccobject(L, params[i]);
	}
	return lua_execute(nHandler, paramCount);
}

int CCLuaEngine::executeFunction(int nHandler, int paramCount, void* params[], const char* paramNames[])
{
	for (int i = 0; i < paramCount; i++)
	{
		tolua_pushusertype(L, params[i], paramNames[i]);
	}
	return lua_execute(nHandler, paramCount);
}

int CCLuaEngine::executeFunction(int nHandler, int paramCount)
{
	return lua_execute(nHandler, paramCount);
}

int CCLuaEngine::executeActionUpdate(int nHandler, void* param, const char* paramName, float deltaTime)
{
	if (!nHandler) return 0;
	tolua_pushusertype(L, param, paramName);
	lua_pushnumber(L, deltaTime);
	return lua_execute(nHandler, 2);
}

int CCLuaEngine::executeNodeEvent(CCNode* pNode, int nAction)
{
	int nHandler = pNode->getScriptHandler();
	if (!nHandler) return 0;
	lua_pushinteger(L, nAction);
	return lua_execute(nHandler, 1);
}

int CCLuaEngine::executeAppEvent(int nHandler, int eventType)
{
	if (!nHandler) return 0;
	lua_pushinteger(L, eventType);
	return lua_execute(nHandler, 1);
}

int CCLuaEngine::executeMenuItemEvent(int eventType, CCMenuItem* pMenuItem)
{
	int nHandler = pMenuItem->getScriptTapHandler();
	if (!nHandler) return 0;
	lua_pushinteger(L, eventType);
	tolua_pushccobject(L, pMenuItem);
	return lua_execute(nHandler, 2);
}

int CCLuaEngine::executeSchedule(int nHandler, float dt, CCNode* pNode)
{
	if (!nHandler) return 0;
	if (pNode) tolua_pushccobject(L, pNode);
	lua_pushnumber(L, dt);
	return lua_execute(nHandler, pNode ? 2 : 1);
}

int CCLuaEngine::executeLayerTouchEvent(CCLayer* pLayer, int eventType, CCTouch *pTouch)
{
	CCTouchScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptTouchHandlerEntry();
	if (!pScriptHandlerEntry) return 0;
	int nHandler = pScriptHandlerEntry->getHandler();
	if (!nHandler) return 0;
	lua_pushinteger(L, eventType);
	tolua_pushccobject(L, pTouch);
	return lua_execute(nHandler, 2);
}

int CCLuaEngine::executeLayerTouchesEvent(CCLayer* pLayer, int eventType, CCSet *pTouches)
{
	CCTouchScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptTouchHandlerEntry();
	if (!pScriptHandlerEntry) return 0;
	int nHandler = pScriptHandlerEntry->getHandler();
	if (!nHandler) return 0;
	lua_pushinteger(L, eventType);
	CCDirector* pDirector = CCDirector::sharedDirector();
	lua_createtable(L, pTouches->count(), 0);
	int i = 1;
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCTouch* pTouch = (CCTouch*)*it;
		tolua_pushccobject(L, pTouch);
		lua_rawseti(L, -2, i++);
	}
	return lua_execute(nHandler, 2);
}

int CCLuaEngine::executeLayerKeypadEvent(CCLayer* pLayer, int eventType)
{
	CCScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptKeypadHandlerEntry();
	if (!pScriptHandlerEntry) return 0;
	int nHandler = pScriptHandlerEntry->getHandler();
	if (!nHandler) return 0;
	lua_pushinteger(L, eventType);
	return lua_execute(nHandler, 1);
}

int CCLuaEngine::executeAccelerometerEvent(CCLayer* pLayer, CCAcceleration* pAccelerationValue)
{
	CCScriptHandlerEntry* pScriptHandlerEntry = pLayer->getScriptAccelerateHandlerEntry();
	if (!pScriptHandlerEntry) return 0;
	int nHandler = pScriptHandlerEntry->getHandler();
	if (!nHandler) return 0;
	lua_pushnumber(L, pAccelerationValue->x);
	lua_pushnumber(L, pAccelerationValue->y);
	lua_pushnumber(L, pAccelerationValue->z);
	lua_pushnumber(L, pAccelerationValue->timestamp);
	return lua_execute(nHandler, 4);
}

int CCLuaEngine::executeEvent(int nHandler, const char* pEventName, CCObject* pEventSource /* = NULL*/, const char* pEventSourceClassName /* = NULL*/)
{
	lua_pushstring(L, pEventName);
	if (pEventSource) tolua_pushccobject(L, pEventSource);
	return lua_execute(nHandler, pEventSource ? 2 : 1);
}

bool CCLuaEngine::executeAssert(bool cond, const char *msg)
{
	if (m_callFromLua == 0) return false;
	lua_pushfstring(L, "ASSERT FAILED ON LUA EXECUTE: %s", msg ? msg : "unknown");
	lua_error(L);
	return true;
}

bool CCLuaEngine::scriptHandlerEqual(int nHandlerA, int nHandlerB)
{
	toluafix_get_function_by_refid(L, nHandlerA);
	toluafix_get_function_by_refid(L, nHandlerB);
	int result = lua_equal(L, -1, -2);
	lua_pop(L, 2);
	return result != 0;
}

static int traceback(lua_State* L)
{
	luaL_traceback(L, L, lua_tostring(L, 1), 1);
	CCLOG("[LUA ERROR] %s", lua_tostring(L, -1));
	lua_pop(L, 1);
	return 1;
}

int CCLuaEngine::lua_invoke(int numArgs)
{
#ifndef TOLUA_RELEASE
	int functionIndex = -(numArgs + 1);
	int traceIndex = functionIndex - 1;
	if (!lua_isfunction(L, functionIndex))
	{
		CCLOG("value at stack [%d] is not function", functionIndex);
		lua_pop(L, numArgs + 1); // remove function and arguments
		return 0;
	}

	lua_pushcfunction(L, traceback);// func args... traceback
	lua_insert(L, traceIndex);// traceback func args...

	++m_callFromLua;
	int error = lua_pcall(L, numArgs, 1, traceIndex);// traceback error ret
	--m_callFromLua;

	if (error)// traceback error
	{
		lua_settop(L, 0);// stack clear
		return 0;
	}
#else
	lua_call(L, numArgs, 1);
#endif
	return 1;
}

int CCLuaEngine::lua_execute(int numArgs)
{
	int ret = 0;
	if (lua_invoke(numArgs))
	{
		// get return value
		if (lua_isnumber(L, -1))// traceback ret
		{
			ret = lua_tointeger(L, -1);
		}
		else if (lua_isboolean(L, -1))
		{
			ret = lua_toboolean(L, -1);
		}
		lua_settop(L, 0);// stack clear
	}
	return ret;
}

int CCLuaEngine::lua_execute(int nHandler, int numArgs)
{
	toluafix_get_function_by_refid(L, nHandler);// args... func
	int t = lua_type(L, -1);
	if (!lua_isfunction(L, -1))
	{
		CCLOG("[LUA ERROR] function refid '%d' does not reference a Lua function", nHandler);
		lua_pop(L, 1);
		return 0;
	}
	if (numArgs > 0) lua_insert(L, -(numArgs + 1));// func args...

	return lua_execute(numArgs);
}

int CCLuaEngine::lua_invoke(int nHandler, int numArgs)
{
	toluafix_get_function_by_refid(L, nHandler);// args... func
	if (!lua_isfunction(L, -1))
	{
		CCLOG("[LUA ERROR] function refid '%d' does not reference a Lua function", nHandler);
		lua_pop(L, 1);
		return 0;
	}
	if (numArgs > 0) lua_insert(L, -(numArgs + 1));// func args...

	return lua_invoke(numArgs);
}

int CCLuaEngine::executeActionCreate(int nHandler)
{
	int handler = 0;
	lua_invoke(nHandler, 0);
	int top = lua_gettop(L);
	if (lua_isfunction(L, top))
	{
		handler = toluafix_ref_function(L, top);
	}
	lua_settop(L, 0);
	return handler;
}

NS_CC_END
