#include "HTTP_winHTTP.h"




HTTP_winHTTP::HTTP_winHTTP()
{
}


HTTP_winHTTP::~HTTP_winHTTP()
{
}

void HTTP_winHTTP::testGetFunc()
{
	LPCWSTR lpszAgent = L"WinInetGet/0.1";
	HINTERNET hInternet = WinHttpOpen(lpszAgent, WINHTTP_ACCESS_TYPE_NO_PROXY, NULL, NULL, 0); //初始化WinINet
	if (!hInternet)
	{
		MessageBox(NULL, L"InternetOpen failed!", L"Attention", MB_OK);
		return;
	}

	DWORD errCode = GetLastError();

	LPCWSTR lpszServerName = L"127.0.0.1";
	INTERNET_PORT nServerPort = 3000;// INTERNET_DEFAULT_HTTP_PORT;
	DWORD_PTR dwContext = 0;
	HINTERNET hConnect = WinHttpConnect(hInternet, lpszServerName, nServerPort, 0); //连接服务器
	
	if (!hConnect)
	{
		MessageBox(NULL, L"InternetConnect failed!", L"Attention", MB_OK);
		return;
	}

	errCode = 0;
	errCode = GetLastError();


	LPCWSTR lpszVerb = NULL; //缺省GET
	LPCWSTR lpszObjectName = L"/current";// "/"
	LPCWSTR lpszVersion = NULL;//缺省HTTP/1.0
	LPCWSTR lpszReferrer = WINHTTP_NO_REFERER;//没有引用页
	LPCWSTR FAR* lplpszAcceptTypes = WINHTTP_DEFAULT_ACCEPT_TYPES;// only "text/*"

	HINTERNET hOpenRequest = WinHttpOpenRequest(hConnect, lpszVerb, lpszObjectName, lpszVersion, lpszReferrer,
		lplpszAcceptTypes, 0); //创建http请求  //?INTERNET_FLAG_DONT_CACHE  (LPCWSTR*)"*/*"
	if (!hOpenRequest)
	{
		MessageBox(NULL, L"HttpOpenRequest failed!", L"Attention", MB_OK);
		return;
	}

	errCode = 0;
	errCode = GetLastError();

	LPCWSTR lpszHeaders;
	DWORD dwHeadersLength;
	LPVOID lpOptional;
	DWORD dwOptionalLength;

	BOOL bRequest = WinHttpSendRequest(hOpenRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0); //发送http请求
	//if(!bRequest && GetLastError() == ERROR_INTERNET_INVALID_CA)
	//{
	//	//DWORD dwFlags = 0;
	//	DWORD dwBuffLen = sizeof(dwFlags);

	//	WinHttpQueryOption(hOpenRequest, INTERNET_OPTION_SECURITY_FLAGS, (LPVOID)& dwFlags, &dwBuffLen);
	//	dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;
	//	WinHttpSetOption(hOpenRequest, INTERNET_OPTION_SECURITY_FLAGS, & dwFlags, sizeof(dwFlags));
	//	bRequest = WinHttpSendRequest(hOpenRequest, NULL, 0, NULL, 0); //发送http请求
	//}

	if (!bRequest)
	{
		MessageBox(NULL, L"HttpSendRequest failed!", L"Attention", MB_OK);
		return;
	}

	errCode = 0;
	errCode = GetLastError();

	if (bRequest)
		bRequest = WinHttpReceiveResponse(hOpenRequest, NULL);

	//获得HTTP Response Header信息
	char szBuff[TRANSFER_SIZE] = { '/0' };
	char* pszBuff;
	WCHAR wszBuff[TRANSFER_SIZE];
	DWORD dwReadSize = TRANSFER_SIZE;
	LPWSTR lpOutBuffer = NULL;
	BOOL bResult = FALSE;
	WinHttpQueryHeaders(hOpenRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, NULL, &dwReadSize, WINHTTP_NO_HEADER_INDEX);
	
	// Allocate memory for the buffer.
	if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
	{
		lpOutBuffer = new WCHAR[dwReadSize / sizeof(WCHAR)];

		// Now, use WinHttpQueryHeaders to retrieve the header.
		bResult = WinHttpQueryHeaders(hOpenRequest,
			WINHTTP_QUERY_RAW_HEADERS_CRLF,
			WINHTTP_HEADER_NAME_BY_INDEX,
			(LPVOID)lpOutBuffer, &dwReadSize,
			WINHTTP_NO_HEADER_INDEX);
	}

	// Print the header contents.
	if (bResult)
		printf("Header contents: \n%S", lpOutBuffer);

	if (!bResult)
	{
		MessageBox(NULL, L"HttpQueryInfo failed!", L"Attention", MB_OK);
		return;
	}

	char tt[1024];
	sprintf_s(tt, dwReadSize, "%s", wchar2char(lpOutBuffer));
	printf("%s/n", szBuff);

	//HTTP Response Body
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	LPSTR pszOutBuffer;
	if (bResult)
		do
		{
			// Verify available data.
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hOpenRequest, &dwSize))
				printf("Error %u in WinHttpQueryDataAvailable.\n",
					GetLastError());

			// Allocate space for the buffer.
			pszOutBuffer = new char[dwSize + 1];
			if (!pszOutBuffer)
			{
				printf("Out of memory\n");
				dwSize = 0;
			}
			else
			{
				// Read the Data.
				ZeroMemory(pszOutBuffer, dwSize + 1);

				if (!WinHttpReadData(hOpenRequest, (LPVOID)pszOutBuffer,
					dwSize, &dwDownloaded))
					printf("Error %u in WinHttpReadData.\n", GetLastError());
				else
					printf("%s\n", pszOutBuffer);

				std::string t = pszOutBuffer;
				/*char* tt = new char(1024);
				sprintf_s(tt, dwReadSize, "%s", pszOutBuffer);
				printf("%s/n", szBuff);*/

				// Free the memory allocated to the buffer.
				delete[] pszOutBuffer;
			}

		} while (dwSize > 0);


		// Report any errors.
		if (!bResult)
			printf("Error %d has occurred.\n", GetLastError());

	if(hInternet)
		WinHttpCloseHandle(hInternet);
	if(hConnect)
		WinHttpCloseHandle(hConnect);
	if(hOpenRequest)
		WinHttpCloseHandle(hOpenRequest);
}


