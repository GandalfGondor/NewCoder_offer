#include "../daytime/daytime.h"
#include <stdio.h>
#include <unistd.h>
#include "../cpp11netbase/EventLoop.h"
int main()
{
	printf("pid = %d",getpid());
	EventLoop loop;
	InetAddress listenAddr(2013);
	DaytimeServer server(&loop, listenAddr);
	server.start();
	loop.loop();
	return 1;
}


