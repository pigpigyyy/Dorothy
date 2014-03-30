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
_count(0),
_acceptOpacity(true)
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
	_buffer = new ccVertex2F[count];
	for (size_t i = 0; i < (size_t)count; i++)
	{
		_buffer[i] = {vecs[i].x,vecs[i].y};
	}
	_count = count;
}

void oLine::setAcceptOpacity(bool var)
{
	_acceptOpacity = var;
	CCNode::setOpacity(_realOpacity);
}

bool oLine::isAcceptOpacity() const
{
	return _acceptOpacity;
}

void oLine::draw()
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

void oLine::updateDisplayedOpacity(float parentOpacity)
{
	if (m_pParent && m_pParent->isCascadeOpacity() && _acceptOpacity)
	{
		_displayedOpacity = _realOpacity * parentOpacity;
	}
	if (_cascadeOpacity)
	{
		CCObject* pObj;
		CCARRAY_FOREACH(m_pChildren, pObj)
		{
			CCNode* node = (CCNode*)pObj;
			node->updateDisplayedOpacity(_displayedOpacity);
		}
	}
}

oLine* oLine::create(oVec2 vecs[], int count, const ccColor4B& color)
{
	oLine* line = new oLine();
	line->init();
	line->autorelease();
	line->set(vecs, count);
	line->setColor(ccColor3B(color.r, color.g, color.b));
	line->setOpacity(color.a / 255.0f);
	return line;
}

NS_DOROTHY_END
