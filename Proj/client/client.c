#include "../cpp11netbase/Thread.h"
#include "../cpp11netbase/EventLoop.h"
#include "../cpp11netbase/TcpClient.h"
#include <functional>
#include "../cpp11netbase/TcpConnection.h"
#include "../cpp11netbase/StringPiece.h"
#include <memory>


class MyClient
{
public:
	MyClient(InetAddress Serv,EventLoop *Loop):client(Loop,Serv,"TcpClient"),
			serv(Serv),loop(Loop),msg("this is client! \n")
	{
		client.setConnectionCallback(std::bind(&MyClient::connecback,this,_1));
		client.setMessageCallback(std::bind(&MyClient::messagecallback,this,_1,_2,_3));
	}

	void threadFunc(EventLoop* loop)
	{
		client.connect();
	}
	void connecback(const TcpConnectionPtr& conn)
	{
		conn->send("connecback!\n");
		con = conn;
	}
	void messagecallback(const TcpConnectionPtr& conn,Buffer* buf,Timestamp receiveTime)
	{

		string msg(buf->retrieveAllAsString());
		printf("client rev from serv : %s",msg.c_str());
	}
	void every()
	{
		con->send(msg);
		//printf("con use_count() is : %d\n",con.use_count());
	}
private:
	TcpClient client;
	InetAddress serv;
	EventLoop* loop;
	StringPiece msg;
public:
	TcpConnectionPtr con;
};


void myconnec()
{
	InetAddress serverAddr("127.0.0.1", 2013);
	EventLoop loop;
	
	std::shared_ptr<MyClient> myc = std::make_shared<MyClient>(serverAddr,&loop);
	loop.runAfter(5.0, std::bind(&EventLoop::quit, &loop));	
	printf("Thread create:\n");
	Thread thr(std::bind(&MyClient::threadFunc,myc, &loop));
	thr.start();
	//loop.runEvery(20,std::bind(&MyClient::every,myc));
	loop.loop();

}
int main(int argc, char* argv[])
{
	int i =2000;
	while(i--)
	{
		myconnec();
		sleep(2);
	}
	printf("Thread destroy:\n");
	return 1;
}

