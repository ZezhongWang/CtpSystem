#知识点

1. 内存的几大区域：
    - 栈区  
        * 编译器自动分配并且释放,存放函数的参数值,局部变量等
    - 堆区  
        * 由程序员分配和释放,主要存放new构造的对象和数组.只要是new出来的对象,就需要delete来销毁
    - 全局区（静态区）
        * 用来存放全局变量和静态变量,程序结束后由系统释放
    - 文字常量区
        * 存放常量字段,程序结束后由系统释放
    - 代码区
        * 存放函数的二进制代码

2. const char* | char const* | char *const | const char[] 的区别：
    - const char* = char const*: 指针指向可以改变,而字符串内容不可以改变
    - char *const: 字符串内容可以改变,而指针指向不可以改变
    - const char []: 字符串的内容和指向都不可以改变(只有这种方式可以在头文件中书写)

3. TCP是全双工的协议，就是客户端在给服务端发信息的同时，服务端也可以给客户端发送信息。三次握手  
    保证双方都能够收到对方的信息，并且避免因为超时重传或者丢包的情况而建立多个TCP连接。四次挥手
    保证服务端数据已经传输完成才结束。
   
4. CMake Error: Cannot determine link language for target  
    SET(CTP_TD_SRCS td) set变量的时候指定目录而没有到具体文件，导致编译器不知道要采用什么语言编译
    
5. 只登录一次，一个启动，作为服务。再启动另外一个层次
    共享内存，tcp socket，
    
6. 进程间通信的方式
    - 管道（半双工，数据只能向一个方向流动）
        + 分为命名管道和无名管道。命名管道有个名字，有了这个文件名任何进程都有相应的权限可以对它进行访问（通过mknod()或makefifo（）来创建）
        + 无名管道只能访问自己或祖先创建的管道（通过pipe(pipe_fd)创建）
    - 共享内存（效率高，只需要进行两次数据拷贝，且只是在用户空间的拷贝，而管道和消息队列则需要进行4次数据拷贝，多了两次需要从进程读写到内核）
    - socket
    - 信号（Shell中发送的Ctrl+C等指令就是通过信号来传输的）
    - 消息队列
7. 多态，虚函数的实现原理：
    编译器了解继承层次结构之后，知道Base定义了虚函数，并且在Derived类中覆盖了这些函数。这种情况下编译器会为为基类和派生类分别创建一个虚函数表（VFT），实例化这些对象的时候，将创建一个隐藏的指针VFT*，指向对应的VFT。VFT可视为一个包含函数指针的静态数组，每个指针都指向对应的虚函数。
8. 同步与异步
    同步IO与异步IO的区别就在于：数据拷贝的时候进程是否阻塞
    - 同步。就是在发出一个功能调用时，在没有得到结果只前，该调用就不返回。就是事情必须一件一件做，等前一件事做完之后才能做下一件事
        同步，就是我调用一个功能，该功能没有结束之前我就死等结果
    - 异步。异步过程调用发出后，调用者不会立刻得到结果。
        异步，就是我调用一个功能，不需要知道该功能结果，该功能有结果之后通知我（回调通知）
    
9. 阻塞与非阻塞
    阻塞IO与非阻塞IO的区别在于：应用程序的调用是否立即返回
    阻塞与非阻塞与同步和异步概念不同。阻塞与非阻塞关注的是线程有没有被挂起，而同步调用很多时候线程韩式
    - 阻塞。就是调用结果返回之前，当前线程就会被挂起。如socket接收函数recv就是一个例子，如果缓冲区没有数据，函数就会一直等待，直到有数据才返回，cpu不会给线程分配时间片
    - 非阻塞。 指不能立刻得到结果之前，该函数不会阻塞当前线程。阻塞对象可以通过轮询的调用方式编程一个非阻塞式。select就是一个例子，反复调用API检查，
    会大量占用CPU时间

