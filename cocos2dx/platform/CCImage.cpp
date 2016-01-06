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

#include "platform/CCImage.h"
#include "platform/CCFileUtils.h"
#include "textures/CCTexture2D.h"
#include "support/image_support/stb_image_write.h"
#include <string>

NS_CC_BEGIN

#define CC_RGB_UNPREMULTIPLY_ALPHA(vr, vg, vb, va) \
	(((unsigned)(vr)<<8)/((unsigned)(va)+1)) | \
	((((unsigned)(vg)<<8)/((unsigned)(va)+1)) << 8) | \
	((((unsigned)(vb)<<8)/((unsigned)(va)+1)) << 16) | \
	((unsigned)(va) << 24)

bool CCImage::saveToFile(const char* pszFilePath)
{
	unsigned char* pData = m_pData;
	if (m_bPreMulti)
	{
		const int nBytesPerComponent = 4;
		int dataLen = m_nWidth * m_nHeight * nBytesPerComponent;
		pData = new unsigned char[dataLen];
		memcpy(pData, m_pData, dataLen);
		int rowbytes = m_nWidth * nBytesPerComponent;
		unsigned int* tmp = (unsigned int*)pData;
		for (int i = 0; i < m_nHeight; i++)
		{
			for (int j = 0; j < rowbytes; j += 4)
			{
				*tmp++ = CC_RGB_UNPREMULTIPLY_ALPHA(
					pData[i*rowbytes + j],
					pData[i*rowbytes + j + 1],
					pData[i*rowbytes + j + 2],
					pData[i*rowbytes + j + 3]);
			}
		}
	}
	int bRet = 0;
	std::string ext = CCFileUtils::getExt(pszFilePath);
	if (ext == "png")
	{
		bRet = stbi_write_png(pszFilePath, m_nWidth, m_nHeight, 4, pData, 0);
	}
	else if (ext == "bmp")
	{
		bRet = stbi_write_bmp(pszFilePath, m_nWidth, m_nHeight, 4, pData);
	}
	else if (ext == "tga")
	{
		bRet = stbi_write_tga(pszFilePath, m_nWidth, m_nHeight, 4, pData);
	}
	if (m_bPreMulti)
	{
		delete [] pData;
	}
	return bRet != 0;
}

CCImage::EImageFormat CCImage::computeImageFormatType(const std::string& filename)
{
	CCImage::EImageFormat ret = CCImage::kFmtUnKnown;
	std::string ext = CCFileUtils::getExt(filename);
	if (ext == "jpg" || ext == "jpeg")
	{
		ret = CCImage::kFmtJpg;
	}
	else if (ext == "png")
	{
		ret = CCImage::kFmtPng;
	}
	return ret;
}

unsigned char* CCImage::convertToRequiredFormat(CCImage* image)
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
