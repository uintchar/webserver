- [1. 网络结构模式](#1-网络结构模式)
  - [1.1. C/S结构](#11-cs结构)
    - [1.1.1. 简介](#111-简介)
    - [1.1.2. 优缺点](#112-优缺点)
  - [1.2. B/S结构](#12-bs结构)
    - [1.2.1. 简介](#121-简介)
    - [1.2.2. 优缺点](#122-优缺点)
- [2. 网络模型](#2-网络模型)
  - [2.1. OSI七层模型](#21-osi七层模型)
  - [2.2. TCP/IP四层模型](#22-tcpip四层模型)
- [3. TCP/IP网络基础](#3-tcpip网络基础)
  - [3.1. 链路层](#31-链路层)
  - [3.2. 网络层](#32-网络层)
  - [3.3. 传输层](#33-传输层)
    - [3.3.1. TCP](#331-tcp)
    - [3.3.2. UDP](#332-udp)
  - [3.4. 应用层](#34-应用层)
    - [3.4.1. DNS](#341-dns)
    - [3.4.2. HTTP/HTTPS](#342-httphttps)
- [4. Linux网络编程基础API](#4-linux网络编程基础api)
  - [4.1. 字节序](#41-字节序)
    - [4.1.1. 主机字节序](#411-主机字节序)
    - [4.1.2. 网络字节序](#412-网络字节序)
    - [4.1.3. 字节序转换函数](#413-字节序转换函数)
  - [4.2. scoket地址](#42-scoket地址)
    - [4.2.1. 通用socket地址](#421-通用socket地址)
    - [4.2.2. 专用socket地址](#422-专用socket地址)
  - [4.3. IP地址转换](#43-ip地址转换)
- [5. socket系统调用](#5-socket系统调用)
  - [5.1. socket()](#51-socket)
  - [5.2. close()](#52-close)
  - [5.3. bind()](#53-bind)
  - [5.4. listen()](#54-listen)
  - [5.5. accept()](#55-accept)
  - [5.6. connect()](#56-connect)
  - [5.7. read()/recv()/recvfrom()](#57-readrecvrecvfrom)
  - [5.8. write()/send()/sendto()](#58-writesendsendto)
  - [5.9. shutdown()](#59-shutdown)
  - [5.10. 常用查看网络相关信息的命令](#510-常用查看网络相关信息的命令)
  - [5.11. TCP通信流程](#511-tcp通信流程)
  - [5.12. UDP通信流程](#512-udp通信流程)
  - [5.13. 端口复用、广播、组播](#513-端口复用广播组播)
  - [5.14. 本地套接字](#514-本地套接字)
- [6. 并发服务器的简单实现](#6-并发服务器的简单实现)
  - [6.1. 多进程并发服务器](#61-多进程并发服务器)
  - [6.2. 多线程并发服务器](#62-多线程并发服务器)
- [7. I/O多路复用](#7-io多路复用)
  - [7.1. select](#71-select)
  - [7.2. poll](#72-poll)
  - [7.3. select() 和 poll() 的比较](#73-select-和-poll-的比较)
  - [7.4. epoll](#74-epoll)
  - [7.5. 文件描述符何时就绪](#75-文件描述符何时就绪)
- [8. Unix/Linux 五种 IO 模型](#8-unixlinux-五种-io-模型)
  - [8.1. 阻塞/非阻塞、同步/异步](#81-阻塞非阻塞同步异步)
  - [8.2. 阻塞](#82-阻塞)
  - [8.3. 非阻塞](#83-非阻塞)
  - [8.4. I/O 复用](#84-io-复用)
  - [8.5. 信号驱动](#85-信号驱动)
  - [8.6. 异步](#86-异步)

# 1. 网络结构模式

## 1.1. C/S结构

### 1.1.1. 简介

- C/S 结构（Client/Server，客户端/服务器）的应用由两个组件进程组成:
  - 客户端：向服务器发送请求消息，请求服务器执行某些服务
  - 服务器：分析客户端的请求，执行相应的动作，然后，向客户端回发响应消息
- 客户端负责完成与用户的交互任务，而服务器应用则提供对某些共享资源的访问。一般说来，都是众多客户端进程与为数不多的一个或几个服务器端进程进行通信。将某项服务封装于单独的服务器应用中，这样做的主要原因如下：
  - 效率：较之于在本地的每台计算上提供相同资源，在服务器应用管理之下提供资源的一份实例，则要节约许多
  - 控制、协调和安全：由于资源（尤其是信息资源）的统一存放，服务器既可以协调对资源的访问（例如，两个客户端不能同时更新同一信息），还可以保护资源安全，令其只对特定客户端开放
  - 在异构环境中运行：在网络中，客户端和服务器应用所运行的硬件平台和操作系统可以不同

### 1.1.2. 优缺点

- **优点：**
  - 能充分发挥客户端 PC 的处理能力，很多工作可以在客户端处理后再提交给服务器，所以 C/S 结构客户端响应速度快
  - 操作界面漂亮、形式多样，可以充分满足客户自身的个性化要求
  - C/S 结构的管理信息系统具有较强的事务处理能力，能实现复杂的业务流程
  -  安全性较高，C/S 一般面向相对固定的用户群，程序更加注重流程，它可以对权限进行多层次校验，提供了更安全的存取模式，对信息安全的控制能力很强，一般高度机密的信息系统采用 C/S 结构适宜
- **缺点：**
  - 客户端需要安装专用的客户端软件。首先涉及到安装的工作量，其次任何一台电脑出问题，如病毒、硬件损坏，都需要进行安装或维护。系统软件升级时，每一台客户机需要重新安装，其维护和升级成本非常高；
  - 对客户端的操作系统一般也会有限制，不能够跨平台

## 1.2. B/S结构

### 1.2.1. 简介

- B/S 结构（Browser/Server，浏览器/服务器），是 WEB 兴起后的一种网络结构模式，WEB 浏览器是客户端最主要的应用软件。这种模式统一了客户端，将系统功能实现的核心部分集中到服务器上，简化了系统的开发、维护和使用。客户机上只要安装一个浏览器，如 Firefox 或 Internet Explorer，服务器安装 SQL Server、Oracle、MySQL 等数据库。浏览器通过 Web Server 同数据库进行数据交互

### 1.2.2. 优缺点

- **优点：**
  - B/S 架构最大的优点是总体拥有成本低、维护方便、 分布性强、开发简单，可以不用安装任何专门的软件就能实现在任何地方进行操作，客户端零维护，系统的扩展非常容易，只要有一台能上网的电脑就能使用
- **缺点：**
  - 通信开销大、系统和数据的安全性较难保障
  - 个性特点明显降低，无法实现具有个性化的功能要求
  - 协议一般是固定的：http/https
  - 客户端服务器端的交互是请求-响应模式，通常动态刷新页面，响应速度明显降低

# 2. 网络模型

## 2.1. OSI七层模型

七层模型，亦称 OSI（Open System Interconnection）参考模型，即开放式系统互联。参考模型是国际标准化组织（ISO）制定的一个用于计算机或通信系统间互联的标准体系，一般称为 OSI 参考模型或七层模型。它是一个七层的、抽象的模型体，不仅包括一系列抽象的术语或概念，也包括具体的协议，主要包括以下七层协议：
- 应用层
- 表示层：
- 会话层：
- 传输层：
- 网络层：
- 链路层：
- 物理层：

![OSI 七层模型参考图]()

## 2.2. TCP/IP四层模型

现在 Internet（因特网）使用的主流协议族是 TCP/IP 协议族，它是一个分层、多协议的通信体系。TCP/IP协议族是一个四层协议系统，自底而上分别是数据链路层、网络层、传输层和应用层。每一层完成不同的功能，且通过若干协议来实现，上层协议使用下层协议提供的服务。
- 应用层：
- 传输层：
- 网络层：
- 网络接口层：

![TCP/IP 四层模型参考图]()

# 3. TCP/IP网络基础

## 3.1. 链路层

网络接口层常见协议有：ARP协议（Address Resolution Protocol 地址解析协议）、RARP协议（Reverse Address Resolution Protocol 反向地址解析协议）。

## 3.2. 网络层

网络层常见协议有：IP 协议（Internet Protocol 因特网互联协议）、ICMP 协议（Internet Control Message Protocol 因特网控制报文协议）、IGMP 协议（Internet Group Management Protocol 因特网组管理协议）

## 3.3. 传输层

传输层常见协议有：TCP 协议（Transmission Control Protocol 传输控制协议）、UDP 协议（User Datagram Protocol 用户数据报协议）

### 3.3.1. TCP

### 3.3.2. UDP

## 3.4. 应用层

应用层常见的协议有：FTP 协议（File Transfer Protocol 文件传输协议）、HTTP 协议（Hyper Text Transfer Protocol 超文本传输协议）、NFS（Network File System 网络文件系统）

### 3.4.1. DNS

### 3.4.2. HTTP/HTTPS

# 4. Linux网络编程基础API

## 4.1. 字节序

### 4.1.1. 主机字节序

- 主机字节序，就是大于一个字节类型的数据在主机内存中的存放顺序。主机字节序分为大端字节序（Big-Endian） 和小端字节序（Little-Endian）。
  - 大端字节序：指整数的最高位字节（23 ~ 31bit）存储在内存的低地址，低位字节（0 ~ 7bit）存储在内存的高地址
  - 小端字节序：指整数的高位字节存储在内存的高地址，而低位字节则存储在内存的低地址

![字节序示意图]()

### 4.1.2. 网络字节序

- 当格式化的数据在两台使用不同字节序的主机之间直接传递时，接收端必然错误的解释之。解决问题的方法是：发送端总是把要发送的数据转换成大端字节序数据后再发送，而接收端知道对方传送过来的数据总是采用大端字节序，所以接收端可以根据自身采用的字节序决定是否对接收到的数据进行转换（小端机转换，大端机不转换）
- 网络字节顺序是 TCP/IP 中规定好的一种数据表示格式，它与具体的 CPU 类型、操作系统等无关，从而可以保证数据在不同主机之间传输时能够被正确解释，网络字节顺序采用大端排序方式。

### 4.1.3. 字节序转换函数

```cpp {class=line-numbers}
#include <arpa/inet.h>

/* 转换端口 */
uint16_t htons(uint16_t hostshort); /* 将主机字节序转换为网络字节序 */
uint16_t ntohs(uint16_t netshort);  /* 将网络字节序转换为主机字节序 */

/* 转换 IP */
uint32_t htonl(uint32_t hostlong);
uint32_t ntohl(uint32_t netlong);
```

## 4.2. scoket地址

### 4.2.1. 通用socket地址

```cpp {class=line-numbers}
#include <bits/socket.h>

struct sockaddr
{
  sa_family_t sa_family;
  char sa_data[14];
};

typedef unsigned short int sa_family_t;
```

sa_family 成员是地址族类型（sa_family_t）的变量。地址族类型通常与协议族类型对应。常见的协议族（protocol family，也称 domain）和对应的地址族如下所示：

|  协议族  |  地址族  |         描述          |
| :------: | :------: | :-------------------: |
| PF_UNIX  | AF_UNIX  |   UNIX 本地域协议族   |
| PF_INET  | AF_INET  | TCP/IPv4 本地域协议族 |
| PF_INET6 | AF_INET6 | TCP/IPv6 本地域协议族 |

宏 PF_* 和 AF_* 都定义在 `bits/socket.h` 头文件中，且后者与前者有完全相同的值，所以二者通常混用

`sa_data` 成员用于存放 socket 地址值。但是，不同的协议族的地址值具有不同的含义和长度，如下所示：

|  协议族  | 地址值含义和长度                                                            |
| :------: | :-------------------------------------------------------------------------- |
| PF_UNIX  | 文件的路径名，长度可达到 108 字节                                           |
| PF_INET  | 16 bit 端口号和 32 bit IPv4 地址，共 6 字节                                 |
| PF_INET6 | 16bits 端口号，32bits 流标识，128bits IPv6 地址，32bits 范围 ID，共 26 字节 |

由上表可知，14 字节的 sa_data 根本无法容纳多数协议族的地址值。因此，Linux 定义了下面这个新的通用的 socket 地址结构体，这个结构体不仅提供了足够大的空间用于存放地址值，而且是内存对齐的。

```cpp {class=line-numbers}
#include <bits/socket.h>

struct sockaddr_storage
{
  sa_family_t sa_family;
  unsigned long int __ss_align;
  char __ss_padding[128 - sizeof(__ss_align)];
};

typedef unsigned short int sa_family_t;
```

### 4.2.2. 专用socket地址

很多网络编程函数诞生早于 IPv4 协议，那时候都使用的是 `struct sockaddr` 结构体，为了向前兼容，现在 `sockaddr` 退化成了 `void *` 的作用，传递一个地址给函数，至于这个函数是 `sockaddr_in` 还是 `sockaddr_in6`，由地址族确定，然后函数内部再强制类型转化为所需的地址类型。

```cpp {class=line-numbers}
/* UNIX 本地域协议族专用 socket 地址结构体 */
#include <sys/un.h>
struct sockaddr_un
{
  sa_family_t sin_family;
  char sun_path[108];
};


#include <netinet/in.h>
/* IPv4 协议专用 socket 地址结构体  */
struct sockaddr_in
{
  sa_family_t sin_family;
  in_port_t sin_port;      /* 端口号 */
  struct in_addr sin_addr; /* IP 地址 */
  /* Pad to size of `struct sockaddr'. */
  unsigned char sin_zero[sizeof(struct sockaddr) - __SOCKADDR_COMMON_SIZE - 
                         sizeof(in_port_t) - sizeof(struct in_addr)];
};
struct in_addr
{
  in_addr_t s_addr;
};

/* IPv6 协议专用 socket 地址结构体  */
struct sockaddr_in6
{
  sa_family_t sin6_family;
  in_port_t sin6_port;       /* Transport layer port # */
  uint32_t sin6_flowinfo;    /* IPv6 flow information */
  struct in6_addr sin6_addr; /* IPv6 address */
  uint32_t sin6_scope_id;    /* IPv6 scope-id */
};

typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef uint16_t in_port_t;
typedef uint32_t in_addr_t;
#define __SOCKADDR_COMMON_SIZE (sizeof(unsigned short int))
```

## 4.3. IP地址转换

通常，人们习惯用可读性好的字符串来表示 IP 地址，比如用点分十进制字符串表示 IPv4 地址，以及用十六进制字符串表示 IPv6 地址。但编程中我们需要先把它们转化为整数（二进制数）方能使用。而记录日志时则相反，我们要把整数表示的 IP 地址转化为可读的字符串。一下函数可以完成 IP 地址在整数和字符串形式之间的转换。

```cpp {class=line-numbers}
/* 用于用点分十进制字符串表示的 IPv4 地址和用网络字节序整数表示的 IPv4 地址之间的转换 */
#include <arpa/inet.h>
in_addr_t inet_addr(const char *cp);
int inet_aton(const char *cp, struct in_addr *inp);
char *inet_ntoa(struct in_addr in);
```

```cpp {class=line-numbers}
/* 同时适用 IPv4 地址和 IPv6 地址 */
#include <arpa/inet.h>

int inet_pton(int af, const char *src, void *dst);
/**
  * @brief:
  *  - 将字符串形式的 IP 地址转换为网络字节序的整数
  * @param: 
  *  - af：地址族，AF_INET、AF_INET6
  *  - src：需要转换的 IP 字符串
  *  - dst：传出参数，保存转换后的结果
  * @return:
  *  - 成功：1
  *  - 失败：0 表示 src 不是 IP 地址标准字符串表示，-1 表示错误
  **/

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
/**
  * @brief:
  *  - 将网络字节序的整数转换为字符串形式的 IP 地址
  * @param: 
  *  - af：地址族，AF_INET、AF_INET6
  *  - src：需要转换的整数形式的 IP
  *  - dst：传出参数，保存转换后的结果
  *  - size：dest 所指内存的大小
  * @return:
  *  - 成功：返回转换后的数据的地址（字符串），和 dst 是一样的
  *  - 失败：NULL
  **/
```

# 5. socket系统调用

## 5.1. socket()

```cpp {class=line-numbers}
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> /* 包含了这个头文件，上面两个就可以省略 */

int socket(int domain, int type, int protocol);
/**
  * @brief:
  *  - 创建一个 socket 套接字
  * @param: 
  *  - domain：协议族，AF_INET、AF_INET6
  *  - type：通信使用的协议类型
  *    - SOCK_STREAM：流式协议
  *    - SOCK_DGRAM：数据报式协议
  *  - protocol：具体的一个协议，一般写 0
  *    - SOCK_STREAM 流式协议默认使用 TCP
  *    - SOCK_DGRAM 数据报式协议默认使用 UDP
  * @return:
  *  - 成功：返回文件描述符，操作对应的内核缓冲区
  *  - 失败：-1，并设置 errno
  **/
```

## 5.2. close()

```cpp {class=line-numbers}
#include <unistd.h>

int close(int sockfd)
/**
  * @brief:
  *  - 关闭文件描述符 fd
  * @param: 
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

## 5.3. bind()

```cpp {class=line-numbers}
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> /* 包含了这个头文件，上面两个就可以省略 */

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen); 
/**
  * @brief:
  *  - 命名 socket，将 sockfd 和本地的 IP + 端口号进行绑定
  *  - 一般来讲会将服务器的地址绑定到一个周知的地址
  * @param: 
  *  - sockfd：通过 socket() 得到的文件描述符
  *  - addr：需要绑定的 socket 地址，地址里封装了 IP 和端口号
  *  - addrlen：第二个参数结构体所占内存的大小
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

## 5.4. listen()

```cpp {class=line-numbers}
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> /* 包含了这个头文件，上面两个就可以省略 */

int listen(int sockfd, int backlog);
/**
  * @brief:
  *  - 监听指定 socket 上的连接
  * @param: 
  *  - sockfd：通过 socket() 获得的文件描述符
  *  - backlog：未连接的与已经连接的和的最大值
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

## 5.5. accept()

```cpp {class=line-numbers}
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> /* 包含了这个头文件，上面两个就可以省略 */

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
/**
  * @brief:
  *  - 接受客户端的连接，默认是一个阻塞的函数，阻塞等待客户端的连接
  * @param: 
  *  - sockfd：用于监听的文件描述符
  *  - addr：传出参数，记录了连接成功后客户端的地址信息（IP、端口号）
  *  - addrlen：socket 地址所占内存的大小
  * @return:
  *  - 成功：用于与客户端进行通信的文件描述符
  *  - 失败：-1，并设置 errno
  **/
```

## 5.6. connect()

```cpp {class=line-numbers}
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> /* 包含了这个头文件，上面两个就可以省略 */

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
/**
  * @brief:
  *  - 客户端主动连接指定的服务器
  * @param: 
  *  - sockfd：通过 socket() 得到的用于通信的文件描述符
  *  - sockaddr：客户端要连接的服务器的 socket 地址信息（IP、端口号）
  *  - addrlen：socket 地址所占内存的大小
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

## 5.7. read()/recv()/recvfrom()

```cpp {class=line-numbers}
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);
/**
  * @brief:
  *  - 在指定的文件描述符 fd 上读取 count 字节的数据将其保存到 buf 指定的地址中
  *  - 可能会被信号中断
  * @param: 
  * @return:
  *  - 成功：实际读取到的字节数
  *  - 失败：-1，并设置 errno
  **/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> /* 包含了这个头文件，上面两个就可以省略 */

ssize_t recv(int sockfd, void *buf, size_t len, int flags);
/**
  * @brief:
  *  - 流式 socket
  * @param: 
  *   - sockfd：
  *   - buf：
  *   - len：
  *   - flags：
  * @return:
  *  - 成功：
  *  - 失败：-1，并设置 errno
  **/

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                 struct sockaddr *src_addr, socklen_t *addrlen);
/**
  * @brief:
  *  - 数据报 socket
  * @param: 
  *   - sockfd：通信的 fd
  *   - buf：接收数据的缓冲区
  *   - len：接收缓冲区的大小
  *   - flags：0
  *   - src_addr：传出参数，用来保存通信对方的地址信息，不需要可以指定为 NULL
  *   - addrlen：地址所占内存的大小
  * @return:
  *  - 成功：实际读取到的字节数，0 表示 EOF
  *  - 失败：-1，并设置 errno
  **/
```

## 5.8. write()/send()/sendto()

```cpp {class=line-numbers}
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
/**
  * @brief:
  *  - 向指定的文件描述符 fd 写入 buf 中的 count 各字节的数据
  * @param: 
  * @return:
  *  - 成功：实际写入的数据
  *  - 失败：-1，并设置 errno
  **/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> /* 包含了这个头文件，上面两个就可以省略 */

ssize_t send(int sockfd, const void *buf, size_t len, int flags);
/**
  * @brief:
  *  - 流式 socket
  * @param: 
  *   - sockfd：
  *   - buf：
  *   - len：
  *   - flags：
  * @return:
  *  - 成功：实际发送的字节数
  *  - 失败：-1，并设置 errno
  **/

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen);
/**
  * @brief:
  *  - 数据报 socket
  * @param: 
  *   - sockfd：通信的 fd
  *   - buf：待发送数据缓冲区
  *   - len：待发送数据的长度
  *   - flags：0
  *   - dest_addr：通信对方的地址信息
  *   - addrlen：dest_addr 所指地址所占内存的大小
  * @return:
  *  - 成功：实际发送的字节数
  *  - 失败：-1，并设置 errno
  **/
```

## 5.9. shutdown()

当 TCP 链接中主动断开连接方 A 向另一方 B 发送 FIN 请求断开连接，另一端 B 回应 ACK 之后（A 端进入 FIN_WAIT_2 状态），并没有立即发送 FIN 给 A，A 方处于半连接状态（半关闭），此时 A 可以接收 B 发送的数据，但是 A 已经不能再向 B 发送数据。可以使用 `shutdown()` 来控制实现半连接

使用 `close()` 中止一个连接，但它只是减少描述符的引用计数，并不直接关闭连接，只有当描述符的引用计数为 0 时才关闭连接。`shutdown()` 不考虑描述符的引用计数，直接关闭描述符。也可选择中止一个方向的连接，只中止读或只中止写。

如果有多个进程共享一个套接字，`close()` 每被调用一次，计数减 1 ，直到计数为 0 时，也就是所有进程都调用了 `close()`，套接字将被释放

在多进程中如果一个进程调用了 `shutdown(sfd, SHUT_RDWR)` 后，其它的进程将无法进行通信。但如果一个进程 close(sfd) 将不会影响到其它进程

```cpp {class=line-numbers}
 #include <sys/socket.h>

int shutdown(int sockfd, int how);
/**
  * @brief:
  *  - 以指定的方式 how 关闭 sockfd
  * @param: 
  *  - sockfd：要关闭的文件描述符
  *  - how：可以以以下几种方式关闭 sockfd
  *    - SHUT_RD(0)：关闭 sockfd 上的读功能，此选项将不允许 sockfd 进行读操作。该套接字不再接收数据，任何当前在套接字接受缓冲区的数据将被默认丢弃掉
  *    - SHUT_WR(1): 关闭 sockfd 的写功能，此选项将不允许 sockfd 进行写操作
  *    - SHUT_RDWR(2):关闭 sockfd 的读写功能。相当于调用 shutdown 两次：首先是 SHUT_RD，然后以 SHUT_WR
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

## 5.10. 常用查看网络相关信息的命令

```cpp {class=line-numbers}
netstat
  -a：所有的socket
  -p：显示正在使用socket的程序的名称
  -n：直接使用IP地址，而不通过域名服务器

netstat -anp | grep port_num
```

## 5.11. TCP通信流程

![TCP 通信流程图]()

```cpp {class=line-numbers}
/* tcp_server.c */
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  /* 创建 socket，获得用于监听的套接字 */

  int lfd = socket(AF_INET, SOCK_STREAM, 0);
  if (lfd == -1)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  /* 绑定 socket */
  struct sockaddr_in saddr; /* IPv4 socket 地址类型 */
  saddr.sin_family = AF_INET;
  /* inet_pton(AF_INET, "172.26.50.243", saddr.sin_addr.s_addr); */
  saddr.sin_addr.s_addr = INADDR_ANY; /* 0.0.0.0 */
  saddr.sin_port = htons(9999);
  int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
  if (ret == -1)
  {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  /* 监听客户端连接 */
  ret = listen(lfd, 8);
  if (ret == -1)
  {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  /* 接受客户端连接 */
  struct sockaddr_in clientaddr;
  int len = sizeof(clientaddr);
  int cfd = accept(lfd, (struct sockaddr *)&clientaddr, &len);
  if (cfd == -1)
  {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  /* 输出客户端的信息 */
  char clientIP[16];
  inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, clientIP, sizeof(clientIP));
  unsigned short clientPort = ntohs(clientaddr.sin_port);
  printf("client ip is %s, port is %d\n", clientIP, clientPort);

  /* 通信 */
  char recv_buf[1024] = {0};
  char send_buf[1024] = {0};
  memset(recv_buf, -1, sizeof(recv_buf));
  memset(send_buf, -1, sizeof(send_buf));

  while (1)
  {
    int num = read(cfd, recv_buf, sizeof(recv_buf));
    if (num == -1)
    {
      perror("read");
      exit(EXIT_FAILURE);
    }
    else if (num > 0)
    {
      printf("recv client data : %s", recv_buf);
    }
    else if (num == 0)
    {
      /* 表示客户端断开连接 */
      printf("clinet closed...");
      break;
    }

    fgets(send_buf, sizeof(send_buf), stdin); /* 会读入换行符 */
    num = write(cfd, send_buf, strlen(send_buf) + 1);
    if (num == -1)
    {
      perror("write");
      exit(EXIT_FAILURE);
    }
  }

  close(cfd);
  close(lfd);

  return 0;
}
```

```cpp {class=line-numbers}
/* tcp_client.c */
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  /* 创建套接字 */
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1)
  {
    perror("socket");
    exit(-1);
  }

  /* 主动连接服务器端，需要指定服务器的地址，客户端自身则会随机绑定一个端口号 */
  struct sockaddr_in serveraddr;
  serveraddr.sin_family = AF_INET;
  inet_pton(AF_INET, "172.26.50.243", &serveraddr.sin_addr.s_addr);
  serveraddr.sin_port = htons(9999);
  int ret = connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
  if (ret == -1)
  {
    perror("connect");
    exit(-1);
  }

  /* 通信 */
  char recv_buf[1024] = {0};
  char send_buf[1024] = {0};
  memset(recv_buf, -1, sizeof(recv_buf));
  memset(send_buf, -1, sizeof(send_buf));
  while (1)
  {
    fgets(send_buf, sizeof(send_buf), stdin); /* 会读入换行符 */
    int num =  write(fd, send_buf, strlen(send_buf) + 1);
    if (num == -1)
    {
      perror("read");
      exit(-1);
    }

    num = read(fd, recv_buf, sizeof(recv_buf));
    if (num == -1)
    {
      perror("read");
      exit(-1);
    }
    else if (num > 0)
    {
      printf("recv server data : %s", recv_buf);
    }
    else if (num == 0)
    {
      // 表示服务器端断开连接
      printf("server closed...");
      break;
    }
  }

  close(fd);

  return 0;
}
```

## 5.12. UDP通信流程

![UDP 通信流程图]()

```cpp {class=line-numbers}
/* udp_server.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
  int fd = socket(PF_INET, SOCK_DGRAM, 0);
  if (fd == -1)
  {
    perror("socket");
    exit(-1);
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9999);
  addr.sin_addr.s_addr = INADDR_ANY;
  int ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
  if (ret == -1)
  {
    perror("bind");
    exit(-1);
  }

  while (1)
  {
    char recvbuf[128];
    char ipbuf[16];

    struct sockaddr_in cliaddr;
    int len = sizeof(cliaddr);

    int num = recvfrom(fd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&cliaddr, &len);
    inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ipbuf, sizeof(ipbuf));
    
    printf("client IP : %s, Port : %d\n", ipbuf, ntohs(cliaddr.sin_port));
    printf("client say : %s\n", recvbuf);

    sendto(fd, recvbuf, strlen(recvbuf) + 1, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
  }

  close(fd);
  return 0;
}
```

```cpp {class=line-numbers}
/* udp_client.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
  int fd = socket(PF_INET, SOCK_DGRAM, 0);
  if (fd == -1)
  {
    perror("socket");
    exit(-1);
  }

  struct sockaddr_in saddr;
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(9999);
  inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr.s_addr);

  int num = 0;
  while (1)
  {
    char sendBuf[128];
    sprintf(sendBuf, "hello , i am client %d\n", num++);
    sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&saddr, sizeof(saddr));

    int len = recvfrom(fd, sendBuf, sizeof(sendBuf), 0, NULL, NULL);
    printf("server say : %s\n", sendBuf);

    sleep(2);
  }

  close(fd);
  return 0;
}
```

## 5.13. 端口复用、广播、组播

- 端口复用最常用的用途是：
  - 防止服务器重启时之前绑定的端口还未释放
  - 程序突然退出而系统没有释放端口
</br>

- 向子网中多台计算机发送消息，并且子网中所有的计算机都可以接收到发送方发送的消息，每个广播消息都包含一个特殊的IP地址，这个 IP 中子网内主机标志部分的二进制全部为 1。
  - 只能在局域网中使用
  - 客户端需要绑定服务器广播使用的端口，才可以接收到广播消息
</br>

- 单播地址标识单个 IP 接口，广播地址标识某个子网的所有 IP 接口，多播地址标识一组 IP 接口。单播和广播是寻址方案的两个极端（要么单个要么全部），多播则意在两者之间提供一种折中方案。多播数据报只应该由对它感兴趣的接口接收，也就是说由运行相应多播会话应用系统的主机上的接口接收。另外，广播一般局限于局域网内使用，而多播则既可以用于局域网，也可以跨广域网使用。
  - 组播既可以用于局域网，也可以用于广域网
  - 客户端需要加入多播组，才能接收到多播的数据

```cpp {class=line-numbers}
#include <sys/types.h>
#include <sys/socket.h>

int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
/**
  * @brief:
  *  - 设置套接字的属性（不仅仅能设置端口复用）
  *  - 设置端口复用的时机是在服务器绑定端口之前
  * @param: 
  *  - sockfd：指定的文件描述符
  *  - level：级别
  *    - SOL_SOCKET：复用、广播
  *    - IPPROTO_IP：组播
  *  - optname：选项的名称
  *    - SO_REUSEADDR：地址复用
  *    - SO_REUSEPORT：端口复用
  *    - SO_BROADCAST：广播
  *    - IP_MULTICAST_IF：服务器设置组播信息，外出接口
  *    - IP_ADD_MEMBERSHIP：客户端加入多播组
  *  - optval：端口复用的值（整型）
  *    - 1：可以复用（广播、组播）
  *    - 0：不可以复用（广播、组播）
  *    - struct in_addr：服务器设置组播信息
  *    - struct ip_mreq：客户端加入多播组
  *  - optlen：optval 的大小
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/

struct ip_mreq
{
  /* IP multicast address of group. */
  struct in_addr imr_multiaddr; // 组播的IP地址
  /* Local IP address of interface. */
  struct in_addr imr_interface; // 本地的IP地址
};

typedef uint32_t in_addr_t;
struct in_addr
{
  in_addr_t s_addr;
};

/* 设置端口复用 */
int optval = 1;
setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
```

```cpp {class=line-numbers}
/* 广播程序应用示例 */

/* broadcast_server.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
  int fd = socket(PF_INET, SOCK_DGRAM, 0);
  if (fd == -1)
  {
    perror("socket");
    exit(-1);
  }

  /* 设置广播属性 */
  int op = 1;
  setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &op, sizeof(op));

  /* 创建一个广播的地址 */
  struct sockaddr_in cliaddr;
  cliaddr.sin_family = AF_INET;
  cliaddr.sin_port = htons(9999);
  inet_pton(AF_INET, "172.26.50.255", &cliaddr.sin_addr.s_addr);

  int num = 0;
  while (1)
  {
    char sendBuf[128];
    sprintf(sendBuf, "hello, client....%d\n", num++);
    sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    printf("broadcast data: %s\n", sendBuf);
    sleep(3);
  }

  close(fd);
  return 0;
}

/* broadcast_client.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
  int fd = socket(PF_INET, SOCK_DGRAM, 0);
  if (fd == -1)
  {
    perror("socket");
    exit(-1);
  }

  struct in_addr in;

  /* 客户端绑定本地的 IP 和端口 */
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9999);
  addr.sin_addr.s_addr = INADDR_ANY;
  int ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
  if (ret == -1)
  {
    perror("bind");
    exit(-1);
  }

  while (1)
  {
    char buf[128];
    int num = recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
    printf("server say : %s\n", buf);
  }

  close(fd);
  return 0;
}
```

```cpp {class=line-numbers}
/* 组播程序应用示例 */

/* multicast_server.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
  int fd = socket(PF_INET, SOCK_DGRAM, 0);
  if (fd == -1)
  {
    perror("socket");
    exit(-1);
  }

  /* 设置多播的属性，设置外出接口 */
  struct in_addr imr_multiaddr;
  
  /* 初始化多播地址 */
  inet_pton(AF_INET, "239.0.0.10", &imr_multiaddr.s_addr);
  setsockopt(fd, IPPROTO_IP, IP_MULTICAST_IF, &imr_multiaddr, sizeof(imr_multiaddr));

  /* 初始化客户端的地址信息 */
  struct sockaddr_in cliaddr;
  cliaddr.sin_family = AF_INET;
  cliaddr.sin_port = htons(9999);
  inet_pton(AF_INET, "239.0.0.10", &cliaddr.sin_addr.s_addr);

  int num = 0;
  while (1)
  {

    char sendBuf[128];
    sprintf(sendBuf, "hello, client....%d\n", num++);
    sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    printf("multicast data: %s\n", sendBuf);
    sleep(1);
  }

  close(fd);
  return 0;
}

/* multicast_client.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
  int fd = socket(PF_INET, SOCK_DGRAM, 0);
  if (fd == -1)
  {
    perror("socket");
    exit(-1);
  }

  struct in_addr in;
  
  /* 客户端绑定本地的 IP 和端口 */
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9999);
  addr.sin_addr.s_addr = INADDR_ANY;
  int ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
  if (ret == -1)
  {
    perror("bind");
    exit(-1);
  }

  struct ip_mreq op;
  inet_pton(AF_INET, "239.0.0.10", &op.imr_multiaddr.s_addr);
  op.imr_interface.s_addr = INADDR_ANY;

  /* 加入到多播组 */
  setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &op, sizeof(op));

  while (1)
  {
    char buf[128];
    int num = recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
    printf("server say : %s\n", buf);
  }

  close(fd);
  return 0;
}
```

## 5.14. 本地套接字

- 本地套接字的作用：本地的进程间通信
  - 有关系的进程间的通信
  - 没有关系的进程间的通信
  - 本地套接字实现流程和网络套接字类似，一般呢采用 TCP 的通信流程。

```cpp {class=line-numbers}
#include <sys/un.h>
#define UNIX_PATH_MAX 108
struct sockaddr_un
{
  sa_family_t sun_family;       /* 地址族协议 af_local */
  char sun_path[UNIX_PATH_MAX]; /* 套接字文件的路径, 这是一个伪文件, 大小永远=0 */
};

/* localsocket_server.c */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/un.h>

int main()
{

  unlink("server.sock"); /* 防止本地套接字文件被占用 */

  int lfd = socket(AF_LOCAL, SOCK_STREAM, 0);
  if (lfd == -1)
  {
    perror("socket");
    exit(-1);
  }

  /* 绑定本地套接字文件 */
  struct sockaddr_un addr;
  addr.sun_family = AF_LOCAL;
  strcpy(addr.sun_path, "server.sock");
  int ret = bind(lfd, (struct sockaddr *)&addr, sizeof(addr));
  if (ret == -1)
  {
    perror("bind");
    exit(-1);
  }

  ret = listen(lfd, 100);
  if (ret == -1)
  {
    perror("listen");
    exit(-1);
  }

  struct sockaddr_un cliaddr;
  int len = sizeof(cliaddr);
  int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);
  if (cfd == -1)
  {
    perror("accept");
    exit(-1);
  }

  printf("client socket filename: %s\n", cliaddr.sun_path);

  while (1)
  {
    char buf[128];
    int len = recv(cfd, buf, sizeof(buf), 0);
    if (len == -1)
    {
      perror("recv");
      exit(-1);
    }
    else if (len == 0)
    {
      printf("client closed....\n");
      break;
    }
    else if (len > 0)
    {
      printf("client say : %s\n", buf);
      send(cfd, buf, len, 0);
    }
  }

  close(cfd);
  close(lfd);

  return 0;
}
```

```cpp {class=line-numbers}
/* localsocket_client.c */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/un.h>

int main()
{

  unlink("client.sock"); /* 防止本地套接字文件被占用 */

  int cfd = socket(AF_LOCAL, SOCK_STREAM, 0);
  if (cfd == -1)
  {
    perror("socket");
    exit(-1);
  }

  /* 绑定本地套接字文件 */
  struct sockaddr_un addr;
  addr.sun_family = AF_LOCAL;
  strcpy(addr.sun_path, "client.sock");
  int ret = bind(cfd, (struct sockaddr *)&addr, sizeof(addr));
  if (ret == -1)
  {
    perror("bind");
    exit(-1);
  }

  struct sockaddr_un seraddr;
  seraddr.sun_family = AF_LOCAL;
  strcpy(seraddr.sun_path, "server.sock");
  ret = connect(cfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
  if (ret == -1)
  {
    perror("connect");
    exit(-1);
  }

  int num = 0;
  while (1)
  {
    char buf[128];
    sprintf(buf, "hello, i am client %d\n", num++);
    send(cfd, buf, strlen(buf) + 1, 0);
    printf("client say : %s\n", buf);

    int len = recv(cfd, buf, sizeof(buf), 0);
    if (len == -1)
    {
      perror("recv");
      exit(-1);
    }
    else if (len == 0)
    {
      printf("server closed....\n");
      break;
    }
    else if (len > 0)
    {
      printf("server say : %s\n", buf);
    }

    sleep(3);
  }

  close(cfd);
  return 0;
}
```

# 6. 并发服务器的简单实现

## 6.1. 多进程并发服务器

```cpp {class=line-numbers}
/* tcpserver_mulserver.c */

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <wait.h>
#include <errno.h>

void recyle_child(int arg)
{
  while (1)
  {
    int ret = waitpid(-1, NULL, WNOHANG);
    if (ret == -1) /* 所有的子进程都回收了 */
      break;
    else if (ret == 0) /* 还有子进程活着 */
      break;
    else if (ret > 0)
      printf("子进程 %d 被回收了\n", ret);
  }
}

int main()
{
  /* 利用 SIGCHLD 信号回收子进程，防止产生大量僵尸进程 */
  struct sigaction act;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);
  act.sa_handler = recyle_child;
  sigaction(SIGCHLD, &act, NULL);

  int lfd = socket(PF_INET, SOCK_STREAM, 0);
  if (lfd == -1)
  {
    perror("socket");
    exit(-1);
  }

  struct sockaddr_in saddr;
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(9999);
  saddr.sin_addr.s_addr = INADDR_ANY;
  int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
  if (ret == -1)
  {
    perror("bind");
    exit(-1);
  }

  ret = listen(lfd, 128);
  if (ret == -1)
  {
    perror("listen");
    exit(-1);
  }

  while (1)
  {
    struct sockaddr_in cliaddr;
    int len = sizeof(cliaddr);
    int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);
    if (cfd == -1)
    {
      if (errno == EINTR)
      {
        continue; /* 被中断打断了产生的错误 */
      }
      perror("accept");
      exit(-1);
    }

    /* 每一个连接进来，创建一个子进程跟客户端通信 */
    pid_t pid = fork();
    if (pid == 0)
    {
      char cliIp[16];
      inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, cliIp, sizeof(cliIp));
      unsigned short cliPort = ntohs(cliaddr.sin_port);
      printf("client ip is : %s, prot is %d\n", cliIp, cliPort);

      char recvBuf[1024];
      while (1)
      {
        int len = read(cfd, &recvBuf, sizeof(recvBuf));
        if (len == -1)
        {
          perror("read");
          exit(-1);
        }
        else if (len > 0)
        {
          printf("recv client : %s\n", recvBuf);
        }
        else if (len == 0)
        {
          printf("client closed....\n");
          break;
        }

        write(cfd, recvBuf, strlen(recvBuf) + 1);
      }
      close(cfd);
      exit(0); /* 退出当前子进程 */
    }
  }

  close(lfd);
  return 0;
}
```

```cpp {class=line-numbers}
/* tcp_client.c */

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1)
  {
    perror("socket");
    exit(-1);
  }

  struct sockaddr_in saddr;
  saddr.sin_family = AF_INET;
  inet_pton(AF_INET, "172.26.50.243", &saddr.sin_addr.s_addr);
  saddr.sin_port = htons(9999);
  int ret = connect(fd, (struct sockaddr *)&saddr, sizeof(saddr));
  if (ret == -1)
  {
    perror("connect");
    exit(-1);
  }

  char recvBuf[1024];
  int i = 0;
  while (1)
  {
    sprintf(recvBuf, "data : %d\n", i++);
    write(fd, recvBuf, strlen(recvBuf) + 1);

    int len = read(fd, recvBuf, sizeof(recvBuf));
    if (len == -1)
    {
      perror("read");
      exit(-1);
    }
    else if (len > 0)
    {
      printf("recv server : %s\n", recvBuf);
    }
    else if (len == 0)
    {
      printf("server closed...");
      break;
    }

    sleep(2);
  }

  close(fd);

  return 0;
}
```

## 6.2. 多线程并发服务器

```cpp {class=line-numbers}
/* tcpserver_multhread.c */

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct sock_info
{
  int fd;
  struct sockaddr_in addr;
  pthread_t tid;
};

/* 全局变量用于记录子线程处理的客户端 socket 连接的相关信息 */
struct sock_info sock_infos[4];

void *working(void *arg)
{
  /* 获取客户端的信息 */
  struct sock_info *pinfo = (struct sock_info *)arg;

  char cliIp[16];
  inet_ntop(AF_INET, &pinfo->addr.sin_addr.s_addr, cliIp, sizeof(cliIp));
  unsigned short cliPort = ntohs(pinfo->addr.sin_port);
  printf("client ip is : %s, prot is %d\n", cliIp, cliPort);

  char recvBuf[1024];
  while (1)
  {
    int len = read(pinfo->fd, &recvBuf, sizeof(recvBuf));
    if (len == -1)
    {
      perror("read");
      exit(-1);
    }
    else if (len > 0)
    {
      printf("recv client : %s\n", recvBuf);
    }
    else if (len == 0)
    {
      printf("client closed....\n");
      break;
    }

    write(pinfo->fd, recvBuf, strlen(recvBuf) + 1);
  }

  close(pinfo->fd);
  printf("thread %ld exit\n", pinfo->tid);

  pinfo->fd = -1;
  pinfo->tid = -1;


  return NULL;
}

int main()
{
  int lfd = socket(PF_INET, SOCK_STREAM, 0);
  if (lfd == -1)
  {
    perror("socket");
    exit(-1);
  }

  struct sockaddr_in saddr;
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(9999);
  saddr.sin_addr.s_addr = INADDR_ANY;
  int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
  if (ret == -1)
  {
    perror("bind");
    exit(-1);
  }

  ret = listen(lfd, 128);
  if (ret == -1)
  {
    perror("listen");
    exit(-1);
  }

  int max = sizeof(sock_infos) / sizeof(sock_infos[0]);
  for (int i = 0; i < max; i++)
  {
    bzero(&sock_infos[i], sizeof(sock_infos[i]));
    sock_infos[i].fd = -1;
    sock_infos[i].tid = -1;
  }

  /* 循环等待客户端连接，一旦一个客户端连接进来，就创建一个子线程进行通信 */
  while (1)
  {
    struct sockaddr_in cliaddr;
    int len = sizeof(cliaddr);
    int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);
    struct sock_info *pinfo;
    for (int i = 0; i < max; i++)
    {
      /* 从这个数组中找到一个可以用的 sock_info 元素 */
      if (sock_infos[i].fd == -1)
      {
        pinfo = &sock_infos[i];
        break;
      }
      if (i == max - 1)
      {
        printf("max nums client access, please wait\n");
        sleep(2);
        i = 0; /* 从头开始遍历 */
      }
    }

    pinfo->fd = cfd;
    memcpy(&pinfo->addr, &cliaddr, len);

    pthread_create(&pinfo->tid, NULL, working, pinfo);
    pthread_detach(pinfo->tid);
  }

  close(lfd);
  return 0;
}
```

# 7. I/O多路复用

I/O 多路复用使得程序能同时监听多个文件描述符，能够提高程序的性能，Linux 下实现 I/O 多路复用的系统调用主要有 `select(), poll(), epoll()`。

## 7.1. select

- 首先构造一个关于文件描述符的列表，将要监听的文件描述符添加到该列表中
- 调用 `select()`，监听该列表中的文件描述符，直到这些描述符中的一个或者多个进行 I/O 操作时，该函数才返回
  - `select()` 是阻塞的
  - `select()` 对文件描述符的检测操作是由内核完成的
- 在返回时，`select()` 会告诉进程有多少（哪些）描述符要进行 I/O 操作

```cpp {class=line-numbers}
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
/**
  * @brief:
  *  - 委托内核检测给定文件描述符集合中发生 I/O 操作的文件描述符
  * @param: 
  *  - nfds：比 3 个文件描述符集合中所包含的最大文件描述符号还要大 1
  *  - readfds：要检测的读文件描述符的集合，对应于 socket 对方发送来数据
  *  - writefds：要检测的写文件描述符的集合
  *  - exceptfds：要检测的发生异常的文件描述符集合
  *  - timeout：设置阻塞超时时间，在循环中使用应确保每次循环都更新
  *    - NULL：永久阻塞，直到检测到了文件描述符发生变化
  *    - = 0：不阻塞
  *    - > 0：阻塞对应时间
  * @return:
  *  - 成功：
  *    - 返回处于三个文件描述符集合中处于就绪态的文件描述符的个数，对同一个 fd 会多次计算
  *    - 0 表示超时，此时每个返回的文件描述符集都会被清空
  *  - 失败：-1，并设置 errno
  *    - EBADF：三个文件描述符集合中存在非法文件描述符（例如当前没打开）
  *    - EINTR：该调用被信号处理例程中断，此时 select() 不会自动恢复
  * 
  **/

void FD_CLR(int fd, fd_set *set);  /* 将参数文件描述符fd对应的标志位设置为0 */
int FD_ISSET(int fd, fd_set *set); /* 判断 fd 对应的标志位是 0 还是 1 */
void FD_SET(int fd, fd_set *set);  /* 将参数文件描述符 fd 对应的标志位设置为 1 */
void FD_ZERO(fd_set *set);         /* fd_set 一共有1024 bits, 全部初始化为 0 */
```

## 7.2. poll

```cpp {class=line-numbers}
#include <poll.h>

int poll(struct pollfd *fds, nfds_t nfds, int timeout);
struct pollfd
{
  int fd;        /* 委托内核检测的文件描述符 */
  short events;  /* 委托内核检测的 fd 上发生的事件 */
  short revents; /* 返回 fd 上实际发生的事件 */
};
/**
  * @brief:
  *  - 委托内核对给定 fds 集合中发生 I/O 操作的 fd 进行检测
  * @param: 
  *  - fds：struct pollfd 类型的结构体数组，保存了需要检测的文件描述符集合
  *  - nfds：fds 数组中最后一个有效元素的下标 + 1
  *  - timeout：阻塞时长
  *    - 0：不阻塞
  *    - -1：阻塞，当检测的 fds 上有 I/O 发生时，解除阻塞
  *    - >0：阻塞的时长
  * @return:
  *  - 成功：
  *    - >0：返回就绪的 fd 数量（数组 fds 中拥有非零 revents 字段的元素数量）
  *    - 0：表示未检测任意一个 fd 就绪前就超时了
  *  - 失败：-1，并设置 errno
  *    - EINTR：该调用被一个信号处理例程打断，poll() 不会自动恢复
  **/
```

## 7.3. select() 和 poll() 的比较

- **相同点：**
  - 系统调用 `select()` 和 `poll()` 都是用来同时检查多个文件描述符就绪状态的方法
  - `select()` 和 `poll()` 都需要将一个表示待检测的文件描述符列表的数据结构传递给内核，内核检查列表中的每一个文件描述符后，修改这个数据结构并返回给用户进程。当检查大量文件描述符时，这种从用户空间到内核空间的来回拷贝将带来大量的时间开销
  - `select()` 和 `poll()` 调用返回后，程序必须检查返回的数据结构中的每一个元素，以检查哪个文件描述符处于就绪状态
</br>

- **不同点：**
  - `select()` 对被检查的文件描述符数量有一个上限（FD_SETSIZE），在 Linux 下这个上限默认为 1024。而 `poll()` 对检查的文件描述符数量没有上限限制
  - `select()` 的 `fd_set` 是传入传出参数，如果要在循环中重复调用 `select()` 的话， 必须每次都要重新初始化 `fd_set`。 而 `poll()` 通过独立的两个字段 `events`（针对输入）和 `revents`（针对输出）来处理，从而避免每次都要重新初始化参数
  - `select()` 提供的超时精度（微秒）比 `poll()` 提供的超时精度（毫秒）高。 （这两个系统调用的超时精度都受软件时钟粒度的限制）
  - 如果其中一个被检查的文件描述符关闭了，通过在对应的 `revents` 字段中设定 POLLNVAL 标记，`poll()` 会准确告诉我们是哪一个文件描述符关闭了。 与之相反， `select()` 只会返回 −1，并设错误码为 EBADF。通过在描述符上执行 I/O 系统调用并检查错误码，让我们自己来判断哪个文件描述符关闭了
  - 当检查的文件描述符范围较小，或者数量较大但是分布较密集时（集中在 0 ~ 某个上限之间）时，两者性能差别不大；但是如果当检查的文件描述符集合较为稀疏时，`poll()` 的性能将优于 `select()`


## 7.4. epoll

```cpp {class=line-numbers}
/**
  * @brief:
  *  - 
  * @param: 
  *  - 
  * @return:
  *  - 成功：
  *  - 失败：
  **/
```

## 7.5. 文件描述符何时就绪

- 普通文件
- 终端和伪终端
- 管道和FIFO
- 套接字

# 8. Unix/Linux 五种 IO 模型

## 8.1. 阻塞/非阻塞、同步/异步

```cpp {class=line-numbers}

```

## 8.2. 阻塞

## 8.3. 非阻塞

## 8.4. I/O 复用

## 8.5. 信号驱动

## 8.6. 异步

```cpp {class=line-numbers}

```