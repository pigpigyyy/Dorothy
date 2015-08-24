/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "model/oKeyFrameDef.h"
#include "model/oKeyFrame.h"
#include "model/oSequence.h"
#include "const/oXml.h"
#include "misc/oHelper.h"

#define s(x) oHelper::convert(x,2,buf,32)

NS_DOROTHY_BEGIN

oKeyFrameDef::oKeyFrameDef():
easePos(0),
easeScale(0),
easeRotation(0),
easeSkew(0),
easeOpacity(0),
visible(true),
opacity(1.0f),
duration(0.0f),
x(0.0f),
y(0.0f),
scaleX(1.0f),
scaleY(1.0f),
rotation(0.0f),
skewX(0.0f),
skewY(0.0f)
{ }

string oKeyFrameDef::toXml(oKeyFrameDef* lastDef)
{
	char buf[32];
	ostringstream stream;
	stream << '<' << char(oModelXml::KeyFrame);
	if ((lastDef && lastDef->duration != duration) || (!lastDef && duration != 0.0f))
	{
		stream << ' ' << char(oModelXml::Duration) << "=\"" << (int)(duration*60.0f+0.5f) << '\"';
	}
	if ((lastDef && lastDef->visible != visible) || (!lastDef && !visible))
	{
		stream << ' ' << char(oModelXml::Visible) << "=\"" << (visible ? "1" : "0") << '\"';
	}
	if ((lastDef && (lastDef->x != x || lastDef->y != y)) || (!lastDef && (x != 0.0f || y != 0.0f)))
	{
		stream << ' ' << char(oModelXml::Position) << "=\"" << s(x);
		stream << ',' << s(y) << '\"';
	}
	if ((lastDef && lastDef->rotation != rotation) || (!lastDef && rotation != 0.0f))
	{
		stream << ' ' << char(oModelXml::Rotation) << "=\"" << s(rotation) << '\"';
	}
	if ((lastDef && (lastDef->scaleX != scaleX || lastDef->scaleY != scaleY)) || (!lastDef && (scaleX != 1.0f || scaleY != 1.0f)))
	{
		stream << ' ' << char(oModelXml::Scale) << "=\"" << s(scaleX);
		stream << ',' << s(scaleY) << '\"';
	}
	if ((lastDef && lastDef->opacity != opacity) || (!lastDef && opacity != 1.0f))
	{
		stream << ' ' << char(oModelXml::Opacity) << "=\"" << s(opacity) << '\"';
	}
	if ((lastDef && (lastDef->skewX != skewX || lastDef->skewY != skewY)) || (!lastDef && (skewX != 0.0f || skewY != 0.0f)))
	{
		stream << ' ' << char(oModelXml::Skew) << "=\"" << s(skewX);
		stream << ',' << s(skewY) << '\"';
	}
	if (easePos != 0)
	{
		stream << ' ' << char(oModelXml::EasePos) << "=\"" << (int)easePos << '\"';
	}
	if (easeScale != 0)
	{
		stream << ' ' << char(oModelXml::EaseScale) << "=\"" << (int)easeScale << '\"';
	}
	if (easeRotation != 0)
	{
		stream << ' ' << char(oModelXml::EaseRotate) << "=\"" << (int)easeRotation << '\"';
	}
	if (easeSkew != 0)
	{
		stream << ' ' << char(oModelXml::EaseSkew) << "=\"" << (int)easeSkew << '\"';
	}
	if (easeOpacity != 0)
	{
		stream << ' ' << char(oModelXml::EaseOpacity) << "=\"" << (int)easeOpacity << '\"';
	}
	stream << "/>";
	return stream.str();
}

oKeyFrameDef* oKeyAnimationDef::getLastFrameDef() const
{
	if (!_keyFrameDefs.empty())
	{
		return _keyFrameDefs.back();
	}
	return nullptr;
}

void oKeyAnimationDef::add( oKeyFrameDef* def )
{
	_keyFrameDefs.push_back(def);
}

const oOwnVector<oKeyFrameDef>& oKeyAnimationDef::getFrames() const
{
	return _keyFrameDefs;
}

