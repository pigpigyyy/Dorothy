/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "support/TransformUtils.h"
#include "misc/oNode3D.h"

#if CC_NODE_RENDER_SUBPIXEL
	#define RENDER_IN_SUBPIXEL
#else
	#define RENDER_IN_SUBPIXEL (__ARGS__) (ceil(__ARGS__))
#endif

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

void oNode3D::transform()
{
	kmMat4 transfrom4x4;

	float x = m_obPosition.x;
	float y = m_obPosition.y;
	float c = 1, s = 0;
	if (m_fRotation)
	{
		float radians = -CC_DEGREES_TO_RADIANS(m_fRotation);
		c = cosf(radians);
		s = sinf(radians);
	}
	bool needsSkewMatrix = (m_fSkewX || m_fSkewY);

	if (!needsSkewMatrix && m_obAnchorPointInPoints != CCPoint::zero)
	{
		x += c * -m_obAnchorPointInPoints.x * m_fScaleX + -s * -m_obAnchorPointInPoints.y * m_fScaleY;
		y += s * -m_obAnchorPointInPoints.x * m_fScaleX + c * -m_obAnchorPointInPoints.y * m_fScaleY;
	}
	m_sTransform = CCAffineTransformMake(c * m_fScaleX, s * m_fScaleX,
		-s * m_fScaleY, c * m_fScaleY,
		x, y);
	
	CGAffineToGL(&m_sTransform, transfrom4x4.mat);
	transfrom4x4.mat[14] = m_fPositionZ;

	if (!needsSkewMatrix && m_obAnchorPointInPoints != CCPoint::zero)
	{
		kmMat4 translate;
		kmMat4Translation(&translate, m_obAnchorPointInPoints.x, m_obAnchorPointInPoints.y, 0);
		kmMat4Multiply(&transfrom4x4, &transfrom4x4, &translate);
	}

	if (_rotationX)
	{
		kmMat4 rot;
		kmMat4RotationX(&rot, CC_DEGREES_TO_RADIANS(_rotationX));
		kmMat4Multiply(&transfrom4x4, &transfrom4x4, &rot);
	}
	if (_rotationY)
	{
		kmMat4 rot;
		kmMat4RotationY(&rot, CC_DEGREES_TO_RADIANS(_rotationY));
		kmMat4Multiply(&transfrom4x4, &transfrom4x4, &rot);
	}

	if (!needsSkewMatrix && m_obAnchorPointInPoints != CCPoint::zero)
	{
		kmMat4 translate;
		kmMat4Translation(&translate, -m_obAnchorPointInPoints.x, -m_obAnchorPointInPoints.y, 0);
		kmMat4Multiply(&transfrom4x4, &transfrom4x4, &translate);
	}

	if (needsSkewMatrix)
	{
		CCAffineTransform skewMatrix = CCAffineTransformMake(1.0f, tanf(CC_DEGREES_TO_RADIANS(m_fSkewY)),
			tanf(CC_DEGREES_TO_RADIANS(m_fSkewX)), 1.0f,
			0.0f, 0.0f);
		m_sTransform = CCAffineTransformConcat(skewMatrix, m_sTransform);

		kmMat4 skewTransfrom4x4;
		CGAffineToGL(&skewMatrix, skewTransfrom4x4.mat);
		kmMat4Multiply(&transfrom4x4, &transfrom4x4, &skewTransfrom4x4);

		if (m_obAnchorPointInPoints != CCPoint::zero)
		{
			m_sTransform = CCAffineTransformTranslate(m_sTransform, -m_obAnchorPointInPoints.x, -m_obAnchorPointInPoints.y);
			kmMat4 translate;
			kmMat4Translation(&translate, -m_obAnchorPointInPoints.x, -m_obAnchorPointInPoints.y, 0);
			kmMat4Multiply(&transfrom4x4, &transfrom4x4, &translate);
		}
	}

	kmGLMultMatrix(&transfrom4x4);

	// XXX: Expensive calls. Camera should be integrated into the cached affine matrix
	if (m_pCamera != NULL && !(m_pGrid != NULL && m_pGrid->isActive()))
	{
		bool translate = (m_obAnchorPointInPoints.x != 0.0f || m_obAnchorPointInPoints.y != 0.0f);

		if (translate)
		{
			kmGLTranslatef(RENDER_IN_SUBPIXEL(m_obAnchorPointInPoints.x), RENDER_IN_SUBPIXEL(m_obAnchorPointInPoints.y), 0);
		}
		m_pCamera->locate();
		if (translate)
		{
			kmGLTranslatef(RENDER_IN_SUBPIXEL(-m_obAnchorPointInPoints.x), RENDER_IN_SUBPIXEL(-m_obAnchorPointInPoints.y), 0);
		}
	}
}

NS_DOROTHY_END
