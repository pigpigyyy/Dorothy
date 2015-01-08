#ifndef __MKDIR__
#define __MKDIR__

#ifdef _MSC_VER
	#include <direct.h>
	#include <io.h>
	#pragma warning (disable : 4996)
#else
	#include <stdarg.h>
	#include <sys/stat.h>
#endif

#ifdef _MSC_VER
	#define ACCESS _access
	#define MKDIR(a) _mkdir((a))
#else
	#define ACCESS access
	#define MKDIR(a) mkdir((a),0755)
#endif

int CreateDir(const char* dir)
{
	const int MAX_PATH_LEN = 256;
	int iLen = strlen(dir);
	if (iLen > MAX_PATH_LEN - 2) return -1;
	char pszDir[MAX_PATH_LEN];
	strcpy(pszDir, dir);
	int i = 0;
	int iRet;

	//在末尾加/
	if (pszDir[iLen - 1] != '\\' && pszDir[iLen - 1] != '/')
	{
		pszDir[iLen] = '/';
		pszDir[iLen + 1] = '\0';
	}

	// 创建目录
	for (int i = 0; i < iLen + 1; i++)
	{
		if (pszDir[i] == '\\' || pszDir[i] == '/')
		{
			pszDir[i] = '\0';

			//如果不存在,创建
			iRet = ACCESS(pszDir,0);
			if (iRet != 0)
			{
				iRet = MKDIR(pszDir);
				if (iRet != 0)
				{
					return -1;
				}
			}
			//支持linux,将所有\换成/
			pszDir[i] = '/';
		}
	}
	return 0;
}

#endif
