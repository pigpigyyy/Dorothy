#include "const/oDefine.h"
#include "misc/oAsync.h"
#include <errno.h>
#include <queue>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

NS_DOROTHY_BEGIN

static pthread_t s_loadingThread;
static pthread_mutex_t s_asyncQueueMutex;
static pthread_mutex_t s_resultMutex;

static sem_t* s_pSem = nullptr;
static unsigned long s_nAsyncRefCount = 0;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    #define OASYNC_USE_NAMED_SEMAPHORE 1
#else
    #define OASYNC_USE_NAMED_SEMAPHORE 0
#endif

#if OASYNC_USE_NAMED_SEMAPHORE
    #define OASYNC_SEMAPHORE "oAsync"
#else
    static sem_t s_sem;
#endif

static bool need_quit = false;

struct oAsyncStruct
{
	function<void*()> worker;
	function<void(void*)> finisher;
};
typedef queue<oAsyncStruct> oAsyncQueue;

struct oResultStruct
{
	function<void(void*)> finisher;
	void* result;
};
typedef queue<oResultStruct> oResultQueue;

static oAsyncQueue* s_asyncQueue = nullptr;
static oResultQueue* s_resultQueue = nullptr;

static void* dowork(void* data)
{
	oAsyncStruct asyncStruct;
    while (true)
    {
        CCThread thread;
        thread.createAutoreleasePool();

        int semWaitRet = sem_wait(s_pSem);
        if(semWaitRet < 0)
        {
            CCLOG("oAsync thread semaphore error: %s\n", strerror(errno));
            break;
        }

        pthread_mutex_lock(&s_asyncQueueMutex);
        if (s_asyncQueue->empty())
        {
            pthread_mutex_unlock(&s_asyncQueueMutex);
            if (need_quit) break;
            else continue;
        }
        else
        {
            asyncStruct = s_asyncQueue->front();
            s_asyncQueue->pop();
            pthread_mutex_unlock(&s_asyncQueueMutex);
        }
		
        pthread_mutex_lock(&s_resultMutex);
        s_resultQueue->push(oResultStruct{asyncStruct.finisher,asyncStruct.worker()});
		pthread_mutex_unlock(&s_resultMutex);
    }

    if (s_pSem)
    {
#if OASYNC_USE_NAMED_SEMAPHORE
        sem_unlink(OASYNC_SEMAPHORE);
        sem_close(s_pSem);
#else
        sem_destroy(s_pSem);
#endif
        s_pSem = nullptr;
        delete s_asyncQueue;
        delete s_resultQueue;
    }

    return 0;
}

class oAsyncWorker: CCObject
{
public:
	~oAsyncWorker()
	{
		need_quit = true;
    	if (s_pSem)
    	{
        	sem_post(s_pSem);
    	}
	}
	void async(const function<void*()>& worker, const function<void(void*)>& finisher)
	{
	    if (!s_pSem)
    	{
#if OASYNC_USE_NAMED_SEMAPHORE
        	s_pSem = sem_open(OASYNC_SEMAPHORE, O_CREAT, 0644, 0);
	        if(s_pSem == SEM_FAILED)
    	    {
        	    CCLOG("oAsync thread semaphore init error: %s\n", strerror(errno));
            	s_pSem = nullptr;
	            return;
    	    }
#else
        	int semInitRet = sem_init(&s_sem, 0, 0);
			if (semInitRet < 0)
			{
				CCLOG("oAsync thread semaphore init error: %s\n", strerror(errno));
				return;
			}
        	s_pSem = &s_sem;
#endif
    	    s_asyncQueue = new oAsyncQueue();
    	    s_resultQueue = new oResultQueue();
			pthread_mutex_init(&s_asyncQueueMutex, nullptr);
			pthread_mutex_init(&s_resultMutex, nullptr);
			pthread_create(&s_loadingThread, nullptr, dowork, nullptr);
			need_quit = false;
		}
		if (0 == s_nAsyncRefCount)
		{
			CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(oAsyncWorker::asyncCallback), this, 0, false);
		}
		++s_nAsyncRefCount;
		pthread_mutex_lock(&s_asyncQueueMutex);
		s_asyncQueue->push(oAsyncStruct{worker,finisher});
		pthread_mutex_unlock(&s_asyncQueueMutex);
		sem_post(s_pSem);
	}
	void asyncCallback(float dt)
	{
	    pthread_mutex_lock(&s_resultMutex);
		if (s_resultQueue->empty())
		{
			pthread_mutex_unlock(&s_resultMutex);
		}
		else
		{
			oResultStruct resultStruct = s_resultQueue->front();
			s_resultQueue->pop();
			pthread_mutex_unlock(&s_resultMutex);

			--s_nAsyncRefCount;
			if (0 == s_nAsyncRefCount)
			{
				CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(oAsyncWorker::asyncCallback), this);
			}
			resultStruct.finisher(resultStruct.result);
		}
	}
	static oAsyncWorker* shared()
	{
		static oAsyncWorker worker;
		return &worker;
	}
};

void oAsync(const function<void*()>& worker, const function<void(void*)>& finisher)
{
	oAsyncWorker::shared()->async(worker, finisher);
}

NS_DOROTHY_END
