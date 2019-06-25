#include "HttpConnect.h"
#include <Windows.h>
#include <winsock.h>
#include <sstream>

#ifdef WIN32
#pragma comment(lib,"ws2_32.lib")
#endif


HttpConnect::HttpConnect()
{
#ifdef WIN32
	//此处一定要初始化一下，否则gethostbyname返回一直为空
	WSADATA wsa = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsa);
#endif
}

HttpConnect::~HttpConnect()
{

}
void HttpConnect::socketHttp(std::string& host, std::string& request)
{
	//TiXmlDocument* myDocument_ = new TiXmlDocument();

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;

	address.sin_family = AF_INET;
	address.sin_port = htons(0xBB8);

	struct hostent* server;

	server = gethostbyname(host.c_str());
	memcpy((char*)& address.sin_addr.s_addr, (char*)server->h_addr, server->h_length);

	if (-1 == connect(sockfd, (struct sockaddr*) & address, sizeof(address))) {
		printf("connection error!");
		return;
	}

	printf(request.c_str());

#ifdef WIN32
	send(sockfd, request.c_str(), request.size(), 0);
#else
	write(sockfd, request.c_str(), request.size());
#endif

	//char buf[1024 * 1024] = { 0 };//stack overflow
	char* buf = new char(1024 * 1024);
	int offset = 0;
	int rc;

#ifdef WIN32
	while (rc = recv(sockfd, buf + offset, 1024, 0))
#else
	while (rc = read(sockfd, buf + offset, 1024))
#endif
	{
		offset += rc;
	}

#ifdef WIN32
	closesocket(sockfd);
#else
	close(sockfd);
#endif
	buf[offset] = 0;
	printf(buf);

	return;
	//buf += 202;
	//char* p = new char(1024*1024);// = buf + 202;
	std::string temp = buf;
	temp = temp.substr(202);
	//p = temp.c_str();
	//_memccpy(p, buf, 202, 1024 * 1024 - 202);
	//strncpy(p, buf + 200, 1024);
	///

	TiXmlDocument doc("demotest.xml");
	doc.Parse(temp.c_str());


	TiXmlDocument myDocument;
	//myDocument_->Parse(temp.c_str());
	myDocument.Parse(temp.c_str());

	TiXmlElement* rootElement = myDocument.RootElement();//myDocument_->RootElement();

	if (rootElement)
	{
		TiXmlElement* element = rootElement->FirstChildElement();//rootElement->FirstChildElement();
	}
}

void HttpConnect::postData(std::string host, std::string path, std::string post_content)
{
	//POST请求方式
	std::stringstream stream;
	stream << "POST " << path;
	stream << " HTTP/1.0\r\n";
	stream << "Host: " << host << "\r\n";
	stream << "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n";
	stream << "Content-Type:application/x-www-form-urlencoded\r\n";
	stream << "Content-Length:" << post_content.length() << "\r\n";
	stream << "Connection:close\r\n\r\n";
	stream << post_content.c_str();

	std::string temp = stream.str();
	socketHttp(host, temp);
}

void HttpConnect::getData(std::string host, std::string path, std::string get_content)
{
	//GET请求方式
	std::stringstream stream;
	stream << "GET " << path << "?" << get_content;
	stream << " HTTP/1.0\r\n";
	stream << "Host: " << host << "\r\n";
	stream << "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n";
	stream << "Connection:close\r\n\r\n";

	std::string temp = stream.str();
	try
	{
		socketHttp(host, temp);
	}
	catch (const std::exception& e)
	{
		DWORD t = GetLastError();
		const char* p = e.what();
	}
	
}