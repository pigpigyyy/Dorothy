-- usage: (use instead of ant)
-- tolua++ "-L" "basic.lua" "-o" "../../scripting/lua/cocos2dx_support/LuaCocos2d.cpp" "Cocos2d.pkg"

_is_functions = _is_functions or {}
_to_functions = _to_functions or {}
_push_functions = _push_functions or {}
_collect_functions = _collect_functions or {}
local CCObjectTypes = {
    "CCObject",
    "CCAction",
    "CCImage",
    "CCFiniteTimeAction",
    "CCActionInstant",
    "CCCallFunc",
    "CCCallFuncN",
    "CCFlipX",
    "CCFlipY",
    "CCHide",
    "CCPlace",
    "CCReuseGrid",
    "CCShow",
    "CCStopGrid",
    "CCToggleVisibility",
    "CCActionInterval",
    "CCAccelAmplitude",
    "CCAccelDeccelAmplitude",
    "CCActionCamera",
    "CCOrbitCamera",
    "CCCardinalSplineTo",
    "CCCardinalSplineBy",
    "CCCatmullRomTo",
    "CCCatmullRomBy",
    "CCActionEase",
    "CCEaseBackIn",
    "CCEaseBackInOut",
    "CCEaseBackOut",
    "CCEaseBounce",
    "CCEaseElastic",
    "CCEaseExponentialIn",
    "CCEaseExponentialInOut",
    "CCEaseExponentialOut",
    "CCEaseRateAction",
    "CCEaseSineIn",
    "CCEaseSineInOut",
    "CCEaseSineOut",
    "CCAnimate",
    "CCBezierBy",
    "CCBezierTo",
    "CCBlink",
    "CCDeccelAmplitude",
    "CCDelayTime",
    "CCFadeIn",
    "CCFadeOut",
    "CCFadeTo",
    "CCGridAction",
    "CCJumpBy",
    "CCJumpTo",
    "CCMoveTo",
    "CCMoveBy",
    "CCProgressFromTo",
    "CCProgressTo",
    "CCRepeat",
    "CCRepeatForever",
    "CCReverseTime",
    "CCRotateBy",
    "CCRotateTo",
    "CCScaleTo",
    "CCScaleBy",
    "CCSequence",
    "CCSkewTo",
    "CCSkewBy",
    "CCSpawn",
    "CCTintBy",
    "CCTintTo",
    "CCActionManager",
    "CCAnimation",
    "CCAnimationCache",
    "CCArray",
    "CCAsyncObject",
    "CCAutoreleasePool",
    "CCBMFontConfiguration",
    "CCCamera",
    "CCConfiguration",
    "CCData",
    "CCDisplayLinkDirector",
    "CCEvent",
    "CCGrabber",
    "CCGrid3D",
    "CCTiledGrid3D",
    "CCKeypadDispatcher",
    "CCKeypadHandler",
    "CCNode",
	"CCDrawNode",
    "CCAtlasNode",
    "CCLabelAtlas",
    "CCTileMapAtlas",
    "CCLayer",
    "CCLayerColor",
    "CCLayerGradient",
    "CCLayerMultiplex",
    "CCMenu",
    "CCMenuItem",
    "CCMenuItemLabel",
    "CCMenuItemAtlasFont",
    "CCMenuItemFont",
    "CCMenuItemSprite",
    "CCMenuItemImage",
    "CCMenuItemToggle",
    "CCMotionStreak",
    "CCParallaxNode",
    "CCParticleSystem",
    "CCParticleBatchNode",
    "CCParticleSystemQuad",
    "CCProgressTimer",
    "CCRenderTexture",
    "CCRibbon",
    "CCScene",
    "CCTransitionScene",
    "CCTransitionCrossFade",
    "CCTransitionFade",
    "CCTransitionFadeTR",
    "CCTransitionFadeBL",
    "CCTransitionFadeDown",
    "CCTransitionFadeUp",
    "CCTransitionJumpZoom",
    "CCTransitionMoveInL",
    "CCTransitionMoveInB",
    "CCTransitionMoveInR",
    "CCTransitionMoveInT",
    "CCTransitionPageTurn",
    "CCTransitionRotoZoom",
    "CCTransitionSceneOriented",
    "CCTransitionFlipAngular",
    "CCTransitionFlipX",
    "CCTransitionFlipY",
    "CCTransitionZoomFlipAngular",
    "CCTransitionZoomFlipX",
    "CCTransitionZoomFlipY",
    "CCTransitionShrinkGrow",
    "CCTransitionSlideInL",
    "CCTransitionSlideInB",
    "CCTransitionSlideInR",
    "CCTransitionSlideInT",
    "CCTransitionSplitCols",
    "CCTransitionSplitRows",
    "CCTransitionTurnOffTiles",
    "CCTransitionProgress",
    "CCTransitionProgressRadialCCW",
    "CCTransitionProgressRadialCW",
    "CCTransitionProgressHorizontal",
    "CCTransitionProgressVertical",
    "CCTransitionProgressInOut",
    "CCTransitionProgressOutIn",
    "CCSprite",
    "CCLabelTTF",
    "CCTextFieldTTF",
    "CCSpriteBatchNode",
    "CCLabelBMFont",
    "CCTMXLayer",
    "CCTMXTiledMap",
    "CCPointObject",
    "CCProjectionProtocol",
    "CCRibbonSegment",
    "CCScheduler",
    "CCSet",
    "CCSpriteFrame",
    "CCSpriteFrameCache",
    "CCString",
    "CCTexture2D",
    "CCTexturePVR",
    "CCTimer",
    "CCTMXLayerInfo",
    "CCTMXMapInfo",
    "CCTMXObjectGroup",
    "CCTMXTilesetInfo",
    "CCTouch",
    "CCTouchDispatcher",
    "CCTouchHandler",
    "CCParticleFire",
    "CCParticleFireworks",
    "CCParticleSun",
    "CCParticleGalaxy",
    "CCParticleFlower",
    "CCParticleMeteor",
    "CCParticleSpiral",
    "CCParticleExplosion",
    "CCParticleSmoke",
    "CCParticleSnow",
    "CCParticleRain",
	
	"oModelDef",
	"oModel",
	"oKeyPos",
	"oKeyScale",
	"oKeyRotate",
	"oKeyOpacity",
	"oKeySkew",
	"oKeyRoll",
	"oFrameAction",
	"oFace",
	
	"oNode3D",
	"oEffect",
	
	"oWorld",
	"oSensor",
	"oBodyDef",
	"oBody",
	
	"oCamera",
	"oPlatformWorld",
	"oBulletDef",
	"oBullet",
	"oUnitDef",
	"oUnit",
	"oAILeaf",
}

