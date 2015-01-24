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
    GLubyte r;
    GLubyte g;
    GLubyte b;
};
//! helper macro that creates an ccColor3B type
inline ccColor3B ccc3(const GLubyte r, const GLubyte g, const GLubyte b)
{
	return ccColor3B{r, g, b};
}
inline ccColor3B ccc3(unsigned int value)
{
	return ccColor3B
	{
		(GLubyte)((value&0x00FF0000) >> 16),
		(GLubyte)((value&0x0000FF00) >> 8),
		(GLubyte)(value&0x000000FF)
	};
}

//ccColor3B predefined colors
//! White color (255,255,255)
static const ccColor3B ccWHITE{255,255,255};
//! Yellow color (255,255,0)
static const ccColor3B ccYELLOW{255,255,0};
//! Blue color (0,0,255)
static const ccColor3B ccBLUE{0,0,255};
//! Green Color (0,255,0)
static const ccColor3B ccGREEN{0,255,0};
//! Red Color (255,0,0)
static const ccColor3B ccRED{255,0,0};
//! Magenta Color (255,0,255)
static const ccColor3B ccMAGENTA{255,0,255};
//! Black Color (0,0,0)
static const ccColor3B ccBLACK{0};
//! Orange Color (255,127,0)
static const ccColor3B ccORANGE{255,127,0};
//! Gray Color (166,166,166)
static const ccColor3B ccGRAY{166,166,166};

/** RGBA color composed of 4 bytes
@since v0.8
*/
struct ccColor4B
{
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};
//! helper macro that creates an ccColor4B type
inline ccColor4B ccc4(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte a)
{
	return ccColor4B{r, g, b, a};
}
inline ccColor4B ccc4(unsigned int value)
{
	return ccColor4B
	{
		(GLubyte)((value & 0x00FF0000) >> 16), // r
		(GLubyte)((value & 0x0000FF00) >> 8), // g
		(GLubyte)(value & 0x000000FF), // b
		(GLubyte)(value >> 24) // a
	};
}
inline ccColor4B ccc4(const ccColor3B& c, GLubyte a = 255)
{
	return ccColor4B{c.r, c.g, c.b, a};
}

/** RGBA color composed of 4 floats
@since v0.8
*/
struct ccColor4F
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
};

/** Returns a ccColor4F from a ccColor3B. Alpha will be 1.
 @since v0.99.1
 */
inline ccColor4F ccc4f(ccColor3B c, GLfloat a = 1.f)
{
	return ccColor4F{c.r / 255.f, c.g / 255.f, c.b / 255.f, a};
}
inline ccColor4F ccc4f(const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a)
{
	return ccColor4F{r, g, b, a};
}
inline ccColor4F ccc4f(const ccColor4B& c)
{
	return ccColor4F{c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a / 255.f};
}

