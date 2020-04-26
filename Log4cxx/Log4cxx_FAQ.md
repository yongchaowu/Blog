# log4cxx——third section

## Frequently Asked Technical Questions

### How do I add a custom level to Apache log4cxx?
```
This is a common topic for all the Apache logging frameworks and typically motivated to try to categorize events by functionality or audience. An common request is to add an AUDIT level so that the user can configure AUDIT level messages to go to a specific appender. However, the logger name was designed explicitly to support routing of messages by topic or audience. The common pattern of using classnames for logger names obscures the more general capability of logger name to represent the topic or audience of the logging request. The easiest approach to solve the underlying issue is to use a logger names like "AUDIT.com.example.MyPackage.MyClass" that allow all AUDIT messages to be routed to a particular appender. If you attempted to use a level for that then you would lose the ability to distinguish between different significances within the audit messages.
```
对于所有Apache日志框架来说，这都是一个常见的主题，通常会根据功能或用户对事件进行分类。一个常见的请求是添加一个审计级别，这样用户就可以配置审计级别消息到一个特定的追加器。然而，logger名称被明确设计为支持根据主题或受众路由消息。使用类名作为日志记录器名称的常见模式掩盖了日志记录器名称表示日志记录请求的主题或受众的更一般的功能。解决底层问题的最简单方法是使用诸如“AUDIT.com.example.MyPackage.MyClass”这样的日志程序名称，该名称允许将所有审计消息路由到特定的附加程序。如果您试图为此使用一个级别，那么您将失去在审计消息中区分不同重要性的能力。

### My application on Windows crashes on shutdown?
```
Apache log4cxx API calls use C++ Standard Template Library string parameters. If the caller is using a different instance or type of the C Runtime Library that log4cxx, then it is very likely that some memory that was originally allocated by log4cxx would be freed by the caller. If log4cxx and the caller are using different C RTL's, the program will likely crash at the point. Use "Multithread DLL" with release builds of log4cxx and "Multithread DLL Debug" with debug builds.
```
Apache log4cxx API调用使用c++标准模板库字符串参数。如果调用者使用的是log4cxx的另一个实例或C运行时库的类型，那么很有可能调用者会释放一些最初由log4cxx分配的内存。如果log4cxx和调用者使用的是不同的C RTL，则程序可能会在此时崩溃。在log4cxx的发布版本中使用“多线程DLL”，在调试版本中使用“多线程DLL调试”。

### Does Apache log4cxx support Unicode?
```
Yes. Apache log4cxx exposes API methods in multiple string flavors const char*, std::string, wchar_t*, std::wstring, CFStringRef et al. const char* and std::string are interpreted according to the current locale settings. Applications should call setlocale(LC_ALL, "") on startup or the C RTL will assume US-ASCII. Before being processed internally, all these are converted to the LogString type which is one of several supported Unicode representations selected by the --with-logchar option. When using methods that take LogString arguments, the LOG4CXX_STR() macro can be used to convert ASCII literals to the current LogString type. FileAppenders support an encoding property which should be explicitly specified to "UTF-8" or "UTF-16" for XML files. 
```

是的。Apache log4cxx公开了多种字符串形式的API方法，包括const char*、std::string、wchar_t*、std::wstring、CFStringRef等。应用程序应该在启动时调用setlocale(LC_ALL， "")，否则C RTL将采用US-ASCII。在进行内部处理之前，所有这些都转换为LogString类型，这是—with-logchar选项选择的几种受支持的Unicode表示之一。当使用带有LogString参数的方法时，可以使用LOG4CXX_STR()宏将ASCII文本转换为当前的LogString类型。FileAppenders支持一个编码属性，对于XML文件应该显式地指定为“UTF-8”或“UTF-16”。