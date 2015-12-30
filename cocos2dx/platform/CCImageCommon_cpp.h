/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#ifndef __CC_PLATFORM_IMAGE_CPP__
#error "CCFileUtilsCommon_cpp.h can only be included for CCFileUtils.cpp in platform/win32(android,...)"
#endif /* __CC_PLATFORM_IMAGE_CPP__ */

#include "CCImage.h"
#include "CCCommon.h"
#include "CCStdC.h"
#include "CCFileUtils.h"
#include "textures/CCTexture2D.h"
#include <string>
#include <ctype.h>
#include "support/image_support/stb_image.h"
#include "support/image_support/stb_image_write.h"

NS_CC_BEGIN

// premultiply alpha, or the effect will wrong when want to use other pixel format in CCTexture2D,
// such as RGB888, RGB5A1
#define CC_RGB_PREMULTIPLY_ALPHA(vr, vg, vb, va) \
    (unsigned)(((unsigned)((unsigned char)(vr) * ((unsigned char)(va) + 1)) >> 8) | \
    ((unsigned)((unsigned char)(vg) * ((unsigned char)(va) + 1) >> 8) << 8) | \
    ((unsigned)((unsigned char)(vb) * ((unsigned char)(va) + 1) >> 8) << 16) | \
    ((unsigned)(unsigned char)(va) << 24))

//////////////////////////////////////////////////////////////////////////
// Implement CCImage
//////////////////////////////////////////////////////////////////////////

bool CCImage::isPngAlphaPremultiplied = true;

CCImage::CCImage()
: m_nWidth(0)
, m_nHeight(0)
, m_nBitsPerComponent(0)
, m_pData(0)
, m_bHasAlpha(false)
, m_bPreMulti(false)
, _img_free_func(nullptr)
{

}

CCImage::~CCImage()
{
    if (_img_free_func)
        _img_free_func(m_pData);
    else
        CC_SAFE_DELETE_ARRAY(m_pData);
}

bool CCImage::initWithImageFile(const char * strPath, EImageFormat eImgFmt/* = eFmtPng*/)
{
    bool bRet = false;
    unsigned long nSize = 0;
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(strPath);
    unsigned char* pBuffer = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "rb", &nSize);
    if (pBuffer != NULL && nSize > 0)
    {
        bRet = initWithImageData(pBuffer, nSize, eImgFmt);
    }
    CC_SAFE_DELETE_ARRAY(pBuffer);
    return bRet;
}

bool CCImage::initWithImageFileThreadSafe(const char *fullpath, EImageFormat imageType)
{
    bool bRet = false;
    unsigned long nSize = 0;
    unsigned char *pBuffer = CCFileUtils::sharedFileUtils()->getFileData(fullpath, "rb", &nSize);
    if (pBuffer != NULL && nSize > 0)
    {
        bRet = initWithImageData(pBuffer, nSize, imageType);
    }
    CC_SAFE_DELETE_ARRAY(pBuffer);
    return bRet;
}

bool CCImage::initWithImageData(void* pData, 
                                int nDataLen, 
                                EImageFormat eFmt/* = eSrcFmtPng*/, 
                                int nWidth/* = 0*/,
                                int nHeight/* = 0*/,
                                int nBitsPerComponent/* = 8*/)
{
    m_bHasAlpha = true;

    if (eFmt != kFmtRawData)
    {
        int w, h, components;

        // always 4 components. May be very slow for some formats.
        m_pData = stbi_load_from_memory((stbi_uc*)pData, nDataLen, &w, &h, (int*)&components, 4);
        _img_free_func = stbi_image_free;

        m_nWidth = w;
        m_nHeight = h;
        return !!m_pData;
    }
    else
    {
        bool bRet = false;
        do
        {
            CC_BREAK_IF(0 == nWidth || 0 == nHeight);

            m_nBitsPerComponent = nBitsPerComponent;
            m_nHeight = (short)nHeight;
            m_nWidth = (short)nWidth;
            m_bHasAlpha = true;
            m_bPreMulti = false;

            // only RGBA8888 supported
            int nBytesPerComponent = 4;
            int nSize = nHeight * nWidth * nBytesPerComponent;
            m_pData = new unsigned char[nSize];
            CC_BREAK_IF(!m_pData);
            memcpy(m_pData, pData, nSize);

            bRet = true;
        } while (0);
        return bRet;
    }
}

static std::string getExt(const std::string& filename)
{
	int index = filename.find_last_of('.');
	if (index != -1)
	{
		std::string ext = filename.substr(index + 1);
		for (unsigned int i = 0; i < ext.length(); ++i)
		{
			ext[i] = tolower(ext[i]);
		}
		return ext;
	}
	else return std::string();
}

bool CCImage::saveToFile(const char* pszFilePath)
{
	int bRet = 0;
	std::string strFilePath(pszFilePath);
	if (getExt(strFilePath) == "png")
	{
		bRet = stbi_write_png(strFilePath.c_str(), m_nWidth, m_nHeight, 4, m_pData, 0);
	}
	else if (getExt(strFilePath) == "bmp")
	{
		bRet = stbi_write_bmp(strFilePath.c_str(), m_nWidth, m_nHeight, 4, m_pData);
	}
	else if (getExt(strFilePath) == "tga")
	{
		bRet = stbi_write_tga(strFilePath.c_str(), m_nWidth, m_nHeight, 4, m_pData);
	}
	return bRet != 0;
}

