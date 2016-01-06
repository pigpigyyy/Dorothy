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

CCImage::CCImage()
: m_nWidth(0)
, m_nHeight(0)
, m_nBitsPerComponent(0)
, m_pData(0)
, m_bHasAlpha(false)
, m_bPreMulti(false)
, m_format(kFmtUnKnown)
{ }

CCImage::~CCImage()
{
	if (m_format != kFmtRawData)
	{
		stbi_image_free(m_pData);
	}
	else
	{
		CC_SAFE_DELETE_ARRAY(m_pData);
	}
}

bool CCImage::initWithImageFile(const char* strPath, EImageFormat eImgFmt/* = eFmtPng*/)
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
	const int nBytesPerComponent = 4;
	bool bRet = false;
	m_bHasAlpha = true;
	m_nBitsPerComponent = nBitsPerComponent;
	m_format = eFmt;
	if (eFmt != kFmtRawData)
	{
		int w, h, components;
		// always 4 components. May be very slow for some formats.
		m_pData = stbi_load_from_memory((stbi_uc*)pData, nDataLen, &w, &h, (int*)&components, nBytesPerComponent);
		m_nWidth = w;
		m_nHeight = h;
		if (m_pData)
		{
			bRet = true;
			int rowbytes = m_nWidth * nBytesPerComponent;
			unsigned int *tmp = (unsigned int*)m_pData;
			for (int i = 0; i < m_nHeight; i++)
			{
				for (int j = 0; j < rowbytes; j += 4)
				{
					*tmp++ = CC_RGB_PREMULTIPLY_ALPHA(m_pData[i*rowbytes + j], m_pData[i*rowbytes + j + 1], m_pData[i*rowbytes + j + 2], m_pData[i*rowbytes + j + 3]);
				}
			}
			m_bPreMulti = true;
		}
	}
	else
	{
		do
		{
			CC_BREAK_IF(0 == nWidth || 0 == nHeight);
			m_nHeight = (short)nHeight;
			m_nWidth = (short)nWidth;
			// only RGBA8888 supported
			int nSize = nHeight * nWidth * nBytesPerComponent;
			m_pData = new unsigned char[nSize];
			CC_BREAK_IF(!m_pData);
			memcpy(m_pData, pData, nSize);
			m_bPreMulti = true;
			bRet = true;
		} while (0);
	}
	return bRet;
}

NS_CC_END

