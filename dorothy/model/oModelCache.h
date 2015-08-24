/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_MODEL_OMODELCACHE__
#define __DOROTHY_MODEL_OMODELCACHE__

#include "misc/oXmlItemCache.h"

NS_DOROTHY_BEGIN

class oSpriteDef;
class oModelAnimationDef;
class oKeyAnimationDef;
class oModelDef;
class oModel;

class oModelCache: public oXmlItemCache<oModelDef>
{
public:
	SHARED_FUNC(oModelCache);
protected:
	oModelCache(){}
	virtual void beforeParse( const char* filename );
	virtual void afterParse( const char* filename );
	virtual void textHandler( void *ctx, const char *s, int len );
	virtual void startElement( void *ctx, const char *name, const char **atts );
	virtual void endElement( void *ctx, const char *name );
	const static int MAX_LOOKS;
private:
	oKeyAnimationDef* getCurrentKeyAnimation();
	stack<oSpriteDef*> _nodeStack;
	oModelAnimationDef* _currentAnimationDef;
};

#define oSharedModelCache (*oModelCache::shared())

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OMODELCACHE__