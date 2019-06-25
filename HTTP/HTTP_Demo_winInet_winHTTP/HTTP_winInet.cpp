#include "HTTP_winInet.h"




HTTP_winInet::HTTP_winInet()
{
}


HTTP_winInet::~HTTP_winInet()
{
}

void HTTP_winInet::testGetFunc()
{
	LPCWSTR lpszAgent = L"WinInetGet/0.1";
	HINTERNET hInternet = InternetOpen(lpszAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0); //初始化WinINet
	if (!hInternet)
	{
		MessageBox(NULL, L"InternetOpen failed!", L"Attention", MB_OK);
		return;
	}

	DWORD errCode = GetLastError();

	LPCWSTR lpszServerName = L"127.0.0.1";
	INTERNET_PORT nServerPort = 3000;// INTERNET_DEFAULT_HTTP_PORT;
	LPCWSTR lpszUserName = NULL;
	LPCWSTR lpszPassword = NULL;
	DWORD dwService = INTERNET_SERVICE_HTTP;
	//DWORD dwFlags = 0;
	DWORD_PTR dwContext = 0;
	HINTERNET hConnect = InternetConnect(hInternet, lpszServerName, nServerPort, lpszUserName, lpszPassword, INTERNET_SERVICE_HTTP, 0, dwContext); //连接服务器
	
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
	LPCWSTR lpszReferrer = NULL;//没有引用页
	LPCWSTR FAR* lplpszAcceptTypes = NULL;// only "text/*"
	DWORD dwFlags = INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP | 
		INTERNET_FLAG_KEEP_CONNECTION |
		INTERNET_FLAG_NO_AUTH |
		INTERNET_FLAG_NO_COOKIES |
		INTERNET_FLAG_NO_UI;
		//设置启用HTTPS
		//INTERNET_FLAG_SECURE |
		//INTERNET_FLAG_IGNORE_CERT_CN_INVALID |
		//INTERNET_FLAG_IGNORE_CERT_DATE_INVALID |
		//INTERNET_FLAG_RELOAD;
	//DWORD_PTR dwContext = 0;;

	HINTERNET hOpenRequest = HttpOpenRequest(hConnect, lpszVerb, lpszObjectName, lpszVersion, lpszReferrer,
		lplpszAcceptTypes, dwFlags, dwContext); //创建http请求  //?INTERNET_FLAG_DONT_CACHE  (LPCWSTR*)"*/*"
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

	BOOL bRequest = HttpSendRequest(hOpenRequest, NULL, 0, NULL, 0); //发送http请求
	if(!bRequest && GetLastError() == ERROR_INTERNET_INVALID_CA)
	{
		//DWORD dwFlags = 0;
		DWORD dwBuffLen = sizeof(dwFlags);

		InternetQueryOption(hOpenRequest, INTERNET_OPTION_SECURITY_FLAGS, (LPVOID)& dwFlags, &dwBuffLen);
		dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;
		InternetSetOption(hOpenRequest, INTERNET_OPTION_SECURITY_FLAGS, & dwFlags, sizeof(dwFlags));
		bRequest = HttpSendRequest(hOpenRequest, NULL, 0, NULL, 0); //发送http请求
	}

	if (!bRequest)
	{
		MessageBox(NULL, L"HttpSendRequest failed!", L"Attention", MB_OK);
		return;
	}

	errCode = 0;
	errCode = GetLastError();

	//获得HTTP Response Header信息
	char szBuff[TRANSFER_SIZE] = { '/0' };
	char* pszBuff;
	WCHAR wszBuff[TRANSFER_SIZE];
	DWORD dwReadSize = TRANSFER_SIZE;
	BOOL bResult = HttpQueryInfo(hOpenRequest, HTTP_QUERY_RAW_HEADERS_CRLF, wszBuff, &dwReadSize, NULL);
	pszBuff = wchar2char(wszBuff);

	if (!bResult)
	{
		MessageBox(NULL, L"HttpQueryInfo failed!", L"Attention", MB_OK);
		return;
	}
	szBuff[dwReadSize] = '/0';
	std::string t = szBuff;
	char tt[1024];
	sprintf_s(tt, dwReadSize, "%s", szBuff);
	printf("%s/n", szBuff);

	//HTTP Response Body
	DWORD dwBytesAvailable;
	bResult = InternetQueryDataAvailable(hOpenRequest, &dwBytesAvailable, 0, 0);
	if (!bResult)
	{
		MessageBox(NULL, L"InternetQueryDataAvailable failed!", L"Attention", MB_OK);
		return;
	}

	if (dwBytesAvailable > TRANSFER_SIZE)
	{
		MessageBox(NULL, L"HttpQueryInfo too long!", L"Attention", MB_OK);
		int t = GetLastError();
		return;
	}

	DWORD dwBytesRead;
	bResult = InternetReadFile(hOpenRequest, szBuff, dwBytesAvailable, &dwBytesRead);
	if (!bResult)
	{
		MessageBox(NULL, L"InternetReadFile failed!", L"Attention", MB_OK);
		return;
	}
	szBuff[dwBytesRead] = '/0';
	t = szBuff;
	printf("%s/n", szBuff);

	if(hInternet)
		InternetCloseHandle(hInternet);
	if(hConnect)
		InternetCloseHandle(hConnect);
	if(hOpenRequest)
		InternetCloseHandle(hOpenRequest);
}


