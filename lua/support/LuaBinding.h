
#ifndef __LUACOCOS2D_H_
#define __LUACOCOS2D_H_

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}

#include <string>
#include "tolua_fix.h"
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "Dorothy.h"
#include "DorothyModule.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace Dorothy;
using namespace Dorothy::Platform;

TOLUA_API int tolua_LuaBinding_open(lua_State* tolua_S);
TOLUA_API int tolua_LuaCode_open(lua_State* tolua_S);

#endif // __LUACOCOS2D_H_
