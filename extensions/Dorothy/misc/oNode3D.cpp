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
	if (!m_obAnchorPointInPoints.equals(CCPointZero))
	{
		kmGLTranslatef(m_obAnchorPointInPoints.x, m_obAnchorPointInPoints.y, 0);
	}
}

NS_DOROTHY_END
