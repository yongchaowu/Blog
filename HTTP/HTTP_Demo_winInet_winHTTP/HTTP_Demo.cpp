// HTTP_Demo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>


#include "HttpConnect.h"

//#include "HTTP_winInet.h"

#include "HTTP_winHTTP.h"


int main()
{
    std::cout << "Hello World!\n";
	
	//-socket
	//HttpConnect* http = new HttpConnect();
	//http->getData("127.0.0.1", "/login", "id=liukang&pw=123");
	//http->postData("127.0.0.1", "/login", "id=liukang&pw=123");

	//-winInet
	//HTTP_winInet* pHTTP_winInet = new HTTP_winInet();
	//pHTTP_winInet->testGetFunc();

	//-winHTTP
	HTTP_winHTTP* pHTTP_winHTTP = new HTTP_winHTTP();
	pHTTP_winHTTP->testGetFunc();
}

