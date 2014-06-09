/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/model/oModelDef.h"
#include "Dorothy/model/oModelAnimationDef.h"
#include "Dorothy/const/oXml.h"
#include "Dorothy/model/oKeyFrame.h"
#include "Dorothy/model/oModel.h"
#include "Dorothy/model/oClip.h"
#include "Dorothy/misc/oContent.h"
#include "Dorothy/misc/oHelper.h"

#define s(x) oHelper::convert(x,2,buf,32)
#define sp(x) oHelper::convert(x,3,buf,32)

NS_DOROTHY_BEGIN

CCSprite* oSpriteDef::toSprite()
{
	CCSprite* sprite = CCSprite::createWithTexture(texture, rect);
	sprite->setAnchorPoint(ccp(anchorX, anchorY));
	oSpriteDef::restore(sprite);
	return sprite;
}

void oSpriteDef::restore( CCSprite* sprite )
{
	sprite->setPosition(ccp(x, y));
	sprite->setScaleX(scaleX);
	sprite->setScaleY(scaleY);
	sprite->setRotation(rotation);
	sprite->setSkewX(skewX);
	sprite->setSkewY(skewY);
	sprite->setOpacity(opacity);
}

oSpriteDef::oSpriteDef():
x(0.0f),
y(0.0f),
rotation(0.0f),
anchorX(0.5f),
anchorY(0.5f),
scaleX(1.0f),
scaleY(1.0f),
skewX(0.0f),
skewY(0.0f),
texture(nullptr),
rect(),
clip(),
opacity(1.0f)
{ }

string oSpriteDef::toXml()
{
	char buf[32];
	ostringstream stream;
	stream << '<' << char(oModelXml::Sprite);
	if (x != 0.0f || y != 0.0f)
	{
		stream << ' ' << char(oModelXml::Position) << "=\"" << s(x);
		stream << ',' << s(y) << '\"';
	}
	if (rotation != 0.0f)
	{
		stream << ' ' << char(oModelXml::Rotation) << "=\"" << s(rotation) << '\"';
	}
	if (anchorX != 0.5f || anchorY != 0.5f)
	{
		stream << ' ' << char(oModelXml::Key) << "=\"" << sp(anchorX);
		stream << ',' << sp(anchorY) << '\"';
	}
	if (scaleX != 1.0f || scaleY != 1.0f)
	{
		stream << ' ' << char(oModelXml::Scale) << "=\"" << s(scaleX);
		stream << ',' << s(scaleY) << '\"';
	}
	if (skewX != 0.0f || skewY != 0.0f)
	{
		stream << ' ' << char(oModelXml::Skew) << "=\"" << s(skewX);
		stream << ',' << s(skewY) << '\"';
	}
	if (!name.empty())
	{
		stream << ' ' << char(oModelXml::Name) << "=\"" << name << '\"';
	}
	if (!clip.empty())
	{
		stream << ' ' << char(oModelXml::Clip) << "=\"" << clip << '\"';
	}
	stream << '>';
	for (oModelAnimationDef* actionDef : animationDefs)
	{
		if (actionDef)
		{
			stream << actionDef->toXml();
		}
		else
		{
			stream << '<' << char(oModelXml::KeyAnimation) << "/>";
		}
	}
	if (!looks.empty())
	{
		stream << '<' << char(oModelXml::Look) << ' '
			<< char(oModelXml::Name) << "=\"";
		int last = looks.size() - 1;
		for (int i = 0;i < (int)looks.size();i++)
		{
			stream << looks[i];
			if (i != last)
			{
				stream << ',';
			}
		}
		stream << "\"/>";
	}
	for (oSpriteDef* spriteDef : children)
	{
		stream << spriteDef->toXml();
	}
	stream << "</" << char(oModelXml::Sprite) << '>';
	return stream.str();
}

tuple<CCFiniteTimeAction*,CCArray*> oSpriteDef::toResetAction()
{
	CCArray* keyFrames = CCArray::createWithCapacity(5);
	keyFrames->addObject(oKeyPos::create(1.0f, x, y, oEase::InOutQuad));
	keyFrames->addObject(oKeyScale::create(1.0f, scaleX, scaleY, oEase::InOutQuad));
	keyFrames->addObject(oKeyRoll::create(1.0f, rotation, oEase::InOutQuad));
	keyFrames->addObject(oKeySkew::create(1.0f, skewX, skewY, oEase::InOutQuad));
	keyFrames->addObject(oKeyOpacity::create(1.0f, opacity, oEase::InOutQuad));
	/*
	oKeyPos
	oKeyScale
	oKeyRoll
	oKeySkew
	oKeyOpacity
	*/
	return std::make_tuple(CCSpawn::create(keyFrames), keyFrames);
}

