/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/misc/oVec2.h"

NS_DOROTHY_BEGIN

oMemoryPool<oVec2> oVec2::_memory;

const oVec2 oVec2::zero;

oVec2::oVec2(float x, float y):
x(x),
y(y)
{ }
oVec2::oVec2(const oVec2& vec):
x(vec.x),
y(vec.y)
{ }
oVec2::oVec2(const b2Vec2& v):
x(v.x),
y(v.y)
{ }
oVec2::oVec2(const CCPoint& p):
x(p.x),
y(p.y)
{ }
void oVec2::set(float x, float y)
{
	x = x;
	y = y;
}
oVec2 oVec2::operator+(const oVec2& vec) const
{
	return oVec2(x + vec.x, y + vec.y);
}
oVec2 oVec2::operator-(const oVec2& vec) const
{
	return oVec2(x - vec.x, y - vec.y);
}
oVec2 oVec2::operator*(float value) const
{
	return oVec2(x * value, y * value);
}
oVec2 oVec2::operator*(const oVec2& vec) const
{
	return oVec2(x * vec.x, y * vec.y);
}
oVec2 oVec2::operator/(float value) const
{
	return oVec2(x / value, y / value);
}
bool oVec2::operator==(const oVec2& vec) const
{
	return x == vec.x && y == vec.y;
}
bool oVec2::operator!=(const oVec2& vec) const
{
	return x != vec.x || y != vec.y;
}
float oVec2::distance(const oVec2& vec) const
{
	float dx = x - vec.x;
	float dy = y - vec.y;
	return sqrtf(dx * dx + dy * dy);
}
float oVec2::distanceSquared(const oVec2& vec) const
{
	float dx = x - vec.x;
	float dy = y - vec.y;
	return dx * dx + dy * dy;
}
float oVec2::length() const
{
	return sqrtf(x * x + y * y);
}
float oVec2::lengthSquared() const
{
	return x * x + y * y;
}
void oVec2::normalize()
{
	float length = oVec2::length();
	x /= length;
	y /= length;
}
float oVec2::angle() const
{
	return atan2f(y, x);
}

NS_DOROTHY_END
