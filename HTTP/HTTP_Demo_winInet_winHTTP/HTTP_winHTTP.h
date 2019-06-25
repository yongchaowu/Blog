#pragma once
#include <windows.h>
#include <winhttp.h>
#include <stdio.h>
#include <string>
#pragma comment(lib, "Winhttp.lib")

#define TRANSFER_SIZE 1024
class HTTP_winHTTP
{
public:
	HTTP_winHTTP();
	~HTTP_winHTTP();


	void testGetFunc();
	void testPostFunc();

	char* wchar2char(const wchar_t* wchar);
	wchar_t* char2wchar(const char* cchar);

};