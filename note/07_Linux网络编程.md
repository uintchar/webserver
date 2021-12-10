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
  - [5.9. TCP通信流程](#59-tcp通信流程)
  - [5.10. UDP通信流程](#510-udp通信流程)
- [6. 多进程并发服务器](#6-多进程并发服务器)
- [7. 多线程并发服务器](#7-多线程并发服务器)
- [8. I/O多路复用](#8-io多路复用)
  - [8.1. select](#81-select)
  - [8.2. poll](#82-poll)
  - [8.3. epoll](#83-epoll)
- [9. Unix/Linux 五种 IO 模型](#9-unixlinux-五种-io-模型)
  - [9.1. 阻塞/非阻塞、同步/异步](#91-阻塞非阻塞同步异步)
  - [9.2. 阻塞](#92-阻塞)
  - [9.3. 非阻塞](#93-非阻塞)
  - [9.4. I/O 复用](#94-io-复用)
  - [9.5. 信号驱动](#95-信号驱动)
  - [9.6. 异步](#96-异步)

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


// 将网络字节序的整数，转换成点分十进制的IP地址字符串
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
  *  - 
  * @param: 
  *  - 
  * @return:
  *  - 成功：
  *  - 失败：
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
  *  - 
  * @param: 
  *  - 
  * @return:
  *  - 成功：
  *  - 失败：
  **/
```

## 5.4. listen()

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

## 5.5. accept()

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

## 5.6. connect()

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

## 5.7. read()/recv()/recvfrom()

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

## 5.8. write()/send()/sendto()

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

## 5.9. TCP通信流程 

```cpp {class=line-numbers}
netstat -anp | grep port_num
```

## 5.10. UDP通信流程

```cpp {class=line-numbers}

```

# 6. 多进程并发服务器

# 7. 多线程并发服务器

# 8. I/O多路复用

## 8.1. select

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

## 8.2. poll

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

## 8.3. epoll

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

# 9. Unix/Linux 五种 IO 模型

## 9.1. 阻塞/非阻塞、同步/异步

```cpp {class=line-numbers}

```

## 9.2. 阻塞

## 9.3. 非阻塞

## 9.4. I/O 复用

## 9.5. 信号驱动

## 9.6. 异步

```cpp {class=line-numbers}

```