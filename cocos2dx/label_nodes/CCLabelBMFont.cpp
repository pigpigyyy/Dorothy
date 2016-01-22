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

Use any of these editors to generate BMFonts:
http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
http://www.angelcode.com/products/bmfont/ (Free, Windows only)

****************************************************************************/
#include "CCLabelBMFont.h"
#include "cocoa/CCString.h"
#include "platform/platform.h"
#include "cocoa/CCDictionary.h"
#include "basics/CCConfiguration.h"
#include "draw_nodes/CCDrawingPrimitives.h"
#include "sprite_nodes/CCSprite.h"
#include "support/CCPointExtension.h"
#include "platform/CCFileUtils.h"
#include "basics/CCDirector.h"
#include "textures/CCTextureCache.h"
#include "support/ccUTF8.h"
#include <memory>

using namespace std;


NS_CC_BEGIN

// The return value needs to be deleted by CC_SAFE_DELETE_ARRAY.
static unsigned short* copyUTF16StringN(unsigned short* str)
{
	int length = str ? cc_wcslen(str) : 0;
	unsigned short* ret = new unsigned short[length + 1];
	for (int i = 0; i < length; ++i) {
		ret[i] = str[i];
	}
	ret[length] = 0;
	return ret;
}

//
//FNTConfig Cache - free functions
//
static CCDictionary* s_pConfigurations = NULL;

CCBMFontConfiguration* FNTConfigLoadFile(const char *fntFile)
{
	CCBMFontConfiguration* pRet = NULL;

	if (s_pConfigurations == NULL)
	{
		s_pConfigurations = new CCDictionary();
	}

	pRet = (CCBMFontConfiguration*)s_pConfigurations->objectForKey(fntFile);
	if (pRet == NULL)
	{
		pRet = CCBMFontConfiguration::create(fntFile);
		if (pRet)
		{
			s_pConfigurations->setObject(pRet, fntFile);
		}
	}

	return pRet;
}

void FNTConfigRemoveCache(void)
{
	if (s_pConfigurations)
	{
		s_pConfigurations->removeAllObjects();
		CC_SAFE_RELEASE_NULL(s_pConfigurations);
	}
}

//
//BitmapFontConfiguration
//

