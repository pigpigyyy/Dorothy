/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_CONST_OXML_H__
#define __DOROTHY_CONST_OXML_H__

#include "Dorothy/const/oDefine.h"

NS_DOROTHY_BEGIN

struct oClipXml
{
	enum
	{
		Texture = 'A',//0
			//<a>
			File = 'A',
			//</a>

			Clip = 'B',//1
				//<a>
				Name = 'A',
				Rect = 'B'
				//</a>
	};
};

struct oEffectXml
{
	enum
	{
		Dorothy = 'A',//0
			Effect = 'B',//1
				//<a>
				Index = 'A',
				File = 'B'
				//</a>
	};
};

struct oFrameXml
{
	enum
	{
		Texture = 'A',//0
			// <a>
			File = 'A',
			Duration = 'B',
			// </a>

			Clip = 'B',//1
				// <a>
				Rect = 'A',
				// </a>
	};
};

struct oModelXml
{
	enum
	{
		Dorothy = 'A',//0
			//<a>
			File = 'A',
			FaceRight = 'B',
			UseBatch = 'C',
			Size = 'D',
			//</a>

			Sprite = 'B',//1
				//<a>
				Key = 'A',
				Visible = 'B',
				Opacity = 'C',
				Position = 'D',
				Scale = 'E',
				Rotation = 'F',
				Skew = 'G',
				Name = 'H',
				Clip = 'I',
				Front = 'J',
				//</a>

				KeyAnimation = 'C',//2
					KeyFrame = 'D',//3
						//<a>
						Duration = 'A',
//		 				Visible = 'B',
//		 				Opacity = 'C',
//		 				Position = 'D',
//		 				Scale = 'E',
//		 				Rotation = 'F',
//		 				Skew = 'G',
						EaseOpacity = 'H',
						EasePos = 'I',
						EaseScale = 'J',
						EaseRotate = 'K',
						EaseSkew = 'L',
						//</a>

 				FrameAnimation = 'E',//4
					//<a>
//		 			File = 'A',
					Delay = 'B',
					//</a>

				Look = 'F',//5
					//<a>
//		 			Name = 'H',
					//</a>

			Sound = 'G',//6
 				Track = 'H',//7
					//<a>
//	 				File = 'A',
					Time = 'B',
					Index = 'C',
					//</a>

			LookName = 'I',//8
				//<a>
//				Index = 'C',
//				Name = 'H'
				//</a>

			AnimationName = 'J',//9
				//<a>
//				Index = 'C',
//				Name = 'H'
				//</a>
	};
};

struct oFaceXml
{
	enum
	{
		Str = 'A',
		Pos = 'B'
	};
};

NS_DOROTHY_END

#endif // __DOROTHY_CONST_OXML_H__