CCImage::EImageFormat CCImage::computeImageFormatType(const std::string& filename)
{
	CCImage::EImageFormat ret = CCImage::kFmtUnKnown;
	if (getExt(filename) == "jpg" || getExt(filename) == "jpeg")
	{
		ret = CCImage::kFmtJpg;
	}
	else if (getExt(filename) == "png")
	{
		ret = CCImage::kFmtPng;
	}
	return ret;
}

unsigned char* CCImage::convertToPremultipliedData(CCImage* image)
{
	unsigned char* tempData = image->getData();
    bool hasAlpha = image->hasAlpha();
	unsigned int width = image->getWidth();
    unsigned int height = image->getHeight();
    size_t bpp = image->getBitsPerComponent();
    // compute pixel format
    CCTexture2DPixelFormat pixelFormat = hasAlpha ? CCTexture2D::getDefaultAlphaPixelFormat() : (bpp >= 8 ? kCCTexture2DPixelFormat_RGB888 : kCCTexture2DPixelFormat_RGB565);
    
    // Repack the pixel data into the right format
    unsigned int length = width * height;
    unsigned int* inPixel32 = NULL;
    unsigned char* inPixel8 = NULL;
    unsigned short* outPixel16 = NULL;
	
    if (pixelFormat == kCCTexture2DPixelFormat_RGB565)
    {
        if (hasAlpha)
        {
            // Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGGBBBBB"
            
            tempData = new unsigned char[width * height * 2];
            outPixel16 = (unsigned short*)tempData;
            inPixel32 = (unsigned int*)image->getData();
            
            for (unsigned int i = 0; i < length; ++i, ++inPixel32)
            {
				unsigned int R = ((((*inPixel32 >>  0) & 0xFF) >> 3) << 11);
				unsigned int G = ((((*inPixel32 >>  8) & 0xFF) >> 2) << 5);
				unsigned int B = ((((*inPixel32 >> 16) & 0xFF) >> 3) << 0);
                *outPixel16++ = R|G|B;
            }
        }
        else 
        {
            // Convert "RRRRRRRRRGGGGGGGGBBBBBBBB" to "RRRRRGGGGGGBBBBB"
            
            tempData = new unsigned char[width * height * 2];
            outPixel16 = (unsigned short*)tempData;
            inPixel8 = (unsigned char*)image->getData();
            
            for (unsigned int i = 0; i < length; ++i)
            {
				unsigned int R = (((*inPixel8++ & 0xFF) >> 3) << 11);
				unsigned int G = (((*inPixel8++ & 0xFF) >> 2) << 5);
				unsigned int B = (((*inPixel8++ & 0xFF) >> 3) << 0);
                *outPixel16++ = R|G|B;
            }
        }    
    }
    else if (pixelFormat == kCCTexture2DPixelFormat_RGBA4444)
    {
        // Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRGGGGBBBBAAAA"
        
        inPixel32 = (unsigned int*)image->getData();  
        tempData = new unsigned char[width * height * 2];
        outPixel16 = (unsigned short*)tempData;
        
        for (unsigned int i = 0; i < length; ++i, ++inPixel32)
        {
            *outPixel16++ = 
            ((((*inPixel32 >> 0) & 0xFF) >> 4) << 12) | // R
            ((((*inPixel32 >> 8) & 0xFF) >> 4) <<  8) | // G
            ((((*inPixel32 >> 16) & 0xFF) >> 4) << 4) | // B
            ((((*inPixel32 >> 24) & 0xFF) >> 4) << 0);  // A
        }
    }
    else if (pixelFormat == kCCTexture2DPixelFormat_RGB5A1)
    {
        // Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGBBBBBA"
        inPixel32 = (unsigned int*)image->getData();   
        tempData = new unsigned char[width * height * 2];
        outPixel16 = (unsigned short*)tempData;
        
        for (unsigned int i = 0; i < length; ++i, ++inPixel32)
        {
            *outPixel16++ = 
            ((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) | // R
            ((((*inPixel32 >> 8) & 0xFF) >> 3) <<  6) | // G
            ((((*inPixel32 >> 16) & 0xFF) >> 3) << 1) | // B
            ((((*inPixel32 >> 24) & 0xFF) >> 7) << 0);  // A
        }
    }
    else if (pixelFormat == kCCTexture2DPixelFormat_A8)
    {
        // Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "AAAAAAAA"
        inPixel32 = (unsigned int*)image->getData();
        tempData = new unsigned char[width * height];
        unsigned char *outPixel8 = tempData;
        
        for (unsigned int i = 0; i < length; ++i, ++inPixel32)
        {
            *outPixel8++ = (*inPixel32 >> 24) & 0xFF;  // A
        }
    }

    if (hasAlpha && pixelFormat == kCCTexture2DPixelFormat_RGB888)
    {
        // Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRRRRGGGGGGGGBBBBBBBB"
        inPixel32 = (unsigned int*)image->getData();
        tempData = new unsigned char[width * height * 3];
        unsigned char *outPixel8 = tempData;
        
        for (unsigned int i = 0; i < length; ++i, ++inPixel32)
        {
            *outPixel8++ = (*inPixel32 >> 0) & 0xFF; // R
            *outPixel8++ = (*inPixel32 >> 8) & 0xFF; // G
            *outPixel8++ = (*inPixel32 >> 16) & 0xFF; // B
        }
    }
	return tempData;
}

NS_CC_END

