/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/misc/oNode3D.h"

NS_DOROTHY_BEGIN

oNode3D::oNode3D()
: _rotationX(0.0f)
, _rotationY(0.0f)
{ }

void oNode3D::setRotationX(float var)
{
	_rotationX = var;
	m_bTransformDirty = m_bInverseDirty = true;
}

void oNode3D::setRotationY(float var)
{
	_rotationY = var;
	m_bTransformDirty = m_bInverseDirty = true;
}

float oNode3D::getRotationX() const
{
	return _rotationX;
}

float oNode3D::getRotationY() const
{
	return _rotationY;
}

CCAffineTransform oNode3D::nodeToParentTransform()
{
	if (m_bTransformDirty) 
	{
		float x = m_obPosition.x;
		float y = m_obPosition.y;
		float c = 1, s = 0;
		if (m_fRotation)
		{
			float radians = -CC_DEGREES_TO_RADIANS(m_fRotation);
			c = cosf(radians);
			s = sinf(radians);
		}
		m_sTransform = CCAffineTransformMake(
			c * m_fScaleX,  s * m_fScaleX,
			-s * m_fScaleY, c * m_fScaleY,
			x, y);
		if (m_fSkewX || m_fSkewY)
		{
			CCAffineTransform skewMatrix = CCAffineTransformMake(
				1.0f, tanf(CC_DEGREES_TO_RADIANS(m_fSkewY)),
				tanf(CC_DEGREES_TO_RADIANS(m_fSkewX)), 1.0f,
				0.0f, 0.0f );
			m_sTransform = CCAffineTransformConcat(skewMatrix, m_sTransform);
		}
		m_bTransformDirty = false;
	}
	return m_sTransform;
}

void oNode3D::transform()
{
	CCNode::transform();
	if (_rotationX)
	{
		kmGLRotatef(_rotationX, 1, 0, 0);
	}
	if (_rotationY)
	{
		kmGLRotatef(_rotationY, 0, 1, 0);
	}
	if (m_obAnchorPointInPoints != CCPoint::zero)
	{
		kmGLTranslatef(m_obAnchorPointInPoints.x, m_obAnchorPointInPoints.y, 0);
	}
}

NS_DOROTHY_END