inline ccColor4B ccc4(const ccColor4F& c)
{
	return ccColor4B
	{
		(GLubyte)(c.r*255),
		(GLubyte)(c.g*255),
		(GLubyte)(c.b*255),
		(GLubyte)(c.a*255)
	};
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
struct ccVertex2F
{
    GLfloat x;
    GLfloat y;
};

inline ccVertex2F vertex2(const float x, const float y)
{
	return ccVertex2F{x, y};
}

/** A vertex composed of 2 floats: x, y
 @since v0.8
 */
struct ccVertex3F
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

inline ccVertex3F vertex3(const float x, const float y, const float z)
{
    return ccVertex3F{x, y, z};
}
        
/** A texcoord composed of 2 floats: u, y
 @since v0.8
 */
struct ccTex2F
{
     GLfloat u;
     GLfloat v;
};

inline ccTex2F tex2(const float u, const float v)
{
    return ccTex2F{u, v};
}

 
//! Point Sprite component
struct ccPointSprite
{
    ccVertex2F pos;        // 8 bytes
    ccColor4B color;        // 4 bytes
    GLfloat size;        // 4 bytes
};

//!    A 2D Quad. 4 * 2 floats
struct ccQuad2
{
    ccVertex2F tl;
    ccVertex2F tr;
    ccVertex2F bl;
    ccVertex2F br;
};


//!    A 3D Quad. 4 * 3 floats
struct ccQuad3
{
	ccVertex3F bl;
	ccVertex3F br;
	ccVertex3F tl;
	ccVertex3F tr;
};

//! a Point with a vertex point, a tex coord point and a color 4B
struct ccV2F_C4B_T2F
{
    //! vertices (2F)
	ccVertex2F vertices;
    //! colors (4B)
	ccColor4B colors;
    //! tex coords (2F)
	ccTex2F texCoords;
};

//! a Point with a vertex point, a tex coord point and a color 4F
struct ccV2F_C4F_T2F
{
    //! vertices (2F)
	ccVertex2F vertices;
    //! colors (4F)
	ccColor4F colors;
    //! tex coords (2F)
	ccTex2F texCoords;
};

struct ccV2F_C4F
{
	//! vertices (2F)
	ccVertex2F vertices;
	//! colors (4F)
	ccColor4F colors;
};

//! a Point with a vertex point, a tex coord point and a color 4B
struct ccV3F_C4B_T2F
{
    //! vertices (3F)
	ccVertex3F vertices;            // 12 bytes
//    char __padding__[4];
    //! colors (4B)
	ccColor4B colors;                // 4 bytes
//    char __padding2__[4];
    // tex coords (2F)
	ccTex2F texCoords;            // 8 bytes
};

//! A Triangle of ccV2F_C4B_T2F
struct ccV2F_C4B_T2F_Triangle
{
	//! Point A
	ccV2F_C4B_T2F a;
	//! Point B
	ccV2F_C4B_T2F b;
	//! Point B
	ccV2F_C4B_T2F c;
};

struct ccV2F_C4F_T2F_Triangle
{
	//! Point A
	ccV2F_C4F_T2F a;
	//! Point B
	ccV2F_C4F_T2F b;
	//! Point B
	ccV2F_C4F_T2F c;
};

struct ccV2F_C4F_Triangle
{
	//! Point A
	ccV2F_C4F a;
	//! Point B
	ccV2F_C4F b;
	//! Point B
	ccV2F_C4F c;
};

//! A Quad of ccV2F_C4B_T2F
struct ccV2F_C4B_T2F_Quad
{
    //! bottom left
	ccV2F_C4B_T2F bl;
    //! bottom right
	ccV2F_C4B_T2F br;
    //! top left
	ccV2F_C4B_T2F tl;
    //! top right
	ccV2F_C4B_T2F tr;
};

//! 4 ccVertex3FTex2FColor4B
struct ccV3F_C4B_T2F_Quad
{
    //! top left
	ccV3F_C4B_T2F tl;
    //! bottom left
	ccV3F_C4B_T2F bl;
    //! top right
	ccV3F_C4B_T2F tr;
    //! bottom right
	ccV3F_C4B_T2F br;
};

//! 4 ccVertex2FTex2FColor4F Quad
struct ccV2F_C4F_T2F_Quad
{
    //! bottom left
	ccV2F_C4F_T2F bl;
    //! bottom right
	ccV2F_C4F_T2F br;
    //! top left
	ccV2F_C4F_T2F tl;
    //! top right
	ccV2F_C4F_T2F tr;
};

//! Blend Function used for textures
struct ccBlendFunc// : public CCBase
{
	ccBlendFunc(GLenum src = GL_ONE, GLenum dst = GL_ZERO):src(src),dst(dst){}
    //! source blend function
    GLenum src;
    //! destination blend function
    GLenum dst;
	//CC_LUA_TYPE(ccBlendFunc)
};

static const ccBlendFunc kCCBlendFuncDisable{GL_ONE, GL_ZERO};

// XXX: If any of these enums are edited and/or reordered, update CCTexture2D.m
//! Vertical text alignment type
enum CCVerticalTextAlignment
{
    kCCVerticalTextAlignmentTop,
    kCCVerticalTextAlignmentCenter,
    kCCVerticalTextAlignmentBottom,
};

// XXX: If any of these enums are edited and/or reordered, update CCTexture2D.m
//! Horizontal text alignment type
enum CCTextAlignment
{
    kCCTextAlignmentLeft,
    kCCTextAlignmentCenter,
    kCCTextAlignmentRight,
};

// types for animation in particle systems

// texture coordinates for a quad
struct ccT2F_Quad
{
    //! bottom left
	ccTex2F bl;
    //! bottom right
	ccTex2F br;
    //! top left
	ccTex2F tl;
    //! top right
	ccTex2F tr;
};

NS_CC_END

#endif //__CCTYPES_H__