void HTTP_winHTTP::testPostFunc()// NEED CHANGE
{
	LPCWSTR lpszAgent = L"WinInetPost/0.1";
	HINTERNET hInternet = WinHttpOpen(lpszAgent, WINHTTP_ACCESS_TYPE_NO_PROXY, NULL, NULL, 0); //初始化WinINet
	if (!hInternet)
	{
		MessageBox(NULL, L"InternetOpen failed!", L"Attention", MB_OK);
		return;
	}

	DWORD errCode = GetLastError();

	LPCWSTR lpszServerName = L"127.0.0.1";
	INTERNET_PORT nServerPort = 3000;// INTERNET_DEFAULT_HTTP_PORT;
	DWORD_PTR dwContext = 0;
	HINTERNET hConnect = WinHttpConnect(hInternet, lpszServerName, nServerPort, 0); //连接服务器

	if (!hConnect)
	{
		MessageBox(NULL, L"InternetConnect failed!", L"Attention", MB_OK);
		return;
	}

	errCode = 0;
	errCode = GetLastError();


	LPCWSTR lpszVerb = L"POST"; //缺省GET
	LPCWSTR lpszObjectName = L"/current";// "/"
	LPCWSTR lpszVersion = NULL;//缺省HTTP/1.0
	LPCWSTR lpszReferrer = WINHTTP_NO_REFERER;//没有引用页
	LPCWSTR FAR* lplpszAcceptTypes = WINHTTP_DEFAULT_ACCEPT_TYPES;// only "text/*"

	HINTERNET hOpenRequest = WinHttpOpenRequest(hConnect, lpszVerb, lpszObjectName, lpszVersion, lpszReferrer,
		lplpszAcceptTypes, 0); //创建http请求  //?INTERNET_FLAG_DONT_CACHE  (LPCWSTR*)"*/*"
	if (!hOpenRequest)
	{
		MessageBox(NULL, L"HttpOpenRequest failed!", L"Attention", MB_OK);
		return;
	}

	errCode = 0;
	errCode = GetLastError();

	LPCWSTR lpszHeaders;
	DWORD dwHeadersLength;
	LPVOID lpOptional;
	DWORD dwOptionalLength;

	BOOL bRequest = WinHttpSendRequest(hOpenRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0); //发送http请求
	//if(!bRequest && GetLastError() == ERROR_INTERNET_INVALID_CA)
	//{
	//	//DWORD dwFlags = 0;
	//	DWORD dwBuffLen = sizeof(dwFlags);

	//	WinHttpQueryOption(hOpenRequest, INTERNET_OPTION_SECURITY_FLAGS, (LPVOID)& dwFlags, &dwBuffLen);
	//	dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;
	//	WinHttpSetOption(hOpenRequest, INTERNET_OPTION_SECURITY_FLAGS, & dwFlags, sizeof(dwFlags));
	//	bRequest = WinHttpSendRequest(hOpenRequest, NULL, 0, NULL, 0); //发送http请求
	//}

	if (!bRequest)
	{
		MessageBox(NULL, L"HttpSendRequest failed!", L"Attention", MB_OK);
		return;
	}

	errCode = 0;
	errCode = GetLastError();

	if (bRequest)
		bRequest = WinHttpReceiveResponse(hOpenRequest, NULL);

	//获得HTTP Response Header信息
	char szBuff[TRANSFER_SIZE] = { '/0' };
	char* pszBuff;
	WCHAR wszBuff[TRANSFER_SIZE];
	DWORD dwReadSize = TRANSFER_SIZE;
	LPVOID lpOutBuffer = NULL;
	BOOL bResult = FALSE;
	WinHttpQueryHeaders(hOpenRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, NULL, &dwReadSize, WINHTTP_NO_HEADER_INDEX);

	// Allocate memory for the buffer.
	if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
	{
		lpOutBuffer = new WCHAR[dwReadSize / sizeof(WCHAR)];

		// Now, use WinHttpQueryHeaders to retrieve the header.
		bResult = WinHttpQueryHeaders(hOpenRequest,
			WINHTTP_QUERY_RAW_HEADERS_CRLF,
			WINHTTP_HEADER_NAME_BY_INDEX,
			lpOutBuffer, &dwReadSize,
			WINHTTP_NO_HEADER_INDEX);
	}

	// Print the header contents.
	if (bResult)
		printf("Header contents: \n%S", lpOutBuffer);

	if (!bResult)
	{
		MessageBox(NULL, L"HttpQueryInfo failed!", L"Attention", MB_OK);
		return;
	}

	char tt[1024];
	sprintf_s(tt, dwReadSize, "%s", lpOutBuffer);
	printf("%s/n", szBuff);

	//HTTP Response Body
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	LPSTR pszOutBuffer;
	if (bResult)
		do
		{

			// Verify available data.
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hOpenRequest, &dwSize))
				printf("Error %u in WinHttpQueryDataAvailable.\n",
					GetLastError());

			// Allocate space for the buffer.
			pszOutBuffer = new char[dwSize + 1];
			if (!pszOutBuffer)
			{
				printf("Out of memory\n");
				dwSize = 0;
			}
			else
			{
				// Read the Data.
				ZeroMemory(pszOutBuffer, dwSize + 1);

				if (!WinHttpReadData(hOpenRequest, (LPVOID)pszOutBuffer,
					dwSize, &dwDownloaded))
					printf("Error %u in WinHttpReadData.\n", GetLastError());
				else
					printf("%s\n", pszOutBuffer);

				// Free the memory allocated to the buffer.
				delete[] pszOutBuffer;
			}

		} while (dwSize > 0);


		// Report any errors.
		if (!bResult)
			printf("Error %d has occurred.\n", GetLastError());

		if (hInternet)
			WinHttpCloseHandle(hInternet);
		if (hConnect)
			WinHttpCloseHandle(hConnect);
		if (hOpenRequest)
			WinHttpCloseHandle(hOpenRequest);
}

char* HTTP_winHTTP::wchar2char(const wchar_t* wchar)
{
	char* m_char;
	int len = WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), NULL, 0, NULL, NULL);
	m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	return m_char;
}

wchar_t* HTTP_winHTTP::char2wchar(const char* cchar)
{
	wchar_t* m_wchar;
	int len = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);
	m_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);
	m_wchar[len] = '\0';
	return m_wchar;
}
