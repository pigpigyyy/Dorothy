/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "CCFileUtilsWin32.h"
#include "platform/CCCommon.h"
#include "support/file_system/tinydir.h"
#include <Shlobj.h>

using namespace std;

NS_CC_BEGIN

static char s_pszResourcePath[MAX_PATH] = {0};

static void _checkPath()
{
    if (! s_pszResourcePath[0])
    {
        WCHAR  wszPath[MAX_PATH] = {0};
        int nNum = WideCharToMultiByte(CP_ACP, 0, wszPath,
            GetCurrentDirectoryW(sizeof(wszPath), wszPath),
            s_pszResourcePath, MAX_PATH, NULL, NULL);
        s_pszResourcePath[nNum] = '\\';
    }
}

CCFileUtils* CCFileUtils::sharedFileUtils()
{
	static CCFileUtilsWin32 fileUtils;
	return &fileUtils;
}

CCFileUtilsWin32::CCFileUtilsWin32()
{
	this->init();
}

bool CCFileUtilsWin32::init()
{
    _checkPath();
    m_strDefaultResRootPath = s_pszResourcePath;
    return CCFileUtils::init();
}

bool CCFileUtilsWin32::isFileExist(const std::string& strFilePath)
{
    std::string strPath = strFilePath;
    if (!isAbsolutePath(strPath))
    { // Not absolute path, add the default root path at the beginning.
        strPath.insert(0, m_strDefaultResRootPath);
    }
    return GetFileAttributesA(strPath.c_str()) != -1 ? true : false;
}

bool CCFileUtilsWin32::isFolder(const std::string& path)
{
	struct stat buf;
	if (::stat(path.c_str(), &buf) == 0)
	{
		return (buf.st_mode & S_IFDIR) != 0;
	}
	return false;
}

std::vector<std::string> CCFileUtilsWin32::getDirEntries(const std::string& path, bool isFolder)
{
	std::string searchName = path;
	char last = searchName[searchName.length() - 1];
	if (last == '/' || last == '\\')
	{
		searchName.erase(--searchName.end());
	}
	std::vector<std::string> files;
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
		CCLOG("oContent get entry error, %s, %s", strerror(errno), fullPath.c_str());
	}
	return std::move(files);
}

bool CCFileUtilsWin32::isAbsolutePath(const std::string& strPath)
{
    if (   strPath.length() > 2 
        && ( (strPath[0] >= 'a' && strPath[0] <= 'z') || (strPath[0] >= 'A' && strPath[0] <= 'Z') )
        && strPath[1] == ':')
    {
        return true;
    }
    return false;
}

string CCFileUtilsWin32::getWritablePath()
{
    // Get full path of executable, e.g. c:\Program Files (x86)\My Game Folder\MyGame.exe
    char full_path[_MAX_PATH + 1];
    ::GetModuleFileNameA(NULL, full_path, _MAX_PATH + 1);

    // Debug app uses executable directory; Non-debug app uses local app data directory
#ifndef _DEBUG
        // Get filename of executable only, e.g. MyGame.exe
        char *base_name = strrchr(full_path, '\\');

        if(base_name)
        {
            char app_data_path[_MAX_PATH + 1];

            // Get local app data directory, e.g. C:\Documents and Settings\username\Local Settings\Application Data
            if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, app_data_path)))
            {
                string ret((char*)app_data_path);

                // Adding executable filename, e.g. C:\Documents and Settings\username\Local Settings\Application Data\MyGame.exe
                ret += base_name;

                // Remove ".exe" extension, e.g. C:\Documents and Settings\username\Local Settings\Application Data\MyGame
                ret = ret.substr(0, ret.rfind("."));

                ret += "\\";

                // Create directory
                if (SUCCEEDED(SHCreateDirectoryExA(NULL, ret.c_str(), NULL)))
                {
                    return ret;
                }
            }
        }
#endif // not defined _DEBUG

    // If fetching of local app data directory fails, use the executable one
    string ret((char*)full_path);

    // remove xxx.exe
    ret =  ret.substr(0, ret.rfind("\\") + 1);

    return ret;
}

NS_CC_END
