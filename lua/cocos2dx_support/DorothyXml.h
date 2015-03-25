#ifndef __DOROTHY_XML_H__
#define __DOROTHY_XML_H__

#include "Dorothy.h"
using namespace Dorothy;
using namespace Dorothy::Platform;

class oXmlDelegate;

class oXmlLoader
{
public:
	SHARED_FUNC(oXmlLoader);
public:
	oXmlLoader();
	~oXmlLoader();
	string load(const char* filename);
private:
	oOwn<oXmlDelegate> _delegate;
	CCSAXParser _parser;
};

#define oSharedXMLLoader (*oXmlLoader::shared())

#endif //__DOROTHY_XML_H__