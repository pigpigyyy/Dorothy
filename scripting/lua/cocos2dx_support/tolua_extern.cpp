extern "C"
{
	#include "tolua++.h"
	#include "tolua_fix.h"
}
#include <stack>
using std::stack;
#include "cocos2d.h"
using namespace cocos2d;

static int g_ref_id = 0;
static stack<int> g_available_ref_ids;

extern "C" int alloc_ref_id()
{
	if (!g_available_ref_ids.empty())
	{
		int id = g_available_ref_ids.top();
		g_available_ref_ids.pop();
		//CCLOG("Reuse id: %d", id);
		return id;
	}
	else
	{
		g_ref_id++;
		//CCLOG("Alloc id: %d", g_ref_id);
		return g_ref_id;
	}
}

extern "C" void collect_ref_id(int refid)
{
	//CCLOG("Collect id: %d", refid);
	g_available_ref_ids.push(refid);
}

extern "C" void tolua_register_ccobject_gc(void* ptr)
{
	CCObject* object = (CCObject*)ptr;
	object->retain();
}

extern "C" int tolua_collect_ccobject(lua_State* tolua_S)
{
	CCObject* object = (CCObject*)tolua_tousertype(tolua_S, 1, 0);
	object->release();
	return 0;
}

extern "C" int tolua_pushccobject(lua_State* L, void* ptr, const char* type)
{
	return toluafix_pushusertype_ccobject(L, ((CCObject*)ptr)->getObjectId(), (void*)ptr, type);
}