10. select、poll、epoll区别
    都是IO多路复用的机制，可以监听多个文件描述符（fd， file description）。一旦某个描述符就绪（通常为读写），能够通知程序进行相应的读写操作。本质上都是同步IO，因为都需要在读写事件就绪后自己负责读写，也就是说这个读写的过程是阻塞的。
    但select, poll, epoll本质上都是同步IO，因为他们都需要在读写事件就绪后自己负责读写，整个读写过程是阻塞的。
    select: 每次调用select,都需要把fd集合从用户态拷贝到内核态，这个开销在fd很多的时候会很大。每次调用select需要遍历所有fd，select支持的文件描述符数量有上限
    poll: 与select基本没有区别，但是没有最大文件描述符数量的限制。文件描述符的数组被整体复制于用户态和内核的地址空间之间。
    epoll: 对select、poll的改进，能够避免上述三个确定。提供三个函数epoll_create, epoll_ctl和epoll_wait。
      对于第一个缺点，epoll解决方案在epoll_ctl函数中，每次注册的新事件，会把所有的fd拷贝到内核，确保每个fd在整个过程中只会拷贝一次。
      对于第二个缺点，不像select或者poll一样每一次都把current轮流加入fd对应的设备等待队列中，而只在epoll_ctl时把current挂一遍，并未每个fd指定一个回调函数，
        当设备就绪时，唤醒等待队列上的等待者时，就会调用这个回调函数，而这个回调函数会把就绪的fd加入一个就绪链表。epoll_wait实际上就是在这个就绪链表中查看有没有就绪的fd
      对于第三个缺点，epoll没有打开fd数量的上限。
11. Linux标准文件描述符
    文件描述符   缩写  描述
    0       STDIN   标准输入
    1       STDOUT  标准输出
    2       STDERR  标准错误输出
    例如输入输出重定向：
        exec 1> out.txt // 将标准输出的位置改到out.txt中
    文件描述符是一个简单的整数，用以标明每一个被进程所打开的文件和socket。Unix操作系统通常会给每一进程能打开的文件数量加以限制。

12. IO多路复用
    是指一旦发现进程指定的一个或者多个IO条件准备读取，它就通知该进程。使用场合：
    - 当客户处理多个描述字的时候
    - TCP服务器既要处理监听套接口，又要处理已连接套接口
    - 服务器既要处理TCP，又要处理UDP
    - 服务器要处理多个服务或多个协议
    *优势：系统开销小，不必创建维护进程/线程，减少系统开销*

13. select函数
        
        int select(int maxfdp1,fd_set *readset,fd_set *writeset,fd_set *exceptset,const struct timeval *timeout)
        return:
            就绪描述符的个数，超时返回0,出错返回-1
        Parameters:
        - maxfdp1 指定待测试的描述符个数，值是待测试的最大描述字+1,描述字0,1,2...maxfdp1-1均被测试
        - readset, writeset, exceptset
        指定我们要让内核测试读、写和异常条件的描述字。可设置为空指针
        struct fd_set 是一个存放着fd的集合，可以通过一下四个宏进行设置：
        void FD_ZERO(fd_set *fdset); //清空集合
        void FD_SET(int fd, fd_set *fdset); //将一个文件描述符加入集合之中
        void FD_CLR(int fd, fd_set *fdset); //将一个给定的文件描述符从集合中删除
        int FD_ISSET(int fd, fd_set *fdset); //检查集合中指定的文件描述符是否可以读写
        - timeout
        告知内核等待所指定描述字中的任何一个就绪可话多少之间，可用于指定这段时间的描述和微秒数。
        struct timeval{
            long tv_sec; //seconds
            long tv_usec; //microseconds
        }
        这个参数有三种可能：
        (1) 永远等待下去：仅有一个描述字准备好I/O时才返回。设置为NULL
        (2) 等待一段固定时间：在有一个描述字准备好I/O时才返回，但是不超过timeval
        (3) 不等待： 设置为0

    原理图：https://images2015.cnblogs.com/blog/305504/201509/305504-20150918012828961-1176245587.png

