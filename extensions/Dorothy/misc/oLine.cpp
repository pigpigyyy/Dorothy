/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/misc/oLine.h"

NS_DOROTHY_BEGIN

int getColorLocation()
{
	static int colorLocation = glGetUniformLocation(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_Position_uColor)->getProgram(), "u_color");
	return colorLocation;
}

oLine::oLine():
_buffer(nullptr),
_count(0)
{ }

oLine::~oLine()
{
	CC_SAFE_DELETE_ARRAY(_buffer);
}

bool oLine::init()
{
	CCNode::init();
	CC_SAFE_DELETE_ARRAY(_buffer);
	_count = 0;
	CCGLProgram* shader = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_Position_uColor);
	CCNode::setShaderProgram(shader);
	return true;
}

void oLine::set(oVec2 vecs[], int count)
{
	CC_SAFE_DELETE_ARRAY(_buffer);
	if (count > 0)
	{
		_buffer = new ccVertex2F[count];
		for (size_t i = 0; i < (size_t)count; i++)
		{
			_buffer[i] = { vecs[i].x, vecs[i].y };
		}
	}
	_count = count;
}

void oLine::draw()
{
	if (_count >= 2)
	{
		ccGLBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
		m_pShaderProgram->use();
		m_pShaderProgram->setUniformsForBuiltins();
		ccColor4F color(_displayedColor, _displayedOpacity);
		m_pShaderProgram->setUniformLocationWith4fv(getColorLocation(), (GLfloat*)&color.r, 1);

		ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
		glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, _buffer);
		glDrawArrays(GL_LINE_STRIP, 0, _count);

		CC_INCREMENT_GL_DRAWS(1);
	}
}

oLine* oLine::create()
{
	oLine* line = new oLine();
	line->init();
	line->autorelease();
	return line;
}

oLine* oLine::create(oVec2 vecs[], int count, const ccColor4B& color)
{
	oLine* line = oLine::create();
	line->set(vecs, count);
	line->setColor(ccColor3B(color.r, color.g, color.b));
	line->setOpacity(color.a / 255.0f);
	return line;
}

NS_DOROTHY_END
