#include "Dorothy/const/oDefine.h"
#include "Dorothy/model/oKeyFrameDef.h"
#include "Dorothy/model/oKeyFrame.h"
#include "Dorothy/model/oSequence.h"
#include "Dorothy/const/oXml.h"

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

string oKeyFrameDef::toXml()
{
	ostringstream stream;
	stream << '<' << char(oModelXml::KeyFrame);
	if (duration != 0.0f)
	{
		stream << ' ' << char(oModelXml::Duration) << "=\"" << (int)(duration*60.0f+0.5f) << '\"';
	}
	if (x != 0.0f || y != 0.0f)
	{
		stream << ' ' << char(oModelXml::Position) << "=\"" << x << ',' << y << '\"';
	}
	if (rotation != 0.0f)
	{
		stream << ' ' << char(oModelXml::Rotation) << "=\"" << rotation << '\"';
	}
	if (scaleX != 1.0f || scaleY != 1.0f)
	{
		stream << ' ' << char(oModelXml::Scale) << "=\"" << scaleX << ',' << scaleY << '\"';
	}
	if (opacity != 1.0f)
	{
		stream << ' ' << char(oModelXml::Opacity) << "=\"" << opacity << '\"';
	}
	if (skewX != 0.0f || skewY != 0.0f)
	{
		stream << ' ' << char(oModelXml::Skew) << "=\"" << skewX << ',' << skewY << '\"';
	}
	if (easePos != 0)
	{
		stream << ' ' << char(oModelXml::EasePos) << "=\"" << easePos << '\"';
	}
	if (easeScale != 0)
	{
		stream << ' ' << char(oModelXml::EaseScale) << "=\"" << easeScale << '\"';
	}
	if (easeRotation != 0)
	{
		stream << ' ' << char(oModelXml::EaseRotate) << "=\"" << easeRotation << '\"';
	}
	if (easeSkew != 0)
	{
		stream << ' ' << char(oModelXml::EaseSkew) << "=\"" << easeSkew << '\"';
	}
	if (easeOpacity != 0)
	{
		stream << ' ' << char(oModelXml::EaseOpacity) << "=\"" << easeOpacity << '\"';
	}
	stream << "/>";
	return stream.str();
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
	CCFiniteTimeAction** keyFrames = (CCFiniteTimeAction**)alloca(sizeof(CCFiniteTimeAction*)*(_keyFrameDefs.size() + 1));
	int indexAttrs = 0;
	CCFiniteTimeAction** keyAttrs = (CCFiniteTimeAction**)alloca(sizeof(CCFiniteTimeAction*)*(oKeyFrameDef::MaxKeyAttributes + 1));

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
			keyAttrs[indexAttrs++] = nullptr;
			keyFrames[indexFrames++] = oSpawn::createWithVariableList(keyAttrs[0],(va_list)(keyAttrs+1));
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
	keyFrames[indexFrames++] = nullptr;
	return oSequence::createWithVariableList(keyFrames[0],(va_list)(keyFrames+1));
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
		for (oKeyFrameDef* keyFrameDef : _keyFrameDefs)
		{
			stream << keyFrameDef->toXml();
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
