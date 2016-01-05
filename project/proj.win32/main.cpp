#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include "resource.h"
#include <algorithm>

USING_NS_CC;


int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int nCmdShow)
{
#ifdef _DEBUG
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif
	if (lpCmdLine && lpCmdLine[0])
	{
		string filename = lpCmdLine;
		filename.erase(std::remove(filename.begin(),filename.end(),'\"'),filename.end());
		CCUserDefault::sharedUserDefault()->setStringForKey("ScriptEntry", filename.c_str());
	}

	// create the application instance
	AppDelegate app;
	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	eglView->setViewName("Dorothy");

	SetClassLong(eglView->getHWnd(), GCL_HICON, (long)LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME)));
	int width = CCUserDefault::sharedUserDefault()->getIntegerForKey("Width");
	int height = CCUserDefault::sharedUserDefault()->getIntegerForKey("Height");
	if (width == 0 || height == 0)
	{
		width = 800;
		height = 600;
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Width", width);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Height", height);
	}

	eglView->setFrameSize(CCSize(width, height));

	int ret = CCApplication::sharedApplication()->run();
#if defined(_DEBUG)
	FreeConsole();
#endif
	return ret;
}
