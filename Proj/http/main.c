#include "HttpServer.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "../cpp11netbase/EventLoop.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream> 
#include <string>
char favicon[555]="favicon";
bool benchmark = false;

// 实际的请求处理
void onRequest(const HttpRequest &req, HttpResponse *resp)
{
	printf("%s              !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",req.path().c_str());
	//std::cout << "Headers " << req.methodString() << " " << req.path() << std::endl;
	if (!benchmark)
	{
		const std::map<string, string> &headers = req.headers();
		for (std::map<string, string>::const_iterator it = headers.begin();
			it != headers.end(); ++it)
		{
			//std::cout << it->first << ": " << it->second << std::endl;
		}
	}

	if (req.path() == "/")
	{
		std::ifstream t("MyServ2.html");
		string body((std::istreambuf_iterator<char>(t)),
                		std::istreambuf_iterator<char>());
		resp->setStatusCode(HttpResponse::k200Ok);
		resp->setStatusMessage("OK");
		resp->setContentType("text/html");
		resp->addHeader("Server", "MiniMuduoHttpServ");
		string now = Timestamp::now().toFormattedString();
		resp->setBody(body);
	}
	if (req.path() == "/?wd=")
	{
		std::ifstream t("MyServ.html");
		string body((std::istreambuf_iterator<char>(t)),
                		std::istreambuf_iterator<char>());
		resp->setStatusCode(HttpResponse::k200Ok);
		resp->setStatusMessage("OK");
		resp->setContentType("text/html");
		resp->addHeader("Server", "MiniMuduoHttpServ");
		string now = Timestamp::now().toFormattedString();
		resp->setBody(body);
	}
	else if (req.path() == "/favicon.ico")
	{
		resp->setStatusCode(HttpResponse::k404NotFound);
		resp->setStatusMessage("NOT");
		//resp->setContentType("image/png");
		//resp->setBody(string(favicon, sizeof favicon));
	}
	else if (req.path() == "/parper")
	{
		resp->setStatusCode(HttpResponse::k200Ok);
		resp->setStatusMessage("OK");
		resp->setContentType("text/html");
		resp->addHeader("Server", "MiniMuduoHttpServ");
		string body = "<!DOCTYPE html><html><head><meta charset=\"utf-8\"><title>MY_HTTP_SERVER</title></head><body><h1>我的标题</h1><p>第一段。</p></body></html>";
		resp->setBody(body);
	}
	else if(req.path() == "/login")
	{
		resp->setStatusCode(HttpResponse::k200Ok);
		resp->setStatusMessage("OK");
		resp->setContentType("text/html");
		resp->addHeader("Server","Wc");
		string body = "<body><form name=\"form_1\" action=\"/cgi-bin/post.cgi\" method=\"post\"><table align=\"center\"><tr><td align=\"center\" colspan=\"2\"></td></tr><tr><td align=\"right\">username</td><td><input type=\"text\" name=\"Username\"></td> </tr><tr><td align=\"right\">password</td><td><input type=\"password\" name=\"Password\"></td></tr><tr><td><input type=\"submit\" value=\login></td><td><input type=\"reset\" value=\"cancel\"></td></tr></table></form></body>";
		resp->setBody(body);
	}
	else
	{
		resp->setStatusCode(HttpResponse::k404NotFound);
		resp->setStatusMessage("Not Found");
		resp->setCloseConnection(true);
	}
}

int main(int argc, char *argv[])
{
	int numThreads = 0;
	if (argc > 1)
	{
		benchmark = true;
		numThreads = atoi(argv[1]);
	}
	EventLoop loop;
	InetAddress ad("127.0.0.1",2000);
	HttpServer server(&loop, ad, "dummy");

	server.setHttpCallback(onRequest);
	server.setThreadNum(numThreads);
	server.start();
	loop.loop();
}

