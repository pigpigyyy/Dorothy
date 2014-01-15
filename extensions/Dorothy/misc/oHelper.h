#ifndef __DOROTHY_MISC_OHELPER_H__
#define __DOROTHY_MISC_OHELPER_H__

NS_DOROTHY_BEGIN

struct oString
{
	static const string Empty;
};

struct oHelper
{
	static void getPosFromStr(const char* str, float& x, float& y);
};

struct oFileExt
{
	static const string Clip;
	static const string Model;
	static const string Texture;
	static const string Particle;
	static const string Frame;
	static const string Effect;
	static bool check(const string& filename, const string& ext);
};

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OHELPER_H__