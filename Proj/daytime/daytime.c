#include "../cpp11netbase/EventLoop.h"
#include <stdio.h>
#include "daytime.h"
DaytimeServer::DaytimeServer(EventLoop *loop,const InetAddress& listenAddr)
	:server_(loop,listenAddr,"DaytimeServer")
{
	server_.setConnectionCallback(std::bind(&DaytimeServer::onConnection,this,_1));
	server_.setMessageCallback(std::bind(&DaytimeServer::onMessage,this,_1,_2,_3));
}

void DaytimeServer::start()
{
	server_.start();
}

void DaytimeServer::onConnection(const TcpConnectionPtr& conn)
{
	//printf("DaytimeServer - %s -> %s is "
	//	,conn->peerAddress().toIpPort().c_str()
	//	,conn->localAddress().toIpPort().c_str());
	if(conn->connected())
	{
	//	printf("true\n");
		conn->send(Timestamp::now().toFormattedString() +"\n");
		conn->shutdown();
	}
	else 
	{
		//printf("false\n");
	}
	
}
void DaytimeServer::onMessage(const TcpConnectionPtr& conn,Buffer* buf,Timestamp time)
{
	string msg(buf->retrieveAllAsString());
	//printf("%s discards %d bytes received at %s \n",msg.c_str(),msg.size(),time.toString().c_str());
}
