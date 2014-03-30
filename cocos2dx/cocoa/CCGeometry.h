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

#ifndef __CCGEMETRY_H__
#define __CCGEMETRY_H__

#include "platform/CCPlatformMacros.h"
#include "CCObject.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

class CC_DLL CCPoint
{
public:
    float x;
    float y;

public:
    CCPoint();
    CCPoint(float x, float y);
    CCPoint(const CCPoint& other);
    CCPoint& operator=(const CCPoint& other);
	void set(float x, float y);
	bool operator==(const CCPoint& other) const;
	bool operator!=(const CCPoint& other) const;
	static const CCPoint zero;
};

class CC_DLL CCSize
{
public:
    float width;
    float height;

public:
    CCSize();
    CCSize(float width, float height);
    CCSize(const CCSize& other);
	CCSize& operator=(const CCSize& other);
	bool operator==(const CCSize& other) const;
	bool operator!=(const CCSize& other) const;
    void set(float width, float height);
	static const CCSize zero;
};

class CC_DLL CCRect
{
public:
    CCPoint origin;
    CCSize  size;

public:
    CCRect();
	CCRect(const CCPoint& origin, const CCSize& size);
    CCRect(float x, float y, float width, float height);
    CCRect(const CCRect& other);
	CCRect& operator=(const CCRect& other);
	bool operator==(const CCRect& other) const;
	bool operator!=(const CCRect& other) const;
    void set(float x, float y, float width, float height);
    float getMinX() const; /// return the leftmost x-value of current rect
    float getMidX() const; /// return the midpoint x-value of current rect
    float getMaxX() const; /// return the rightmost x-value of current rect
    float getMinY() const; /// return the bottommost y-value of current rect
    float getMidY() const; /// return the midpoint y-value of current rect
    float getMaxY() const; /// return the topmost y-value of current rect
    bool containsPoint(const CCPoint& point) const;
	bool intersectsRect(const CCRect& rect) const;
	static const CCRect zero;
};

#define CCPointMake(x, y) CCPoint((float)(x), (float)(y))
#define CCSizeMake(width, height) CCSize((float)(width), (float)(height))
#define CCRectMake(x, y, width, height) CCRect((float)(x), (float)(y), (float)(width), (float)(height))

// end of data_structure group
/// @}

NS_CC_END

#endif // __CCGEMETRY_H__