oModelDef::oModelDef():
_texture(nullptr),
_isFaceRight(false),
_isBatchUsed(true)
{ }

oModelDef::oModelDef(
	bool isFaceRight,
	bool isBatchUsed,
	const CCSize& size,
	const string& clipFile,
	CCTexture2D* texture,
	oSpriteDef* root,
	const vector<oVec2>& keys,
	const hash_strmap<int>& animationIndex,
	const hash_strmap<int>& lookIndex):
_texture(texture),
_clip(clipFile),
_isFaceRight(isFaceRight),
_isBatchUsed(isBatchUsed),
_size(size),
_keys(keys),
_animationIndex(animationIndex),
_lookIndex(lookIndex),
_root(oOwnMake(root))
{ }

void oModelDef::setTexture( CCTexture2D* tex )
{
	_texture = tex;
}

const string& oModelDef::getClipFile() const
{
	return _clip;
}

CCTexture2D* oModelDef::getTexture()
{
	return _texture;
}

void oModelDef::setRoot( oSpriteDef* root )
{
	_root = oOwnMake(root);
}

oSpriteDef* oModelDef::getRoot()
{
	return _root;
}

oModel* oModelDef::toModel()
{
	return oModel::create(this);
}

const oVec2& oModelDef::getKeyPoint( uint32 index ) const
{
	if (index >= _keys.size())
	{
		return oVec2::zero;
	}
	return _keys[index];
}

string oModelDef::toXml()
{
	char buf[32];
	ostringstream stream;
	stream << '<' << char(oModelXml::Dorothy) << ' '
		<< char(oModelXml::File) << "=\"" << oString::getFileName(_clip) << "\" ";
	if (_isFaceRight)
	{
		stream << char(oModelXml::FaceRight) << "=\"1\" ";
	}
	if (!_isBatchUsed)
	{
		stream << char(oModelXml::UseBatch) << "=\"0\" ";
	}
	if (_size != CCSize::zero)
	{
		stream << char(oModelXml::Size) << "=\"" << s(_size.width);
		stream << ',' << s(_size.height) << "\" ";
	}
	stream << '>' << _root->toXml();
	for (const oIndexMap::value_type& item: _animationIndex)
	{
		stream << '<' << char(oModelXml::AnimationName) << ' '
			<< char(oModelXml::Index) << "=\"" << item.second << "\" "
			<< char(oModelXml::Name) << "=\"" << item.first.p << "\"/>";
	}
	for (const oIndexMap::value_type& item: _lookIndex)
	{
		stream << '<' << char(oModelXml::LookName) << ' '
			<< char(oModelXml::Index) << "=\"" << item.second << "\" "
			<< char(oModelXml::Name) << "=\"" << item.first.p << "\"/>";
	}
	stream << "</" << char(oModelXml::Dorothy) << '>';
	return stream.str();
}

bool oModelDef::isFaceRight() const
{
	return _isFaceRight;
}

int oModelDef::getAnimationIndexByName( const string& name )
{
	auto it = _animationIndex.find(name);
	if (it != _animationIndex.end())
	{
		return it->second;
	}
	return oAnimation::None;
}

string oModelDef::getAnimationNameByIndex( int index )
{
	for (oIndexMap::value_type& item : _animationIndex)
	{
		if (item.second == index)
		{
			return string(item.first.c_str());
		}
	}
	return string();
}

int oModelDef::getLookIndexByName( const string& name )
{
	auto it = _lookIndex.find(name);
	if (it != _lookIndex.end())
	{
		return it->second;
	}
	return oLook::None;
}

int oModelDef::getKeyPointCount() const
{
	return _keys.size();
}

const hash_strmap<int>& oModelDef::getAnimationIndexMap() const
{
	return _animationIndex;
}

const hash_strmap<int>& oModelDef::getLookIndexMap() const
{
	return _lookIndex;
}

void oModelDef::setActionName( int index, const string& name )
{
	_animationIndex[name] = index;
}

void oModelDef::setLookName( int index, const string& name )
{
	_lookIndex[name] = index;
}

void oModelDef::addKeyPoint( const oVec2& point )
{
	_keys.push_back(point);
}

oModelDef* oModelDef::create()
{
	oModelDef* modelDef = new oModelDef();
	modelDef->autorelease();
	return modelDef;
}

bool oModelDef::isBatchUsed() const
{
	return _isBatchUsed;
}

const CCSize& oModelDef::getSize() const
{
	return _size;
}

NS_DOROTHY_END
