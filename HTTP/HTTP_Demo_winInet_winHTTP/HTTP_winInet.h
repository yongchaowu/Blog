#pragma once
#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#include <string>
#pragma comment(lib, "WinInet.lib")

#define TRANSFER_SIZE 1024
class HTTP_winInet
{
public:
	HTTP_winInet();
	~HTTP_winInet();


	void testGetFunc();
	void testPostFunc();
};

char* wchar2char(const wchar_t* wchar);
wchar_t* char2wchar(const char* cchar);