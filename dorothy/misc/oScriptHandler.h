/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_MISC_OSCRIPTHANDLER_H__
#define __DOROTHY_MISC_OSCRIPTHANDLER_H__

NS_DOROTHY_BEGIN


class oScriptHandler: public CCObject
{
public:
	virtual ~oScriptHandler();
	static oScriptHandler* create(int handler);
	void set(int handler);
	int get() const;
private:
	oScriptHandler(int handler);
	int _handler;
};

class oHandlerWrapper
{
public:
	oHandlerWrapper(int handler);
	bool operator==(const oHandlerWrapper& handler) const;
	int getHandler() const;
private:
	oRef<oScriptHandler> _handler;
};
#define HANDLER_WRAP_START(type) class type: public oHandlerWrapper\
{\
public:\
	type(int handler):oHandlerWrapper(handler){}\
	const type& operator*() const {return *this;}

#define HANDLER_WRAP_END };

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OSCRIPTHANDLER_H__