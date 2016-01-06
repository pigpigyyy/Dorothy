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
#import "CCImage.h"
#import "CCFileUtils.h"
#import "CCCommon.h"
#import "CCTexture2D.h"
#import "stb_image_write.h"
#import <string>

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define CC_RGB_PREMULTIPLY_ALPHA(vr, vg, vb, va) \
    (unsigned)(((unsigned)((unsigned char)(vr) * ((unsigned char)(va) + 1)) >> 8) | \
    ((unsigned)((unsigned char)(vg) * ((unsigned char)(va) + 1) >> 8) << 8) | \
    ((unsigned)((unsigned char)(vb) * ((unsigned char)(va) + 1) >> 8) << 16) | \
    ((unsigned)(unsigned char)(va) << 24))

#define CC_RGB_UNPREMULTIPLY_ALPHA(vr, vg, vb, va) \
	(((unsigned)(vr)<<8)/((unsigned)(va)+1)) | \
	((((unsigned)(vg)<<8)/((unsigned)(va)+1)) << 8) | \
	((((unsigned)(vb)<<8)/((unsigned)(va)+1)) << 16) | \
	((unsigned)(va) << 24)

typedef struct
{
	unsigned int height;
	unsigned int width;
	int bitsPerComponent;
	bool hasAlpha;
	bool isPremultipliedAlpha;
	unsigned char* data;
} tImageInfo;

static bool _initWithImage(CGImageRef cgImage, tImageInfo* pImageinfo)
{
    if (cgImage == NULL)
    {
        return false;
    }
    
    // get image info
    pImageinfo->width = (unsigned int)CGImageGetWidth(cgImage);
    pImageinfo->height = (unsigned int)CGImageGetHeight(cgImage);
    
    CGImageAlphaInfo info = CGImageGetAlphaInfo(cgImage);
    pImageinfo->hasAlpha = (info == kCGImageAlphaPremultipliedLast) 
                            || (info == kCGImageAlphaPremultipliedFirst) 
                            || (info == kCGImageAlphaLast) 
                            || (info == kCGImageAlphaFirst);
    
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(cgImage);
    if (colorSpace)
    {
        if (pImageinfo->hasAlpha)
        {
            info = kCGImageAlphaPremultipliedLast;
            pImageinfo->isPremultipliedAlpha = true;
        }
        else 
        {
            info = kCGImageAlphaNoneSkipLast;
            pImageinfo->isPremultipliedAlpha = false;
        }
    }
    else
    {
        return false;
    }
    
    // change to RGBA8888
    pImageinfo->hasAlpha = true;
    pImageinfo->bitsPerComponent = 8;
    pImageinfo->data = new unsigned char[pImageinfo->width * pImageinfo->height * 4];
    colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(pImageinfo->data, 
                                                 pImageinfo->width,
                                                 pImageinfo->height,
                                                 8, 
                                                 4 * pImageinfo->width, 
                                                 colorSpace, 
                                                 info | kCGBitmapByteOrder32Big);
    
    CGContextClearRect(context, CGRectMake(0, 0, pImageinfo->width, pImageinfo->height));
    //CGContextTranslateCTM(context, 0, 0);
    CGContextDrawImage(context, CGRectMake(0, 0, pImageinfo->width, pImageinfo->height), cgImage);
    
    CGContextRelease(context);
    CFRelease(colorSpace);
  
    return true;
}

static bool _initWithFile(const char* path, tImageInfo *pImageinfo)
{
    CGImageRef CGImage;
    UIImage* jpg;
    UIImage* png;
    bool ret;
    
    // convert jpg to png before loading the texture
    NSString* fullPath = [NSString stringWithUTF8String:path];
    jpg = [[UIImage alloc] initWithContentsOfFile: fullPath];
    png = [[UIImage alloc] initWithData:UIImagePNGRepresentation(jpg)];
    CGImage = png.CGImage;    
    
    ret = _initWithImage(CGImage, pImageinfo);
    
    [png release];
    [jpg release];
    
    return ret;
}

static bool _initWithData(void* pBuffer, int length, tImageInfo* pImageinfo)
{
    bool ret = false;
    
    if (pBuffer) 
    {
        CGImageRef CGImage;
        NSData* data;
        
        data = [NSData dataWithBytes:pBuffer length:length];
        CGImage = [[UIImage imageWithData:data] CGImage];
        
        ret = _initWithImage(CGImage, pImageinfo);
    }
    
    return ret;
}

