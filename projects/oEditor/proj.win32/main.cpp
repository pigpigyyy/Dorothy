#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

// uncomment below line, open debug console
#define USE_WIN32_CONSOLE

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("Dorothy Animation Editor");
	int width = CCUserDefault::sharedUserDefault()->getIntegerForKey("Width");
	int height = CCUserDefault::sharedUserDefault()->getIntegerForKey("Height");
	if (width == 0 || height == 0)
	{
		width = 1024;
		height = 768;
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Width", width);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Height", height);
	}
	eglView->setFrameSize(CCSize(width, height));

    int ret = CCApplication::sharedApplication()->run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}
