/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_PLATFORM_OCAMERA_H__
#define __DOROTHY_PLATFORM_OCAMERA_H__

NS_DOROTHY_PLATFORM_BEGIN

typedef Delegate<void (float deltaX, float deltaY)> oCameraHandler;

class oCamera: public CCNode
{
public:
	oCamera();
	PROPERTY_REF(CCRect, _boundary, Boundary);
	PROPERTY_REF(oVec2, _ratio, FollowRatio);
	virtual bool init();
	virtual void setScaleX(float scaleX);
	virtual void setScaleY(float scaleY);
	virtual void setPosition(const CCPoint& var);
	virtual const CCPoint& getPosition();
	void follow(CCNode* target);
	virtual CCAffineTransform nodeToParentTransform();
	virtual CCAffineTransform nodeToGameParentTransform();
	oCameraHandler moved;
	CREATE_FUNC(oCamera);
private:
	CCPoint _camPos;
	oWRef<CCNode> _target;
	CC_LUA_TYPE(oCamera)
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OCAMERA_H__