14. static 关键字作用
    - 隐藏。 加了static前缀的全局变量或者函数对其他源文件隐藏
    - 保持变量持久。两种变量存储在静态变量区：全局变量和static变量。全局变量和static变量的区别主要在作用域上
    - 默认初始化为0. 
    - 类成员声明为static。类的静态函数属于整个类而不是类的对象，所以它没有this指针，导致了它仅能访问类的静态数据和静态成员变量
   
15. Linux下的五种IO模型
    - 阻塞IO blocking I/O     -线程挂起
    - 非阻塞IO nonblocking I/O     -反复调用API并迅速返回，占用CPU
    - IO复用(select和poll)  IO multiplexing    -select、poll、epoll，可以同时阻塞多个IO操作，性能上比阻塞IO没有什么优越性  
    ，关键是能够实现同时对多个IO进行监听;
    - 信号驱动IO    signal driven IO    -当数据准备好时，进程会收到一个SIGIO信号，可以在信号处理函数中调用IO操作函数处理数据
    - 异步IO  asynchronous IO     =数据拷贝的时候无需阻塞
    前4种都是同步，只有最后一种才是异步IO
    
16. epoll总结  

        #include <sys/epoll.h>
        int epoll_create(int size);
        int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
        int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
    
    (1) int epoll_create(int size)
        创建一个epoll句柄，size用来告诉内核这个监听的数目一共有多大。创建好epoll句柄之后，它会占用一个fd值
    (2) int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
        epoll的事件注册函数，它不同于select()是在监听事件时告诉内核要监听什么类型的事件，而是先注册要监听的事件类型。第一个参数是epoll_create()
        的返回值，第二个参数表示动作，用三个宏表示：EPOLL_CTL_ADD, EPOLL_CTL_MOD, EPOLL_CTL_DEL。第三个参数是要监听的fd，第四个参数
        是告诉要监听什么事件。
            
        struct epoll_event {
          __uint32_t events;  /* Epoll events */
          epoll_data_t data;  /* User data variable */
        };
        events可以是以下几个宏的集合： EPOLLIN， EPOLLOUT， EPOLLPRI， EPOLLERR， EPOLLHUP， EPOLLET， EPOLLONESHOT
        EPOLLOUT主要用于发送大量数据的时候，通过EPOLLOUT通知套接字缓冲区可以写了
        
    （3）int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout)
        等待事件的产生，类似于select()调用。参数events用来从内核得到实践的集合，maxevents告知内核这个events有多大，这个maxevents的值
        不能大于创建epoll_create()时的size，参数timeout是超时时间（毫秒）。返回就绪描述符的个数，超时返回0,出错返回-1
        
    工作模式： LT（level trigger）和ET（edge trigger）模式
    LT模式：当epoll_wait检测到描述符事件发生，并将此事件通知应用程序，应用程序可以不立即处理该事件，下次调用epoll_wait时，会再次响应应用程序并通知此事件
    ET模式：当epoll_wait检测到描述符事件发生，并将此事件通知应用程序，应用程序必须立即处理该事件，下次调用epoll_wait时，不会再次响应应用程序并通知此事件
    通常epoll服务器流程：
    - 创建socket，并且bind，listen
    - epollfd = epoll_create(FDSIZE)
    - epoll_clt(epollfd, EPOLL_CTL_ADD, listenfd, &ev); (struct epoll_event ev;)
    - while(true) int num = epoll_wait(epollfd, events, EPOLLEVENTS, timeout);
        -  for 1:num: 
            -   if fd == listenfd && events[i].events & EPOLLIN : handle_accept
            -   else if events[i].events & EPOLLIN : do_read
            -   else if events[i].events & EPOLLOUT: do_write
    
    