#ifndef DATTIME_H
#define DATTIME_H

#include "../cpp11netbase/TcpServer.h"

class EventLoop;
class InetAddress;
class TcpConnection;
class Buffer;
class Timestamp;

//typedef shared_ptr<TcpConnection> TcpConnectionPtr;
class DaytimeServer
{
public:
	DaytimeServer(EventLoop *loop,const InetAddress& listenAddr);
	void start();
private:
	void onConnection(const TcpConnectionPtr& conn);
	void onMessage(const TcpConnectionPtr& conn,Buffer* buf,Timestamp time);
	TcpServer server_;
};


#endif