-- register CCObject types
for i = 1, #CCObjectTypes do
    _push_functions[CCObjectTypes[i]] = "toluafix_pushusertype_ccobject"
	_collect_functions[CCObjectTypes[i]] = "tolua_collect_ccobject"
end

-- register LUA_FUNCTION, LUA_TABLE, LUA_HANDLE type
_to_functions["LUA_FUNCTION"] = "toluafix_ref_function"
_is_functions["LUA_FUNCTION"] = "toluafix_isfunction"
_to_functions["LUA_TABLE"] = "toluafix_totable"
_is_functions["LUA_TABLE"] = "toluafix_istable"

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

	replace([[*((LUA_FUNCTION*)]], [[(]])

	replace([[unsigned void* tolua_ret = (unsigned void*)  self->getTiles();]],
        [[unsigned int* tolua_ret = (unsigned int*)  self->getTiles();]])

	replace([[ccColor3B color = *((ccColor3B*)  tolua_tousertype(tolua_S,4,(void*)&(const ccColor3B)ccBLACK));]],
        [[const ccColor3B clr = ccBLACK;
	ccColor3B color = *((ccColor3B*)  tolua_tousertype(tolua_S,4,(void*)&clr));]])

	replace([[tolua_usertype(tolua_S,"LUA_FUNCTION");]], [[]])

	replace([[toluafix_pushusertype_ccobject(tolua_S,(void*)tolua_ret]],
        [[toluafix_pushusertype_ccobject(tolua_S, tolua_ret->getObjectId(), &tolua_ret->m_nLuaRef, (void*)tolua_ret]])
	
	replace([[toluafix_pushusertype_ccobject(tolua_S,(void*)]],
		[[TOLUAFIX_PUSHUSERTYPE_CCOBJECT(tolua_S,]])
    
	replace([[tolua_beginmodule(tolua_S,"oSensor");]],
	[[tolua_beginmodule(tolua_S,"oSensor");
    tolua_constant(tolua_S,"Enter",0);
    tolua_constant(tolua_S,"Leave",1);]])
	
	replace([[unsigned int]], [[uint32]])
	
	replace([[unsigned char]], [[uint8]])

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