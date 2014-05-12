/*
** Lua binding: Cocos2d
** Generated automatically by tolua++-1.0.92 on 05/12/14 17:14:17.
*/

/****************************************************************************
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
 ****************************************************************************/



#include "LuaCocos2d.h"

/* function to release collected object via destructor */

static int tolua_collect_CCSize (lua_State* tolua_S)
{
 CCSize* self = (CCSize*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_ccColor3B (lua_State* tolua_S)
{
 ccColor3B* self = (ccColor3B*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_ccColor4B (lua_State* tolua_S)
{
 ccColor4B* self = (ccColor4B*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_ccBlendFunc (lua_State* tolua_S)
{
 ccBlendFunc* self = (ccBlendFunc*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_oVec2 (lua_State* tolua_S)
{
 oVec2* self = (oVec2*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CCRect (lua_State* tolua_S)
{
 CCRect* self = (CCRect*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

/* function to register type */
static void tolua_reg_types(lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CCTileMapAtlas");
 Mtolua_typeid(CCTileMapAtlas,"CCTileMapAtlas");
 tolua_usertype(tolua_S,"CCParallaxNode");
 Mtolua_typeid(CCParallaxNode,"CCParallaxNode");
 tolua_usertype(tolua_S,"CCFiniteTimeAction");
 Mtolua_typeid(CCFiniteTimeAction,"CCFiniteTimeAction");
 tolua_usertype(tolua_S,"CCMotionStreak");
 Mtolua_typeid(CCMotionStreak,"CCMotionStreak");
 tolua_usertype(tolua_S,"Clip");
 Mtolua_typeid(oClipCache,"Clip");
 tolua_usertype(tolua_S,"oNode3D");
 Mtolua_typeid(oNode3D,"oNode3D");
 tolua_usertype(tolua_S,"CCSpriteBatchNode");
 Mtolua_typeid(CCSpriteBatchNode,"CCSpriteBatchNode");
 tolua_usertype(tolua_S,"oUnitDef");
 Mtolua_typeid(oUnitDef,"oUnitDef");
 tolua_usertype(tolua_S,"Particle");
 Mtolua_typeid(oParticleCache,"Particle");
 tolua_usertype(tolua_S,"ccColor3");
 Mtolua_typeid(ccColor3B,"ccColor3");
 tolua_usertype(tolua_S,"CCDrawNode");
 Mtolua_typeid(CCDrawNode,"CCDrawNode");
 tolua_usertype(tolua_S,"CCTextureCache");
 Mtolua_typeid(CCTextureCache,"CCTextureCache");
 tolua_usertype(tolua_S,"oModel");
 Mtolua_typeid(oModel,"oModel");
 tolua_usertype(tolua_S,"oListener");
 Mtolua_typeid(oListener,"oListener");
 tolua_usertype(tolua_S,"CCClipNode");
 Mtolua_typeid(CCClippingNode,"CCClipNode");
 tolua_usertype(tolua_S,"oLine");
 Mtolua_typeid(oLine,"oLine");
 tolua_usertype(tolua_S,"CCTMXLayer");
 Mtolua_typeid(CCTMXLayer,"CCTMXLayer");
 tolua_usertype(tolua_S,"oWorld");
 Mtolua_typeid(oWorld,"oWorld");
 tolua_usertype(tolua_S,"CCView");
 Mtolua_typeid(CCEGLView,"CCView");
 tolua_usertype(tolua_S,"Model");
 Mtolua_typeid(oModelCache,"Model");
 tolua_usertype(tolua_S,"oBulletDef");
 Mtolua_typeid(oBulletDef,"oBulletDef");
 tolua_usertype(tolua_S,"oLayer");
 Mtolua_typeid(oLayer,"oLayer");
 tolua_usertype(tolua_S,"CCLabelTTF");
 Mtolua_typeid(CCLabelTTF,"CCLabelTTF");
 tolua_usertype(tolua_S,"ccBlendFunc");
 Mtolua_typeid(ccBlendFunc,"ccBlendFunc");
 tolua_usertype(tolua_S,"CCImage");
 Mtolua_typeid(CCImage,"CCImage");
 tolua_usertype(tolua_S,"CCSprite");
 Mtolua_typeid(CCSprite,"CCSprite");
 tolua_usertype(tolua_S,"oMusic");
 Mtolua_typeid(oMusic,"oMusic");
 tolua_usertype(tolua_S,"CCFileUtils");
 Mtolua_typeid(CCFileUtils,"CCFileUtils");
 tolua_usertype(tolua_S,"CCLayerGradient");
 Mtolua_typeid(CCLayerGradient,"CCLayerGradient");
 tolua_usertype(tolua_S,"CCTouch");
 Mtolua_typeid(CCTouch,"CCTouch");
 tolua_usertype(tolua_S,"oData");
 Mtolua_typeid(oData,"oData");
 tolua_usertype(tolua_S,"CCMenu");
 Mtolua_typeid(CCMenu,"CCMenu");
 tolua_usertype(tolua_S,"oAction");
 Mtolua_typeid(oAction,"oAction");
 tolua_usertype(tolua_S,"oFace");
 Mtolua_typeid(oFace,"oFace");
 tolua_usertype(tolua_S,"oFrameAction");
 Mtolua_typeid(oFrameAction,"oFrameAction");
 tolua_usertype(tolua_S,"CCUserDefault");
 Mtolua_typeid(CCUserDefault,"CCUserDefault");
 tolua_usertype(tolua_S,"CCProgressTimer");
 Mtolua_typeid(CCProgressTimer,"CCProgressTimer");
 tolua_usertype(tolua_S,"oAI");
 Mtolua_typeid(oAI,"oAI");
 tolua_usertype(tolua_S,"oEffect");
 Mtolua_typeid(oEffect,"oEffect");
 tolua_usertype(tolua_S,"CCLayerColor");
 Mtolua_typeid(CCLayerColor,"CCLayerColor");
 tolua_usertype(tolua_S,"oContent");
 Mtolua_typeid(oContent,"oContent");
 tolua_usertype(tolua_S,"CCLabelAtlas");
 Mtolua_typeid(CCLabelAtlas,"CCLabelAtlas");
 tolua_usertype(tolua_S,"CCActionInterval");
 Mtolua_typeid(CCActionInterval,"CCActionInterval");
 tolua_usertype(tolua_S,"oInstinct");
 Mtolua_typeid(oInstinct,"oInstinct");
 tolua_usertype(tolua_S,"CCRenderTarget");
 Mtolua_typeid(CCRenderTexture,"CCRenderTarget");
 tolua_usertype(tolua_S,"CCObject");
 Mtolua_typeid(CCObject,"CCObject");
 tolua_usertype(tolua_S,"oAILeaf");
 Mtolua_typeid(oAILeaf,"oAILeaf");
 tolua_usertype(tolua_S,"oUnit");
 Mtolua_typeid(oUnit,"oUnit");
 tolua_usertype(tolua_S,"oCamera");
 Mtolua_typeid(oCamera,"oCamera");
 tolua_usertype(tolua_S,"oBullet");
 Mtolua_typeid(oBullet,"oBullet");
 tolua_usertype(tolua_S,"oTargetAllow");
 Mtolua_typeid(oTargetAllow,"oTargetAllow");
 tolua_usertype(tolua_S,"oSound");
 Mtolua_typeid(oSound,"oSound");
 tolua_usertype(tolua_S,"CCRect");
 Mtolua_typeid(CCRect,"CCRect");
 tolua_usertype(tolua_S,"oEase");
 Mtolua_typeid(oEase,"oEase");
 tolua_usertype(tolua_S,"oSensor");
 Mtolua_typeid(oSensor,"oSensor");
 tolua_usertype(tolua_S,"CCTexture2D");
 Mtolua_typeid(CCTexture2D,"CCTexture2D");
 tolua_usertype(tolua_S,"CCLayer");
 Mtolua_typeid(CCLayer,"CCLayer");
 tolua_usertype(tolua_S,"oPlatformWorld");
 Mtolua_typeid(oPlatformWorld,"oPlatformWorld");
 tolua_usertype(tolua_S,"CCSize");
 Mtolua_typeid(CCSize,"CCSize");
 tolua_usertype(tolua_S,"CCMenuItem");
 Mtolua_typeid(CCMenuItem,"CCMenuItem");
 tolua_usertype(tolua_S,"ccColor4");
 Mtolua_typeid(ccColor4B,"ccColor4");
 tolua_usertype(tolua_S,"CCDirector");
 Mtolua_typeid(CCDirector,"CCDirector");
 tolua_usertype(tolua_S,"oFixtureDef");
 Mtolua_typeid(oFixtureDef,"oFixtureDef");
 tolua_usertype(tolua_S,"CCArray");
 Mtolua_typeid(CCArray,"CCArray");
 tolua_usertype(tolua_S,"CCNode");
 Mtolua_typeid(CCNode,"CCNode");
 tolua_usertype(tolua_S,"CCApplication");
 Mtolua_typeid(CCApplication,"CCApplication");
 tolua_usertype(tolua_S,"CCAction");
 Mtolua_typeid(CCAction,"CCAction");
 tolua_usertype(tolua_S,"CCScene");
 Mtolua_typeid(CCScene,"CCScene");
 tolua_usertype(tolua_S,"Effect");
 Mtolua_typeid(oEffectCache,"Effect");
 tolua_usertype(tolua_S,"oEvent");
 Mtolua_typeid(oEvent,"oEvent");
 tolua_usertype(tolua_S,"Animation");
 Mtolua_typeid(oAnimationCache,"Animation");
 tolua_usertype(tolua_S,"CCSpeed");
 Mtolua_typeid(CCSpeed,"CCSpeed");
 tolua_usertype(tolua_S,"CCTextFieldTTF");
 Mtolua_typeid(CCTextFieldTTF,"CCTextFieldTTF");
 tolua_usertype(tolua_S,"oBody");
 Mtolua_typeid(oBody,"oBody");
 tolua_usertype(tolua_S,"oVec2");
 Mtolua_typeid(oVec2,"oVec2");
 tolua_usertype(tolua_S,"CCLabelBMFont");
 Mtolua_typeid(CCLabelBMFont,"CCLabelBMFont");
 tolua_usertype(tolua_S,"CCTMXTiledMap");
 Mtolua_typeid(CCTMXTiledMap,"CCTMXTiledMap");
 tolua_usertype(tolua_S,"CCScheduler");
 Mtolua_typeid(CCScheduler,"CCScheduler");
 tolua_usertype(tolua_S,"oBodyDef");
 Mtolua_typeid(oBodyDef,"oBodyDef");
}

/* method: new_local of class  ccColor3B */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ccColor3_new00_local
static int tolua_Cocos2d_ccColor3_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ccColor3",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ccColor3B* tolua_ret = (ccColor3B*)  Mtolua_new((ccColor3B)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ccColor3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ccColor3B */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ccColor3_new01_local
static int tolua_Cocos2d_ccColor3_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ccColor3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned int value = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   ccColor3B* tolua_ret = (ccColor3B*)  Mtolua_new((ccColor3B)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ccColor3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_ccColor3_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ccColor3B */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ccColor3_new02_local
static int tolua_Cocos2d_ccColor3_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ccColor3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned char r = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char g = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
  unsigned char b = (( unsigned char)  tolua_tonumber(tolua_S,4,0));
  {
   ccColor3B* tolua_ret = (ccColor3B*)  Mtolua_new((ccColor3B)(r,g,b));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ccColor3");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_ccColor3_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: r of class  ccColor3B */
#ifndef TOLUA_DISABLE_tolua_get_ccColor3B_unsigned_r
static int tolua_get_ccColor3B_unsigned_r(lua_State* tolua_S)
{
  ccColor3B* self = (ccColor3B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'r'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->r);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: r of class  ccColor3B */
#ifndef TOLUA_DISABLE_tolua_set_ccColor3B_unsigned_r
static int tolua_set_ccColor3B_unsigned_r(lua_State* tolua_S)
{
  ccColor3B* self = (ccColor3B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'r'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->r = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: g of class  ccColor3B */
#ifndef TOLUA_DISABLE_tolua_get_ccColor3B_unsigned_g
static int tolua_get_ccColor3B_unsigned_g(lua_State* tolua_S)
{
  ccColor3B* self = (ccColor3B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'g'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->g);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: g of class  ccColor3B */
#ifndef TOLUA_DISABLE_tolua_set_ccColor3B_unsigned_g
static int tolua_set_ccColor3B_unsigned_g(lua_State* tolua_S)
{
  ccColor3B* self = (ccColor3B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'g'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->g = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: b of class  ccColor3B */
#ifndef TOLUA_DISABLE_tolua_get_ccColor3B_unsigned_b
static int tolua_get_ccColor3B_unsigned_b(lua_State* tolua_S)
{
  ccColor3B* self = (ccColor3B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->b);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: b of class  ccColor3B */
#ifndef TOLUA_DISABLE_tolua_set_ccColor3B_unsigned_b
static int tolua_set_ccColor3B_unsigned_b(lua_State* tolua_S)
{
  ccColor3B* self = (ccColor3B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->b = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ccColor4_new00_local
static int tolua_Cocos2d_ccColor4_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ccColor4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ccColor4B* tolua_ret = (ccColor4B*)  Mtolua_new((ccColor4B)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ccColor4");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ccColor4_new01_local
static int tolua_Cocos2d_ccColor4_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ccColor4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned int value = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   ccColor4B* tolua_ret = (ccColor4B*)  Mtolua_new((ccColor4B)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ccColor4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_ccColor4_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ccColor4_new02_local
static int tolua_Cocos2d_ccColor4_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ccColor4",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor3",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ccColor3B c = *((ccColor3B*)  tolua_tousertype(tolua_S,2,0));
  unsigned char a = (( unsigned char)  tolua_tonumber(tolua_S,3,255));
  {
   ccColor4B* tolua_ret = (ccColor4B*)  Mtolua_new((ccColor4B)(c,a));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ccColor4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_ccColor4_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ccColor4_new03_local
static int tolua_Cocos2d_ccColor4_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ccColor4",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned char r = (( unsigned char)  tolua_tonumber(tolua_S,2,0));
  unsigned char g = (( unsigned char)  tolua_tonumber(tolua_S,3,0));
  unsigned char b = (( unsigned char)  tolua_tonumber(tolua_S,4,0));
  unsigned char a = (( unsigned char)  tolua_tonumber(tolua_S,5,0));
  {
   ccColor4B* tolua_ret = (ccColor4B*)  Mtolua_new((ccColor4B)(r,g,b,a));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ccColor4");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_ccColor4_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: r of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_get_ccColor4B_unsigned_r
static int tolua_get_ccColor4B_unsigned_r(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'r'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->r);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: r of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_set_ccColor4B_unsigned_r
static int tolua_set_ccColor4B_unsigned_r(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'r'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->r = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: g of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_get_ccColor4B_unsigned_g
static int tolua_get_ccColor4B_unsigned_g(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'g'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->g);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: g of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_set_ccColor4B_unsigned_g
static int tolua_set_ccColor4B_unsigned_g(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'g'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->g = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: b of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_get_ccColor4B_unsigned_b
static int tolua_get_ccColor4B_unsigned_b(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->b);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: b of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_set_ccColor4B_unsigned_b
static int tolua_set_ccColor4B_unsigned_b(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->b = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: a of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_get_ccColor4B_unsigned_a
static int tolua_get_ccColor4B_unsigned_a(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'a'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->a);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: a of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_set_ccColor4B_unsigned_a
static int tolua_set_ccColor4B_unsigned_a(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'a'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->a = (( unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ccBlendFunc */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ccBlendFunc_new00_local
static int tolua_Cocos2d_ccBlendFunc_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ccBlendFunc",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ccBlendFunc* tolua_ret = (ccBlendFunc*)  Mtolua_new((ccBlendFunc)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ccBlendFunc");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ccBlendFunc */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ccBlendFunc_new01_local
static int tolua_Cocos2d_ccBlendFunc_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ccBlendFunc",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned int src = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int dst = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   tolua_outside ccBlendFunc* tolua_ret = (tolua_outside ccBlendFunc*)  ccBlendFuncNew(src,dst);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ccBlendFunc");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_ccBlendFunc_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: src of class  ccBlendFunc */
#ifndef TOLUA_DISABLE_tolua_get_ccBlendFunc_unsigned_src
static int tolua_get_ccBlendFunc_unsigned_src(lua_State* tolua_S)
{
  ccBlendFunc* self = (ccBlendFunc*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'src'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->src);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: src of class  ccBlendFunc */
#ifndef TOLUA_DISABLE_tolua_set_ccBlendFunc_unsigned_src
static int tolua_set_ccBlendFunc_unsigned_src(lua_State* tolua_S)
{
  ccBlendFunc* self = (ccBlendFunc*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'src'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->src = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dst of class  ccBlendFunc */
#ifndef TOLUA_DISABLE_tolua_get_ccBlendFunc_unsigned_dst
static int tolua_get_ccBlendFunc_unsigned_dst(lua_State* tolua_S)
{
  ccBlendFunc* self = (ccBlendFunc*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dst'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->dst);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dst of class  ccBlendFunc */
#ifndef TOLUA_DISABLE_tolua_set_ccBlendFunc_unsigned_dst
static int tolua_set_ccBlendFunc_unsigned_dst(lua_State* tolua_S)
{
  ccBlendFunc* self = (ccBlendFunc*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dst'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dst = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: objectId of class  CCObject */
#ifndef TOLUA_DISABLE_tolua_get_CCObject_id
static int tolua_get_CCObject_id(lua_State* tolua_S)
{
  CCObject* self = (CCObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'objectId'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getObjectId());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: objectCount of class  CCObject */
#ifndef TOLUA_DISABLE_tolua_get_CCObject_unsigned_count
static int tolua_get_CCObject_unsigned_count(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)CCObject::getObjectCount());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: luaRefCount of class  CCObject */
#ifndef TOLUA_DISABLE_tolua_get_CCObject_unsigned_luaRefCount
static int tolua_get_CCObject_unsigned_luaRefCount(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)CCObject::getLuaRefCount());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: toluafix_get_callback_ref_count */
#ifndef TOLUA_DISABLE_tolua_get_CCObject_callRefCount
static int tolua_get_CCObject_callRefCount(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)toluafix_get_callback_ref_count());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCLuaLog */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLuaLog00
static int tolua_Cocos2d_CCLuaLog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* pszFormat = ((char*)  tolua_tostring(tolua_S,1,0));
  {
   CCLuaLog(pszFormat);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCLuaLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCMessageBox */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCMessageBox00
static int tolua_Cocos2d_CCMessageBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* pszMsg = ((char*)  tolua_tostring(tolua_S,1,0));
  char* pszTitle = ((char*)  tolua_tostring(tolua_S,2,0));
  {
   CCMessageBox(pszMsg,pszTitle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCMessageBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCSize */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCSize_new00_local
static int tolua_Cocos2d_CCSize_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSize",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCSize* tolua_ret = (CCSize*)  Mtolua_new((CCSize)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCSize */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCSize_new01_local
static int tolua_Cocos2d_CCSize_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSize",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CCSize* tolua_ret = (CCSize*)  Mtolua_new((CCSize)(width,height));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSize");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCSize_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: width of class  CCSize */
#ifndef TOLUA_DISABLE_tolua_get_CCSize_width
static int tolua_get_CCSize_width(lua_State* tolua_S)
{
  CCSize* self = (CCSize*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'width'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->width);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: width of class  CCSize */
#ifndef TOLUA_DISABLE_tolua_set_CCSize_width
static int tolua_set_CCSize_width(lua_State* tolua_S)
{
  CCSize* self = (CCSize*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'width'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->width = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: height of class  CCSize */
#ifndef TOLUA_DISABLE_tolua_get_CCSize_height
static int tolua_get_CCSize_height(lua_State* tolua_S)
{
  CCSize* self = (CCSize*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'height'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->height);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: height of class  CCSize */
#ifndef TOLUA_DISABLE_tolua_set_CCSize_height
static int tolua_set_CCSize_height(lua_State* tolua_S)
{
  CCSize* self = (CCSize*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'height'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->height = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CCSize */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCSize__eq00
static int tolua_Cocos2d_CCSize__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSize",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSize* self = (CCSize*)  tolua_tousertype(tolua_S,1,0);
  CCSize* target = ((CCSize*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*target);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: zero of class  CCSize */
#ifndef TOLUA_DISABLE_tolua_get_CCSize_zero
static int tolua_get_CCSize_zero(lua_State* tolua_S)
{
    void* tolua_obj = Mtolua_new((CCSize)(CCSize::zero));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCRect_new00_local
static int tolua_Cocos2d_CCRect_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCRect* tolua_ret = (CCRect*)  Mtolua_new((CCRect)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCRect_new01_local
static int tolua_Cocos2d_CCRect_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  oVec2* origin = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
  CCSize* size = ((CCSize*)  tolua_tousertype(tolua_S,3,0));
  {
   CCRect* tolua_ret = (CCRect*)  Mtolua_new((CCRect)(*origin,*size));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCRect");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCRect_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCRect_new02_local
static int tolua_Cocos2d_CCRect_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float width = ((float)  tolua_tonumber(tolua_S,4,0));
  float height = ((float)  tolua_tonumber(tolua_S,5,0));
  {
   CCRect* tolua_ret = (CCRect*)  Mtolua_new((CCRect)(x,y,width,height));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCRect");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCRect_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: origin of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_get_CCRect_origin
static int tolua_get_CCRect_origin(lua_State* tolua_S)
{
  CCRect* self = (CCRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'origin'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->origin));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: origin of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_set_CCRect_origin
static int tolua_set_CCRect_origin(lua_State* tolua_S)
{
  CCRect* self = (CCRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'origin'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->origin = *((oVec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: size of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_get_CCRect_size
static int tolua_get_CCRect_size(lua_State* tolua_S)
{
  CCRect* self = (CCRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->size));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: size of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_set_CCRect_size
static int tolua_set_CCRect_size(lua_State* tolua_S)
{
  CCRect* self = (CCRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->size = *((CCSize*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: minX of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_get_CCRect_left
static int tolua_get_CCRect_left(lua_State* tolua_S)
{
  CCRect* self = (CCRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'minX'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getMinX());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxX of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_get_CCRect_right
static int tolua_get_CCRect_right(lua_State* tolua_S)
{
  CCRect* self = (CCRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxX'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getMaxX());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: minY of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_get_CCRect_bottom
static int tolua_get_CCRect_bottom(lua_State* tolua_S)
{
  CCRect* self = (CCRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'minY'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getMinY());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxY of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_get_CCRect_up
static int tolua_get_CCRect_up(lua_State* tolua_S)
{
  CCRect* self = (CCRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxY'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getMaxY());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: midX of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_get_CCRect_midX
static int tolua_get_CCRect_midX(lua_State* tolua_S)
{
  CCRect* self = (CCRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'midX'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getMidX());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: midY of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_get_CCRect_midY
static int tolua_get_CCRect_midY(lua_State* tolua_S)
{
  CCRect* self = (CCRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'midY'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getMidY());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCRect__eq00
static int tolua_Cocos2d_CCRect__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRect* self = (CCRect*)  tolua_tousertype(tolua_S,1,0);
  CCRect* rect = ((CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rect);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: containsPoint of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCRect_containsPoint00
static int tolua_Cocos2d_CCRect_containsPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRect* self = (CCRect*)  tolua_tousertype(tolua_S,1,0);
  oVec2* point = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'containsPoint'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->containsPoint(*point);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'containsPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: intersectsRect of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCRect_intersectsRect00
static int tolua_Cocos2d_CCRect_intersectsRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRect* self = (CCRect*)  tolua_tousertype(tolua_S,1,0);
  CCRect* rect = ((CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intersectsRect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->intersectsRect(*rect);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'intersectsRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: zero of class  CCRect */
#ifndef TOLUA_DISABLE_tolua_get_CCRect_zero
static int tolua_get_CCRect_zero(lua_State* tolua_S)
{
    void* tolua_obj = Mtolua_new((CCRect)(CCRect::zero));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_new00_local
static int tolua_Cocos2d_CCArray_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCArray* tolua_ret = (CCArray*)  CCArray::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_new01_local
static int tolua_Cocos2d_CCArray_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCArray* otherArray = ((CCArray*)  tolua_tousertype(tolua_S,2,0));
  {
   CCArray* tolua_ret = (CCArray*)  CCArray::createWithArray(otherArray);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCArray");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCArray_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_new02_local
static int tolua_Cocos2d_CCArray_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned int capacity = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   CCArray* tolua_ret = (CCArray*)  CCArray::createWithCapacity(capacity);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCArray");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCArray_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_new03_local
static int tolua_Cocos2d_CCArray_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int tolua_len = lua_objlen(tolua_S,2);
  CCObject** objects = Mtolua_new_dim(CCObject*, tolua_len);
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,2,"CCObject",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    objects[i] = ((CCObject*)  tolua_tofieldusertype(tolua_S,2,i+1,0));
   }
  }
  {
   tolua_outside CCArray* tolua_ret = (tolua_outside CCArray*)  CCArray_create(objects,tolua_len);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCArray");
  }
  Mtolua_delete_dim(objects);
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCArray_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: count of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_get_CCArray_unsigned_count
static int tolua_get_CCArray_unsigned_count(lua_State* tolua_S)
{
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'count'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->count());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: capacity of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_get_CCArray_unsigned_capacity
static int tolua_get_CCArray_unsigned_capacity(lua_State* tolua_S)
{
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'capacity'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->capacity());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: lastObject of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_get_CCArray_last_ptr
static int tolua_get_CCArray_last_ptr(lua_State* tolua_S)
{
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lastObject'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->lastObject(),"CCObject");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: randomObject of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_get_CCArray_randomObject_ptr
static int tolua_get_CCArray_randomObject_ptr(lua_State* tolua_S)
{
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'randomObject'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->randomObject(),"CCObject");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: isEqualToArray of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_equals00
static int tolua_Cocos2d_CCArray_equals00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
  CCArray* pOtherArray = ((CCArray*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEqualToArray'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEqualToArray(pOtherArray);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'equals'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: containsObject of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_contains00
static int tolua_Cocos2d_CCArray_contains00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
  CCObject* object = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'containsObject'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->containsObject(object);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'contains'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addObject of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_add00
static int tolua_Cocos2d_CCArray_add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
  CCObject* object = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addObject'", NULL);
#endif
  {
   self->addObject(object);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addObjectsFromArray of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_join00
static int tolua_Cocos2d_CCArray_join00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
  CCArray* otherArray = ((CCArray*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addObjectsFromArray'", NULL);
#endif
  {
   self->addObjectsFromArray(otherArray);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'join'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeLastObject of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_removeLast00
static int tolua_Cocos2d_CCArray_removeLast00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeLastObject'", NULL);
#endif
  {
   self->removeLastObject();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeLast'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeObject of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_remove00
static int tolua_Cocos2d_CCArray_remove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
  CCObject* object = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeObject'", NULL);
#endif
  {
   self->removeObject(object);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'remove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeObjectsInArray of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_removeFrom00
static int tolua_Cocos2d_CCArray_removeFrom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
  CCArray* otherArray = ((CCArray*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeObjectsInArray'", NULL);
#endif
  {
   self->removeObjectsInArray(otherArray);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeFrom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllObjects of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_clear00
static int tolua_Cocos2d_CCArray_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllObjects'", NULL);
#endif
  {
   self->removeAllObjects();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: fastRemoveObject of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_fastRemove00
static int tolua_Cocos2d_CCArray_fastRemove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
  CCObject* object = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fastRemoveObject'", NULL);
#endif
  {
   self->fastRemoveObject(object);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fastRemove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: exchangeObject of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_swap00
static int tolua_Cocos2d_CCArray_swap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
  CCObject* object1 = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  CCObject* object2 = ((CCObject*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'exchangeObject'", NULL);
#endif
  {
   self->exchangeObject(object1,object2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'swap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reverseObjects of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_reverse00
static int tolua_Cocos2d_CCArray_reverse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reverseObjects'", NULL);
#endif
  {
   self->reverseObjects();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reverse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reduceMemoryFootprint of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_shrink00
static int tolua_Cocos2d_CCArray_shrink00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reduceMemoryFootprint'", NULL);
#endif
  {
   self->reduceMemoryFootprint();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'shrink'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCArray_index of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_index00
static int tolua_Cocos2d_CCArray_index00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
  CCObject* object = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CCArray_index'", NULL);
#endif
  {
   tolua_outside unsigned int tolua_ret = (tolua_outside unsigned int)  CCArray_index(self,object);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'index'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CArray_get of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_get00
static int tolua_Cocos2d_CCArray_get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
  unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CArray_get'", NULL);
#endif
  {
   tolua_outside CCObject* tolua_ret = (tolua_outside CCObject*)  CArray_get(self,index);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CArray_insert of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_insert00
static int tolua_Cocos2d_CCArray_insert00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
  CCObject* object = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CArray_insert'", NULL);
#endif
  {
   CArray_insert(self,object,index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'insert'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CArray_removeAt of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_removeAt00
static int tolua_Cocos2d_CCArray_removeAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
  unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CArray_removeAt'", NULL);
#endif
  {
   CArray_removeAt(self,index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CArray_exchange of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_exchange00
static int tolua_Cocos2d_CCArray_exchange00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
  unsigned int index1 = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int index2 = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CArray_exchange'", NULL);
#endif
  {
   CArray_exchange(self,index1,index2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'exchange'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CArray_fastRemoveAt of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_fastRemoveAt00
static int tolua_Cocos2d_CCArray_fastRemoveAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
  unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CArray_fastRemoveAt'", NULL);
#endif
  {
   CArray_fastRemoveAt(self,index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fastRemoveAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CArray_set of class  CCArray */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCArray_set00
static int tolua_Cocos2d_CCArray_set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* self = (CCArray*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uIndex = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  CCObject* pObject = ((CCObject*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CArray_set'", NULL);
#endif
  {
   CArray_set(self,uIndex,pObject);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: visibleSize of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_get_CCEGLView_visibleSize
static int tolua_get_CCEGLView_visibleSize(lua_State* tolua_S)
{
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'visibleSize'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->getVisibleSize()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: visibleOrigin of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_get_CCEGLView_visibleOrigin
static int tolua_get_CCEGLView_visibleOrigin(lua_State* tolua_S)
{
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'visibleOrigin'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getVisibleOrigin()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scaleX of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_get_CCEGLView_scaleX
static int tolua_get_CCEGLView_scaleX(lua_State* tolua_S)
{
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scaleX'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getScaleX());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scaleY of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_get_CCEGLView_scaleY
static int tolua_get_CCEGLView_scaleY(lua_State* tolua_S)
{
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scaleY'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getScaleY());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: designResolutionSize of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_get_CCEGLView_designResolutionSize
static int tolua_get_CCEGLView_designResolutionSize(lua_State* tolua_S)
{
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'designResolutionSize'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->getDesignResolutionSize()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: frameSize of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_get_CCEGLView_frameSize
static int tolua_get_CCEGLView_frameSize(lua_State* tolua_S)
{
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'frameSize'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->getFrameSize()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: frameSize of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_set_CCEGLView_frameSize
static int tolua_set_CCEGLView_frameSize(lua_State* tolua_S)
{
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'frameSize'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setFrameSize(*((CCSize*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: viewPortRect of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_get_CCEGLView_viewPort
static int tolua_get_CCEGLView_viewPort(lua_State* tolua_S)
{
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'viewPortRect'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCRect)(self->getViewPortRect()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: viewPortRect of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_set_CCEGLView_viewPort
static int tolua_set_CCEGLView_viewPort(lua_State* tolua_S)
{
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'viewPortRect'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setViewPortRect(*((CCRect*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: viewName of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_get_CCEGLView_viewName
static int tolua_get_CCEGLView_viewName(lua_State* tolua_S)
{
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'viewName'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->getViewName());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: viewName of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_set_CCEGLView_viewName
static int tolua_set_CCEGLView_viewName(lua_State* tolua_S)
{
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'viewName'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setViewName(((char*)  tolua_tostring(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDesignResolutionSize of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCView_setDesignResolution00
static int tolua_Cocos2d_CCView_setDesignResolution00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
  ResolutionPolicy resolutionPolicy = ((ResolutionPolicy) (int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDesignResolutionSize'", NULL);
#endif
  {
   self->setDesignResolutionSize(width,height,resolutionPolicy);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDesignResolution'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScissorInPoints of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCView_setScissorRect00
static int tolua_Cocos2d_CCView_setScissorRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCEGLView* self = (CCEGLView*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float w = ((float)  tolua_tonumber(tolua_S,4,0));
  float h = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScissorInPoints'", NULL);
#endif
  {
   self->setScissorInPoints(x,y,w,h);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScissorRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCEGLView */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCView_new00_local
static int tolua_Cocos2d_CCView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCEGLView* tolua_ret = (CCEGLView*)  CCEGLView::sharedOpenGLView();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: writablePath of class  CCFileUtils */
#ifndef TOLUA_DISABLE_tolua_get_CCFileUtils_writablePath
static int tolua_get_CCFileUtils_writablePath(lua_State* tolua_S)
{
  CCFileUtils* self = (CCFileUtils*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'writablePath'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->getWritablePath());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: popupNotify of class  CCFileUtils */
#ifndef TOLUA_DISABLE_tolua_get_CCFileUtils_popupNotify
static int tolua_get_CCFileUtils_popupNotify(lua_State* tolua_S)
{
  CCFileUtils* self = (CCFileUtils*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'popupNotify'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isPopupNotify());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: popupNotify of class  CCFileUtils */
#ifndef TOLUA_DISABLE_tolua_set_CCFileUtils_popupNotify
static int tolua_set_CCFileUtils_popupNotify(lua_State* tolua_S)
{
  CCFileUtils* self = (CCFileUtils*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'popupNotify'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setPopupNotify(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: fullPathForFilename of class  CCFileUtils */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCFileUtils_getFullPath00
static int tolua_Cocos2d_CCFileUtils_getFullPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFileUtils",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFileUtils* self = (CCFileUtils*)  tolua_tousertype(tolua_S,1,0);
  char* pszFileName = ((char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fullPathForFilename'", NULL);
#endif
  {
   string tolua_ret = (string)  self->fullPathForFilename(pszFileName);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFullPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: fullPathFromRelativeFile of class  CCFileUtils */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCFileUtils_getRelativeFullPath00
static int tolua_Cocos2d_CCFileUtils_getRelativeFullPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFileUtils",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFileUtils* self = (CCFileUtils*)  tolua_tousertype(tolua_S,1,0);
  char* pszFilename = ((char*)  tolua_tostring(tolua_S,2,0));
  char* pszRelativeFile = ((char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fullPathFromRelativeFile'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->fullPathFromRelativeFile(pszFilename,pszRelativeFile);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRelativeFullPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadFilenameLookupDictionaryFromFile of class  CCFileUtils */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCFileUtils_loadFileLookupInfo00
static int tolua_Cocos2d_CCFileUtils_loadFileLookupInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFileUtils",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFileUtils* self = (CCFileUtils*)  tolua_tousertype(tolua_S,1,0);
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadFilenameLookupDictionaryFromFile'", NULL);
#endif
  {
   self->loadFilenameLookupDictionaryFromFile(filename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadFileLookupInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addSearchPath of class  CCFileUtils */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCFileUtils_addSearchPath00
static int tolua_Cocos2d_CCFileUtils_addSearchPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFileUtils",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFileUtils* self = (CCFileUtils*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addSearchPath'", NULL);
#endif
  {
   self->addSearchPath(path);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addSearchPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addSearchResolutionsOrder of class  CCFileUtils */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCFileUtils_addSearchResolutionsOrder00
static int tolua_Cocos2d_CCFileUtils_addSearchResolutionsOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFileUtils",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFileUtils* self = (CCFileUtils*)  tolua_tousertype(tolua_S,1,0);
  const char* order = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addSearchResolutionsOrder'", NULL);
#endif
  {
   self->addSearchResolutionsOrder(order);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addSearchResolutionsOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purgeCachedEntries of class  CCFileUtils */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCFileUtils_purgeCachedEntries00
static int tolua_Cocos2d_CCFileUtils_purgeCachedEntries00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFileUtils",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFileUtils* self = (CCFileUtils*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'purgeCachedEntries'", NULL);
#endif
  {
   self->purgeCachedEntries();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purgeCachedEntries'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCFileUtils */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCFileUtils_new00_local
static int tolua_Cocos2d_CCFileUtils_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCFileUtils",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCFileUtils* tolua_ret = (CCFileUtils*)  CCFileUtils::sharedFileUtils();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCFileUtils");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: currentLanguage of class  CCApplication */
#ifndef TOLUA_DISABLE_tolua_get_CCApplication_currentLanguage
static int tolua_get_CCApplication_currentLanguage(lua_State* tolua_S)
{
  CCApplication* self = (CCApplication*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'currentLanguage'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getCurrentLanguage());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: targetPlatform of class  CCApplication */
#ifndef TOLUA_DISABLE_tolua_get_CCApplication_targetPlatform
static int tolua_get_CCApplication_targetPlatform(lua_State* tolua_S)
{
  CCApplication* self = (CCApplication*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'targetPlatform'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getTargetPlatform());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCApplication */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCApplication_new00_local
static int tolua_Cocos2d_CCApplication_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCApplication",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCApplication* tolua_ret = (CCApplication*)  CCApplication::sharedApplication();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCApplication");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: runningScene of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_get_CCDirector_currentScene_ptr
static int tolua_get_CCDirector_currentScene_ptr(lua_State* tolua_S)
{
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'runningScene'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getRunningScene(),"CCScene");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: animationInterval of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_get_CCDirector_animationInterval
static int tolua_get_CCDirector_animationInterval(lua_State* tolua_S)
{
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'animationInterval'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getAnimationInterval());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: paused of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_get_CCDirector_paused
static int tolua_get_CCDirector_paused(lua_State* tolua_S)
{
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'paused'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isPaused());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: winSize of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_get_CCDirector_winSize
static int tolua_get_CCDirector_winSize(lua_State* tolua_S)
{
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'winSize'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->getWinSize()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: visibleSize of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_get_CCDirector_visibleSize
static int tolua_get_CCDirector_visibleSize(lua_State* tolua_S)
{
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'visibleSize'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->getVisibleSize()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: visibleOrigin of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_get_CCDirector_visibleOrigin
static int tolua_get_CCDirector_visibleOrigin(lua_State* tolua_S)
{
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'visibleOrigin'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getVisibleOrigin()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: displayStats of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_get_CCDirector_displayStats
static int tolua_get_CCDirector_displayStats(lua_State* tolua_S)
{
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'displayStats'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isDisplayStats());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: displayStats of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_set_CCDirector_displayStats
static int tolua_set_CCDirector_displayStats(lua_State* tolua_S)
{
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'displayStats'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setDisplayStats(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: contentScaleFactor of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_get_CCDirector_contentScaleFactor
static int tolua_get_CCDirector_contentScaleFactor(lua_State* tolua_S)
{
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'contentScaleFactor'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getContentScaleFactor());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: contentScaleFactor of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_set_CCDirector_contentScaleFactor
static int tolua_set_CCDirector_contentScaleFactor(lua_State* tolua_S)
{
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'contentScaleFactor'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setContentScaleFactor(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: notificationNode of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_get_CCDirector_notificationNode_ptr
static int tolua_get_CCDirector_notificationNode_ptr(lua_State* tolua_S)
{
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'notificationNode'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getNotificationNode(),"CCNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: notificationNode of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_set_CCDirector_notificationNode_ptr
static int tolua_set_CCDirector_notificationNode_ptr(lua_State* tolua_S)
{
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'notificationNode'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setNotificationNode(((CCNode*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scheduler of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_get_CCDirector_scheduler_ptr
static int tolua_get_CCDirector_scheduler_ptr(lua_State* tolua_S)
{
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scheduler'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getScheduler(),"CCScheduler");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scheduler of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_set_CCDirector_scheduler_ptr
static int tolua_set_CCDirector_scheduler_ptr(lua_State* tolua_S)
{
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scheduler'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCScheduler",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setScheduler(((CCScheduler*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: convertToGL of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDirector_convertToGL00
static int tolua_Cocos2d_CCDirector_convertToGL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDirector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
  oVec2 point = *((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'convertToGL'", NULL);
#endif
  {
   oVec2 tolua_ret = (oVec2)  self->convertToGL(point);
   {
    void* tolua_obj = Mtolua_new((oVec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'convertToGL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: convertToUI of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDirector_convertToUI00
static int tolua_Cocos2d_CCDirector_convertToUI00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDirector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
  oVec2 point = *((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'convertToUI'", NULL);
#endif
  {
   oVec2 tolua_ret = (oVec2)  self->convertToUI(point);
   {
    void* tolua_obj = Mtolua_new((oVec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'convertToUI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: runWithScene of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDirector_run00
static int tolua_Cocos2d_CCDirector_run00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDirector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
  CCScene* scene = ((CCScene*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'runWithScene'", NULL);
#endif
  {
   self->runWithScene(scene);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'run'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pause of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDirector_pause00
static int tolua_Cocos2d_CCDirector_pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDirector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pause'", NULL);
#endif
  {
   self->pause();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resume of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDirector_resume00
static int tolua_Cocos2d_CCDirector_resume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDirector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resume'", NULL);
#endif
  {
   self->resume();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: end of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDirector_stop00
static int tolua_Cocos2d_CCDirector_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDirector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'end'", NULL);
#endif
  {
   self->end();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purgeCachedData of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDirector_purge00
static int tolua_Cocos2d_CCDirector_purge00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDirector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'purgeCachedData'", NULL);
#endif
  {
   self->purgeCachedData();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purge'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pushScene of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDirector_pushScene00
static int tolua_Cocos2d_CCDirector_pushScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDirector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
  CCScene* scene = ((CCScene*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pushScene'", NULL);
#endif
  {
   self->pushScene(scene);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pushScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: popScene of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDirector_popScene00
static int tolua_Cocos2d_CCDirector_popScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDirector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'popScene'", NULL);
#endif
  {
   self->popScene();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'popScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: popToRootScene of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDirector_popToRootScene00
static int tolua_Cocos2d_CCDirector_popToRootScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDirector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'popToRootScene'", NULL);
#endif
  {
   self->popToRootScene();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'popToRootScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: replaceScene of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDirector_replaceScene00
static int tolua_Cocos2d_CCDirector_replaceScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDirector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
  CCScene* scene = ((CCScene*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'replaceScene'", NULL);
#endif
  {
   self->replaceScene(scene);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'replaceScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDepthTest of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDirector_setDepthTest00
static int tolua_Cocos2d_CCDirector_setDepthTest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDirector",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDirector* self = (CCDirector*)  tolua_tousertype(tolua_S,1,0);
  bool var = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDepthTest'", NULL);
#endif
  {
   self->setDepthTest(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDepthTest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCDirector */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDirector_new00_local
static int tolua_Cocos2d_CCDirector_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDirector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCDirector* tolua_ret = (CCDirector*)  CCDirector::sharedDirector();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDirector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: xMLFilePath of class  CCUserDefault */
#ifndef TOLUA_DISABLE_tolua_get_CCUserDefault_filePath
static int tolua_get_CCUserDefault_filePath(lua_State* tolua_S)
{
  tolua_pushcppstring(tolua_S,(const char*)CCUserDefault::getXMLFilePath());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBoolForKey of class  CCUserDefault */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCUserDefault_get00
static int tolua_Cocos2d_CCUserDefault_get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCUserDefault",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCUserDefault* self = (CCUserDefault*)  tolua_tousertype(tolua_S,1,0);
  const char* pKey = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBoolForKey'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getBoolForKey(pKey);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDoubleForKey of class  CCUserDefault */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCUserDefault_get01
static int tolua_Cocos2d_CCUserDefault_get01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCUserDefault",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCUserDefault* self = (CCUserDefault*)  tolua_tousertype(tolua_S,1,0);
  const char* pKey = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDoubleForKey'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getDoubleForKey(pKey);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCUserDefault_get00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStringForKey of class  CCUserDefault */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCUserDefault_get02
static int tolua_Cocos2d_CCUserDefault_get02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCUserDefault",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCUserDefault* self = (CCUserDefault*)  tolua_tousertype(tolua_S,1,0);
  const char* pKey = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStringForKey'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getStringForKey(pKey);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCUserDefault_get01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBoolForKey of class  CCUserDefault */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCUserDefault_set00
static int tolua_Cocos2d_CCUserDefault_set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCUserDefault",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCUserDefault* self = (CCUserDefault*)  tolua_tousertype(tolua_S,1,0);
  const char* pKey = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool value = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBoolForKey'", NULL);
#endif
  {
   self->setBoolForKey(pKey,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDoubleForKey of class  CCUserDefault */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCUserDefault_set01
static int tolua_Cocos2d_CCUserDefault_set01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCUserDefault",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCUserDefault* self = (CCUserDefault*)  tolua_tousertype(tolua_S,1,0);
  const char* pKey = ((const char*)  tolua_tostring(tolua_S,2,0));
  double value = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDoubleForKey'", NULL);
#endif
  {
   self->setDoubleForKey(pKey,value);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_CCUserDefault_set00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStringForKey of class  CCUserDefault */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCUserDefault_set02
static int tolua_Cocos2d_CCUserDefault_set02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCUserDefault",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCUserDefault* self = (CCUserDefault*)  tolua_tousertype(tolua_S,1,0);
  const char* pKey = ((const char*)  tolua_tostring(tolua_S,2,0));
  string value = ((string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStringForKey'", NULL);
#endif
  {
   self->setStringForKey(pKey,value);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_CCUserDefault_set01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCUserDefault */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCUserDefault_new00_local
static int tolua_Cocos2d_CCUserDefault_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCUserDefault",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCUserDefault* tolua_ret = (CCUserDefault*)  CCUserDefault::sharedUserDefault();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCUserDefault");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: width of class  CCImage */
#ifndef TOLUA_DISABLE_tolua_get_CCImage_width
static int tolua_get_CCImage_width(lua_State* tolua_S)
{
  CCImage* self = (CCImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'width'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getWidth());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: height of class  CCImage */
#ifndef TOLUA_DISABLE_tolua_get_CCImage_height
static int tolua_get_CCImage_height(lua_State* tolua_S)
{
  CCImage* self = (CCImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'height'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getHeight());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: zOrder of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_zOrder
static int tolua_get_CCNode_zOrder(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'zOrder'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getZOrder());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rotation of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_rotation
static int tolua_get_CCNode_rotation(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rotation'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getRotation());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rotation of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_rotation
static int tolua_set_CCNode_rotation(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rotation'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setRotation(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scaleX of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_scaleX
static int tolua_get_CCNode_scaleX(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scaleX'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getScaleX());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scaleX of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_scaleX
static int tolua_set_CCNode_scaleX(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scaleX'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setScaleX(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scaleY of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_scaleY
static int tolua_get_CCNode_scaleY(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scaleY'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getScaleY());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scaleY of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_scaleY
static int tolua_set_CCNode_scaleY(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scaleY'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setScaleY(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: position of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_position
static int tolua_get_CCNode_position(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'position'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getPosition()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: position of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_position
static int tolua_set_CCNode_position(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'position'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setPosition(*((oVec2*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: positionX of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_positionX
static int tolua_get_CCNode_positionX(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'positionX'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getPositionX());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: positionX of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_positionX
static int tolua_set_CCNode_positionX(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'positionX'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setPositionX(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: positionY of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_positionY
static int tolua_get_CCNode_positionY(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'positionY'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getPositionY());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: positionY of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_positionY
static int tolua_set_CCNode_positionY(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'positionY'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setPositionY(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: positionZ of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_positionZ
static int tolua_get_CCNode_positionZ(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'positionZ'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getPositionZ());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: positionZ of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_positionZ
static int tolua_set_CCNode_positionZ(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'positionZ'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setPositionZ(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: skewX of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_skewX
static int tolua_get_CCNode_skewX(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skewX'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getSkewX());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: skewX of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_skewX
static int tolua_set_CCNode_skewX(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skewX'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setSkewX(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: skewY of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_skewY
static int tolua_get_CCNode_skewY(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skewY'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getSkewY());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: skewY of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_skewY
static int tolua_set_CCNode_skewY(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skewY'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setSkewY(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: visible of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_visible
static int tolua_get_CCNode_visible(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'visible'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isVisible());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: visible of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_visible
static int tolua_set_CCNode_visible(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'visible'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setVisible(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: anchorPoint of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_anchorPoint
static int tolua_get_CCNode_anchorPoint(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anchorPoint'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getAnchorPoint()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: anchorPoint of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_anchorPoint
static int tolua_set_CCNode_anchorPoint(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anchorPoint'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setAnchorPoint(*((oVec2*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: contentSize of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_contentSize
static int tolua_get_CCNode_contentSize(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'contentSize'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->getContentSize()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: contentSize of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_contentSize
static int tolua_set_CCNode_contentSize(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'contentSize'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setContentSize(*((CCSize*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tag of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_tag
static int tolua_get_CCNode_tag(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tag'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getTag());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: tag of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_tag
static int tolua_set_CCNode_tag(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tag'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setTag(((int)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: color of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_color
static int tolua_get_CCNode_color(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'color'",NULL);
#endif
    void* tolua_obj = Mtolua_new((ccColor3B)(self->getColor()));
     tolua_pushusertype(tolua_S,tolua_obj,"ccColor3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: color of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_color
static int tolua_set_CCNode_color(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'color'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor3",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setColor(*((ccColor3B*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: opacity of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_opacity
static int tolua_get_CCNode_opacity(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'opacity'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getOpacity());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: opacity of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_opacity
static int tolua_set_CCNode_opacity(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'opacity'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setOpacity(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: cascadeOpacity of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_cascadeOpacity
static int tolua_get_CCNode_cascadeOpacity(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cascadeOpacity'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isCascadeOpacity());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: cascadeOpacity of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_cascadeOpacity
static int tolua_set_CCNode_cascadeOpacity(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cascadeOpacity'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setCascadeOpacity(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: cascadeColor of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_cascadeColor
static int tolua_get_CCNode_cascadeColor(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cascadeColor'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isCascadeColor());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: cascadeColor of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_cascadeColor
static int tolua_set_CCNode_cascadeColor(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cascadeColor'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setCascadeColor(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: transformTarget of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_transformTarget_ptr
static int tolua_get_CCNode_transformTarget_ptr(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'transformTarget'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getTransformTarget(),"CCNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: transformTarget of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_transformTarget_ptr
static int tolua_set_CCNode_transformTarget_ptr(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'transformTarget'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setTransformTarget(((CCNode*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scheduler of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_scheduler_ptr
static int tolua_get_CCNode_scheduler_ptr(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scheduler'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getScheduler(),"CCScheduler");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scheduler of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_set_CCNode_scheduler_ptr
static int tolua_set_CCNode_scheduler_ptr(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scheduler'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCScheduler",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setScheduler(((CCScheduler*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: parent of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_parent_ptr
static int tolua_get_CCNode_parent_ptr(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'parent'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getParent(),"CCNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: boundingBox of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_boundingBox
static int tolua_get_CCNode_boundingBox(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'boundingBox'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCRect)(self->boundingBox()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: description of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_description
static int tolua_get_CCNode_description(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'description'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->description());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: numberOfRunningActions of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_numberOfRunningActions
static int tolua_get_CCNode_numberOfRunningActions(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'numberOfRunningActions'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->numberOfRunningActions());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: children of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_children_ptr
static int tolua_get_CCNode_children_ptr(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'children'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getChildren(),"CCArray");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: running of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_get_CCNode_running
static int tolua_get_CCNode_running(lua_State* tolua_S)
{
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'running'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isRunning());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_addChild00
static int tolua_Cocos2d_CCNode_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_addChild01
static int tolua_Cocos2d_CCNode_addChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child,zOrder);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_CCNode_addChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_addChild02
static int tolua_Cocos2d_CCNode_addChild02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
  int tag = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child,zOrder,tag);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_CCNode_addChild01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChild of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_removeChild00
static int tolua_Cocos2d_CCNode_removeChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'", NULL);
#endif
  {
   self->removeChild(child,cleanup);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChildByTag of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_removeChildByTag00
static int tolua_Cocos2d_CCNode_removeChildByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChildByTag'", NULL);
#endif
  {
   self->removeChildByTag(tag,cleanup);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeChildByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllChildrenWithCleanup of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_removeAllChildren00
static int tolua_Cocos2d_CCNode_removeAllChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  bool cleanup = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllChildrenWithCleanup'", NULL);
#endif
  {
   self->removeAllChildrenWithCleanup(cleanup);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reorderChild of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_reorderChild00
static int tolua_Cocos2d_CCNode_reorderChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reorderChild'", NULL);
#endif
  {
   self->reorderChild(child,zOrder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reorderChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: runAction of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_runAction00
static int tolua_Cocos2d_CCNode_runAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCAction",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  CCAction* action = ((CCAction*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'runAction'", NULL);
#endif
  {
   self->runAction(action);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'runAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopAllActions of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_stopAllActions00
static int tolua_Cocos2d_CCNode_stopAllActions00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopAllActions'", NULL);
#endif
  {
   self->stopAllActions();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopAllActions'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopAction of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_stopAction00
static int tolua_Cocos2d_CCNode_stopAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCAction",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  CCAction* action = ((CCAction*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopAction'", NULL);
#endif
  {
   self->stopAction(action);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stopActionByTag of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_stopActionByTag00
static int tolua_Cocos2d_CCNode_stopActionByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stopActionByTag'", NULL);
#endif
  {
   self->stopActionByTag(tag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stopActionByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getActionByTag of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_getActionByTag00
static int tolua_Cocos2d_CCNode_getActionByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getActionByTag'", NULL);
#endif
  {
   CCAction* tolua_ret = (CCAction*)  self->getActionByTag(tag);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getActionByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildByTag of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_getChildByTag00
static int tolua_Cocos2d_CCNode_getChildByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildByTag'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getChildByTag(tag);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scheduleUpdateWithPriorityLua of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_scheduleUpdate00
static int tolua_Cocos2d_CCNode_scheduleUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,2,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  int nHandler = toluafix_ref_function(tolua_S,2);
  int priority = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scheduleUpdateWithPriorityLua'", NULL);
#endif
  {
   self->scheduleUpdateWithPriorityLua(nHandler,priority);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scheduleUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unscheduleUpdate of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_unscheduleUpdate00
static int tolua_Cocos2d_CCNode_unscheduleUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unscheduleUpdate'", NULL);
#endif
  {
   self->unscheduleUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unscheduleUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptHandler of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_registerEventHandler00
static int tolua_Cocos2d_CCNode_registerEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,2,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  int funcID = toluafix_ref_function(tolua_S,2);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptHandler'", NULL);
#endif
  {
   self->registerScriptHandler(funcID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptHandler of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_unregisterEventHandler00
static int tolua_Cocos2d_CCNode_unregisterEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptHandler'", NULL);
#endif
  {
   self->unregisterScriptHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: convertToNodeSpaceAR of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_convertToNodeSpace00
static int tolua_Cocos2d_CCNode_convertToNodeSpace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  oVec2* worldPoint = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'convertToNodeSpaceAR'", NULL);
#endif
  {
   oVec2 tolua_ret = (oVec2)  self->convertToNodeSpaceAR(*worldPoint);
   {
    void* tolua_obj = Mtolua_new((oVec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'convertToNodeSpace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: convertToWorldSpaceAR of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_convertToWorldSpace00
static int tolua_Cocos2d_CCNode_convertToWorldSpace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  oVec2* nodePoint = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'convertToWorldSpaceAR'", NULL);
#endif
  {
   oVec2 tolua_ret = (oVec2)  self->convertToWorldSpaceAR(*nodePoint);
   {
    void* tolua_obj = Mtolua_new((oVec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'convertToWorldSpace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: convertToGameSpace of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_convertToGameSpace00
static int tolua_Cocos2d_CCNode_convertToGameSpace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* self = (CCNode*)  tolua_tousertype(tolua_S,1,0);
  oVec2* nodePoint = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'convertToGameSpace'", NULL);
#endif
  {
   oVec2 tolua_ret = (oVec2)  self->convertToGameSpace(*nodePoint);
   {
    void* tolua_obj = Mtolua_new((oVec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'convertToGameSpace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCNode_new00_local
static int tolua_Cocos2d_CCNode_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCNode* tolua_ret = (CCNode*)  CCNode::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawDot of class  CCDrawNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDrawNode_drawDot00
static int tolua_Cocos2d_CCDrawNode_drawDot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDrawNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"ccColor4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDrawNode* self = (CCDrawNode*)  tolua_tousertype(tolua_S,1,0);
  oVec2* pos = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
  float radius = ((float)  tolua_tonumber(tolua_S,3,0));
  ccColor4B* color = ((ccColor4B*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawDot'", NULL);
#endif
  {
   self->drawDot(*pos,radius,*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawDot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawSegment of class  CCDrawNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDrawNode_drawSegment00
static int tolua_Cocos2d_CCDrawNode_drawSegment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDrawNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"oVec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"ccColor4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDrawNode* self = (CCDrawNode*)  tolua_tousertype(tolua_S,1,0);
  oVec2* from = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
  oVec2* to = ((oVec2*)  tolua_tousertype(tolua_S,3,0));
  float radius = ((float)  tolua_tonumber(tolua_S,4,0));
  ccColor4B* color = ((ccColor4B*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawSegment'", NULL);
#endif
  {
   self->drawSegment(*from,*to,radius,*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawSegment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCDrawNode_drawPolygon of class  CCDrawNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDrawNode_drawPolygon00
static int tolua_Cocos2d_CCDrawNode_drawPolygon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDrawNode",0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"ccColor4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDrawNode* self = (CCDrawNode*)  tolua_tousertype(tolua_S,1,0);
  int tolua_len = lua_objlen(tolua_S,2);
  oVec2* verts = Mtolua_new_dim(oVec2, tolua_len);
  ccColor4B* fillColor = ((ccColor4B*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CCDrawNode_drawPolygon'", NULL);
#endif
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,2,"oVec2",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    verts[i] = *((oVec2*)  tolua_tofieldusertype(tolua_S,2,i+1,0));
   }
  }
  {
   CCDrawNode_drawPolygon(self,verts,tolua_len,*fillColor);
  }
  Mtolua_delete_dim(verts);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawPolygon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCDrawNode_drawPolygon of class  CCDrawNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDrawNode_drawPolygon01
static int tolua_Cocos2d_CCDrawNode_drawPolygon01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDrawNode",0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"ccColor4",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"ccColor4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCDrawNode* self = (CCDrawNode*)  tolua_tousertype(tolua_S,1,0);
  int tolua_len = lua_objlen(tolua_S,2);
  oVec2* verts = Mtolua_new_dim(oVec2, tolua_len);
  ccColor4B* fillColor = ((ccColor4B*)  tolua_tousertype(tolua_S,3,0));
  float borderWidth = ((float)  tolua_tonumber(tolua_S,4,0));
  ccColor4B borderColor = *((ccColor4B*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CCDrawNode_drawPolygon'", NULL);
#endif
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,2,"oVec2",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    verts[i] = *((oVec2*)  tolua_tofieldusertype(tolua_S,2,i+1,0));
   }
  }
  {
   CCDrawNode_drawPolygon(self,verts,tolua_len,*fillColor,borderWidth,borderColor);
  }
  Mtolua_delete_dim(verts);
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_CCDrawNode_drawPolygon00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  CCDrawNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDrawNode_clear00
static int tolua_Cocos2d_CCDrawNode_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDrawNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDrawNode* self = (CCDrawNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCDrawNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDrawNode_new00_local
static int tolua_Cocos2d_CCDrawNode_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDrawNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCDrawNode* tolua_ret = (CCDrawNode*)  CCDrawNode::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCDrawNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: contentSizeInPixels of class  CCTexture2D */
#ifndef TOLUA_DISABLE_tolua_get_CCTexture2D_size
static int tolua_get_CCTexture2D_size(lua_State* tolua_S)
{
  CCTexture2D* self = (CCTexture2D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'contentSizeInPixels'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->getContentSizeInPixels()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hasMipmaps of class  CCTexture2D */
#ifndef TOLUA_DISABLE_tolua_get_CCTexture2D_hasMipmaps
static int tolua_get_CCTexture2D_hasMipmaps(lua_State* tolua_S)
{
  CCTexture2D* self = (CCTexture2D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hasMipmaps'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->hasMipmaps());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: antiAlias of class  CCTexture2D */
#ifndef TOLUA_DISABLE_tolua_get_CCTexture2D_antiAlias
static int tolua_get_CCTexture2D_antiAlias(lua_State* tolua_S)
{
  CCTexture2D* self = (CCTexture2D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'antiAlias'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->getAntiAlias());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: antiAlias of class  CCTexture2D */
#ifndef TOLUA_DISABLE_tolua_set_CCTexture2D_antiAlias
static int tolua_set_CCTexture2D_antiAlias(lua_State* tolua_S)
{
  CCTexture2D* self = (CCTexture2D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'antiAlias'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setAntiAlias(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: defaultAlphaPixelFormat of class  CCTexture2D */
#ifndef TOLUA_DISABLE_tolua_get_CCTexture2D_pixelFormat
static int tolua_get_CCTexture2D_pixelFormat(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)CCTexture2D::getDefaultAlphaPixelFormat());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: defaultAlphaPixelFormat of class  CCTexture2D */
#ifndef TOLUA_DISABLE_tolua_set_CCTexture2D_pixelFormat
static int tolua_set_CCTexture2D_pixelFormat(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  CCTexture2D::setDefaultAlphaPixelFormat(((CCTexture2DPixelFormat) (int)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: generateMipmap of class  CCTexture2D */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTexture2D_generateMipmap00
static int tolua_Cocos2d_CCTexture2D_generateMipmap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTexture2D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTexture2D* self = (CCTexture2D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'generateMipmap'", NULL);
#endif
  {
   self->generateMipmap();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'generateMipmap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCTextureCache_add of class  CCTextureCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTextureCache_add00
static int tolua_Cocos2d_CCTextureCache_add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextureCache",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCRenderTarget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextureCache* self = (CCTextureCache*)  tolua_tousertype(tolua_S,1,0);
  CCRenderTexture* renderTexture = ((CCRenderTexture*)  tolua_tousertype(tolua_S,2,0));
  const char* key = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CCTextureCache_add'", NULL);
#endif
  {
   tolua_outside CCTexture2D* tolua_ret = (tolua_outside CCTexture2D*)  CCTextureCache_add(self,renderTexture,key);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCTexture2D");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addImage of class  CCTextureCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTextureCache_load00
static int tolua_Cocos2d_CCTextureCache_load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextureCache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextureCache* self = (CCTextureCache*)  tolua_tousertype(tolua_S,1,0);
  const char* fileimage = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addImage'", NULL);
#endif
  {
   CCTexture2D* tolua_ret = (CCTexture2D*)  self->addImage(fileimage);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCTexture2D");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllTextures of class  CCTextureCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTextureCache_unload00
static int tolua_Cocos2d_CCTextureCache_unload00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextureCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextureCache* self = (CCTextureCache*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllTextures'", NULL);
#endif
  {
   self->removeAllTextures();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unload'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeUnusedTextures of class  CCTextureCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTextureCache_removeUnused00
static int tolua_Cocos2d_CCTextureCache_removeUnused00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextureCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextureCache* self = (CCTextureCache*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeUnusedTextures'", NULL);
#endif
  {
   self->removeUnusedTextures();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeUnused'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeTextureForKey of class  CCTextureCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTextureCache_remove00
static int tolua_Cocos2d_CCTextureCache_remove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextureCache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextureCache* self = (CCTextureCache*)  tolua_tousertype(tolua_S,1,0);
  const char* textureKeyName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeTextureForKey'", NULL);
#endif
  {
   self->removeTextureForKey(textureKeyName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'remove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeTexture of class  CCTextureCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTextureCache_remove01
static int tolua_Cocos2d_CCTextureCache_remove01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextureCache",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCTextureCache* self = (CCTextureCache*)  tolua_tousertype(tolua_S,1,0);
  CCTexture2D* texture = ((CCTexture2D*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeTexture'", NULL);
#endif
  {
   self->removeTexture(texture);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_CCTextureCache_remove00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: dumpCachedTextureInfo of class  CCTextureCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTextureCache_dumpInfo00
static int tolua_Cocos2d_CCTextureCache_dumpInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextureCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextureCache* self = (CCTextureCache*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dumpCachedTextureInfo'", NULL);
#endif
  {
   self->dumpCachedTextureInfo();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dumpInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCTextureCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTextureCache_new00_local
static int tolua_Cocos2d_CCTextureCache_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTextureCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCTextureCache* tolua_ret = (CCTextureCache*)  CCTextureCache::sharedTextureCache();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTextureCache");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: beginWithClear of class  CCRenderTexture */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCRenderTarget_beginPaint00
static int tolua_Cocos2d_CCRenderTarget_beginPaint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRenderTarget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRenderTexture* self = (CCRenderTexture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'beginWithClear'", NULL);
#endif
  {
   self->beginWithClear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'beginPaint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: beginWithClear of class  CCRenderTexture */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCRenderTarget_beginPaint01
static int tolua_Cocos2d_CCRenderTarget_beginPaint01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRenderTarget",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCRenderTexture* self = (CCRenderTexture*)  tolua_tousertype(tolua_S,1,0);
  ccColor4B* color = ((ccColor4B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'beginWithClear'", NULL);
#endif
  {
   self->beginWithClear(*color);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_CCRenderTarget_beginPaint00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: render of class  CCRenderTexture */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCRenderTarget_draw00
static int tolua_Cocos2d_CCRenderTarget_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRenderTarget",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRenderTexture* self = (CCRenderTexture*)  tolua_tousertype(tolua_S,1,0);
  CCNode* target = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'render'", NULL);
#endif
  {
   self->render(target);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: end of class  CCRenderTexture */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCRenderTarget_endPaint00
static int tolua_Cocos2d_CCRenderTarget_endPaint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRenderTarget",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRenderTexture* self = (CCRenderTexture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'end'", NULL);
#endif
  {
   self->end();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'endPaint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: saveToFile of class  CCRenderTexture */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCRenderTarget_save00
static int tolua_Cocos2d_CCRenderTarget_save00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRenderTarget",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRenderTexture* self = (CCRenderTexture*)  tolua_tousertype(tolua_S,1,0);
  char* name = ((char*)  tolua_tostring(tolua_S,2,0));
  tCCImageFormat format = ((tCCImageFormat) (int)  tolua_tonumber(tolua_S,3,kCCImageFormatJPEG));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'saveToFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->saveToFile(name,format);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'save'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCRenderTexture */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCRenderTarget_new00_local
static int tolua_Cocos2d_CCRenderTarget_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCRenderTarget",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int w = ((int)  tolua_tonumber(tolua_S,2,0));
  int h = ((int)  tolua_tonumber(tolua_S,3,0));
  bool withDepthStencil = ((bool)  tolua_toboolean(tolua_S,4,false));
  {
   tolua_outside CCRenderTexture* tolua_ret = (tolua_outside CCRenderTexture*)  CCRenderTexture_create(w,h,withDepthStencil);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCRenderTarget");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: texture of class  CCSprite */
#ifndef TOLUA_DISABLE_tolua_get_CCSprite_texture_ptr
static int tolua_get_CCSprite_texture_ptr(lua_State* tolua_S)
{
  CCSprite* self = (CCSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'texture'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getTexture(),"CCTexture2D");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: texture of class  CCSprite */
#ifndef TOLUA_DISABLE_tolua_set_CCSprite_texture_ptr
static int tolua_set_CCSprite_texture_ptr(lua_State* tolua_S)
{
  CCSprite* self = (CCSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'texture'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setTexture(((CCTexture2D*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: textureRect of class  CCSprite */
#ifndef TOLUA_DISABLE_tolua_get_CCSprite_textureRect
static int tolua_get_CCSprite_textureRect(lua_State* tolua_S)
{
  CCSprite* self = (CCSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'textureRect'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCRect)(self->getTextureRect()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: textureRect of class  CCSprite */
#ifndef TOLUA_DISABLE_tolua_set_CCSprite_textureRect
static int tolua_set_CCSprite_textureRect(lua_State* tolua_S)
{
  CCSprite* self = (CCSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'textureRect'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setTextureRect(*((CCRect*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: blendFunc of class  CCSprite */
#ifndef TOLUA_DISABLE_tolua_get_CCSprite_blendFunc
static int tolua_get_CCSprite_blendFunc(lua_State* tolua_S)
{
  CCSprite* self = (CCSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blendFunc'",NULL);
#endif
    void* tolua_obj = Mtolua_new((ccBlendFunc)(self->getBlendFunc()));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: blendFunc of class  CCSprite */
#ifndef TOLUA_DISABLE_tolua_set_CCSprite_blendFunc
static int tolua_set_CCSprite_blendFunc(lua_State* tolua_S)
{
  CCSprite* self = (CCSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blendFunc'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccBlendFunc",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setBlendFunc(*((ccBlendFunc*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: flipX of class  CCSprite */
#ifndef TOLUA_DISABLE_tolua_get_CCSprite_flipX
static int tolua_get_CCSprite_flipX(lua_State* tolua_S)
{
  CCSprite* self = (CCSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'flipX'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isFlipX());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: flipX of class  CCSprite */
#ifndef TOLUA_DISABLE_tolua_set_CCSprite_flipX
static int tolua_set_CCSprite_flipX(lua_State* tolua_S)
{
  CCSprite* self = (CCSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'flipX'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setFlipX(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: flipY of class  CCSprite */
#ifndef TOLUA_DISABLE_tolua_get_CCSprite_flipY
static int tolua_get_CCSprite_flipY(lua_State* tolua_S)
{
  CCSprite* self = (CCSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'flipY'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isFlipY());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: flipY of class  CCSprite */
#ifndef TOLUA_DISABLE_tolua_set_CCSprite_flipY
static int tolua_set_CCSprite_flipY(lua_State* tolua_S)
{
  CCSprite* self = (CCSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'flipY'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setFlipY(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCSprite */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCSprite_new00_local
static int tolua_Cocos2d_CCSprite_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCSprite* tolua_ret = (CCSprite*)  CCSprite::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCSprite */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCSprite_new01_local
static int tolua_Cocos2d_CCSprite_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCTexture2D* pTexture = ((CCTexture2D*)  tolua_tousertype(tolua_S,2,0));
  {
   CCSprite* tolua_ret = (CCSprite*)  CCSprite::createWithTexture(pTexture);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCSprite_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCSprite */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCSprite_new02_local
static int tolua_Cocos2d_CCSprite_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCTexture2D* pTexture = ((CCTexture2D*)  tolua_tousertype(tolua_S,2,0));
  CCRect rect = *((CCRect*)  tolua_tousertype(tolua_S,3,0));
  {
   CCSprite* tolua_ret = (CCSprite*)  CCSprite::createWithTexture(pTexture,rect);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCSprite_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCSprite */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCSprite_new03_local
static int tolua_Cocos2d_CCSprite_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* clipStr = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   tolua_outside CCSprite* tolua_ret = (tolua_outside CCSprite*)  CCSprite_createWithClip(clipStr);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCSprite_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCSpriteBatchNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCSpriteBatchNode_new00_local
static int tolua_Cocos2d_CCSpriteBatchNode_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSpriteBatchNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTexture2D* tex = ((CCTexture2D*)  tolua_tousertype(tolua_S,2,0));
  {
   CCSpriteBatchNode* tolua_ret = (CCSpriteBatchNode*)  CCSpriteBatchNode::createWithTexture(tex);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCSpriteBatchNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCSpriteBatchNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCSpriteBatchNode_new01_local
static int tolua_Cocos2d_CCSpriteBatchNode_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSpriteBatchNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCTexture2D* tex = ((CCTexture2D*)  tolua_tousertype(tolua_S,2,0));
  unsigned int capacity = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   CCSpriteBatchNode* tolua_ret = (CCSpriteBatchNode*)  CCSpriteBatchNode::createWithTexture(tex,capacity);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCSpriteBatchNode");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCSpriteBatchNode_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCSpriteBatchNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCSpriteBatchNode_new02_local
static int tolua_Cocos2d_CCSpriteBatchNode_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSpriteBatchNode",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* fileImage = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int capacity = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   CCSpriteBatchNode* tolua_ret = (CCSpriteBatchNode*)  CCSpriteBatchNode::create(fileImage,capacity);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCSpriteBatchNode");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCSpriteBatchNode_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCSpriteBatchNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCSpriteBatchNode_new03_local
static int tolua_Cocos2d_CCSpriteBatchNode_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSpriteBatchNode",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* fileImage = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCSpriteBatchNode* tolua_ret = (CCSpriteBatchNode*)  CCSpriteBatchNode::create(fileImage);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCSpriteBatchNode");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCSpriteBatchNode_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: touchEnabled of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_get_CCLayer_touchEnabled
static int tolua_get_CCLayer_touchEnabled(lua_State* tolua_S)
{
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'touchEnabled'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isTouchEnabled());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: touchEnabled of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_set_CCLayer_touchEnabled
static int tolua_set_CCLayer_touchEnabled(lua_State* tolua_S)
{
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'touchEnabled'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setTouchEnabled(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: accelerometerEnabled of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_get_CCLayer_accelerometerEnabled
static int tolua_get_CCLayer_accelerometerEnabled(lua_State* tolua_S)
{
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'accelerometerEnabled'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isAccelerometerEnabled());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: accelerometerEnabled of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_set_CCLayer_accelerometerEnabled
static int tolua_set_CCLayer_accelerometerEnabled(lua_State* tolua_S)
{
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'accelerometerEnabled'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setAccelerometerEnabled(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: keypadEnabled of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_get_CCLayer_keypadEnabled
static int tolua_get_CCLayer_keypadEnabled(lua_State* tolua_S)
{
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'keypadEnabled'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isKeypadEnabled());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: keypadEnabled of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_set_CCLayer_keypadEnabled
static int tolua_set_CCLayer_keypadEnabled(lua_State* tolua_S)
{
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'keypadEnabled'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setKeypadEnabled(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: touchMode of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_get_CCLayer_touchMode
static int tolua_get_CCLayer_touchMode(lua_State* tolua_S)
{
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'touchMode'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getTouchMode());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: touchMode of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_set_CCLayer_touchMode
static int tolua_set_CCLayer_touchMode(lua_State* tolua_S)
{
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'touchMode'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setTouchMode(((int)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: touchPriority of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_get_CCLayer_touchPriority
static int tolua_get_CCLayer_touchPriority(lua_State* tolua_S)
{
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'touchPriority'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getTouchPriority());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: touchPriority of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_set_CCLayer_touchPriority
static int tolua_set_CCLayer_touchPriority(lua_State* tolua_S)
{
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'touchPriority'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setTouchPriority(((int)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptTouchHandler of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLayer_registerTouchHandler00
static int tolua_Cocos2d_CCLayer_registerTouchHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,2,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
  int nHandler = toluafix_ref_function(tolua_S,2);
  bool bIsMultiTouches = ((bool)  tolua_toboolean(tolua_S,3,false));
  int nPriority = ((int)  tolua_tonumber(tolua_S,4,0));
  bool bSwallowsTouches = ((bool)  tolua_toboolean(tolua_S,5,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptTouchHandler'", NULL);
#endif
  {
   self->registerScriptTouchHandler(nHandler,bIsMultiTouches,nPriority,bSwallowsTouches);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerTouchHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptTouchHandler of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLayer_unregisterTouchHandler00
static int tolua_Cocos2d_CCLayer_unregisterTouchHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptTouchHandler'", NULL);
#endif
  {
   self->unregisterScriptTouchHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterTouchHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptKeypadHandler of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLayer_registerKeypadHandler00
static int tolua_Cocos2d_CCLayer_registerKeypadHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,2,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
  int nHandler = toluafix_ref_function(tolua_S,2);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptKeypadHandler'", NULL);
#endif
  {
   self->registerScriptKeypadHandler(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerKeypadHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptKeypadHandler of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLayer_unregisterKeypadHandler00
static int tolua_Cocos2d_CCLayer_unregisterKeypadHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptKeypadHandler'", NULL);
#endif
  {
   self->unregisterScriptKeypadHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterKeypadHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptAccelerateHandler of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLayer_registerAccelerateHandler00
static int tolua_Cocos2d_CCLayer_registerAccelerateHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,2,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
  int nHandler = toluafix_ref_function(tolua_S,2);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptAccelerateHandler'", NULL);
#endif
  {
   self->registerScriptAccelerateHandler(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerAccelerateHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptAccelerateHandler of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLayer_unregisterAccelerateHandler00
static int tolua_Cocos2d_CCLayer_unregisterAccelerateHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptAccelerateHandler'", NULL);
#endif
  {
   self->unregisterScriptAccelerateHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterAccelerateHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLayer_new00_local
static int tolua_Cocos2d_CCLayer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCLayer* tolua_ret = (CCLayer*)  CCLayer::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: blendFunc of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_get_CCLayerColor_blendFunc
static int tolua_get_CCLayerColor_blendFunc(lua_State* tolua_S)
{
  CCLayerColor* self = (CCLayerColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blendFunc'",NULL);
#endif
    void* tolua_obj = Mtolua_new((ccBlendFunc)(self->getBlendFunc()));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: blendFunc of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_set_CCLayerColor_blendFunc
static int tolua_set_CCLayerColor_blendFunc(lua_State* tolua_S)
{
  CCLayerColor* self = (CCLayerColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blendFunc'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccBlendFunc",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setBlendFunc(*((ccBlendFunc*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLayerColor_new00_local
static int tolua_Cocos2d_CCLayerColor_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor4",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ccColor4B color = *((ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  float width = ((float)  tolua_tonumber(tolua_S,3,0));
  float height = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCLayerColor* tolua_ret = (CCLayerColor*)  CCLayerColor::create(color,width,height);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCLayerColor");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLayerColor_new01_local
static int tolua_Cocos2d_CCLayerColor_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ccColor4B color = *((ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  {
   CCLayerColor* tolua_ret = (CCLayerColor*)  CCLayerColor::create(color);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCLayerColor");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCLayerColor_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: blendFunc of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_get_CCLayerGradient_blendFunc
static int tolua_get_CCLayerGradient_blendFunc(lua_State* tolua_S)
{
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blendFunc'",NULL);
#endif
    void* tolua_obj = Mtolua_new((ccBlendFunc)(self->getBlendFunc()));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: blendFunc of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_set_CCLayerGradient_blendFunc
static int tolua_set_CCLayerGradient_blendFunc(lua_State* tolua_S)
{
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blendFunc'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccBlendFunc",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setBlendFunc(*((ccBlendFunc*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: startColor of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_get_CCLayerGradient_startColor
static int tolua_get_CCLayerGradient_startColor(lua_State* tolua_S)
{
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'startColor'",NULL);
#endif
    void* tolua_obj = Mtolua_new((ccColor3B)(self->getStartColor()));
     tolua_pushusertype(tolua_S,tolua_obj,"ccColor3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: startColor of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_set_CCLayerGradient_startColor
static int tolua_set_CCLayerGradient_startColor(lua_State* tolua_S)
{
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'startColor'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor3",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setStartColor(*((ccColor3B*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: endColor of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_get_CCLayerGradient_endColor
static int tolua_get_CCLayerGradient_endColor(lua_State* tolua_S)
{
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'endColor'",NULL);
#endif
    void* tolua_obj = Mtolua_new((ccColor3B)(self->getEndColor()));
     tolua_pushusertype(tolua_S,tolua_obj,"ccColor3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: endColor of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_set_CCLayerGradient_endColor
static int tolua_set_CCLayerGradient_endColor(lua_State* tolua_S)
{
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'endColor'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor3",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setEndColor(*((ccColor3B*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: startOpacity of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_get_CCLayerGradient_startOpacity
static int tolua_get_CCLayerGradient_startOpacity(lua_State* tolua_S)
{
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'startOpacity'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getStartOpacity());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: startOpacity of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_set_CCLayerGradient_startOpacity
static int tolua_set_CCLayerGradient_startOpacity(lua_State* tolua_S)
{
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'startOpacity'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setStartOpacity(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: endOpacity of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_get_CCLayerGradient_endOpacity
static int tolua_get_CCLayerGradient_endOpacity(lua_State* tolua_S)
{
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'endOpacity'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getEndOpacity());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: endOpacity of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_set_CCLayerGradient_endOpacity
static int tolua_set_CCLayerGradient_endOpacity(lua_State* tolua_S)
{
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'endOpacity'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setEndOpacity(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: vector of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_get_CCLayerGradient_vector
static int tolua_get_CCLayerGradient_vector(lua_State* tolua_S)
{
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vector'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getVector()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: vector of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_set_CCLayerGradient_vector
static int tolua_set_CCLayerGradient_vector(lua_State* tolua_S)
{
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vector'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setVector(*((oVec2*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: compressedInterpolation of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_get_CCLayerGradient_compressedInterpolation
static int tolua_get_CCLayerGradient_compressedInterpolation(lua_State* tolua_S)
{
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'compressedInterpolation'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isCompressedInterpolation());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: compressedInterpolation of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_set_CCLayerGradient_compressedInterpolation
static int tolua_set_CCLayerGradient_compressedInterpolation(lua_State* tolua_S)
{
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'compressedInterpolation'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setCompressedInterpolation(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLayerGradient_new00_local
static int tolua_Cocos2d_CCLayerGradient_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor4",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"ccColor4",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ccColor4B start = *((ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  ccColor4B end = *((ccColor4B*)  tolua_tousertype(tolua_S,3,0));
  oVec2 v = *((oVec2*)  tolua_tousertype(tolua_S,4,0));
  {
   CCLayerGradient* tolua_ret = (CCLayerGradient*)  CCLayerGradient::create(start,end,v);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCLayerGradient");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLayerGradient_new01_local
static int tolua_Cocos2d_CCLayerGradient_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor4",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"ccColor4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ccColor4B start = *((ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  ccColor4B end = *((ccColor4B*)  tolua_tousertype(tolua_S,3,0));
  {
   CCLayerGradient* tolua_ret = (CCLayerGradient*)  CCLayerGradient::create(start,end);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCLayerGradient");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCLayerGradient_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLayerGradient_new02_local
static int tolua_Cocos2d_CCLayerGradient_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   CCLayerGradient* tolua_ret = (CCLayerGradient*)  CCLayerGradient::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCLayerGradient");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCLayerGradient_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_new00_local
static int tolua_Cocos2d_CCScene_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCScene* tolua_ret = (CCScene*)  CCScene::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createOriented of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_oriented00
static int tolua_Cocos2d_CCScene_oriented00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  tOrientation orientation = ((tOrientation) (int)  tolua_tonumber(tolua_S,4,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createOriented(duration,nextScene,orientation);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'oriented'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createRotoZoom of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_rotoZoom00
static int tolua_Cocos2d_CCScene_rotoZoom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createRotoZoom(duration,nextScene);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rotoZoom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createJumpZoom of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_jumpZoom00
static int tolua_Cocos2d_CCScene_jumpZoom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createJumpZoom(duration,nextScene);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'jumpZoom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createMove of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_move00
static int tolua_Cocos2d_CCScene_move00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  tOrientation orientation = ((tOrientation) (int)  tolua_tonumber(tolua_S,4,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createMove(duration,nextScene,orientation);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'move'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createSlide of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_slide00
static int tolua_Cocos2d_CCScene_slide00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  tOrientation orientation = ((tOrientation) (int)  tolua_tonumber(tolua_S,4,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createSlide(duration,nextScene,orientation);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'slide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createShrinkGrow of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_shrinkGrow00
static int tolua_Cocos2d_CCScene_shrinkGrow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createShrinkGrow(duration,nextScene);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'shrinkGrow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createFlipX of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_flipX00
static int tolua_Cocos2d_CCScene_flipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  tOrientation orientation = ((tOrientation) (int)  tolua_tonumber(tolua_S,4,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createFlipX(duration,nextScene,orientation);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'flipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createFlipY of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_flipY00
static int tolua_Cocos2d_CCScene_flipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  tOrientation orientation = ((tOrientation) (int)  tolua_tonumber(tolua_S,4,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createFlipY(duration,nextScene,orientation);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'flipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createFlipAngular of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_flipAngular00
static int tolua_Cocos2d_CCScene_flipAngular00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  tOrientation orientation = ((tOrientation) (int)  tolua_tonumber(tolua_S,4,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createFlipAngular(duration,nextScene,orientation);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'flipAngular'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createZoomFlipX of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_zoomFlipX00
static int tolua_Cocos2d_CCScene_zoomFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  tOrientation orientation = ((tOrientation) (int)  tolua_tonumber(tolua_S,4,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createZoomFlipX(duration,nextScene,orientation);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'zoomFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createZoomFlipY of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_zoomFlipY00
static int tolua_Cocos2d_CCScene_zoomFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  tOrientation orientation = ((tOrientation) (int)  tolua_tonumber(tolua_S,4,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createZoomFlipY(duration,nextScene,orientation);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'zoomFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createZoomFlipAngular of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_zoomFlipAngular00
static int tolua_Cocos2d_CCScene_zoomFlipAngular00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  tOrientation orientation = ((tOrientation) (int)  tolua_tonumber(tolua_S,4,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createZoomFlipAngular(duration,nextScene,orientation);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'zoomFlipAngular'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createFade of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_fade00
static int tolua_Cocos2d_CCScene_fade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"ccColor3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  ccColor3B* color = ((ccColor3B*)  tolua_tousertype(tolua_S,4,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createFade(duration,nextScene,*color);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createCrossFade of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_crossFade00
static int tolua_Cocos2d_CCScene_crossFade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createCrossFade(duration,nextScene);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'crossFade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createTurnOffTiles of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_turnOffTiles00
static int tolua_Cocos2d_CCScene_turnOffTiles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createTurnOffTiles(duration,nextScene);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'turnOffTiles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createSplitCols of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_splitCols00
static int tolua_Cocos2d_CCScene_splitCols00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createSplitCols(duration,nextScene);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'splitCols'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createSplitRows of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_splitRows00
static int tolua_Cocos2d_CCScene_splitRows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createSplitRows(duration,nextScene);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'splitRows'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createFadeTiles of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_fadeTiles00
static int tolua_Cocos2d_CCScene_fadeTiles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  tOrientation orientation = ((tOrientation) (int)  tolua_tonumber(tolua_S,4,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createFadeTiles(duration,nextScene,orientation);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fadeTiles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createPageTurn of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_pageTurn00
static int tolua_Cocos2d_CCScene_pageTurn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  bool backward = ((bool)  tolua_toboolean(tolua_S,4,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createPageTurn(duration,nextScene,backward);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pageTurn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createProgressCCW of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_progressCCW00
static int tolua_Cocos2d_CCScene_progressCCW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createProgressCCW(duration,nextScene);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'progressCCW'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createProgressCW of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_progressCW00
static int tolua_Cocos2d_CCScene_progressCW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createProgressCW(duration,nextScene);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'progressCW'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createProgressH of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_progressH00
static int tolua_Cocos2d_CCScene_progressH00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createProgressH(duration,nextScene);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'progressH'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createProgressV of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_progressV00
static int tolua_Cocos2d_CCScene_progressV00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createProgressV(duration,nextScene);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'progressV'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createProgressIO of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_progressIO00
static int tolua_Cocos2d_CCScene_progressIO00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createProgressIO(duration,nextScene);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'progressIO'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCScene_createProgressOI of class  CCScene */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScene_progressOI00
static int tolua_Cocos2d_CCScene_progressOI00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCScene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCScene* nextScene = ((CCScene*)  tolua_tousertype(tolua_S,3,0));
  {
   tolua_outside CCScene* tolua_ret = (tolua_outside CCScene*)  CCScene_createProgressOI(duration,nextScene);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'progressOI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: timeScale of class  CCScheduler */
#ifndef TOLUA_DISABLE_tolua_get_CCScheduler_timeScale
static int tolua_get_CCScheduler_timeScale(lua_State* tolua_S)
{
  CCScheduler* self = (CCScheduler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'timeScale'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getTimeScale());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: timeScale of class  CCScheduler */
#ifndef TOLUA_DISABLE_tolua_set_CCScheduler_timeScale
static int tolua_set_CCScheduler_timeScale(lua_State* tolua_S)
{
  CCScheduler* self = (CCScheduler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'timeScale'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setTimeScale(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: scheduleScriptFunc of class  CCScheduler */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScheduler_shedule00
static int tolua_Cocos2d_CCScheduler_shedule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScheduler",0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,2,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScheduler* self = (CCScheduler*)  tolua_tousertype(tolua_S,1,0);
  int nHandler = toluafix_ref_function(tolua_S,2);
  float fInterval = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scheduleScriptFunc'", NULL);
#endif
  {
   self->scheduleScriptFunc(nHandler,fInterval);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'shedule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unscheduleScriptFunc of class  CCScheduler */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScheduler_unshedule00
static int tolua_Cocos2d_CCScheduler_unshedule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScheduler",0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,2,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScheduler* self = (CCScheduler*)  tolua_tousertype(tolua_S,1,0);
  int nHandler = toluafix_ref_function(tolua_S,2);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unscheduleScriptFunc'", NULL);
#endif
  {
   self->unscheduleScriptFunc(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unshedule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCScheduler */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCScheduler_new00_local
static int tolua_Cocos2d_CCScheduler_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScheduler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCScheduler* tolua_ret = (CCScheduler*)  CCScheduler::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCScheduler");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: done of class  CCAction */
#ifndef TOLUA_DISABLE_tolua_get_CCAction_done
static int tolua_get_CCAction_done(lua_State* tolua_S)
{
  CCAction* self = (CCAction*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'done'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isDone());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: target of class  CCAction */
#ifndef TOLUA_DISABLE_tolua_get_CCAction_target_ptr
static int tolua_get_CCAction_target_ptr(lua_State* tolua_S)
{
  CCAction* self = (CCAction*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'target'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getTarget(),"CCNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tag of class  CCAction */
#ifndef TOLUA_DISABLE_tolua_get_CCAction_tag
static int tolua_get_CCAction_tag(lua_State* tolua_S)
{
  CCAction* self = (CCAction*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tag'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getTag());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: tag of class  CCAction */
#ifndef TOLUA_DISABLE_tolua_set_CCAction_tag
static int tolua_set_CCAction_tag(lua_State* tolua_S)
{
  CCAction* self = (CCAction*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tag'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setTag(((int)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: duration of class  CCFiniteTimeAction */
#ifndef TOLUA_DISABLE_tolua_get_CCFiniteTimeAction_duration
static int tolua_get_CCFiniteTimeAction_duration(lua_State* tolua_S)
{
  CCFiniteTimeAction* self = (CCFiniteTimeAction*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'duration'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getDuration());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: reverse of class  CCFiniteTimeAction */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCFiniteTimeAction_reverse00
static int tolua_Cocos2d_CCFiniteTimeAction_reverse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFiniteTimeAction",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFiniteTimeAction* self = (CCFiniteTimeAction*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reverse'", NULL);
#endif
  {
   CCFiniteTimeAction* tolua_ret = (CCFiniteTimeAction*)  self->reverse();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCFiniteTimeAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reverse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: elapsed of class  CCActionInterval */
#ifndef TOLUA_DISABLE_tolua_get_CCActionInterval_elapsed
static int tolua_get_CCActionInterval_elapsed(lua_State* tolua_S)
{
  CCActionInterval* self = (CCActionInterval*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'elapsed'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getElapsed());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: reverse of class  CCActionInterval */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCActionInterval_reverse00
static int tolua_Cocos2d_CCActionInterval_reverse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCActionInterval",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCActionInterval* self = (CCActionInterval*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reverse'", NULL);
#endif
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  self->reverse();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reverse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: speed of class  CCSpeed */
#ifndef TOLUA_DISABLE_tolua_get_CCSpeed_rate
static int tolua_get_CCSpeed_rate(lua_State* tolua_S)
{
  CCSpeed* self = (CCSpeed*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'speed'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getSpeed());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: speed of class  CCSpeed */
#ifndef TOLUA_DISABLE_tolua_set_CCSpeed_rate
static int tolua_set_CCSpeed_rate(lua_State* tolua_S)
{
  CCSpeed* self = (CCSpeed*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'speed'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setSpeed(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCSpeed */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCSpeed_new00_local
static int tolua_Cocos2d_CCSpeed_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSpeed",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCActionInterval",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCActionInterval* pAction = ((CCActionInterval*)  tolua_tousertype(tolua_S,2,0));
  float fRate = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CCSpeed* tolua_ret = (CCSpeed*)  CCSpeed::create(pAction,fRate);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSpeed");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCFollow::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCFollow00
static int tolua_Cocos2d_CCFollow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* pFollowedNode = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  {
   CCAction* tolua_ret = (CCAction*)  CCFollow::create(pFollowedNode);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCFollow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCFollow::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCFollow01
static int tolua_Cocos2d_CCFollow01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCNode* pFollowedNode = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  CCRect rect = *((CCRect*)  tolua_tousertype(tolua_S,2,0));
  {
   CCAction* tolua_ret = (CCAction*)  CCFollow::create(pFollowedNode,rect);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCAction");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCFollow00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCSequence::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCSequence00
static int tolua_Cocos2d_CCSequence00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_istable(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int tolua_len = lua_objlen(tolua_S,1);
  CCFiniteTimeAction** actions = Mtolua_new_dim(CCFiniteTimeAction*, tolua_len);
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,1,"CCFiniteTimeAction",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    actions[i] = ((CCFiniteTimeAction*)  tolua_tofieldusertype(tolua_S,1,i+1,0));
   }
  }
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCSequence::create(actions,tolua_len);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
  Mtolua_delete_dim(actions);
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCSequence'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCRepeat::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCRepeat00
static int tolua_Cocos2d_CCRepeat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFiniteTimeAction",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFiniteTimeAction* pAction = ((CCFiniteTimeAction*)  tolua_tousertype(tolua_S,1,0));
  unsigned int times = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCRepeat::create(pAction,times);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCRepeat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCRepeatForever::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCRepeatForever00
static int tolua_Cocos2d_CCRepeatForever00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCActionInterval",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCActionInterval* pAction = ((CCActionInterval*)  tolua_tousertype(tolua_S,1,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCRepeatForever::create(pAction);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCRepeatForever'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCSpawn::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCSpawn00
static int tolua_Cocos2d_CCSpawn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_istable(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int tolua_len = lua_objlen(tolua_S,1);
  CCFiniteTimeAction** actions = Mtolua_new_dim(CCFiniteTimeAction*, tolua_len);
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,1,"CCFiniteTimeAction",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    actions[i] = ((CCFiniteTimeAction*)  tolua_tofieldusertype(tolua_S,1,i+1,0));
   }
  }
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCSpawn::create(actions,tolua_len);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
  Mtolua_delete_dim(actions);
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCSpawn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCJumpBy::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCJumpBy00
static int tolua_Cocos2d_CCJumpBy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  oVec2 position = *((oVec2*)  tolua_tousertype(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
  int jumps = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCJumpBy::create(duration,position,height,jumps);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCJumpBy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCJumpTo::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCJumpTo00
static int tolua_Cocos2d_CCJumpTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  oVec2 position = *((oVec2*)  tolua_tousertype(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
  int jumps = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCJumpTo::create(duration,position,height,jumps);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCJumpTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCBezierBy::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBezierBy00
static int tolua_Cocos2d_CCBezierBy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"oVec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float t = ((float)  tolua_tonumber(tolua_S,1,0));
  oVec2* deltaPosition = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
  oVec2* deltaControlA = ((oVec2*)  tolua_tousertype(tolua_S,3,0));
  oVec2* deltaControlB = ((oVec2*)  tolua_tousertype(tolua_S,4,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCBezierBy::create(t,*deltaPosition,*deltaControlA,*deltaControlB);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCBezierBy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCBezierTo::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBezierTo00
static int tolua_Cocos2d_CCBezierTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"oVec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float t = ((float)  tolua_tonumber(tolua_S,1,0));
  oVec2* position = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
  oVec2* controlA = ((oVec2*)  tolua_tousertype(tolua_S,3,0));
  oVec2* controlB = ((oVec2*)  tolua_tousertype(tolua_S,4,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCBezierTo::create(t,*position,*controlA,*controlB);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCBezierTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCBlink::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCBlink00
static int tolua_Cocos2d_CCBlink00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  unsigned int uBlinks = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCBlink::create(duration,uBlinks);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCBlink'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCTintTo::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTintTo00
static int tolua_Cocos2d_CCTintTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  unsigned int colorValue = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCTintTo::create(duration,colorValue);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCTintTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCTintBy::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTintBy00
static int tolua_Cocos2d_CCTintBy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  unsigned int colorValue = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCTintBy::create(duration,colorValue);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCTintBy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCDelayTime::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCDelay00
static int tolua_Cocos2d_CCDelay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float d = ((float)  tolua_tonumber(tolua_S,1,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCDelayTime::create(d);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCDelay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCShow::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCShow00
static int tolua_Cocos2d_CCShow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCFiniteTimeAction* tolua_ret = (CCFiniteTimeAction*)  CCShow::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCFiniteTimeAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCShow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCHide::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCHide00
static int tolua_Cocos2d_CCHide00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCFiniteTimeAction* tolua_ret = (CCFiniteTimeAction*)  CCHide::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCFiniteTimeAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCHide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCToggleVisibility::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCToggleVisibility00
static int tolua_Cocos2d_CCToggleVisibility00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCFiniteTimeAction* tolua_ret = (CCFiniteTimeAction*)  CCToggleVisibility::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCFiniteTimeAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCToggleVisibility'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCFlipY::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCFlipY00
static int tolua_Cocos2d_CCFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isboolean(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool x = ((bool)  tolua_toboolean(tolua_S,1,0));
  {
   CCFiniteTimeAction* tolua_ret = (CCFiniteTimeAction*)  CCFlipY::create(x);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCFiniteTimeAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCFlipY::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCFlipY01
static int tolua_Cocos2d_CCFlipY01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isboolean(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  bool y = ((bool)  tolua_toboolean(tolua_S,1,0));
  {
   CCFiniteTimeAction* tolua_ret = (CCFiniteTimeAction*)  CCFlipY::create(y);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCFiniteTimeAction");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCFlipY00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCPlace::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCPlace00
static int tolua_Cocos2d_CCPlace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oVec2 pos = *((oVec2*)  tolua_tousertype(tolua_S,1,0));
  {
   CCFiniteTimeAction* tolua_ret = (CCFiniteTimeAction*)  CCPlace::create(pos);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCFiniteTimeAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCPlace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCCall::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCCall00
static int tolua_Cocos2d_CCCall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !toluafix_isfunction(tolua_S,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int handler = toluafix_ref_function(tolua_S,1);
  {
   CCFiniteTimeAction* tolua_ret = (CCFiniteTimeAction*)  CCCall::create(handler);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCFiniteTimeAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCCall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCOrbitCamera::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCOrbitCamera00
static int tolua_Cocos2d_CCOrbitCamera00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float t = ((float)  tolua_tonumber(tolua_S,1,0));
  float radius = ((float)  tolua_tonumber(tolua_S,2,0));
  float deltaRadius = ((float)  tolua_tonumber(tolua_S,3,0));
  float angleZ = ((float)  tolua_tonumber(tolua_S,4,0));
  float deltaAngleZ = ((float)  tolua_tonumber(tolua_S,5,0));
  float angleX = ((float)  tolua_tonumber(tolua_S,6,0));
  float deltaAngleX = ((float)  tolua_tonumber(tolua_S,7,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCOrbitCamera::create(t,radius,deltaRadius,angleZ,deltaAngleZ,angleX,deltaAngleX);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCOrbitCamera'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCCardinalSplineTo_create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCCardinalSplineTo00
static int tolua_Cocos2d_CCCardinalSplineTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  int tolua_len = lua_objlen(tolua_S,2);
  oVec2* points = Mtolua_new_dim(oVec2, tolua_len);
  float tension = ((float)  tolua_tonumber(tolua_S,3,0));
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,2,"oVec2",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    points[i] = *((oVec2*)  tolua_tofieldusertype(tolua_S,2,i+1,0));
   }
  }
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCCardinalSplineTo_create(duration,points,tolua_len,tension);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
  Mtolua_delete_dim(points);
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCCardinalSplineTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCCardinalSplineBy_create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCCardinalSplineBy00
static int tolua_Cocos2d_CCCardinalSplineBy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  int tolua_len = lua_objlen(tolua_S,2);
  oVec2* points = Mtolua_new_dim(oVec2, tolua_len);
  float tension = ((float)  tolua_tonumber(tolua_S,3,0));
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,2,"oVec2",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    points[i] = *((oVec2*)  tolua_tofieldusertype(tolua_S,2,i+1,0));
   }
  }
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCCardinalSplineBy_create(duration,points,tolua_len,tension);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
  Mtolua_delete_dim(points);
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCCardinalSplineBy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCCatmullRomTo_create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCCatmullRomTo00
static int tolua_Cocos2d_CCCatmullRomTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  int tolua_len = lua_objlen(tolua_S,2);
  oVec2* points = Mtolua_new_dim(oVec2, tolua_len);
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,2,"oVec2",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    points[i] = *((oVec2*)  tolua_tofieldusertype(tolua_S,2,i+1,0));
   }
  }
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCCatmullRomTo_create(duration,points,tolua_len);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
  Mtolua_delete_dim(points);
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCCatmullRomTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCCatmullRomBy_create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCCatmullRomBy00
static int tolua_Cocos2d_CCCatmullRomBy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  int tolua_len = lua_objlen(tolua_S,2);
  oVec2* points = Mtolua_new_dim(oVec2, tolua_len);
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,2,"oVec2",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    points[i] = *((oVec2*)  tolua_tofieldusertype(tolua_S,2,i+1,0));
   }
  }
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCCatmullRomBy_create(duration,points,tolua_len);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
  Mtolua_delete_dim(points);
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCCatmullRomBy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCStopGrid::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGrid_stop00
static int tolua_Cocos2d_CCGrid_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCFiniteTimeAction* tolua_ret = (CCFiniteTimeAction*)  CCStopGrid::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCFiniteTimeAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCReuseGrid::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGrid_reuse00
static int tolua_Cocos2d_CCGrid_reuse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int times = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   CCFiniteTimeAction* tolua_ret = (CCFiniteTimeAction*)  CCReuseGrid::create(times);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCFiniteTimeAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reuse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCWaves3D::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGrid_waves3D00
static int tolua_Cocos2d_CCGrid_waves3D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  CCSize gridSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  unsigned int waves = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  float amplitude = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCWaves3D::create(duration,gridSize,waves,amplitude);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'waves3D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCFlipX3D::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGrid_flipX3D00
static int tolua_Cocos2d_CCGrid_flipX3D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCFlipX3D::create(duration);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'flipX3D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCFlipY3D::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGrid_flipY3D00
static int tolua_Cocos2d_CCGrid_flipY3D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCFlipY3D::create(duration);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'flipY3D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCLens3D::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGrid_lens3D00
static int tolua_Cocos2d_CCGrid_lens3D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"oVec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  CCSize gridSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  oVec2 position = *((oVec2*)  tolua_tousertype(tolua_S,3,0));
  float radius = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCLens3D::create(duration,gridSize,position,radius);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'lens3D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCRipple3D::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGrid_ripple3D00
static int tolua_Cocos2d_CCGrid_ripple3D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"oVec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  CCSize gridSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  oVec2 position = *((oVec2*)  tolua_tousertype(tolua_S,3,0));
  float radius = ((float)  tolua_tonumber(tolua_S,4,0));
  unsigned int waves = ((unsigned int)  tolua_tonumber(tolua_S,5,0));
  float amplitude = ((float)  tolua_tonumber(tolua_S,6,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCRipple3D::create(duration,gridSize,position,radius,waves,amplitude);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ripple3D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCShaky3D::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGrid_shaky3D00
static int tolua_Cocos2d_CCGrid_shaky3D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  CCSize gridSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  int range = ((int)  tolua_tonumber(tolua_S,3,0));
  bool shakeZ = ((bool)  tolua_toboolean(tolua_S,4,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCShaky3D::create(duration,gridSize,range,shakeZ);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'shaky3D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCLiquid::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGrid_liquid00
static int tolua_Cocos2d_CCGrid_liquid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  CCSize gridSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  unsigned int waves = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  float amplitude = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCLiquid::create(duration,gridSize,waves,amplitude);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'liquid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCWaves::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGrid_waves00
static int tolua_Cocos2d_CCGrid_waves00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  CCSize gridSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  unsigned int waves = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  float amplitude = ((float)  tolua_tonumber(tolua_S,4,0));
  bool horizontal = ((bool)  tolua_toboolean(tolua_S,5,0));
  bool vertical = ((bool)  tolua_toboolean(tolua_S,6,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCWaves::create(duration,gridSize,waves,amplitude,horizontal,vertical);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'waves'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCTwirl::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCGrid_twirl00
static int tolua_Cocos2d_CCGrid_twirl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"oVec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  CCSize gridSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  oVec2 position = *((oVec2*)  tolua_tousertype(tolua_S,3,0));
  unsigned int twirls = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
  float amplitude = ((float)  tolua_tonumber(tolua_S,5,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCTwirl::create(duration,gridSize,position,twirls,amplitude);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'twirl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCShakyTiles3D::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTile_shaky3D00
static int tolua_Cocos2d_CCTile_shaky3D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  CCSize gridSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  int nRange = ((int)  tolua_tonumber(tolua_S,3,0));
  bool bShakeZ = ((bool)  tolua_toboolean(tolua_S,4,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCShakyTiles3D::create(duration,gridSize,nRange,bShakeZ);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'shaky3D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCShatteredTiles3D::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTile_shattered3D00
static int tolua_Cocos2d_CCTile_shattered3D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  CCSize gridSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  int nRange = ((int)  tolua_tonumber(tolua_S,3,0));
  bool bShatterZ = ((bool)  tolua_toboolean(tolua_S,4,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCShatteredTiles3D::create(duration,gridSize,nRange,bShatterZ);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'shattered3D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCShuffleTiles::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTile_shuffle00
static int tolua_Cocos2d_CCTile_shuffle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  CCSize gridSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCShuffleTiles::create(duration,gridSize);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'shuffle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCTile_createFadeOut */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTile_fadeOut00
static int tolua_Cocos2d_CCTile_fadeOut00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  CCSize gridSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  tOrientation orientation = ((tOrientation) (int)  tolua_tonumber(tolua_S,3,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCTile_createFadeOut(duration,gridSize,orientation);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fadeOut'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCTurnOffTiles::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTile_turnOff00
static int tolua_Cocos2d_CCTile_turnOff00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  CCSize gridSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCTurnOffTiles::create(duration,gridSize);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'turnOff'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCWavesTiles3D::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTile_waves3D00
static int tolua_Cocos2d_CCTile_waves3D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  CCSize gridSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  unsigned int waves = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  float amplitude = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCWavesTiles3D::create(duration,gridSize,waves,amplitude);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'waves3D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCJumpTiles3D::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTile_jump3D00
static int tolua_Cocos2d_CCTile_jump3D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  CCSize gridSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  unsigned int numberOfJumps = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  float amplitude = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCJumpTiles3D::create(duration,gridSize,numberOfJumps,amplitude);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'jump3D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCSplitRows::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTile_splitRows00
static int tolua_Cocos2d_CCTile_splitRows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  unsigned int nRows = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCSplitRows::create(duration,nRows);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'splitRows'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCSplitCols::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTile_splitCols00
static int tolua_Cocos2d_CCTile_splitCols00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  unsigned int nCols = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCSplitCols::create(duration,nCols);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'splitCols'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCPageTurn3D::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCPageTurn3D00
static int tolua_Cocos2d_CCPageTurn3D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  CCSize gridSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCPageTurn3D::create(duration,gridSize);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCPageTurn3D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCProgressTo::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCProgressTo00
static int tolua_Cocos2d_CCProgressTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  float fPercent = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCProgressTo::create(duration,fPercent);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCProgressTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CCProgressFromTo::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCProgressFromTo00
static int tolua_Cocos2d_CCProgressFromTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  float fFromPercentage = ((float)  tolua_tonumber(tolua_S,2,0));
  float fToPercentage = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  CCProgressFromTo::create(duration,fFromPercentage,fToPercentage);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CCProgressFromTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: texture of class  CCMotionStreak */
#ifndef TOLUA_DISABLE_tolua_get_CCMotionStreak_texture_ptr
static int tolua_get_CCMotionStreak_texture_ptr(lua_State* tolua_S)
{
  CCMotionStreak* self = (CCMotionStreak*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'texture'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getTexture(),"CCTexture2D");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: texture of class  CCMotionStreak */
#ifndef TOLUA_DISABLE_tolua_set_CCMotionStreak_texture_ptr
static int tolua_set_CCMotionStreak_texture_ptr(lua_State* tolua_S)
{
  CCMotionStreak* self = (CCMotionStreak*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'texture'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setTexture(((CCTexture2D*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: blendFunc of class  CCMotionStreak */
#ifndef TOLUA_DISABLE_tolua_get_CCMotionStreak_blendFunc
static int tolua_get_CCMotionStreak_blendFunc(lua_State* tolua_S)
{
  CCMotionStreak* self = (CCMotionStreak*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blendFunc'",NULL);
#endif
    void* tolua_obj = Mtolua_new((ccBlendFunc)(self->getBlendFunc()));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: blendFunc of class  CCMotionStreak */
#ifndef TOLUA_DISABLE_tolua_set_CCMotionStreak_blendFunc
static int tolua_set_CCMotionStreak_blendFunc(lua_State* tolua_S)
{
  CCMotionStreak* self = (CCMotionStreak*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blendFunc'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccBlendFunc",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setBlendFunc(*((ccBlendFunc*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fastMode of class  CCMotionStreak */
#ifndef TOLUA_DISABLE_tolua_get_CCMotionStreak_fastMode
static int tolua_get_CCMotionStreak_fastMode(lua_State* tolua_S)
{
  CCMotionStreak* self = (CCMotionStreak*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fastMode'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isFastMode());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fastMode of class  CCMotionStreak */
#ifndef TOLUA_DISABLE_tolua_set_CCMotionStreak_fastMode
static int tolua_set_CCMotionStreak_fastMode(lua_State* tolua_S)
{
  CCMotionStreak* self = (CCMotionStreak*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fastMode'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setFastMode(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: startingPositionInitialized of class  CCMotionStreak */
#ifndef TOLUA_DISABLE_tolua_get_CCMotionStreak_startPosInit
static int tolua_get_CCMotionStreak_startPosInit(lua_State* tolua_S)
{
  CCMotionStreak* self = (CCMotionStreak*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'startingPositionInitialized'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isStartingPositionInitialized());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: startingPositionInitialized of class  CCMotionStreak */
#ifndef TOLUA_DISABLE_tolua_set_CCMotionStreak_startPosInit
static int tolua_set_CCMotionStreak_startPosInit(lua_State* tolua_S)
{
  CCMotionStreak* self = (CCMotionStreak*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'startingPositionInitialized'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setStartingPositionInitialized(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: tintWithColor of class  CCMotionStreak */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCMotionStreak_tintWithColor00
static int tolua_Cocos2d_CCMotionStreak_tintWithColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMotionStreak",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMotionStreak* self = (CCMotionStreak*)  tolua_tousertype(tolua_S,1,0);
  ccColor3B colors = *((ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tintWithColor'", NULL);
#endif
  {
   self->tintWithColor(colors);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tintWithColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  CCMotionStreak */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCMotionStreak_reset00
static int tolua_Cocos2d_CCMotionStreak_reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMotionStreak",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMotionStreak* self = (CCMotionStreak*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'", NULL);
#endif
  {
   self->reset();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCMotionStreak */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCMotionStreak_new00_local
static int tolua_Cocos2d_CCMotionStreak_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCMotionStreak",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"ccColor3",0,&tolua_err)) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float fade = ((float)  tolua_tonumber(tolua_S,2,0));
  float minSeg = ((float)  tolua_tonumber(tolua_S,3,0));
  float stroke = ((float)  tolua_tonumber(tolua_S,4,0));
  ccColor3B color = *((ccColor3B*)  tolua_tousertype(tolua_S,5,0));
  const char* path = ((const char*)  tolua_tostring(tolua_S,6,0));
  {
   CCMotionStreak* tolua_ret = (CCMotionStreak*)  CCMotionStreak::create(fade,minSeg,stroke,color,path);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCMotionStreak");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCMotionStreak */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCMotionStreak_new01_local
static int tolua_Cocos2d_CCMotionStreak_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCMotionStreak",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"ccColor3",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,6,"CCTexture2D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float fade = ((float)  tolua_tonumber(tolua_S,2,0));
  float minSeg = ((float)  tolua_tonumber(tolua_S,3,0));
  float stroke = ((float)  tolua_tonumber(tolua_S,4,0));
  ccColor3B color = *((ccColor3B*)  tolua_tousertype(tolua_S,5,0));
  CCTexture2D* texture = ((CCTexture2D*)  tolua_tousertype(tolua_S,6,0));
  {
   CCMotionStreak* tolua_ret = (CCMotionStreak*)  CCMotionStreak::create(fade,minSeg,stroke,color,texture);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCMotionStreak");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCMotionStreak_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: stencil of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_get_CCClippingNode_stencil_ptr
static int tolua_get_CCClippingNode_stencil_ptr(lua_State* tolua_S)
{
  CCClippingNode* self = (CCClippingNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'stencil'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getStencil(),"CCNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: stencil of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_set_CCClippingNode_stencil_ptr
static int tolua_set_CCClippingNode_stencil_ptr(lua_State* tolua_S)
{
  CCClippingNode* self = (CCClippingNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'stencil'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setStencil(((CCNode*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: alphaThreshold of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_get_CCClippingNode_alphaThreshold
static int tolua_get_CCClippingNode_alphaThreshold(lua_State* tolua_S)
{
  CCClippingNode* self = (CCClippingNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'alphaThreshold'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getAlphaThreshold());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: alphaThreshold of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_set_CCClippingNode_alphaThreshold
static int tolua_set_CCClippingNode_alphaThreshold(lua_State* tolua_S)
{
  CCClippingNode* self = (CCClippingNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'alphaThreshold'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setAlphaThreshold(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: inverted of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_get_CCClippingNode_inverted
static int tolua_get_CCClippingNode_inverted(lua_State* tolua_S)
{
  CCClippingNode* self = (CCClippingNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'inverted'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isInverted());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: inverted of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_set_CCClippingNode_inverted
static int tolua_set_CCClippingNode_inverted(lua_State* tolua_S)
{
  CCClippingNode* self = (CCClippingNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'inverted'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setInverted(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCClipNode_new00_local
static int tolua_Cocos2d_CCClipNode_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCClipNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCClippingNode* tolua_ret = (CCClippingNode*)  CCClippingNode::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCClipNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCClipNode_new01_local
static int tolua_Cocos2d_CCClipNode_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCClipNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCNode* pStencil = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  {
   CCClippingNode* tolua_ret = (CCClippingNode*)  CCClippingNode::create(pStencil);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCClipNode");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCClipNode_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: text of class  CCLabelAtlas */
#ifndef TOLUA_DISABLE_tolua_get_CCLabelAtlas_text
static int tolua_get_CCLabelAtlas_text(lua_State* tolua_S)
{
  CCLabelAtlas* self = (CCLabelAtlas*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'text'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->getText());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: text of class  CCLabelAtlas */
#ifndef TOLUA_DISABLE_tolua_set_CCLabelAtlas_text
static int tolua_set_CCLabelAtlas_text(lua_State* tolua_S)
{
  CCLabelAtlas* self = (CCLabelAtlas*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'text'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setText(((char*)  tolua_tostring(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: texture of class  CCLabelAtlas */
#ifndef TOLUA_DISABLE_tolua_get_CCLabelAtlas_texture_ptr
static int tolua_get_CCLabelAtlas_texture_ptr(lua_State* tolua_S)
{
  CCLabelAtlas* self = (CCLabelAtlas*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'texture'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getTexture(),"CCTexture2D");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: texture of class  CCLabelAtlas */
#ifndef TOLUA_DISABLE_tolua_set_CCLabelAtlas_texture_ptr
static int tolua_set_CCLabelAtlas_texture_ptr(lua_State* tolua_S)
{
  CCLabelAtlas* self = (CCLabelAtlas*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'texture'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setTexture(((CCTexture2D*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLabelAtlas */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLabelAtlas_new00_local
static int tolua_Cocos2d_CCLabelAtlas_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLabelAtlas",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* label = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* charMapFile = ((const char*)  tolua_tostring(tolua_S,3,0));
  unsigned int itemWidth = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
  unsigned int itemHeight = ((unsigned int)  tolua_tonumber(tolua_S,5,0));
  unsigned int startCharMap = ((unsigned int)  tolua_tonumber(tolua_S,6,0));
  {
   CCLabelAtlas* tolua_ret = (CCLabelAtlas*)  CCLabelAtlas::create(label,charMapFile,itemWidth,itemHeight,startCharMap);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCLabelAtlas");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLabelAtlas */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLabelAtlas_new01_local
static int tolua_Cocos2d_CCLabelAtlas_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLabelAtlas",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* sring = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* fntFile = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   CCLabelAtlas* tolua_ret = (CCLabelAtlas*)  CCLabelAtlas::create(sring,fntFile);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCLabelAtlas");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCLabelAtlas_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: text of class  CCLabelBMFont */
#ifndef TOLUA_DISABLE_tolua_get_CCLabelBMFont_text
static int tolua_get_CCLabelBMFont_text(lua_State* tolua_S)
{
  CCLabelBMFont* self = (CCLabelBMFont*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'text'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->getText());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: text of class  CCLabelBMFont */
#ifndef TOLUA_DISABLE_tolua_set_CCLabelBMFont_text
static int tolua_set_CCLabelBMFont_text(lua_State* tolua_S)
{
  CCLabelBMFont* self = (CCLabelBMFont*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'text'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setText(((char*)  tolua_tostring(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fntFile of class  CCLabelBMFont */
#ifndef TOLUA_DISABLE_tolua_get_CCLabelBMFont_fntFile
static int tolua_get_CCLabelBMFont_fntFile(lua_State* tolua_S)
{
  CCLabelBMFont* self = (CCLabelBMFont*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fntFile'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->getFntFile());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fntFile of class  CCLabelBMFont */
#ifndef TOLUA_DISABLE_tolua_set_CCLabelBMFont_fntFile
static int tolua_set_CCLabelBMFont_fntFile(lua_State* tolua_S)
{
  CCLabelBMFont* self = (CCLabelBMFont*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fntFile'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setFntFile(((char*)  tolua_tostring(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAlignment of class  CCLabelBMFont */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLabelBMFont_setAlignment00
static int tolua_Cocos2d_CCLabelBMFont_setAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLabelBMFont",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLabelBMFont* self = (CCLabelBMFont*)  tolua_tousertype(tolua_S,1,0);
  CCTextAlignment alignment = ((CCTextAlignment) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAlignment'", NULL);
#endif
  {
   self->setAlignment(alignment);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setWidth of class  CCLabelBMFont */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLabelBMFont_setWidth00
static int tolua_Cocos2d_CCLabelBMFont_setWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLabelBMFont",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLabelBMFont* self = (CCLabelBMFont*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWidth'", NULL);
#endif
  {
   self->setWidth(width);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLineBreakWithoutSpace of class  CCLabelBMFont */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLabelBMFont_setLineBreakWithoutSpace00
static int tolua_Cocos2d_CCLabelBMFont_setLineBreakWithoutSpace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLabelBMFont",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLabelBMFont* self = (CCLabelBMFont*)  tolua_tousertype(tolua_S,1,0);
  bool breakWithoutSpace = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLineBreakWithoutSpace'", NULL);
#endif
  {
   self->setLineBreakWithoutSpace(breakWithoutSpace);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLineBreakWithoutSpace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purgeCachedData of class  CCLabelBMFont */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLabelBMFont_purgeCachedData00
static int tolua_Cocos2d_CCLabelBMFont_purgeCachedData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCLabelBMFont::purgeCachedData();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purgeCachedData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLabelBMFont */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLabelBMFont_new00_local
static int tolua_Cocos2d_CCLabelBMFont_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLabelBMFont",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"oVec2",1,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* fntFile = ((const char*)  tolua_tostring(tolua_S,3,0));
  float width = ((float)  tolua_tonumber(tolua_S,4,kCCLabelAutomaticWidth));
  CCTextAlignment alignment = ((CCTextAlignment) (int)  tolua_tonumber(tolua_S,5,kCCTextAlignmentLeft));
  oVec2 imageOffset = *((oVec2*)  tolua_tousertype(tolua_S,6,(void*)&(const oVec2)oVec2::zero));
  {
   CCLabelBMFont* tolua_ret = (CCLabelBMFont*)  CCLabelBMFont::create(str,fntFile,width,alignment,imageOffset);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCLabelBMFont");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLabelBMFont */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLabelBMFont_new01_local
static int tolua_Cocos2d_CCLabelBMFont_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLabelBMFont",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   CCLabelBMFont* tolua_ret = (CCLabelBMFont*)  CCLabelBMFont::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCLabelBMFont");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCLabelBMFont_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: text of class  CCLabelTTF */
#ifndef TOLUA_DISABLE_tolua_get_CCLabelTTF_text
static int tolua_get_CCLabelTTF_text(lua_State* tolua_S)
{
  CCLabelTTF* self = (CCLabelTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'text'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->getText());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: text of class  CCLabelTTF */
#ifndef TOLUA_DISABLE_tolua_set_CCLabelTTF_text
static int tolua_set_CCLabelTTF_text(lua_State* tolua_S)
{
  CCLabelTTF* self = (CCLabelTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'text'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setText(((char*)  tolua_tostring(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: horizontalAlignment of class  CCLabelTTF */
#ifndef TOLUA_DISABLE_tolua_get_CCLabelTTF_horizontalAlignment
static int tolua_get_CCLabelTTF_horizontalAlignment(lua_State* tolua_S)
{
  CCLabelTTF* self = (CCLabelTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'horizontalAlignment'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getHorizontalAlignment());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: horizontalAlignment of class  CCLabelTTF */
#ifndef TOLUA_DISABLE_tolua_set_CCLabelTTF_horizontalAlignment
static int tolua_set_CCLabelTTF_horizontalAlignment(lua_State* tolua_S)
{
  CCLabelTTF* self = (CCLabelTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'horizontalAlignment'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setHorizontalAlignment(((CCTextAlignment) (int)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: verticalAlignment of class  CCLabelTTF */
#ifndef TOLUA_DISABLE_tolua_get_CCLabelTTF_verticalAlignment
static int tolua_get_CCLabelTTF_verticalAlignment(lua_State* tolua_S)
{
  CCLabelTTF* self = (CCLabelTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'verticalAlignment'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getVerticalAlignment());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: verticalAlignment of class  CCLabelTTF */
#ifndef TOLUA_DISABLE_tolua_set_CCLabelTTF_verticalAlignment
static int tolua_set_CCLabelTTF_verticalAlignment(lua_State* tolua_S)
{
  CCLabelTTF* self = (CCLabelTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'verticalAlignment'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setVerticalAlignment(((CCVerticalTextAlignment) (int)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dimensions of class  CCLabelTTF */
#ifndef TOLUA_DISABLE_tolua_get_CCLabelTTF_dimensions
static int tolua_get_CCLabelTTF_dimensions(lua_State* tolua_S)
{
  CCLabelTTF* self = (CCLabelTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dimensions'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->getDimensions()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dimensions of class  CCLabelTTF */
#ifndef TOLUA_DISABLE_tolua_set_CCLabelTTF_dimensions
static int tolua_set_CCLabelTTF_dimensions(lua_State* tolua_S)
{
  CCLabelTTF* self = (CCLabelTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dimensions'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setDimensions(*((CCSize*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fontSize of class  CCLabelTTF */
#ifndef TOLUA_DISABLE_tolua_get_CCLabelTTF_fontSize
static int tolua_get_CCLabelTTF_fontSize(lua_State* tolua_S)
{
  CCLabelTTF* self = (CCLabelTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fontSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getFontSize());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fontSize of class  CCLabelTTF */
#ifndef TOLUA_DISABLE_tolua_set_CCLabelTTF_fontSize
static int tolua_set_CCLabelTTF_fontSize(lua_State* tolua_S)
{
  CCLabelTTF* self = (CCLabelTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fontSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setFontSize(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fontName of class  CCLabelTTF */
#ifndef TOLUA_DISABLE_tolua_get_CCLabelTTF_fontName
static int tolua_get_CCLabelTTF_fontName(lua_State* tolua_S)
{
  CCLabelTTF* self = (CCLabelTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fontName'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->getFontName());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fontName of class  CCLabelTTF */
#ifndef TOLUA_DISABLE_tolua_set_CCLabelTTF_fontName
static int tolua_set_CCLabelTTF_fontName(lua_State* tolua_S)
{
  CCLabelTTF* self = (CCLabelTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fontName'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setFontName(((char*)  tolua_tostring(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLabelTTF */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLabelTTF_new00_local
static int tolua_Cocos2d_CCLabelTTF_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLabelTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCLabelTTF* tolua_ret = (CCLabelTTF*)  CCLabelTTF::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCLabelTTF");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLabelTTF */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLabelTTF_new01_local
static int tolua_Cocos2d_CCLabelTTF_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLabelTTF",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* fontName = ((const char*)  tolua_tostring(tolua_S,3,0));
  float fontSize = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCLabelTTF* tolua_ret = (CCLabelTTF*)  CCLabelTTF::create(str,fontName,fontSize);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCLabelTTF");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCLabelTTF_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLabelTTF */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCLabelTTF_new02_local
static int tolua_Cocos2d_CCLabelTTF_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLabelTTF",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* fontName = ((const char*)  tolua_tostring(tolua_S,3,0));
  float fontSize = ((float)  tolua_tonumber(tolua_S,4,0));
  CCSize* dimensions = ((CCSize*)  tolua_tousertype(tolua_S,5,0));
  CCTextAlignment hAlignment = ((CCTextAlignment) (int)  tolua_tonumber(tolua_S,6,0));
  CCVerticalTextAlignment vAlignment = ((CCVerticalTextAlignment) (int)  tolua_tonumber(tolua_S,7,kCCVerticalTextAlignmentCenter));
  {
   CCLabelTTF* tolua_ret = (CCLabelTTF*)  CCLabelTTF::create(str,fontName,fontSize,*dimensions,hAlignment,vAlignment);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCLabelTTF");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCLabelTTF_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: enabled of class  CCMenu */
#ifndef TOLUA_DISABLE_tolua_get_CCMenu_enabled
static int tolua_get_CCMenu_enabled(lua_State* tolua_S)
{
  CCMenu* self = (CCMenu*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'enabled'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isEnabled());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: enabled of class  CCMenu */
#ifndef TOLUA_DISABLE_tolua_set_CCMenu_enabled
static int tolua_set_CCMenu_enabled(lua_State* tolua_S)
{
  CCMenu* self = (CCMenu*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'enabled'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setEnabled(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: alignItemsVertically of class  CCMenu */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCMenu_alignItemsVertically00
static int tolua_Cocos2d_CCMenu_alignItemsVertically00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMenu",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMenu* self = (CCMenu*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'alignItemsVertically'", NULL);
#endif
  {
   self->alignItemsVertically();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'alignItemsVertically'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: alignItemsVerticallyWithPadding of class  CCMenu */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCMenu_alignItemsVertically01
static int tolua_Cocos2d_CCMenu_alignItemsVertically01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMenu",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCMenu* self = (CCMenu*)  tolua_tousertype(tolua_S,1,0);
  float padding = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'alignItemsVerticallyWithPadding'", NULL);
#endif
  {
   self->alignItemsVerticallyWithPadding(padding);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_CCMenu_alignItemsVertically00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: alignItemsHorizontally of class  CCMenu */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCMenu_alignItemsHorizontally00
static int tolua_Cocos2d_CCMenu_alignItemsHorizontally00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMenu",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMenu* self = (CCMenu*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'alignItemsHorizontally'", NULL);
#endif
  {
   self->alignItemsHorizontally();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'alignItemsHorizontally'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: alignItemsHorizontallyWithPadding of class  CCMenu */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCMenu_alignItemsHorizontally01
static int tolua_Cocos2d_CCMenu_alignItemsHorizontally01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMenu",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCMenu* self = (CCMenu*)  tolua_tousertype(tolua_S,1,0);
  float padding = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'alignItemsHorizontallyWithPadding'", NULL);
#endif
  {
   self->alignItemsHorizontallyWithPadding(padding);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_CCMenu_alignItemsHorizontally00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHandlerPriority of class  CCMenu */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCMenu_setHandlerPriority00
static int tolua_Cocos2d_CCMenu_setHandlerPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMenu",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMenu* self = (CCMenu*)  tolua_tousertype(tolua_S,1,0);
  int newPriority = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHandlerPriority'", NULL);
#endif
  {
   self->setHandlerPriority(newPriority);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHandlerPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCMenu */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCMenu_new00_local
static int tolua_Cocos2d_CCMenu_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCMenu",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool swallow = ((bool)  tolua_toboolean(tolua_S,2,true));
  {
   CCMenu* tolua_ret = (CCMenu*)  CCMenu::create(swallow);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCMenu");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCMenu */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCMenu_new01_local
static int tolua_Cocos2d_CCMenu_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCArray",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCArray* items = ((CCArray*)  tolua_tousertype(tolua_S,2,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,3,true));
  {
   CCMenu* tolua_ret = (CCMenu*)  CCMenu::createWithArray(items,swallow);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCMenu");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCMenu_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rect of class  CCMenuItem */
#ifndef TOLUA_DISABLE_tolua_get_CCMenuItem_hitArea
static int tolua_get_CCMenuItem_hitArea(lua_State* tolua_S)
{
  CCMenuItem* self = (CCMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rect'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCRect)(self->rect()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: selected of class  CCMenuItem */
#ifndef TOLUA_DISABLE_tolua_get_CCMenuItem_selected
static int tolua_get_CCMenuItem_selected(lua_State* tolua_S)
{
  CCMenuItem* self = (CCMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'selected'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isSelected());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: enabled of class  CCMenuItem */
#ifndef TOLUA_DISABLE_tolua_get_CCMenuItem_enabled
static int tolua_get_CCMenuItem_enabled(lua_State* tolua_S)
{
  CCMenuItem* self = (CCMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'enabled'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isEnabled());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: enabled of class  CCMenuItem */
#ifndef TOLUA_DISABLE_tolua_set_CCMenuItem_enabled
static int tolua_set_CCMenuItem_enabled(lua_State* tolua_S)
{
  CCMenuItem* self = (CCMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'enabled'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setEnabled(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptTapHandler of class  CCMenuItem */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCMenuItem_registerTapHandler00
static int tolua_Cocos2d_CCMenuItem_registerTapHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMenuItem",0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,2,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMenuItem* self = (CCMenuItem*)  tolua_tousertype(tolua_S,1,0);
  int funcID = toluafix_ref_function(tolua_S,2);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptTapHandler'", NULL);
#endif
  {
   self->registerScriptTapHandler(funcID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerTapHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptTapHandler of class  CCMenuItem */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCMenuItem_unregisterTapHandler00
static int tolua_Cocos2d_CCMenuItem_unregisterTapHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMenuItem* self = (CCMenuItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptTapHandler'", NULL);
#endif
  {
   self->unregisterScriptTapHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterTapHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCMenuItem */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCMenuItem_new00_local
static int tolua_Cocos2d_CCMenuItem_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCMenuItem* tolua_ret = (CCMenuItem*)  CCMenuItem::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCMenuItem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  CCParallaxNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCParallaxNode_addChild00
static int tolua_Cocos2d_CCParallaxNode_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCParallaxNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"oVec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCParallaxNode* self = (CCParallaxNode*)  tolua_tousertype(tolua_S,1,0);
  CCNode* child = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  unsigned int z = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  oVec2 ratio = *((oVec2*)  tolua_tousertype(tolua_S,4,0));
  oVec2 offset = *((oVec2*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(child,z,ratio,offset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCParallaxNode */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCParallaxNode_new00_local
static int tolua_Cocos2d_CCParallaxNode_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCParallaxNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCParallaxNode* tolua_ret = (CCParallaxNode*)  CCParallaxNode::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCParallaxNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: midpoint of class  CCProgressTimer */
#ifndef TOLUA_DISABLE_tolua_get_CCProgressTimer_midPoint
static int tolua_get_CCProgressTimer_midPoint(lua_State* tolua_S)
{
  CCProgressTimer* self = (CCProgressTimer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'midpoint'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getMidpoint()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: midpoint of class  CCProgressTimer */
#ifndef TOLUA_DISABLE_tolua_set_CCProgressTimer_midPoint
static int tolua_set_CCProgressTimer_midPoint(lua_State* tolua_S)
{
  CCProgressTimer* self = (CCProgressTimer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'midpoint'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setMidpoint(*((oVec2*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  CCProgressTimer */
#ifndef TOLUA_DISABLE_tolua_get_CCProgressTimer_type
static int tolua_get_CCProgressTimer_type(lua_State* tolua_S)
{
  CCProgressTimer* self = (CCProgressTimer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getType());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  CCProgressTimer */
#ifndef TOLUA_DISABLE_tolua_set_CCProgressTimer_type
static int tolua_set_CCProgressTimer_type(lua_State* tolua_S)
{
  CCProgressTimer* self = (CCProgressTimer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setType(((CCProgressTimerType) (int)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: percentage of class  CCProgressTimer */
#ifndef TOLUA_DISABLE_tolua_get_CCProgressTimer_percentage
static int tolua_get_CCProgressTimer_percentage(lua_State* tolua_S)
{
  CCProgressTimer* self = (CCProgressTimer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'percentage'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getPercentage());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: percentage of class  CCProgressTimer */
#ifndef TOLUA_DISABLE_tolua_set_CCProgressTimer_percentage
static int tolua_set_CCProgressTimer_percentage(lua_State* tolua_S)
{
  CCProgressTimer* self = (CCProgressTimer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'percentage'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setPercentage(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sprite of class  CCProgressTimer */
#ifndef TOLUA_DISABLE_tolua_get_CCProgressTimer_sprite_ptr
static int tolua_get_CCProgressTimer_sprite_ptr(lua_State* tolua_S)
{
  CCProgressTimer* self = (CCProgressTimer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sprite'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getSprite(),"CCSprite");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sprite of class  CCProgressTimer */
#ifndef TOLUA_DISABLE_tolua_set_CCProgressTimer_sprite_ptr
static int tolua_set_CCProgressTimer_sprite_ptr(lua_State* tolua_S)
{
  CCProgressTimer* self = (CCProgressTimer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sprite'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setSprite(((CCSprite*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: barChangeRate of class  CCProgressTimer */
#ifndef TOLUA_DISABLE_tolua_get_CCProgressTimer_barChangeRate
static int tolua_get_CCProgressTimer_barChangeRate(lua_State* tolua_S)
{
  CCProgressTimer* self = (CCProgressTimer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'barChangeRate'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getBarChangeRate()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: barChangeRate of class  CCProgressTimer */
#ifndef TOLUA_DISABLE_tolua_set_CCProgressTimer_barChangeRate
static int tolua_set_CCProgressTimer_barChangeRate(lua_State* tolua_S)
{
  CCProgressTimer* self = (CCProgressTimer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'barChangeRate'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setBarChangeRate(*((oVec2*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: reverseDirection of class  CCProgressTimer */
#ifndef TOLUA_DISABLE_tolua_get_CCProgressTimer_reverseDirection
static int tolua_get_CCProgressTimer_reverseDirection(lua_State* tolua_S)
{
  CCProgressTimer* self = (CCProgressTimer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'reverseDirection'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isReverseDirection());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: reverseDirection of class  CCProgressTimer */
#ifndef TOLUA_DISABLE_tolua_set_CCProgressTimer_reverseDirection
static int tolua_set_CCProgressTimer_reverseDirection(lua_State* tolua_S)
{
  CCProgressTimer* self = (CCProgressTimer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'reverseDirection'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setReverseDirection(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: setReverseProgress of class  CCProgressTimer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCProgressTimer_setReverseProgress00
static int tolua_Cocos2d_CCProgressTimer_setReverseProgress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCProgressTimer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCProgressTimer* self = (CCProgressTimer*)  tolua_tousertype(tolua_S,1,0);
  bool reverse = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setReverseProgress'", NULL);
#endif
  {
   self->setReverseProgress(reverse);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setReverseProgress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCProgressTimer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCProgressTimer_new00_local
static int tolua_Cocos2d_CCProgressTimer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCProgressTimer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSprite* sp = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
  {
   CCProgressTimer* tolua_ret = (CCProgressTimer*)  CCProgressTimer::create(sp);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCProgressTimer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachWithIME of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTextFieldTTF_attachWithIME00
static int tolua_Cocos2d_CCTextFieldTTF_attachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachWithIME'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->attachWithIME();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachWithIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: detachWithIME of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTextFieldTTF_detachWithIME00
static int tolua_Cocos2d_CCTextFieldTTF_detachWithIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'detachWithIME'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->detachWithIME();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'detachWithIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: colorSpaceHolder of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_get_CCTextFieldTTF_colorSpaceHolder
static int tolua_get_CCTextFieldTTF_colorSpaceHolder(lua_State* tolua_S)
{
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'colorSpaceHolder'",NULL);
#endif
    void* tolua_obj = Mtolua_new((ccColor3B)(self->getColorSpaceHolder()));
     tolua_pushusertype(tolua_S,tolua_obj,"ccColor3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: colorSpaceHolder of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_set_CCTextFieldTTF_colorSpaceHolder
static int tolua_set_CCTextFieldTTF_colorSpaceHolder(lua_State* tolua_S)
{
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'colorSpaceHolder'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor3",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setColorSpaceHolder(*((ccColor3B*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: text of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_get_CCTextFieldTTF_text
static int tolua_get_CCTextFieldTTF_text(lua_State* tolua_S)
{
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'text'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->getText());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: text of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_set_CCTextFieldTTF_text
static int tolua_set_CCTextFieldTTF_text(lua_State* tolua_S)
{
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'text'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setText(((char*)  tolua_tostring(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: placeHolder of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_get_CCTextFieldTTF_placeHolder
static int tolua_get_CCTextFieldTTF_placeHolder(lua_State* tolua_S)
{
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'placeHolder'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->getPlaceHolder());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: placeHolder of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_set_CCTextFieldTTF_placeHolder
static int tolua_set_CCTextFieldTTF_placeHolder(lua_State* tolua_S)
{
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'placeHolder'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setPlaceHolder(((char*)  tolua_tostring(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCTextFieldTTF_registerInputHandler of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTextFieldTTF_registerInputHandler00
static int tolua_Cocos2d_CCTextFieldTTF_registerInputHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,2,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
  int handler = toluafix_ref_function(tolua_S,2);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CCTextFieldTTF_registerInputHandler'", NULL);
#endif
  {
   CCTextFieldTTF_registerInputHandler(self,handler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerInputHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CCTextFieldTTF_unregisterInputHandler of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTextFieldTTF_unregisterInputHandler00
static int tolua_Cocos2d_CCTextFieldTTF_unregisterInputHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTextFieldTTF* self = (CCTextFieldTTF*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CCTextFieldTTF_unregisterInputHandler'", NULL);
#endif
  {
   CCTextFieldTTF_unregisterInputHandler(self);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterInputHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCTextFieldTTF */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTextFieldTTF_new00_local
static int tolua_Cocos2d_CCTextFieldTTF_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTextFieldTTF",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* placeholder = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* fontName = ((const char*)  tolua_tostring(tolua_S,3,0));
  float fontSize = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   tolua_outside CCTextFieldTTF* tolua_ret = (tolua_outside CCTextFieldTTF*)  CCTextFieldTTF_create(placeholder,fontName,fontSize);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCTextFieldTTF");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTile of class  CCTileMapAtlas */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTileMapAtlas_setTile00
static int tolua_Cocos2d_CCTileMapAtlas_setTile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTileMapAtlas",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccColor3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTileMapAtlas* self = (CCTileMapAtlas*)  tolua_tousertype(tolua_S,1,0);
  ccColor3B tile = *((ccColor3B*)  tolua_tousertype(tolua_S,2,0));
  oVec2 position = *((oVec2*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTile'", NULL);
#endif
  {
   self->setTile(tile,position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: tileAt of class  CCTileMapAtlas */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTileMapAtlas_getTile00
static int tolua_Cocos2d_CCTileMapAtlas_getTile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTileMapAtlas",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTileMapAtlas* self = (CCTileMapAtlas*)  tolua_tousertype(tolua_S,1,0);
  oVec2* pos = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tileAt'", NULL);
#endif
  {
   ccColor3B tolua_ret = (ccColor3B)  self->tileAt(*pos);
   {
    void* tolua_obj = Mtolua_new((ccColor3B)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ccColor3");
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCTileMapAtlas */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTileMapAtlas_new00_local
static int tolua_Cocos2d_CCTileMapAtlas_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTileMapAtlas",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* tile = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* mapFile = ((const char*)  tolua_tostring(tolua_S,3,0));
  int tileWidth = ((int)  tolua_tonumber(tolua_S,4,0));
  int tileHeight = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   CCTileMapAtlas* tolua_ret = (CCTileMapAtlas*)  CCTileMapAtlas::create(tile,mapFile,tileWidth,tileHeight);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCTileMapAtlas");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: layerSize of class  CCTMXLayer */
#ifndef TOLUA_DISABLE_tolua_get_CCTMXLayer_layerSize
static int tolua_get_CCTMXLayer_layerSize(lua_State* tolua_S)
{
  CCTMXLayer* self = (CCTMXLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'layerSize'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->getLayerSize()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mapTileSize of class  CCTMXLayer */
#ifndef TOLUA_DISABLE_tolua_get_CCTMXLayer_mapTileSize
static int tolua_get_CCTMXLayer_mapTileSize(lua_State* tolua_S)
{
  CCTMXLayer* self = (CCTMXLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mapTileSize'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->getMapTileSize()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: layerName of class  CCTMXLayer */
#ifndef TOLUA_DISABLE_tolua_get_CCTMXLayer_layerName
static int tolua_get_CCTMXLayer_layerName(lua_State* tolua_S)
{
  CCTMXLayer* self = (CCTMXLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'layerName'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->getLayerName());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: tileAt of class  CCTMXLayer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTMXLayer_getTile00
static int tolua_Cocos2d_CCTMXLayer_getTile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTMXLayer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTMXLayer* self = (CCTMXLayer*)  tolua_tousertype(tolua_S,1,0);
  oVec2 tileCoordinate = *((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tileAt'", NULL);
#endif
  {
   CCSprite* tolua_ret = (CCSprite*)  self->tileAt(tileCoordinate);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: tileGIDAt of class  CCTMXLayer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTMXLayer_getTileGID00
static int tolua_Cocos2d_CCTMXLayer_getTileGID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTMXLayer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTMXLayer* self = (CCTMXLayer*)  tolua_tousertype(tolua_S,1,0);
  oVec2* tileCoordinate = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tileGIDAt'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->tileGIDAt(*tileCoordinate);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTileGID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeTileAt of class  CCTMXLayer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTMXLayer_removeTile00
static int tolua_Cocos2d_CCTMXLayer_removeTile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTMXLayer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTMXLayer* self = (CCTMXLayer*)  tolua_tousertype(tolua_S,1,0);
  oVec2 tileCoordinate = *((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeTileAt'", NULL);
#endif
  {
   self->removeTileAt(tileCoordinate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeTile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: positionAt of class  CCTMXLayer */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTMXLayer_getPosition00
static int tolua_Cocos2d_CCTMXLayer_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTMXLayer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTMXLayer* self = (CCTMXLayer*)  tolua_tousertype(tolua_S,1,0);
  oVec2 tileCoordinate = *((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'positionAt'", NULL);
#endif
  {
   oVec2 tolua_ret = (oVec2)  self->positionAt(tileCoordinate);
   {
    void* tolua_obj = Mtolua_new((oVec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mapSize of class  CCTMXTiledMap */
#ifndef TOLUA_DISABLE_tolua_get_CCTMXTiledMap_mapSize
static int tolua_get_CCTMXTiledMap_mapSize(lua_State* tolua_S)
{
  CCTMXTiledMap* self = (CCTMXTiledMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mapSize'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->getMapSize()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tileSize of class  CCTMXTiledMap */
#ifndef TOLUA_DISABLE_tolua_get_CCTMXTiledMap_tileSize
static int tolua_get_CCTMXTiledMap_tileSize(lua_State* tolua_S)
{
  CCTMXTiledMap* self = (CCTMXTiledMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tileSize'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->getTileSize()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mapOrientation of class  CCTMXTiledMap */
#ifndef TOLUA_DISABLE_tolua_get_CCTMXTiledMap_mapOrientation
static int tolua_get_CCTMXTiledMap_mapOrientation(lua_State* tolua_S)
{
  CCTMXTiledMap* self = (CCTMXTiledMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mapOrientation'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getMapOrientation());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: layerNamed of class  CCTMXTiledMap */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTMXTiledMap_getLayer00
static int tolua_Cocos2d_CCTMXTiledMap_getLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTMXTiledMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTMXTiledMap* self = (CCTMXTiledMap*)  tolua_tousertype(tolua_S,1,0);
  const char* layerName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'layerNamed'", NULL);
#endif
  {
   CCTMXLayer* tolua_ret = (CCTMXLayer*)  self->layerNamed(layerName);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCTMXLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCTMXTiledMap */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTMXTiledMap_new00_local
static int tolua_Cocos2d_CCTMXTiledMap_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTMXTiledMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* tmxFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CCTMXTiledMap* tolua_ret = (CCTMXTiledMap*)  CCTMXTiledMap::create(tmxFile);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCTMXTiledMap");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCTMXTiledMap */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_CCTMXTiledMap_new01_local
static int tolua_Cocos2d_CCTMXTiledMap_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCTMXTiledMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* tmxString = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* resourcePath = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   CCTMXTiledMap* tolua_ret = (CCTMXTiledMap*)  CCTMXTiledMap::createWithXML(tmxString,resourcePath);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCTMXTiledMap");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_CCTMXTiledMap_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: location of class  CCTouch */
#ifndef TOLUA_DISABLE_tolua_get_CCTouch_location
static int tolua_get_CCTouch_location(lua_State* tolua_S)
{
  CCTouch* self = (CCTouch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'location'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getLocation()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: previousLocation of class  CCTouch */
#ifndef TOLUA_DISABLE_tolua_get_CCTouch_preLocation
static int tolua_get_CCTouch_preLocation(lua_State* tolua_S)
{
  CCTouch* self = (CCTouch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'previousLocation'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getPreviousLocation()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: delta of class  CCTouch */
#ifndef TOLUA_DISABLE_tolua_get_CCTouch_delta
static int tolua_get_CCTouch_delta(lua_State* tolua_S)
{
  CCTouch* self = (CCTouch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'delta'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getDelta()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: locationInView of class  CCTouch */
#ifndef TOLUA_DISABLE_tolua_get_CCTouch_locationInView
static int tolua_get_CCTouch_locationInView(lua_State* tolua_S)
{
  CCTouch* self = (CCTouch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'locationInView'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getLocationInView()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: previousLocationInView of class  CCTouch */
#ifndef TOLUA_DISABLE_tolua_get_CCTouch_preLocationInView
static int tolua_get_CCTouch_preLocationInView(lua_State* tolua_S)
{
  CCTouch* self = (CCTouch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'previousLocationInView'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getPreviousLocationInView()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iD of class  CCTouch */
#ifndef TOLUA_DISABLE_tolua_get_CCTouch_id
static int tolua_get_CCTouch_id(lua_State* tolua_S)
{
  CCTouch* self = (CCTouch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iD'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getID());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: look of class  oModel */
#ifndef TOLUA_DISABLE_tolua_get_oModel_look
static int tolua_get_oModel_look(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'look'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->getLook());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: look of class  oModel */
#ifndef TOLUA_DISABLE_tolua_set_oModel_look
static int tolua_set_oModel_look(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'look'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setLook(((string)  tolua_tocppstring(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: speed of class  oModel */
#ifndef TOLUA_DISABLE_tolua_get_oModel_speed
static int tolua_get_oModel_speed(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'speed'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getSpeed());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: speed of class  oModel */
#ifndef TOLUA_DISABLE_tolua_set_oModel_speed
static int tolua_set_oModel_speed(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'speed'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setSpeed(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: loop of class  oModel */
#ifndef TOLUA_DISABLE_tolua_get_oModel_loop
static int tolua_get_oModel_loop(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'loop'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isLoop());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: loop of class  oModel */
#ifndef TOLUA_DISABLE_tolua_set_oModel_loop
static int tolua_set_oModel_loop(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'loop'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setLoop(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: time of class  oModel */
#ifndef TOLUA_DISABLE_tolua_get_oModel_time
static int tolua_get_oModel_time(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'time'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getTime());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: time of class  oModel */
#ifndef TOLUA_DISABLE_tolua_set_oModel_time
static int tolua_set_oModel_time(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'time'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setTime(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: duration of class  oModel */
#ifndef TOLUA_DISABLE_tolua_get_oModel_duration
static int tolua_get_oModel_duration(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'duration'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getDuration());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: recovery of class  oModel */
#ifndef TOLUA_DISABLE_tolua_get_oModel_recovery
static int tolua_get_oModel_recovery(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'recovery'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getRecovery());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: recovery of class  oModel */
#ifndef TOLUA_DISABLE_tolua_set_oModel_recovery
static int tolua_set_oModel_recovery(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'recovery'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setRecovery(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: faceRight of class  oModel */
#ifndef TOLUA_DISABLE_tolua_get_oModel_faceRight
static int tolua_get_oModel_faceRight(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'faceRight'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isFaceRight());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: faceRight of class  oModel */
#ifndef TOLUA_DISABLE_tolua_set_oModel_faceRight
static int tolua_set_oModel_faceRight(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'faceRight'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setFaceRight(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: playing of class  oModel */
#ifndef TOLUA_DISABLE_tolua_get_oModel_playing
static int tolua_get_oModel_playing(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'playing'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isPlaying());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: paused of class  oModel */
#ifndef TOLUA_DISABLE_tolua_get_oModel_paused
static int tolua_get_oModel_paused(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'paused'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isPaused());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: currentAnimationName of class  oModel */
#ifndef TOLUA_DISABLE_tolua_get_oModel_currentAnimation
static int tolua_get_oModel_currentAnimation(lua_State* tolua_S)
{
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'currentAnimationName'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->getCurrentAnimationName());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: oModel_addHandler of class  oModel */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oModel_addHandler00
static int tolua_Cocos2d_oModel_addHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oModel",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,3,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  int nHandler = toluafix_ref_function(tolua_S,3);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'oModel_addHandler'", NULL);
#endif
  {
   oModel_addHandler(self,name,nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oModel_removeHandler of class  oModel */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oModel_removeHandler00
static int tolua_Cocos2d_oModel_removeHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oModel",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,3,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  int nHandler = toluafix_ref_function(tolua_S,3);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'oModel_removeHandler'", NULL);
#endif
  {
   oModel_removeHandler(self,name,nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oModel_clearHandler of class  oModel */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oModel_clearHandler00
static int tolua_Cocos2d_oModel_clearHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oModel",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'oModel_clearHandler'", NULL);
#endif
  {
   oModel_clearHandler(self,name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oModel_getKey of class  oModel */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oModel_getKey00
static int tolua_Cocos2d_oModel_getKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
  unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'oModel_getKey'", NULL);
#endif
  {
   tolua_outside oVec2& tolua_ret = (tolua_outside oVec2&)  oModel_getKey(self,index);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"oVec2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  oModel */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oModel_play00
static int tolua_Cocos2d_oModel_play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oModel",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'", NULL);
#endif
  {
   self->play(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pause of class  oModel */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oModel_pause00
static int tolua_Cocos2d_oModel_pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pause'", NULL);
#endif
  {
   self->pause();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resume of class  oModel */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oModel_resume00
static int tolua_Cocos2d_oModel_resume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resume'", NULL);
#endif
  {
   self->resume();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resume of class  oModel */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oModel_resume01
static int tolua_Cocos2d_oModel_resume01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oModel",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resume'", NULL);
#endif
  {
   self->resume(name);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_oModel_resume00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  oModel */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oModel_stop00
static int tolua_Cocos2d_oModel_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stop'", NULL);
#endif
  {
   self->stop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reset of class  oModel */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oModel_reset00
static int tolua_Cocos2d_oModel_reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'", NULL);
#endif
  {
   self->reset();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNodeByName of class  oModel */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oModel_getNodeByName00
static int tolua_Cocos2d_oModel_getNodeByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oModel",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oModel* self = (oModel*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNodeByName'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getNodeByName(name);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNodeByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oModel */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oModel_new00_local
static int tolua_Cocos2d_oModel_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oModel",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   oModel* tolua_ret = (oModel*)  oModel::create(filename);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oModel");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: none of class  oModel */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oModel_none00
static int tolua_Cocos2d_oModel_none00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oModel* tolua_ret = (oModel*)  oModel::none();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oModel");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'none'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLoop of class  oFrameAction */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oFrameAction_setLoop00
static int tolua_Cocos2d_oFrameAction_setLoop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oFrameAction",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oFrameAction* self = (oFrameAction*)  tolua_tousertype(tolua_S,1,0);
  bool loop = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLoop'", NULL);
#endif
  {
   self->setLoop(loop);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLoop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oFrameAction */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oFrameAction_new00_local
static int tolua_Cocos2d_oFrameAction_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oFrameAction",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   oFrameAction* tolua_ret = (oFrameAction*)  oFrameAction::create(filename);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oFrameAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  oFace */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oFace_addChild00
static int tolua_Cocos2d_oFace_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oFace",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"oFace",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oFace* self = (oFace*)  tolua_tousertype(tolua_S,1,0);
  oFace* face = ((oFace*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(face);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeChild of class  oFace */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oFace_removeChild00
static int tolua_Cocos2d_oFace_removeChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oFace",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"oFace",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oFace* self = (oFace*)  tolua_tousertype(tolua_S,1,0);
  oFace* face = ((oFace*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeChild'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->removeChild(face);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: toNode of class  oFace */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oFace_toNode00
static int tolua_Cocos2d_oFace_toNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oFace",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oFace* self = (oFace*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->toNode();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oFace */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oFace_new00_local
static int tolua_Cocos2d_oFace_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oFace",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  string faceStr = ((string)  tolua_tocppstring(tolua_S,2,0));
  oVec2* point = ((oVec2*)  tolua_tousertype(tolua_S,3,0));
  {
   oFace* tolua_ret = (oFace*)  oFace::create(faceStr,*point);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oFace");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: playing of class  oEffect */
#ifndef TOLUA_DISABLE_tolua_get_oEffect_playing
static int tolua_get_oEffect_playing(lua_State* tolua_S)
{
  oEffect* self = (oEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'playing'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isPlaying());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: start of class  oEffect */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oEffect_start00
static int tolua_Cocos2d_oEffect_start00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oEffect* self = (oEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'start'", NULL);
#endif
  {
   self->start();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'start'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  oEffect */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oEffect_stop00
static int tolua_Cocos2d_oEffect_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oEffect* self = (oEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stop'", NULL);
#endif
  {
   self->stop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOffset of class  oEffect */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oEffect_setOffset00
static int tolua_Cocos2d_oEffect_setOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oEffect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oEffect* self = (oEffect*)  tolua_tousertype(tolua_S,1,0);
  oVec2* pos = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOffset'", NULL);
#endif
  {
   oEffect* tolua_ret = (oEffect*)  self->setOffset(*pos);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oEffect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachTo of class  oEffect */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oEffect_attachTo00
static int tolua_Cocos2d_oEffect_attachTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oEffect",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oEffect* self = (oEffect*)  tolua_tousertype(tolua_S,1,0);
  CCNode* parent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachTo'", NULL);
#endif
  {
   oEffect* tolua_ret = (oEffect*)  self->attachTo(parent,zOrder);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oEffect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: autoRemove of class  oEffect */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oEffect_autoRemove00
static int tolua_Cocos2d_oEffect_autoRemove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oEffect* self = (oEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'autoRemove'", NULL);
#endif
  {
   oEffect* tolua_ret = (oEffect*)  self->autoRemove();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oEffect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'autoRemove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oEffect */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oEffect_new00_local
static int tolua_Cocos2d_oEffect_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oEffect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   oEffect* tolua_ret = (oEffect*)  oEffect::create(index);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oEffect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oAnimationCache_load of class  oAnimationCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Animation_load00
static int tolua_Cocos2d_oCache_Animation_load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  oAnimationCache_load(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oAnimationCache_update of class  oAnimationCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Animation_update00
static int tolua_Cocos2d_oCache_Animation_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* content = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  oAnimationCache_update(name,content);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oAnimationCache_unload of class  oAnimationCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Animation_unload00
static int tolua_Cocos2d_oCache_Animation_unload00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Animation",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,nullptr));
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  oAnimationCache_unload(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unload'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oParticleCache_load of class  oParticleCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Particle_load00
static int tolua_Cocos2d_oCache_Particle_load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Particle",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  oParticleCache_load(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oParticleCache_update of class  oParticleCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Particle_update00
static int tolua_Cocos2d_oCache_Particle_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Particle",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* content = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  oParticleCache_update(name,content);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oParticleCache_unload of class  oParticleCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Particle_unload00
static int tolua_Cocos2d_oCache_Particle_unload00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Particle",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,nullptr));
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  oParticleCache_unload(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unload'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oEffectCache_load of class  oEffectCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Effect_load00
static int tolua_Cocos2d_oCache_Effect_load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Effect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  oEffectCache_load(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oEffectCache_update of class  oEffectCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Effect_update00
static int tolua_Cocos2d_oCache_Effect_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Effect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* content = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  oEffectCache_update(content);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oEffectCache_unload of class  oEffectCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Effect_unload00
static int tolua_Cocos2d_oCache_Effect_unload00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Effect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  oEffectCache_unload();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unload'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oModelCache_load of class  oModelCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Model_load00
static int tolua_Cocos2d_oCache_Model_load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Model",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  oModelCache_load(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oModelCache_update of class  oModelCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Model_update00
static int tolua_Cocos2d_oCache_Model_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Model",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* content = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  oModelCache_update(name,content);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oModelCache_unload of class  oModelCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Model_unload00
static int tolua_Cocos2d_oCache_Model_unload00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Model",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,nullptr));
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  oModelCache_unload(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unload'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oModelCache_getData of class  oModelCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Model_getData00
static int tolua_Cocos2d_oCache_Model_getData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Model",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   oModelCache_getData(filename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oModelCache_loadData of class  oModelCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Model_loadData00
static int tolua_Cocos2d_oCache_Model_loadData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Model",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_istable(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  int table_idx = 3;
  {
   oModelCache_loadData(filename,table_idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oModelCache_save of class  oModelCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Model_save00
static int tolua_Cocos2d_oCache_Model_save00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Model",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* itemName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* targetName = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   oModelCache_save(itemName,targetName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'save'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oClipCache_load of class  oClipCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Clip_load00
static int tolua_Cocos2d_oCache_Clip_load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Clip",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  oClipCache_load(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oClipCache_update of class  oClipCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Clip_update00
static int tolua_Cocos2d_oCache_Clip_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Clip",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* content = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  oClipCache_update(name,content);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oClipCache_unload of class  oClipCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Clip_unload00
static int tolua_Cocos2d_oCache_Clip_unload00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Clip",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,nullptr));
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  oClipCache_unload(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unload'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oClipCache_getNames of class  oClipCache */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_Clip_getNames00
static int tolua_Cocos2d_oCache_Clip_getNames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Clip",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   oClipCache_getNames(filename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNames'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: oCache_clear */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCache_clear00
static int tolua_Cocos2d_oCache_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oCache_clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rotationX of class  oNode3D */
#ifndef TOLUA_DISABLE_tolua_get_oNode3D_rotationX
static int tolua_get_oNode3D_rotationX(lua_State* tolua_S)
{
  oNode3D* self = (oNode3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rotationX'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getRotationX());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rotationX of class  oNode3D */
#ifndef TOLUA_DISABLE_tolua_set_oNode3D_rotationX
static int tolua_set_oNode3D_rotationX(lua_State* tolua_S)
{
  oNode3D* self = (oNode3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rotationX'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setRotationX(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rotationY of class  oNode3D */
#ifndef TOLUA_DISABLE_tolua_get_oNode3D_rotationY
static int tolua_get_oNode3D_rotationY(lua_State* tolua_S)
{
  oNode3D* self = (oNode3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rotationY'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getRotationY());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rotationY of class  oNode3D */
#ifndef TOLUA_DISABLE_tolua_set_oNode3D_rotationY
static int tolua_set_oNode3D_rotationY(lua_State* tolua_S)
{
  oNode3D* self = (oNode3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rotationY'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setRotationY(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oNode3D */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oNode3D_new00_local
static int tolua_Cocos2d_oNode3D_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oNode3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oNode3D* tolua_ret = (oNode3D*)  oNode3D::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oNode3D");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: usingGameFile of class  oContent */
#ifndef TOLUA_DISABLE_tolua_get_oContent_useGameFile
static int tolua_get_oContent_useGameFile(lua_State* tolua_S)
{
  oContent* self = (oContent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'usingGameFile'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isUsingGameFile());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: usingGameFile of class  oContent */
#ifndef TOLUA_DISABLE_tolua_set_oContent_useGameFile
static int tolua_set_oContent_useGameFile(lua_State* tolua_S)
{
  oContent* self = (oContent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'usingGameFile'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setUsingGameFile(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: setGameFile of class  oContent */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oContent_setGameFile00
static int tolua_Cocos2d_oContent_setGameFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oContent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oContent* self = (oContent*)  tolua_tousertype(tolua_S,1,0);
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setGameFile'", NULL);
#endif
  {
   self->setGameFile(filename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setGameFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPassword of class  oContent */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oContent_setPassword00
static int tolua_Cocos2d_oContent_setPassword00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oContent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oContent* self = (oContent*)  tolua_tousertype(tolua_S,1,0);
  const char* password = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPassword'", NULL);
#endif
  {
   self->setPassword(password);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPassword'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: saveToFile of class  oContent */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oContent_saveToFile00
static int tolua_Cocos2d_oContent_saveToFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oContent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oContent* self = (oContent*)  tolua_tousertype(tolua_S,1,0);
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* content = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'saveToFile'", NULL);
#endif
  {
   self->saveToFile(filename,content);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'saveToFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oContent_getDirEntries of class  oContent */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oContent_getDirEntries00
static int tolua_Cocos2d_oContent_getDirEntries00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oContent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oContent* self = (oContent*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool isFolder = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'oContent_getDirEntries'", NULL);
#endif
  {
   oContent_getDirEntries(self,path,isFolder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDirEntries'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oContent */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oContent_new00_local
static int tolua_Cocos2d_oContent_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oContent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oContent* tolua_ret = (oContent*)  oContent::shared();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"oContent");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oVec2_new00_local
static int tolua_Cocos2d_oVec2_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oVec2",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0.0f));
  float y = ((float)  tolua_tonumber(tolua_S,3,0.0f));
  {
   oVec2* tolua_ret = (oVec2*)  Mtolua_new((oVec2)(x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"oVec2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oVec2__add00
static int tolua_Cocos2d_oVec2__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oVec2",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
  oVec2* vec = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   oVec2 tolua_ret = (oVec2)  self->operator+(*vec);
   {
    void* tolua_obj = Mtolua_new((oVec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oVec2__sub00
static int tolua_Cocos2d_oVec2__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oVec2",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
  oVec2* vec = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   oVec2 tolua_ret = (oVec2)  self->operator-(*vec);
   {
    void* tolua_obj = Mtolua_new((oVec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oVec2__mul00
static int tolua_Cocos2d_oVec2__mul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oVec2",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   oVec2 tolua_ret = (oVec2)  self->operator*(value);
   {
    void* tolua_obj = Mtolua_new((oVec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.mul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator* of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oVec2__mul01
static int tolua_Cocos2d_oVec2__mul01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oVec2",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
  oVec2* vec = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator*'", NULL);
#endif
  {
   oVec2 tolua_ret = (oVec2)  self->operator*(*vec);
   {
    void* tolua_obj = Mtolua_new((oVec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_oVec2__mul00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator/ of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oVec2__div00
static int tolua_Cocos2d_oVec2__div00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oVec2",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator/'", NULL);
#endif
  {
   oVec2 tolua_ret = (oVec2)  self->operator/(value);
   {
    void* tolua_obj = Mtolua_new((oVec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.div'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oVec2__eq00
static int tolua_Cocos2d_oVec2__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oVec2",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
  oVec2* vec = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*vec);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: distance of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oVec2_distance00
static int tolua_Cocos2d_oVec2_distance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oVec2",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
  oVec2* vec = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'distance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->distance(*vec);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'distance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: distanceSquared of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oVec2_distanceSquared00
static int tolua_Cocos2d_oVec2_distanceSquared00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oVec2",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
  oVec2* vec = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'distanceSquared'", NULL);
#endif
  {
   float tolua_ret = (float)  self->distanceSquared(*vec);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'distanceSquared'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: length of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_get_oVec2_length
static int tolua_get_oVec2_length(lua_State* tolua_S)
{
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'length'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->length());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: lengthSquared of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_get_oVec2_lengthSquared
static int tolua_get_oVec2_lengthSquared(lua_State* tolua_S)
{
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lengthSquared'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->lengthSquared());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: angle of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_get_oVec2_angle
static int tolua_get_oVec2_angle(lua_State* tolua_S)
{
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'angle'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->angle());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: normalize of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oVec2_normalize00
static int tolua_Cocos2d_oVec2_normalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oVec2",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'normalize'", NULL);
#endif
  {
   self->normalize();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'normalize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: x of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_get_oVec2_x
static int tolua_get_oVec2_x(lua_State* tolua_S)
{
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_set_oVec2_x
static int tolua_set_oVec2_x(lua_State* tolua_S)
{
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_get_oVec2_y
static int tolua_get_oVec2_y(lua_State* tolua_S)
{
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_set_oVec2_y
static int tolua_set_oVec2_y(lua_State* tolua_S)
{
  oVec2* self = (oVec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: zero of class  oVec2 */
#ifndef TOLUA_DISABLE_tolua_get_oVec2_zero
static int tolua_get_oVec2_zero(lua_State* tolua_S)
{
    void* tolua_obj = Mtolua_new((oVec2)(oVec2::zero));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: set of class  oLine */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oLine_set00
static int tolua_Cocos2d_oLine_set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oLine",0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oLine* self = (oLine*)  tolua_tousertype(tolua_S,1,0);
  int tolua_len = lua_objlen(tolua_S,2);
  oVec2* vecs = Mtolua_new_dim(oVec2, tolua_len);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set'", NULL);
#endif
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,2,"oVec2",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    vecs[i] = *((oVec2*)  tolua_tofieldusertype(tolua_S,2,i+1,0));
   }
  }
  {
   self->set(vecs,tolua_len);
  }
  Mtolua_delete_dim(vecs);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oLine */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oLine_new00_local
static int tolua_Cocos2d_oLine_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oLine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oLine* tolua_ret = (oLine*)  oLine::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oLine");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oLine */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oLine_new01_local
static int tolua_Cocos2d_oLine_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oLine",0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"ccColor4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int tolua_len = lua_objlen(tolua_S,2);
  oVec2* vecs = Mtolua_new_dim(oVec2, tolua_len);
  ccColor4B* color = ((ccColor4B*)  tolua_tousertype(tolua_S,3,0));
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,2,"oVec2",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    vecs[i] = *((oVec2*)  tolua_tofieldusertype(tolua_S,2,i+1,0));
   }
  }
  {
   oLine* tolua_ret = (oLine*)  oLine::create(vecs,tolua_len,*color);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oLine");
  }
  Mtolua_delete_dim(vecs);
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_oLine_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: name of class  oEvent */
#ifndef TOLUA_DISABLE_tolua_get_oEvent_name
static int tolua_get_oEvent_name(lua_State* tolua_S)
{
  oEvent* self = (oEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->getName());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: addType of class  oEvent */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oEvent_add00
static int tolua_Cocos2d_oEvent_add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oEvent",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  string name = ((string)  tolua_tocppstring(tolua_S,2,0));
  {
   oEvent::addType(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeType of class  oEvent */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oEvent_remove00
static int tolua_Cocos2d_oEvent_remove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oEvent",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  string name = ((string)  tolua_tocppstring(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  oEvent::removeType(name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'remove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: send of class  oEvent */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oEvent_send00
static int tolua_Cocos2d_oEvent_send00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oEvent",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  string name = ((string)  tolua_tocppstring(tolua_S,2,0));
  {
   oEvent::send(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: enabled of class  oListener */
#ifndef TOLUA_DISABLE_tolua_get_oListener_enabled
static int tolua_get_oListener_enabled(lua_State* tolua_S)
{
  oListener* self = (oListener*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'enabled'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isEnabled());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: enabled of class  oListener */
#ifndef TOLUA_DISABLE_tolua_set_oListener_enabled
static int tolua_set_oListener_enabled(lua_State* tolua_S)
{
  oListener* self = (oListener*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'enabled'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setEnabled(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oListener */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oListener_new00_local
static int tolua_Cocos2d_oListener_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oListener",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,3,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  string name = ((string)  tolua_tocppstring(tolua_S,2,0));
  int handler = toluafix_ref_function(tolua_S,3);
  {
   tolua_outside oListener* tolua_ret = (tolua_outside oListener*)  oListener_create(name,handler);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oListener");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: gravity of class  oWorld */
#ifndef TOLUA_DISABLE_tolua_get_oWorld_gravity
static int tolua_get_oWorld_gravity(lua_State* tolua_S)
{
  oWorld* self = (oWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gravity'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getGravity()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: gravity of class  oWorld */
#ifndef TOLUA_DISABLE_tolua_set_oWorld_gravity
static int tolua_set_oWorld_gravity(lua_State* tolua_S)
{
  oWorld* self = (oWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gravity'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setGravity(*((oVec2*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: oWorld_query of class  oWorld */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oWorld_query00
static int tolua_Cocos2d_oWorld_query00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oWorld",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)) ||
     !toluafix_isfunction(tolua_S,3,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oWorld* self = (oWorld*)  tolua_tousertype(tolua_S,1,0);
  CCRect* rect = ((CCRect*)  tolua_tousertype(tolua_S,2,0));
  int nHandler = toluafix_ref_function(tolua_S,3);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'oWorld_query'", NULL);
#endif
  {
   oWorld_query(self,*rect,nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'query'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIterations of class  oWorld */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oWorld_setIterations00
static int tolua_Cocos2d_oWorld_setIterations00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oWorld* self = (oWorld*)  tolua_tousertype(tolua_S,1,0);
  int velocityIter = ((int)  tolua_tonumber(tolua_S,2,0));
  int positionIter = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIterations'", NULL);
#endif
  {
   self->setIterations(velocityIter,positionIter);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIterations'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setShouldContact of class  oWorld */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oWorld_setShouldContact00
static int tolua_Cocos2d_oWorld_setShouldContact00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oWorld* self = (oWorld*)  tolua_tousertype(tolua_S,1,0);
  int groupA = ((int)  tolua_tonumber(tolua_S,2,0));
  int groupB = ((int)  tolua_tonumber(tolua_S,3,0));
  bool contact = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setShouldContact'", NULL);
#endif
  {
   self->setShouldContact(groupA,groupB,contact);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setShouldContact'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getShouldContact of class  oWorld */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oWorld_getShouldContact00
static int tolua_Cocos2d_oWorld_getShouldContact00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oWorld* self = (oWorld*)  tolua_tousertype(tolua_S,1,0);
  int groupA = ((int)  tolua_tonumber(tolua_S,2,0));
  int groupB = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getShouldContact'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getShouldContact(groupA,groupB);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getShouldContact'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: b2Factor of class  oWorld */
#ifndef TOLUA_DISABLE_tolua_get_oWorld_b2Factor
static int tolua_get_oWorld_b2Factor(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)oWorld::b2Factor);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: b2Factor of class  oWorld */
#ifndef TOLUA_DISABLE_tolua_set_oWorld_b2Factor
static int tolua_set_oWorld_b2Factor(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  oWorld::b2Factor = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oWorld */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oWorld_new00_local
static int tolua_Cocos2d_oWorld_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oWorld* tolua_ret = (oWorld*)  oWorld::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oWorld");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_get_oBodyDef_type
static int tolua_get_oBodyDef_type(lua_State* tolua_S)
{
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->type);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_set_oBodyDef_type
static int tolua_set_oBodyDef_type(lua_State* tolua_S)
{
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->type = ((b2BodyType) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: linearDamping of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_get_oBodyDef_linearDamping
static int tolua_get_oBodyDef_linearDamping(lua_State* tolua_S)
{
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'linearDamping'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->linearDamping);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: linearDamping of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_set_oBodyDef_linearDamping
static int tolua_set_oBodyDef_linearDamping(lua_State* tolua_S)
{
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'linearDamping'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->linearDamping = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: angularDamping of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_get_oBodyDef_angularDamping
static int tolua_get_oBodyDef_angularDamping(lua_State* tolua_S)
{
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'angularDamping'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->angularDamping);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: angularDamping of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_set_oBodyDef_angularDamping
static int tolua_set_oBodyDef_angularDamping(lua_State* tolua_S)
{
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'angularDamping'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->angularDamping = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fixedRotation of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_get_oBodyDef_fixedRotation
static int tolua_get_oBodyDef_fixedRotation(lua_State* tolua_S)
{
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fixedRotation'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->fixedRotation);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fixedRotation of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_set_oBodyDef_fixedRotation
static int tolua_set_oBodyDef_fixedRotation(lua_State* tolua_S)
{
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fixedRotation'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fixedRotation = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bullet of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_get_oBodyDef_bullet
static int tolua_get_oBodyDef_bullet(lua_State* tolua_S)
{
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bullet'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->bullet);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bullet of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_set_oBodyDef_bullet
static int tolua_set_oBodyDef_bullet(lua_State* tolua_S)
{
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bullet'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bullet = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: gravityScale of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_get_oBodyDef_gravityScale
static int tolua_get_oBodyDef_gravityScale(lua_State* tolua_S)
{
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gravityScale'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->gravityScale);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: gravityScale of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_set_oBodyDef_gravityScale
static int tolua_set_oBodyDef_gravityScale(lua_State* tolua_S)
{
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gravityScale'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->gravityScale = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: polygon of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_polygon00
static int tolua_Cocos2d_oBodyDef_polygon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oVec2* center = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
  float width = ((float)  tolua_tonumber(tolua_S,3,0));
  float height = ((float)  tolua_tonumber(tolua_S,4,0));
  float angle = ((float)  tolua_tonumber(tolua_S,5,0.0f));
  float density = ((float)  tolua_tonumber(tolua_S,6,0.0f));
  float friction = ((float)  tolua_tonumber(tolua_S,7,0.4f));
  float restitution = ((float)  tolua_tonumber(tolua_S,8,0.0f));
  {
   oFixtureDef* tolua_ret = (oFixtureDef*)  oBodyDef::polygon(*center,width,height,angle,density,friction,restitution);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"oFixtureDef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'polygon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: polygon of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_polygon01
static int tolua_Cocos2d_oBodyDef_polygon01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
  float density = ((float)  tolua_tonumber(tolua_S,4,0.0f));
  float friction = ((float)  tolua_tonumber(tolua_S,5,0.4f));
  float restitution = ((float)  tolua_tonumber(tolua_S,6,0.0f));
  {
   oFixtureDef* tolua_ret = (oFixtureDef*)  oBodyDef::polygon(width,height,density,friction,restitution);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"oFixtureDef");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_oBodyDef_polygon00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: polygon of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_polygon02
static int tolua_Cocos2d_oBodyDef_polygon02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int tolua_len = lua_objlen(tolua_S,2);
  oVec2* vertices = Mtolua_new_dim(oVec2, tolua_len);
  float density = ((float)  tolua_tonumber(tolua_S,3,0.0f));
  float friction = ((float)  tolua_tonumber(tolua_S,4,0.4f));
  float restitution = ((float)  tolua_tonumber(tolua_S,5,0.0f));
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,2,"oVec2",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    vertices[i] = *((oVec2*)  tolua_tofieldusertype(tolua_S,2,i+1,0));
   }
  }
  {
   oFixtureDef* tolua_ret = (oFixtureDef*)  oBodyDef::polygon(vertices,tolua_len,density,friction,restitution);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"oFixtureDef");
  }
  Mtolua_delete_dim(vertices);
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_oBodyDef_polygon01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachPolygon of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_attachPolygon00
static int tolua_Cocos2d_oBodyDef_attachPolygon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
  oVec2* center = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
  float width = ((float)  tolua_tonumber(tolua_S,3,0));
  float height = ((float)  tolua_tonumber(tolua_S,4,0));
  float angle = ((float)  tolua_tonumber(tolua_S,5,0.0f));
  float density = ((float)  tolua_tonumber(tolua_S,6,0.0f));
  float friction = ((float)  tolua_tonumber(tolua_S,7,0.4f));
  float restitution = ((float)  tolua_tonumber(tolua_S,8,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachPolygon'", NULL);
#endif
  {
   self->attachPolygon(*center,width,height,angle,density,friction,restitution);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachPolygon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachPolygon of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_attachPolygon01
static int tolua_Cocos2d_oBodyDef_attachPolygon01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
  float density = ((float)  tolua_tonumber(tolua_S,4,0.0f));
  float friction = ((float)  tolua_tonumber(tolua_S,5,0.4f));
  float restitution = ((float)  tolua_tonumber(tolua_S,6,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachPolygon'", NULL);
#endif
  {
   self->attachPolygon(width,height,density,friction,restitution);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_oBodyDef_attachPolygon00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachPolygon of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_attachPolygon02
static int tolua_Cocos2d_oBodyDef_attachPolygon02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
  int tolua_len = lua_objlen(tolua_S,2);
  oVec2* vertices = Mtolua_new_dim(oVec2, tolua_len);
  float density = ((float)  tolua_tonumber(tolua_S,3,0.0f));
  float friction = ((float)  tolua_tonumber(tolua_S,4,0.4f));
  float restitution = ((float)  tolua_tonumber(tolua_S,5,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachPolygon'", NULL);
#endif
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,2,"oVec2",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    vertices[i] = *((oVec2*)  tolua_tofieldusertype(tolua_S,2,i+1,0));
   }
  }
  {
   self->attachPolygon(vertices,tolua_len,density,friction,restitution);
  }
  Mtolua_delete_dim(vertices);
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_oBodyDef_attachPolygon01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: loop of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_loop00
static int tolua_Cocos2d_oBodyDef_loop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int tolua_len = lua_objlen(tolua_S,2);
  oVec2* vertices = Mtolua_new_dim(oVec2, tolua_len);
  float friction = ((float)  tolua_tonumber(tolua_S,3,0.4f));
  float restitution = ((float)  tolua_tonumber(tolua_S,4,0.0f));
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,2,"oVec2",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    vertices[i] = *((oVec2*)  tolua_tofieldusertype(tolua_S,2,i+1,0));
   }
  }
  {
   oFixtureDef* tolua_ret = (oFixtureDef*)  oBodyDef::loop(vertices,tolua_len,friction,restitution);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"oFixtureDef");
  }
  Mtolua_delete_dim(vertices);
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachLoop of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_attachLoop00
static int tolua_Cocos2d_oBodyDef_attachLoop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
  int tolua_len = lua_objlen(tolua_S,2);
  oVec2* vertices = Mtolua_new_dim(oVec2, tolua_len);
  float friction = ((float)  tolua_tonumber(tolua_S,3,0.4f));
  float restitution = ((float)  tolua_tonumber(tolua_S,4,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachLoop'", NULL);
#endif
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,2,"oVec2",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    vertices[i] = *((oVec2*)  tolua_tofieldusertype(tolua_S,2,i+1,0));
   }
  }
  {
   self->attachLoop(vertices,tolua_len,friction,restitution);
  }
  Mtolua_delete_dim(vertices);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachLoop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: circle of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_circle00
static int tolua_Cocos2d_oBodyDef_circle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oVec2* center = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
  float radius = ((float)  tolua_tonumber(tolua_S,3,0));
  float density = ((float)  tolua_tonumber(tolua_S,4,0.0f));
  float friction = ((float)  tolua_tonumber(tolua_S,5,0.4f));
  float restitution = ((float)  tolua_tonumber(tolua_S,6,0.0f));
  {
   oFixtureDef* tolua_ret = (oFixtureDef*)  oBodyDef::circle(*center,radius,density,friction,restitution);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"oFixtureDef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'circle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: circle of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_circle01
static int tolua_Cocos2d_oBodyDef_circle01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float radius = ((float)  tolua_tonumber(tolua_S,2,0));
  float density = ((float)  tolua_tonumber(tolua_S,3,0.0f));
  float friction = ((float)  tolua_tonumber(tolua_S,4,0.4f));
  float restitution = ((float)  tolua_tonumber(tolua_S,5,0.0f));
  {
   oFixtureDef* tolua_ret = (oFixtureDef*)  oBodyDef::circle(radius,density,friction,restitution);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"oFixtureDef");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_oBodyDef_circle00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachCircle of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_attachCircle00
static int tolua_Cocos2d_oBodyDef_attachCircle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
  oVec2* center = ((oVec2*)  tolua_tousertype(tolua_S,2,0));
  float radius = ((float)  tolua_tonumber(tolua_S,3,0));
  float density = ((float)  tolua_tonumber(tolua_S,4,0.0f));
  float friction = ((float)  tolua_tonumber(tolua_S,5,0.4f));
  float restitution = ((float)  tolua_tonumber(tolua_S,6,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachCircle'", NULL);
#endif
  {
   self->attachCircle(*center,radius,density,friction,restitution);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachCircle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachCircle of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_attachCircle01
static int tolua_Cocos2d_oBodyDef_attachCircle01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
  float radius = ((float)  tolua_tonumber(tolua_S,2,0));
  float density = ((float)  tolua_tonumber(tolua_S,3,0.0f));
  float friction = ((float)  tolua_tonumber(tolua_S,4,0.4f));
  float restitution = ((float)  tolua_tonumber(tolua_S,5,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachCircle'", NULL);
#endif
  {
   self->attachCircle(radius,density,friction,restitution);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_oBodyDef_attachCircle00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: chain of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_chain00
static int tolua_Cocos2d_oBodyDef_chain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int tolua_len = lua_objlen(tolua_S,2);
  oVec2* vertices = Mtolua_new_dim(oVec2, tolua_len);
  float friction = ((float)  tolua_tonumber(tolua_S,3,0.4f));
  float restitution = ((float)  tolua_tonumber(tolua_S,4,0.0f));
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,2,"oVec2",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    vertices[i] = *((oVec2*)  tolua_tofieldusertype(tolua_S,2,i+1,0));
   }
  }
  {
   oFixtureDef* tolua_ret = (oFixtureDef*)  oBodyDef::chain(vertices,tolua_len,friction,restitution);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"oFixtureDef");
  }
  Mtolua_delete_dim(vertices);
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'chain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachChain of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_attachChain00
static int tolua_Cocos2d_oBodyDef_attachChain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
  int tolua_len = lua_objlen(tolua_S,2);
  oVec2* vertices = Mtolua_new_dim(oVec2, tolua_len);
  float friction = ((float)  tolua_tonumber(tolua_S,3,0.4f));
  float restitution = ((float)  tolua_tonumber(tolua_S,4,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachChain'", NULL);
#endif
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,2,"oVec2",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    vertices[i] = *((oVec2*)  tolua_tofieldusertype(tolua_S,2,i+1,0));
   }
  }
  {
   self->attachChain(vertices,tolua_len,friction,restitution);
  }
  Mtolua_delete_dim(vertices);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachChain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachPolygonSensor of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_attachPolygonSensor00
static int tolua_Cocos2d_oBodyDef_attachPolygonSensor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  float width = ((float)  tolua_tonumber(tolua_S,3,0));
  float height = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachPolygonSensor'", NULL);
#endif
  {
   self->attachPolygonSensor(tag,width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachPolygonSensor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachPolygonSensor of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_attachPolygonSensor01
static int tolua_Cocos2d_oBodyDef_attachPolygonSensor01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"oVec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  float width = ((float)  tolua_tonumber(tolua_S,3,0));
  float height = ((float)  tolua_tonumber(tolua_S,4,0));
  oVec2* center = ((oVec2*)  tolua_tousertype(tolua_S,5,0));
  float angle = ((float)  tolua_tonumber(tolua_S,6,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachPolygonSensor'", NULL);
#endif
  {
   self->attachPolygonSensor(tag,width,height,*center,angle);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_oBodyDef_attachPolygonSensor00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachPolygonSensor of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_attachPolygonSensor02
static int tolua_Cocos2d_oBodyDef_attachPolygonSensor02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_istable(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  int tolua_len = lua_objlen(tolua_S,3);
  oVec2* vertices = Mtolua_new_dim(oVec2, tolua_len);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachPolygonSensor'", NULL);
#endif
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isusertypearray(tolua_S,3,"oVec2",tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    vertices[i] = *((oVec2*)  tolua_tofieldusertype(tolua_S,3,i+1,0));
   }
  }
  {
   self->attachPolygonSensor(tag,vertices,tolua_len);
  }
  Mtolua_delete_dim(vertices);
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_oBodyDef_attachPolygonSensor01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachCircleSensor of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_attachCircleSensor00
static int tolua_Cocos2d_oBodyDef_attachCircleSensor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"oVec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  oVec2* center = ((oVec2*)  tolua_tousertype(tolua_S,3,0));
  float radius = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachCircleSensor'", NULL);
#endif
  {
   self->attachCircleSensor(tag,*center,radius);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachCircleSensor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachCircleSensor of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_attachCircleSensor01
static int tolua_Cocos2d_oBodyDef_attachCircleSensor01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  float radius = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachCircleSensor'", NULL);
#endif
  {
   self->attachCircleSensor(tag,radius);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_oBodyDef_attachCircleSensor00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_new00_local
static int tolua_Cocos2d_oBodyDef_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oBodyDef* tolua_ret = (oBodyDef*)  oBodyDef::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oBodyDef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: toBody of class  oBodyDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBodyDef_toBody00
static int tolua_Cocos2d_oBodyDef_toBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBodyDef",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"oWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBodyDef* self = (oBodyDef*)  tolua_tousertype(tolua_S,1,0);
  oWorld* world = ((oWorld*)  tolua_tousertype(tolua_S,2,0));
  int group = ((int)  tolua_tonumber(tolua_S,3,0));
  float x = ((float)  tolua_tonumber(tolua_S,4,0));
  float y = ((float)  tolua_tonumber(tolua_S,5,0));
  float angle = ((float)  tolua_tonumber(tolua_S,6,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toBody'", NULL);
#endif
  {
   oBody* tolua_ret = (oBody*)  self->toBody(world,group,x,y,angle);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oBody");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: world of class  oBody */
#ifndef TOLUA_DISABLE_tolua_get_oBody_world_ptr
static int tolua_get_oBody_world_ptr(lua_State* tolua_S)
{
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'world'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getWorld(),"oWorld");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bodyDef of class  oBody */
#ifndef TOLUA_DISABLE_tolua_get_oBody_bodyDef_ptr
static int tolua_get_oBody_bodyDef_ptr(lua_State* tolua_S)
{
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bodyDef'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getBodyDef(),"oBodyDef");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: velocityX of class  oBody */
#ifndef TOLUA_DISABLE_tolua_get_oBody_velocityX
static int tolua_get_oBody_velocityX(lua_State* tolua_S)
{
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'velocityX'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getVelocityX());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: velocityX of class  oBody */
#ifndef TOLUA_DISABLE_tolua_set_oBody_velocityX
static int tolua_set_oBody_velocityX(lua_State* tolua_S)
{
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'velocityX'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setVelocityX(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: velocityY of class  oBody */
#ifndef TOLUA_DISABLE_tolua_get_oBody_velocityY
static int tolua_get_oBody_velocityY(lua_State* tolua_S)
{
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'velocityY'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getVelocityY());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: velocityY of class  oBody */
#ifndef TOLUA_DISABLE_tolua_set_oBody_velocityY
static int tolua_set_oBody_velocityY(lua_State* tolua_S)
{
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'velocityY'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setVelocityY(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: velocity of class  oBody */
#ifndef TOLUA_DISABLE_tolua_get_oBody_velocity
static int tolua_get_oBody_velocity(lua_State* tolua_S)
{
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'velocity'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getVelocity()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: velocity of class  oBody */
#ifndef TOLUA_DISABLE_tolua_set_oBody_velocity
static int tolua_set_oBody_velocity(lua_State* tolua_S)
{
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'velocity'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setVelocity(*((oVec2*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: group of class  oBody */
#ifndef TOLUA_DISABLE_tolua_get_oBody_group
static int tolua_get_oBody_group(lua_State* tolua_S)
{
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'group'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getGroup());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: group of class  oBody */
#ifndef TOLUA_DISABLE_tolua_set_oBody_group
static int tolua_set_oBody_group(lua_State* tolua_S)
{
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'group'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setGroup(((int)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSensorByTag of class  oBody */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBody_getSensorByTag00
static int tolua_Cocos2d_oBody_getSensorByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSensorByTag'", NULL);
#endif
  {
   oSensor* tolua_ret = (oSensor*)  self->getSensorByTag(tag);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oSensor");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSensorByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeSensorByTag of class  oBody */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBody_removeSensorByTag00
static int tolua_Cocos2d_oBody_removeSensorByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeSensorByTag'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->removeSensorByTag(tag);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeSensorByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeSensor of class  oBody */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBody_removeSensor00
static int tolua_Cocos2d_oBody_removeSensor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"oSensor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
  oSensor* sensor = ((oSensor*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeSensor'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->removeSensor(sensor);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeSensor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attach of class  oBody */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBody_attach00
static int tolua_Cocos2d_oBody_attach00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"oFixtureDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
  oFixtureDef* fixtureDef = ((oFixtureDef*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attach'", NULL);
#endif
  {
   self->attach(fixtureDef);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attach'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachSensor of class  oBody */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBody_attachSensor00
static int tolua_Cocos2d_oBody_attachSensor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"oFixtureDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
  int tag = ((int)  tolua_tonumber(tolua_S,2,0));
  oFixtureDef* fixtureDef = ((oFixtureDef*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachSensor'", NULL);
#endif
  {
   oSensor* tolua_ret = (oSensor*)  self->attachSensor(tag,fixtureDef);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oSensor");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachSensor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy of class  oBody */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBody_destroy00
static int tolua_Cocos2d_oBody_destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBody* self = (oBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'destroy'", NULL);
#endif
  {
   self->destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: enabled of class  oSensor */
#ifndef TOLUA_DISABLE_tolua_get_oSensor_enabled
static int tolua_get_oSensor_enabled(lua_State* tolua_S)
{
  oSensor* self = (oSensor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'enabled'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isEnabled());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: enabled of class  oSensor */
#ifndef TOLUA_DISABLE_tolua_set_oSensor_enabled
static int tolua_set_oSensor_enabled(lua_State* tolua_S)
{
  oSensor* self = (oSensor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'enabled'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setEnabled(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tag of class  oSensor */
#ifndef TOLUA_DISABLE_tolua_get_oSensor_tag
static int tolua_get_oSensor_tag(lua_State* tolua_S)
{
  oSensor* self = (oSensor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tag'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getTag());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: owner of class  oSensor */
#ifndef TOLUA_DISABLE_tolua_get_oSensor_owner_ptr
static int tolua_get_oSensor_owner_ptr(lua_State* tolua_S)
{
  oSensor* self = (oSensor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'owner'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getOwner(),"oBody");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sensed of class  oSensor */
#ifndef TOLUA_DISABLE_tolua_get_oSensor_sensed
static int tolua_get_oSensor_sensed(lua_State* tolua_S)
{
  oSensor* self = (oSensor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sensed'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isSensed());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sensedBodies of class  oSensor */
#ifndef TOLUA_DISABLE_tolua_get_oSensor_sensedBodies_ptr
static int tolua_get_oSensor_sensedBodies_ptr(lua_State* tolua_S)
{
  oSensor* self = (oSensor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sensedBodies'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getSensedBodies(),"CCArray");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: oSensor_addHandler of class  oSensor */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oSensor_addHandler00
static int tolua_Cocos2d_oSensor_addHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oSensor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,3,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oSensor* self = (oSensor*)  tolua_tousertype(tolua_S,1,0);
  unsigned int flag = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  int nHandler = toluafix_ref_function(tolua_S,3);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'oSensor_addHandler'", NULL);
#endif
  {
   oSensor_addHandler(self,flag,nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oSensor_removeHandler of class  oSensor */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oSensor_removeHandler00
static int tolua_Cocos2d_oSensor_removeHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oSensor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,3,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oSensor* self = (oSensor*)  tolua_tousertype(tolua_S,1,0);
  unsigned int flag = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  int nHandler = toluafix_ref_function(tolua_S,3);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'oSensor_removeHandler'", NULL);
#endif
  {
   oSensor_removeHandler(self,flag,nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oSensor_clearHandler of class  oSensor */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oSensor_clearHandler00
static int tolua_Cocos2d_oSensor_clearHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oSensor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oSensor* self = (oSensor*)  tolua_tousertype(tolua_S,1,0);
  unsigned int flag = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'oSensor_clearHandler'", NULL);
#endif
  {
   oSensor_clearHandler(self,flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: contains of class  oSensor */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oSensor_contains00
static int tolua_Cocos2d_oSensor_contains00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oSensor",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"oBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oSensor* self = (oSensor*)  tolua_tousertype(tolua_S,1,0);
  oBody* body = ((oBody*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'contains'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->contains(body);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'contains'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: func of class  oEase */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oEase_func00
static int tolua_Cocos2d_oEase_func00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oEase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
  float begin = ((float)  tolua_tonumber(tolua_S,4,0));
  float change = ((float)  tolua_tonumber(tolua_S,5,0));
  {
   float tolua_ret = (float)  oEase::func(id,time,begin,change);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'func'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: oKeyPos::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oPos00
static int tolua_Cocos2d_oPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  float posX = ((float)  tolua_tonumber(tolua_S,2,0));
  float posY = ((float)  tolua_tonumber(tolua_S,3,0));
  unsigned char easeId = ((unsigned char)  tolua_tonumber(tolua_S,4,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  oKeyPos::create(duration,posX,posY,easeId);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'oPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: oKeyScale::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oScale00
static int tolua_Cocos2d_oScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  float scaleX = ((float)  tolua_tonumber(tolua_S,2,0));
  float scaleY = ((float)  tolua_tonumber(tolua_S,3,0));
  unsigned char easeId = ((unsigned char)  tolua_tonumber(tolua_S,4,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  oKeyScale::create(duration,scaleX,scaleY,easeId);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'oScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: oKeyRotate::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oRotate00
static int tolua_Cocos2d_oRotate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  float rotate = ((float)  tolua_tonumber(tolua_S,2,0));
  unsigned char easeId = ((unsigned char)  tolua_tonumber(tolua_S,3,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  oKeyRotate::create(duration,rotate,easeId);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'oRotate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: oKeyOpacity::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oOpacity00
static int tolua_Cocos2d_oOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  float opacity = ((float)  tolua_tonumber(tolua_S,2,0));
  unsigned char easeId = ((unsigned char)  tolua_tonumber(tolua_S,3,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  oKeyOpacity::create(duration,opacity,easeId);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'oOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: oKeySkew::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oSkew00
static int tolua_Cocos2d_oSkew00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  float skewX = ((float)  tolua_tonumber(tolua_S,2,0));
  float skewY = ((float)  tolua_tonumber(tolua_S,3,0));
  unsigned char easeId = ((unsigned char)  tolua_tonumber(tolua_S,4,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  oKeySkew::create(duration,skewX,skewY,easeId);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'oSkew'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: oKeyRoll::create */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oRoll00
static int tolua_Cocos2d_oRoll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,1,0));
  float roll = ((float)  tolua_tonumber(tolua_S,2,0));
  unsigned char easeId = ((unsigned char)  tolua_tonumber(tolua_S,3,0));
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  oKeyRoll::create(duration,roll,easeId);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'oRoll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: boudary of class  oCamera */
#ifndef TOLUA_DISABLE_tolua_get_oCamera_boudary
static int tolua_get_oCamera_boudary(lua_State* tolua_S)
{
  oCamera* self = (oCamera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'boudary'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCRect)(self->getBoudary()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: boudary of class  oCamera */
#ifndef TOLUA_DISABLE_tolua_set_oCamera_boudary
static int tolua_set_oCamera_boudary(lua_State* tolua_S)
{
  oCamera* self = (oCamera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'boudary'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setBoudary(*((CCRect*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: view of class  oCamera */
#ifndef TOLUA_DISABLE_tolua_get_oCamera_view
static int tolua_get_oCamera_view(lua_State* tolua_S)
{
  oCamera* self = (oCamera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'view'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->getView()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: view of class  oCamera */
#ifndef TOLUA_DISABLE_tolua_set_oCamera_view
static int tolua_set_oCamera_view(lua_State* tolua_S)
{
  oCamera* self = (oCamera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'view'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setView(*((CCSize*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: followRatio of class  oCamera */
#ifndef TOLUA_DISABLE_tolua_get_oCamera_followRatio
static int tolua_get_oCamera_followRatio(lua_State* tolua_S)
{
  oCamera* self = (oCamera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'followRatio'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getFollowRatio()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: followRatio of class  oCamera */
#ifndef TOLUA_DISABLE_tolua_set_oCamera_followRatio
static int tolua_set_oCamera_followRatio(lua_State* tolua_S)
{
  oCamera* self = (oCamera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'followRatio'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setFollowRatio(*((oVec2*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: follow of class  oCamera */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCamera_follow00
static int tolua_Cocos2d_oCamera_follow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oCamera",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oCamera* self = (oCamera*)  tolua_tousertype(tolua_S,1,0);
  CCNode* target = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'follow'", NULL);
#endif
  {
   self->follow(target);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'follow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: camera of class  oPlatformWorld */
#ifndef TOLUA_DISABLE_tolua_get_oPlatformWorld_camera_ptr
static int tolua_get_oPlatformWorld_camera_ptr(lua_State* tolua_S)
{
  oPlatformWorld* self = (oPlatformWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'camera'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getCamera(),"oCamera");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UILayer of class  oPlatformWorld */
#ifndef TOLUA_DISABLE_tolua_get_oPlatformWorld_UILayer_ptr
static int tolua_get_oPlatformWorld_UILayer_ptr(lua_State* tolua_S)
{
  oPlatformWorld* self = (oPlatformWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UILayer'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getUILayer(),"CCNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLayer of class  oPlatformWorld */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oPlatformWorld_getLayer00
static int tolua_Cocos2d_oPlatformWorld_getLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oPlatformWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oPlatformWorld* self = (oPlatformWorld*)  tolua_tousertype(tolua_S,1,0);
  int zOrder = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLayer'", NULL);
#endif
  {
   oLayer* tolua_ret = (oLayer*)  self->getLayer(zOrder);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"oLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeLayer of class  oPlatformWorld */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oPlatformWorld_removeLayer00
static int tolua_Cocos2d_oPlatformWorld_removeLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oPlatformWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oPlatformWorld* self = (oPlatformWorld*)  tolua_tousertype(tolua_S,1,0);
  int zOrder = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeLayer'", NULL);
#endif
  {
   self->removeLayer(zOrder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllLayers of class  oPlatformWorld */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oPlatformWorld_removeAllLayers00
static int tolua_Cocos2d_oPlatformWorld_removeAllLayers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oPlatformWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oPlatformWorld* self = (oPlatformWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllLayers'", NULL);
#endif
  {
   self->removeAllLayers();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllLayers'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLayerRatio of class  oPlatformWorld */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oPlatformWorld_setLayerRatio00
static int tolua_Cocos2d_oPlatformWorld_setLayerRatio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oPlatformWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oPlatformWorld* self = (oPlatformWorld*)  tolua_tousertype(tolua_S,1,0);
  int zOrder = ((int)  tolua_tonumber(tolua_S,2,0));
  oVec2* ratio = ((oVec2*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLayerRatio'", NULL);
#endif
  {
   self->setLayerRatio(zOrder,*ratio);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLayerRatio'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLayerRatio of class  oPlatformWorld */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oPlatformWorld_getLayerRatio00
static int tolua_Cocos2d_oPlatformWorld_getLayerRatio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oPlatformWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oPlatformWorld* self = (oPlatformWorld*)  tolua_tousertype(tolua_S,1,0);
  int zOrder = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLayerRatio'", NULL);
#endif
  {
   oVec2& tolua_ret = (oVec2&)  self->getLayerRatio(zOrder);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"oVec2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLayerRatio'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLayerOffset of class  oPlatformWorld */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oPlatformWorld_setLayerOffset00
static int tolua_Cocos2d_oPlatformWorld_setLayerOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oPlatformWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"oVec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oPlatformWorld* self = (oPlatformWorld*)  tolua_tousertype(tolua_S,1,0);
  int zOrder = ((int)  tolua_tonumber(tolua_S,2,0));
  oVec2* offset = ((oVec2*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLayerOffset'", NULL);
#endif
  {
   self->setLayerOffset(zOrder,*offset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLayerOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLayerOffset of class  oPlatformWorld */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oPlatformWorld_getLayerOffset00
static int tolua_Cocos2d_oPlatformWorld_getLayerOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oPlatformWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oPlatformWorld* self = (oPlatformWorld*)  tolua_tousertype(tolua_S,1,0);
  int zOrder = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLayerOffset'", NULL);
#endif
  {
   oVec2& tolua_ret = (oVec2&)  self->getLayerOffset(zOrder);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"oVec2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLayerOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oPlatformWorld */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oPlatformWorld_new00_local
static int tolua_Cocos2d_oPlatformWorld_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oPlatformWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oPlatformWorld* tolua_ret = (oPlatformWorld*)  oPlatformWorld::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oPlatformWorld");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: load of class  oSound */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oSound_load00
static int tolua_Cocos2d_oSound_load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oSound",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   oSound::load(filename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  oSound */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oSound_play00
static int tolua_Cocos2d_oSound_play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oSound",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool loop = ((bool)  tolua_toboolean(tolua_S,3,false));
  {
   int tolua_ret = (int)  oSound::play(filename,loop);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  oSound */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oSound_stop00
static int tolua_Cocos2d_oSound_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oSound",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   oSound::stop(id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  oSound */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oSound_stop01
static int tolua_Cocos2d_oSound_stop01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oSound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   oSound::stop();
  }
 }
 return 0;
tolua_lerror:
 return tolua_Cocos2d_oSound_stop00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: volume of class  oSound */
#ifndef TOLUA_DISABLE_tolua_get_oSound_volume
static int tolua_get_oSound_volume(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)oSound::getVolume());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: volume of class  oSound */
#ifndef TOLUA_DISABLE_tolua_set_oSound_volume
static int tolua_set_oSound_volume(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  oSound::setVolume(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: useCache of class  oSound */
#ifndef TOLUA_DISABLE_tolua_get_oSound_useCache
static int tolua_get_oSound_useCache(lua_State* tolua_S)
{
  tolua_pushboolean(tolua_S,(bool)oSound::isUseCache());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: useCache of class  oSound */
#ifndef TOLUA_DISABLE_tolua_set_oSound_useCache
static int tolua_set_oSound_useCache(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  oSound::setUseCache(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: load of class  oMusic */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oMusic_load00
static int tolua_Cocos2d_oMusic_load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oMusic",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   oMusic::load(filename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  oMusic */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oMusic_play00
static int tolua_Cocos2d_oMusic_play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oMusic",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool loop = ((bool)  tolua_toboolean(tolua_S,3,false));
  {
   oMusic::play(filename,loop);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pause of class  oMusic */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oMusic_pause00
static int tolua_Cocos2d_oMusic_pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oMusic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oMusic::pause();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resume of class  oMusic */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oMusic_resume00
static int tolua_Cocos2d_oMusic_resume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oMusic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oMusic::resume();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  oMusic */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oMusic_stop00
static int tolua_Cocos2d_oMusic_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oMusic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oMusic::stop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: volume of class  oMusic */
#ifndef TOLUA_DISABLE_tolua_get_oMusic_volume
static int tolua_get_oMusic_volume(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)oMusic::getVolume());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: volume of class  oMusic */
#ifndef TOLUA_DISABLE_tolua_set_oMusic_volume
static int tolua_set_oMusic_volume(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  oMusic::setVolume(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: terrainAllowed of class  oTargetAllow */
#ifndef TOLUA_DISABLE_tolua_get_oTargetAllow_terrainAllowed
static int tolua_get_oTargetAllow_terrainAllowed(lua_State* tolua_S)
{
  oTargetAllow* self = (oTargetAllow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'terrainAllowed'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isTerrainAllowed());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: terrainAllowed of class  oTargetAllow */
#ifndef TOLUA_DISABLE_tolua_set_oTargetAllow_terrainAllowed
static int tolua_set_oTargetAllow_terrainAllowed(lua_State* tolua_S)
{
  oTargetAllow* self = (oTargetAllow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'terrainAllowed'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setTerrainAllowed(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: allow of class  oTargetAllow */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oTargetAllow_allow00
static int tolua_Cocos2d_oTargetAllow_allow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oTargetAllow",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oTargetAllow* self = (oTargetAllow*)  tolua_tousertype(tolua_S,1,0);
  oRelation flag = ((oRelation) (int)  tolua_tonumber(tolua_S,2,0));
  bool allow = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'allow'", NULL);
#endif
  {
   self->allow(flag,allow);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'allow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isAllow of class  oTargetAllow */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oTargetAllow_isAllow00
static int tolua_Cocos2d_oTargetAllow_isAllow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oTargetAllow",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oTargetAllow* self = (oTargetAllow*)  tolua_tousertype(tolua_S,1,0);
  oRelation flag = ((oRelation) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isAllow'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isAllow(flag);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isAllow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_get_oBulletDef_type
static int tolua_get_oBulletDef_type(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->type);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_set_oBulletDef_type
static int tolua_set_oBulletDef_type(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->type = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: endEffect of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_get_oBulletDef_endEffect
static int tolua_get_oBulletDef_endEffect(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'endEffect'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->endEffect);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: endEffect of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_set_oBulletDef_endEffect
static int tolua_set_oBulletDef_endEffect(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'endEffect'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->endEffect = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: lifeTime of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_get_oBulletDef_lifeTime
static int tolua_get_oBulletDef_lifeTime(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lifeTime'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->lifeTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lifeTime of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_set_oBulletDef_lifeTime
static int tolua_set_oBulletDef_lifeTime(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lifeTime'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->lifeTime = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: damageRadius of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_get_oBulletDef_damageRadius
static int tolua_get_oBulletDef_damageRadius(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'damageRadius'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->damageRadius);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: damageRadius of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_set_oBulletDef_damageRadius
static int tolua_set_oBulletDef_damageRadius(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'damageRadius'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->damageRadius = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: highSpeedFix of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_get_oBulletDef_highSpeedFix
static int tolua_get_oBulletDef_highSpeedFix(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'highSpeedFix'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isHighSpeedFix());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: highSpeedFix of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_set_oBulletDef_highSpeedFix
static int tolua_set_oBulletDef_highSpeedFix(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'highSpeedFix'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setHighSpeedFix(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: gravityScale of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_get_oBulletDef_gravityScale
static int tolua_get_oBulletDef_gravityScale(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gravityScale'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getGravityScale());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: gravityScale of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_set_oBulletDef_gravityScale
static int tolua_set_oBulletDef_gravityScale(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gravityScale'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setGravityScale(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: face of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_get_oBulletDef_face_ptr
static int tolua_get_oBulletDef_face_ptr(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'face'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getFace(),"oFace");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: face of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_set_oBulletDef_face_ptr
static int tolua_set_oBulletDef_face_ptr(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'face'",NULL);
  if (!tolua_isusertype(tolua_S,2,"oFace",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setFace(((oFace*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bodyDef of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_get_oBulletDef_bodyDef_ptr
static int tolua_get_oBulletDef_bodyDef_ptr(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bodyDef'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getBodyDef(),"oBodyDef");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: velocity of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_get_oBulletDef_velocity
static int tolua_get_oBulletDef_velocity(lua_State* tolua_S)
{
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'velocity'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->getVelocity()));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAsCircle of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBulletDef_setAsCircle00
static int tolua_Cocos2d_oBulletDef_setAsCircle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBulletDef",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
  float radius = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAsCircle'", NULL);
#endif
  {
   self->setAsCircle(radius);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAsCircle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVelocity of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBulletDef_setVelocity00
static int tolua_Cocos2d_oBulletDef_setVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBulletDef",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
  float angle = ((float)  tolua_tonumber(tolua_S,2,0));
  float speed = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVelocity'", NULL);
#endif
  {
   self->setVelocity(angle,speed);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: toBullet of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBulletDef_toBullet00
static int tolua_Cocos2d_oBulletDef_toBullet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBulletDef",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"oWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"oUnit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBulletDef* self = (oBulletDef*)  tolua_tousertype(tolua_S,1,0);
  oWorld* world = ((oWorld*)  tolua_tousertype(tolua_S,2,0));
  oUnit* unit = ((oUnit*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toBullet'", NULL);
#endif
  {
   oBullet* tolua_ret = (oBullet*)  self->toBullet(world,unit);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oBullet");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toBullet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SensorTag of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_get_oBulletDef_SensorTag
static int tolua_get_oBulletDef_SensorTag(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)oBulletDef::SensorTag);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oBulletDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBulletDef_new00_local
static int tolua_Cocos2d_oBulletDef_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oBulletDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oBulletDef* tolua_ret = (oBulletDef*)  oBulletDef::create();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oBulletDef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  oBullet */
#ifndef TOLUA_DISABLE_tolua_get_oBullet_type
static int tolua_get_oBullet_type(lua_State* tolua_S)
{
  oBullet* self = (oBullet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->type);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  oBullet */
#ifndef TOLUA_DISABLE_tolua_set_oBullet_type
static int tolua_set_oBullet_type(lua_State* tolua_S)
{
  oBullet* self = (oBullet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->type = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: targetAllow of class  oBullet */
#ifndef TOLUA_DISABLE_tolua_get_oBullet_targetAllow
static int tolua_get_oBullet_targetAllow(lua_State* tolua_S)
{
  oBullet* self = (oBullet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'targetAllow'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oTargetAllow)(self->targetAllow));
     tolua_pushusertype(tolua_S,tolua_obj,"oTargetAllow");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: targetAllow of class  oBullet */
#ifndef TOLUA_DISABLE_tolua_set_oBullet_targetAllow
static int tolua_set_oBullet_targetAllow(lua_State* tolua_S)
{
  oBullet* self = (oBullet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'targetAllow'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oTargetAllow",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->targetAllow = *((oTargetAllow*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: faceRight of class  oBullet */
#ifndef TOLUA_DISABLE_tolua_get_oBullet_faceRight
static int tolua_get_oBullet_faceRight(lua_State* tolua_S)
{
  oBullet* self = (oBullet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'faceRight'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isFaceRight());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: owner of class  oBullet */
#ifndef TOLUA_DISABLE_tolua_get_oBullet_owner_ptr
static int tolua_get_oBullet_owner_ptr(lua_State* tolua_S)
{
  oBullet* self = (oBullet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'owner'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getOwner(),"oUnit");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: detectSensor of class  oBullet */
#ifndef TOLUA_DISABLE_tolua_get_oBullet_detectSensor_ptr
static int tolua_get_oBullet_detectSensor_ptr(lua_State* tolua_S)
{
  oBullet* self = (oBullet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'detectSensor'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getDetectSensor(),"oSensor");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bulletDef of class  oBullet */
#ifndef TOLUA_DISABLE_tolua_get_oBullet_bulletDef_ptr
static int tolua_get_oBullet_bulletDef_ptr(lua_State* tolua_S)
{
  oBullet* self = (oBullet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bulletDef'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getBulletDef(),"oBulletDef");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: face of class  oBullet */
#ifndef TOLUA_DISABLE_tolua_get_oBullet_face_ptr
static int tolua_get_oBullet_face_ptr(lua_State* tolua_S)
{
  oBullet* self = (oBullet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'face'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getFace(),"CCNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: face of class  oBullet */
#ifndef TOLUA_DISABLE_tolua_set_oBullet_face_ptr
static int tolua_set_oBullet_face_ptr(lua_State* tolua_S)
{
  oBullet* self = (oBullet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'face'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setFace(((CCNode*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: addHandler of class  oBullet */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBullet_addHandler00
static int tolua_Cocos2d_oBullet_addHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBullet",0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,2,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBullet* self = (oBullet*)  tolua_tousertype(tolua_S,1,0);
  int handler = toluafix_ref_function(tolua_S,2);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addHandler'", NULL);
#endif
  {
   self->addHandler(handler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeHandler of class  oBullet */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBullet_removeHandler00
static int tolua_Cocos2d_oBullet_removeHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBullet",0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,2,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBullet* self = (oBullet*)  tolua_tousertype(tolua_S,1,0);
  int handler = toluafix_ref_function(tolua_S,2);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeHandler'", NULL);
#endif
  {
   self->removeHandler(handler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearHandler of class  oBullet */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBullet_clearHandler00
static int tolua_Cocos2d_oBullet_clearHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBullet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBullet* self = (oBullet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearHandler'", NULL);
#endif
  {
   self->clearHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy of class  oBullet */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBullet_destroy00
static int tolua_Cocos2d_oBullet_destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oBullet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oBullet* self = (oBullet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'destroy'", NULL);
#endif
  {
   self->destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oBullet */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oBullet_new00_local
static int tolua_Cocos2d_oBullet_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oBullet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"oWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"oBulletDef",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"oUnit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oWorld* world = ((oWorld*)  tolua_tousertype(tolua_S,2,0));
  oBulletDef* def = ((oBulletDef*)  tolua_tousertype(tolua_S,3,0));
  oUnit* unit = ((oUnit*)  tolua_tousertype(tolua_S,4,0));
  {
   oBullet* tolua_ret = (oBullet*)  oBullet::create(world,def,unit);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oBullet");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnitDef_new00_local
static int tolua_Cocos2d_oUnitDef_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oUnitDef",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  string modelFile = ((string)  tolua_tocppstring(tolua_S,2,0));
  CCSize* size = ((CCSize*)  tolua_tousertype(tolua_S,3,0));
  float density = ((float)  tolua_tonumber(tolua_S,4,0));
  float friction = ((float)  tolua_tonumber(tolua_S,5,0));
  float restitution = ((float)  tolua_tonumber(tolua_S,6,0));
  {
   oUnitDef* tolua_ret = (oUnitDef*)  oUnitDef::create(modelFile,*size,density,friction,restitution);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oUnitDef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bodyDef of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_bodyDef_ptr
static int tolua_get_oUnitDef_bodyDef_ptr(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bodyDef'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getBodyDef(),"oBodyDef");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: size of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_size
static int tolua_get_oUnitDef_size(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->getSize()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: static of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_static
static int tolua_get_oUnitDef_static(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'static'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isStatic());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: toUnit of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnitDef_toUnit00
static int tolua_Cocos2d_oUnitDef_toUnit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnitDef",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"oWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
  oWorld* world = ((oWorld*)  tolua_tousertype(tolua_S,2,0));
  int group = ((int)  tolua_tonumber(tolua_S,3,0));
  float x = ((float)  tolua_tonumber(tolua_S,4,0));
  float y = ((float)  tolua_tonumber(tolua_S,5,0));
  bool faceRight = ((bool)  tolua_toboolean(tolua_S,6,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toUnit'", NULL);
#endif
  {
   oUnit* tolua_ret = (oUnit*)  self->toUnit(world,group,x,y,faceRight);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oUnit");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toUnit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_type
static int tolua_get_oUnitDef_type(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->type);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_type
static int tolua_set_oUnitDef_type(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->type = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sensity of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_sensity
static int tolua_get_oUnitDef_sensity(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sensity'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->sensity);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sensity of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_sensity
static int tolua_set_oUnitDef_sensity(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sensity'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sensity = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: move of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_move
static int tolua_get_oUnitDef_move(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'move'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->move);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: move of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_move
static int tolua_set_oUnitDef_move(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'move'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->move = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: jump of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_jump
static int tolua_get_oUnitDef_jump(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'jump'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->jump);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: jump of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_jump
static int tolua_set_oUnitDef_jump(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'jump'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->jump = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: detectDistance of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_detectDistance
static int tolua_get_oUnitDef_detectDistance(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'detectDistance'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->detectDistance);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: detectDistance of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_detectDistance
static int tolua_set_oUnitDef_detectDistance(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'detectDistance'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->detectDistance = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxHp of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_maxHp
static int tolua_get_oUnitDef_maxHp(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxHp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxHp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxHp of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_maxHp
static int tolua_set_oUnitDef_maxHp(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxHp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxHp = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackBase of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_attackBase
static int tolua_get_oUnitDef_attackBase(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackBase'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attackBase);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackBase of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_attackBase
static int tolua_set_oUnitDef_attackBase(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackBase'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attackBase = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackDelay of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_attackDelay
static int tolua_get_oUnitDef_attackDelay(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackDelay'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attackDelay);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackDelay of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_attackDelay
static int tolua_set_oUnitDef_attackDelay(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackDelay'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attackDelay = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackEffectDelay of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_attackEffectDelay
static int tolua_get_oUnitDef_attackEffectDelay(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackEffectDelay'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attackEffectDelay);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackEffectDelay of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_attackEffectDelay
static int tolua_set_oUnitDef_attackEffectDelay(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackEffectDelay'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attackEffectDelay = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackRange of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_attackRange
static int tolua_get_oUnitDef_attackRange(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackRange'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->attackRange));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackRange of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_attackRange
static int tolua_set_oUnitDef_attackRange(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackRange'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attackRange = *((CCSize*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackPower of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_attackPower
static int tolua_get_oUnitDef_attackPower(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackPower'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->attackPower));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackPower of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_attackPower
static int tolua_set_oUnitDef_attackPower(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackPower'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attackPower = *((oVec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackType of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_attackType
static int tolua_get_oUnitDef_attackType(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attackType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackType of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_attackType
static int tolua_set_oUnitDef_attackType(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attackType = ((oAttackType) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackTarget of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_attackTarget
static int tolua_get_oUnitDef_attackTarget(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackTarget'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attackTarget);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackTarget of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_attackTarget
static int tolua_set_oUnitDef_attackTarget(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackTarget'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attackTarget = ((oAttackTarget) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: targetAllow of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_targetAllow
static int tolua_get_oUnitDef_targetAllow(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'targetAllow'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oTargetAllow)(self->targetAllow));
     tolua_pushusertype(tolua_S,tolua_obj,"oTargetAllow");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: targetAllow of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_targetAllow
static int tolua_set_oUnitDef_targetAllow(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'targetAllow'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oTargetAllow",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->targetAllow = *((oTargetAllow*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: damageType of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_unsigned_damageType
static int tolua_get_oUnitDef_unsigned_damageType(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'damageType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->damageType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: damageType of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_unsigned_damageType
static int tolua_set_oUnitDef_unsigned_damageType(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'damageType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->damageType = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: defenceType of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_unsigned_defenceType
static int tolua_get_oUnitDef_unsigned_defenceType(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'defenceType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->defenceType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: defenceType of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_unsigned_defenceType
static int tolua_set_oUnitDef_unsigned_defenceType(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'defenceType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->defenceType = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bulletType of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_bulletType
static int tolua_get_oUnitDef_bulletType(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bulletType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->bulletType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bulletType of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_bulletType
static int tolua_set_oUnitDef_bulletType(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bulletType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bulletType = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackEffect of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_attackEffect
static int tolua_get_oUnitDef_attackEffect(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackEffect'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attackEffect);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackEffect of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_attackEffect
static int tolua_set_oUnitDef_attackEffect(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackEffect'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attackEffect = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hitEffect of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_hitEffect
static int tolua_get_oUnitDef_hitEffect(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hitEffect'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->hitEffect);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hitEffect of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_hitEffect
static int tolua_set_oUnitDef_hitEffect(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hitEffect'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hitEffect = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: name of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_name
static int tolua_get_oUnitDef_name(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: name of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_name
static int tolua_set_oUnitDef_name(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->name = ((string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: desc of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_desc
static int tolua_get_oUnitDef_desc(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'desc'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->desc);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: desc of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_desc
static int tolua_set_oUnitDef_desc(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'desc'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->desc = ((string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sndAttack of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_sndAttack
static int tolua_get_oUnitDef_sndAttack(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sndAttack'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->sndAttack);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sndAttack of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_sndAttack
static int tolua_set_oUnitDef_sndAttack(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sndAttack'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sndAttack = ((string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sndDeath of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_get_oUnitDef_sndDeath
static int tolua_get_oUnitDef_sndDeath(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sndDeath'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->sndDeath);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sndDeath of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_set_oUnitDef_sndDeath
static int tolua_set_oUnitDef_sndDeath(lua_State* tolua_S)
{
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sndDeath'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sndDeath = ((string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: oUnitDef_setActions of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnitDef_setActions00
static int tolua_Cocos2d_oUnitDef_setActions00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnitDef",0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
  int tolua_len = lua_objlen(tolua_S,2);
  int* actions = Mtolua_new_dim(int, tolua_len);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'oUnitDef_setActions'", NULL);
#endif
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isnumberarray(tolua_S,2,tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    actions[i] = ((int)  tolua_tofieldnumber(tolua_S,2,i+1,0));
   }
  }
  {
   oUnitDef_setActions(self,actions,tolua_len);
  }
  Mtolua_delete_dim(actions);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setActions'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: oUnitDef_setInstincts of class  oUnitDef */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnitDef_setInstincts00
static int tolua_Cocos2d_oUnitDef_setInstincts00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnitDef",0,&tolua_err) ||
     !tolua_istable(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnitDef* self = (oUnitDef*)  tolua_tousertype(tolua_S,1,0);
  int tolua_len = lua_objlen(tolua_S,2);
  int* instincts = Mtolua_new_dim(int, tolua_len);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'oUnitDef_setInstincts'", NULL);
#endif
  {
#ifndef TOLUA_RELEASE
   if (!tolua_isnumberarray(tolua_S,2,tolua_len,0,&tolua_err))
    goto tolua_lerror;
   else
#endif
   {
    for (int i=0;i<(int)tolua_len;i++)
    instincts[i] = ((int)  tolua_tofieldnumber(tolua_S,2,i+1,0));
   }
  }
  {
   oUnitDef_setInstincts(self,instincts,tolua_len);
  }
  Mtolua_delete_dim(instincts);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInstincts'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sensity of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_sensity
static int tolua_get_oUnit_sensity(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sensity'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->sensity);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sensity of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_sensity
static int tolua_set_oUnit_sensity(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sensity'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sensity = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: move of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_move
static int tolua_get_oUnit_move(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'move'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->move);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: move of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_move
static int tolua_set_oUnit_move(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'move'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->move = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: moveSpeed of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_moveSpeed
static int tolua_get_oUnit_moveSpeed(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'moveSpeed'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->moveSpeed);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: moveSpeed of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_moveSpeed
static int tolua_set_oUnit_moveSpeed(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'moveSpeed'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->moveSpeed = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: jump of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_jump
static int tolua_get_oUnit_jump(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'jump'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->jump);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: jump of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_jump
static int tolua_set_oUnit_jump(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'jump'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->jump = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxHp of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_maxHp
static int tolua_get_oUnit_maxHp(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxHp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxHp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxHp of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_maxHp
static int tolua_set_oUnit_maxHp(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxHp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxHp = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackBase of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_attackBase
static int tolua_get_oUnit_attackBase(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackBase'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attackBase);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackBase of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_attackBase
static int tolua_set_oUnit_attackBase(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackBase'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attackBase = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackBonus of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_attackBonus
static int tolua_get_oUnit_attackBonus(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackBonus'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attackBonus);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackBonus of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_attackBonus
static int tolua_set_oUnit_attackBonus(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackBonus'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attackBonus = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackFactor of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_attackFactor
static int tolua_get_oUnit_attackFactor(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackFactor'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attackFactor);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackFactor of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_attackFactor
static int tolua_set_oUnit_attackFactor(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackFactor'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attackFactor = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackSpeed of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_attackSpeed
static int tolua_get_oUnit_attackSpeed(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackSpeed'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attackSpeed);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackSpeed of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_attackSpeed
static int tolua_set_oUnit_attackSpeed(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackSpeed'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attackSpeed = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackPower of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_attackPower
static int tolua_get_oUnit_attackPower(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackPower'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oVec2)(self->attackPower));
     tolua_pushusertype(tolua_S,tolua_obj,"oVec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackPower of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_attackPower
static int tolua_set_oUnit_attackPower(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackPower'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oVec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attackPower = *((oVec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackType of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_attackType
static int tolua_get_oUnit_attackType(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attackType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackType of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_attackType
static int tolua_set_oUnit_attackType(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attackType = ((oAttackType) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackTarget of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_attackTarget
static int tolua_get_oUnit_attackTarget(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackTarget'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->attackTarget);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackTarget of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_attackTarget
static int tolua_set_oUnit_attackTarget(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackTarget'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attackTarget = ((oAttackTarget) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: targetAllow of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_targetAllow
static int tolua_get_oUnit_targetAllow(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'targetAllow'",NULL);
#endif
    void* tolua_obj = Mtolua_new((oTargetAllow)(self->targetAllow));
     tolua_pushusertype(tolua_S,tolua_obj,"oTargetAllow");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: targetAllow of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_targetAllow
static int tolua_set_oUnit_targetAllow(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'targetAllow'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"oTargetAllow",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->targetAllow = *((oTargetAllow*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: damageType of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_unsigned_damageType
static int tolua_get_oUnit_unsigned_damageType(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'damageType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->damageType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: damageType of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_unsigned_damageType
static int tolua_set_oUnit_unsigned_damageType(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'damageType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->damageType = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: defenceType of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_unsigned_defenceType
static int tolua_get_oUnit_unsigned_defenceType(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'defenceType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->defenceType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: defenceType of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_unsigned_defenceType
static int tolua_set_oUnit_unsigned_defenceType(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'defenceType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->defenceType = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: model of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_model_ptr
static int tolua_get_oUnit_model_ptr(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'model'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getModel(),"oModel");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: model of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_model_ptr
static int tolua_set_oUnit_model_ptr(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'model'",NULL);
  if (!tolua_isusertype(tolua_S,2,"oModel",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setModel(((oModel*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: detectDistance of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_detectDistance
static int tolua_get_oUnit_detectDistance(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'detectDistance'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getDetectDistance());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: detectDistance of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_detectDistance
static int tolua_set_oUnit_detectDistance(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'detectDistance'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setDetectDistance(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackRange of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_attackRange
static int tolua_get_oUnit_attackRange(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackRange'",NULL);
#endif
    void* tolua_obj = Mtolua_new((CCSize)(self->getAttackRange()));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attackRange of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_attackRange
static int tolua_set_oUnit_attackRange(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackRange'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setAttackRange(*((CCSize*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: faceRight of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_faceRight
static int tolua_get_oUnit_faceRight(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'faceRight'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isFaceRight());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: faceRight of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_faceRight
static int tolua_set_oUnit_faceRight(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'faceRight'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setFaceRight(((bool)  tolua_toboolean(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bulletDef of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_bulletDef_ptr
static int tolua_get_oUnit_bulletDef_ptr(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bulletDef'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getBulletDef(),"oBulletDef");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bulletDef of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_set_oUnit_bulletDef_ptr
static int tolua_set_oUnit_bulletDef_ptr(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bulletDef'",NULL);
  if (!tolua_isusertype(tolua_S,2,"oBulletDef",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->setBulletDef(((oBulletDef*)  tolua_tousertype(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: onSurface of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_onSurface
static int tolua_get_oUnit_onSurface(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'onSurface'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isOnSurface());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: groundSensor of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_groundSensor_ptr
static int tolua_get_oUnit_groundSensor_ptr(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'groundSensor'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getGroundSensor(),"oSensor");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: detectSensor of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_detectSensor_ptr
static int tolua_get_oUnit_detectSensor_ptr(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'detectSensor'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getDetectSensor(),"oSensor");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attackSensor of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_attackSensor_ptr
static int tolua_get_oUnit_attackSensor_ptr(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attackSensor'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getAttackSensor(),"oSensor");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: unitDef of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_unitDef_ptr
static int tolua_get_oUnit_unitDef_ptr(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'unitDef'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getUnitDef(),"oUnitDef");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: currentAction of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_currentAction_ptr
static int tolua_get_oUnit_currentAction_ptr(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'currentAction'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->getCurrentAction(),"oAction");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: width of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_width
static int tolua_get_oUnit_width(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'width'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getWidth());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: height of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_get_oUnit_height
static int tolua_get_oUnit_height(lua_State* tolua_S)
{
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'height'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getHeight());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachAction of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnit_attachAction00
static int tolua_Cocos2d_oUnit_attachAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachAction'", NULL);
#endif
  {
   oAction* tolua_ret = (oAction*)  self->attachAction(id);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"oAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAction of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnit_removeAction00
static int tolua_Cocos2d_oUnit_removeAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAction'", NULL);
#endif
  {
   self->removeAction(id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllActions of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnit_removeAllActions00
static int tolua_Cocos2d_oUnit_removeAllActions00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllActions'", NULL);
#endif
  {
   self->removeAllActions();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllActions'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAction of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnit_getAction00
static int tolua_Cocos2d_oUnit_getAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAction'", NULL);
#endif
  {
   oAction* tolua_ret = (oAction*)  self->getAction(id);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"oAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: doIt of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnit_doIt00
static int tolua_Cocos2d_oUnit_doIt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'doIt'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->doIt(id);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'doIt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attachInstinct of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnit_attachInstinct00
static int tolua_Cocos2d_oUnit_attachInstinct00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attachInstinct'", NULL);
#endif
  {
   self->attachInstinct(id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attachInstinct'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeInstinct of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnit_removeInstinct00
static int tolua_Cocos2d_oUnit_removeInstinct00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeInstinct'", NULL);
#endif
  {
   self->removeInstinct(id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeInstinct'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllInstincts of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnit_removeAllInstincts00
static int tolua_Cocos2d_oUnit_removeAllInstincts00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllInstincts'", NULL);
#endif
  {
   self->removeAllInstincts();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllInstincts'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setReflexArc of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnit_setReflexArc00
static int tolua_Cocos2d_oUnit_setReflexArc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setReflexArc'", NULL);
#endif
  {
   self->setReflexArc(id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setReflexArc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: set of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnit_set00
static int tolua_Cocos2d_oUnit_set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnit",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  float value = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set'", NULL);
#endif
  {
   self->set(name,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnit_get00
static int tolua_Cocos2d_oUnit_get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnit",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'", NULL);
#endif
  {
   float tolua_ret = (float)  self->get(name);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: remove of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnit_remove00
static int tolua_Cocos2d_oUnit_remove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnit",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'remove'", NULL);
#endif
  {
   self->remove(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'remove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnit_clear00
static int tolua_Cocos2d_oUnit_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oUnit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oUnit* self = (oUnit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oUnit */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oUnit_new00_local
static int tolua_Cocos2d_oUnit_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oUnit",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"oWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"oUnitDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oWorld* world = ((oWorld*)  tolua_tousertype(tolua_S,2,0));
  oUnitDef* unitDef = ((oUnitDef*)  tolua_tousertype(tolua_S,3,0));
  {
   oUnit* tolua_ret = (oUnit*)  oUnit::create(world,unitDef);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oUnit");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: reaction of class  oAction */
#ifndef TOLUA_DISABLE_tolua_get_oAction_reaction
static int tolua_get_oAction_reaction(lua_State* tolua_S)
{
  oAction* self = (oAction*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'reaction'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->reaction);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: reaction of class  oAction */
#ifndef TOLUA_DISABLE_tolua_set_oAction_reaction
static int tolua_set_oAction_reaction(lua_State* tolua_S)
{
  oAction* self = (oAction*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'reaction'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->reaction = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: id of class  oAction */
#ifndef TOLUA_DISABLE_tolua_get_oAction_id
static int tolua_get_oAction_id(lua_State* tolua_S)
{
  oAction* self = (oAction*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getId());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: priority of class  oAction */
#ifndef TOLUA_DISABLE_tolua_get_oAction_priority
static int tolua_get_oAction_priority(lua_State* tolua_S)
{
  oAction* self = (oAction*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'priority'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getPriority());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: doing of class  oAction */
#ifndef TOLUA_DISABLE_tolua_get_oAction_doing
static int tolua_get_oAction_doing(lua_State* tolua_S)
{
  oAction* self = (oAction*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'doing'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isDoing());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: owner of class  oAction */
#ifndef TOLUA_DISABLE_tolua_get_oAction_owner_ptr
static int tolua_get_oAction_owner_ptr(lua_State* tolua_S)
{
  oAction* self = (oAction*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'owner'",NULL);
#endif
   tolua_pushccobject(tolua_S,(void*)self->getOwner(),"oUnit");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  oAction */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oAction_stop00
static int tolua_Cocos2d_oAction_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oAction",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oAction* self = (oAction*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stop'", NULL);
#endif
  {
   self->stop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addHandler of class  oAction */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oAction_addHandler00
static int tolua_Cocos2d_oAction_addHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oAction",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,3,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oAction* self = (oAction*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  int handler = toluafix_ref_function(tolua_S,3);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addHandler'", NULL);
#endif
  {
   self->addHandler(type,handler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeHandler of class  oAction */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oAction_removeHandler00
static int tolua_Cocos2d_oAction_removeHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oAction",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,3,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oAction* self = (oAction*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  int handler = toluafix_ref_function(tolua_S,3);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeHandler'", NULL);
#endif
  {
   self->removeHandler(type,handler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearHandler of class  oAction */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oAction_clearHandler00
static int tolua_Cocos2d_oAction_clearHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oAction",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oAction* self = (oAction*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearHandler'", NULL);
#endif
  {
   self->clearHandler(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: add of class  oAction */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oAction_add00
static int tolua_Cocos2d_oAction_add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oAction",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !toluafix_isfunction(tolua_S,5,&tolua_err) ||
     !toluafix_isfunction(tolua_S,6,&tolua_err) ||
     !toluafix_isfunction(tolua_S,7,&tolua_err) ||
     !toluafix_isfunction(tolua_S,8,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  int priority = ((int)  tolua_tonumber(tolua_S,3,0));
  float reaction = ((float)  tolua_tonumber(tolua_S,4,0));
  int available = toluafix_ref_function(tolua_S,5);
  int run = toluafix_ref_function(tolua_S,6);
  int update = toluafix_ref_function(tolua_S,7);
  int stop = toluafix_ref_function(tolua_S,8);
  {
   oAction::add(id,priority,reaction,available,run,update,stop);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  oAction */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oAction_clear00
static int tolua_Cocos2d_oAction_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oAction",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oAction::clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UserID of class  oAction */
#ifndef TOLUA_DISABLE_tolua_get_oAction_UserID
static int tolua_get_oAction_UserID(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)oAction::UserID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: self of class  oAI */
#ifndef TOLUA_DISABLE_tolua_get_oAI_self_ptr
static int tolua_get_oAI_self_ptr(lua_State* tolua_S)
{
   tolua_pushccobject(tolua_S,(void*)oAI::getSelf(),"oUnit");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: oldInstinctValue of class  oAI */
#ifndef TOLUA_DISABLE_tolua_get_oAI_oldInstinctValue
static int tolua_get_oAI_oldInstinctValue(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)oAI::getOldInstinctValue());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: newInstinctValue of class  oAI */
#ifndef TOLUA_DISABLE_tolua_get_oAI_newInstinctValue
static int tolua_get_oAI_newInstinctValue(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)oAI::getNewInstinctValue());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUnitsByRelation of class  oAI */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oAI_getUnitsByRelation00
static int tolua_Cocos2d_oAI_getUnitsByRelation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oAI",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oRelation relation = ((oRelation) (int)  tolua_tonumber(tolua_S,2,0));
  {
   CCArray* tolua_ret = (CCArray*)  oAI::getUnitsByRelation(relation);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUnitsByRelation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDetectedUnits of class  oAI */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oAI_getDetectedUnits00
static int tolua_Cocos2d_oAI_getDetectedUnits00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oAI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCArray* tolua_ret = (CCArray*)  oAI::getDetectedUnits();
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDetectedUnits'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNearestUnit of class  oAI */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oAI_getNearestUnit00
static int tolua_Cocos2d_oAI_getNearestUnit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oAI",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oRelation relation = ((oRelation) (int)  tolua_tonumber(tolua_S,2,0));
  {
   oUnit* tolua_ret = (oUnit*)  oAI::getNearestUnit(relation);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oUnit");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNearestUnit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNearestUnitDistance of class  oAI */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oAI_getNearestUnitDistance00
static int tolua_Cocos2d_oAI_getNearestUnitDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oAI",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oRelation relation = ((oRelation) (int)  tolua_tonumber(tolua_S,2,0));
  {
   float tolua_ret = (float)  oAI::getNearestUnitDistance(relation);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNearestUnitDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: add of class  oAI */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oAI_add00
static int tolua_Cocos2d_oAI_add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oAI",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"oAILeaf",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  oAILeaf* leaf = ((oAILeaf*)  tolua_tousertype(tolua_S,3,0));
  {
   oAI::add(id,leaf);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  oAI */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oAI_clear00
static int tolua_Cocos2d_oAI_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oAI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oAI::clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: add of class  oInstinct */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oInstinct_add00
static int tolua_Cocos2d_oInstinct_add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oInstinct",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"oAILeaf",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  string propName = ((string)  tolua_tocppstring(tolua_S,3,0));
  oAILeaf* node = ((oAILeaf*)  tolua_tousertype(tolua_S,4,0));
  {
   oInstinct::add(id,propName,node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  oInstinct */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oInstinct_clear00
static int tolua_Cocos2d_oInstinct_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oInstinct",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oInstinct::clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: oSel */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oSel00
static int tolua_Cocos2d_oSel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* nodes = ((CCArray*)  tolua_tousertype(tolua_S,1,0));
  {
   oAILeaf* tolua_ret = (oAILeaf*)  oSel(nodes);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oAILeaf");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'oSel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: oSeq */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oSeq00
static int tolua_Cocos2d_oSeq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* nodes = ((CCArray*)  tolua_tousertype(tolua_S,1,0));
  {
   oAILeaf* tolua_ret = (oAILeaf*)  oSeq(nodes);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oAILeaf");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'oSeq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: oParSel */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oParSel00
static int tolua_Cocos2d_oParSel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* nodes = ((CCArray*)  tolua_tousertype(tolua_S,1,0));
  {
   oAILeaf* tolua_ret = (oAILeaf*)  oParSel(nodes);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oAILeaf");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'oParSel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: oParSeq */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oParSeq00
static int tolua_Cocos2d_oParSeq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCArray",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCArray* nodes = ((CCArray*)  tolua_tousertype(tolua_S,1,0));
  {
   oAILeaf* tolua_ret = (oAILeaf*)  oParSeq(nodes);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oAILeaf");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'oParSeq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: oCon */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oCon00
static int tolua_Cocos2d_oCon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !toluafix_isfunction(tolua_S,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int handler = toluafix_ref_function(tolua_S,1);
  {
   oAILeaf* tolua_ret = (oAILeaf*)  oCon(handler);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oAILeaf");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'oCon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: oAct */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oAct00
static int tolua_Cocos2d_oAct00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actionId = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   oAILeaf* tolua_ret = (oAILeaf*)  oAct(actionId);
    tolua_pushccobject(tolua_S,(void*)tolua_ret,"oAILeaf");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'oAct'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: GroupHide of class  oData */
#ifndef TOLUA_DISABLE_tolua_get_oData_GroupHide
static int tolua_get_oData_GroupHide(lua_State* tolua_S)
{
  oData* self = (oData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'GroupHide'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getGroupHide());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: GroupDetectPlayer of class  oData */
#ifndef TOLUA_DISABLE_tolua_get_oData_GroupDetectPlayer
static int tolua_get_oData_GroupDetectPlayer(lua_State* tolua_S)
{
  oData* self = (oData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'GroupDetectPlayer'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getGroupDetectPlayer());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: GroupTerrain of class  oData */
#ifndef TOLUA_DISABLE_tolua_get_oData_GroupTerrain
static int tolua_get_oData_GroupTerrain(lua_State* tolua_S)
{
  oData* self = (oData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'GroupTerrain'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getGroupTerrain());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: GroupDetect of class  oData */
#ifndef TOLUA_DISABLE_tolua_get_oData_GroupDetect
static int tolua_get_oData_GroupDetect(lua_State* tolua_S)
{
  oData* self = (oData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'GroupDetect'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->getGroupDetect());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRelation of class  oData */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oData_setRelation00
static int tolua_Cocos2d_oData_setRelation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oData",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oData* self = (oData*)  tolua_tousertype(tolua_S,1,0);
  int groupA = ((int)  tolua_tonumber(tolua_S,2,0));
  int groupB = ((int)  tolua_tonumber(tolua_S,3,0));
  oRelation relation = ((oRelation) (int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRelation'", NULL);
#endif
  {
   self->setRelation(groupA,groupB,relation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRelation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRelation of class  oData */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oData_getRelation00
static int tolua_Cocos2d_oData_getRelation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oData",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oData* self = (oData*)  tolua_tousertype(tolua_S,1,0);
  int groupA = ((int)  tolua_tonumber(tolua_S,2,0));
  int groupB = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRelation'", NULL);
#endif
  {
   oRelation tolua_ret = (oRelation)  self->getRelation(groupA,groupB);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRelation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRelation of class  oData */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oData_getRelation01
static int tolua_Cocos2d_oData_getRelation01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oData",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"oUnit",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"oUnit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  oData* self = (oData*)  tolua_tousertype(tolua_S,1,0);
  oUnit* unitA = ((oUnit*)  tolua_tousertype(tolua_S,2,0));
  oUnit* unitB = ((oUnit*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRelation'", NULL);
#endif
  {
   oRelation tolua_ret = (oRelation)  self->getRelation(unitA,unitB);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Cocos2d_oData_getRelation00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDamageFactor of class  oData */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oData_setDamageFactor00
static int tolua_Cocos2d_oData_setDamageFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oData",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oData* self = (oData*)  tolua_tousertype(tolua_S,1,0);
  unsigned short damageType = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
  unsigned short defenceType = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
  float bounus = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDamageFactor'", NULL);
#endif
  {
   self->setDamageFactor(damageType,defenceType,bounus);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDamageFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDamageFactor of class  oData */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oData_getDamageFactor00
static int tolua_Cocos2d_oData_getDamageFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oData",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oData* self = (oData*)  tolua_tousertype(tolua_S,1,0);
  unsigned short damageType = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
  unsigned short defenceType = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDamageFactor'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getDamageFactor(damageType,defenceType);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDamageFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPlayerUnit of class  oData */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oData_isPlayerUnit00
static int tolua_Cocos2d_oData_isPlayerUnit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oData",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"oBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oData* self = (oData*)  tolua_tousertype(tolua_S,1,0);
  oBody* body = ((oBody*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPlayerUnit'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPlayerUnit(body);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPlayerUnit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTerrain of class  oData */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oData_isTerrain00
static int tolua_Cocos2d_oData_isTerrain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"oData",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"oBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  oData* self = (oData*)  tolua_tousertype(tolua_S,1,0);
  oBody* body = ((oBody*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTerrain'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isTerrain(body);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isTerrain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  oData */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_oData_new00_local
static int tolua_Cocos2d_oData_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"oData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   oData* tolua_ret = (oData*)  oData::shared();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"oData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Cocos2d_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"ccColor3","",tolua_collect_ccColor3B);
  tolua_beginmodule(tolua_S,"ccColor3");
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_ccColor3_new02_local);
   tolua_variable(tolua_S,"r",tolua_get_ccColor3B_unsigned_r,tolua_set_ccColor3B_unsigned_r);
   tolua_variable(tolua_S,"g",tolua_get_ccColor3B_unsigned_g,tolua_set_ccColor3B_unsigned_g);
   tolua_variable(tolua_S,"b",tolua_get_ccColor3B_unsigned_b,tolua_set_ccColor3B_unsigned_b);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ccColor4","",tolua_collect_ccColor4B);
  tolua_beginmodule(tolua_S,"ccColor4");
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_ccColor4_new03_local);
   tolua_variable(tolua_S,"r",tolua_get_ccColor4B_unsigned_r,tolua_set_ccColor4B_unsigned_r);
   tolua_variable(tolua_S,"g",tolua_get_ccColor4B_unsigned_g,tolua_set_ccColor4B_unsigned_g);
   tolua_variable(tolua_S,"b",tolua_get_ccColor4B_unsigned_b,tolua_set_ccColor4B_unsigned_b);
   tolua_variable(tolua_S,"a",tolua_get_ccColor4B_unsigned_a,tolua_set_ccColor4B_unsigned_a);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ccBlendFunc","",tolua_collect_ccBlendFunc);
  tolua_beginmodule(tolua_S,"ccBlendFunc");
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_ccBlendFunc_new00_local);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_ccBlendFunc_new01_local);
   tolua_variable(tolua_S,"src",tolua_get_ccBlendFunc_unsigned_src,tolua_set_ccBlendFunc_unsigned_src);
   tolua_variable(tolua_S,"dst",tolua_get_ccBlendFunc_unsigned_dst,tolua_set_ccBlendFunc_unsigned_dst);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"CCTextAlign",0);
  tolua_beginmodule(tolua_S,"CCTextAlign");
   tolua_constant(tolua_S,"HLeft",kCCTextAlignmentLeft);
   tolua_constant(tolua_S,"HCenter",kCCTextAlignmentCenter);
   tolua_constant(tolua_S,"HRight",kCCTextAlignmentRight);
   tolua_constant(tolua_S,"VTop",kCCVerticalTextAlignmentTop);
   tolua_constant(tolua_S,"VCenter",kCCVerticalTextAlignmentCenter);
   tolua_constant(tolua_S,"VBottom",kCCVerticalTextAlignmentBottom);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCObject","",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCObject");
   tolua_variable(tolua_S,"id",tolua_get_CCObject_id,NULL);
   tolua_variable(tolua_S,"count",tolua_get_CCObject_unsigned_count,NULL);
   tolua_variable(tolua_S,"luaRefCount",tolua_get_CCObject_unsigned_luaRefCount,NULL);
   tolua_variable(tolua_S,"callRefCount",tolua_get_CCObject_callRefCount,NULL);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"CCLuaLog",tolua_Cocos2d_CCLuaLog00);
  tolua_function(tolua_S,"CCMessageBox",tolua_Cocos2d_CCMessageBox00);
  tolua_cclass(tolua_S,"CCSize","",tolua_collect_CCSize);
  tolua_beginmodule(tolua_S,"CCSize");
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCSize_new01_local);
   tolua_variable(tolua_S,"width",tolua_get_CCSize_width,tolua_set_CCSize_width);
   tolua_variable(tolua_S,"height",tolua_get_CCSize_height,tolua_set_CCSize_height);
   tolua_call(tolua_S,MT_EQ,tolua_Cocos2d_CCSize__eq00);
   tolua_variable(tolua_S,"zero",tolua_get_CCSize_zero,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCRect","",tolua_collect_CCRect);
  tolua_beginmodule(tolua_S,"CCRect");
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCRect_new02_local);
   tolua_variable(tolua_S,"origin",tolua_get_CCRect_origin,tolua_set_CCRect_origin);
   tolua_variable(tolua_S,"size",tolua_get_CCRect_size,tolua_set_CCRect_size);
   tolua_variable(tolua_S,"left",tolua_get_CCRect_left,NULL);
   tolua_variable(tolua_S,"right",tolua_get_CCRect_right,NULL);
   tolua_variable(tolua_S,"bottom",tolua_get_CCRect_bottom,NULL);
   tolua_variable(tolua_S,"up",tolua_get_CCRect_up,NULL);
   tolua_variable(tolua_S,"midX",tolua_get_CCRect_midX,NULL);
   tolua_variable(tolua_S,"midY",tolua_get_CCRect_midY,NULL);
   tolua_call(tolua_S,MT_EQ,tolua_Cocos2d_CCRect__eq00);
   tolua_function(tolua_S,"containsPoint",tolua_Cocos2d_CCRect_containsPoint00);
   tolua_function(tolua_S,"intersectsRect",tolua_Cocos2d_CCRect_intersectsRect00);
   tolua_variable(tolua_S,"zero",tolua_get_CCRect_zero,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCArray","CCObject",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCArray");
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCArray_new03_local);
   tolua_variable(tolua_S,"count",tolua_get_CCArray_unsigned_count,NULL);
   tolua_variable(tolua_S,"capacity",tolua_get_CCArray_unsigned_capacity,NULL);
   tolua_variable(tolua_S,"last",tolua_get_CCArray_last_ptr,NULL);
   tolua_variable(tolua_S,"randomObject",tolua_get_CCArray_randomObject_ptr,NULL);
   tolua_function(tolua_S,"equals",tolua_Cocos2d_CCArray_equals00);
   tolua_function(tolua_S,"contains",tolua_Cocos2d_CCArray_contains00);
   tolua_function(tolua_S,"add",tolua_Cocos2d_CCArray_add00);
   tolua_function(tolua_S,"join",tolua_Cocos2d_CCArray_join00);
   tolua_function(tolua_S,"removeLast",tolua_Cocos2d_CCArray_removeLast00);
   tolua_function(tolua_S,"remove",tolua_Cocos2d_CCArray_remove00);
   tolua_function(tolua_S,"removeFrom",tolua_Cocos2d_CCArray_removeFrom00);
   tolua_function(tolua_S,"clear",tolua_Cocos2d_CCArray_clear00);
   tolua_function(tolua_S,"fastRemove",tolua_Cocos2d_CCArray_fastRemove00);
   tolua_function(tolua_S,"swap",tolua_Cocos2d_CCArray_swap00);
   tolua_function(tolua_S,"reverse",tolua_Cocos2d_CCArray_reverse00);
   tolua_function(tolua_S,"shrink",tolua_Cocos2d_CCArray_shrink00);
   tolua_function(tolua_S,"index",tolua_Cocos2d_CCArray_index00);
   tolua_function(tolua_S,"get",tolua_Cocos2d_CCArray_get00);
   tolua_function(tolua_S,"insert",tolua_Cocos2d_CCArray_insert00);
   tolua_function(tolua_S,"removeAt",tolua_Cocos2d_CCArray_removeAt00);
   tolua_function(tolua_S,"exchange",tolua_Cocos2d_CCArray_exchange00);
   tolua_function(tolua_S,"fastRemoveAt",tolua_Cocos2d_CCArray_fastRemoveAt00);
   tolua_function(tolua_S,"set",tolua_Cocos2d_CCArray_set00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCView","",NULL);
  tolua_beginmodule(tolua_S,"CCView");
   tolua_constant(tolua_S,"ExactFit",kResolutionExactFit);
   tolua_constant(tolua_S,"NoBorder",kResolutionNoBorder);
   tolua_constant(tolua_S,"ShowAll",kResolutionShowAll);
   tolua_constant(tolua_S,"UnKnown",kResolutionUnKnown);
   tolua_variable(tolua_S,"visibleSize",tolua_get_CCEGLView_visibleSize,NULL);
   tolua_variable(tolua_S,"visibleOrigin",tolua_get_CCEGLView_visibleOrigin,NULL);
   tolua_variable(tolua_S,"scaleX",tolua_get_CCEGLView_scaleX,NULL);
   tolua_variable(tolua_S,"scaleY",tolua_get_CCEGLView_scaleY,NULL);
   tolua_variable(tolua_S,"designResolutionSize",tolua_get_CCEGLView_designResolutionSize,NULL);
   tolua_variable(tolua_S,"frameSize",tolua_get_CCEGLView_frameSize,tolua_set_CCEGLView_frameSize);
   tolua_variable(tolua_S,"viewPort",tolua_get_CCEGLView_viewPort,tolua_set_CCEGLView_viewPort);
   tolua_variable(tolua_S,"viewName",tolua_get_CCEGLView_viewName,tolua_set_CCEGLView_viewName);
   tolua_function(tolua_S,"setDesignResolution",tolua_Cocos2d_CCView_setDesignResolution00);
   tolua_function(tolua_S,"setScissorRect",tolua_Cocos2d_CCView_setScissorRect00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCView_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCFileUtils","",NULL);
  tolua_beginmodule(tolua_S,"CCFileUtils");
   tolua_variable(tolua_S,"writablePath",tolua_get_CCFileUtils_writablePath,NULL);
   tolua_variable(tolua_S,"popupNotify",tolua_get_CCFileUtils_popupNotify,tolua_set_CCFileUtils_popupNotify);
   tolua_function(tolua_S,"getFullPath",tolua_Cocos2d_CCFileUtils_getFullPath00);
   tolua_function(tolua_S,"getRelativeFullPath",tolua_Cocos2d_CCFileUtils_getRelativeFullPath00);
   tolua_function(tolua_S,"loadFileLookupInfo",tolua_Cocos2d_CCFileUtils_loadFileLookupInfo00);
   tolua_function(tolua_S,"addSearchPath",tolua_Cocos2d_CCFileUtils_addSearchPath00);
   tolua_function(tolua_S,"addSearchResolutionsOrder",tolua_Cocos2d_CCFileUtils_addSearchResolutionsOrder00);
   tolua_function(tolua_S,"purgeCachedEntries",tolua_Cocos2d_CCFileUtils_purgeCachedEntries00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCFileUtils_new00_local);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"CCLanguageType",0);
  tolua_beginmodule(tolua_S,"CCLanguageType");
   tolua_constant(tolua_S,"English",kLanguageEnglish);
   tolua_constant(tolua_S,"Chinese",kLanguageChinese);
   tolua_constant(tolua_S,"French",kLanguageFrench);
   tolua_constant(tolua_S,"Italian",kLanguageItalian);
   tolua_constant(tolua_S,"German",kLanguageGerman);
   tolua_constant(tolua_S,"Spanish",kLanguageSpanish);
   tolua_constant(tolua_S,"Russian",kLanguageRussian);
   tolua_constant(tolua_S,"Korean",kLanguageKorean);
   tolua_constant(tolua_S,"Japanese",kLanguageJapanese);
   tolua_constant(tolua_S,"Hungarian",kLanguageHungarian);
   tolua_constant(tolua_S,"Portuguese",kLanguagePortuguese);
   tolua_constant(tolua_S,"Arabic",kLanguageArabic);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"CCTargetPlatform",0);
  tolua_beginmodule(tolua_S,"CCTargetPlatform");
   tolua_constant(tolua_S,"Windows",kTargetWindows);
   tolua_constant(tolua_S,"Linux",kTargetLinux);
   tolua_constant(tolua_S,"MacOS",kTargetMacOS);
   tolua_constant(tolua_S,"Android",kTargetAndroid);
   tolua_constant(tolua_S,"Iphone",kTargetIphone);
   tolua_constant(tolua_S,"Ipad",kTargetIpad);
   tolua_constant(tolua_S,"BlackBerry",kTargetBlackBerry);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCApplication","",NULL);
  tolua_beginmodule(tolua_S,"CCApplication");
   tolua_variable(tolua_S,"currentLanguage",tolua_get_CCApplication_currentLanguage,NULL);
   tolua_variable(tolua_S,"targetPlatform",tolua_get_CCApplication_targetPlatform,NULL);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCApplication_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCDirector","",NULL);
  tolua_beginmodule(tolua_S,"CCDirector");
   tolua_variable(tolua_S,"currentScene",tolua_get_CCDirector_currentScene_ptr,NULL);
   tolua_variable(tolua_S,"animationInterval",tolua_get_CCDirector_animationInterval,NULL);
   tolua_variable(tolua_S,"paused",tolua_get_CCDirector_paused,NULL);
   tolua_variable(tolua_S,"winSize",tolua_get_CCDirector_winSize,NULL);
   tolua_variable(tolua_S,"visibleSize",tolua_get_CCDirector_visibleSize,NULL);
   tolua_variable(tolua_S,"visibleOrigin",tolua_get_CCDirector_visibleOrigin,NULL);
   tolua_variable(tolua_S,"displayStats",tolua_get_CCDirector_displayStats,tolua_set_CCDirector_displayStats);
   tolua_variable(tolua_S,"contentScaleFactor",tolua_get_CCDirector_contentScaleFactor,tolua_set_CCDirector_contentScaleFactor);
   tolua_variable(tolua_S,"notificationNode",tolua_get_CCDirector_notificationNode_ptr,tolua_set_CCDirector_notificationNode_ptr);
   tolua_variable(tolua_S,"scheduler",tolua_get_CCDirector_scheduler_ptr,tolua_set_CCDirector_scheduler_ptr);
   tolua_function(tolua_S,"convertToUI",tolua_Cocos2d_CCDirector_convertToUI00);
   tolua_function(tolua_S,"run",tolua_Cocos2d_CCDirector_run00);
   tolua_function(tolua_S,"pause",tolua_Cocos2d_CCDirector_pause00);
   tolua_function(tolua_S,"resume",tolua_Cocos2d_CCDirector_resume00);
   tolua_function(tolua_S,"stop",tolua_Cocos2d_CCDirector_stop00);
   tolua_function(tolua_S,"purge",tolua_Cocos2d_CCDirector_purge00);
   tolua_function(tolua_S,"pushScene",tolua_Cocos2d_CCDirector_pushScene00);
   tolua_function(tolua_S,"popScene",tolua_Cocos2d_CCDirector_popScene00);
   tolua_function(tolua_S,"popToRootScene",tolua_Cocos2d_CCDirector_popToRootScene00);
   tolua_function(tolua_S,"replaceScene",tolua_Cocos2d_CCDirector_replaceScene00);
   tolua_function(tolua_S,"setDepthTest",tolua_Cocos2d_CCDirector_setDepthTest00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCDirector_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCUserDefault","",NULL);
  tolua_beginmodule(tolua_S,"CCUserDefault");
   tolua_variable(tolua_S,"filePath",tolua_get_CCUserDefault_filePath,NULL);
   tolua_function(tolua_S,"get",tolua_Cocos2d_CCUserDefault_get02);
   tolua_function(tolua_S,"set",tolua_Cocos2d_CCUserDefault_set02);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCUserDefault_new00_local);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"CCKeypad",0);
  tolua_beginmodule(tolua_S,"CCKeypad");
   tolua_constant(tolua_S,"Back",CCKeypad::Back);
   tolua_constant(tolua_S,"Menu",CCKeypad::Menu);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCImage","CCObject",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCImage");
   tolua_constant(tolua_S,"JPG",kCCImageFormatJPEG);
   tolua_constant(tolua_S,"PNG",kCCImageFormatPNG);
   tolua_variable(tolua_S,"width",tolua_get_CCImage_width,NULL);
   tolua_variable(tolua_S,"height",tolua_get_CCImage_height,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCNode","CCObject",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCNode");
   tolua_constant(tolua_S,"InvalidTag",CCNode::InvalidTag);
   tolua_constant(tolua_S,"Enter",CCNode::Enter);
   tolua_constant(tolua_S,"Exit",CCNode::Exit);
   tolua_constant(tolua_S,"EnterTransitionDidFinish",CCNode::EnterTransitionDidFinish);
   tolua_constant(tolua_S,"ExitTransitionDidStart",CCNode::ExitTransitionDidStart);
   tolua_constant(tolua_S,"Cleanup",CCNode::Cleanup);
   tolua_variable(tolua_S,"zOrder",tolua_get_CCNode_zOrder,NULL);
   tolua_variable(tolua_S,"rotation",tolua_get_CCNode_rotation,tolua_set_CCNode_rotation);
   tolua_variable(tolua_S,"scaleX",tolua_get_CCNode_scaleX,tolua_set_CCNode_scaleX);
   tolua_variable(tolua_S,"scaleY",tolua_get_CCNode_scaleY,tolua_set_CCNode_scaleY);
   tolua_variable(tolua_S,"position",tolua_get_CCNode_position,tolua_set_CCNode_position);
   tolua_variable(tolua_S,"positionX",tolua_get_CCNode_positionX,tolua_set_CCNode_positionX);
   tolua_variable(tolua_S,"positionY",tolua_get_CCNode_positionY,tolua_set_CCNode_positionY);
   tolua_variable(tolua_S,"positionZ",tolua_get_CCNode_positionZ,tolua_set_CCNode_positionZ);
   tolua_variable(tolua_S,"skewX",tolua_get_CCNode_skewX,tolua_set_CCNode_skewX);
   tolua_variable(tolua_S,"skewY",tolua_get_CCNode_skewY,tolua_set_CCNode_skewY);
   tolua_variable(tolua_S,"visible",tolua_get_CCNode_visible,tolua_set_CCNode_visible);
   tolua_variable(tolua_S,"anchorPoint",tolua_get_CCNode_anchorPoint,tolua_set_CCNode_anchorPoint);
   tolua_variable(tolua_S,"contentSize",tolua_get_CCNode_contentSize,tolua_set_CCNode_contentSize);
   tolua_variable(tolua_S,"tag",tolua_get_CCNode_tag,tolua_set_CCNode_tag);
   tolua_variable(tolua_S,"color",tolua_get_CCNode_color,tolua_set_CCNode_color);
   tolua_variable(tolua_S,"opacity",tolua_get_CCNode_opacity,tolua_set_CCNode_opacity);
   tolua_variable(tolua_S,"cascadeOpacity",tolua_get_CCNode_cascadeOpacity,tolua_set_CCNode_cascadeOpacity);
   tolua_variable(tolua_S,"cascadeColor",tolua_get_CCNode_cascadeColor,tolua_set_CCNode_cascadeColor);
   tolua_variable(tolua_S,"transformTarget",tolua_get_CCNode_transformTarget_ptr,tolua_set_CCNode_transformTarget_ptr);
   tolua_variable(tolua_S,"scheduler",tolua_get_CCNode_scheduler_ptr,tolua_set_CCNode_scheduler_ptr);
   tolua_variable(tolua_S,"parent",tolua_get_CCNode_parent_ptr,NULL);
   tolua_variable(tolua_S,"boundingBox",tolua_get_CCNode_boundingBox,NULL);
   tolua_variable(tolua_S,"description",tolua_get_CCNode_description,NULL);
   tolua_variable(tolua_S,"numberOfRunningActions",tolua_get_CCNode_numberOfRunningActions,NULL);
   tolua_variable(tolua_S,"children",tolua_get_CCNode_children_ptr,NULL);
   tolua_variable(tolua_S,"running",tolua_get_CCNode_running,NULL);
   tolua_function(tolua_S,"addChild",tolua_Cocos2d_CCNode_addChild02);
   tolua_function(tolua_S,"removeChild",tolua_Cocos2d_CCNode_removeChild00);
   tolua_function(tolua_S,"removeChildByTag",tolua_Cocos2d_CCNode_removeChildByTag00);
   tolua_function(tolua_S,"removeAllChildren",tolua_Cocos2d_CCNode_removeAllChildren00);
   tolua_function(tolua_S,"reorderChild",tolua_Cocos2d_CCNode_reorderChild00);
   tolua_function(tolua_S,"runAction",tolua_Cocos2d_CCNode_runAction00);
   tolua_function(tolua_S,"stopAllActions",tolua_Cocos2d_CCNode_stopAllActions00);
   tolua_function(tolua_S,"stopAction",tolua_Cocos2d_CCNode_stopAction00);
   tolua_function(tolua_S,"stopActionByTag",tolua_Cocos2d_CCNode_stopActionByTag00);
   tolua_function(tolua_S,"getActionByTag",tolua_Cocos2d_CCNode_getActionByTag00);
   tolua_function(tolua_S,"getChildByTag",tolua_Cocos2d_CCNode_getChildByTag00);
   tolua_function(tolua_S,"scheduleUpdate",tolua_Cocos2d_CCNode_scheduleUpdate00);
   tolua_function(tolua_S,"unscheduleUpdate",tolua_Cocos2d_CCNode_unscheduleUpdate00);
   tolua_function(tolua_S,"registerEventHandler",tolua_Cocos2d_CCNode_registerEventHandler00);
   tolua_function(tolua_S,"unregisterEventHandler",tolua_Cocos2d_CCNode_unregisterEventHandler00);
   tolua_function(tolua_S,"convertToNodeSpace",tolua_Cocos2d_CCNode_convertToNodeSpace00);
   tolua_function(tolua_S,"convertToWorldSpace",tolua_Cocos2d_CCNode_convertToWorldSpace00);
   tolua_function(tolua_S,"convertToGameSpace",tolua_Cocos2d_CCNode_convertToGameSpace00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCNode_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCDrawNode","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCDrawNode");
   tolua_function(tolua_S,"drawDot",tolua_Cocos2d_CCDrawNode_drawDot00);
   tolua_function(tolua_S,"drawSegment",tolua_Cocos2d_CCDrawNode_drawSegment00);
   tolua_function(tolua_S,"drawPolygon",tolua_Cocos2d_CCDrawNode_drawPolygon01);
   tolua_function(tolua_S,"clear",tolua_Cocos2d_CCDrawNode_clear00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCDrawNode_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCTexture2D","CCObject",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCTexture2D");
   tolua_constant(tolua_S,"RGB888",kCCTexture2DPixelFormat_RGB888);
   tolua_constant(tolua_S,"RGB565",kCCTexture2DPixelFormat_RGB565);
   tolua_constant(tolua_S,"A8",kCCTexture2DPixelFormat_A8);
   tolua_constant(tolua_S,"I8",kCCTexture2DPixelFormat_I8);
   tolua_constant(tolua_S,"AI88",kCCTexture2DPixelFormat_AI88);
   tolua_constant(tolua_S,"RGBA4444",kCCTexture2DPixelFormat_RGBA4444);
   tolua_constant(tolua_S,"RGB5A1",kCCTexture2DPixelFormat_RGB5A1);
   tolua_constant(tolua_S,"PVRTC4",kCCTexture2DPixelFormat_PVRTC4);
   tolua_constant(tolua_S,"PVRTC2",kCCTexture2DPixelFormat_PVRTC2);
   tolua_constant(tolua_S,"Default",kCCTexture2DPixelFormat_Default);
   tolua_constant(tolua_S,"RGBA8888",kCCTexture2DPixelFormat_RGBA8888);
   tolua_variable(tolua_S,"size",tolua_get_CCTexture2D_size,NULL);
   tolua_variable(tolua_S,"hasMipmaps",tolua_get_CCTexture2D_hasMipmaps,NULL);
   tolua_variable(tolua_S,"antiAlias",tolua_get_CCTexture2D_antiAlias,tolua_set_CCTexture2D_antiAlias);
   tolua_variable(tolua_S,"pixelFormat",tolua_get_CCTexture2D_pixelFormat,tolua_set_CCTexture2D_pixelFormat);
   tolua_function(tolua_S,"generateMipmap",tolua_Cocos2d_CCTexture2D_generateMipmap00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCTextureCache","",NULL);
  tolua_beginmodule(tolua_S,"CCTextureCache");
   tolua_function(tolua_S,"add",tolua_Cocos2d_CCTextureCache_add00);
   tolua_function(tolua_S,"load",tolua_Cocos2d_CCTextureCache_load00);
   tolua_function(tolua_S,"unload",tolua_Cocos2d_CCTextureCache_unload00);
   tolua_function(tolua_S,"removeUnused",tolua_Cocos2d_CCTextureCache_removeUnused00);
   tolua_function(tolua_S,"remove",tolua_Cocos2d_CCTextureCache_remove01);
   tolua_function(tolua_S,"dumpInfo",tolua_Cocos2d_CCTextureCache_dumpInfo00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCTextureCache_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCRenderTarget","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCRenderTarget");
   tolua_function(tolua_S,"beginPaint",tolua_Cocos2d_CCRenderTarget_beginPaint01);
   tolua_function(tolua_S,"draw",tolua_Cocos2d_CCRenderTarget_draw00);
   tolua_function(tolua_S,"endPaint",tolua_Cocos2d_CCRenderTarget_endPaint00);
   tolua_function(tolua_S,"save",tolua_Cocos2d_CCRenderTarget_save00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCRenderTarget_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCSprite","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCSprite");
   tolua_variable(tolua_S,"texture",tolua_get_CCSprite_texture_ptr,tolua_set_CCSprite_texture_ptr);
   tolua_variable(tolua_S,"textureRect",tolua_get_CCSprite_textureRect,tolua_set_CCSprite_textureRect);
   tolua_variable(tolua_S,"blendFunc",tolua_get_CCSprite_blendFunc,tolua_set_CCSprite_blendFunc);
   tolua_variable(tolua_S,"flipX",tolua_get_CCSprite_flipX,tolua_set_CCSprite_flipX);
   tolua_variable(tolua_S,"flipY",tolua_get_CCSprite_flipY,tolua_set_CCSprite_flipY);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCSprite_new03_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCSpriteBatchNode","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCSpriteBatchNode");
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCSpriteBatchNode_new03_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCLayer","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCLayer");
   tolua_constant(tolua_S,"TouchesAllAtOnce",CCLayer::TouchesAllAtOnce);
   tolua_constant(tolua_S,"TouchesOneByOne",CCLayer::TouchesOneByOne);
   tolua_variable(tolua_S,"touchEnabled",tolua_get_CCLayer_touchEnabled,tolua_set_CCLayer_touchEnabled);
   tolua_variable(tolua_S,"accelerometerEnabled",tolua_get_CCLayer_accelerometerEnabled,tolua_set_CCLayer_accelerometerEnabled);
   tolua_variable(tolua_S,"keypadEnabled",tolua_get_CCLayer_keypadEnabled,tolua_set_CCLayer_keypadEnabled);
   tolua_variable(tolua_S,"touchMode",tolua_get_CCLayer_touchMode,tolua_set_CCLayer_touchMode);
   tolua_variable(tolua_S,"touchPriority",tolua_get_CCLayer_touchPriority,tolua_set_CCLayer_touchPriority);
   tolua_function(tolua_S,"registerTouchHandler",tolua_Cocos2d_CCLayer_registerTouchHandler00);
   tolua_function(tolua_S,"unregisterTouchHandler",tolua_Cocos2d_CCLayer_unregisterTouchHandler00);
   tolua_function(tolua_S,"registerKeypadHandler",tolua_Cocos2d_CCLayer_registerKeypadHandler00);
   tolua_function(tolua_S,"unregisterKeypadHandler",tolua_Cocos2d_CCLayer_unregisterKeypadHandler00);
   tolua_function(tolua_S,"registerAccelerateHandler",tolua_Cocos2d_CCLayer_registerAccelerateHandler00);
   tolua_function(tolua_S,"unregisterAccelerateHandler",tolua_Cocos2d_CCLayer_unregisterAccelerateHandler00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCLayer_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCLayerColor","CCLayer",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCLayerColor");
   tolua_variable(tolua_S,"blendFunc",tolua_get_CCLayerColor_blendFunc,tolua_set_CCLayerColor_blendFunc);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCLayerColor_new01_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCLayerGradient","CCLayer",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCLayerGradient");
   tolua_variable(tolua_S,"blendFunc",tolua_get_CCLayerGradient_blendFunc,tolua_set_CCLayerGradient_blendFunc);
   tolua_variable(tolua_S,"startColor",tolua_get_CCLayerGradient_startColor,tolua_set_CCLayerGradient_startColor);
   tolua_variable(tolua_S,"endColor",tolua_get_CCLayerGradient_endColor,tolua_set_CCLayerGradient_endColor);
   tolua_variable(tolua_S,"startOpacity",tolua_get_CCLayerGradient_startOpacity,tolua_set_CCLayerGradient_startOpacity);
   tolua_variable(tolua_S,"endOpacity",tolua_get_CCLayerGradient_endOpacity,tolua_set_CCLayerGradient_endOpacity);
   tolua_variable(tolua_S,"vector",tolua_get_CCLayerGradient_vector,tolua_set_CCLayerGradient_vector);
   tolua_variable(tolua_S,"compressedInterpolation",tolua_get_CCLayerGradient_compressedInterpolation,tolua_set_CCLayerGradient_compressedInterpolation);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCLayerGradient_new02_local);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"CCOrientation",0);
  tolua_beginmodule(tolua_S,"CCOrientation");
   tolua_constant(tolua_S,"Left",kCCTransitionOrientationLeftOver);
   tolua_constant(tolua_S,"Right",kCCTransitionOrientationRightOver);
   tolua_constant(tolua_S,"Up",kCCTransitionOrientationUpOver);
   tolua_constant(tolua_S,"Down",kCCTransitionOrientationDownOver);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCScene","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCScene");
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCScene_new00_local);
   tolua_function(tolua_S,"oriented",tolua_Cocos2d_CCScene_oriented00);
   tolua_function(tolua_S,"rotoZoom",tolua_Cocos2d_CCScene_rotoZoom00);
   tolua_function(tolua_S,"jumpZoom",tolua_Cocos2d_CCScene_jumpZoom00);
   tolua_function(tolua_S,"move",tolua_Cocos2d_CCScene_move00);
   tolua_function(tolua_S,"slide",tolua_Cocos2d_CCScene_slide00);
   tolua_function(tolua_S,"shrinkGrow",tolua_Cocos2d_CCScene_shrinkGrow00);
   tolua_function(tolua_S,"flipY",tolua_Cocos2d_CCScene_flipY00);
   tolua_function(tolua_S,"flipAngular",tolua_Cocos2d_CCScene_flipAngular00);
   tolua_function(tolua_S,"zoomFlipY",tolua_Cocos2d_CCScene_zoomFlipY00);
   tolua_function(tolua_S,"zoomFlipAngular",tolua_Cocos2d_CCScene_zoomFlipAngular00);
   tolua_function(tolua_S,"fade",tolua_Cocos2d_CCScene_fade00);
   tolua_function(tolua_S,"crossFade",tolua_Cocos2d_CCScene_crossFade00);
   tolua_function(tolua_S,"turnOffTiles",tolua_Cocos2d_CCScene_turnOffTiles00);
   tolua_function(tolua_S,"splitCols",tolua_Cocos2d_CCScene_splitCols00);
   tolua_function(tolua_S,"splitRows",tolua_Cocos2d_CCScene_splitRows00);
   tolua_function(tolua_S,"fadeTiles",tolua_Cocos2d_CCScene_fadeTiles00);
   tolua_function(tolua_S,"pageTurn",tolua_Cocos2d_CCScene_pageTurn00);
   tolua_function(tolua_S,"progressCCW",tolua_Cocos2d_CCScene_progressCCW00);
   tolua_function(tolua_S,"progressCW",tolua_Cocos2d_CCScene_progressCW00);
   tolua_function(tolua_S,"progressV",tolua_Cocos2d_CCScene_progressV00);
   tolua_function(tolua_S,"progressOI",tolua_Cocos2d_CCScene_progressOI00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCScheduler","CCObject",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCScheduler");
   tolua_variable(tolua_S,"timeScale",tolua_get_CCScheduler_timeScale,tolua_set_CCScheduler_timeScale);
   tolua_function(tolua_S,"shedule",tolua_Cocos2d_CCScheduler_shedule00);
   tolua_function(tolua_S,"unshedule",tolua_Cocos2d_CCScheduler_unshedule00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCScheduler_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCAction","CCObject",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCAction");
   tolua_variable(tolua_S,"done",tolua_get_CCAction_done,NULL);
   tolua_variable(tolua_S,"target",tolua_get_CCAction_target_ptr,NULL);
   tolua_variable(tolua_S,"tag",tolua_get_CCAction_tag,tolua_set_CCAction_tag);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCFiniteTimeAction","CCAction",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCFiniteTimeAction");
   tolua_variable(tolua_S,"duration",tolua_get_CCFiniteTimeAction_duration,NULL);
   tolua_function(tolua_S,"reverse",tolua_Cocos2d_CCFiniteTimeAction_reverse00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCActionInterval","CCFiniteTimeAction",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCActionInterval");
   tolua_variable(tolua_S,"elapsed",tolua_get_CCActionInterval_elapsed,NULL);
   tolua_function(tolua_S,"reverse",tolua_Cocos2d_CCActionInterval_reverse00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCSpeed","CCAction",NULL);
  tolua_beginmodule(tolua_S,"CCSpeed");
   tolua_variable(tolua_S,"rate",tolua_get_CCSpeed_rate,tolua_set_CCSpeed_rate);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCSpeed_new00_local);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"CCFollow",tolua_Cocos2d_CCFollow00);
  tolua_function(tolua_S,"CCFollow",tolua_Cocos2d_CCFollow01);
  tolua_function(tolua_S,"CCSequence",tolua_Cocos2d_CCSequence00);
  tolua_function(tolua_S,"CCRepeat",tolua_Cocos2d_CCRepeat00);
  tolua_function(tolua_S,"CCRepeatForever",tolua_Cocos2d_CCRepeatForever00);
  tolua_function(tolua_S,"CCSpawn",tolua_Cocos2d_CCSpawn00);
  tolua_function(tolua_S,"CCJumpBy",tolua_Cocos2d_CCJumpBy00);
  tolua_function(tolua_S,"CCJumpTo",tolua_Cocos2d_CCJumpTo00);
  tolua_function(tolua_S,"CCBezierBy",tolua_Cocos2d_CCBezierBy00);
  tolua_function(tolua_S,"CCBezierTo",tolua_Cocos2d_CCBezierTo00);
  tolua_function(tolua_S,"CCBlink",tolua_Cocos2d_CCBlink00);
  tolua_function(tolua_S,"CCTintTo",tolua_Cocos2d_CCTintTo00);
  tolua_function(tolua_S,"CCTintBy",tolua_Cocos2d_CCTintBy00);
  tolua_function(tolua_S,"CCDelay",tolua_Cocos2d_CCDelay00);
  tolua_function(tolua_S,"CCShow",tolua_Cocos2d_CCShow00);
  tolua_function(tolua_S,"CCHide",tolua_Cocos2d_CCHide00);
  tolua_function(tolua_S,"CCToggleVisibility",tolua_Cocos2d_CCToggleVisibility00);
  tolua_function(tolua_S,"CCFlipY",tolua_Cocos2d_CCFlipY00);
  tolua_function(tolua_S,"CCFlipY",tolua_Cocos2d_CCFlipY01);
  tolua_function(tolua_S,"CCPlace",tolua_Cocos2d_CCPlace00);
  tolua_function(tolua_S,"CCCall",tolua_Cocos2d_CCCall00);
  tolua_function(tolua_S,"CCOrbitCamera",tolua_Cocos2d_CCOrbitCamera00);
  tolua_function(tolua_S,"CCCardinalSplineTo",tolua_Cocos2d_CCCardinalSplineTo00);
  tolua_function(tolua_S,"CCCardinalSplineBy",tolua_Cocos2d_CCCardinalSplineBy00);
  tolua_function(tolua_S,"CCCatmullRomTo",tolua_Cocos2d_CCCatmullRomTo00);
  tolua_function(tolua_S,"CCCatmullRomBy",tolua_Cocos2d_CCCatmullRomBy00);
  tolua_module(tolua_S,"CCGrid",0);
  tolua_beginmodule(tolua_S,"CCGrid");
   tolua_function(tolua_S,"stop",tolua_Cocos2d_CCGrid_stop00);
   tolua_function(tolua_S,"reuse",tolua_Cocos2d_CCGrid_reuse00);
   tolua_function(tolua_S,"waves3D",tolua_Cocos2d_CCGrid_waves3D00);
   tolua_function(tolua_S,"flipX3D",tolua_Cocos2d_CCGrid_flipX3D00);
   tolua_function(tolua_S,"flipY3D",tolua_Cocos2d_CCGrid_flipY3D00);
   tolua_function(tolua_S,"lens3D",tolua_Cocos2d_CCGrid_lens3D00);
   tolua_function(tolua_S,"ripple3D",tolua_Cocos2d_CCGrid_ripple3D00);
   tolua_function(tolua_S,"shaky3D",tolua_Cocos2d_CCGrid_shaky3D00);
   tolua_function(tolua_S,"liquid",tolua_Cocos2d_CCGrid_liquid00);
   tolua_function(tolua_S,"waves",tolua_Cocos2d_CCGrid_waves00);
   tolua_function(tolua_S,"twirl",tolua_Cocos2d_CCGrid_twirl00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"CCTile",0);
  tolua_beginmodule(tolua_S,"CCTile");
   tolua_function(tolua_S,"shaky3D",tolua_Cocos2d_CCTile_shaky3D00);
   tolua_function(tolua_S,"shattered3D",tolua_Cocos2d_CCTile_shattered3D00);
   tolua_function(tolua_S,"shuffle",tolua_Cocos2d_CCTile_shuffle00);
   tolua_function(tolua_S,"fadeOut",tolua_Cocos2d_CCTile_fadeOut00);
   tolua_function(tolua_S,"turnOff",tolua_Cocos2d_CCTile_turnOff00);
   tolua_function(tolua_S,"waves3D",tolua_Cocos2d_CCTile_waves3D00);
   tolua_function(tolua_S,"jump3D",tolua_Cocos2d_CCTile_jump3D00);
   tolua_function(tolua_S,"splitRows",tolua_Cocos2d_CCTile_splitRows00);
   tolua_function(tolua_S,"splitCols",tolua_Cocos2d_CCTile_splitCols00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"CCPageTurn3D",tolua_Cocos2d_CCPageTurn3D00);
  tolua_function(tolua_S,"CCProgressTo",tolua_Cocos2d_CCProgressTo00);
  tolua_function(tolua_S,"CCProgressFromTo",tolua_Cocos2d_CCProgressFromTo00);
  tolua_cclass(tolua_S,"CCMotionStreak","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCMotionStreak");
   tolua_variable(tolua_S,"texture",tolua_get_CCMotionStreak_texture_ptr,tolua_set_CCMotionStreak_texture_ptr);
   tolua_variable(tolua_S,"blendFunc",tolua_get_CCMotionStreak_blendFunc,tolua_set_CCMotionStreak_blendFunc);
   tolua_variable(tolua_S,"fastMode",tolua_get_CCMotionStreak_fastMode,tolua_set_CCMotionStreak_fastMode);
   tolua_variable(tolua_S,"startPosInit",tolua_get_CCMotionStreak_startPosInit,tolua_set_CCMotionStreak_startPosInit);
   tolua_function(tolua_S,"tintWithColor",tolua_Cocos2d_CCMotionStreak_tintWithColor00);
   tolua_function(tolua_S,"reset",tolua_Cocos2d_CCMotionStreak_reset00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCMotionStreak_new01_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCClipNode","CCNode",NULL);
  tolua_beginmodule(tolua_S,"CCClipNode");
   tolua_variable(tolua_S,"stencil",tolua_get_CCClippingNode_stencil_ptr,tolua_set_CCClippingNode_stencil_ptr);
   tolua_variable(tolua_S,"alphaThreshold",tolua_get_CCClippingNode_alphaThreshold,tolua_set_CCClippingNode_alphaThreshold);
   tolua_variable(tolua_S,"inverted",tolua_get_CCClippingNode_inverted,tolua_set_CCClippingNode_inverted);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCClipNode_new01_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCLabelAtlas","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCLabelAtlas");
   tolua_variable(tolua_S,"text",tolua_get_CCLabelAtlas_text,tolua_set_CCLabelAtlas_text);
   tolua_variable(tolua_S,"texture",tolua_get_CCLabelAtlas_texture_ptr,tolua_set_CCLabelAtlas_texture_ptr);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCLabelAtlas_new01_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCLabelBMFont","CCSpriteBatchNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCLabelBMFont");
   tolua_constant(tolua_S,"AutomaticWidth",kCCLabelAutomaticWidth);
   tolua_variable(tolua_S,"text",tolua_get_CCLabelBMFont_text,tolua_set_CCLabelBMFont_text);
   tolua_variable(tolua_S,"fntFile",tolua_get_CCLabelBMFont_fntFile,tolua_set_CCLabelBMFont_fntFile);
   tolua_function(tolua_S,"setAlignment",tolua_Cocos2d_CCLabelBMFont_setAlignment00);
   tolua_function(tolua_S,"setWidth",tolua_Cocos2d_CCLabelBMFont_setWidth00);
   tolua_function(tolua_S,"setLineBreakWithoutSpace",tolua_Cocos2d_CCLabelBMFont_setLineBreakWithoutSpace00);
   tolua_function(tolua_S,"purgeCachedData",tolua_Cocos2d_CCLabelBMFont_purgeCachedData00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCLabelBMFont_new01_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCLabelTTF","CCSprite",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCLabelTTF");
   tolua_variable(tolua_S,"text",tolua_get_CCLabelTTF_text,tolua_set_CCLabelTTF_text);
   tolua_variable(tolua_S,"horizontalAlignment",tolua_get_CCLabelTTF_horizontalAlignment,tolua_set_CCLabelTTF_horizontalAlignment);
   tolua_variable(tolua_S,"verticalAlignment",tolua_get_CCLabelTTF_verticalAlignment,tolua_set_CCLabelTTF_verticalAlignment);
   tolua_variable(tolua_S,"dimensions",tolua_get_CCLabelTTF_dimensions,tolua_set_CCLabelTTF_dimensions);
   tolua_variable(tolua_S,"fontSize",tolua_get_CCLabelTTF_fontSize,tolua_set_CCLabelTTF_fontSize);
   tolua_variable(tolua_S,"fontName",tolua_get_CCLabelTTF_fontName,tolua_set_CCLabelTTF_fontName);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCLabelTTF_new02_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCMenu","CCLayer",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCMenu");
   tolua_constant(tolua_S,"DefaultHandlerPriority",kCCMenuHandlerPriority);
   tolua_variable(tolua_S,"enabled",tolua_get_CCMenu_enabled,tolua_set_CCMenu_enabled);
   tolua_function(tolua_S,"alignItemsVertically",tolua_Cocos2d_CCMenu_alignItemsVertically01);
   tolua_function(tolua_S,"alignItemsHorizontally",tolua_Cocos2d_CCMenu_alignItemsHorizontally01);
   tolua_function(tolua_S,"setHandlerPriority",tolua_Cocos2d_CCMenu_setHandlerPriority00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCMenu_new01_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCMenuItem","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCMenuItem");
   tolua_constant(tolua_S,"TapBegan",CCMenuItem::TapBegan);
   tolua_constant(tolua_S,"Tapped",CCMenuItem::Tapped);
   tolua_constant(tolua_S,"TapEnded",CCMenuItem::TapEnded);
   tolua_variable(tolua_S,"hitArea",tolua_get_CCMenuItem_hitArea,NULL);
   tolua_variable(tolua_S,"selected",tolua_get_CCMenuItem_selected,NULL);
   tolua_variable(tolua_S,"enabled",tolua_get_CCMenuItem_enabled,tolua_set_CCMenuItem_enabled);
   tolua_function(tolua_S,"registerTapHandler",tolua_Cocos2d_CCMenuItem_registerTapHandler00);
   tolua_function(tolua_S,"unregisterTapHandler",tolua_Cocos2d_CCMenuItem_unregisterTapHandler00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCMenuItem_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCParallaxNode","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCParallaxNode");
   tolua_function(tolua_S,"addChild",tolua_Cocos2d_CCParallaxNode_addChild00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCParallaxNode_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCProgressTimer","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCProgressTimer");
   tolua_constant(tolua_S,"Radial",kCCProgressTimerTypeRadial);
   tolua_constant(tolua_S,"Bar",kCCProgressTimerTypeBar);
   tolua_variable(tolua_S,"midPoint",tolua_get_CCProgressTimer_midPoint,tolua_set_CCProgressTimer_midPoint);
   tolua_variable(tolua_S,"type",tolua_get_CCProgressTimer_type,tolua_set_CCProgressTimer_type);
   tolua_variable(tolua_S,"percentage",tolua_get_CCProgressTimer_percentage,tolua_set_CCProgressTimer_percentage);
   tolua_variable(tolua_S,"sprite",tolua_get_CCProgressTimer_sprite_ptr,tolua_set_CCProgressTimer_sprite_ptr);
   tolua_variable(tolua_S,"barChangeRate",tolua_get_CCProgressTimer_barChangeRate,tolua_set_CCProgressTimer_barChangeRate);
   tolua_variable(tolua_S,"reverseDirection",tolua_get_CCProgressTimer_reverseDirection,tolua_set_CCProgressTimer_reverseDirection);
   tolua_function(tolua_S,"setReverseProgress",tolua_Cocos2d_CCProgressTimer_setReverseProgress00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCProgressTimer_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCTextFieldTTF","CCLabelTTF",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCTextFieldTTF");
   tolua_constant(tolua_S,"Attach",oTextFieldEvent::Attach);
   tolua_constant(tolua_S,"Detach",oTextFieldEvent::Detach);
   tolua_constant(tolua_S,"Insert",oTextFieldEvent::Insert);
   tolua_constant(tolua_S,"Inserted",oTextFieldEvent::Inserted);
   tolua_constant(tolua_S,"Delete",oTextFieldEvent::Delete);
   tolua_constant(tolua_S,"Deleted",oTextFieldEvent::Deleted);
   tolua_function(tolua_S,"attachWithIME",tolua_Cocos2d_CCTextFieldTTF_attachWithIME00);
   tolua_function(tolua_S,"detachWithIME",tolua_Cocos2d_CCTextFieldTTF_detachWithIME00);
   tolua_variable(tolua_S,"colorSpaceHolder",tolua_get_CCTextFieldTTF_colorSpaceHolder,tolua_set_CCTextFieldTTF_colorSpaceHolder);
   tolua_variable(tolua_S,"text",tolua_get_CCTextFieldTTF_text,tolua_set_CCTextFieldTTF_text);
   tolua_variable(tolua_S,"placeHolder",tolua_get_CCTextFieldTTF_placeHolder,tolua_set_CCTextFieldTTF_placeHolder);
   tolua_function(tolua_S,"registerInputHandler",tolua_Cocos2d_CCTextFieldTTF_registerInputHandler00);
   tolua_function(tolua_S,"unregisterInputHandler",tolua_Cocos2d_CCTextFieldTTF_unregisterInputHandler00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCTextFieldTTF_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCTileMapAtlas","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCTileMapAtlas");
   tolua_function(tolua_S,"setTile",tolua_Cocos2d_CCTileMapAtlas_setTile00);
   tolua_function(tolua_S,"getTile",tolua_Cocos2d_CCTileMapAtlas_getTile00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCTileMapAtlas_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCTMXLayer","CCSpriteBatchNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCTMXLayer");
   tolua_variable(tolua_S,"layerSize",tolua_get_CCTMXLayer_layerSize,NULL);
   tolua_variable(tolua_S,"mapTileSize",tolua_get_CCTMXLayer_mapTileSize,NULL);
   tolua_variable(tolua_S,"layerName",tolua_get_CCTMXLayer_layerName,NULL);
   tolua_function(tolua_S,"getTile",tolua_Cocos2d_CCTMXLayer_getTile00);
   tolua_function(tolua_S,"getTileGID",tolua_Cocos2d_CCTMXLayer_getTileGID00);
   tolua_function(tolua_S,"removeTile",tolua_Cocos2d_CCTMXLayer_removeTile00);
   tolua_function(tolua_S,"getPosition",tolua_Cocos2d_CCTMXLayer_getPosition00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCTMXTiledMap","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCTMXTiledMap");
   tolua_constant(tolua_S,"Ortho",CCTMXOrientationOrtho);
   tolua_constant(tolua_S,"Hex",CCTMXOrientationHex);
   tolua_constant(tolua_S,"Iso",CCTMXOrientationIso);
   tolua_variable(tolua_S,"mapSize",tolua_get_CCTMXTiledMap_mapSize,NULL);
   tolua_variable(tolua_S,"tileSize",tolua_get_CCTMXTiledMap_tileSize,NULL);
   tolua_variable(tolua_S,"mapOrientation",tolua_get_CCTMXTiledMap_mapOrientation,NULL);
   tolua_function(tolua_S,"getLayer",tolua_Cocos2d_CCTMXTiledMap_getLayer00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_CCTMXTiledMap_new01_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCTouch","CCObject",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"CCTouch");
   tolua_constant(tolua_S,"Began",CCTouch::Began);
   tolua_constant(tolua_S,"Moved",CCTouch::Moved);
   tolua_constant(tolua_S,"Ended",CCTouch::Ended);
   tolua_constant(tolua_S,"Cancelled",CCTouch::Cancelled);
   tolua_variable(tolua_S,"location",tolua_get_CCTouch_location,NULL);
   tolua_variable(tolua_S,"preLocation",tolua_get_CCTouch_preLocation,NULL);
   tolua_variable(tolua_S,"delta",tolua_get_CCTouch_delta,NULL);
   tolua_variable(tolua_S,"locationInView",tolua_get_CCTouch_locationInView,NULL);
   tolua_variable(tolua_S,"preLocationInView",tolua_get_CCTouch_preLocationInView,NULL);
   tolua_variable(tolua_S,"id",tolua_get_CCTouch_id,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oModel","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oModel");
   tolua_variable(tolua_S,"look",tolua_get_oModel_look,tolua_set_oModel_look);
   tolua_variable(tolua_S,"speed",tolua_get_oModel_speed,tolua_set_oModel_speed);
   tolua_variable(tolua_S,"loop",tolua_get_oModel_loop,tolua_set_oModel_loop);
   tolua_variable(tolua_S,"time",tolua_get_oModel_time,tolua_set_oModel_time);
   tolua_variable(tolua_S,"duration",tolua_get_oModel_duration,NULL);
   tolua_variable(tolua_S,"recovery",tolua_get_oModel_recovery,tolua_set_oModel_recovery);
   tolua_variable(tolua_S,"faceRight",tolua_get_oModel_faceRight,tolua_set_oModel_faceRight);
   tolua_variable(tolua_S,"playing",tolua_get_oModel_playing,NULL);
   tolua_variable(tolua_S,"paused",tolua_get_oModel_paused,NULL);
   tolua_variable(tolua_S,"currentAnimation",tolua_get_oModel_currentAnimation,NULL);
   tolua_function(tolua_S,"addHandler",tolua_Cocos2d_oModel_addHandler00);
   tolua_function(tolua_S,"removeHandler",tolua_Cocos2d_oModel_removeHandler00);
   tolua_function(tolua_S,"clearHandler",tolua_Cocos2d_oModel_clearHandler00);
   tolua_function(tolua_S,"getKey",tolua_Cocos2d_oModel_getKey00);
   tolua_function(tolua_S,"play",tolua_Cocos2d_oModel_play00);
   tolua_function(tolua_S,"pause",tolua_Cocos2d_oModel_pause00);
   tolua_function(tolua_S,"resume",tolua_Cocos2d_oModel_resume01);
   tolua_function(tolua_S,"stop",tolua_Cocos2d_oModel_stop00);
   tolua_function(tolua_S,"reset",tolua_Cocos2d_oModel_reset00);
   tolua_function(tolua_S,"getNodeByName",tolua_Cocos2d_oModel_getNodeByName00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oModel_new00_local);
   tolua_function(tolua_S,"none",tolua_Cocos2d_oModel_none00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oFrameAction","CCFiniteTimeAction",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oFrameAction");
   tolua_function(tolua_S,"setLoop",tolua_Cocos2d_oFrameAction_setLoop00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oFrameAction_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oFace","CCObject",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oFace");
   tolua_function(tolua_S,"addChild",tolua_Cocos2d_oFace_addChild00);
   tolua_function(tolua_S,"removeChild",tolua_Cocos2d_oFace_removeChild00);
   tolua_function(tolua_S,"toNode",tolua_Cocos2d_oFace_toNode00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oFace_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oEffect","CCObject",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oEffect");
   tolua_variable(tolua_S,"playing",tolua_get_oEffect_playing,NULL);
   tolua_function(tolua_S,"start",tolua_Cocos2d_oEffect_start00);
   tolua_function(tolua_S,"stop",tolua_Cocos2d_oEffect_stop00);
   tolua_function(tolua_S,"setOffset",tolua_Cocos2d_oEffect_setOffset00);
   tolua_function(tolua_S,"attachTo",tolua_Cocos2d_oEffect_attachTo00);
   tolua_function(tolua_S,"autoRemove",tolua_Cocos2d_oEffect_autoRemove00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oEffect_new00_local);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"oCache",0);
  tolua_beginmodule(tolua_S,"oCache");
   tolua_cclass(tolua_S,"Animation","",NULL);
   tolua_beginmodule(tolua_S,"Animation");
    tolua_function(tolua_S,"load",tolua_Cocos2d_oCache_Animation_load00);
    tolua_function(tolua_S,"update",tolua_Cocos2d_oCache_Animation_update00);
    tolua_function(tolua_S,"unload",tolua_Cocos2d_oCache_Animation_unload00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Particle","",NULL);
   tolua_beginmodule(tolua_S,"Particle");
    tolua_function(tolua_S,"load",tolua_Cocos2d_oCache_Particle_load00);
    tolua_function(tolua_S,"update",tolua_Cocos2d_oCache_Particle_update00);
    tolua_function(tolua_S,"unload",tolua_Cocos2d_oCache_Particle_unload00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Effect","",NULL);
   tolua_beginmodule(tolua_S,"Effect");
    tolua_function(tolua_S,"load",tolua_Cocos2d_oCache_Effect_load00);
    tolua_function(tolua_S,"update",tolua_Cocos2d_oCache_Effect_update00);
    tolua_function(tolua_S,"unload",tolua_Cocos2d_oCache_Effect_unload00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Model","",NULL);
   tolua_beginmodule(tolua_S,"Model");
    tolua_function(tolua_S,"load",tolua_Cocos2d_oCache_Model_load00);
    tolua_function(tolua_S,"update",tolua_Cocos2d_oCache_Model_update00);
    tolua_function(tolua_S,"unload",tolua_Cocos2d_oCache_Model_unload00);
    tolua_function(tolua_S,"getData",tolua_Cocos2d_oCache_Model_getData00);
    tolua_function(tolua_S,"loadData",tolua_Cocos2d_oCache_Model_loadData00);
    tolua_function(tolua_S,"save",tolua_Cocos2d_oCache_Model_save00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Clip","",NULL);
   tolua_beginmodule(tolua_S,"Clip");
    tolua_function(tolua_S,"load",tolua_Cocos2d_oCache_Clip_load00);
    tolua_function(tolua_S,"update",tolua_Cocos2d_oCache_Clip_update00);
    tolua_function(tolua_S,"unload",tolua_Cocos2d_oCache_Clip_unload00);
    tolua_function(tolua_S,"getNames",tolua_Cocos2d_oCache_Clip_getNames00);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"clear",tolua_Cocos2d_oCache_clear00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oNode3D","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oNode3D");
   tolua_variable(tolua_S,"rotationX",tolua_get_oNode3D_rotationX,tolua_set_oNode3D_rotationX);
   tolua_variable(tolua_S,"rotationY",tolua_get_oNode3D_rotationY,tolua_set_oNode3D_rotationY);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oNode3D_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oContent","",NULL);
  tolua_beginmodule(tolua_S,"oContent");
   tolua_variable(tolua_S,"useGameFile",tolua_get_oContent_useGameFile,tolua_set_oContent_useGameFile);
   tolua_function(tolua_S,"setGameFile",tolua_Cocos2d_oContent_setGameFile00);
   tolua_function(tolua_S,"setPassword",tolua_Cocos2d_oContent_setPassword00);
   tolua_function(tolua_S,"saveToFile",tolua_Cocos2d_oContent_saveToFile00);
   tolua_function(tolua_S,"getDirEntries",tolua_Cocos2d_oContent_getDirEntries00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oContent_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oVec2","",tolua_collect_oVec2);
  tolua_beginmodule(tolua_S,"oVec2");
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oVec2_new00_local);
   tolua_call(tolua_S,MT_ADD,tolua_Cocos2d_oVec2__add00);
   tolua_call(tolua_S,MT_SUB,tolua_Cocos2d_oVec2__sub00);
   tolua_call(tolua_S,MT_MUL,tolua_Cocos2d_oVec2__mul00);
   tolua_call(tolua_S,MT_MUL,tolua_Cocos2d_oVec2__mul01);
   tolua_call(tolua_S,MT_DIV,tolua_Cocos2d_oVec2__div00);
   tolua_call(tolua_S,MT_EQ,tolua_Cocos2d_oVec2__eq00);
   tolua_function(tolua_S,"distance",tolua_Cocos2d_oVec2_distance00);
   tolua_function(tolua_S,"distanceSquared",tolua_Cocos2d_oVec2_distanceSquared00);
   tolua_variable(tolua_S,"length",tolua_get_oVec2_length,NULL);
   tolua_variable(tolua_S,"lengthSquared",tolua_get_oVec2_lengthSquared,NULL);
   tolua_variable(tolua_S,"angle",tolua_get_oVec2_angle,NULL);
   tolua_function(tolua_S,"normalize",tolua_Cocos2d_oVec2_normalize00);
   tolua_variable(tolua_S,"x",tolua_get_oVec2_x,tolua_set_oVec2_x);
   tolua_variable(tolua_S,"y",tolua_get_oVec2_y,tolua_set_oVec2_y);
   tolua_variable(tolua_S,"zero",tolua_get_oVec2_zero,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oLine","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oLine");
   tolua_function(tolua_S,"set",tolua_Cocos2d_oLine_set00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oLine_new01_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oEvent","",NULL);
  tolua_beginmodule(tolua_S,"oEvent");
   tolua_variable(tolua_S,"name",tolua_get_oEvent_name,NULL);
   tolua_function(tolua_S,"add",tolua_Cocos2d_oEvent_add00);
   tolua_function(tolua_S,"remove",tolua_Cocos2d_oEvent_remove00);
   tolua_function(tolua_S,"send",tolua_Cocos2d_oEvent_send00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oListener","CCObject",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oListener");
   tolua_variable(tolua_S,"enabled",tolua_get_oListener_enabled,tolua_set_oListener_enabled);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oListener_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oWorld","CCLayer",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oWorld");
   tolua_variable(tolua_S,"gravity",tolua_get_oWorld_gravity,tolua_set_oWorld_gravity);
   tolua_function(tolua_S,"query",tolua_Cocos2d_oWorld_query00);
   tolua_function(tolua_S,"setIterations",tolua_Cocos2d_oWorld_setIterations00);
   tolua_function(tolua_S,"setShouldContact",tolua_Cocos2d_oWorld_setShouldContact00);
   tolua_function(tolua_S,"getShouldContact",tolua_Cocos2d_oWorld_getShouldContact00);
   tolua_variable(tolua_S,"b2Factor",tolua_get_oWorld_b2Factor,tolua_set_oWorld_b2Factor);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oWorld_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oFixtureDef","",NULL);
  tolua_beginmodule(tolua_S,"oFixtureDef");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oBodyDef","CCObject",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oBodyDef");
   tolua_constant(tolua_S,"Static",b2_staticBody);
   tolua_constant(tolua_S,"Dynamic",b2_dynamicBody);
   tolua_constant(tolua_S,"Kinematic",b2_kinematicBody);
   tolua_variable(tolua_S,"type",tolua_get_oBodyDef_type,tolua_set_oBodyDef_type);
   tolua_variable(tolua_S,"linearDamping",tolua_get_oBodyDef_linearDamping,tolua_set_oBodyDef_linearDamping);
   tolua_variable(tolua_S,"angularDamping",tolua_get_oBodyDef_angularDamping,tolua_set_oBodyDef_angularDamping);
   tolua_variable(tolua_S,"fixedRotation",tolua_get_oBodyDef_fixedRotation,tolua_set_oBodyDef_fixedRotation);
   tolua_variable(tolua_S,"bullet",tolua_get_oBodyDef_bullet,tolua_set_oBodyDef_bullet);
   tolua_variable(tolua_S,"gravityScale",tolua_get_oBodyDef_gravityScale,tolua_set_oBodyDef_gravityScale);
   tolua_function(tolua_S,"polygon",tolua_Cocos2d_oBodyDef_polygon02);
   tolua_function(tolua_S,"attachPolygon",tolua_Cocos2d_oBodyDef_attachPolygon02);
   tolua_function(tolua_S,"loop",tolua_Cocos2d_oBodyDef_loop00);
   tolua_function(tolua_S,"attachLoop",tolua_Cocos2d_oBodyDef_attachLoop00);
   tolua_function(tolua_S,"circle",tolua_Cocos2d_oBodyDef_circle01);
   tolua_function(tolua_S,"attachCircle",tolua_Cocos2d_oBodyDef_attachCircle01);
   tolua_function(tolua_S,"chain",tolua_Cocos2d_oBodyDef_chain00);
   tolua_function(tolua_S,"attachChain",tolua_Cocos2d_oBodyDef_attachChain00);
   tolua_function(tolua_S,"attachPolygonSensor",tolua_Cocos2d_oBodyDef_attachPolygonSensor02);
   tolua_function(tolua_S,"attachCircleSensor",tolua_Cocos2d_oBodyDef_attachCircleSensor01);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oBodyDef_new00_local);
   tolua_function(tolua_S,"toBody",tolua_Cocos2d_oBodyDef_toBody00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oBody","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oBody");
   tolua_variable(tolua_S,"world",tolua_get_oBody_world_ptr,NULL);
   tolua_variable(tolua_S,"bodyDef",tolua_get_oBody_bodyDef_ptr,NULL);
   tolua_variable(tolua_S,"velocityX",tolua_get_oBody_velocityX,tolua_set_oBody_velocityX);
   tolua_variable(tolua_S,"velocityY",tolua_get_oBody_velocityY,tolua_set_oBody_velocityY);
   tolua_variable(tolua_S,"velocity",tolua_get_oBody_velocity,tolua_set_oBody_velocity);
   tolua_variable(tolua_S,"group",tolua_get_oBody_group,tolua_set_oBody_group);
   tolua_function(tolua_S,"getSensorByTag",tolua_Cocos2d_oBody_getSensorByTag00);
   tolua_function(tolua_S,"removeSensorByTag",tolua_Cocos2d_oBody_removeSensorByTag00);
   tolua_function(tolua_S,"removeSensor",tolua_Cocos2d_oBody_removeSensor00);
   tolua_function(tolua_S,"attach",tolua_Cocos2d_oBody_attach00);
   tolua_function(tolua_S,"attachSensor",tolua_Cocos2d_oBody_attachSensor00);
   tolua_function(tolua_S,"destroy",tolua_Cocos2d_oBody_destroy00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oSensor","CCObject",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oSensor");
   tolua_constant(tolua_S,"Enter",oSensorEvent::Enter);
   tolua_constant(tolua_S,"Leave",oSensorEvent::Leave);
   tolua_variable(tolua_S,"enabled",tolua_get_oSensor_enabled,tolua_set_oSensor_enabled);
   tolua_variable(tolua_S,"tag",tolua_get_oSensor_tag,NULL);
   tolua_variable(tolua_S,"owner",tolua_get_oSensor_owner_ptr,NULL);
   tolua_variable(tolua_S,"sensed",tolua_get_oSensor_sensed,NULL);
   tolua_variable(tolua_S,"sensedBodies",tolua_get_oSensor_sensedBodies_ptr,NULL);
   tolua_function(tolua_S,"addHandler",tolua_Cocos2d_oSensor_addHandler00);
   tolua_function(tolua_S,"removeHandler",tolua_Cocos2d_oSensor_removeHandler00);
   tolua_function(tolua_S,"clearHandler",tolua_Cocos2d_oSensor_clearHandler00);
   tolua_function(tolua_S,"contains",tolua_Cocos2d_oSensor_contains00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oEase","",NULL);
  tolua_beginmodule(tolua_S,"oEase");
   tolua_constant(tolua_S,"Linear",oEase::Linear);
   tolua_constant(tolua_S,"InQuad",oEase::InQuad);
   tolua_constant(tolua_S,"OutQuad",oEase::OutQuad);
   tolua_constant(tolua_S,"InOutQuad",oEase::InOutQuad);
   tolua_constant(tolua_S,"InCubic",oEase::InCubic);
   tolua_constant(tolua_S,"OutCubic",oEase::OutCubic);
   tolua_constant(tolua_S,"InOutCubic",oEase::InOutCubic);
   tolua_constant(tolua_S,"InQuart",oEase::InQuart);
   tolua_constant(tolua_S,"OutQuart",oEase::OutQuart);
   tolua_constant(tolua_S,"InOutQuart",oEase::InOutQuart);
   tolua_constant(tolua_S,"InQuint",oEase::InQuint);
   tolua_constant(tolua_S,"OutQuint",oEase::OutQuint);
   tolua_constant(tolua_S,"InOutQuint",oEase::InOutQuint);
   tolua_constant(tolua_S,"InSine",oEase::InSine);
   tolua_constant(tolua_S,"OutSine",oEase::OutSine);
   tolua_constant(tolua_S,"InOutSine",oEase::InOutSine);
   tolua_constant(tolua_S,"InExpo",oEase::InExpo);
   tolua_constant(tolua_S,"OutExpo",oEase::OutExpo);
   tolua_constant(tolua_S,"InOutExpo",oEase::InOutExpo);
   tolua_constant(tolua_S,"InCirc",oEase::InCirc);
   tolua_constant(tolua_S,"OutCirc",oEase::OutCirc);
   tolua_constant(tolua_S,"InOutCirc",oEase::InOutCirc);
   tolua_constant(tolua_S,"InElastic",oEase::InElastic);
   tolua_constant(tolua_S,"OutElastic",oEase::OutElastic);
   tolua_constant(tolua_S,"InOutElastic",oEase::InOutElastic);
   tolua_constant(tolua_S,"InBack",oEase::InBack);
   tolua_constant(tolua_S,"OutBack",oEase::OutBack);
   tolua_constant(tolua_S,"InOutBack",oEase::InOutBack);
   tolua_constant(tolua_S,"InBounce",oEase::InBounce);
   tolua_constant(tolua_S,"OutBounce",oEase::OutBounce);
   tolua_constant(tolua_S,"InOutBounce",oEase::InOutBounce);
   tolua_function(tolua_S,"func",tolua_Cocos2d_oEase_func00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"oPos",tolua_Cocos2d_oPos00);
  tolua_function(tolua_S,"oScale",tolua_Cocos2d_oScale00);
  tolua_function(tolua_S,"oRotate",tolua_Cocos2d_oRotate00);
  tolua_function(tolua_S,"oOpacity",tolua_Cocos2d_oOpacity00);
  tolua_function(tolua_S,"oSkew",tolua_Cocos2d_oSkew00);
  tolua_function(tolua_S,"oRoll",tolua_Cocos2d_oRoll00);
  tolua_cclass(tolua_S,"oCamera","CCNode",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oCamera");
   tolua_variable(tolua_S,"boudary",tolua_get_oCamera_boudary,tolua_set_oCamera_boudary);
   tolua_variable(tolua_S,"view",tolua_get_oCamera_view,tolua_set_oCamera_view);
   tolua_variable(tolua_S,"followRatio",tolua_get_oCamera_followRatio,tolua_set_oCamera_followRatio);
   tolua_function(tolua_S,"follow",tolua_Cocos2d_oCamera_follow00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oLayer","oNode3D",NULL);
  tolua_beginmodule(tolua_S,"oLayer");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oPlatformWorld","oWorld",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oPlatformWorld");
   tolua_variable(tolua_S,"camera",tolua_get_oPlatformWorld_camera_ptr,NULL);
   tolua_variable(tolua_S,"UILayer",tolua_get_oPlatformWorld_UILayer_ptr,NULL);
   tolua_function(tolua_S,"getLayer",tolua_Cocos2d_oPlatformWorld_getLayer00);
   tolua_function(tolua_S,"removeLayer",tolua_Cocos2d_oPlatformWorld_removeLayer00);
   tolua_function(tolua_S,"removeAllLayers",tolua_Cocos2d_oPlatformWorld_removeAllLayers00);
   tolua_function(tolua_S,"setLayerRatio",tolua_Cocos2d_oPlatformWorld_setLayerRatio00);
   tolua_function(tolua_S,"getLayerRatio",tolua_Cocos2d_oPlatformWorld_getLayerRatio00);
   tolua_function(tolua_S,"setLayerOffset",tolua_Cocos2d_oPlatformWorld_setLayerOffset00);
   tolua_function(tolua_S,"getLayerOffset",tolua_Cocos2d_oPlatformWorld_getLayerOffset00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oPlatformWorld_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oSound","",NULL);
  tolua_beginmodule(tolua_S,"oSound");
   tolua_function(tolua_S,"load",tolua_Cocos2d_oSound_load00);
   tolua_function(tolua_S,"play",tolua_Cocos2d_oSound_play00);
   tolua_function(tolua_S,"stop",tolua_Cocos2d_oSound_stop01);
   tolua_variable(tolua_S,"volume",tolua_get_oSound_volume,tolua_set_oSound_volume);
   tolua_variable(tolua_S,"useCache",tolua_get_oSound_useCache,tolua_set_oSound_useCache);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oMusic","",NULL);
  tolua_beginmodule(tolua_S,"oMusic");
   tolua_function(tolua_S,"load",tolua_Cocos2d_oMusic_load00);
   tolua_function(tolua_S,"play",tolua_Cocos2d_oMusic_play00);
   tolua_function(tolua_S,"pause",tolua_Cocos2d_oMusic_pause00);
   tolua_function(tolua_S,"resume",tolua_Cocos2d_oMusic_resume00);
   tolua_function(tolua_S,"stop",tolua_Cocos2d_oMusic_stop00);
   tolua_variable(tolua_S,"volume",tolua_get_oMusic_volume,tolua_set_oMusic_volume);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"oAttackType",0);
  tolua_beginmodule(tolua_S,"oAttackType");
   tolua_constant(tolua_S,"Melee",oAttackType::Melee);
   tolua_constant(tolua_S,"Range",oAttackType::Range);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"oAttackTarget",0);
  tolua_beginmodule(tolua_S,"oAttackTarget");
   tolua_constant(tolua_S,"Single",oAttackTarget::Single);
   tolua_constant(tolua_S,"Multi",oAttackTarget::Multi);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"oRelation",0);
  tolua_beginmodule(tolua_S,"oRelation");
   tolua_constant(tolua_S,"Unkown",oRelation::Unkown);
   tolua_constant(tolua_S,"Friend",oRelation::Friend);
   tolua_constant(tolua_S,"Neutral",oRelation::Neutral);
   tolua_constant(tolua_S,"Enemy",oRelation::Enemy);
   tolua_constant(tolua_S,"Any",oRelation::Any);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oTargetAllow","",NULL);
  tolua_beginmodule(tolua_S,"oTargetAllow");
   tolua_variable(tolua_S,"terrainAllowed",tolua_get_oTargetAllow_terrainAllowed,tolua_set_oTargetAllow_terrainAllowed);
   tolua_function(tolua_S,"allow",tolua_Cocos2d_oTargetAllow_allow00);
   tolua_function(tolua_S,"isAllow",tolua_Cocos2d_oTargetAllow_isAllow00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oBulletDef","CCObject",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oBulletDef");
   tolua_constant(tolua_S,"NoneType",oBulletDef::NoneType);
   tolua_variable(tolua_S,"type",tolua_get_oBulletDef_type,tolua_set_oBulletDef_type);
   tolua_variable(tolua_S,"endEffect",tolua_get_oBulletDef_endEffect,tolua_set_oBulletDef_endEffect);
   tolua_variable(tolua_S,"lifeTime",tolua_get_oBulletDef_lifeTime,tolua_set_oBulletDef_lifeTime);
   tolua_variable(tolua_S,"damageRadius",tolua_get_oBulletDef_damageRadius,tolua_set_oBulletDef_damageRadius);
   tolua_variable(tolua_S,"highSpeedFix",tolua_get_oBulletDef_highSpeedFix,tolua_set_oBulletDef_highSpeedFix);
   tolua_variable(tolua_S,"gravityScale",tolua_get_oBulletDef_gravityScale,tolua_set_oBulletDef_gravityScale);
   tolua_variable(tolua_S,"face",tolua_get_oBulletDef_face_ptr,tolua_set_oBulletDef_face_ptr);
   tolua_variable(tolua_S,"bodyDef",tolua_get_oBulletDef_bodyDef_ptr,NULL);
   tolua_variable(tolua_S,"velocity",tolua_get_oBulletDef_velocity,NULL);
   tolua_function(tolua_S,"setAsCircle",tolua_Cocos2d_oBulletDef_setAsCircle00);
   tolua_function(tolua_S,"setVelocity",tolua_Cocos2d_oBulletDef_setVelocity00);
   tolua_function(tolua_S,"toBullet",tolua_Cocos2d_oBulletDef_toBullet00);
   tolua_variable(tolua_S,"SensorTag",tolua_get_oBulletDef_SensorTag,NULL);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oBulletDef_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oBullet","oBody",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oBullet");
   tolua_variable(tolua_S,"type",tolua_get_oBullet_type,tolua_set_oBullet_type);
   tolua_variable(tolua_S,"targetAllow",tolua_get_oBullet_targetAllow,tolua_set_oBullet_targetAllow);
   tolua_variable(tolua_S,"faceRight",tolua_get_oBullet_faceRight,NULL);
   tolua_variable(tolua_S,"owner",tolua_get_oBullet_owner_ptr,NULL);
   tolua_variable(tolua_S,"detectSensor",tolua_get_oBullet_detectSensor_ptr,NULL);
   tolua_variable(tolua_S,"bulletDef",tolua_get_oBullet_bulletDef_ptr,NULL);
   tolua_variable(tolua_S,"face",tolua_get_oBullet_face_ptr,tolua_set_oBullet_face_ptr);
   tolua_function(tolua_S,"addHandler",tolua_Cocos2d_oBullet_addHandler00);
   tolua_function(tolua_S,"removeHandler",tolua_Cocos2d_oBullet_removeHandler00);
   tolua_function(tolua_S,"clearHandler",tolua_Cocos2d_oBullet_clearHandler00);
   tolua_function(tolua_S,"destroy",tolua_Cocos2d_oBullet_destroy00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oBullet_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oUnitDef","CCObject",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oUnitDef");
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oUnitDef_new00_local);
   tolua_variable(tolua_S,"bodyDef",tolua_get_oUnitDef_bodyDef_ptr,NULL);
   tolua_variable(tolua_S,"size",tolua_get_oUnitDef_size,NULL);
   tolua_variable(tolua_S,"static",tolua_get_oUnitDef_static,NULL);
   tolua_function(tolua_S,"toUnit",tolua_Cocos2d_oUnitDef_toUnit00);
   tolua_constant(tolua_S,"GroundSensorTag",oUnitDef::GroundSensorTag);
   tolua_constant(tolua_S,"DetectSensorTag",oUnitDef::DetectSensorTag);
   tolua_constant(tolua_S,"AttackSensorTag",oUnitDef::AttackSensorTag);
   tolua_constant(tolua_S,"BulletKey",oUnitDef::BulletKey);
   tolua_constant(tolua_S,"AttackKey",oUnitDef::AttackKey);
   tolua_constant(tolua_S,"HitKey",oUnitDef::HitKey);
   tolua_variable(tolua_S,"type",tolua_get_oUnitDef_type,tolua_set_oUnitDef_type);
   tolua_variable(tolua_S,"sensity",tolua_get_oUnitDef_sensity,tolua_set_oUnitDef_sensity);
   tolua_variable(tolua_S,"move",tolua_get_oUnitDef_move,tolua_set_oUnitDef_move);
   tolua_variable(tolua_S,"jump",tolua_get_oUnitDef_jump,tolua_set_oUnitDef_jump);
   tolua_variable(tolua_S,"detectDistance",tolua_get_oUnitDef_detectDistance,tolua_set_oUnitDef_detectDistance);
   tolua_variable(tolua_S,"maxHp",tolua_get_oUnitDef_maxHp,tolua_set_oUnitDef_maxHp);
   tolua_variable(tolua_S,"attackBase",tolua_get_oUnitDef_attackBase,tolua_set_oUnitDef_attackBase);
   tolua_variable(tolua_S,"attackDelay",tolua_get_oUnitDef_attackDelay,tolua_set_oUnitDef_attackDelay);
   tolua_variable(tolua_S,"attackEffectDelay",tolua_get_oUnitDef_attackEffectDelay,tolua_set_oUnitDef_attackEffectDelay);
   tolua_variable(tolua_S,"attackRange",tolua_get_oUnitDef_attackRange,tolua_set_oUnitDef_attackRange);
   tolua_variable(tolua_S,"attackPower",tolua_get_oUnitDef_attackPower,tolua_set_oUnitDef_attackPower);
   tolua_variable(tolua_S,"attackType",tolua_get_oUnitDef_attackType,tolua_set_oUnitDef_attackType);
   tolua_variable(tolua_S,"attackTarget",tolua_get_oUnitDef_attackTarget,tolua_set_oUnitDef_attackTarget);
   tolua_variable(tolua_S,"targetAllow",tolua_get_oUnitDef_targetAllow,tolua_set_oUnitDef_targetAllow);
   tolua_variable(tolua_S,"damageType",tolua_get_oUnitDef_unsigned_damageType,tolua_set_oUnitDef_unsigned_damageType);
   tolua_variable(tolua_S,"defenceType",tolua_get_oUnitDef_unsigned_defenceType,tolua_set_oUnitDef_unsigned_defenceType);
   tolua_variable(tolua_S,"bulletType",tolua_get_oUnitDef_bulletType,tolua_set_oUnitDef_bulletType);
   tolua_variable(tolua_S,"attackEffect",tolua_get_oUnitDef_attackEffect,tolua_set_oUnitDef_attackEffect);
   tolua_variable(tolua_S,"hitEffect",tolua_get_oUnitDef_hitEffect,tolua_set_oUnitDef_hitEffect);
   tolua_variable(tolua_S,"name",tolua_get_oUnitDef_name,tolua_set_oUnitDef_name);
   tolua_variable(tolua_S,"desc",tolua_get_oUnitDef_desc,tolua_set_oUnitDef_desc);
   tolua_variable(tolua_S,"sndAttack",tolua_get_oUnitDef_sndAttack,tolua_set_oUnitDef_sndAttack);
   tolua_variable(tolua_S,"sndDeath",tolua_get_oUnitDef_sndDeath,tolua_set_oUnitDef_sndDeath);
   tolua_function(tolua_S,"setActions",tolua_Cocos2d_oUnitDef_setActions00);
   tolua_function(tolua_S,"setInstincts",tolua_Cocos2d_oUnitDef_setInstincts00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oUnit","oBody",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oUnit");
   tolua_variable(tolua_S,"sensity",tolua_get_oUnit_sensity,tolua_set_oUnit_sensity);
   tolua_variable(tolua_S,"move",tolua_get_oUnit_move,tolua_set_oUnit_move);
   tolua_variable(tolua_S,"moveSpeed",tolua_get_oUnit_moveSpeed,tolua_set_oUnit_moveSpeed);
   tolua_variable(tolua_S,"jump",tolua_get_oUnit_jump,tolua_set_oUnit_jump);
   tolua_variable(tolua_S,"maxHp",tolua_get_oUnit_maxHp,tolua_set_oUnit_maxHp);
   tolua_variable(tolua_S,"attackBase",tolua_get_oUnit_attackBase,tolua_set_oUnit_attackBase);
   tolua_variable(tolua_S,"attackBonus",tolua_get_oUnit_attackBonus,tolua_set_oUnit_attackBonus);
   tolua_variable(tolua_S,"attackFactor",tolua_get_oUnit_attackFactor,tolua_set_oUnit_attackFactor);
   tolua_variable(tolua_S,"attackSpeed",tolua_get_oUnit_attackSpeed,tolua_set_oUnit_attackSpeed);
   tolua_variable(tolua_S,"attackPower",tolua_get_oUnit_attackPower,tolua_set_oUnit_attackPower);
   tolua_variable(tolua_S,"attackType",tolua_get_oUnit_attackType,tolua_set_oUnit_attackType);
   tolua_variable(tolua_S,"attackTarget",tolua_get_oUnit_attackTarget,tolua_set_oUnit_attackTarget);
   tolua_variable(tolua_S,"targetAllow",tolua_get_oUnit_targetAllow,tolua_set_oUnit_targetAllow);
   tolua_variable(tolua_S,"damageType",tolua_get_oUnit_unsigned_damageType,tolua_set_oUnit_unsigned_damageType);
   tolua_variable(tolua_S,"defenceType",tolua_get_oUnit_unsigned_defenceType,tolua_set_oUnit_unsigned_defenceType);
   tolua_variable(tolua_S,"model",tolua_get_oUnit_model_ptr,tolua_set_oUnit_model_ptr);
   tolua_variable(tolua_S,"detectDistance",tolua_get_oUnit_detectDistance,tolua_set_oUnit_detectDistance);
   tolua_variable(tolua_S,"attackRange",tolua_get_oUnit_attackRange,tolua_set_oUnit_attackRange);
   tolua_variable(tolua_S,"faceRight",tolua_get_oUnit_faceRight,tolua_set_oUnit_faceRight);
   tolua_variable(tolua_S,"bulletDef",tolua_get_oUnit_bulletDef_ptr,tolua_set_oUnit_bulletDef_ptr);
   tolua_variable(tolua_S,"onSurface",tolua_get_oUnit_onSurface,NULL);
   tolua_variable(tolua_S,"groundSensor",tolua_get_oUnit_groundSensor_ptr,NULL);
   tolua_variable(tolua_S,"detectSensor",tolua_get_oUnit_detectSensor_ptr,NULL);
   tolua_variable(tolua_S,"attackSensor",tolua_get_oUnit_attackSensor_ptr,NULL);
   tolua_variable(tolua_S,"unitDef",tolua_get_oUnit_unitDef_ptr,NULL);
   tolua_variable(tolua_S,"currentAction",tolua_get_oUnit_currentAction_ptr,NULL);
   tolua_variable(tolua_S,"width",tolua_get_oUnit_width,NULL);
   tolua_variable(tolua_S,"height",tolua_get_oUnit_height,NULL);
   tolua_function(tolua_S,"attachAction",tolua_Cocos2d_oUnit_attachAction00);
   tolua_function(tolua_S,"removeAction",tolua_Cocos2d_oUnit_removeAction00);
   tolua_function(tolua_S,"removeAllActions",tolua_Cocos2d_oUnit_removeAllActions00);
   tolua_function(tolua_S,"getAction",tolua_Cocos2d_oUnit_getAction00);
   tolua_function(tolua_S,"doIt",tolua_Cocos2d_oUnit_doIt00);
   tolua_function(tolua_S,"attachInstinct",tolua_Cocos2d_oUnit_attachInstinct00);
   tolua_function(tolua_S,"removeInstinct",tolua_Cocos2d_oUnit_removeInstinct00);
   tolua_function(tolua_S,"removeAllInstincts",tolua_Cocos2d_oUnit_removeAllInstincts00);
   tolua_function(tolua_S,"setReflexArc",tolua_Cocos2d_oUnit_setReflexArc00);
   tolua_function(tolua_S,"set",tolua_Cocos2d_oUnit_set00);
   tolua_function(tolua_S,"get",tolua_Cocos2d_oUnit_get00);
   tolua_function(tolua_S,"remove",tolua_Cocos2d_oUnit_remove00);
   tolua_function(tolua_S,"clear",tolua_Cocos2d_oUnit_clear00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oUnit_new00_local);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oAction","",NULL);
  tolua_beginmodule(tolua_S,"oAction");
   tolua_constant(tolua_S,"Start",oAction::Start);
   tolua_constant(tolua_S,"End",oAction::End);
   tolua_variable(tolua_S,"reaction",tolua_get_oAction_reaction,tolua_set_oAction_reaction);
   tolua_variable(tolua_S,"id",tolua_get_oAction_id,NULL);
   tolua_variable(tolua_S,"priority",tolua_get_oAction_priority,NULL);
   tolua_variable(tolua_S,"doing",tolua_get_oAction_doing,NULL);
   tolua_variable(tolua_S,"owner",tolua_get_oAction_owner_ptr,NULL);
   tolua_function(tolua_S,"stop",tolua_Cocos2d_oAction_stop00);
   tolua_function(tolua_S,"addHandler",tolua_Cocos2d_oAction_addHandler00);
   tolua_function(tolua_S,"removeHandler",tolua_Cocos2d_oAction_removeHandler00);
   tolua_function(tolua_S,"clearHandler",tolua_Cocos2d_oAction_clearHandler00);
   tolua_function(tolua_S,"add",tolua_Cocos2d_oAction_add00);
   tolua_function(tolua_S,"clear",tolua_Cocos2d_oAction_clear00);
   tolua_variable(tolua_S,"UserID",tolua_get_oAction_UserID,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oAI","",NULL);
  tolua_beginmodule(tolua_S,"oAI");
   tolua_variable(tolua_S,"self",tolua_get_oAI_self_ptr,NULL);
   tolua_variable(tolua_S,"oldInstinctValue",tolua_get_oAI_oldInstinctValue,NULL);
   tolua_variable(tolua_S,"newInstinctValue",tolua_get_oAI_newInstinctValue,NULL);
   tolua_function(tolua_S,"getUnitsByRelation",tolua_Cocos2d_oAI_getUnitsByRelation00);
   tolua_function(tolua_S,"getDetectedUnits",tolua_Cocos2d_oAI_getDetectedUnits00);
   tolua_function(tolua_S,"getNearestUnit",tolua_Cocos2d_oAI_getNearestUnit00);
   tolua_function(tolua_S,"getNearestUnitDistance",tolua_Cocos2d_oAI_getNearestUnitDistance00);
   tolua_function(tolua_S,"add",tolua_Cocos2d_oAI_add00);
   tolua_function(tolua_S,"clear",tolua_Cocos2d_oAI_clear00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oAILeaf","CCObject",tolua_collect_ccobject);
  tolua_beginmodule(tolua_S,"oAILeaf");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"oInstinct","",NULL);
  tolua_beginmodule(tolua_S,"oInstinct");
   tolua_function(tolua_S,"add",tolua_Cocos2d_oInstinct_add00);
   tolua_function(tolua_S,"clear",tolua_Cocos2d_oInstinct_clear00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"oSel",tolua_Cocos2d_oSel00);
  tolua_function(tolua_S,"oSeq",tolua_Cocos2d_oSeq00);
  tolua_function(tolua_S,"oParSel",tolua_Cocos2d_oParSel00);
  tolua_function(tolua_S,"oParSeq",tolua_Cocos2d_oParSeq00);
  tolua_function(tolua_S,"oCon",tolua_Cocos2d_oCon00);
  tolua_function(tolua_S,"oAct",tolua_Cocos2d_oAct00);
  tolua_cclass(tolua_S,"oData","",NULL);
  tolua_beginmodule(tolua_S,"oData");
   tolua_variable(tolua_S,"GroupHide",tolua_get_oData_GroupHide,NULL);
   tolua_variable(tolua_S,"GroupDetectPlayer",tolua_get_oData_GroupDetectPlayer,NULL);
   tolua_variable(tolua_S,"GroupTerrain",tolua_get_oData_GroupTerrain,NULL);
   tolua_variable(tolua_S,"GroupDetect",tolua_get_oData_GroupDetect,NULL);
   tolua_function(tolua_S,"setRelation",tolua_Cocos2d_oData_setRelation00);
   tolua_function(tolua_S,"getRelation",tolua_Cocos2d_oData_getRelation01);
   tolua_function(tolua_S,"setDamageFactor",tolua_Cocos2d_oData_setDamageFactor00);
   tolua_function(tolua_S,"getDamageFactor",tolua_Cocos2d_oData_getDamageFactor00);
   tolua_function(tolua_S,"isPlayerUnit",tolua_Cocos2d_oData_isPlayerUnit00);
   tolua_function(tolua_S,"isTerrain",tolua_Cocos2d_oData_isTerrain00);
   tolua_call(tolua_S,MT_CALL,tolua_Cocos2d_oData_new00_local);
  tolua_endmodule(tolua_S);

  { /* begin embedded lua code */
   int top = lua_gettop(tolua_S);
   static const unsigned char B[] = {
    10, 99, 99,108,111,103, 32, 61, 32,102,117,110, 99,116,105,
    111,110, 40, 46, 46, 46, 41, 10, 67, 67, 76,117, 97, 76,111,
    103, 40,115,116,114,105,110,103, 46,102,111,114,109, 97,116,
     40, 46, 46, 46, 41, 41, 10,101,110,100, 10, 99, 99,109,115,
    103, 32, 61, 32,102,117,110, 99,116,105,111,110, 40,116,105,
    116,108,101, 44, 32, 46, 46, 46, 41, 10, 67, 67, 77,101,115,
    115, 97,103,101, 66,111,120, 40,115,116,114,105,110,103, 46,
    102,111,114,109, 97,116, 40, 46, 46, 46, 41, 44, 32,116,105,
    116,108,101, 41, 10,101,110,100, 10,111, 69,118,101,110,116,
     46, 97,114,103,115, 32, 61, 32,123,125, 10,111, 69,118,101,
    110,116, 46,115,101,110,100, 32, 61, 32, 40,102,117,110, 99,
    116,105,111,110, 40, 41, 10,108,111, 99, 97,108, 32,115,101,
    110,100, 32, 61, 32,111, 69,118,101,110,116, 46,115,101,110,
    100, 10,114,101,116,117,114,110, 32,102,117,110, 99,116,105,
    111,110, 40,115,101,108,102, 44, 32,110, 97,109,101, 44, 32,
     97,114,103,115, 41, 10,111, 69,118,101,110,116, 46, 97,114,
    103,115, 91,110, 97,109,101, 93, 32, 61, 32, 97,114,103,115,
     10,115,101,110,100, 40,115,101,108,102, 44, 32,110, 97,109,
    101, 41, 10,101,110,100, 10,101,110,100, 41, 40, 41, 10,111,
     76,105,115,116,101,110,101,114, 32, 61, 32, 40,102,117,110,
     99,116,105,111,110, 40, 41, 10,108,111, 99, 97,108, 32,108,
    105,115,116,101,110,101,114, 32, 61, 32,111, 76,105,115,116,
    101,110,101,114, 10,114,101,116,117,114,110, 32,102,117,110,
     99,116,105,111,110, 40,110, 97,109,101, 44, 32,104, 97,110,
    100,108,101,114, 41, 10,114,101,116,117,114,110, 32,108,105,
    115,116,101,110,101,114, 40,110, 97,109,101, 44, 10,102,117,
    110, 99,116,105,111,110, 40,101,118,101,110,116, 41, 10,104,
     97,110,100,108,101,114, 40,111, 69,118,101,110,116, 46, 97,
    114,103,115, 91,110, 97,109,101, 93, 44, 32,101,118,101,110,
    116, 41, 10,101,110,100, 41, 10,101,110,100, 10,101,110,100,
     41, 40, 41, 10, 67, 67, 86,105,101,119, 32, 61, 32, 67, 67,
     86,105,101,119, 40, 41, 10, 67, 67, 70,105,108,101, 85,116,
    105,108,115, 32, 61, 32, 67, 67, 70,105,108,101, 85,116,105,
    108,115, 40, 41, 10, 67, 67, 65,112,112,108,105, 99, 97,116,
    105,111,110, 32, 61, 32, 67, 67, 65,112,112,108,105, 99, 97,
    116,105,111,110, 40, 41, 10, 67, 67, 68,105,114,101, 99,116,
    111,114, 32, 61, 32, 67, 67, 68,105,114,101, 99,116,111,114,
     40, 41, 10, 67, 67, 85,115,101,114, 68,101,102, 97,117,108,
    116, 32, 61, 32, 67, 67, 85,115,101,114, 68,101,102, 97,117,
    108,116, 40, 41, 10, 67, 67, 84,101,120,116,117,114,101, 67,
     97, 99,104,101, 32, 61, 32, 67, 67, 84,101,120,116,117,114,
    101, 67, 97, 99,104,101, 40, 41, 10,111, 67,111,110,116,101,
    110,116, 32, 61, 32,111, 67,111,110,116,101,110,116, 40, 41,
     10,111, 68, 97,116, 97, 32, 61, 32,111, 68, 97,116, 97, 40,
     41, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,32
   };
   tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua: embedded Lua code 1");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */

 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Cocos2d (lua_State* tolua_S) {
 return tolua_Cocos2d_open(tolua_S);
};
#endif