CCBMFontConfiguration * CCBMFontConfiguration::create(const char *FNTfile)
{
	CCBMFontConfiguration * pRet = new CCBMFontConfiguration();
	if (pRet->initWithFNTfile(FNTfile))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCBMFontConfiguration::initWithFNTfile(const char *FNTfile)
{
	m_pKerningDictionary = NULL;
	m_pFontDefDictionary = NULL;

	m_pCharacterSet = this->parseConfigFile(FNTfile);

	if (!m_pCharacterSet)
	{
		return false;
	}

	return true;
}

std::set<unsigned int>* CCBMFontConfiguration::getCharacterSet() const
{
	return m_pCharacterSet;
}

CCBMFontConfiguration::CCBMFontConfiguration()
	: m_pFontDefDictionary(NULL)
	, m_nCommonHeight(0)
	, m_pKerningDictionary(NULL)
	, m_pCharacterSet(NULL)
{

}

CCBMFontConfiguration::~CCBMFontConfiguration()
{
	CCLOGINFO("cocos2d: deallocing CCBMFontConfiguration");
	this->purgeFontDefDictionary();
	this->purgeKerningDictionary();
	m_sAtlasName.clear();
	CC_SAFE_DELETE(m_pCharacterSet);
}

const char* CCBMFontConfiguration::description()
{
	return CCString::createWithFormat(
		"<CCBMFontConfiguration = %08X | Glphys:%d Kernings:%d | Image = %s>",
		this,
		HASH_COUNT(m_pFontDefDictionary),
		HASH_COUNT(m_pKerningDictionary),
		m_sAtlasName.c_str()
		)->getCString();
}

void CCBMFontConfiguration::purgeKerningDictionary()
{
	tCCKerningHashElement *current;
	while (m_pKerningDictionary)
	{
		current = m_pKerningDictionary;
		HASH_DEL(m_pKerningDictionary, current);
		free(current);
	}
}

void CCBMFontConfiguration::purgeFontDefDictionary()
{
	tCCFontDefHashElement *current, *tmp;

	HASH_ITER(hh, m_pFontDefDictionary, current, tmp) {
		HASH_DEL(m_pFontDefDictionary, current);
		free(current);
	}
}

std::set<unsigned int>* CCBMFontConfiguration::parseConfigFile(const char *controlFile)
{
	std::string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(controlFile);
	CCString *contents = CCString::createWithContentsOfFile(fullpath.c_str());

	CCAssert(contents, "CCBMFontConfiguration::parseConfigFile | Open file error.");

	set<unsigned int> *validCharsString = new set<unsigned int>();

	if (!contents)
	{
		CCLOG("cocos2d: Error parsing FNTfile %s", controlFile);
		return NULL;
	}

	// parse spacing / padding
	std::string line;
	std::string strLeft = contents->getCString();
	while (strLeft.length() > 0)
	{
		int pos = (int)strLeft.find('\n');

		if (pos != (int)std::string::npos)
		{
			// the data is more than a line.get one line
			line = strLeft.substr(0, pos);
			strLeft = strLeft.substr(pos + 1);
		}
		else
		{
			// get the left data
			line = strLeft;
			strLeft.erase();
		}

		if (line.substr(0, strlen("info face")) == "info face")
		{
			// XXX: info parsing is incomplete
			// Not needed for the Hiero editors, but needed for the AngelCode editor
			//            [self parseInfoArguments:line];
			this->parseInfoArguments(line);
		}
		// Check to see if the start of the line is something we are interested in
		else if (line.substr(0, strlen("common lineHeight")) == "common lineHeight")
		{
			this->parseCommonArguments(line);
		}
		else if (line.substr(0, strlen("page id")) == "page id")
		{
			this->parseImageFileName(line, controlFile);
		}
		else if (line.substr(0, strlen("chars c")) == "chars c")
		{
			// Ignore this line
		}
		else if (line.substr(0, strlen("char")) == "char")
		{
			// Parse the current line and create a new CharDef
			tCCFontDefHashElement* element = (tCCFontDefHashElement*)malloc(sizeof(*element));
			this->parseCharacterDefinition(line, &element->fontDef);

			element->key = element->fontDef.charID;
			HASH_ADD_INT(m_pFontDefDictionary, key, element);

			validCharsString->insert(element->fontDef.charID);
		}
		//        else if(line.substr(0,strlen("kernings count")) == "kernings count")
		//        {
		//            this->parseKerningCapacity(line);
		//        }
		else if (line.substr(0, strlen("kerning first")) == "kerning first")
		{
			this->parseKerningEntry(line);
		}
	}

	return validCharsString;
}

void CCBMFontConfiguration::parseImageFileName(std::string line, const char *fntFile)
{
	//////////////////////////////////////////////////////////////////////////
	// line to parse:
	// page id=0 file="bitmapFontTest.png"
	//////////////////////////////////////////////////////////////////////////

	// page ID. Sanity check
	int index = (int)line.find('=') + 1;
	int index2 = (int)line.find(' ', index);
	std::string value = line.substr(index, index2 - index);
	CCAssert(atoi(value.c_str()) == 0, "LabelBMFont file could not be found");
	// file 
	index = (int)line.find('"') + 1;
	index2 = (int)line.find('"', index);
	value = line.substr(index, index2 - index);

	m_sAtlasName = CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(value.c_str(), fntFile);
}

void CCBMFontConfiguration::parseInfoArguments(std::string line)
{
	//////////////////////////////////////////////////////////////////////////
	// possible lines to parse:
	// info face="Script" size=32 bold=0 italic=0 charset="" unicode=1 stretchH=100 smooth=1 aa=1 padding=1,4,3,2 spacing=0,0 outline=0
	// info face="Cracked" size=36 bold=0 italic=0 charset="" unicode=0 stretchH=100 smooth=1 aa=1 padding=0,0,0,0 spacing=1,1
	//////////////////////////////////////////////////////////////////////////

	// padding
	int index = (int)line.find("padding=");
	int index2 = (int)line.find(' ', index);
	std::string value = line.substr(index, index2 - index);
	sscanf(value.c_str(), "padding=%d,%d,%d,%d", &m_tPadding.top, &m_tPadding.right, &m_tPadding.bottom, &m_tPadding.left);
	//CCLOG("cocos2d: padding: %d,%d,%d,%d", m_tPadding.left, m_tPadding.top, m_tPadding.right, m_tPadding.bottom);
}

void CCBMFontConfiguration::parseCommonArguments(std::string line)
{
	//////////////////////////////////////////////////////////////////////////
	// line to parse:
	// common lineHeight=104 base=26 scaleW=1024 scaleH=512 pages=1 packed=0
	//////////////////////////////////////////////////////////////////////////

	// Height
	int index = (int)line.find("lineHeight=");
	int index2 = (int)line.find(' ', index);
	std::string value = line.substr(index, index2 - index);
	sscanf(value.c_str(), "lineHeight=%d", &m_nCommonHeight);
	// scaleW. sanity check
	index = (int)line.find("scaleW=") + strlen("scaleW=");
	index2 = (int)line.find(' ', index);
	value = line.substr(index, index2 - index);
	CCAssert(atoi(value.c_str()) <= CCConfiguration::sharedConfiguration()->getMaxTextureSize(), "CCLabelBMFont: page can't be larger than supported");
	// scaleH. sanity check
	index = (int)line.find("scaleH=") + strlen("scaleH=");
	index2 = (int)line.find(' ', index);
	value = line.substr(index, index2 - index);
	CCAssert(atoi(value.c_str()) <= CCConfiguration::sharedConfiguration()->getMaxTextureSize(), "CCLabelBMFont: page can't be larger than supported");
	// pages. sanity check
	index = (int)line.find("pages=") + strlen("pages=");
	index2 = (int)line.find(' ', index);
	value = line.substr(index, index2 - index);
	CCAssert(atoi(value.c_str()) == 1, "CCBitfontAtlas: only supports 1 page");

	// packed (ignore) What does this mean ??
}

void CCBMFontConfiguration::parseCharacterDefinition(std::string line, ccBMFontDef *characterDefinition)
{
	//////////////////////////////////////////////////////////////////////////
	// line to parse:
	// char id=32   x=0     y=0     width=0     height=0     xoffset=0     yoffset=44    xadvance=14     page=0  chnl=0 
	//////////////////////////////////////////////////////////////////////////

	// Character ID
	int index = (int)line.find("id=");
	int index2 = (int)line.find(' ', index);
	std::string value = line.substr(index, index2 - index);
	sscanf(value.c_str(), "id=%u", &characterDefinition->charID);

	// Character x
	index = (int)line.find("x=");
	index2 = (int)line.find(' ', index);
	value = line.substr(index, index2 - index);
	sscanf(value.c_str(), "x=%f", &characterDefinition->rect.origin.x);
	// Character y
	index = (int)line.find("y=");
	index2 = (int)line.find(' ', index);
	value = line.substr(index, index2 - index);
	sscanf(value.c_str(), "y=%f", &characterDefinition->rect.origin.y);
	// Character width
	index = (int)line.find("width=");
	index2 = (int)line.find(' ', index);
	value = line.substr(index, index2 - index);
	sscanf(value.c_str(), "width=%f", &characterDefinition->rect.size.width);
	// Character height
	index = (int)line.find("height=");
	index2 = (int)line.find(' ', index);
	value = line.substr(index, index2 - index);
	sscanf(value.c_str(), "height=%f", &characterDefinition->rect.size.height);
	// Character xoffset
	index = (int)line.find("xoffset=");
	index2 = (int)line.find(' ', index);
	value = line.substr(index, index2 - index);
	sscanf(value.c_str(), "xoffset=%hd", &characterDefinition->xOffset);
	// Character yoffset
	index = (int)line.find("yoffset=");
	index2 = (int)line.find(' ', index);
	value = line.substr(index, index2 - index);
	sscanf(value.c_str(), "yoffset=%hd", &characterDefinition->yOffset);
	// Character xadvance
	index = (int)line.find("xadvance=");
	index2 = (int)line.find(' ', index);
	value = line.substr(index, index2 - index);
	sscanf(value.c_str(), "xadvance=%hd", &characterDefinition->xAdvance);
}

void CCBMFontConfiguration::parseKerningEntry(std::string line)
{
	//////////////////////////////////////////////////////////////////////////
	// line to parse:
	// kerning first=121  second=44  amount=-7
	//////////////////////////////////////////////////////////////////////////

	// first
	int first;
	int index = (int)line.find("first=");
	int index2 = (int)line.find(' ', index);
	std::string value = line.substr(index, index2 - index);
	sscanf(value.c_str(), "first=%d", &first);

	// second
	int second;
	index = (int)line.find("second=");
	index2 = (int)line.find(' ', index);
	value = line.substr(index, index2 - index);
	sscanf(value.c_str(), "second=%d", &second);

	// amount
	int amount;
	index = (int)line.find("amount=");
	index2 = (int)line.find(' ', index);
	value = line.substr(index, index2 - index);
	sscanf(value.c_str(), "amount=%d", &amount);

	tCCKerningHashElement *element = (tCCKerningHashElement *)calloc(sizeof(*element), 1);
	element->amount = amount;
	element->key = (first << 16) | (second & 0xffff);
	HASH_ADD_INT(m_pKerningDictionary, key, element);
}
//
//CCLabelBMFont
//

//LabelBMFont - Purge Cache
void CCLabelBMFont::purgeCachedData()
{
	FNTConfigRemoveCache();
}

CCLabelBMFont * CCLabelBMFont::create()
{
	CCLabelBMFont * pRet = new CCLabelBMFont();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CCLabelBMFont * CCLabelBMFont::create(const char *str, const char *fntFile, float width, CCTextAlignment alignment)
{
	return CCLabelBMFont::create(str, fntFile, width, alignment, CCPoint::zero);
}

CCLabelBMFont * CCLabelBMFont::create(const char *str, const char *fntFile, float width)
{
	return CCLabelBMFont::create(str, fntFile, width, kCCTextAlignmentLeft, CCPoint::zero);
}

CCLabelBMFont * CCLabelBMFont::create(const char *str, const char *fntFile)
{
	return CCLabelBMFont::create(str, fntFile, kCCLabelAutomaticWidth, kCCTextAlignmentLeft, CCPoint::zero);
}

//LabelBMFont - Creation & Init
CCLabelBMFont *CCLabelBMFont::create(const char *str, const char *fntFile, float width/* = kCCLabelAutomaticWidth*/, CCTextAlignment alignment/* = kCCTextAlignmentLeft*/, CCPoint imageOffset/* = CCPoint::zero*/)
{
	CCLabelBMFont *pRet = new CCLabelBMFont();
	if (pRet && pRet->initWithString(str, fntFile, width, alignment, imageOffset))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CCLabelBMFont::init()
{
	if (!CCSpriteBatchNode::init()) return false;
	return initWithString(NULL, NULL, kCCLabelAutomaticWidth, kCCTextAlignmentLeft, CCPoint::zero);
}

bool CCLabelBMFont::initWithString(const char *theString, const char *fntFile, float width/* = kCCLabelAutomaticWidth*/, CCTextAlignment alignment/* = kCCTextAlignmentLeft*/, CCPoint imageOffset/* = CCPoint::zero*/)
{
	CCAssert(!m_pConfiguration, "re-init is no longer supported");
	CCAssert((theString && fntFile) || (theString == NULL && fntFile == NULL), "Invalid params for CCLabelBMFont");

	CCTexture2D *texture = NULL;

	if (fntFile)
	{
		CCBMFontConfiguration *newConf = FNTConfigLoadFile(fntFile);
		if (!newConf)
		{
			CCLOG("cocos2d: WARNING. CCLabelBMFont: Impossible to create font. Please check file: '%s'", fntFile);
			release();
			return false;
		}

		newConf->retain();
		CC_SAFE_RELEASE(m_pConfiguration);
		m_pConfiguration = newConf;

		m_sFntFile = fntFile;

		texture = CCTextureCache::sharedTextureCache()->addImage(m_pConfiguration->getAtlasName());
	}
	else
	{
		texture = new CCTexture2D();
		texture->autorelease();
	}

	if (theString == NULL)
	{
		theString = "";
	}

	if (CCSpriteBatchNode::initWithTexture(texture, (unsigned int)strlen(theString)))
	{
		m_fWidth = width;
		m_pAlignment = alignment;

		m_obContentSize = CCSize::zero;

		m_bIsOpacityModifyRGB = m_pobTextureAtlas->getTexture()->hasPremultipliedAlpha();
		m_obAnchorPoint = ccp(0.5f, 0.5f);

		m_tImageOffset = imageOffset;

		this->setText(theString, true);

		return true;
	}
	return false;
}

CCLabelBMFont::CCLabelBMFont()
	: m_sString(NULL)
	, m_sInitialString(NULL)
	, m_pAlignment(kCCTextAlignmentCenter)
	, m_fWidth(kCCLabelAutomaticWidth)
	, m_pConfiguration(NULL)
	, m_bLineBreakWithoutSpaces(false)
	, m_tImageOffset(CCPoint::zero)
	, m_bIsOpacityModifyRGB(false)
{ }

CCLabelBMFont::~CCLabelBMFont()
{
	CC_SAFE_DELETE_ARRAY(m_sString);
	CC_SAFE_DELETE_ARRAY(m_sInitialString);
	CC_SAFE_RELEASE(m_pConfiguration);
}

// LabelBMFont - Atlas generation
int CCLabelBMFont::kerningAmountForFirst(unsigned short first, unsigned short second)
{
	int ret = 0;
	unsigned int key = (first << 16) | (second & 0xffff);

	if (m_pConfiguration->m_pKerningDictionary) {
		tCCKerningHashElement *element = NULL;
		HASH_FIND_INT(m_pConfiguration->m_pKerningDictionary, &key, element);
		if (element)
			ret = element->amount;
	}
	return ret;
}

void CCLabelBMFont::createFontChars()
{
	int nextFontPositionX = 0;
	int nextFontPositionY = 0;
	unsigned short prev = -1;
	int kerningAmount = 0;

	CCSize tmpSize = CCSize::zero;

	int longestLine = 0;
	unsigned int totalHeight = 0;

	unsigned int quantityOfLines = 1;
	unsigned int stringLen = m_sString ? cc_wcslen(m_sString) : 0;

	if (stringLen == 0) return;

	if (_chars.size() < stringLen) _chars.resize(stringLen);

	set<unsigned int>* charSet = m_pConfiguration->getCharacterSet();

	for (unsigned int i = 0; i < stringLen - 1; ++i)
	{
		unsigned short c = m_sString[i];
		if (c == '\n')
		{
			quantityOfLines++;
		}
	}

	totalHeight = m_pConfiguration->m_nCommonHeight * quantityOfLines;
	nextFontPositionY = 0 - (m_pConfiguration->m_nCommonHeight - m_pConfiguration->m_nCommonHeight * quantityOfLines);

	CCRect rect;
	ccBMFontDef fontDef;

	for (unsigned int i = 0; i < stringLen; i++)
	{
		unsigned short c = m_sString[i];

		if (c == '\n')
		{
			nextFontPositionX = 0;
			nextFontPositionY -= m_pConfiguration->m_nCommonHeight;
			continue;
		}

		if (charSet->find(c) == charSet->end())
		{
			CCLOGWARN("cocos2d::CCLabelBMFont: Attempted to use character not defined in this bitmap: %d", c);
			continue;
		}

		kerningAmount = this->kerningAmountForFirst(prev, c);

		tCCFontDefHashElement* element = NULL;

		// unichar is a short, and an int is needed on HASH_FIND_INT
		unsigned int key = c;
		HASH_FIND_INT(m_pConfiguration->m_pFontDefDictionary, &key, element);
		if (!element)
		{
			CCLOGWARN("cocos2d::CCLabelBMFont: characer not found %d", c);
			continue;
		}

		fontDef = element->fontDef;

		rect = fontDef.rect;
		rect = CC_RECT_PIXELS_TO_POINTS(rect);

		rect.origin.x += m_tImageOffset.x;
		rect.origin.y += m_tImageOffset.y;

		CCSprite* fontChar = _chars[i];
		if (fontChar)
		{
			// Reusing previous Sprite
			fontChar->setVisible(true);
		}
		else
		{
			fontChar = new CCSprite();
			fontChar->initWithTexture(m_pobTextureAtlas->getTexture(), rect);
			addChild(fontChar, 0, i);
			fontChar->release();
			// Apply label properties
			fontChar->setOpacityModifyRGB(m_bIsOpacityModifyRGB);
			_chars[i] = fontChar;
		}

		// updating previous sprite
		fontChar->setTextureRect(rect);

		// See issue 1343. cast( signed short + unsigned integer ) == unsigned integer (sign is lost!)
		int yOffset = m_pConfiguration->m_nCommonHeight - fontDef.yOffset;
		CCPoint fontPos = ccp((float)nextFontPositionX + fontDef.xOffset + fontDef.rect.size.width*0.5f + kerningAmount,
			(float)nextFontPositionY + yOffset - rect.size.height*0.5f * CC_CONTENT_SCALE_FACTOR());
		fontChar->setPosition(CC_POINT_PIXELS_TO_POINTS(fontPos));

		// update kerning
		nextFontPositionX += fontDef.xAdvance + kerningAmount;
		prev = c;

		if (longestLine < nextFontPositionX)
		{
			longestLine = nextFontPositionX;
		}
	}

	// If the last character processed has an xAdvance which is less that the width of the characters image, then we need
	// to adjust the width of the string to take this into account, or the character will overlap the end of the bounding
	// box
	if (fontDef.xAdvance < fontDef.rect.size.width)
	{
		tmpSize.width = longestLine + fontDef.rect.size.width - fontDef.xAdvance;
	}
	else
	{
		tmpSize.width = longestLine;
	}
	tmpSize.height = totalHeight;

	this->setContentSize(CC_SIZE_PIXELS_TO_POINTS(tmpSize));
}

//LabelBMFont - CCLabelProtocol protocol
void CCLabelBMFont::setText(const char *newString)
{
	this->setText(newString, true);
}

void CCLabelBMFont::setText(const char *newString, bool needUpdateLabel)
{
	if (newString == NULL)
	{
		newString = "";
	}
	if (needUpdateLabel)
	{
		m_sInitialStringUTF8 = newString;
	}
	unsigned short* utf16String = cc_utf8_to_utf16(newString);
	setText(utf16String, needUpdateLabel);
	CC_SAFE_DELETE_ARRAY(utf16String);
}

CCSprite* CCLabelBMFont::getChar(int index)
{
	if (index < (int)_chars.size())
	{
		return _chars[index];
	}
	return nullptr;
}

void CCLabelBMFont::setText(unsigned short* newString, bool needUpdateLabel)
{
	if (needUpdateLabel)
	{
		unsigned short* tmp = m_sInitialString;
		m_sInitialString = copyUTF16StringN(newString);
		CC_SAFE_DELETE_ARRAY(m_sString);
		CC_SAFE_DELETE_ARRAY(tmp);
	}
	else
	{
		unsigned short* tmp = m_sString;
		m_sString = copyUTF16StringN(newString);
		CC_SAFE_DELETE_ARRAY(tmp);
	}

	if (m_pChildren && m_pChildren->count() != 0)
	{
		CCObject* child;
		CCARRAY_FOREACH(m_pChildren, child)
		{
			CCNode* pNode = (CCNode*)child;
			if (pNode)
			{
				pNode->setVisible(false);
			}
		}
	}
	this->createFontChars();

	if (needUpdateLabel)
	{
		updateLabel();
	}
}

const char* CCLabelBMFont::getText()
{
	return m_sInitialStringUTF8.c_str();
}

void CCLabelBMFont::setOpacityModifyRGB(bool var)
{
	m_bIsOpacityModifyRGB = var;
	if (m_pChildren && m_pChildren->count() != 0)
	{
		CCObject* child;
		CCARRAY_FOREACH(m_pChildren, child)
		{
			CCNode* pNode = (CCNode*)child;
			if (pNode)
			{
				pNode->setOpacityModifyRGB(m_bIsOpacityModifyRGB);
			}
		}
	}
}
bool CCLabelBMFont::isOpacityModifyRGB()
{
	return m_bIsOpacityModifyRGB;
}

// LabelBMFont - AnchorPoint
void CCLabelBMFont::setAnchorPoint(const CCPoint& point)
{
	if (point != m_obAnchorPoint)
	{
		CCSpriteBatchNode::setAnchorPoint(point);
		updateLabel();
	}
}

// LabelBMFont - Alignment
void CCLabelBMFont::updateLabel()
{
	this->setText(m_sInitialString, false);

	if (m_fWidth != kCCLabelAutomaticWidth)
	{
		// Step 1: Make multiline
		vector<unsigned short> str_whole = cc_utf16_vec_from_utf16_str(m_sString);
		unsigned int stringLength = str_whole.size();
		vector<unsigned short> multiline_string;
		multiline_string.reserve(stringLength);
		vector<unsigned short> last_word;
		last_word.reserve(stringLength);

		unsigned int i = 0;
		bool start_line = false, start_word = false;
		float startOfLine = -1, startOfWord = -1;

		for (unsigned int j = 0; j < stringLength; j++)
		{
			int justSkipped = 0;
			CCSprite* characterSprite;
			while (!(characterSprite = _chars[j + justSkipped]) || !characterSprite->isVisible())
			{
				justSkipped++;
			}
			j += justSkipped;

			if (i >= stringLength) break;

			unsigned short character = str_whole[i];

			if (!start_word)
			{
				startOfWord = getLetterPosXLeft(characterSprite);
				start_word = true;
			}
			if (!start_line)
			{
				startOfLine = startOfWord;
				start_line = true;
			}

			// Newline.
			if (character == '\n')
			{
				cc_utf8_trim_ws(&last_word);
				for (int n = 0; n < justSkipped; n++)
				{
					last_word.push_back('\n');
				}
				multiline_string.insert(
					multiline_string.end(),
					last_word.begin(),
					last_word.end());
				last_word.clear();
				start_word = false;
				start_line = false;
				startOfWord = -1;
				startOfLine = -1;
				i += justSkipped;

				if (i >= stringLength) break;

				character = str_whole[i];
				if (!startOfWord)
				{
					startOfWord = getLetterPosXLeft(characterSprite);
					start_word = true;
				}
				if (!startOfLine)
				{
					startOfLine = startOfWord;
					start_line = true;
				}
			}

			// Whitespace.
			if (isspace_unicode(character))
			{
				last_word.push_back(character);
				multiline_string.insert(
					multiline_string.end(),
					last_word.begin(),
					last_word.end());
				last_word.clear();
				start_word = false;
				startOfWord = -1;
				i++;
				continue;
			}

			// Out of bounds.
			if (getLetterPosXRight(characterSprite) - startOfLine > m_fWidth)
			{
				if (!m_bLineBreakWithoutSpaces)
				{
					last_word.push_back(character);
					int found = cc_utf8_find_last_not_char(multiline_string, ' ');
					if (found != -1)
					{
						cc_utf8_trim_ws(&multiline_string);
					}
					else
					{
						multiline_string.clear();
					}
					if (multiline_string.size() > 0)
					{
						multiline_string.push_back('\n');
					}
					start_line = false;
					startOfLine = -1;
					i++;
				}
				else
				{
					cc_utf8_trim_ws(&last_word);

					last_word.push_back('\n');
					multiline_string.insert(
						multiline_string.end(),
						last_word.begin(),
						last_word.end());
					last_word.clear();
					start_word = false;
					start_line = false;
					startOfWord = -1;
					startOfLine = -1;

					if (i >= stringLength) break;

					if (!startOfWord)
					{
						startOfWord = getLetterPosXLeft(characterSprite);
						start_word = true;
					}
					if (!startOfLine)
					{
						startOfLine = startOfWord;
						start_line = true;
					}
					j--;
				}
			}
			else
			{
				// Character is normal.
				last_word.push_back(character);
				i++;
			}
		}

		multiline_string.insert(multiline_string.end(), last_word.begin(), last_word.end());

		int size = multiline_string.size();
		unsigned short* str_new = new unsigned short[size + 1];

		for (int i = 0; i < size; ++i)
		{
			str_new[i] = multiline_string[i];
		}

		str_new[size] = '\0';

		this->setText(str_new, false);

		CC_SAFE_DELETE_ARRAY(str_new);
	}

	// Step 2: Make alignment
	if (m_pAlignment != kCCTextAlignmentLeft)
	{
		int i = 0;

		int lineNumber = 0;
		int str_len = cc_wcslen(m_sString);
		vector<unsigned short> last_line;
		for (int ctr = 0; ctr <= str_len; ++ctr)
		{
			if (m_sString[ctr] == '\n' || m_sString[ctr] == 0)
			{
				float lineWidth = 0.0f;
				unsigned int line_length = last_line.size();
				// if last line is empty we must just increase lineNumber and work with next line
				if (line_length == 0)
				{
					lineNumber++;
					continue;
				}
				int index = i + line_length - 1 + lineNumber;
				if (index < 0) continue;

				CCSprite* lastChar = (CCSprite*)_chars[index];
				if (lastChar == NULL)
					continue;

				lineWidth = lastChar->getPosition().x + lastChar->getContentSize().width / 2.0f;

				float shift = 0;
				switch (m_pAlignment)
				{
				case kCCTextAlignmentCenter:
					shift = getContentSize().width / 2.0f - lineWidth / 2.0f;
					break;
				case kCCTextAlignmentRight:
					shift = getContentSize().width - lineWidth;
					break;
				default:
					break;
				}

				if (shift != 0)
				{
					for (unsigned j = 0; j < line_length; j++)
					{
						index = i + j + lineNumber;
						if (index < 0) continue;

						CCSprite* characterSprite = (CCSprite*)_chars[index];
						if (characterSprite)
						{
							characterSprite->setPosition(ccpAdd(characterSprite->getPosition(), ccp(shift, 0.0f)));
						}
					}
				}

				i += line_length;
				lineNumber++;

				last_line.clear();
				continue;
			}

			last_line.push_back(m_sString[ctr]);
		}
	}
}

// LabelBMFont - Alignment
void CCLabelBMFont::setAlignment(CCTextAlignment alignment)
{
	m_pAlignment = alignment;
	updateLabel();
}

CCTextAlignment CCLabelBMFont::getAlignment()
{
	return m_pAlignment;
}

void CCLabelBMFont::setTextWidth(float width)
{
	this->m_fWidth = width;
	updateLabel();
}

float CCLabelBMFont::getTextWidth()
{
	return m_fWidth;
}

void CCLabelBMFont::setLineBreakWithoutSpace(bool breakWithoutSpace)
{
	m_bLineBreakWithoutSpaces = breakWithoutSpace;
	updateLabel();
}

bool CCLabelBMFont::isLineBreakWithoutSpace()
{
	return m_bLineBreakWithoutSpaces;
}

void CCLabelBMFont::setScale(float scale)
{
	CCSpriteBatchNode::setScale(scale);
	updateLabel();
}

void CCLabelBMFont::setScaleX(float scaleX)
{
	CCSpriteBatchNode::setScaleX(scaleX);
	updateLabel();
}

void CCLabelBMFont::setScaleY(float scaleY)
{
	CCSpriteBatchNode::setScaleY(scaleY);
	updateLabel();
}

float CCLabelBMFont::getLetterPosXLeft(CCSprite* sp)
{
	return sp->getPosition().x * m_fScaleX - (sp->getContentSize().width * m_fScaleX * sp->getAnchorPoint().x);
}

float CCLabelBMFont::getLetterPosXRight(CCSprite* sp)
{
	return sp->getPosition().x * m_fScaleX + (sp->getContentSize().width * m_fScaleX * sp->getAnchorPoint().x);
}

// LabelBMFont - FntFile
void CCLabelBMFont::setFntFile(const char* fntFile)
{
	if (fntFile != NULL && strcmp(fntFile, m_sFntFile.c_str()) != 0)
	{
		CCBMFontConfiguration *newConf = FNTConfigLoadFile(fntFile);

		CCAssert(newConf, "CCLabelBMFont: Impossible to create font. Please check file");

		m_sFntFile = fntFile;

		CC_SAFE_RETAIN(newConf);
		CC_SAFE_RELEASE(m_pConfiguration);
		m_pConfiguration = newConf;

		this->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_pConfiguration->getAtlasName()));
		this->createFontChars();
	}
}

const char* CCLabelBMFont::getFntFile()
{
	return m_sFntFile.c_str();
}


//LabelBMFont - Debug draw
#if CC_LABELBMFONT_DEBUG_DRAW
void CCLabelBMFont::draw()
{
	CCSpriteBatchNode::draw();
	const CCSize& s = this->getContentSize();
	CCPoint vertices[4] = {
		ccp(0,0),ccp(s.width,0),
		ccp(s.width,s.height),ccp(0,s.height),
	};
	ccDrawPoly(vertices, 4, true);
}

#endif // CC_LABELBMFONT_DEBUG_DRAW

NS_CC_END
