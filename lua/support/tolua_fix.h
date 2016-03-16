
#ifndef __TOLUA_FIX_H_
#define __TOLUA_FIX_H_

#include "tolua++.h"

#ifdef __cplusplus
extern "C"
{
#endif

TOLUA_API void toluafix_open(lua_State* L);
TOLUA_API int toluafix_ref_function(lua_State* L, int lo);
TOLUA_API void toluafix_get_function_by_refid(lua_State* L, int refid);
TOLUA_API void toluafix_remove_function_by_refid(lua_State* L, int refid);
TOLUA_API int toluafix_isfunction(lua_State* L, int lo, tolua_Error* err);
TOLUA_API void toluafix_stack_dump(lua_State* L, int offset, const char* label);
TOLUA_API int toluafix_get_callback_ref_count();
TOLUA_API int toluafix_get_max_callback_ref_count();
TOLUA_API void luaopen_lpeg(lua_State* L);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __TOLUA_FIX_H_
