/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_MISC_OHELPER_H__
#define __DOROTHY_MISC_OHELPER_H__

NS_DOROTHY_BEGIN

struct oString
{
	static const string Empty;
	static string getFilePath(const string& filename);
	static string getFileName(const string& filename);
};

struct oHelper
{
	static void getPosFromStr(const char* str, float& x, float& y);
	static char* convert(float value, int precision, char* buf, int len);
};

struct oFileExt
{
	static const string Clip;
	static const string Model;
	static const string Texture;
	static const string Particle;
	static const string Frame;
	static const string Effect;
	static bool check(const string& filename, const string& ext);
};

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OHELPER_H__