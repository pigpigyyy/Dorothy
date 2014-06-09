/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/misc/oHelper.h"

NS_DOROTHY_BEGIN

const string oString::Empty;

void oHelper::getPosFromStr( const char* str, float& x, float& y )
{
	char temp[64];
	strcpy(temp, str);
	char* token = strtok(temp, ",");
	x = (float)atof(token);
	token = strtok(nullptr, ",");
	y = (float)atof(token);
}

string oString::getFilePath(const string& filename)
{
	size_t pos = filename.find_last_of("/\\");
	if (pos == string::npos)
	{
		return oString::Empty;
	}
	return filename.substr(0, pos) + "/";
}
string oString::getFileName(const string& filename)
{
	size_t pos = filename.find_last_of("/\\");
	if (pos == string::npos)
	{
		return oString::Empty;
	}
	return filename.substr(pos+1);
}
char* oHelper::convert(float value, int precision, char* buf, int buflen)
{
	snprintf(buf, buflen, "%f", value);
	int len = strlen(buf);
	char* pos = buf + len;
	pos -= (6 - precision);
	*pos = '\0';
	pos--;
	while (*pos == '0') *pos-- = '\0';
	if (*pos == '.') *pos = '\0';
	return buf;
}

const string oFileExt::Clip = ".clip";
const string oFileExt::Model = ".model";
const string oFileExt::Texture = ".png";
const string oFileExt::Particle = ".plist";
const string oFileExt::Frame = ".frame";
const string oFileExt::Effect = ".effect";

bool oFileExt::check( const string& filename, const string& ext )
{
	return filename.find(ext.c_str(), filename.size() - ext.length(), ext.length()) != string::npos;
}

NS_DOROTHY_END
