/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_MISC_OVEC2_H__
#define __DOROTHY_MISC_OVEC2_H__

#include "Dorothy/misc/oMemoryPool.h"

NS_DOROTHY_BEGIN

class oVec2
{
public:
	oVec2(float x = 0.0f, float y = 0.0f);
	oVec2(const oVec2& vec);
	oVec2(const b2Vec2& v);
	oVec2(const CCPoint& p);
	inline operator b2Vec2() const { return *((b2Vec2*)this); }
	inline operator CCPoint() const { return *((CCPoint*)this); }
	void set(float x, float y);
	oVec2 operator+(const oVec2& vec) const;
	oVec2 operator-(const oVec2& vec) const;
	oVec2 operator*(float value) const;
	oVec2 operator*(const oVec2& vec) const;
	oVec2 operator/(float value) const;
	bool operator==(const oVec2& vec) const;
	bool operator!=(const oVec2& vec) const;
	float distance(const oVec2& vec) const;
	float distanceSquared(const oVec2& vec) const;
	float length() const;
	float lengthSquared() const;
	float angle() const;
	void normalize();
	float x;
	float y;
	static const oVec2 zero;
	USE_MEMORY_POOL(oVec2)
};

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OVEC2_H__