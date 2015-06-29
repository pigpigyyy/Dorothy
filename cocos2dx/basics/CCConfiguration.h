/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2010      Ricardo Quesada

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

#ifndef __CCCONFIGURATION_H__
#define __CCCONFIGURATION_H__

#include "cocoa/CCObject.h"
#include "CCGL.h"
#include <string>

NS_CC_BEGIN

/**
 * @addtogroup global
 * @{
 */
/**
 @brief CCConfiguration contains some openGL variables
 @since v0.99.0
 */
class CC_DLL CCConfiguration : public CCObject
{
public:
    /** returns a shared instance of CCConfiguration */
    static CCConfiguration *sharedConfiguration();
    /** purge the shared instance of CCConfiguration */
    static void purgeConfiguration();
public:    
    
    /** OpenGL Max texture size. */
    inline int getMaxTextureSize()
    {
        return m_nMaxTextureSize;
    }
    
    /** OpenGL Max Modelview Stack Depth. */
    inline int getMaxModelviewStackDepth()
    {
        return m_nMaxModelviewStackDepth;
    }

    /** returns the maximum texture units
     @since v2.0.0
     */
    inline int getMaxTextureUnits()
    {
        return m_nMaxTextureUnits;
    }

    /** Whether or not the GPU supports NPOT (Non Power Of Two) textures.
     OpenGL ES 2.0 already supports NPOT (iOS).
     
     @since v0.99.2
     */
    inline bool supportsNPOT()
    {
        return m_bSupportsNPOT;
    }

    /** Whether or not PVR Texture Compressed is supported */
    inline bool supportsPVRTC()
    {
        return m_bSupportsPVRTC;
    }

    /** Whether or not BGRA8888 textures are supported.
     @since v0.99.2
     */
    inline bool supportsBGRA8888()
    {
        return m_bSupportsBGRA8888;
    }

    /** Whether or not glDiscardFramebufferEXT is supported
     @since v0.99.2
     */
    inline bool supportsDiscardFramebuffer()
    {
        return m_bSupportsDiscardFramebuffer;
    }

    /** Whether or not shareable VAOs are supported.
     @since v2.0.0
     */
    inline bool supportsShareableVAO()
    {
        return m_bSupportsShareableVAO;
    }

    /** returns whether or not an OpenGL is supported */
    bool checkForGLExtension(const std::string &searchName);

    bool init();

private:
    CCConfiguration();
    static CCConfiguration *s_gSharedConfiguration;
    
protected:
    GLint           m_nMaxTextureSize;
    GLint           m_nMaxModelviewStackDepth;
    bool            m_bSupportsPVRTC;
    bool            m_bSupportsNPOT;
    bool            m_bSupportsBGRA8888;
    bool            m_bSupportsDiscardFramebuffer;
    bool            m_bSupportsShareableVAO;
    GLint           m_nMaxSamplesAllowed;
    GLint           m_nMaxTextureUnits;
    char *          m_pGlExtensions;
};

// end of global group
/// @}

NS_CC_END

#endif // __CCCONFIGURATION_H__
