/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "platform/oPlatformDefine.h"
#include "platform/oCamera.h"

NS_DOROTHY_PLATFORM_BEGIN

oCamera::oCamera():
_ratio(1.0f, 1.0f),
_view(CCDirector::sharedDirector()->getWinSize())
{ }

bool oCamera::init()
{
	if (!CCNode::init()) return false;
	CCNode::setContentSize(CCDirector::sharedDirector()->getWinSize());
	return true;
}

void oCamera::setBoudary(const CCRect& var)
{
	_boudary = var;
}

const CCRect& oCamera::getBoudary() const
{
	return _boudary;
}

void oCamera::setView(const CCSize& var)
{
	_view = var;
}

const CCSize& oCamera::getView() const
{
	return _view;
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

void oCamera::setPosition(const CCPoint& var)
{
	if (_camPos != var)
	{
		CCPoint pos(
			-var.x + _view.width * 0.5f,
			-var.y + _view.height * 0.5f);
		CCPoint to(-_boudary.origin.x, -_boudary.origin.y);
		CCPoint from(
			_view.width - _boudary.origin.x - _boudary.size.width,
			_view.height - _boudary.size.height);
		pos = ccpClamp(pos, from, to);
		const CCPoint& lastPos = CCNode::getPosition();
		float deltaX = (pos.x - lastPos.x) * _ratio.x;
		float deltaY = (pos.y - lastPos.y) * _ratio.y;
		_camPos.x += deltaX;
		_camPos.x += deltaY;
		if (moved)
		{
			moved(deltaX, deltaY);
		}
		CCNode::setPosition(ccp(lastPos.x+deltaX, lastPos.y+deltaY));
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
		oCamera::setPosition(_target->getPosition());
	}
	return CCNode::nodeToParentTransform();
}

CCAffineTransform oCamera::nodeToGameParentTransform()
{
	return CCAffineTransformIdentity;
}

NS_DOROTHY_PLATFORM_END