static CGSize _calculateStringSize(NSString *str, id font, CGSize *constrainSize)
{
    NSArray *listItems = [str componentsSeparatedByString: @"\n"];
    CGSize dim = CGSizeZero;
    CGSize textRect = CGSizeZero;
    textRect.width = constrainSize->width > 0 ? constrainSize->width
                                              : 0x7fffffff;
    textRect.height = constrainSize->height > 0 ? constrainSize->height
                                              : 0x7fffffff;
    
    
    for (NSString *s in listItems)
    {
        CGSize tmp = [s sizeWithFont:font constrainedToSize:textRect];
        
        if (tmp.width > dim.width)
        {
           dim.width = tmp.width; 
        }
        
        dim.height += tmp.height;
    }
    
    return dim;
}

// refer CCImage::ETextAlign
#define ALIGN_TOP 1
#define ALIGN_CENTER 3
#define ALIGN_BOTTOM 2

static bool _initWithString(const char* pText, cocos2d::CCImage::ETextAlign eAlign, const char* pFontName, int nSize, tImageInfo* pInfo)
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(!pText || !pInfo);
        
        NSString* str  = [NSString stringWithUTF8String:pText];
        NSString* fntName = [NSString stringWithUTF8String:pFontName];
        CGSize dim, constrainSize;
        constrainSize.width = pInfo->width;
        constrainSize.height = pInfo->height;
        
        // On iOS custom fonts must be listed beforehand in the App info.plist (in order to be usable) and referenced only the by the font family name itself when
        // calling [UIFont fontWithName]. Therefore even if the developer adds 'SomeFont.ttf' or 'fonts/SomeFont.ttf' to the App .plist, the font must
        // be referenced as 'SomeFont' when calling [UIFont fontWithName]. Hence we strip out the folder path components and the extension here in order to get just
        // the font family name itself. This stripping step is required especially for references to user fonts stored in CCB files; CCB files appear to store
        // the '.ttf' extensions when referring to custom fonts.
        fntName = [[fntName lastPathComponent] stringByDeletingPathExtension];
        
        // create the font   
        id font = [UIFont fontWithName:fntName size:nSize];
        
        if (font)
        {
            dim = _calculateStringSize(str, font, &constrainSize);
        }
        else
        {
            if (!font)
            {
                font = [UIFont systemFontOfSize:nSize];
            }
                
            if (font)
            {
                dim = _calculateStringSize(str, font, &constrainSize);
            }
        }

        CC_BREAK_IF(!font);
        
        // compute start point
        int startH = 0;
        if (constrainSize.height > dim.height)
        {
            // vertical alignment
            unsigned int vAlignment = (eAlign >> 4) & 0x0F;
            if (vAlignment == ALIGN_TOP)
            {
                startH = 0;
            }
            else if (vAlignment == ALIGN_CENTER)
            {
                startH = (constrainSize.height - dim.height) / 2;
            }
            else 
            {
                startH = constrainSize.height - dim.height;
            }
        }
        
        // adjust text rect
        if (constrainSize.width > 0 && constrainSize.width > dim.width)
        {
            dim.width = constrainSize.width;
        }
        if (constrainSize.height > 0 && constrainSize.height > dim.height)
        {
            dim.height = constrainSize.height;
        }
        
        unsigned char* data = new unsigned char[(int)(dim.width * dim.height * 4)];
        memset(data, 0, (int)(dim.width * dim.height * 4));
        
        // draw text
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();    
        CGContextRef context = CGBitmapContextCreate(data, dim.width, dim.height, 8, (int)dim.width * 4, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
        CGColorSpaceRelease(colorSpace);
        
        if (! context)
        {
            delete [] data;
            break;
        }
        
        CGContextSetRGBFillColor(context, 1, 1, 1, 1);
        CGContextTranslateCTM(context, 0.0f, dim.height);
        CGContextScaleCTM(context, 1.0f, -1.0f); //NOTE: NSString draws in UIKit referential i.e. renders upside-down compared to CGBitmapContext referential
        UIGraphicsPushContext(context);
        
        // measure text size with specified font and determine the rectangle to draw text in
        unsigned uHoriFlag = eAlign & 0x0f;
        UITextAlignment align = (UITextAlignment)((2 == uHoriFlag) ? UITextAlignmentRight
                                : (3 == uHoriFlag) ? UITextAlignmentCenter
                                : UITextAlignmentLeft);
        
        // normal fonts
        /*
        if( [font isKindOfClass:[UIFont class] ] )
        {
            [str drawInRect:CGRectMake(0, startH, dim.width, dim.height) withFont:font lineBreakMode:(UILineBreakMode)UILineBreakModeWordWrap alignment:align];
        }
        else // ZFont class 
        {
            [FontLabelStringDrawingHelper drawInRect:str rect:CGRectMake(0, startH, dim.width, dim.height) withZFont:font lineBreakMode:(UILineBreakMode)UILineBreakModeWordWrap alignment:align];
        }
         */
        [str drawInRect:CGRectMake(0, startH, dim.width, dim.height) withFont:font lineBreakMode:NSLineBreakByWordWrapping alignment:(NSTextAlignment)align];

        UIGraphicsPopContext();
        
        CGContextRelease(context);
               
        // output params
        pInfo->data = data;
        pInfo->hasAlpha = true;
        pInfo->isPremultipliedAlpha = true;
        pInfo->bitsPerComponent = 8;
        pInfo->width = dim.width;
        pInfo->height = dim.height;
        bRet = true;
    } while (0);

    return bRet;
}

