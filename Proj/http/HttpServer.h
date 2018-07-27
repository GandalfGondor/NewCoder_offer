#ifndef MUDUO_NET_HTTP_HTTPSERVER_H
#define MUDUO_NET_HTTP_HTTPSERVER_H

#include "../cpp11netbase/TcpServer.h"


class HttpRequest;
class HttpResponse;

class HttpServer : noncopyable
{
public:
	typedef std::function<void (const HttpRequest&,
		              HttpResponse*)> HttpCallback;

	HttpServer(EventLoop* loop,
	     const InetAddress& listenAddr,
	     const string& name,
	     TcpServer::Option option = TcpServer::kNoReusePort);

	EventLoop* getLoop() const { return server_.getLoop(); }

	/// Not thread safe, callback be registered before calling start().
	void setHttpCallback(const HttpCallback& cb)
	{
		httpCallback_ = cb;
	}

	void setThreadNum(int numThreads)
	{
		server_.setThreadNum(numThreads);
	}

	void start();

private:

	void onConnection(const TcpConnectionPtr& conn);
	void onMessage(const TcpConnectionPtr& conn,
		 Buffer* buf,
		 Timestamp receiveTime);
	void onRequest(const TcpConnectionPtr&, const HttpRequest&);

	TcpServer server_;
	HttpCallback httpCallback_;
};

#endif 
