#include "Dorothy/const/oDefine.h"

NS_DOROTHY_BEGIN

size_t oFNVHash( const char* str )
{
	size_t hash = 2166136261u;
	for (unsigned char *s = (unsigned char *)str;*s;++s)
	{
		hash = hash ^ ((size_t)*s) * 16777619u;
	}
	return hash;
}

NS_DOROTHY_END
