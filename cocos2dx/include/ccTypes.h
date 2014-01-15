/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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

#ifndef __CCTYPES_H__
#define __CCTYPES_H__

#include "cocoa/CCGeometry.h"
#include "CCGL.h"

NS_CC_BEGIN

/** RGB color composed of bytes 3 bytes
@since v0.8
 */
struct ccColor3B
{
	ccColor3B():r(0), g(0), b(0){}
	ccColor3B(unsigned int value): r((value&0x00FF0000)>>16), g((value&0x0000FF00)>>8), b(value&0x000000FF){}
	ccColor3B(GLubyte r, GLubyte g, GLubyte b):r(r), g(g), b(b){}
    GLubyte r;
    GLubyte g;
    GLubyte b;
};

//! helper macro that creates an ccColor3B type
inline ccColor3B ccc3(const GLubyte r, const GLubyte g, const GLubyte b)
{
	return ccColor3B(r, g, b);
}
//ccColor3B predefined colors
//! White color (255,255,255)
static const ccColor3B ccWHITE(0xffffff);
//! Yellow color (255,255,0)
static const ccColor3B ccYELLOW(0xffff00);
//! Blue color (0,0,255)
static const ccColor3B ccBLUE(0x0000ff);
//! Green Color (0,255,0)
static const ccColor3B ccGREEN(0x00ff00);
//! Red Color (255,0,0,)
static const ccColor3B ccRED(0xff0000);
//! Magenta Color (255,0,255)
static const ccColor3B ccMAGENTA(0xff00ff);
//! Black Color (0,0,0)
static const ccColor3B ccBLACK(0);
//! Orange Color (255,127,0)
static const ccColor3B ccORANGE(0xff8800);
//! Gray Color (166,166,166)
static const ccColor3B ccGRAY(0xaaaaaa);

/** RGBA color composed of 4 bytes
@since v0.8
*/
struct ccColor4B
{
	ccColor4B(unsigned int value) :a(value >> 24), r((value & 0x00FF0000) >> 16), g((value & 0x0000FF00) >> 8), b(value & 0x000000FF){}
	ccColor4B():r(0), g(0), b(0), a(0){}
	ccColor4B(GLubyte r, GLubyte g, GLubyte b, GLubyte a) :r(r), g(g), b(b), a(a){}
	ccColor4B(ccColor3B c, GLubyte a = 255) :r(c.r), g(c.g), b(c.b), a(a){}
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};
//! helper macro that creates an ccColor4B type
inline ccColor4B ccc4(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte a)
{
	return ccColor4B(r, g, b, a);
}

/** RGBA color composed of 4 floats
@since v0.8
*/
struct ccColor4F
{
	ccColor4F() :r(0), g(0), b(0), a(0){}
	ccColor4F(GLfloat r, GLfloat g, GLfloat b, GLfloat a) :r(r), g(g), b(b), a(a){}
	ccColor4F(ccColor3B c, GLfloat a = 1.f) :r(c.r / 255.f), g(c.g / 255.f), b(c.b / 255.f), a(a){}
	ccColor4F(ccColor4B c) :r(c.r / 255.f), g(c.g / 255.f), b(c.b / 255.f), a(c.a / 255.f){}
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
};

/** Returns a ccColor4F from a ccColor3B. Alpha will be 1.
 @since v0.99.1
 */
inline ccColor4F ccc4FFromccc3B(ccColor3B c)
{
	return ccColor4F(c.r / 255.f, c.g / 255.f, c.b / 255.f, 1.f);
}

//! helper that creates a ccColor4f type
inline ccColor4F ccc4f(const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a)
{
	return ccColor4F(r, g, b, a);
}

/** Returns a ccColor4F from a ccColor4B.
 @since v0.99.1
 */
inline ccColor4F ccc4FFromccc4B(ccColor4B c)
{
	return ccColor4F(c.r/255.f, c.g/255.f, c.b/255.f, c.a/255.f);
}

inline ccColor4B ccc4BFromccc4F(ccColor4F c)
{
	return ccColor4B((GLubyte)(c.r*255), (GLubyte)(c.g*255), (GLubyte)(c.b*255), (GLubyte)(c.a*255));
}

/** returns YES if both ccColor4F are equal. Otherwise it returns NO.
 @since v0.99.1
 */
inline bool ccc4FEqual(ccColor4F a, ccColor4F b)
{
	return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

/** A vertex composed of 2 floats: x, y
 @since v0.8
 */
typedef struct _ccVertex2F
{
    GLfloat x;
    GLfloat y;
} ccVertex2F;

static inline ccVertex2F vertex2(const float x, const float y)
{
    ccVertex2F c = {x, y};
    return c;
}


/** A vertex composed of 2 floats: x, y
 @since v0.8
 */
typedef struct _ccVertex3F
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
} ccVertex3F;

static inline ccVertex3F vertex3(const float x, const float y, const float z)
{
    ccVertex3F c = {x, y, z};
    return c;
}
        
/** A texcoord composed of 2 floats: u, y
 @since v0.8
 */
typedef struct _ccTex2F {
     GLfloat u;
     GLfloat v;
} ccTex2F;

