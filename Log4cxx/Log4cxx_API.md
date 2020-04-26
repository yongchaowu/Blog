# log4cxx——second section
[API](https://logging.apache.org/log4cxx/latest_stable/apidocs/index.html)
---
## 参考链接：

[网上总结1](https://blog.csdn.net/u012632043/article/details/79746573)
版权声明：本文为CSDN博主「大丽在路上」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/u012632043/java/article/details/79746573
## Appenders
- appender常见类

```
org.apache.log4j.ConsoleAppender   (控制台)
org.apache.log4j.FileAppende       (文件)
org.apache.log4j.DailyRollingFileAppender(每天产生一个日志文件)
org.apache.log4j.RollingFileAppender(文件大小达到指定尺寸时产生一个新的文件)
org.apache.log4j.WriterAppender     (将日志信息以流格式发送到任意指定的地方)
```

- apender的使用

```
配置模式:
    log4j.appender.appenderName = className
    log4j.appender.appenderName.Option1 = value1
    ...
    log4j.appender.appenderName.optionN = valueN

使用举例：
	log4j.rootLogger=INFO,stdout
    log4j.appender.stdout=org.apache.log4j.ConsoleAppender
    log4j.appender.stdout.Target=System.out
    log4j.appender.stdout.layout=org.apache.log4j.PatternLayout
    log4j.appender.stdout.layout.ConversionPattern=%d{ABSOLUTE} %5p %c{1}:%L - %m%n
```

- appender类使用时的option解析
	- ConsoleAppender选项
	```
    Threshold = WARN ： 指定日志信息的最低输出级别，默认为DEBUG
    ImmediateFlush = true : 表示所有消息都被立即输出，设为false则不输出， 默认值为true
    Target = System.err : 默认值是System.out
    ```
	- FileAppender选项
	```
    Threshold = WARN
    ImmediateFlush = true
    Append = false : true表示消息增加到指定文件中，false则将消息覆盖指定的文件内容，默认值是true
    File = D:/logs/logging.log4j : 指定消息输出的文件目录名
    ```
    - DailyRollingFileAppender选项
    ```
    Threshold = WARN
    ImmediateFlush = true
    Append = false
    File = D:/logs/logging.log4j
    DatePattern = '.'yyyy-MM : 每个月生成一个新的日志文件
                  '.'yyyy-ww : 每周
                  '.'yyyy-MM-dd:每天
                  '.'yyyy-MM-dd-a:每天2次
                  '.'yyyy-MM-dd-HH：每小时
                  '.'yyyy-MM-dd-HH-mm : 每分钟
    ```
    - RollingFileAppender选项
    ```
    Threshold = WARN
    ImmediateFlush = true
    Append = false
    File = D:/logs/logging.log4j
    MaxFileSize = 100KB ：文件达到该大小时，会自动滚动，即将原来的内容移到logging.log4j.1文件中
    MaxBackupIndex = 2 : 指定可以产生滚动文件的最大数，例如，设为2则可以产生logging.log4j.1, logging.log4j.2两个滚动文件和一个log
	```
## Layouts
- Layouts提供日志输出格式
```
	1. HTML样式 ：  org.apache.log4j.HTMLLayout
	2. 自由指定样式：org.apache.log4j.PatternLayout
	3. 包含日志级别和信息字符串的样式：     org.apache.log4j.SimpleLayout
	4. 包含日志产生的时间、线程、类别等信息：org.apache.log4j.TTCCLayout
```

- layout使用option解析
	- HTMLLayout选项
			LocaltionInfo = true : 输出java文件名和行号，默认值是false
			Title = My Logging : 默认值是Log4j Log Messages
	- PatternLayout选项
			ConversionPattern = %m%n ： 设定以怎样的格式显示消息
	格式化符号说明:
	```
	%p： 输出日志信息的优先级，即DEBUG,INFO,WARN,ERROR,FATAL
	%d： 输出日志时间点的日期或时间，默认格式为ISO8601，也可以指定格式，eg.%d{yyyy/MM/dd HH:mm:ss,SSS}。
	%r： 输出自应用程序启动到输出到该log信息耗费额毫秒数
	%t： 输出产生该日志事件的线程名
	%l:  输出日志事件的发生位置，相当于%c.%M(%F:%L)的组合，包括类全名、方法、文件名及在代码行中的行数。
		 eg.test.TestLog4j.main(TestLog4j.java:10)。
	%c: logger所属类的全名，最小长度是20，若名称长度小于20，默认右对齐。
	%M: 输出产生日志信息的方法名
	%F: 输出日志消息产生时所在的文件名称
	%L: 输出代码中的行号
	%m：输出logger的日志消息，eg.LOG4CXX_DEBUG(m_logger,"日志消息")
	%n：输出一个回车换行符，windows平台为"\r\n",Unix平台为"\n"
	%x: 输出和当前线程相关联的NDC(嵌套诊断环境)，尤其用到像java servlets这样的多客户多线程的应用中
	%%：输出一个"%"字符

	另外，还可以在%与格式字符之间加上修饰符，来控制器最小长度、最大长度、文本对齐方式。如：
	1） %-20c : "-"号表示左对齐
	2） %.30c : 指定%c最大长度为30，若大于30，会将左边多出来的字符截掉，但小于30也不会补空格
	```
## 配置文件详解
-  配置root logger
```
	log4j.rootLogger = [level],appenderName1,appenderName2,...

	**level**： 设定日志记录的最低级别，可设的值有OFF、FATAL、ERROR、WARN、INFO、DEBUG、ALL或者自定义的级别。

	**appenderName**：就是指日志信息要输出到哪里，可以同时指定多个输出目的,用逗号隔开,appenderName可以自定义。
					  eg. log4j.rootLogger＝INFO,A1,B2,C3
```
-----

	log4j.logger.cn.com.Test  = DEBUG,test
	log4j.appender.test=org.apache.log4j.FileAppender
	log4j.appender.test.File=${myweb.root}/WEB-INF/log/test.log
	log4j.appender.test.layout=org.apache.log4j.PatternLayout
	log4j.appender.test.layout.ConversionPattern=%d %p [%c] - %m%n
	这是对名字为cn.com.Test的logger进行配置，从原有日志中分离，形成单独的日志文件。

-  使用多个logger,并配置在一个配置文件
	log4cxx库对日志流设置，只需要更改配置文件中的appender属性
	log4cxx支持Logger继承机制，但由于要将日志流输出到多个文件，需要在配置文件中，将子Logger的继承属性设置为false
	```
	配置文件中配置子Logger:
	// 假设子logger的name为childLogger

	// 在配置文件中定义一个子logger的代码，apname为childlogger使用的appender
	log4j.logger.childLogger = DEBUG,apname     

	// 设置子logger的继承属性设置为false
	log4j.additivity.childLogger = false

	// 设置子logger所使用的日志文件
	log4j.appender.apname.File = ./0.log

	```
-  特别的appender应用
	- 应用于socket
	```
	log4j.appender.socket=org.apache.log4j.RollingFileAppender
	log4j.appender.socket.RemoteHost=localhost
	log4j.appender.socket.Port=5001
	log4j.appender.socket.LocationInfo=true
	```
	- 发送日志到指定邮件
	```
	log4j.appender.mail=org.apache.log4j.net.SMTPAppender
	log4j.appender.mail.Threshold=FATAL
	log4j.appender.mail.BufferSize=10
	log4j.appender.mail.From = xxx@mail.com
	log4j.appender.mail.SMTPHost=mail.com
	log4j.appender.mail.Subject=Log4J Message
	log4j.appender.mail.To= xxx@mail.com
	log4j.appender.mail.layout=org.apache.log4j.PatternLayout
	log4j.appender.mail.layout.ConversionPattern=[%-5p] %d(%r) --> [%t] %l: %m %x %n
	```
	- 应用于数据库
	```
	log4j.appender.database=org.apache.log4j.jdbc.JDBCAppender
	log4j.appender.database.URL=jdbc:mysql://localhost:3306/test
	log4j.appender.database.driver=com.mysql.jdbc.Driver
	log4j.appender.database.user=root
	log4j.appender.database.password=
	log4j.appender.database.sql=INSERT INTO LOG4J (Message) VALUES('=[%-5p] %d(%r) --> [%t] %l: %m %x %n')
	log4j.appender.database.layout=org.apache.log4j.PatternLayout
	log4j.appender.database.layout.ConversionPattern=[%-5p] %d(%r) --> [%t] %l: %m %x %n
	```
	- 自定义Appender
	```
	log4j.appender.im = net.cybercorlin.util.logger.appender.IMAppender
	log4j.appender.im.host = mail.cybercorlin.net
	log4j.appender.im.username = username
	log4j.appender.im.password = password
	log4j.appender.im.recipient = corlin@cybercorlin.net
	log4j.appender.im.layout=org.apache.log4j.PatternLayout
	log4j.appender.im.layout.ConversionPattern=[%-5p] %d(%r) --> [%t] %l: %m %x %n

	```