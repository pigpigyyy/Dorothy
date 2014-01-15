#ifndef __CC_ZIP_H__
#define __CC_ZIP_H__
#include <string>
using std::string;
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

CC_DLL bool ccUZipOpen(const char* zipname);
CC_DLL bool ccUZipIsOpened();
CC_DLL unsigned char* ccUZipReadFile(const char* filename, const char* password, unsigned long& size);
CC_DLL void ccUZipClose();
CC_DLL bool ccUZipExtract(const char* filename, const char* password, const char* targetfile);

NS_CC_END

#endif