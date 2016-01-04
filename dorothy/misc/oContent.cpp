/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "misc/oContent.h"
#include "misc/oAsync.h"
#include "other/mkdir.h"
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
			return (unsigned char*)oSharedContent.loadFileUnsafe(pszFileName, *pSize);
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
			oOwnArray<char> buffer = oContent::loadFile(filename, size);
			oOwn<CCImage> image(new CCImage());
			image->initWithImageData(buffer, (unsigned int)size);
			texture = CCTextureCache::sharedTextureCache()->addUIImage(image, filename);
		}
		return texture;
	}
	else
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(filename);
		return texture;
	}
}

char* oContent::loadFileUnsafe(const char* filename, unsigned long& size)
{
	if (_isUsingGameFile)
	{
		return (char*)ccUZipReadFile(filename,
			_password.empty() ? nullptr : _password.c_str(),
			size);
	}
	else
	{
		return (char*)CCFileUtils::sharedFileUtils()->getFileData(filename, "rb", &size);
	}
}

oOwnArray<char> oContent::loadFile(const char* filename, unsigned long& size)
{
	return oOwnArray<char>(oContent::loadFileUnsafe(filename,size));
}

void oContent::loadFileAsyncUnsafe(const char* filename, const function<void(char*,unsigned long)>& callback)
{
	string filenameStr = filename;
	oAsync([filenameStr,this]
	{
		unsigned long size;
		char* buffer = this->loadFileUnsafe(filenameStr.c_str(), size);
		return new std::tuple<char*,unsigned long>(buffer,size);
	},
	[callback](void* result)
	{
		char* buffer;
		unsigned long size;
		auto data = (std::tuple<char*,unsigned long>*)result;
		std::tie(buffer,size) = *data;
		delete data;
		callback(buffer,size);
	});
}

void oContent::loadFileAsync(const char* filename, const function<void(oOwnArray<char>,unsigned long)>& callback)
{
	oContent::loadFileAsyncUnsafe(filename, [callback](char* buffer,unsigned long size){callback(oOwnArrayMake(buffer),size);});
}

bool oContent::setGameFile(const string& var)
{
	_gameFileName = var;
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
		ccUZipExtract(filename,
			_password.empty() ? nullptr : _password.c_str(),
			targetFullName);
	}
}

void oContent::extractGameFileAsync(const char* file, const char* target, const function<void(const char* filename)>& callback)
{
	string filename = file, targetName = target;
	oAsync([filename,targetName,this]
	{
		this->extractGameFile(filename.c_str(), targetName.c_str());
		return nullptr;
	},
	[callback,targetName](void* result)
	{
		callback(targetName.c_str());
	});
}

void oContent::copyFile(const char* src, const char* dst)
{
	string srcPath = oContent::getFullPath(src);
	//CCLOG("copy file from %s",srcPath.c_str());
	//CCLOG("copy file to %s",dst);
	if (CCFileUtils::sharedFileUtils()->isFolder(srcPath))
	{
		string dstPath = dst;
		auto folders = oContent::getDirEntries(src, true);
		for (const string& folder : folders)
		{
			if (folder != "." && folder != "..")
			{
				//CCLOG("now copy folder %s",folder.c_str());
				string dstFolder = dstPath+'/'+folder;
				if (!oContent::isFileExist(dstFolder.c_str()))
				{
					bool result = oContent::mkdir(dstFolder.c_str());
					if (!result) CCLOG("Create folder failed! %s",dstFolder.c_str());
				}
				oContent::copyFile((srcPath+'/'+folder).c_str(),dstFolder.c_str());
			}
		}
		auto files = oContent::getDirEntries(src, false);
		for (const string& file : files)
		{
			unsigned long size;
			//CCLOG("now copy file %s",file.c_str());
			auto buffer = this->loadFile((srcPath + '/' + file).c_str(), size);
			ofstream stream((dstPath + '/' + file).c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
			if (!stream.write(buffer, size)) CCLOG("write file failed! %s",(dstPath + '/' + file).c_str());
		}
	}
	else
	{
		unsigned long size;
		auto buffer = this->loadFile(src, size);
		ofstream stream(dst, std::ios::out | std::ios::trunc | std::ios::binary);
		stream.write(buffer, size);
	}
}

void oContent::copyFileAsync(const char* src, const char* dst, const function<void()>& callback)
{
	string srcFile = src, dstFile = dst;
	oAsync([srcFile,dstFile,this]
	{
		this->copyFile(srcFile.c_str(), dstFile.c_str());
		return nullptr;
	},
	[callback](void* result)
	{
		callback();
	});
}

string oContent::getExtractedFullName( const char* filename )
{
	return _writablePath + "Extracted/" + filename;
}

bool oContent::isFileExist(const char* filename)
{
	return CCFileUtils::sharedFileUtils()->isFileExist(oContent::getFullPath(filename));
}

bool oContent::removeFile( const char* filename )
{
	string fullpath = oContent::getFullPath(filename);
	return ::remove(fullpath.c_str()) == 0 || RMDIR(fullpath.c_str()) == 0;
}

void oContent::saveToFile(const string& filename, const string& content)
{
	ofstream stream(oContent::getFullPath(filename.c_str()), std::ios::trunc);
	stream.write(content.c_str(), content.size());
}

vector<string> oContent::getDirEntries(const char* path, bool isFolder)
{
	return CCFileUtils::sharedFileUtils()->getDirEntries(path, isFolder);
}

bool oContent::mkdir(const char* path)
{
	return CreateDir(path) == 0;
}

bool oContent::isdir(const char* name)
{
	return CCFileUtils::sharedFileUtils()->isFolder(name);
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

string oContent::getFullPath(const char* pszFileName)
{
	return CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFileName);
}
const char* oContent::getRelativeFullPath(const char *pszFilename, const char *pszRelativeFile)
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
void oContent::removeSearchPath(const char* path)
{
	CCFileUtils::sharedFileUtils()->removeSearchPath(path);
}
void oContent::setSearchPaths(const vector<string>& searchPaths)
{
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
}
void oContent::addSearchResolutionsOrder(const char* order)
{
	CCFileUtils::sharedFileUtils()->addSearchResolutionsOrder(order);
}
void oContent::setSearchResolutionsOrder(const vector<string>& searchOrders)
{
	CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(searchOrders);
}
void oContent::purgeCachedEntries()
{
	CCFileUtils::sharedFileUtils()->purgeCachedEntries();
}

NS_DOROTHY_END
