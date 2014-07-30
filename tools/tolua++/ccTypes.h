typedef unsigned char GLubyte;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char	GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef short GLshort;
typedef unsigned int GLenum;

class ccColor3B @ ccColor3
{
	ccColor3B();
	ccColor3B(unsigned int value);
	ccColor3B(GLubyte r, GLubyte g, GLubyte b);
	~ccColor3B();
    GLubyte r;
    GLubyte g;
    GLubyte b;
};

class ccColor4B @ ccColor4
{
	ccColor4B();
	ccColor4B(unsigned int value);
	ccColor4B(ccColor3B c, GLubyte a = 255);
	ccColor4B(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	~ccColor4B();
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};

class ccBlendFunc
{
	#define GL_SRC_ALPHA @ Src
	#define GL_ONE_MINUS_SRC_ALPHA @ OneMinSrc
	#define GL_DST_ALPHA @ Dst
	#define GL_ONE_MINUS_DST_ALPHA @ OneMinDst
	#define GL_ONE @ One
	#define GL_ZERO @ Zero
	ccBlendFunc();
	~ccBlendFunc();
	static tolua_outside ccBlendFunc* ccBlendFuncNew @ create(GLenum src, GLenum dst);
	GLenum src;
	GLenum dst;
};

enum CCTextAlignment {};
enum CCVerticalTextAlignment {};
module CCTextAlign
{
	#define kCCTextAlignmentLeft @ HLeft
	#define kCCTextAlignmentCenter @ HCenter
	#define kCCTextAlignmentRight @ HRight
	#define kCCVerticalTextAlignmentTop @ VTop
	#define kCCVerticalTextAlignmentCenter @ VCenter
    #define kCCVerticalTextAlignmentBottom @ VBottom
}
