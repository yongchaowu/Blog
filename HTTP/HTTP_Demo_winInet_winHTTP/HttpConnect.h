#pragma once

#include <string>

#include "./tinyxml_2_6_2/tinyxml/tinyxml.h"
#include "./tinyxml_2_6_2/tinyxml/tinystr.h"

class HttpConnect
{
public:
	HttpConnect();
	~HttpConnect();

	void postData(std::string host, std::string path, std::string post_content);
	void getData(std::string host, std::string path, std::string get_content);
private:
	void socketHttp(std::string& host, std::string& request);
public:
	int sockfd;
};

