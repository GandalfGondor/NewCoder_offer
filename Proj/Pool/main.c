#include "../cpp11netbase/ThreadPool.h"
#include "../cpp11netbase/CountDownLatch.h"
#include "../cpp11netbase/CurrentThread.h"
//#include "cpp11netbase/Logging.h"

#include <stdio.h>
#include <unistd.h>  // usleep

void print()
{
	printf("tid=%d\n", CurrentThread::tid());
}

void printString(const std::string& str)
{
	// LOG_INFO << str;
	//printf("tid=%d,%s\n",CurrentThread::tid(),str.c_str());
	usleep(1000*1000);
}

void test(int maxSize)
{
	//LOG_WARN << "Test ThreadPool with max queue size = " << maxSize;
	ThreadPool pool("MainThreadPool");
	pool.setMaxQueueSize(maxSize);
	pool.start(maxSize);

	// LOG_WARN << "Adding";
	pool.run(print);
	pool.run(print);
	for (int i = 0; i < 1000; ++i)
	{
		char buf[32];
		snprintf(buf, sizeof buf, "task %d", i);
		pool.run(std::bind(printString, std::string(buf)));
	}
	//LOG_WARN << "Done";

	CountDownLatch latch(1);
	pool.run(std::bind(&CountDownLatch::countDown, &latch));
	latch.wait();
	pool.stop();
}

int main()
{
  test(20);
}
