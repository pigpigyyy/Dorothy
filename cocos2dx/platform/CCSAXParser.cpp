/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org  http://cocos2d-x.org
 Copyright (c) 2010 Максим Аксенов
 Copyright (c) 2013 Martell Malone
 
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

#include "CCSAXParser.h"
#include "cocoa/CCDictionary.h"
#include "CCFileUtils.h"
#include "support/tinyxml2/tinyxml2.h"

#include <vector> // because its based on windows 8 build :P

NS_CC_BEGIN

class XmlSaxHander : public tinyxml2::XMLVisitor
{
public:
	XmlSaxHander():m_ccsaxParserImp(0){};
	
	virtual bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute );
	virtual bool VisitExit( const tinyxml2::XMLElement& element );
	virtual bool Visit( const tinyxml2::XMLText& text );
	virtual bool Visit( const tinyxml2::XMLUnknown&){ return true; }

	void setCCSAXParserImp(CCSAXParser* parser)
	{
		m_ccsaxParserImp = parser;
	}

private:
	CCSAXParser *m_ccsaxParserImp;
};


bool XmlSaxHander::VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute )
{
	std::vector<const char*> attsVector;
	for( const tinyxml2::XMLAttribute* attrib = firstAttribute; attrib; attrib = attrib->Next() )
	{
		attsVector.push_back(attrib->Name());
		attsVector.push_back(attrib->Value());
	}
    attsVector.push_back(NULL);

	CCSAXParser::startElement(m_ccsaxParserImp, (const CC_XML_CHAR *)element.Value(), (const CC_XML_CHAR **)(&attsVector[0]));
	return true;
}
bool XmlSaxHander::VisitExit( const tinyxml2::XMLElement& element )
{
	CCSAXParser::endElement(m_ccsaxParserImp, (const CC_XML_CHAR *)element.Value());
	return true;
}

bool XmlSaxHander::Visit( const tinyxml2::XMLText& text )
{
	CCSAXParser::textHandler(m_ccsaxParserImp, (const CC_XML_CHAR *)text.Value(), (int)strlen(text.Value()));
	return true;
}

CCSAXParser::CCSAXParser():
m_pDelegator(NULL)
{ }

CCSAXParser::~CCSAXParser()
{ }

bool CCSAXParser::init(const char *pszEncoding)
{
    CC_UNUSED_PARAM(pszEncoding);
    // nothing to do
    return true;
}

const std::string& CCSAXParser::getLastError() const
{
	return _lastError;
}

bool CCSAXParser::parse(const char* pXMLData, unsigned int uDataLength)
{
	_lastError.clear();
	tinyxml2::XMLDocument tinyDoc;
	tinyxml2::XMLError error;
	if (uDataLength == 0)
	{
		 error = tinyDoc.Parse(pXMLData);
	}
	else
	{
		error = tinyDoc.Parse(pXMLData,uDataLength);
	}
	if (error != tinyxml2::XML_NO_ERROR)
	{
		_lastError = "XMLDocument error at: ";
		if (tinyDoc.GetErrorStr1())
		{
			_lastError += tinyDoc.GetErrorStr1();
		}
		if (tinyDoc.GetErrorStr2())
		{
			if (!_lastError.empty()) _lastError += '\n';
			_lastError += tinyDoc.GetErrorStr2();
		}
		return false;
	}
	XmlSaxHander printer;
	printer.setCCSAXParserImp(this);

	if (!tinyDoc.Accept(&printer))
	{
		_lastError = "XMLDocument error at: ";
		if (tinyDoc.GetErrorStr1())
		{
			_lastError += tinyDoc.GetErrorStr1();
		}
		if (tinyDoc.GetErrorStr2())
		{
			if (!_lastError.empty()) _lastError += '\n';
			_lastError += tinyDoc.GetErrorStr2();
		}
		return false;
	}
	return true;
}

bool CCSAXParser::parse(const char *pszFile)
{
    bool bRet = false;
    unsigned long size = 0;
    char* pBuffer = (char*)CCFileUtils::sharedFileUtils()->getFileData(pszFile, "rt", &size);
    if (pBuffer != NULL && size > 0)
    {
        bRet = parse(pBuffer, (unsigned int)size);
    }
    CC_SAFE_DELETE_ARRAY(pBuffer);
    return bRet;
}

void CCSAXParser::startElement(void *ctx, const CC_XML_CHAR *name, const CC_XML_CHAR **atts)
{
    ((CCSAXParser*)(ctx))->m_pDelegator->startElement(ctx, (char*)name, (const char**)atts);
}

void CCSAXParser::endElement(void *ctx, const CC_XML_CHAR *name)
{
    ((CCSAXParser*)(ctx))->m_pDelegator->endElement(ctx, (char*)name);
}

void CCSAXParser::textHandler(void *ctx, const CC_XML_CHAR *name, int len)
{
    ((CCSAXParser*)(ctx))->m_pDelegator->textHandler(ctx, (char*)name, len);
}

void CCSAXParser::setDelegator(CCSAXDelegator* pDelegator)
{
    m_pDelegator = pDelegator;
}

void CCSAXParser::placeCDataHeader(const char* cdataHeader)
{
	tinyxml2::XMLUtil::PlaceCDataHeader(cdataHeader);
}

void CCSAXParser::setHeaderHandler(void(*handler)(const char* start, const char* end))
{
	tinyxml2::XMLUtil::PlaceHeaderHandler(handler);
}

NS_CC_END
