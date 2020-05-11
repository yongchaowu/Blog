# HTTP-Attention

## Wininet中
程序中先用InternetQueryDataAvailable()函数查询返回的字节数，然后再利用InternetReadFile()读取字节数，如果 InternetReadFile()读取的总字节数和InternetQueryDataAvailable()查询到的字节数不相等，则认为出错。
这种思路是不正确的。问题就在于InternetQueryDataAvailable()，首先http请求返回的是字节流，假如一个请求先返回30个字节，后再收到70个字节，那么当返回30个字节的时候正好调用了InternetQueryDataAvailable()得到的值也就是30。而接下来调用InternetReadFile()实际却读到了100个字节。这个时候因为二者不相等，所以程序就认为出错了。
这也就是msdn上说的：The amount of data remaining will not be recalculated until all available data indicated by the call to InternetQueryDataAvailable is read.（除非你调用InternetReadFile()后再次调用InternetQueryDataAvailable()才能重新计算可用的数据大小）
   正确的做法是调用HttpQueryInfo()去查询http请求返回的头部中的content-length字段去确定可以读取的字节数
```
WCHAR buf[64] = { 0 };
DWORD dwSizeOfReq = sizeof(buf);
DWORD dwContLen = 0;//需要注意的是，如果适用HttpQueryInfoW，那么buf必须也是宽字符版本，//虽然HttpQueryInfo()之前只是一个缓冲区，因为如果不使用宽字符，//buf得到的字节数可能会因为\0的原因被截断。
if (HttpQueryInfo(m_hHttpRequest, HTTP_QUERY_CONTENT_LENGTH,buf,&dwSizeOfReq, NULL))
	dwContLen = _wtol(buf);
else
	return false;
```

或者在知道http请求一定会返回结果的情况，直接调用InternetReadFile()函数去接收数据，省略先查询收到的字节长度的步骤。 
————————————————
版权声明：本文为CSDN博主「analogous_love」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/analogous_love/java/article/details/72515002