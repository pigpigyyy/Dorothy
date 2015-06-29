/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "model/oModelCache.h"
#include "model/oModelDef.h"
#include "const/oXml.h"
#include "model/oClip.h"
#include "misc/oHelper.h"
#include "model/oAnimation.h"
#include "model/oKeyFrameDef.h"

NS_DOROTHY_BEGIN

#define oCase case oModelXml

const int oModelCache::MAX_LOOKS = 128;

oKeyAnimationDef* oModelCache::getCurrentKeyAnimation()
{
	//lazy alloc
	if (!_currentAnimationDef)
	{
		_currentAnimationDef = new oKeyAnimationDef();
	}
	return (oKeyAnimationDef*)_currentAnimationDef;
}

void oModelCache::startElement( void *ctx, const char *name, const char **atts )
{
	switch (name[0])
	{
	oCase::Dorothy:
		{
			for (int i = 0;atts[i] != nullptr;i++)
			{
				switch (atts[i][0])
				{
				oCase::File:
					_item->_clip = _path + atts[++i];
					_currentClip = oSharedClipCache.load(_item->_clip.c_str());
					_currentTexture = oSharedContent.loadTexture(_currentClip->textureFile.c_str());
					_item->setTexture(_currentTexture);
					break;
				oCase::FaceRight:
					_item->_isFaceRight = (atoi(atts[++i]) == 1);
					break;
				oCase::UseBatch:
					_item->_isBatchUsed = (atoi(atts[++i]) == 1);
					break;
				oCase::Size:
					oHelper::getPosFromStr(atts[++i], _item->_size.width, _item->_size.height);
					break;
				}
			}
		}
		break;
	oCase::Sprite:
		{
			oSpriteDef* spriteDef = new oSpriteDef();
			spriteDef->texture = _currentTexture;
			if (atts)
			{
				for (int i = 0;atts[i] != nullptr;i++)
				{
					switch (atts[i][0])
					{
					oCase::Key:
						oHelper::getPosFromStr(atts[++i], spriteDef->anchorX, spriteDef->anchorY);
						break;
					oCase::Opacity:
						spriteDef->opacity = (float)atof(atts[++i]);
						break;
					oCase::Position:
						oHelper::getPosFromStr(atts[++i], spriteDef->x, spriteDef->y);
						break;
					oCase::Scale:
						oHelper::getPosFromStr(atts[++i], spriteDef->scaleX, spriteDef->scaleY);
						break;
					oCase::Rotation:
						spriteDef->rotation = (float)atof(atts[++i]);
						break;
					oCase::Skew:
						oHelper::getPosFromStr(atts[++i], spriteDef->skewX, spriteDef->skewY);
						break;
					oCase::Name:
						spriteDef->name = atts[++i];
						break;
					oCase::Clip:
						{
							spriteDef->clip = atts[++i];
							auto it = _currentClip->rects.find(spriteDef->clip);
							if (it == _currentClip->rects.end())
							{
								spriteDef->clip.clear();
							}
							else
							{
								spriteDef->rect = *(it->second);
							}
						}
						break;
					oCase::Front:
						spriteDef->front = atoi(atts[++i]) != 0;
						break;
					}
				}
			}
			_nodeStack.push(spriteDef);
		}
		break;
	oCase::KeyFrame:
		{
			oKeyFrameDef* keyFrameDef = new oKeyFrameDef();
			if (atts)
			{
				for (int i = 0;atts[i] != nullptr;i++)
				{
					switch (atts[i][0])
					{
					oCase::Duration:
						keyFrameDef->duration = (float)atoi(atts[++i])/60.0f;
						break;
					oCase::Position:
						oHelper::getPosFromStr(atts[++i], keyFrameDef->x, keyFrameDef->y);
						break;
					oCase::Rotation:
						keyFrameDef->rotation = (float)atof(atts[++i]);
						break;
					oCase::Scale:
						oHelper::getPosFromStr(atts[++i], keyFrameDef->scaleX, keyFrameDef->scaleY);
						break;
					oCase::Skew:
						oHelper::getPosFromStr(atts[++i], keyFrameDef->skewX, keyFrameDef->skewY);
						break;
					oCase::Opacity:
						keyFrameDef->opacity = (float)atof(atts[++i]);
						break;
					oCase::Visible:
						keyFrameDef->visible = atoi(atts[++i]) == 1;
						break;
					oCase::EasePos:
						keyFrameDef->easePos = atoi(atts[++i]);
						break;
					oCase::EaseScale:
						keyFrameDef->easeScale = atoi(atts[++i]);
						break;
					oCase::EaseSkew:
						keyFrameDef->easeSkew = atoi(atts[++i]);
						break;
					oCase::EaseRotate:
						keyFrameDef->easeRotation = atoi(atts[++i]);
						break;
					oCase::EaseOpacity:
						keyFrameDef->easeOpacity = atoi(atts[++i]);
						break;
					}
				}
			}
			oKeyAnimationDef* animationDef = oModelCache::getCurrentKeyAnimation();
			animationDef->add(keyFrameDef);
		}
		break;
	oCase::FrameAnimation:
		{
			oFrameAnimationDef* frameAnimationDef = new oFrameAnimationDef();
			for (int i = 0;atts[i] != nullptr;i++)
			{
				switch (atts[i][0])
				{
				oCase::File:
					frameAnimationDef->setFile(atts[++i]);
					break;
				oCase::Delay:
					frameAnimationDef->delay = (float)atof(atts[++i]);
					break;
				}
			}
			oSpriteDef* nodeDef = _nodeStack.top();
			nodeDef->animationDefs.push_back(frameAnimationDef);
		}
		break;
	oCase::Look:
		{
			for (int i = 0;atts[i] != nullptr;i++)
			{
				switch (atts[i][0])
				{
					oCase::Name:
					{
						oSpriteDef* nodeDef = _nodeStack.top();
						char lookStr[MAX_LOOKS*2];
						strcpy(lookStr, atts[++i]);
						char* token = strtok(lookStr, ",");
						while(token != nullptr)
						{
							int look = atoi(token);
							nodeDef->looks.push_back(look);
							token = strtok(nullptr, ",");
						}
					}
					break;
				}
			}
		}
		break;
	oCase::AnimationName:
		{
			int index = 0;
			const char* name = nullptr;
			for (int i = 0;atts[i] != nullptr;i++)
			{
				switch (atts[i][0])
				{
					oCase::Index:
						index = atoi(atts[++i]);
						break;
					oCase::Name:
						name = atts[++i];
						break;
				}
			}
			_item->_animationIndex[name] = index;
		}
		break;
	oCase::LookName:
		{
			int index = 0;
			const char* name = nullptr;
			for (int i = 0;atts[i] != nullptr;i++)
			{
				switch (atts[i][0])
				{
					oCase::Index:
						index = atoi(atts[++i]);
						break;
					oCase::Name:
						name = atts[++i];
						break;
				}
			}
			_item->_lookIndex[name] = index;
		}
		break;
	oCase::KeyPoint:
		{
			const char* key = nullptr;
			oVec2 keyPoint;
			for (int i = 0; atts[i] != nullptr; i++)
			{
				switch (atts[i][0])
				{
					oCase::Key:
						key = atts[++i];
						break;
					oCase::Position:
						oHelper::getPosFromStr(atts[++i], keyPoint.x, keyPoint.y);
						break;
				}
			}
			_item->addKeyPoint(key, keyPoint);
		}
		break;
	}
}

void oModelCache::endElement( void *ctx, const char *name )
{
	switch (name[0])
	{
	oCase::Sprite:
		{
			oSpriteDef* nodeDef = _nodeStack.top();
			_nodeStack.pop();
			if (_nodeStack.empty())
			{
				_item->setRoot(nodeDef);
			}
			else
			{
				oSpriteDef* parentDef = _nodeStack.top();
				parentDef->children.push_back(nodeDef);
			}
		}
		break;
	oCase::KeyAnimation:
		{
			oSpriteDef* nodeDef = _nodeStack.top();
			nodeDef->animationDefs.push_back(_currentAnimationDef);
			_currentAnimationDef = nullptr;
		}
		break;
	}
}

void oModelCache::textHandler( void *ctx, const char *s, int len )
{ }

void oModelCache::beforeParse( const char* filename )
{
	for (;!_nodeStack.empty();_nodeStack.pop());
	_currentTexture = nullptr;
	_currentClip = nullptr;
	_currentAnimationDef = nullptr;
	_item = oModelDef::create();
}

void oModelCache::afterParse( const char* filename )
{ }

NS_DOROTHY_END