void HTTP_winInet::testPostFunc()
{
	LPCWSTR lpszAgent = L"WinInetGet/0.1";
	HINTERNET hInternet = InternetOpen(lpszAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0); //初始化WinINet
	if (!hInternet)
	{
		MessageBox(NULL, L"InternetOpen failed!", L"Attention", MB_OK);
		return;
	}

	DWORD errCode = GetLastError();

	LPCWSTR lpszServerName = L"127.0.0.1";
	INTERNET_PORT nServerPort = 3000;// INTERNET_DEFAULT_HTTP_PORT;
	LPCWSTR lpszUserName = NULL;
	LPCWSTR lpszPassword = NULL;
	DWORD dwService = INTERNET_SERVICE_HTTP;
	//DWORD dwFlags = 0;
	DWORD_PTR dwContext = 0;
	HINTERNET hConnect = InternetConnect(hInternet, lpszServerName, nServerPort, lpszUserName, lpszPassword, INTERNET_SERVICE_HTTP, 0, dwContext); //连接服务器

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
	LPCWSTR lpszReferrer = NULL;//没有引用页
	LPCWSTR FAR* lplpszAcceptTypes = NULL;// only "text/*"
	DWORD dwFlags = INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |
		INTERNET_FLAG_KEEP_CONNECTION |
		INTERNET_FLAG_NO_AUTH |
		INTERNET_FLAG_NO_COOKIES |
		INTERNET_FLAG_NO_UI;
	//设置启用HTTPS
	//INTERNET_FLAG_SECURE |
	//INTERNET_FLAG_IGNORE_CERT_CN_INVALID |
	//INTERNET_FLAG_IGNORE_CERT_DATE_INVALID |
	//INTERNET_FLAG_RELOAD;
//DWORD_PTR dwContext = 0;;

	HINTERNET hOpenRequest = HttpOpenRequest(hConnect, lpszVerb, lpszObjectName, lpszVersion, lpszReferrer,
		lplpszAcceptTypes, dwFlags, dwContext); //创建http请求  //?INTERNET_FLAG_DONT_CACHE  (LPCWSTR*)"*/*"
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

	char szHeaderBuff[TRANSFER_SIZE] = { '/0' };
	int nHeaderSize = sprintf_s(szHeaderBuff, "%s", "Content-Type:application/x-www-form-urlencoded");
	char szReqBuff[TRANSFER_SIZE] = { '/0' };
	int szReqSize = sprintf_s(szReqBuff ,"user=%s&pass=%s", "test", "test");

	BOOL bRequest = HttpSendRequest(hOpenRequest, char2wchar(szHeaderBuff), nHeaderSize, szReqBuff, szReqSize); //发送http请求
	if (!bRequest && GetLastError() == ERROR_INTERNET_INVALID_CA)
	{
		//DWORD dwFlags = 0;
		DWORD dwBuffLen = sizeof(dwFlags);

		InternetQueryOption(hOpenRequest, INTERNET_OPTION_SECURITY_FLAGS, (LPVOID)& dwFlags, &dwBuffLen);
		dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;
		InternetSetOption(hOpenRequest, INTERNET_OPTION_SECURITY_FLAGS, &dwFlags, sizeof(dwFlags));
		bRequest = HttpSendRequest(hOpenRequest, char2wchar(szHeaderBuff), nHeaderSize, szReqBuff, szReqSize); //发送http请求
	}

	if (!bRequest)
	{
		MessageBox(NULL, L"HttpSendRequest failed!", L"Attention", MB_OK);
		return;
	}

	errCode = 0;
	errCode = GetLastError();

	//获得HTTP Response Header信息
	char szBuff[TRANSFER_SIZE];
	DWORD dwReadSize = TRANSFER_SIZE;
	BOOL bResult = HttpQueryInfo(hOpenRequest, HTTP_QUERY_RAW_HEADERS_CRLF, szBuff, &dwReadSize, NULL);
	if (!bResult)
	{
		MessageBox(NULL, L"HttpQueryInfo failed!", L"Attention", MB_OK);
		return;
	}
	szBuff[dwReadSize] = '/0';
	std::string t = szBuff;
	char tt[1024];
	sprintf_s(tt, dwReadSize, "%s", szBuff);
	printf("%s/n", szBuff);

	//HTTP Response Body
	DWORD dwBytesAvailable;
	bResult = InternetQueryDataAvailable(hOpenRequest, &dwBytesAvailable, 0, 0);
	if (!bResult)
	{
		MessageBox(NULL, L"InternetQueryDataAvailable failed!", L"Attention", MB_OK);
		return;
	}

	if (dwBytesAvailable > TRANSFER_SIZE)
	{
		MessageBox(NULL, L"HttpQueryInfo too long!", L"Attention", MB_OK);
		int t = GetLastError();
		return;
	}

	DWORD dwBytesRead;
	bResult = InternetReadFile(hOpenRequest, szBuff, dwBytesAvailable, &dwBytesRead);
	if (!bResult)
	{
		MessageBox(NULL, L"InternetReadFile failed!", L"Attention", MB_OK);
		return;
	}
	szBuff[dwBytesRead] = '/0';
	t = szBuff;
	printf("%s/n", szBuff);

	if (hInternet)
		InternetCloseHandle(hInternet);
	if (hConnect)
		InternetCloseHandle(hConnect);
	if (hOpenRequest)
		InternetCloseHandle(hOpenRequest);
}

char* wchar2char(const wchar_t* wchar)
{
	char* m_char;     
	int len = WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), NULL, 0, NULL, NULL);    
	m_char = new char[len + 1];     
	WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), m_char, len, NULL, NULL);
	m_char[len] = '\0';     
	return m_char;
}

wchar_t* char2wchar(const char* cchar) 
{
	wchar_t* m_wchar;     
	int len = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);     
	m_wchar = new wchar_t[len + 1];     
	MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);     
	m_wchar[len] = '\0';    
	return m_wchar; 
}
