#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oCamera.h"

NS_DOROTHY_PLATFORM_BEGIN

oCamera::oCamera():
_ratio(1.0f, 1.0f),
_view(CCDirector::sharedDirector()->getWinSize())
{ }

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
		_camPos = var;
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