static inline ccTex2F tex2(const float u, const float v)
{
    ccTex2F t = {u , v};
    return t;
}

 
//! Point Sprite component
typedef struct _ccPointSprite
{
    ccVertex2F    pos;        // 8 bytes
    ccColor4B    color;        // 4 bytes
    GLfloat        size;        // 4 bytes
} ccPointSprite;

//!    A 2D Quad. 4 * 2 floats
typedef struct _ccQuad2 {
    ccVertex2F        tl;
    ccVertex2F        tr;
    ccVertex2F        bl;
    ccVertex2F        br;
} ccQuad2;


//!    A 3D Quad. 4 * 3 floats
typedef struct _ccQuad3 {
    ccVertex3F        bl;
    ccVertex3F        br;
    ccVertex3F        tl;
    ccVertex3F        tr;
} ccQuad3;

//! a Point with a vertex point, a tex coord point and a color 4B
typedef struct _ccV2F_C4B_T2F
{
    //! vertices (2F)
    ccVertex2F        vertices;
    //! colors (4B)
    ccColor4B        colors;
    //! tex coords (2F)
    ccTex2F            texCoords;
} ccV2F_C4B_T2F;

//! a Point with a vertex point, a tex coord point and a color 4F
typedef struct _ccV2F_C4F_T2F
{
    //! vertices (2F)
    ccVertex2F        vertices;
    //! colors (4F)
    ccColor4F        colors;
    //! tex coords (2F)
    ccTex2F            texCoords;
} ccV2F_C4F_T2F;

//! a Point with a vertex point, a tex coord point and a color 4B
typedef struct _ccV3F_C4B_T2F
{
    //! vertices (3F)
    ccVertex3F        vertices;            // 12 bytes
//    char __padding__[4];

    //! colors (4B)
    ccColor4B        colors;                // 4 bytes
//    char __padding2__[4];

    // tex coords (2F)
    ccTex2F            texCoords;            // 8 bytes
} ccV3F_C4B_T2F;

//! A Triangle of ccV2F_C4B_T2F
typedef struct _ccV2F_C4B_T2F_Triangle
{
	//! Point A
	ccV2F_C4B_T2F a;
	//! Point B
	ccV2F_C4B_T2F b;
	//! Point B
	ccV2F_C4B_T2F c;
} ccV2F_C4B_T2F_Triangle;

//! A Quad of ccV2F_C4B_T2F
typedef struct _ccV2F_C4B_T2F_Quad
{
    //! bottom left
    ccV2F_C4B_T2F    bl;
    //! bottom right
    ccV2F_C4B_T2F    br;
    //! top left
    ccV2F_C4B_T2F    tl;
    //! top right
    ccV2F_C4B_T2F    tr;
} ccV2F_C4B_T2F_Quad;

//! 4 ccVertex3FTex2FColor4B
typedef struct _ccV3F_C4B_T2F_Quad
{
    //! top left
    ccV3F_C4B_T2F    tl;
    //! bottom left
    ccV3F_C4B_T2F    bl;
    //! top right
    ccV3F_C4B_T2F    tr;
    //! bottom right
    ccV3F_C4B_T2F    br;
} ccV3F_C4B_T2F_Quad;

//! 4 ccVertex2FTex2FColor4F Quad
typedef struct _ccV2F_C4F_T2F_Quad
{
    //! bottom left
    ccV2F_C4F_T2F    bl;
    //! bottom right
    ccV2F_C4F_T2F    br;
    //! top left
    ccV2F_C4F_T2F    tl;
    //! top right
    ccV2F_C4F_T2F    tr;
} ccV2F_C4F_T2F_Quad;

//! Blend Function used for textures
typedef struct _ccBlendFunc
{
    //! source blend function
    GLenum src;
    //! destination blend function
    GLenum dst;
} ccBlendFunc;

static const ccBlendFunc kCCBlendFuncDisable = {GL_ONE, GL_ZERO};

// XXX: If any of these enums are edited and/or reordered, update CCTexture2D.m
//! Vertical text alignment type
typedef enum
{
    kCCVerticalTextAlignmentTop,
    kCCVerticalTextAlignmentCenter,
    kCCVerticalTextAlignmentBottom,
} CCVerticalTextAlignment;

// XXX: If any of these enums are edited and/or reordered, update CCTexture2D.m
//! Horizontal text alignment type
typedef enum
{
    kCCTextAlignmentLeft,
    kCCTextAlignmentCenter,
    kCCTextAlignmentRight,
} CCTextAlignment;

// types for animation in particle systems

// texture coordinates for a quad
typedef struct _ccT2F_Quad
{
    //! bottom left
    ccTex2F    bl;
    //! bottom right
    ccTex2F    br;
    //! top left
    ccTex2F    tl;
    //! top right
    ccTex2F    tr;
} ccT2F_Quad;

// struct that holds the size in pixels, texture coordinates and delays for animated CCParticleSystemQuad
typedef struct
{
    ccT2F_Quad texCoords;
    float delay;
    CCSize size; 
} ccAnimationFrameData;

NS_CC_END

#endif //__CCTYPES_H__
