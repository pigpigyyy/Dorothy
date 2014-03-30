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

#include "CCGeometry.h"
#include "ccMacros.h"

// implementation of CCPoint
NS_CC_BEGIN

const CCPoint CCPoint::zero;

CCPoint::CCPoint():
x(0.0f),
y(0.0f)
{ }

CCPoint::CCPoint(float x, float y):
x(x),
y(y)
{ }

CCPoint::CCPoint(const CCPoint& other):
x(other.x),
y(other.y)
{ }

CCPoint& CCPoint::operator=(const CCPoint& other)
{
    set(other.x, other.y);
    return *this;
}

void CCPoint::set(float x, float y)
{
    this->x = x;
    this->y = y;
}

bool CCPoint::operator==(const CCPoint& other) const
{
	return x == other.x && y == other.y;
}

bool CCPoint::operator!=(const CCPoint& other) const
{
	return x != other.x || y != other.y;
}

// implementation of CCSize
const CCSize CCSize::zero;

CCSize::CCSize()
: width(0.0f)
, height(0.0f)
{ }

CCSize::CCSize(float width, float height)
: width(width)
, height(height)
{ }

CCSize::CCSize(const CCSize& other)
: width(other.width)
, height(other.height)
{ }

CCSize& CCSize::operator=(const CCSize& other)
{
    set(other.width, other.height);
    return *this;
}

void CCSize::set(float width, float height)
{
    this->width = width;
    this->height = height;
}

bool CCSize::operator==(const CCSize& target) const
{
    return width == target.width && height == target.height;
}

bool CCSize::operator!=(const CCSize& target) const
{
	return width != target.width || height != target.height;
}

// implementation of CCRect
const CCRect CCRect::zero;

CCRect::CCRect()
{ }

CCRect::CCRect(const CCPoint& origin, const CCSize& size):
origin(origin),
size(size)
{ }

CCRect::CCRect(float x, float y, float width, float height):
origin(x,y),
size(width,height)
{ }

CCRect::CCRect(const CCRect& other):
origin(other.origin),
size(other.size)
{ }

CCRect& CCRect::operator=(const CCRect& other)
{
    set(other.origin.x, other.origin.y, other.size.width, other.size.height);
    return *this;
}

void CCRect::set(float x, float y, float width, float height)
{
    // CGRect can support width<0 or height<0
    // CCAssert(width >= 0.0f && height >= 0.0f, "width and height of Rect must not less than 0.");

    origin.x = x;
    origin.y = y;

    size.width = width;
    size.height = height;
}

bool CCRect::operator==(const CCRect& rect) const
{
    return origin == rect.origin && size == rect.size;
}

bool CCRect::operator!=(const CCRect& rect) const
{
	return origin != rect.origin || size != rect.size;
}

float CCRect::getMaxX() const
{
    return (float)(origin.x + size.width);
}

float CCRect::getMidX() const
{
    return (float)(origin.x + size.width * 0.5f);
}

float CCRect::getMinX() const
{
    return origin.x;
}

float CCRect::getMaxY() const
{
    return origin.y + size.height;
}

float CCRect::getMidY() const
{
    return (float)(origin.y + size.height * 0.5f);
}

float CCRect::getMinY() const
{
    return origin.y;
}

bool CCRect::containsPoint(const CCPoint& point) const
{
    bool bRet = false;

    if (point.x >= getMinX() && point.x <= getMaxX()
        && point.y >= getMinY() && point.y <= getMaxY())
    {
        bRet = true;
    }

    return bRet;
}

bool CCRect::intersectsRect(const CCRect& rect) const
{
    return !(     getMaxX() < rect.getMinX() ||
             rect.getMaxX() <      getMinX() ||
                  getMaxY() < rect.getMinY() ||
             rect.getMaxY() <      getMinY());
}

NS_CC_END
