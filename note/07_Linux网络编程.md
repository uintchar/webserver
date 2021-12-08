- [1. 网络结构模式](#1-网络结构模式)
  - [1.1. C/S 结构](#11-cs-结构)
  - [1.2. B/S 结构](#12-bs-结构)
- [2. MAC 地址、IP 地址和端口号](#2-mac-地址ip-地址和端口号)
- [3. 网络模型](#3-网络模型)
  - [3.1. OSI 七层模型](#31-osi-七层模型)
  - [3.2. TCP/IP 四层模型](#32-tcpip-四层模型)
- [4. 协议](#4-协议)
- [5. 网络通信的过程](#5-网络通信的过程)
- [6. 字节序和 IP 地址转换](#6-字节序和-ip-地址转换)
  - [6.1. 主机字节序](#61-主机字节序)
  - [6.2. 网络字节序](#62-网络字节序)
  - [6.3. IP 地址转换](#63-ip-地址转换)
- [7. socket 网络编程](#7-socket-网络编程)
  - [7.1. scoket 地址](#71-scoket-地址)
    - [7.1.1. 通用 socket 地址](#711-通用-socket-地址)
    - [7.1.2. 专用 socket 地址](#712-专用-socket-地址)
  - [7.2. socket 函数](#72-socket-函数)
  - [7.3. TCP 通信流程](#73-tcp-通信流程)
  - [7.4. UDP 通信流程](#74-udp-通信流程)
  - [7.5. 多进程并发服务器](#75-多进程并发服务器)
  - [7.6. 多线程并发服务器](#76-多线程并发服务器)
- [8. I/O 多路复用](#8-io-多路复用)
  - [8.1. select](#81-select)
  - [8.2. poll](#82-poll)
  - [8.3. epoll](#83-epoll)

# 1. 网络结构模式

## 1.1. C/S 结构

## 1.2. B/S 结构

# 2. MAC 地址、IP 地址和端口号

# 3. 网络模型

## 3.1. OSI 七层模型

## 3.2. TCP/IP 四层模型

# 4. 协议

# 5. 网络通信的过程

# 6. 字节序和 IP 地址转换

## 6.1. 主机字节序

## 6.2. 网络字节序

```cpp {class=line-numbers}
#include <arpa/inet.h>
#include <arpa/inet.h>
// 转换端口
uint16_t htons(uint16_t hostshort); // 主机字节序 - 网络字节序
uint16_t ntohs(uint16_t netshort); // 主机字节序 - 网络字节序
// 转IP
uint32_t htonl(uint32_t hostlong); // 主机字节序 - 网络字节序
uint32_t ntohl(uint32_t netlong); // 主机字节序 - 网络字节序
```

## 6.3. IP 地址转换

# 7. socket 网络编程

## 7.1. scoket 地址

### 7.1.1. 通用 socket 地址

```cpp {class=line-numbers}

```

### 7.1.2. 专用 socket 地址

```cpp {class=line-numbers}

```

## 7.2. socket 函数

```cpp {class=line-numbers}

```

## 7.3. TCP 通信流程 

```cpp {class=line-numbers}

```

## 7.4. UDP 通信流程

```cpp {class=line-numbers}

```

## 7.5. 多进程并发服务器

## 7.6. 多线程并发服务器

# 8. I/O 多路复用

## 8.1. select

```cpp {class=line-numbers}

```

## 8.2. poll

```cpp {class=line-numbers}

```

## 8.3. epoll

```cpp {class=line-numbers}

```