oActionDuration* oKeyAnimationDef::toAction()
{
	if (_keyFrameDefs.empty())
	{
		return nullptr;
	}

	int indexFrames = 0;
	CCFiniteTimeAction** keyFrames = (CCFiniteTimeAction**)alloca(sizeof(CCFiniteTimeAction*)*(_keyFrameDefs.size()));
	int indexAttrs = 0;
	CCFiniteTimeAction** keyAttrs = (CCFiniteTimeAction**)alloca(sizeof(CCFiniteTimeAction*)*(oKeyFrameDef::MaxKeyAttributes));

	oKeyFrameDef* lastDef = _keyFrameDefs.front();
	keyFrames[indexFrames++] = oKeyReset::create(lastDef);
	bool lastVisible = lastDef->visible;
	for (uint32 i = 1; i < _keyFrameDefs.size(); i++)
	{
		/* Get current keyFrameDef */
		oKeyFrameDef* def = _keyFrameDefs[i];
		/* Check for animated attributes of keyFrame */
		if (lastDef->x != def->x || lastDef->y != def->y)
		{
			keyAttrs[indexAttrs++] = oKeyPos::create(def->duration, def->x, def->y, def->easePos);
		}
		if (lastDef->scaleX != def->scaleX || lastDef->scaleY != def->scaleY)
		{
			keyAttrs[indexAttrs++] = oKeyScale::create(def->duration, def->scaleX, def->scaleY, def->easeScale);
		}
		if (lastDef->skewX != def->skewX || lastDef->skewY != def->skewY)
		{
			keyAttrs[indexAttrs++] = oKeySkew::create(def->duration, def->skewX, def->skewY, def->easeSkew);
		}
		if (lastDef->rotation != def->rotation)
		{
			keyAttrs[indexAttrs++] = oKeyRotate::create(def->duration, def->rotation, def->easeRotation);
		}
		if (lastDef->opacity != def->opacity)
		{
			keyAttrs[indexAttrs++] = oKeyOpacity::create(def->duration, def->opacity, def->easeOpacity);
		}
		if (lastVisible != lastDef->visible)
		{
			keyAttrs[indexAttrs++] = lastDef->visible ? (CCFiniteTimeAction*)CCShow::create() : (CCFiniteTimeAction*)CCHide::create();
			lastVisible = lastDef->visible;
		}
		/* Add a new keyFrame */
		if (indexAttrs > 1)// Multiple attributes animated
		{
			keyFrames[indexFrames++] = oSpawn::create(keyAttrs, indexAttrs);
		}
		else if (indexAttrs == 1)// Single attribute animated
		{
			keyFrames[indexFrames++] = keyAttrs[0];
		}
		else // No attribute animated
		{
			keyFrames[indexFrames++] = CCDelayTime::create(def->duration);
		}
		indexAttrs = 0;
		lastDef = def;
	}
	return oSequence::create(keyFrames, indexFrames);
}

string oKeyAnimationDef::toXml()
{
	ostringstream stream;
	stream << '<' << char(oModelXml::KeyAnimation);
	if (_keyFrameDefs.empty())
	{
		stream << "/>";
	}
	else
	{
		stream << '>';
		oKeyFrameDef* lastDef = nullptr;
		for (oKeyFrameDef* keyFrameDef : _keyFrameDefs)
		{
			stream << keyFrameDef->toXml(lastDef);
			lastDef = keyFrameDef;
		}
		stream << "</" << char(oModelXml::KeyAnimation) << '>';
	}
	return stream.str();
}

void oKeyAnimationDef::restoreResetAnimation( CCObject* data )
{
	CCArray* keyFrames = (CCArray*)data;
	((oKeyPos*)(keyFrames->objectAtIndex(0)))->setValue(_keyFrameDefs[0]->x, _keyFrameDefs[0]->y);
	((oKeyScale*)(keyFrames->objectAtIndex(1)))->setValue(_keyFrameDefs[0]->scaleX, _keyFrameDefs[0]->scaleY);
	((oKeyRoll*)(keyFrames->objectAtIndex(2)))->setValue(_keyFrameDefs[0]->rotation);
	((oKeySkew*)(keyFrames->objectAtIndex(3)))->setValue(_keyFrameDefs[0]->skewX, _keyFrameDefs[0]->skewY);
	((oKeyOpacity*)(keyFrames->objectAtIndex(4)))->setValue(_keyFrameDefs[0]->opacity);
}

NS_DOROTHY_END