NS_CC_BEGIN

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
    CC_SAFE_DELETE_ARRAY(m_pData);
}

bool CCImage::initWithImageFile(const char * strPath, EImageFormat eImgFmt/* = eFmtPng*/)
{
	bool bRet = false;
    unsigned long nSize = 0;
    unsigned char* pBuffer = CCFileUtils::sharedFileUtils()->getFileData(
				CCFileUtils::sharedFileUtils()->fullPathForFilename(strPath).c_str(),
				"rb",
				&nSize);
				
    if (pBuffer != NULL && nSize > 0)
    {
        bRet = initWithImageData(pBuffer, (int)nSize, eImgFmt);
    }
    CC_SAFE_DELETE_ARRAY(pBuffer);
    return bRet;
}

bool CCImage::initWithImageFileThreadSafe(const char *fullpath, EImageFormat imageType)
{
    /*
     * CCFileUtils::fullPathFromRelativePath() is not thread-safe, it use autorelease().
     */
    bool bRet = false;
    unsigned long nSize = 0;
    unsigned char* pBuffer = CCFileUtils::sharedFileUtils()->getFileData(fullpath, "rb", &nSize);
    if (pBuffer != NULL && nSize > 0)
    {
        bRet = initWithImageData(pBuffer, (int)nSize, imageType);
    }
    CC_SAFE_DELETE_ARRAY(pBuffer);
    return bRet;
}

bool CCImage::initWithImageData(
	void* pData,
	int nDataLen,
	EImageFormat eFmt,
	int nWidth,
	int nHeight,
	int nBitsPerComponent)
{
    bool bRet = false;
	m_format = eFmt;
    tImageInfo info = {0};
    do 
    {
        CC_BREAK_IF(!pData || nDataLen <= 0);
        if (eFmt == kFmtRawData)
        {
			do
    		{
        		CC_BREAK_IF(0 == nWidth || 0 == nHeight);
        		m_nBitsPerComponent = nBitsPerComponent;
        		m_nHeight = (short)nHeight;
        		m_nWidth = (short)nWidth;
        		m_bHasAlpha = true;
				m_bPreMulti = true;
		        // only RGBA8888 supported
				const int nBytesPerComponent = 4;
        		int nSize = nHeight * nWidth * nBytesPerComponent;
        		m_pData = new unsigned char[nSize];
        		CC_BREAK_IF(!m_pData);
        		memcpy(m_pData, pData, nSize);
		        bRet = true;
    		} while (0);
		}
        else // init with png or jpg file data
        {
            bRet = _initWithData(pData, nDataLen, &info);
            if (bRet)
            {
                m_nHeight = (short)info.height;
                m_nWidth = (short)info.width;
                m_nBitsPerComponent = info.bitsPerComponent;
                m_bHasAlpha = info.hasAlpha;
                m_bPreMulti = info.isPremultipliedAlpha;
                m_pData = info.data;
            }
        }
    } while (0);
    return bRet;
}

bool CCImage::initWithString(
	const char * pText,
	int nWidth /* = 0 */,
	int nHeight /* = 0 */,
	ETextAlign eAlignMask /* = kAlignCenter */,
	const char* pFontName /* = nil */,
	int nSize /* = 0 */)
{
    tImageInfo info = {0};
    info.width = nWidth;
    info.height = nHeight;
      
    if (! _initWithString(pText, eAlignMask, pFontName, nSize, &info))
    {
        return false;
    }
    m_nHeight = (short)info.height;
    m_nWidth = (short)info.width;
    m_nBitsPerComponent = info.bitsPerComponent;
    m_bHasAlpha = info.hasAlpha;
    m_bPreMulti = info.isPremultipliedAlpha;
    m_pData = info.data;

    return true;
}

static std::string getExt(const std::string& filename)
{
	int index = (int)filename.find_last_of('.');
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
	std::string ext = getExt(pszFilePath);
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
	std::string ext = getExt(filename);
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

