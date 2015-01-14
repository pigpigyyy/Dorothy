#ifndef __MKDIR__
#define __MKDIR__

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#ifdef _MSC_VER
	#include <direct.h>
	#pragma warning (disable : 4996)
#else
	#include <stdarg.h>
#endif

#ifdef _MSC_VER
	#define MKDIR(a) _mkdir((a))
#else
	#define MKDIR(a) mkdir((a),0755)
#endif

static void CopyFile(const char* src, const char* dst)
{
	char buf[BUFSIZ];
    size_t size;

    int source = open(src, O_RDONLY, 0);
    int dest = open(dst, O_WRONLY | O_CREAT, 0644);

    while ((size = read(source, buf, BUFSIZ)) > 0)
	{
        write(dest, buf, size);
    }

    close(source);
    close(dest);
}

static bool IsFolder(const char* filename)
{
	struct stat buf;
	lstat(filename, &buf);
	return S_ISDIR(buf.st_mode);
}

static int FileExist(const char* filename)
{
	struct stat buf;
	return ::stat(filename, &buf);
}

static int CreateDir(const char* dir)
{
	const int MAX_PATH_LEN = 256;
	int iLen = (int)strlen(dir);
	if (iLen > MAX_PATH_LEN - 2) return -1;
	char pszDir[MAX_PATH_LEN];
	strcpy(pszDir, dir);

	if (pszDir[iLen - 1] != '\\' && pszDir[iLen - 1] != '/')
	{
		pszDir[iLen] = '/';
		pszDir[iLen + 1] = '\0';
	}

	for (int i = 0; i < iLen + 1; i++)
	{
		if (i != 0 && (pszDir[i] == '\\' || pszDir[i] == '/'))
		{
			pszDir[i] = '\0';

			int iRet = FileExist(pszDir);
			if (iRet != 0)
			{
				iRet = MKDIR(pszDir);
				if (iRet != 0)
				{
					return -1;
				}
			}
			pszDir[i] = '/';
		}
	}
	return 0;
}

#endif
