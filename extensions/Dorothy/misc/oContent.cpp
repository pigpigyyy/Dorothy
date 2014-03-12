#include "Dorothy/const/oDefine.h"
#include "Dorothy/misc/oContent.h"
#include <cstdio>
#include <sys/stat.h>

NS_DOROTHY_BEGIN

class oDataSource: public CCDataSource
{
public:
	virtual unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long* pSize)
	{
		if (oSharedContent.isUsingGameFile())
		{
			return ccUZipReadFile(
				pszFileName,
				oSharedContent.getPassword().empty() ? nullptr : oSharedContent.getPassword().c_str(),
				*pSize);
		}
		return nullptr;
	}
};

oContent::oContent():
_isUsingGameFile(false),
_writablePath(std::move(CCFileUtils::sharedFileUtils()->getWritablePath()))
{
	CCFileUtils::sharedFileUtils()->setDataSource(new oDataSource());
}

oContent::~oContent()
{
	if (ccUZipIsOpened())
	{
		ccUZipClose();
	}
}

CCTexture2D* oContent::loadTexture( const char* filename )
{
	if (_isUsingGameFile)
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey(filename);
		if (!texture)
		{
			unsigned long size;
			unsigned char* buffer = ccUZipReadFile(
				filename,
				_password.empty() ? nullptr : _password.c_str(),
				size);
			CCImage* image = new CCImage();
			image->initWithImageData(buffer, size);
			texture = CCTextureCache::sharedTextureCache()->addUIImage(image, filename);
			delete image;
			delete buffer;
		}
		return texture;
	}
	else
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(filename);
		return texture;
	}
}

oOwnArray<char> oContent::loadFile( const char* filename, unsigned long& size )
{
	if (_isUsingGameFile)
	{
		char* buffer = (char*)ccUZipReadFile(
			filename,
			_password.empty() ? nullptr : _password.c_str(),
			size);
		return oOwnArray<char>(buffer);
	}
	else
	{
		char* buffer = (char*)CCFileUtils::sharedFileUtils()->getFileData(filename, "rt", &size);
		return oOwnArray<char>(buffer);
	}
}

bool oContent::setGameFile(const string& var)
{
	_gameFileName = _writablePath + var;
	if (ccUZipIsOpened())
	{
		ccUZipClose();
	}
	if (!ccUZipOpen(_gameFileName.c_str()))
	{
		_gameFileName.clear();
		return false;
	}
	return true;
}

void oContent::setUsingGameFile(bool use)
{
	_isUsingGameFile = use;
}

bool oContent::isUsingGameFile() const
{
	return _isUsingGameFile;
}

void oContent::setPassword( const string& password )
{
	_password = password;
}

const string& oContent::getPassword() const
{
	return _password;
}

void oContent::extractGameFile(const char* filename, const char* targetFullName)
{
	if (!_gameFileName.empty())
	{
		ccUZipExtract(
			filename,
			_password.empty() ? nullptr : _password.c_str(),
			targetFullName);
	}
}

string oContent::getExtractedFullName( const char* filename )
{
	string file(filename);
	return std::move(_writablePath + file);
}

bool oContent::isFileExist(const char* filename)
{
	struct stat buf;
	if (::stat(filename, &buf) != -1)
	{
		return true;
	}
	return false;
}

bool oContent::removeExtractedFile( const char* filename )
{
	return ::remove(filename) == 0;
}

NS_DOROTHY_END
