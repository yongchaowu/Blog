# Log4cxx
[Log4cxxx](https://logging.apache.org/log4cxx/latest_stable/index.html)

## How to use log4cxx
[Usage](https://logging.apache.org/log4cxx/latest_stable/usage.html)

### Loggers
```
Log4cxx has three main components: loggers, appenders and layouts. These three types of components work together to enable developers to log messages according to message type and level, and to control at runtime how these messages are formatted and where they are reported.

```

Log4cxx有三个主要组件:loggers、appenders和layouts。这三种类型的组件协同工作，使开发人员能够根据消息类型和级别记录消息，并在运行时控制这些消息的格式和报告位置。

#### Hierarchy
```
The first and foremost advantage of any logging API over plain `std::cout` resides in its ability to disable certain log statements while allowing others to print unhindered. This capability assumes that the logging space, that is, the space of all possible logging statements, is categorized according to some developer-chosen criteria.

Loggers are named entities. Logger names are case-sensitive and they follow the hierarchical naming rule:
```
与普通std::cout相比，任何日志API的首要优势在于它能够禁用某些日志语句，同时允许其他语句不受阻碍地打印。该功能假设日志空间(即所有可能的日志语句的空间)是根据一些开发人员选择的标准进行分类的。
日志记录器是命名的实体。日志记录器的名称是大小写敏感的，它们遵循分层命名规则:

##### Named Hierarchy
```
A logger is said to be an ancestor of another logger if its name followed by a dot is a prefix of the descendant logger name. A logger is said to be a parent of a child logger if there are no ancestors between itself and the descendant logger.
For example, the logger named "com.foo" is a parent of the logger named "com.foo.Bar". Similarly, "java" is a parent of "java.util" and an ancestor of "java.util.Vector". This naming scheme should be familiar to most developers.

The root logger resides at the top of the logger hierarchy. It is exceptional in two ways:
1. it always exists,
2. it cannot be retrieved by name.

Invoking the class static log4cxx::Logger::getRootLogger method retrieves it. All other loggers are instantiated and retrieved with the class static log4cxx::Logger::getLogger method. This method takes the name of the desired logger as a parameter. Some of the basic methods in the Logger class are listed below.
```
如果一个日志记录器的名称后面跟一个点是其后代日志记录器名称的前缀，则该日志记录器被称为另一个日志记录器的祖先。如果在其自身和后代记录器之间没有祖先，则记录器被称为子记录器的父记录器。

根记录器驻留在记录器层次结构的顶部。它在两个方面很特别:
1.它总是存在,
2.无法通过名称检索它。

调用类静态log4cxx::Logger::getRootLogger方法检索它。所有其他日志记录器都是用静态log4cxx::Logger::getLogger方法实例化和检索的。此方法将所需记录器的名称作为参数。下面列出了Logger类中的一些基本方法。

```
    namespace log4cxx {
        class Logger {
            public:
                // Creation & retrieval methods:
                static LoggerPtr getRootLogger();
                static LoggerPtr getLogger(const std::string& name);
                static LoggerPtr getLogger(const std::wstring& name);
        }
    }

    //
    // Use these macros instead of calling Logger methods directly.
    // Macros will handle char or wchar_t pointers or strings
    // or most right-hand side expressions of an
    // std::basic_string::operator<<.
    //
    #define LOG4CXX_TRACE(logger, expression) ...
    #define LOG4CXX_DEBUG(logger, expression) ...
    #define LOG4CXX_INFO(logger, expression) ...
    #define LOG4CXX_WARN(logger, expression) ...
    #define LOG4CXX_ERROR(logger, expression) ...
    #define LOG4CXX_FATAL(logger, expression) ...
```


#### Levels
```
Loggers may be assigned levels. The pre-defined levels: TRACE, DEBUG, INFO, WARN, ERROR and FATAL are defined in the log4cxx::Level class which provides accessor functions.

If a given logger is not assigned a level, then it inherits one from its closest ancestor with an assigned level. More formally:
```
日志记录器可能被分配到不同的级别。预定义的级别:TRACE、DEBUG、INFO、WARN、ERROR和FATAL在log4cxx::Level类中定义，该类提供访问器函数。
如果一个给定的日志记录器没有被分配一个级别，那么它将从最近的祖先那里继承一个级别并分配一个级别。更正式地:

##### Level Inheritance
The inherited level for a given logger C, is equal to the first non-null level in the logger hierarchy, starting at C and proceeding upwards in the hierarchy towards the root logger.
给定logger C的继承级别等于logger层次结构中的第一个非空级别，从C开始，在层次结构中向上直到根logger。

```
To ensure that all loggers can eventually inherit a level, the root logger always has an assigned level.

Below are four tables with various assigned level values and the resulting inherited levels according to the above rule.
Example 1:
| Logger name | Assigned level | Inherited level |
|root |Proot|Inherited level|
|X    |none |Proot|
|X.Y  |none |Proot|
|X.Y.Z|none |Proot|
In example 1 above, only the root logger is assigned a level. This level value, Proot, is inherited by the other loggers X, X.Y and X.Y.Z.

Example 2:
| Logger name | Assigned level | Inherited level |
|root |Proot|Proot|
|X    |Px   |Px   |
|X.Y  |Pxy  |Pxy  |
|X.Y.Z|Pxyz |Pxyz |
In example 2, all loggers have an assigned level value. There is no need for level inheritence.

Example 3:
| Logger name | Assigned level | Inherited level |
|root |Proot|Proot|
|X    |Px   |Px   |
|X.Y  |none |Px   |
|X.Y.Z|Pxyz |Pxyz |
In example 3, the loggers root, X and X.Y.Z are assigned the levels Proot, Px and Pxyz respectively. The logger X.Y inherits its level value from its parent X.

Example 4:
| Logger name | Assigned level | Inherited level |
|root |Proot|Proot|
|X    |Px   |Px   |
|X.Y  |none |Px   |
|X.Y.Z|none |Px   |
In example 4, the loggers root and X and are assigned the levels Proot and Px respectively. The loggers X.Y and X.Y.Z inherits their level value from their nearest parent X having an assigned level.
```
#### Requests
```
Logging requests are made by invoking a method of a logger instance, preferrably through the use of LOG4CXX_INFO or similar macros which support short-circuiting if the threshold is not satisfied and use of the insertion operator (<<) in the message parameter.
```
日志请求是通过调用logger实例的方法发出的，最好是通过使用LOG4CXX_INFO或类似的宏来发出，这些宏支持在阈值不满足时短路，并在消息参数中使用插入操作符(<<)。
```
log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("com.foo"));
const char* region = "World";
LOG4CXX_INFO(logger, "Simple message text.")
LOG4CXX_INFO(logger, "Hello, " << region)
LOG4CXX_DEBUG(logger, L"Iteration " << i)
LOG4CXX_DEBUG(logger, "e^10 = " << std::scientific << exp(10.0))
//
// Use a wchar_t first operand to force use of wchar_t based stream.
//
LOG4CXX_WARN(logger, L"" << i << L" is the number of the iteration.")
```
```
A logging request is said to be enabled if its level is higher than or equal to the level of its logger. Otherwise, the request is said to be disabled. A logger without an assigned level will inherit one from the hierarchy. This rule is summarized below.
```
如果日志记录请求的级别高于或等于其日志记录器的级别，则称为启用日志记录请求。否则，请求将被禁用。没有指定级别的记录器将从层次结构继承一个级别。这一规则概述如下。

##### Basic Selection Rule
```
    A log request of level p in a logger with (either assigned or inherited, whichever is appropriate) level q, is enabled if p >= q.
    This rule is at the heart of log4cxx. It assumes that levels are ordered. For the standard levels, we have TRACE < DEBUG < INFO < WARN < ERROR < FATAL
    Here is an example of this rule.
        // get a logger instance named "com.foo"
        log4cxx::LoggerPtr  logger(log4cxx::Logger::getLogger("com.foo"));

        // Now set its level. Normally you do not need to set the
        // level of a logger programmatically. This is usually done
        // in configuration files.
        logger->setLevel(log4cxx::Level::getInfo());

        log4cxx::LoggerPtr barlogger(log4cxx::Logger::getLogger("com.foo.Bar"));

        // This request is enabled, because WARN >= INFO.
        LOG4CXX_WARN(logger, "Low fuel level.")

        // This request is disabled, because DEBUG < INFO.
        LOG4CXX_DEBUG(logger, "Starting search for nearest gas station.")

        // The logger instance barlogger, named "com.foo.Bar",
        // will inherit its level from the logger named
        // "com.foo" Thus, the following request is enabled
        // because INFO >= INFO.
        LOG4CXX_INFO(barlogger. "Located nearest gas station.")

        // This request is disabled, because DEBUG < INFO.
        LOG4CXX_DEBUG(barlogger, "Exiting gas station search")
```
standard levels：TRACE < DEBUG < INFO < WARN < ERROR < FATAL
```
Calling the getLogger method with the same name will always return a reference to the exact same logger object.
For example, in
	log4cxx::LoggerPtr x = log4cxx::Logger::getLogger("wombat");
	log4cxx::LoggerPtr y = log4cxx::Logger::getLogger("wombat");
x and y refer to exactly the same logger object.
```

```
Thus, it is possible to configure a logger and then to retrieve the same instance somewhere else in the code without passing around references. In fundamental contradiction to biological parenthood, where parents always preceed their children, log4cxx loggers can be created and configured in any order. In particular, a "parent" logger will find and link to its descendants even if it is instantiated after them.
```

因此，可以配置一个日志程序，然后在代码的其他地方检索相同的实例，而不需要传递引用。与生物学上的亲子关系(父母总是先他们的孩子)完全相反，log4cxx日志记录器可以按任何顺序创建和配置。特别是，“父”日志记录器将查找并链接到它的后代，即使它是在它们之后实例化的。
```
Configuration of the log4cxx environment is typically done at application initialization. The preferred way is by reading a configuration file. This approach will be discussed shortly.
```
log4cxx环境的配置通常在应用程序初始化时完成。首选的方法是读取配置文件。稍后将讨论这种方法。

```
Log4cxx makes it easy to name loggers by software component. This can be accomplished by statically instantiating a logger in each class, with the logger name equal to the fully qualified name of the class. This is a useful and straightforward method of defining loggers. As the log output bears the name of the generating logger, this naming strategy makes it easy to identify the origin of a log message. However, this is only one possible, albeit common, strategy for naming loggers. Log4cxx does not restrict the possible set of loggers. The developer is free to name the loggers as desired.

Nevertheless, naming loggers after the class where they are located seems to be the best strategy known so far.
```
Log4cxx使得通过软件组件命名日志记录器变得很容易。这可以通过在每个类中静态实例化一个日志程序来实现，日志程序的名称等于类的完全限定名。这是定义记录器的一种有用且简单的方法。由于日志输出使用生成日志记录器的名称，因此这种命名策略使确定日志消息的来源变得很容易。然而，这只是命名日志记录器的一种可能的(尽管很常见)策略。Log4cxx不限制日志记录器的可能集合。开发人员可以根据需要自由地命名日志记录器。
然而，以它们所在的类来命名日志记录器似乎是迄今为止所知的最佳策略。



#### Appenders and Layouts
```
The ability to selectively enable or disable logging requests based on their logger is only part of the picture. Log4cxx allows logging requests to print to multiple destinations. In log4cxx speak, an output destination is called an appender. Currently, appenders exist for the console, files, GUI components, remote socket servers, NT Event Loggers, and remote UNIX Syslog daemons. It is also possible to log asynchronously.
```
根据日志记录器有选择地启用或禁用日志记录请求的功能只是其中的一部分。Log4cxx允许将日志请求打印到多个目的地。在log4cxx中，输出目的地称为**appender**。目前，控制台、文件、GUI组件、远程套接字服务器、NT事件记录器和远程UNIX Syslog守护进程都有附加程序。还可以异步地进行日志记录。

	More than one appender can be attached to a logger.
可以将多个追加器附加到日志记录器。

```
The addAppender method adds an appender to a given logger. Each enabled logging request for a given logger will be forwarded to all the appenders in that logger as well as the appenders higher in the hierarchy. In other words, appenders are inherited additively from the logger hierarchy. For example, if a console appender is added to the root logger, then all enabled logging requests will at least print on the console. If in addition a file appender is added to a logger, say C, then enabled logging requests for C and C's children will print on a file and on the console. It is possible to override this default behavior so that appender accumulation is no longer additive by setting the additivity flag to false.
```
名为**addAppender**的方法向给定的日志记录器添加一个追加器。**给定日志记录器的每个启用的日志记录请求将被转发给该日志记录器中的所有附加程序以及层次结构中更高的附加程序。**换句话说，附加程序额外地继承自记录器层次结构。例如，如果将控制台追加器添加到根日志记录器，那么所有启用的日志请求至少都将在控制台打印。如果将文件追加器添加到日志记录器(如C)中，则C和C的子节点的启用日志记录请求将打印在文件和控制台上。可以通过将**additivity标记设置为false**来覆盖此默认行为，从而使appender累加不再是可添加的。

	The rules governing appender additivity are summarized below.
有关控制Appender的规则概述如下。

##### Appender Additivity
```
    The output of a log statement of logger C will go to all the appenders in C and its ancestors. This is the meaning of the term "appender additivity". However, if an ancestor of logger C, say P, has the additivity flag set to false, then C's output will be directed to all the appenders in C and it's ancestors up to and including P but, not the appenders in any of the ancestors of P.
    Loggers have their additivity flag set to true by default.
```
logger C的日志语句的输出将传递给C中的所有附加程序及其祖先。这就是“appender additivity”一词的含义。但是，如果日志记录器C的祖先，比如P，将可加性标记设置为false，那么C的输出将被定向到C中的所有追加器，并且它的祖先一直到P并包括P，但不包括P的任何祖先中的追加器。
默认情况下，记录器的可加性标记设置为true。

```
The table below shows an example:

| Logger Name | Added Appenders | Additivity Flag | Output Targets | Comment |
|root |A1       |not applicable|A1                  |The root logger is anonymous but can be accessed with the log4cxx::Logger::getRootLogger() method. There is no default appender attached to root.|
|x    |A-x1,A-x2|true          |A1,A-x1,A-x2        |Appenders of "x" and root.|
|x.y  |none     |true          |A1,A-x1,A-x2        |Appenders of "x" and root.|
|x.y.z|A-xyz1   |true          |A1,A-x1,A-x2,A-xyz1 |Appenders of "x" and root.|
|security|A-sec |false         |A-sec               |No appender accumulation since the additivity flag is set to false.|
|security.access|none |true    |A-sec               |Only appenders of "security" because the additivity flag in "security" is set to false.|
```
```
More often than not, users wish to customize not only the output destination but also the output format. This is accomplished by associating a layout with an appender. The layout is responsible for formatting the logging request according to the user's wishes, whereas an appender takes care of sending the formatted output to its destination.

The PatternLayout, part of the standard log4cxx distribution, lets the user specify the output format according to conversion patterns similar to the C language printf function.

For example, the PatternLayout with the conversion pattern "%r [%t] %-5p %c - %m%n" will output something akin to:
		176 [main] INFO org.foo.Bar - Located nearest gas station.
   The first field is the number of milliseconds elapsed since the start of the program. The second field is the thread making the log request. The third field is the level of the log statement. The fourth field is the name of the logger associated with the log request. The text after the '-' is the message of the statement.
```
通常，用户不仅希望自定义输出目的地，还希望自定义输出格式。这是通过将布局与追加器关联来实现的。布局负责根据用户的愿望对日志请求进行格式化，而appender负责将格式化的输出发送到它的目的地。
PatternLayout是标准log4cxx发行版的一部分，它允许用户根据类似于C语言printf函数的转换模式指定输出格式。
例如，转换模式“%r [%t] %-5p %c - %m%n”的PatternLayout将输出类似于:
	`176 [main] INFO org.foo.Bar - Located nearest gas station.`
第一个字段是程序开始后经过的毫秒数。第二个字段是发出日志请求的线程。第三个字段是log语句的级别。第四个字段是与日志请求关联的日志记录器的名称。“-”后面的文本是该语句的消息。



#### Configuration

```
Inserting log requests into the application code requires a fair amount of planning and effort. Observation shows that approximately 4 percent of code is dedicated to logging. Consequently, even moderately sized applications will have thousands of logging statements embedded within their code. Given their number, it becomes imperative to manage these log statements without the need to modify them manually.
The log4cxx environment is fully configurable programmatically. However, it is far more flexible to configure log4cxx using configuration files. Currently, configuration files can be written in XML or in Java properties (key=value) format.
```

将日志请求插入应用程序代码需要大量的计划和工作。观察表明，大约有4%的代码用于日志记录。因此，即使是中等规模的应用程序也会在其代码中嵌入数千条日志语句。有了它们的数量，就必须管理这些日志语句，而不需要手动修改它们。
log4cxx环境是**完全可编程配置的**。但是，使用配置文件配置log4cxx要灵活得多。目前，配置文件可以用**XML或Java属性(key=value)格式**编写。

Let us give a taste of how this is done with the help of an imaginary application MyApp that uses log4cxx.
```
	#include "com/foo/bar.h"
    using namespace com::foo;

    // include log4cxx header files.
    #include "log4cxx/logger.h"
    #include "log4cxx/basicconfigurator.h"
    #include "log4cxx/helpers/exception.h"

    using namespace log4cxx;
    using namespace log4cxx::helpers;

    LoggerPtr logger(Logger::getLogger("MyApp"));

    int main(int argc, char **argv)
    {
        int result = EXIT_SUCCESS;
        try
        {
            // Set up a simple configuration that logs on the console.
            BasicConfigurator::configure();

            LOG4CXX_INFO(logger, "Entering application.")
            Bar bar;
            bar.doIt();
            LOG4CXX_INFO(logger, "Exiting application.")
        }
        catch(Exception&)
        {
            result = EXIT_FAILURE;
        }

        return result;
    }
```
MyApp begins by including log4cxx headers. It then defines a static logger variable with the name MyApp which happens to be the fully qualified name of the class.
MyApp uses the Bar class defined in header file com/foo/bar.h.
```
    // file com/foo/bar.h
    #include "log4cxx/logger.h"

    namespace com {
        namespace foo {
            class Bar {
                static log4cxx::LoggerPtr logger;

                public:
                    void doIt();
            }
        }
    }
```

```
    // file bar.cpp
    #include "com/foo/bar.h"

    using namespace com::foo;
    using namespace log4cxx;

    LoggerPtr Bar::logger(Logger::getLogger("com.foo.bar"));

    void Bar::doIt() {
        LOG4CXX_DEBUG(logger, "Did it again!")
    }
```
The invocation of the BasicConfigurator::configure method creates a rather simple log4cxx setup. This method is hardwired to add to the root logger a ConsoleAppender. The output will be formatted using a PatternLayout set to the pattern "%-4r [%t] %-5p %c %x - %m%n".

Note that by default, the root logger is assigned to Level::getDebug().

The output of MyApp is:
```
        0    [12345] INFO  MyApp  - Entering application.
        36   [12345] DEBUG com.foo.Bar  - Did it again!
        51   [12345] INFO  MyApp  - Exiting application.
```


The previous example always outputs the same log information. Fortunately, it is easy to modify MyApp so that the log output can be controlled at run-time. Here is a slightly modified version.
```
    // file MyApp2.cpp

    #include "com/foo/bar.h"
    using namespace com::foo;

    // include log4cxx header files.
    #include "log4cxx/logger.h"
    #include "log4cxx/basicconfigurator.h"
    #include "log4cxx/propertyconfigurator.h"
    #include "log4cxx/helpers/exception.h"

    using namespace log4cxx;
    using namespace log4cxx::helpers;
    // Define a static logger variable so that it references the
    // Logger instance named "MyApp".
    LoggerPtr logger(Logger::getLogger("MyApp"));

    int main(int argc, char **argv)
    {
        int result = EXIT_SUCCESS;
        try
        {
            if (argc > 1)
            {
                // BasicConfigurator replaced with PropertyConfigurator.
                PropertyConfigurator::configure(argv[1]);
            }
            else
            {
                BasicConfigurator::configure();
            }

            LOG4CXX_INFO(logger, "Entering application.")
            Bar bar
            bar.doIt();
            LOG4CXX_INFO(logger, "Exiting application.")
        }
        catch(Exception&)
        {
            result = EXIT_FAILURE;
        }

        return result;
    }
```
This version of MyApp instructs **PropertyConfigurator** to parse a configuration file and set up logging accordingly.


Here is a sample configuration file that results in exactly same output as the previous BasicConfigurator based example.
```
    # Set root logger level to DEBUG and its only appender to A1.
    log4j.rootLogger=DEBUG, A1

    # A1 is set to be a ConsoleAppender.
    log4j.appender.A1=org.apache.log4j.ConsoleAppender

    # A1 uses PatternLayout.
    log4j.appender.A1.layout=org.apache.log4j.PatternLayout
    log4j.appender.A1.layout.ConversionPattern=%-4r [%t] %-5p %c %x - %m%n
```
It can be noticed that the PropertyConfigurator file format is the same as log4j.


Suppose we are no longer interested in seeing the output of any component belonging to the com::foo package. The following configuration file shows one possible way of achieving this.
```
    log4j.rootLogger=DEBUG, A1
    log4j.appender.A1=org.apache.log4j.ConsoleAppender
    log4j.appender.A1.layout=org.apache.log4j.PatternLayout

    # Print the date in ISO 8601 format
    log4j.appender.A1.layout.ConversionPattern=%d [%t] %-5p %c - %m%n

    # Print only messages of level WARN or above in the package com.foo.
    log4j.logger.com.foo=WARN
```
The output of MyApp configured with this file is shown below.
```
        2000-09-07 14:07:41,508 [12345] INFO  MyApp - Entering application.
        2000-09-07 14:07:41,529 [12345] INFO  MyApp - Exiting application.
```
As the logger com.foo.Bar does not have an assigned level, it inherits its level from com.foo, which was set to WARN in the configuration file. The log statement from the Bar::doIt method has the level DEBUG, lower than the logger level WARN. Consequently, doIt() method's log request is suppressed.


Here is another configuration file that uses multiple appenders.
```
    log4j.rootLogger=debug, stdout, R

    log4j.appender.stdout=org.apache.log4j.ConsoleAppender
    log4j.appender.stdout.layout=org.apache.log4j.PatternLayout

    # Pattern to output the caller's file name and line number.
    log4j.appender.stdout.layout.ConversionPattern=%5p [%t] (%F:%L) - %m%n

    log4j.appender.R=org.apache.log4j.RollingFileAppender
    log4j.appender.R.File=example.log

    log4j.appender.R.MaxFileSize=100KB
    # Keep one backup file
    log4j.appender.R.MaxBackupIndex=1

    log4j.appender.R.layout=org.apache.log4j.PatternLayout
    log4j.appender.R.layout.ConversionPattern=%p %t %c - %m%n
```
Calling the enhanced MyApp with the this configuration file will output the following on the console.
```
        INFO [12345] (MyApp2.cpp:31) - Entering application.
        DEBUG [12345] (Bar.h:16) - Doing it again!
        INFO [12345] (MyApp2.cpp:34) - Exiting application.
```
In addition, as the root logger has been allocated a second appender, output will also be directed to the example.log file. This file will be rolled over when it reaches 100KB. When roll-over occurs, the old version of example.log is automatically moved to example.log.1.

```
Note that to obtain these different logging behaviors we did not need to recompile code. We could just as easily have logged to a UNIX Syslog daemon, redirected all com.foo output to an NT Event logger, or forwarded logging events to a remote log4cxx server, which would log according to local server policy, for example by forwarding the log event to a second log4cxx server.
```

注意，为了获得这些不同的日志记录行为，我们不需要重新编译代码。我们可以很容易地登录到UNIX Syslog守护进程，重定向所有com.foo输出到NT事件日志记录器，或将日志事件转发到远程log4cxx服务器，后者将根据本地服务器策略进行日志记录，例如通过将日志事件转发到第二个log4cxx服务器。


#### Default Initialization Procedure
```
The log4cxx library does not make any assumptions about its environment. In particular, there are no default log4cxx appenders. Under certain well-defined circumstances however, the static inializer of the Logger class will attempt to automatically configure log4cxx.
The exact default initialization algorithm is defined as follows:

1. Set the configurationOptionStr string variable to the value of the LOG4CXX_CONFIGURATION environment variable if set, otherwise the value of the log4j.configuration or LOG4CXX_CONFIGURATION environment variable if set, otherwise the first of the following file names which exist in the current working directory, "log4cxx.xml", "log4cxx.properties", "log4j.xml" and "log4j.properties". If configurationOptionStr has not been set, then disable logging.

2. Unless a custom configurator is specified using the LOG4CXX_CONFIGURATOR_CLASS or log4j.configuratorClass environment variable, the PropertyConfigurator will be used to configure log4cxx unless the file name ends with the ".xml" extension, in which case the DOMConfigurator will be used. If a custom configurator is specified, the environment variable should contain a fully qualified class name of a class that implements the Configurator interface.
```
log4cxx库没有对其环境做任何假设。特别是，没有默认的log4cxx附加程序。但是，在某些定义良好的情况下，Logger类的静态初始化器将尝试自动配置log4cxx。
精确的默认初始化算法定义如下:

1. 将configurationOptionStr string变量设置为LOG4CXX_CONFIGURATION的值（如果已设置），否则为log4j.CONFIGURATION或LOG4CXX_CONFIGURATION的值（如果已设置），否则为当前工作目录中存在的下列文件名中的第一个，“LOG4CXX.xml”，“LOG4CXX.properties”，“log4j.xml”和“log4j.properties”。如果尚未设置configurationOptionStr，则禁用日志记录。
2. 除非使用LOG4CXX_configurator_类或log4j.configuratorClass环境变量指定自定义配置程序，否则将使用PropertyConfigurator配置LOG4CXX，除非文件名以“.xml”扩展名结尾，在这种情况下将使用DOMConfigurator。如果指定了自定义配置程序，则环境变量应包含实现配置程序接口的类的完全限定类名。

#### Nested Diagnostic Contexts
```
Most real-world systems have to deal with multiple clients simultaneously. In a typical multithreaded implementation of such a system, different threads will handle different clients. Logging is especially well suited to trace and debug complex distributed applications. A common approach to differentiate the logging output of one client from another is to instantiate a new separate logger for each client. This promotes the proliferation of loggers and increases the management overhead of logging.
A lighter technique is to uniquely stamp each log request initiated from the same client interaction. Neil Harrison described this method in the book "Patterns for Logging Diagnostic Messages," in Pattern Languages of Program Design 3, edited by R. Martin, D. Riehle, and F. Buschmann (Addison-Wesley, 1997).
```
大多数实际的系统必须同时处理多个客户机。在这样一个系统的典型多线程实现中，不同的线程将处理不同的客户机。日志记录特别适合跟踪和调试复杂的分布式应用程序。区分一个客户机与另一个客户机的日志输出的一种常见方法是为每个客户机实例化一个新的单独的日志记录器。这促进了日志记录器的增加，并增加了日志的管理开销。
一种较轻的技术是惟一地标记来自相同客户机交互的每个日志请求。Neil Harrison在由R. Martin、D. Riehle和F. Buschmann (Addison-Wesley, 1997)编辑的程序设计模式语言3的《记录诊断消息的模式》一书中描述了这种方法。

    To uniquely stamp each request, the user pushes contextual information into the NDC, the abbreviation of Nested Diagnostic Context. The NDC class is shown below.
为了惟一地标记每个请求，用户将上下文信息推入NDC(嵌套诊断上下文的缩写)。NDC类如下所示。
```
	namespace log4cxx {
        class NDC {
            public:
                // pushes the value on construction and pops on destruction.
                NDC(const std::string& value);
                NDC(const std::wstring& value);

                // Remove the top of the context from the NDC.
                static LogString pop();

                // Add diagnostic context for the current thread.
                static void push(const std::string& message);
                static void push(const std::wstring& message);
        }
    }
```
```
The NDC is managed per thread as a stack of contextual information. Note that all methods of the log4cxx::NDC class are static. Assuming that NDC printing is turned on, every time a log request is made, the appropriate log4cxx component will include the entire NDC stack for the current thread in the log output. This is done without the intervention of the user, who is responsible only for placing the correct information in the NDC by using the push and pop methods at a few well-defined points in the code. In contrast, the per-client logger approach commands extensive changes in the code.
```
每个线程都将NDC作为上下文信息的堆栈进行管理。注意，log4cxx::NDC类的所有方法都是静态的。假设每次发出日志请求时都打开NDC打印，那么相应的log4cxx组件将在日志输出中包含当前线程的整个NDC堆栈。这是在没有用户干预的情况下完成的，用户只负责通过在代码中定义良好的几个点上使用push和pop方法将正确的信息放置到NDC中。相反，每个客户机日志记录器方法要求对代码进行大量更改

```
To illustrate this point, let us take the example of a servlet delivering content to numerous clients. The servlet can build the NDC at the very beginning of the request before executing other code. The contextual information can be the client's host name and other information inherent to the request, typically information contained in cookies. Hence, even if the servlet is serving multiple clients simultaneously, the logs initiated by the same code, i.e. belonging to the same logger, can still be distinguished because each client request will have a different NDC stack. Contrast this with the complexity of passing a freshly instantiated logger to all code exercised during the client's request.
```
为了说明这一点，让我们以servlet为例，将内容交付给许多客户机。servlet可以在请求开始时构建NDC，然后再执行其他代码。上下文信息可以是客户机的主机名和请求固有的其他信息，通常是cookie中包含的信息。因此，即使servlet同时为多个客户端提供服务，由相同代码(即属于同一日志记录器)发起的日志仍然可以区分，因为每个客户端请求将具有不同的NDC堆栈。与此形成对比的是，将新实例化的日志记录器传递给客户机请求期间执行的所有代码的复杂性。

```
Nevertheless, some sophisticated applications, such as virtual hosting web servers, must log differently depending on the virtual host context and also depending on the software component issuing the request. Recent log4cxx releases support multiple hierarchy trees. This enhancement allows each virtual host to possess its own copy of the logger hierarchy.
```
然而，一些复杂的应用程序(如虚拟主机web服务器)必须根据虚拟主机上下文和发出请求的软件组件进行不同的日志记录。最近发布的log4cxx版本支持多个层次结构树。这种增强允许每个虚拟主机拥有自己的日志记录器层次结构的副本。



#### Performance
	One of the often-cited arguments against logging is its computational cost. This is a legitimate concern as even moderately sized applications can generate thousands of log requests. Much effort was spent measuring and tweaking logging performance. Log4cxx claims to be fast and flexible: speed first, flexibility second.
   经常被引用的反对日志记录的理由之一是它的计算成本。这是一个合理的问题，因为即使是中等大小的应用程序也可能生成数千个日志请求。在测量和调整日志记录性能上花费了大量的精力。Log4cxx声称是快速和灵活的:速度第一，灵活性第二。
```
	The user should be aware of the following performance issues.

1. Logging performance when logging is turned off.
    When logging is turned off entirely or just for a set of levels, the cost of a log request consists of a method invocation plus an integer comparison. The LOG4CXX_DEBUG and similar macros suppress unnecessary expression evaluation if the request is not enabled.

2. The performance of deciding whether to log or not to log when logging is turned on.
    This is essentially the performance of walking the logger hierarchy. When logging is turned on, log4cxx still needs to compare the level of the log request with the level of the request logger. However, loggers may not have an assigned level; they can inherit them from the logger hierarchy. Thus, before inheriting a level, the logger may need to search its ancestors.
    There has been a serious effort to make this hierarchy walk to be as fast as possible. For example, child loggers link only to their existing ancestors. In the BasicConfigurator example shown earlier, the logger named com.foo.Bar is linked directly to the root logger, thereby circumventing the nonexistent com or com.foo loggers. This significantly improves the speed of the walk, especially in "sparse" hierarchies.
    The cost of walking the hierarchy is typically 3 times slower than when logging is turned off entirely.

3. Actually outputting log messages
	This is the cost of formatting the log output and sending it to its target destination. Here again, a serious effort was made to make layouts (formatters) perform as quickly as possible. The same is true for appenders.
```
用户应该注意以下性能问题。

1. 关闭日志记录时的日志记录性能。
当日志记录被完全关闭或仅针对一组级别关闭时，日志请求的成本包括方法调用和整数比较。如果没有启用请求，LOG4CXX_DEBUG和类似的宏会抑制不必要的表达式求值。

2. 在打开日志记录时决定是否进行日志记录的性能。
这本质上是遍历logger层次结构的性能。在打开日志记录时，log4cxx仍然需要比较日志请求的级别和请求日志记录器的级别。但是，记录器可能没有指定的级别;它们可以从logger层次结构继承它们。因此，在继承一个级别之前，日志记录器可能需要搜索它的祖先。
有一个认真的努力，使这个层次走得越快越好。例如，子日志记录器仅链接到其现有的祖先。在前面显示的BasicConfigurator示例中，名为com.foo的日志程序。Bar直接链接到根日志记录器，从而绕过不存在的com或com.foo logger。这极大地提高了步行的速度，特别是在“稀疏”层次结构中。
遍历层次结构的成本通常比完全关闭日志记录时慢3倍。

3. 实际上输出日志消息
这是格式化日志输出并将其发送到目标目的地的成本。这里，我们再次认真地努力使布局(格式化程序)尽可能快地执行。对于附加程序也是如此。




#### Conclusions
```
Apache Log4cxx is a popular logging package written in C++. One of its distinctive features is the notion of inheritance in loggers. Using a logger hierarchy it is possible to control which log statements are output at arbitrary granularity. This helps reduce the volume of logged output and minimize the cost of logging.

One of the advantages of the log4cxx API is its manageability. Once the log statements have been inserted into the code, they can be controlled with configuration files. They can be selectively enabled or disabled, and sent to different and multiple output targets in user-chosen formats. The log4cxx package is designed so that log statements can remain in shipped code without incurring a heavy performance cost.
```
Apache Log4cxx是一个用c++编写的流行日志程序包。其独特的特性之一是记录器中的继承概念。使用logger层次结构可以控制以任意粒度输出哪些日志语句。这有助于减少日志输出的数量和最小化日志记录的成本。
log4cxx API的优点之一是它的可管理性。一旦将日志语句插入到代码中，就可以使用配置文件控制它们。它们可以有选择地启用或禁用，并以用户选择的格式发送到不同和多个输出目标。log4cxx包的设计目的是使日志语句可以保留在附带的代码中，而不会导致严重的性能开销。