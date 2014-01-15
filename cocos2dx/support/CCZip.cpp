#include "CCZip.h"
#include "ccMacros.h"
#include "support/zip_support/unzip.h"
#include <fstream>
using std::ofstream;

NS_CC_BEGIN

static unzFile g_file = NULL;

bool ccUZipOpen( const char* zipname )
{
	g_file = unzOpen(zipname);
	if (!g_file)
	{
		return false;
	}
	return true;
}

unsigned char* ccUZipReadFile( const char* filename, const char* password, unsigned long& size )
{
	unsigned char * pBuffer = NULL;
	size = 0;
	int result;
	do
	{
		result = unzLocateFile(g_file, filename, 1);
		CC_BREAK_IF(UNZ_OK != result);
		char szFilePathA[260];
		unz_file_info fileInfo;
		result = unzGetCurrentFileInfo(g_file, &fileInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0);
		CC_BREAK_IF(UNZ_OK != result);
		result = unzOpenCurrentFilePassword(g_file, password);
		CC_BREAK_IF(UNZ_OK != result);
		pBuffer = new unsigned char[fileInfo.uncompressed_size];
		int nSize = 0;
		nSize = unzReadCurrentFile(g_file, pBuffer, fileInfo.uncompressed_size);
		CCAssert(nSize == 0 || nSize == (int)fileInfo.uncompressed_size, "the file size is wrong");
		size = fileInfo.uncompressed_size;
		unzCloseCurrentFile(g_file);
	}
	while (0);
	if (result == UNZ_OK)
	{
		return pBuffer;
	}
	return NULL;
}

void ccUZipClose()
{
	if (g_file)
	{
		unzClose(g_file);
		g_file = NULL;
	}
}

bool ccUZipIsOpened()
{
	return g_file != NULL;
}

bool ccUZipExtract( const char* filename, const char* password, const char* targetfile )
{
	do
	{
		int result;
		ofstream stream(targetfile, ofstream::binary|ofstream::trunc);
		CC_BREAK_IF(!stream);

		result = unzLocateFile(g_file, filename, 1);
		CC_BREAK_IF(UNZ_OK != result);

		result = unzOpenCurrentFilePassword(g_file, password);
		CC_BREAK_IF(UNZ_OK != result);

		const int length = 4096;
		char pBuffer[length];
		int nSize = 0;
		do 
		{
			nSize = unzReadCurrentFile(g_file, pBuffer, length);
			stream.write(pBuffer, nSize);
		} while (nSize > 0);

		unzCloseCurrentFile(g_file);
		stream.close();

		return true;
	}
	while (0);
	return false;
}

NS_CC_END