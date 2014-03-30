
#ifndef __TOLUA_FIX_H_
#define __TOLUA_FIX_H_

#include "tolua++.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
#define TOLUA_REFID_PTR_MAPPING "tolua_ptr_mapping"
#define TOLUA_REFID_TYPE_MAPPING "tolua_type_mapping"
#define TOLUA_REFID_FUNCTION_MAPPING "tolua_function_mapping"
    
TOLUA_API void toluafix_open(lua_State* L);
TOLUA_API int toluafix_pushusertype_ccobject(lua_State* L,
                                             int refid,
                                             int* luaRef,
                                             void* ptr,
                                             const char* type);
TOLUA_API int toluafix_remove_ccobject_by_refid(lua_State* L, int refid);
TOLUA_API int toluafix_ref_function(lua_State* L, int lo, int def);
TOLUA_API void toluafix_get_function_by_refid(lua_State* L, int refid);
TOLUA_API void toluafix_remove_function_by_refid(lua_State* L, int refid);
TOLUA_API int toluafix_isfunction(lua_State* L, int lo, const char* type, int def, tolua_Error* err);
TOLUA_API int toluafix_totable(lua_State* L, int lo, int def);
TOLUA_API int toluafix_istable(lua_State* L, int lo, const char* type, int def, tolua_Error* err);
TOLUA_API void toluafix_stack_dump(lua_State* L, const char* label);

#ifdef __cplusplus
} // extern "C"
#endif

#define TOLUAFIX_PUSHUSERTYPE_CCOBJECT(L, ptr, type) \
	if (ptr) toluafix_pushusertype_ccobject(L, ptr->getObjectId(), &ptr->m_nLuaRef, (void*)ptr, type); \
	else lua_pushnil(L)

#endif // __TOLUA_FIX_H_
