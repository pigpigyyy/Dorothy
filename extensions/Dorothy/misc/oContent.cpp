/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/misc/oContent.h"
#include "Dorothy/other/tinydir.h"
#include "Dorothy/other/mkdir.h"
#include <fstream>
using std::ofstream;

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
			image->initWithImageData(buffer, (unsigned int)size);
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
	return FileExist(filename) == 0;
}

bool oContent::removeFile( const char* filename )
{
	return ::remove(filename) == 0;
}

void oContent::saveToFile(const string& filename, const string& content)
{
	ofstream stream(filename, std::ios::trunc);
	stream.write(content.c_str(), content.size());
}

vector<string> oContent::getDirEntries(const char* path, bool isFolder)
{
    std::string searchName = path;
	char last = searchName[searchName.length()-1];
	if (last == '/' || last == '\\')
	{
		searchName.erase(--searchName.end());
	}
	vector<string> files;
	tinydir_dir dir;
	string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(searchName.c_str());
	int ret = tinydir_open(&dir, fullPath.c_str());
	if (ret == 0)
	{
		while (dir.has_next)
		{
			tinydir_file file;
			tinydir_readfile(&dir, &file);
			if ((file.is_dir != 0) == isFolder)
			{
				files.push_back(file.name);
			}
			tinydir_next(&dir);
		}
		tinydir_close(&dir);
	}
	else
	{
		CCLOG("oContent get entry error, code %d", errno);
	}
	return std::move(files);
}

bool oContent::mkdir(const char* path)
{
	return CreateDir(path) == 0;
}

string oContent::getWritablePath() const
{
	return CCFileUtils::sharedFileUtils()->getWritablePath();
}

void oContent::setPopupNotify(bool var)
{
	CCFileUtils::sharedFileUtils()->setPopupNotify(var);
}
bool oContent::isPopupNotify() const
{
	return CCFileUtils::sharedFileUtils()->isPopupNotify();
}

string oContent::getFullPath(char *pszFileName)
{
	return CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFileName);
}
const char* oContent::getRelativeFullPath(char *pszFilename, char *pszRelativeFile)
{
	return CCFileUtils::sharedFileUtils()->fullPathFromRelativeFile(pszFilename, pszRelativeFile);
}
void oContent::loadFileLookupInfo(const char* filename)
{
	CCFileUtils::sharedFileUtils()->loadFilenameLookupDictionaryFromFile(filename);
}

void oContent::addSearchPath(const char* path)
{
	CCFileUtils::sharedFileUtils()->addSearchPath(path);
}
void oContent::addSearchResolutionsOrder(const char* order)
{
	CCFileUtils::sharedFileUtils()->addSearchResolutionsOrder(order);
}
void oContent::purgeCachedEntries()
{
	CCFileUtils::sharedFileUtils()->purgeCachedEntries();
}

NS_DOROTHY_END
