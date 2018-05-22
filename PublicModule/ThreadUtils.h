#pragma once

#include "ThreadUtils/_pri_thread_global.h"
#include "ThreadUtils/ThreadPool.h"
#include <thread>

namespace SSUtils
{
	namespace Thread
	{
		API_DECLSPEC void sleep(const uint64 milliseconds);
		API_DECLSPEC std::thread::id getThisThreadId(void);
	};
};
