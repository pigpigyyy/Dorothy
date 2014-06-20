-- usage: (use instead of ant)
-- tolua++ "-L" "basic.lua" "-o" "../../scripting/lua/cocos2dx_support/LuaCocos2d.cpp" "Cocos2d.pkg"

_push_functions = _push_functions or {}
_collect_functions = _collect_functions or {}
local ccobjects = {
"CCObject",
"CCNode",
"CCSprite",
"CCClippingNode",
"CCSpriteBatchNode",
"CCRenderTexture",
"CCMotionStreak",
"CCParallaxNode",
"CCAction",
"CCFiniteTimeAction",
"CCActionInterval",
"CCDrawNode",
"CCLabelTTF",
"CCLabelBMFont",
"CCLabelAtlas",
"CCTextFieldTTF",
"CCImage",
"CCLayer",
"CCLayerColor",
"CCLayerGradient",
"CCTouch",
"CCMenu",
"CCMenuItem",
"CCProgressTimer",
"CCTexture2D",
"CCArray",
"CCScene",
"CCTMXLayer",
"CCTMXTiledMap",
"CCTileMapAtlas",
"CCScheduler",
"CCSpeed",
"oNode3D",
"oModel",
"oListener",
"oLine",
"oFace",
"oEffect",
"oAILeaf",
"oWorld",
"oBodyDef",
"oBody",
"oSensor",
"oUnitDef",
"oUnit",
"oBulletDef",
"oBullet",
"oPlatformWorld",
"oCamera",
"oJoint",
"oMoveJoint",
"oMotorJoint",
}
_ccobject_types = {}

-- register CCObject types
for i = 1, #ccobjects do
    _push_functions[ccobjects[i]] = "tolua_push_ccobject"
	_collect_functions[ccobjects[i]] = "tolua_collect_ccobject"
	_ccobject_types[ccobjects[i]] = true
end

local toWrite = {}
local currentString = ''
local out
local WRITE, OUTPUT = write, output

function output(s)
    out = _OUTPUT
    output = OUTPUT -- restore
    output(s)
end

function write(a)
    if out == _OUTPUT then
        currentString = currentString .. a
        if string.sub(currentString,-1) == '\n'  then
            toWrite[#toWrite+1] = currentString
            currentString = ''
        end
    else
        WRITE(a)
    end
end

function post_output_hook(package)
    local result = table.concat(toWrite)
    local function replace(pattern, replacement)
        local k = 0
        local nxt, currentString = 1, ''
        repeat
            local s, e = string.find(result, pattern, nxt, true)
            if e then
                currentString = currentString .. string.sub(result, nxt, s-1) .. replacement
                nxt = e + 1
                k = k + 1
            end
        until not e
        result = currentString..string.sub(result, nxt)
        if k == 0 then print('Pattern not replaced', pattern) end
    end

    replace([[#include "string.h"
#include "tolua++.h"]],
      [[/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
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
 ****************************************************************************/]])

	replace([[/* Exported function */
TOLUA_API int  tolua_Cocos2d_open (lua_State* tolua_S);]], [[]])

    WRITE(result)
end

function get_property_methods_hook(ptype, name)
	--tolua_property__common
	if ptype == "common" then
		local newName = string.upper(string.sub(name,1,1))..string.sub(name,2,string.len(name))
		return "get"..newName, "set"..newName
	end
	--tolua_property__bool
	if ptype == "bool" then
		--local temp = string.sub(name,3,string.len(name)-2)
		--local newName = string.upper(string.sub(str1,1,1))..string.sub(str1,2,string.len(str1)-1)
		local newName = string.upper(string.sub(name,1,1))..string.sub(name,2,string.len(name))
		return "is"..newName, "set"..newName
	end
	-- etc
end