/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "platform/oPlatformDefine.h"
#include "platform/oCamera.h"

NS_DOROTHY_PLATFORM_BEGIN

oCamera::oCamera():
_ratio(1.0f, 1.0f)
{ }

bool oCamera::init()
{
	if (!CCNode::init()) return false;
	CCNode::setContentSize(CCDirector::sharedDirector()->getWinSize());
	_camPos = ccp(CCNode::getWidth()*0.5f, CCNode::getHeight()*0.5f);
	CCNode::setPosition(_camPos);
	return true;
}

void oCamera::setBoundary(const CCRect& var)
{
	_boundary = var;
}

const CCRect& oCamera::getBoundary() const
{
	return _boundary;
}

void oCamera::setFollowRatio(const oVec2& var)
{
	_ratio = var;
}

const oVec2& oCamera::getFollowRatio() const
{
	return _ratio;
}

void oCamera::follow( CCNode* target )
{
	_target = target;
}

void oCamera::setScaleX(float scaleX)
{
	CCNode::setScaleX(scaleX);
	setPosition(getPosition());
}

void oCamera::setScaleY(float scaleY)
{
	CCNode::setScaleY(scaleY);
	setPosition(getPosition());
}

void oCamera::setPosition(const CCPoint& var)
{
	CCPoint pos = var;
	if (_boundary.size.width > 0 &&
		_boundary.size.height > 0)
	{
		float halfW = CCNode::getWidth() * 0.5f / getScaleX();
		float halfH = CCNode::getHeight() * 0.5f / getScaleY();
		oVec2 from(_boundary.getX() + halfW, _boundary.getY() + halfH);
		oVec2 to(
			_boundary.getX() + _boundary.getWidth() - halfW,
			_boundary.getY() + _boundary.getHeight() - halfH);
		pos = ccpClamp(var, from, to);
		if (from.x > to.x)
		{
			pos.x = (_boundary.getLeft() + _boundary.getRight()) * 0.5f;
		}
		if (from.y > to.y)
		{
			pos.y = (_boundary.getBottom() + _boundary.getTop()) * 0.5f;
		}
	}
	float deltaX = pos.x - _camPos.x;
	float deltaY = pos.y - _camPos.y;
	_camPos = pos;
	const CCPoint& anchor = CCNode::getAnchorPoint();
	CCNode::setAnchorPoint(ccp(anchor.x + deltaX / CCNode::getWidth(), anchor.y + deltaY / CCNode::getHeight()));
	if (moved)
	{
		moved(deltaX, deltaY);
	}
}

const CCPoint& oCamera::getPosition()
{
	return _camPos;
}

CCAffineTransform oCamera::nodeToParentTransform()
{
	if (_target)
	{
		const CCPoint& pos = oCamera::getPosition();
		CCPoint delta = ccpSub(_target->getPosition(), pos);
		delta.x = delta.x * _ratio.x;
		delta.y = delta.y * _ratio.y;
		oCamera::setPosition(ccpAdd(pos, delta));
	}
	return CCNode::nodeToParentTransform();
}

CCAffineTransform oCamera::nodeToGameParentTransform()
{
	return CCAffineTransformIdentity;
}

NS_DOROTHY_PLATFORM_END