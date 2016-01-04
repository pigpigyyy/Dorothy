/*
 * Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
 *
 * iPhone port by Simon Oliver - http://www.simonoliver.com - http://www.handcircus.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "const/oDefine.h"
#include "DebugDraw.h"
#include "cocos2d.h"
USING_NS_CC;
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "physics/oBody.h"
using namespace Dorothy;

GLESDebugDraw::GLESDebugDraw() :
ratio(1.0f)
{
	this->initShader();
	this->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
}

void GLESDebugDraw::initShader(void)
{
	_shaderProgram = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_Position_uColor);
	_colorLocation = glGetUniformLocation(_shaderProgram->getProgram(), "u_color");
}

void GLESDebugDraw::Begin()
{
	ccGLBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
	_shaderProgram->use();
	_shaderProgram->setUniformsForBuiltins();
}

bool GLESDebugDraw::IsVisible(b2Fixture* fixture)
{
	return IsVisible(fixture->GetBody());
}

bool GLESDebugDraw::IsVisible(b2Body* bodyB2)
{
	oBody* body = (oBody*)bodyB2->GetUserData();
	CCNode* owner = (CCNode*)body->getOwner();
	return body->isVisible() && (owner == nullptr || (owner->isVisible() && (owner->getParent() == nullptr || owner->getParent()->isVisible())));
}

void GLESDebugDraw::DrawPolygon(const b2Vec2* old_vertices, int vertexCount, const b2Color& color)
{
	b2Vec2 vertices[b2_maxPolygonVertices];
	for (int i = 0; i < vertexCount; i++)
	{
		vertices[i] = old_vertices[i];
		vertices[i] *= ratio;
	}

	_shaderProgram->setUniformLocationWith4f(_colorLocation, color.r, color.g, color.b, 1);

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

	CC_INCREMENT_GL_DRAWS(1);

	CHECK_GL_ERROR_DEBUG();
}

void GLESDebugDraw::DrawSolidPolygon(const b2Vec2* old_vertices, int vertexCount, const b2Color& color)
{
	b2Vec2 vertices[b2_maxPolygonVertices];
	for (int i = 0; i < vertexCount; i++)
	{
		vertices[i] = old_vertices[i];
		vertices[i] *= ratio;
	}

	_shaderProgram->setUniformLocationWith4f(_colorLocation, color.r*0.5f, color.g*0.5f, color.b*0.5f, 0.5f);

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);

	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

	_shaderProgram->setUniformLocationWith4f(_colorLocation, color.r, color.g, color.b, 1);
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

	CC_INCREMENT_GL_DRAWS(2);

	CHECK_GL_ERROR_DEBUG();
}

void GLESDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	const float32 k_segments = 16.0f;
	const int vertexCount = 16;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;

	GLfloat glVertices[vertexCount * 2];
	for (int i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertices[i * 2] = v.x * ratio;
		glVertices[i * 2 + 1] = v.y * ratio;
		theta += k_increment;
	}

	_shaderProgram->setUniformLocationWith4f(_colorLocation, color.r, color.g, color.b, 1);
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, glVertices);

	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

	CC_INCREMENT_GL_DRAWS(1);

	CHECK_GL_ERROR_DEBUG();
}

void GLESDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	const float32 k_segments = 16.0f;
	const int vertexCount = 16;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;

	GLfloat glVertices[vertexCount * 2];
	for (int i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertices[i * 2] = v.x * ratio;
		glVertices[i * 2 + 1] = v.y * ratio;
		theta += k_increment;
	}

	_shaderProgram->setUniformLocationWith4f(_colorLocation, color.r*0.5f, color.g*0.5f, color.b*0.5f, 0.5f);
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

	_shaderProgram->setUniformLocationWith4f(_colorLocation, color.r, color.g, color.b, 1);
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

	// Draw the axis line
	DrawSegment(center, center + radius*axis, color);

	CC_INCREMENT_GL_DRAWS(2);

	CHECK_GL_ERROR_DEBUG();
}

void GLESDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	_shaderProgram->setUniformLocationWith4f(_colorLocation, color.r, color.g, color.b, 1);

	GLfloat glVertices[] =
	{
		p1.x * ratio, p1.y * ratio,
		p2.x * ratio, p2.y * ratio
	};
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, glVertices);

	glDrawArrays(GL_LINES, 0, 2);

	CC_INCREMENT_GL_DRAWS(1);

	CHECK_GL_ERROR_DEBUG();
}

void GLESDebugDraw::DrawTransform(const b2Transform& xf)
{
	b2Vec2 p1 = xf.p, p2;
	const float32 k_axisScale = 0.4f;
	p2 = p1 + k_axisScale * xf.q.GetXAxis();
	DrawSegment(p1, p2, b2Color(1, 0, 0));

	p2 = p1 + k_axisScale * xf.q.GetYAxis();
	DrawSegment(p1, p2, b2Color(0, 1, 0));
}

void GLESDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	_shaderProgram->setUniformLocationWith4f(_colorLocation, color.r, color.g, color.b, 1);

	//    glPointSize(size);

	GLfloat glVertices[] =
	{
		p.x * ratio, p.y * ratio
	};

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, glVertices);

	glDrawArrays(GL_POINTS, 0, 1);
	//    glPointSize(1.0f);

	CC_INCREMENT_GL_DRAWS(1);

	CHECK_GL_ERROR_DEBUG();
}

void GLESDebugDraw::DrawString(int x, int y, const char *string, ...)
{
	//    NSLog(@"DrawString: unsupported: %s", string);
	//printf(string);
	/* Unsupported as yet. Could replace with bitmap font renderer at a later date */
}

void GLESDebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color)
{
	_shaderProgram->setUniformLocationWith4f(_colorLocation, color.r, color.g, color.b, 1);

	GLfloat glVertices[] =
	{
		aabb->lowerBound.x * ratio, aabb->lowerBound.y * ratio,
		aabb->upperBound.x * ratio, aabb->lowerBound.y * ratio,
		aabb->upperBound.x * ratio, aabb->upperBound.y * ratio,
		aabb->lowerBound.x * ratio, aabb->upperBound.y * ratio
	};

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
	glDrawArrays(GL_LINE_LOOP, 0, 8);

	CC_INCREMENT_GL_DRAWS(1);

	CHECK_GL_ERROR_DEBUG();
}
