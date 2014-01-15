#include "Dorothy/const/oDefine.h"
#include "Dorothy/misc/oHelper.h"

NS_DOROTHY_BEGIN

const string oString::Empty;

void oHelper::getPosFromStr( const char* str, float& x, float& y )
{
	char temp[64];
	strcpy(temp, str);
	char* token = strtok(temp, ",");
	x = (float)atof(token);
	token = strtok(nullptr, ",");
	y = (float)atof(token);
}

const string oFileExt::Clip = ".clip";
const string oFileExt::Model = ".model";
const string oFileExt::Texture = ".png";
const string oFileExt::Particle = ".plist";
const string oFileExt::Frame = ".frame";
const string oFileExt::Effect = ".effect";

bool oFileExt::check( const string& filename, const string& ext )
{
	return filename.find(ext.c_str(), filename.size() - ext.length(), ext.length()) != string::npos;
}

NS_DOROTHY_END
