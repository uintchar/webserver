- [1. 进程概述](#1-进程概述)
  - [1.1. 程序和进程](#11-程序和进程)
  - [1.2. 进程控制块 PCB](#12-进程控制块-pcb)
  - [1.3. 进程状态转换](#13-进程状态转换)
- [2. Linux 进程相关命令](#2-linux-进程相关命令)
  - [2.1. ps](#21-ps)
  - [2.2. top](#22-top)
  - [2.3. kill](#23-kill)
  - [2.4. 进程号和相关函数](#24-进程号和相关函数)
  - [2.5. 获取和设置资源限制](#25-获取和设置资源限制)
  - [2.6. 应用示例](#26-应用示例)
- [3. 进程的创建和退出](#3-进程的创建和退出)
  - [3.1. fork](#31-fork)
  - [3.2. 父子进程的虚拟地址空间](#32-父子进程的虚拟地址空间)
  - [3.3. gdb 多进程调试](#33-gdb-多进程调试)
  - [3.4. exec 函数族](#34-exec-函数族)
  - [3.5. 进程退出](#35-进程退出)
    - [3.5.1. exit 和 _exit](#351-exit-和-_exit)
    - [3.5.2. 孤儿进程](#352-孤儿进程)
    - [3.5.3. 僵尸进程](#353-僵尸进程)
    - [3.5.4. 进程回收](#354-进程回收)
  - [3.6. 应用示例](#36-应用示例)
- [4. 终端、会话和守护进程](#4-终端会话和守护进程)
  - [4.1. 终端](#41-终端)
  - [4.2. 进程组](#42-进程组)
  - [4.3. 会话](#43-会话)
  - [4.4. 进程组、会话操作函数](#44-进程组会话操作函数)
  - [4.5. 守护进程](#45-守护进程)
  - [4.6. 应用示例](#46-应用示例)
    - [4.6.1. 每 1s 向磁盘文件打印当前系统时间的守护进程](#461-每-1s-向磁盘文件打印当前系统时间的守护进程)
- [5. 进程间通信](#5-进程间通信)
  - [5.1. 匿名管道](#51-匿名管道)
    - [5.1.1. 管道的特点](#511-管道的特点)
    - [5.1.2. 管道的数据结构](#512-管道的数据结构)
    - [5.1.3. 匿名管道的使用](#513-匿名管道的使用)
    - [5.1.4. 应用示例](#514-应用示例)
      - [5.1.4.1. 父进程向子进程发送消息](#5141-父进程向子进程发送消息)
      - [5.1.4.2. 实现 `ps aux | grep xxx` 父子进程间通信](#5142-实现-ps-aux--grep-xxx-父子进程间通信)
      - [5.1.4.3. 设置管道非阻塞](#5143-设置管道非阻塞)
  - [5.2. 有名管道 FIFO](#52-有名管道-fifo)
    - [5.2.1. 有名管道的特点](#521-有名管道的特点)
    - [5.2.2. 有名管道的使用](#522-有名管道的使用)
    - [5.2.3. 应用示例](#523-应用示例)
      - [5.2.3.1. 不同进程使用有名管道进行通信](#5231-不同进程使用有名管道进行通信)
  - [5.3. 内存映射](#53-内存映射)
    - [5.3.1. 内存映射相关系统调用](#531-内存映射相关系统调用)
    - [5.3.2. 应用示例](#532-应用示例)
  - [5.4. 共享内存](#54-共享内存)
    - [5.4.1. 共享内存的概念](#541-共享内存的概念)
    - [5.4.2. 共享内存的使用步骤](#542-共享内存的使用步骤)
    - [5.4.3. 共享内存操作函数](#543-共享内存操作函数)
    - [5.4.4. 应用示例](#544-应用示例)
  - [5.5. POSIX消息队列](#55-posix消息队列)
    - [5.5.1. POSIX消息队列概述](#551-posix消息队列概述)
    - [5.5.2. mq_open()](#552-mq_open)
    - [5.5.3. mq_close()](#553-mq_close)
    - [5.5.4. mq_unlink()](#554-mq_unlink)
    - [5.5.5. mq_send()](#555-mq_send)
    - [5.5.6. mq_receive()](#556-mq_receive)
    - [5.5.7. mq_notify()](#557-mq_notify)
    - [5.5.8. mq_attr](#558-mq_attr)
    - [5.5.9. POSIX消息队列限制](#559-posix消息队列限制)
    - [5.5.10. 应用示例](#5510-应用示例)
  - [5.6. 信号](#56-信号)
    - [5.6.1. 信号的概念](#561-信号的概念)
    - [5.6.2. 信号的类型](#562-信号的类型)
    - [5.6.3. 信号的发送](#563-信号的发送)
      - [5.6.3.1. kill()](#5631-kill)
      - [5.6.3.2. raise()](#5632-raise)
      - [5.6.3.3. abort()](#5633-abort)
    - [5.6.4. 信号的等待](#564-信号的等待)
    - [5.6.5. 信号的捕捉](#565-信号的捕捉)
      - [5.6.5.1. signal()](#5651-signal)
      - [5.6.5.2. sigaction()](#5652-sigaction)
    - [5.6.6. 信号集和信号掩码](#566-信号集和信号掩码)
      - [5.6.6.1. sigprocmask()](#5661-sigprocmask)
      - [5.6.6.2. sigpending()](#5662-sigpending)
    - [5.6.7. 信号处理器](#567-信号处理器)
      - [5.6.7.1. 设计信号处理器函数](#5671-设计信号处理器函数)
        - [5.6.7.1.1. 可重入函数和非可重入函数](#56711-可重入函数和非可重入函数)
        - [5.6.7.1.2. 异步信号安全函数](#56712-异步信号安全函数)
        - [5.6.7.1.3. 全局变量和 sig_atomic_t 数据类型](#56713-全局变量和-sig_atomic_t-数据类型)
      - [5.6.7.2. 终止信号处理器函数的其他方法](#5672-终止信号处理器函数的其他方法)
      - [5.6.7.3. 在备选栈中处理信号：sigaltstack()](#5673-在备选栈中处理信号sigaltstack)
      - [5.6.7.4. SA_SIGINFO 标志](#5674-sa_siginfo-标志)
      - [5.6.7.5. 系统调用的中断和重启](#5675-系统调用的中断和重启)
    - [5.6.8. 信号的高级特性](#568-信号的高级特性)
      - [5.6.8.1. 核心转储文件](#5681-核心转储文件)
      - [5.6.8.2. 传递、处置及处理特殊情况](#5682-传递处置及处理特殊情况)
      - [5.6.8.3. 可中断和不可中断的进程睡眠状态](#5683-可中断和不可中断的进程睡眠状态)
      - [5.6.8.4. 硬件产生的信号](#5684-硬件产生的信号)
      - [5.6.8.5. 信号的同步生成和异步生成](#5685-信号的同步生成和异步生成)
      - [5.6.8.6. 信号传递的时机和顺序](#5686-信号传递的时机和顺序)
      - [5.6.8.7. 实时信号](#5687-实时信号)
        - [5.6.8.7.1. 发送实时信号：sigqueue()](#56871-发送实时信号sigqueue)
        - [5.6.8.7.2. 处理实时信号](#56872-处理实时信号)
      - [5.6.8.8. 使用掩码来等待信号：sigsuspended()](#5688-使用掩码来等待信号sigsuspended)
      - [5.6.8.9. 同步方式等待信号](#5689-同步方式等待信号)
      - [5.6.8.10. 通过文件描述符来获取信号](#56810-通过文件描述符来获取信号)
    - [5.6.9. 信号和线程](#569-信号和线程)
    - [5.6.10. 应用示例](#5610-应用示例)
      - [5.6.10.1. 信号捕捉实现周期性定时器](#56101-信号捕捉实现周期性定时器)
      - [5.6.10.2. 使用SIGCHLD信号解决僵尸进程的问题](#56102-使用sigchld信号解决僵尸进程的问题)
      - [5.6.10.3. 信号集操作函数范例](#56103-信号集操作函数范例)
- [6. 时间](#6-时间)
  - [6.1. 日历时间和时间转换函数](#61-日历时间和时间转换函数)
  - [6.2. 软件时钟（jiffies）](#62-软件时钟jiffies)
  - [6.3. 进程时间](#63-进程时间)
    - [6.3.1. times()](#631-times)
    - [6.3.2. clock()](#632-clock)
- [7. 定时器和休眠](#7-定时器和休眠)
  - [7.1. 间隔定时器](#71-间隔定时器)
    - [7.1.1. setitimer()](#711-setitimer)
    - [7.1.2. alarm()](#712-alarm)
  - [7.2. 定时器的调度和精度](#72-定时器的调度和精度)
  - [7.3. 休眠进程](#73-休眠进程)
    - [7.3.1. sleep()](#731-sleep)
    - [7.3.2. nanosleep()](#732-nanosleep)
  - [7.4. POSIX 时钟](#74-posix-时钟)
  - [7.5. POSIX 间隔定时器](#75-posix-间隔定时器)
    - [7.5.1. timer_create()](#751-timer_create)
    - [7.5.2. timer_settime()](#752-timer_settime)
    - [7.5.3. timer_delete()](#753-timer_delete)
    - [7.5.4. 通过信号通知](#754-通过信号通知)
    - [7.5.5. 通过线程通知](#755-通过线程通知)
    - [7.5.6. 定时器溢出](#756-定时器溢出)
  - [7.6. 利用文件描述符进行通知的定时器： timerfd API](#76-利用文件描述符进行通知的定时器-timerfd-api)

# 1. 进程概述

## 1.1. 程序和进程

## 1.2. 进程控制块 PCB

## 1.3. 进程状态转换

# 2. Linux 进程相关命令

## 2.1. ps

查看进程的 status 文件： cat /proc/pid/status

## 2.2. top

## 2.3. kill

## 2.4. 进程号和相关函数

## 2.5. 获取和设置资源限制

```cpp {class=line-numbers}
// shell 命令
ulimit

// 系统调用
#include <sys/time.h>
#include <sys/resource.h>

int getrlimit(int resource, struct rlimit *rlim);
int setrlimit(int resource, const struct rlimit *rlim);

int prlimit(pid_t pid, int resource, const struct rlimit *new_limit, struct rlimit *old_limit);
```

## 2.6. 应用示例

# 3. 进程的创建和退出

## 3.1. fork

## 3.2. 父子进程的虚拟地址空间

- 两者虚拟地址空间中内容的差别
- 写时拷贝

## 3.3. gdb 多进程调试

- `fork-follow-mode`
- `detch-on-fork`

## 3.4. exec 函数族

- execl

- execlp

## 3.5. 进程退出

### 3.5.1. exit 和 _exit

### 3.5.2. 孤儿进程

### 3.5.3. 僵尸进程

### 3.5.4. 进程回收

- `wait`
- `waitpid`

## 3.6. 应用示例

# 4. 终端、会话和守护进程

## 4.1. 终端

- 在 UNIX 系统中，用户通过终端登录系统后得到一个 shell 进程，这个终端成为 shell 进程的控制终端；
- 进程中，控制终端是保存在 PCB 中的信息，而 `fork()` 会复制 PCB 中的信息，因此由 shell 进程启动的其它进程的控制终端也是这个终端；
- 默认情况下（没有重定向），每个进程的标准输入、标准输出和标准错误输出都指向控制终端，进程从标准输入读也就是读用户的键盘输入，进程往标准输出或标准错误输出写也就是输出到显示器上；
- 在控制终端输入一些特殊的控制键可以给前台进程发信号，例如 `Ctrl + C` 会产生 `SIGINT` 信号， `Ctrl + \` 会产生 `SIGQUIT` 信号；
- `echo $$`：显示当前 shell 进程的进程号；

## 4.2. 进程组

- 进程组和会话在进程之间形成了一种两级层次关系：进程组是一组相关进程的集合，会话是一组相关进程组的集合。进程组和会话是为支持 shell 作业控制而定义的抽象概念，用户通过 shell 能够交互式地在前台或后台运行命令；
- 进行组由一个或多个共享同一进程组标识符（PGID）的进程组成。一个进程组拥有一个进程组首进程，该进程是创建该组的进程，其进程 ID 为该进程组的 ID，新进程会继承其父进程所属的进程组 ID；
- 进程组拥有一个生命周期，其开始时间为首进程创建组的时刻，结束时间为最后一个成员进程退出组的时刻。一个进程可能会因为终止而退出进程组，也可能会因为加入了另外一个进程组而退出进程组。进程组首进程无需是最后一个离开进程组的成员；

## 4.3. 会话

- 会话是一组进程组的集合。会话首进程是创建该新会话的进程，其进程 ID 会成为会话 ID。新进程会继承其父进程的会话 ID；
- 一个会话中的所有进程共享单个控制终端。控制终端会在会话首进程首次打开一个终端设备时被建立。一个终端最多可能会成为一个会话的控制终端；
- 在任一时刻，会话中的其中一个进程组会成为终端的**前台进程组**，其他进程组会成为**后台进程组**。只有前台进程组中的进程才能从控制终端中读取输入。当用户在控制终端中输入终端字符生成信号后，该信号会被发送到前台进程组中的所有成员；
- 当控制终端的连接建立起来之后，会话首进程会成为该终端的**控制进程**；
- 例子：
  ```cpp {class=line-numbers}
  find / 2 > /dev/null | wc -l & // & 用于设置后台进程
  sort < longlist | uniq -c
  ```
  ![进程组-会话-控制终端间的关系](webserver/note/figure/进程组_会话_控制终端间的关系.PNG)

## 4.4. 进程组、会话操作函数

```cpp {class=line-numbers}
#include <sys/types.h>
#include <unistd.h>

pid_t getpgid(pid_t pid);
/**
  * @brief:
  *  - 获取进程号为 pid 的进程的进程组 id；
  *  - 如果 pid 设为 0，则获取的是调用此函数的进程的进程组 id；
  * @param: 
  *  - pid_t pid
  * @return:
  *  - 成功：进程组 id
  *  - 失败：-1，并设置 errno
  **/

pid_t getpgrp(void); // POSIX.1 version
/**
  * @brief:
  *  - 获取调用进程的进程组 id；
  * @param: 
  * @return:
  **/

pid_t getpgrp(pid_t pid); // BSD version
/**
  * @brief:
  * @param: 
  * @return:
  **/

int setpgid(pid_t pid, pid_t pgid);
/**
  * @brief:
  *  - 将进程号为 pid 的进程的进程组设为 pgid；
  *  - 如果 pid 为 0，则使用调用进程的 pid；如果 pgid 为 0，则设置由 pid 指定的进程的 pgid 和该进程的 pgid 相同；
  *  - 将一个进程从一个进程组移动到另一个进程组时，两个进程组必须属于同一个会话；
  * @param: 
  *  - pid_t pid
  *  - pid_t pgid
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/

int setpgrp(void); // System V version
/**
  * @brief:
  *  - 等效于 setpgid(0, 0)
  * @param: 
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/

int setpgrp(pid_t pid, pid_t pgid);  // BSD version
/**
  * @brief:
  * @param: 
  * @return:
  **/

// 获取和设置会话 id
pid_t getsid(pid_t pid);
pid_t setsid(void);
```

## 4.5. 守护进程

- 守护进程（Daemon Process），也就是通常说的 Daemon 进程（精灵进程），是 Linux 中的后台服务进程。它是一个生存期较长的进程，通常独立于控制终端并且周
期性地执行某种任务或等待处理某些发生的事件。一般采用以 d 结尾的名字；
- 守护进程具备下列特征：
  - 生命周期很长，守护进程会在系统启动的时候被创建并一直运行直至系统被关闭；
  - 在后台运行并且不拥有控制终端。没有控制终端确保了内核永远不会为守护进程自动生成任何控制信号以及终端相关的信号（如 `SIGINT`、 `SIGQUIT`）;
- Linux 的大多数服务器就是用守护进程实现的。比如， Internet 服务器 inetd，Web 服务器 httpd 等；
- 守护进程的创建步骤：
  - 执行一个 `fork()`，之后父进程退出，子进程继续执行；
  - 子进程调用 `setsid()` 开启一个新会话；
  - 清除进程的 `umask` 以确保当守护进程创建文件和目录时拥有所需的权限；
  - 修改进程的当前工作目录，通常会改为根目录（/）；
  - 关闭守护进程从其父进程继承而来的所有打开着的文件描述符；
  - 在关闭了文件描述符 0、 1、 2 之后，守护进程通常会打开 `/dev/null` 并使用 `dup2()` 使所有这些描述符指向这个设备；
  - 核心业务逻辑；

## 4.6. 应用示例

### 4.6.1. 每 1s 向磁盘文件打印当前系统时间的守护进程

```cpp {class=line-numbers}
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// 捕捉到信号之后，获取系统时间，写入磁盘文件
void work(int num)
{
  time_t abs_tm = time(NULL); // 返回自 Epoch 1970-01-01 00:00:00 +0000 (UTC) 时到当前时刻所经过的秒数
  struct tm *loc_tm = localtime(&abs_tm);
  char *str = asctime(loc_tm);

  int fd = open("time.txt", O_RDWR | O_CREAT | O_APPEND, 0664);
  write(fd, str, strlen(str));
  close(fd);
}

int main()
{
  // 创建子进程，退出父进程
  pid_t pid = fork();
  if (pid < 0)
  {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  else if (pid > 0)
  {
    exit(0);
  }

  // 将子进程重新创建一个会话
  setsid();

  // 设置掩码
  umask(022);

  // 更改工作目录
  chdir("/home/hrl/");

  // 关闭、重定向文件描述符
  int fd = open("/dev/null", O_RDWR);
  dup2(fd, STDIN_FILENO);
  dup2(fd, STDOUT_FILENO);
  dup2(fd, STDERR_FILENO);

  // 业务逻辑：使用周期性定时器实现每秒向磁盘文件写入当前系统时间
  struct sigaction sig_act;
  sig_act.sa_flags = 0;
  sig_act.sa_handler = work;
  sigemptyset(&sig_act.sa_mask);
  sigaction(SIGALRM, &sig_act, NULL);

  struct itimerval it_val;
  it_val.it_value.tv_sec = 1;
  it_val.it_value.tv_usec = 0;
  it_val.it_interval.tv_sec = 1;
  it_val.it_interval.tv_usec = 0;

  // 创建定时器
  setitimer(ITIMER_REAL, &it_val, NULL);

  // 使后台进程一直运行
  while (1);

  return 0;
}
```

# 5. 进程间通信

- 同一主机进程间通信
  - Unix 进程间通信方式
    - 匿名管道
    - 有名管道
    - 信号
  - System V & Posix 进程间通信方式
    - 消息队列
    - 共享内存
    - 信号量
- 不同主机进程间通信
  - socket

## 5.1. 匿名管道

### 5.1.1. 管道的特点

- 管道其实是一个在内核内存中维护的缓冲区，其存储能力是有限的，不同的操作系统大小不一定相同；
- 管道拥有文件的性质：读操作、写操作，可以按照操作文件的方式对管道进行操作；匿名管道没有文件实体，有名管道有文件实体，但不存储数据；
- 一个管道是一个字节流，使用管道时不存在消息或者消息边界的概念，从管道读取数据的进程可以读取任意大小的数据块，而不管写入进程写入管道的数据块的大小是多少；
- 通过管道传递的数据是顺序的，从管道中读取出来的字节的顺序和它们被写入管道的顺序是完全一样的；
- 在管道中的数据的传递方向是单向的，一端用于写入，一端用于读取，管道是半双工的；
- 从管道读数据是一次性操作，数据一旦被读走，它就从管道中被抛弃，释放空间以便写更多的数据，在管道中无法使用 `lseek()` 来随机的访问数据；
- 匿名管道只能在具有公共祖先的进程（父进程与子进程，或者两个兄弟进程，具有亲缘关系）之间使用；因为父子进程之间共享打开的文件描述符，所以要先创建管道，再进行 `fork`；
- 对于匿名管道，管道默认是阻塞的：如果管道中没有数据，`read` 阻塞，如果管道满了，`write` 阻塞；
- 使用管道时，需要注意以下几种特殊的情况（假设都是阻塞I/O操作）
  - 读管道：
    - 管道中有数据：`read` 返回实际读到的字节数。
    - 管道中无数据：
      - 写端被全部关闭：`read` 返回 0（相当于读到文件的末尾）
      - 写端未完全关闭：`read` 阻塞等待
  - 写管道：
    - 管道读端被全部关闭，进程异常终止（进程收到 `SIGPIPE` 信号）
    - 管道读端未全部关闭：
      - 管道已满：`write` 阻塞
      - 管道未满：`write` 将数据写入，并返回实际写入的字节数

### 5.1.2. 管道的数据结构

- 环形队列；

### 5.1.3. 匿名管道的使用

- 创建匿名管道

  ```cpp {class=line-numbers}
  #include <unistd.h>
  int pipe(int pipefd[2]);
  /**
   * @brief:
   *  - 创建一个匿名管道，用来进程间通信
   * @param: 
   *  - int pipefd[2]，传出参数
   *    - pipefd[0] 管道的读端
   *    - pipefd[1] 管道的写端
   * @return:
   *  - 成功 0
   *  - 失败 -1
   **/
  ```

- 查看管道缓冲区的大小

  ```cpp {class=line-numbers}
  // 命令方式查看：
  ulimit -a

  // 函数方式查看：
  #include <unistd.h>
  long fpathconf(int fd, int name);
  /**
   * @brief:
   *  - 获取文件描述符 fd 所引用文件的配置项 name 的值
   * @param:
   *  - int fd: 打开的文件描述符
   *  - int name: 具体的配置项名
   * @return:
   *  - 配置项的值
   **/
  
  // example:
  long size = fpathconf(pipefd[0], _PC_PIPE_BUF);
  ```
### 5.1.4. 应用示例

#### 5.1.4.1. 父进程向子进程发送消息

```cpp {class=line-numbers}
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
  // 创建管道
  int pipefd[2] = {0};
  if (pipe(pipefd) == -1)
  {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  // 创建子进程
  pid_t pid = fork();
  if (pid == -1)
  {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  // 父进程向管道写消息：从标准输入获取消息并发送给子进程，当输入 quit 时退出
  if (pid > 0)
  {
    close(pipefd[0]);
    char wbuf[1024] = {0};

    while (1)
    {
      // fgets(wbuf, 1024, stdin); // fgets 从键盘读取数据时会把换行符（回车）读入，并添加 '\0'
      gets(wbuf); // gets 从键盘读取数据时不会把换行符（回车）读入，并添加 '\0'，gets 是不安全的，因为没有指定缓冲区的大小
      write(pipefd[1], wbuf, strlen(wbuf) + 1);
      if (strcmp(wbuf, "quit") == 0)
        break;
      memset(wbuf, 0, 1024);
    }

    close(pipefd[1]);
    exit(EXIT_SUCCESS);
  }
  // 子进程从管道读消息并将其打印到标准输出中
  else
  {
    close(pipefd[1]);
    char rbuf[1024] = {0};

    while (1)
    {
      read(pipefd[0], rbuf, 1024);
      printf("recv from parent:");
      fputs(rbuf, stdout);
      if (strcmp(rbuf, "quit") == 0)
        break;
      memset(rbuf, 0, 1024);
    }

    close(pipefd[0]);
    exit(EXIT_SUCCESS);
  }

  return 0;
}
```

#### 5.1.4.2. 实现 `ps aux | grep xxx` 父子进程间通信

```cpp {class=line-numbers}
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int main()
{
  // 创建一个管道
  int fd[2];
  if (pipe(fd) == -1)
  {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  // 创建子进程
  pid_t pid = fork();
  if (pid > 0)
  {
    close(fd[1]);
    char buf[1024] = {0};

    int len = -1;
    while ((len = read(fd[0], buf, sizeof(buf) - 1)) > 0)
    {
      // todo: 过滤数据输出
      printf("%s", buf);
      memset(buf, 0, 1024);
    }

    wait(NULL);
  }
  else if (pid == 0)
  {
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO); // 将标准输出重定向到管道的写端
    execlp("ps", "ps", "aux", NULL); // 执行 ps aux，其输出将通过管道写端写入管道
    perror("execlp");
    exit(0);
  }
  else
  {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  return 0;
}
```

#### 5.1.4.3. 设置管道非阻塞

```cpp {class=line-numbers}
/**
* @description:
*  - 设置管道非阻塞
*  - int flags = fcntl(fd[0], F_GETFL)；
*  - flags |= O_NONBLOCK;
*  - fcntl(fd[0], F_SETFL, flags);
**/

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main()
{

  // 在fork之前创建管道
  int pipefd[2];
  if (pipe(pipefd) == -1)
  {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  // 创建子进程
  pid_t pid = fork();
  if (pid > 0)
  {
    printf("i am parent process, pid : %d\n", getpid());
    close(pipefd[1]);

    char buf[1024] = {0};

    int flags = fcntl(pipefd[0], F_GETFL); // 获取原来的 flag
    flags |= O_NONBLOCK;                   // 修改 flag 的值
    fcntl(pipefd[0], F_SETFL, flags);      // 设置新的 flag

    while (1)
    {
      int len = read(pipefd[0], buf, sizeof(buf));
      printf("len : %d\n", len);
      printf("parent recv : %s, pid : %d\n", buf, getpid());
      memset(buf, 0, 1024);
      sleep(1);
    }
  }
  else if (pid == 0)
  {
    printf("i am child process, pid : %d\n", getpid());
    close(pipefd[0]);

    char buf[1024] = {0};
    while (1)
    {
      // 向管道中写入数据
      const char *str = "hello,i am child";
      write(pipefd[1], str, strlen(str) + 1);
      sleep(5);
    }
  }
  return 0;
}
```

## 5.2. 有名管道 FIFO

### 5.2.1. 有名管道的特点

- 有名管道有文件实体，提供了路径名与之关联，但不存储数据；
- FIFO 不仅可以用于具有亲缘关系的进程间通信，还可以用于不存在亲缘关系的进程间通信；
- FIFO 在文件系统中作为一个特殊文件存在，但 FIFO 中的内容却存放在内存中；
- 当使用 FIFO 的进程退出后， FIFO 文件将继续保存在文件系统中以便以后使用；
- 有名管道的注意事项：
  - 一个为只读而打开一个管道的进程会阻塞，直到另外一个进程为只写打开管道
  - 一个为只写而打开一个管道的进程会阻塞，直到另外一个进程为只读打开管道
  - 读管道：
    - 管道中有数据，`read` 返回实际读到的字节数
    - 管道中无数据：
      - 管道写端被全部关闭，`read` 返回0，（相当于读到文件末尾）
      - 管道写端未全部关闭，`read` 阻塞等待
  - 写管道：
    - 管道读端被全部关闭：进程异常终止（收到一个 `SIGPIPE` 信号）
    - 管道读端未全部关闭：
      - 管道已满，`write` 会阻塞
      - 管道未满，`write` 将数据写入，并返回实际写入的字节数。

### 5.2.2. 有名管道的使用

- 创建有名管道

  ```cpp {class=line-numbers}
  // 命令方式：
  mkfifo pipe_name

  // 函数方式：
  #include <sys/types.h>
  #include <sys/stat.h>
  int mkfifo(const char *pathname, mode_t mode);
  /**
     * @brief:
     *  - 创建一个有名管道，用来进程间通信
     * @param: 
     *  - const char *pathname: FIFO 管道的路径名
     *  - mode_t mode: 文件访问权限设置
     * @return:
     *  - 成功：0
     *  - 失败：-1，并设置错误号
     **/
  ```

### 5.2.3. 应用示例

#### 5.2.3.1. 不同进程使用有名管道进行通信

```cpp {class=line-numbers}
/**
 * @brief:
 *  - 进程 A 侧的程序代码
 **/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main()
{
  // 判断有名管道文件是否存在
  if (access("fifo1", F_OK) == -1)
  {
    printf("管道不存在，创建对应的有名管道 fifo1\n");
    if (mkfifo("fifo1", 0664) == -1)
    {
      perror("mkfifo");
      exit(0);
    }
  }

  if (access("fifo2", F_OK) == -1)
  {
    printf("管道不存在，创建对应的有名管道 fifo2\n");
    if (mkfifo("fifo2", 0664) == -1)
    {
      perror("mkfifo");
      exit(0);
    }
  }

  // 以只写的方式打开管道 fifo1
  int fdw = open("fifo1", O_WRONLY);
  if (fdw == -1)
  {
    perror("open");
    exit(0);
  }
  printf("打开管道fifo1成功，等待写入...\n");

  // 以只读的方式打开管道fifo2
  int fdr = open("fifo2", O_RDONLY);
  if (fdr == -1)
  {
    perror("open");
    exit(0);
  }
  printf("打开管道fifo2成功，等待读取...\n");

  char buf[1024];

  // 循环的写读数据
  while (1)
  {
    memset(buf, 0, 1024);
    fgets(buf, 1024, stdin); // 会读取换行符
    int len = write(fdw, buf, strlen(buf));
    if (len == -1)
    {
      perror("write");
      exit(0);
    }

    memset(buf, 0, 1024);
    len = read(fdr, buf, 1024);
    if (len <= 0)
    {
      perror("read");
      break;
    }
    printf("buf: %s\n", buf);
  }

  close(fdr);
  close(fdw);

  return 0;
}
```

```cpp {class=line-numbers}
/**
 * @brief:
 *  - 进程 B 侧的程序代码
 **/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main()
{
  // 判断有名管道文件是否存在
  if (access("fifo1", F_OK) == -1)
  {
    printf("管道不存在，创建对应的有名管道 fifo1\n");
    if (mkfifo("fifo1", 0664) == -1)
    {
      perror("mkfifo");
      exit(0);
    }
  }

  if (access("fifo2", F_OK) == -1)
  {
    printf("管道不存在，创建对应的有名管道 fifo2\n");
    if (mkfifo("fifo2", 0664) == -1)
    {
      perror("mkfifo");
      exit(0);
    }
  }

  // 以只读的方式打开管道 fifo1
  int fdr = open("fifo1", O_RDONLY);
  if (fdr == -1)
  {
    perror("open");
    exit(0);
  }
  printf("打开管道fifo1成功，等待读取...\n");
  
  // 以只写的方式打开管道 fifo2
  int fdw = open("fifo2", O_WRONLY);
  if (fdw == -1)
  {
    perror("open");
    exit(0);
  }
  printf("打开管道fifo2成功，等待写入...\n");

  char buf[1024];

  // 循环的读写数据
  while (1)
  {
    memset(buf, 0, 1024);
    int len = read(fdr, buf, 1024);
    if (len <= 0)
    {
      perror("read");
      break;
    }
    printf("buf: %s\n", buf);

    memset(buf, 0, 1024);
    fgets(buf, 1024, stdin); // 会读取换行符
    len = write(fdw, buf, strlen(buf));
    if (len == -1)
    {
      perror("write");
      exit(0);
    }
  }

  close(fdr);
  close(fdw);

  return 0;
}
```

## 5.3. 内存映射

### 5.3.1. 内存映射相关系统调用

- `mmap`
  
  ```cpp {class=line-numbers}
  /**
    * @brief:
    *  - 
    * @param: 
    *  - 
    *  - 
    * @return:
    *  - 成功：
    *  - 失败：
    **/
  ```

- `munmap`

  ```cpp {class=line-numbers}
  /**
    * @brief:
    *  - 
    * @param: 
    *  - 
    *  - 
    * @return:
    *  - 成功：
    *  - 失败：
    **/
  ```

### 5.3.2. 应用示例

- 父子进程使用内存映射通信

  ```cpp {class=line-numbers}
  /**
    * @brief:
    *  - 
    **/
  ```

- 普通进程使用内存映射通信

  ```cpp {class=line-numbers}
  /**
    * @brief:
    *  - 
    **/
  ```

- 内存映射实现文件拷贝功能（文件不能太大）

  ```cpp {class=line-numbers}
  /**
    * @brief:
    *  - 
    **/
  ```

- 匿名映射

  ```cpp {class=line-numbers}
  /**
    * @brief:
    *  - 
    **/
  ```

## 5.4. 共享内存

### 5.4.1. 共享内存的概念

### 5.4.2. 共享内存的使用步骤

### 5.4.3. 共享内存操作函数

```cpp {class=line-numbers}
/**
  * @brief:
  *  - 
  * @param: 
  *  - 
  *  - 
  * @return:
  *  - 成功：
  *  - 失败：
  **/
```

### 5.4.4. 应用示例

## 5.5. POSIX消息队列

### 5.5.1. POSIX消息队列概述

```cpp {class=line-numbers}
mq_open() 函数创建一个新消息队列或打开一个既有队列，返回后续调用中会用到的消息队列描述符。
mq_send() 函数向队列写入一条消息。
mq_receive() 函数从队列中读取一条消息。
mq_close() 函数关闭进程之前打开的一个消息队列。
mq_unlink() 函数删除一个消息队列名并当所有进程关闭该队列时对队列进行标记以便删除
mq_notify() 函数允许一个进程向一个队列注册接收消息通知。在注册完之后，当一条消息可用时会通过发送一个信号或在一个单独的线程中调用一个函数来通知进程。
```

### 5.5.2. mq_open()

```cpp {class=line-numbers}
#include <fcntl.h>    /* For O_* constants */
#include <sys/stat.h> /* For mode constants */
#include <mqueue.h>

mqd_t mq_open(const char *name, int oflag);
mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);

struct mq_attr
{
  long mq_flags;   /* Flags: 0, or O_NONBLOCK (ignored for mq_open()) */
  long mq_maxmsg;  /* Max. # of messages on queue */
  long mq_msgsize; /* Max. message size (bytes) */
  long mq_curmsgs; /* # of messages currently in queue (ignored for mq_open()) */
};

/* Link with - lrt. */
/**
  * @brief:
  *  - 函数创建一个新消息队列或打开一个既有队列，返回后续调用中会用到的消息队列描述符
  *  - Linux 中 POSIX 消息队列描述符被实现为文件描述符
  * @param: 
  *  - name：标识消息队列，其命名需以 '/' 开头，且不超过 NAME_MAX(255) 个字符
  *  - oflag：位掩码
  *    - O_CREAT：队列不存在时创建队列
  *    - O_EXCL：与 O_CREAT 一起排他地创建队列
  *    - O_RDONLY：只读打开
  *    - O_WRONLY：只写打开
  *    - O_RDWR：读写打开
  *    - O_NOBLOCK：非阻塞模式打开
  *  - mode：位掩码，当创建新队列时需指定相关权限，和创建文件时指定权限类似
  *  - attr：mq_attr 结构体，指定消息队列的属性，默认属性则设为 NULL
  * @return:
  *  - 成功：返回消息队列描述符，Linux 上 mqd_t 是 int，Solaris 上是 void *
  *  - 失败：-1，并设置 errno
  **/
```

### 5.5.3. mq_close()

```cpp {class=line-numbers}
#include <mqueue.h>

int mq_close(mqd_t mqdes);

/* Link with - lrt. */
/**
  * @brief:
  *  - 关闭已打开的消息队列描述符 mqdes
  *  - 如果调用进程已经通过 mqdes 在队列上注册了消息通知，那么通知注册会自动被删除，并且另一个进程随后可以向该队列注册消息通知
  *  - 当进程终止或调用 exec() 时，消息队列描述符会被自动关闭
  *  - 与文件上的 close()一样，关闭一个消息队列并不会删除该队列，要删除队列则需要使用 mq_unlink()
  * @param: 
  *  - mqdes：先前已打开的消息队列描述符
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

### 5.5.4. mq_unlink()

```cpp {class=line-numbers}
 #include <mqueue.h>

int mq_unlink(const char *name);

/* Link with -lrt. */
/**
  * @brief:
  *  - 删除 name 标记的消息队列，并将队列标记为在所有进程使用完该队列之后销毁该队列
  *  - 可能会立即删除，但前提是所有打开该队列的进程已经关闭了该队列
  * @param: 
  *  - name：要删除的消息队列的描述符
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

### 5.5.5. mq_send()

```cpp {class=line-numbers}
#include <time.h>
#include <mqueue.h>

int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);
int mq_timedsend(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio, 
                 const struct timespec *abs_timeout);

/* 将超时时间描述为自新纪元到现在的一个绝对值 */
struct timespec
{
  time_t tv_sec; /* seconds */
  long tv_nsec;  /* nanoseconds */
};

/* Link with -lrt. */
/**
  * @brief:
  *  - 将位于 msg_ptr 指向的缓冲区中的消息添加到描述符 mqdes 所引用的消息队列中
  *  - 当消息队列满时会阻塞直到有可用空间或者在 O_NONBLOCK 情况下立即失败返回 EAGAIN 错误
  * @param: 
  *  - mqdes：消息队列描述符
  *  - msg_ptr：待发送消息所在缓冲区地址
  *  - msg_len：待发送消息的长度，可以为0，但是不能超过 mq_msgsize，否则返回 EMSGSIZE 错误
  *  - msg_prio：优先级（0 表示最低优先级），无需优先级则可都设为 0
  *  - abs_timeout：阻塞情况下可以设置阻塞一定超时时长后仍未成功发送消息则立即失败返回 ETIMEDOUT 错误
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  *    - EAGAIN：非阻塞情况下接收消息失败返回
  *    - ETIMEDOUT：阻塞情况下超时未发送消息失败返回
  **/
```

### 5.5.6. mq_receive()

```cpp {class=line-numbers}
#include <time.h>
#include <mqueue.h>

ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);
ssize_t mq_timedreceive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio,
                        const struct timespec *abs_timeout);

/* 将超时时间描述为自新纪元到现在的一个绝对值 */
struct timespec
{
  time_t tv_sec; /* seconds */
  long tv_nsec;  /* nanoseconds */
};

/* Link with -lrt. */
/**
  * @brief:
  *  - 从 mqdes 引用的消息队列中删除一条优先级最高、存在时间最长的消息，并将删除的消息放置在 msg_ptr 指向的缓冲区
  *  - 如果消息队列为空，则会阻塞直到存在可用的消息或在 O_NONBLOCK 时立即失败返回 EAGAIN 错误
  * @param: 
  *  - mqdes：消息队列描述符
  *  - msg_ptr：存储接收到的消息的缓冲区的地址
  *  - msg_len：接收缓冲区的大小，需要大于或等于 mq_msgsize，否则会失败并返回 EMSGSIZE 错误
  *  - msg_prio：若不为 NULL，则保存消息的优先级
  *  - abs_timeout：阻塞情况下，可设置阻塞到一定的超时时间后仍无消息可读则立即失败返回 ETIMEDOUT 错误 
  * @return:
  *  - 成功：返回接收到的消息的实际字节数
  *  - 失败：-1，并设置 errno
  *    - EAGAIN：非阻塞情况下接收消息失败返回
  *    - ETIMEDOUT：阻塞情况下超时未接收到消息失败返回
  **/
```

### 5.5.7. mq_notify()

```cpp {class=line-numbers}
#include <mqueue.h>

int mq_notify(mqd_t mqdes, const struct sigevent *sevp);

#include <signal.h>
struct sigevent
{
  int sigev_notify;                            /* Notification method */
  int sigev_signo;                             /* Notification signal */
  union sigval sigev_value;                    /* Data passed with notification */
  void (*sigev_notify_function)(union sigval); /* Function used for thread notification (SIGEV_THREAD) */
  void *sigev_notify_attributes;               /* Attributes for notification thread (SIGEV_THREAD) */
  pid_t sigev_notify_thread_id;                /* ID of thread to signal (SIGEV_THREAD_ID) */
};

union sigval
{
  int sival_int;   /* Integer value */
  void *sival_ptr; /* Pointer value */
};

/* Link with -lrt. */
/**
  * @brief:
  *  - 注册调用进程在一条消息进入描述符 mqdes 引用的空队列时接收通知
  *  - 在任何一个时刻都只有一个进程能够向一个特定的消息队列注册接收通知。如果一个消息队列上已经存在注册进程了，那么后续在该队列上的注册请求将会失败返回 EBUSY 错误
  *  - 只有当一条新消息进入之前为空的队列时注册进程才会收到通知。如果在注册的时候队列中已经包含消息，那么只有当队列被清空之后有一条新消息达到之时才会发出通知
  *  - 当向注册进程发送了一个通知之后就会删除注册信息，之后任何进程就能够向队列注册接收通知了。换句话说，只要一个进程想要持续地接收通知，那么它就必须要在每次接收到通知之后再次调用 mq_notify() 来注册自己
  *  - 注册进程只有在当前不存在其他在该队列上调用 mq_receive()而发生阻塞的进程时才会收到通知。如果其他进程在 mq_receive() 调用中被阻塞了，那么该进程会读取消息，注册进程会保持注册状态
  *  - 一个进程可以通过在调用 mq_notify() 时传入一个值为 NULL 的 notification 参数来撤销自己在消息通知上的注册信息
  * @param: 
  *  - mqdes：消息队列描述符
  *  - sevp：
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

### 5.5.8. mq_attr

```cpp {class=line-numbers}
#include <mqueue.h>

int mq_getattr(mqd_t mqdes, struct mq_attr *attr);
int mq_setattr(mqd_t mqdes, const struct mq_attr *newattr, struct mq_attr *oldattr);

struct mq_attr
{
  long mq_flags;   /* Flags: 0 or O_NONBLOCK */
  long mq_maxmsg;  /* Max. number of messages on queue */
  long mq_msgsize; /* Max. message size (bytes) */
  long mq_curmsgs; /* Number of messages currently in queue */
};

/* Link with -lrt. */
/**
  * - mq_flags：0 或 O_NONBLOCK [mq_getattr(), mq_setattr()]
  * - mq_maxmsg：一条消息队列上可以承载的消息的数量的上限 [mq_open(), mq_getattr()]
  * - mq_msgsize：每条消息的大小的上限 [mq_open(), mq_getattr()]
  * - mq_curmsgs：消息队列上当前承载的消息的数量 [mq_getattr()]
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

### 5.5.9. POSIX消息队列限制

- **MQ_PRIO_MAX：** 
- **MQ_OPEN_MAX：** 指明一个进程最多能打开的消息队列数量。 SUSv3 要求这个限制最小为 _POSIX_MQ_OPEN_MAX（8）。 Linux 并没有定义这个限制，相反，由于 Linux 将消息队列描述符实现成了文件描述符，因此适用于文件描述符的限制将适用于消息队列描述符
- **msg_max：** 为新消息队列的 `mq_maxmsg` 特性的取值规定了一个上限。这个限制的默认值是 10，最小值是 1（在早于 2.6.28 的内核中是 10），最大值由内核常量 `HARD_MSGMAX` 定义，该常量的值是通过公式 `(131072 / sizeof(void *))` 计算得来的，在 Linux/x86-32 上其值为 32768。当一个特权进程（CAP_SYS_RESOURCE）调用 `mq_open()` 时 `msg_max` 限制会被忽略，但 `HARD_MSGMAX` 仍然担当着 `mq_maxmsg` 的上限值的角色
- **msgsize_max：** 为非特权进程创建的新消息队列的 mq_msgsize 特性的取值规定了一个上限（即使用 `mq_open()` 创建队列时 `attr.mq_msgsize` 字段的上限值）。这个限制的默认值是 8192，最小值是 128（在早于 2.6.28 的内核中是 8192），最大值是 1048576（在早于 2.6.28 的内核中是 INT_MAX）。当一个特权进程调用 `mq_open()` 时会忽略这个限制
- **queues_max：** 系统级别的限制，规定了系统上最多能够创建的消息队列的数量。一旦达到这个限制，就只有特权进程才能够创建新队列。这个限制的默认值是 256，其取值可以为范围从 0 到 INT_MAX 之间的任意一个值。

- Linux 还提供了一些/proc 文件来查看和修改（需具备特权）控制 POSIX 消息队列的使用的限制。下面这三个文件位于 /proc/sys/fs/mqueue 目录中（`man 7 mq_overview`）

### 5.5.10. 应用示例

## 5.6. 信号

### 5.6.1. 信号的概念

- 信号是 Linux 进程间通信的最古老的方式之一，是事件发生时对进程的通知机制，有时也称之为软件中断，是一种异步通信的方式。
- 信号可以导致一个正在运行的进程被另一个正在运行的异步进程中断，转而处理某一个突发事件。发往进程的诸多信号，通常都是源于内核。引发内核为进程产生信号的各类事件大致如下：
  - 对于前台进程，用户可以通过输入特殊的终端字符来给它发送信号。比如输入中断字符 `Ctrl+C`、暂停字符 `Ctrl + Z` 通常会给进程发送一个中断信号；
  - 硬件发生异常，即硬件检测到一个错误条件并通知内核，随即再由内核发送相应信号给相关进程。比如执行一条异常的机器语言指令，诸如被 0 除，或者引用了无法访问的内存区域；
  - 发生了软件事件。例如，针对文件描述符的输出变为有效，调整了终端窗口大小，定时器到期，进程执行的 CPU 时间超限，或者该进程的某个子进程退出。
  - 运行 `kill` 命令或调用 `kill()` 函数；
- 尽管可以将信号视为 IPC 的方式之一，但诸多制约因素令其常常无法胜任这一目的，其中包括信号的异步本质、不对信号进行排队处理的事实，以及较低的传递带宽。信号更为常
见的应用场景是用于进程同步，或是各种其他目的（比如，事件通知、作业控制以及定时器到期）。
</br>

- 使用信号的两个主要目的是：
  - 让进程知道已经发生了一个特定的事情；
  - 强迫进程执行它自己代码中的信号处理程序；
- 信号的特点：
  - 简单，不能携带大量信息；
  - 满足某个特定条件才发送；
  - 优先级比较高；
</br>

- 信号因某些事件而产生后，会于稍后被传递给某一进程，而进程也会采取某些措施来响应信号。在产生和到达期间，信号处于等待（pending）状态。一旦（内核）接下来要调度该进程运行，等待信号会马上送达，或者如果进程正在运行，则会立即传递信号（例如，进程向自身发送信号）。
- 有时为了确保一段代码不被传递来的信号所中断，可以将信号添加到进程的信号掩码中，从而阻塞信号的到达。如果所产生的信号属于阻塞之列，那么信号将保持等待状态，直至稍后对其解除阻塞（从信号掩码中移除）。进程可使用各种系统调用对其信号掩码添加和移除信号。
</br>

- 信号到达后，进程视具体信号执行如下五种默认行为之一：
  - Term：终止进程，有时是指进程异常终止，而不是进程因调用 `exit()` 而发生的正常终止
  - Ign：内核将信号丢弃，当前进程忽略掉这个信号
  - Core：终止进程，并生成一个Core文件。核心转储文件包含对进程虚拟内存的镜像，可将其加载到调试器中以检查进程终止时的状态
  - Stop：暂停当前进程
  - Cont：继续执行当前被暂停的进程
- 除了根据特定信号而采取默认行为之外，程序也能改变信号到达时的响应行为。也将此称之为对信号的处置（ disposition）设置。程序可以将对信号的处置设置为：
  - 采取默认行为。这适用于撤销之前对信号处置的修改、恢复其默认处置的场景。
  - 忽略信号。这适用于默认行为为终止进程的信号。
  - 执行信号处理器程序。信号处理器程序是由程序员编写的函数，用于为响应传递来的信号而执行适当任务。调用信号处理器程序以响应传递来的信号，则称之为信号已处理（handled），或者已捕获（caught）。请注意，无法将信号处置设置为终止进程或者转储核心（除非这是对信号的默认处置）。
- SIGKILL 和 SIGSTOP 信号不能被捕捉、阻塞或者忽略，只能执行默认动作
- 生成 core 文件 `ulimit -c new_size`
</br>

- Linux 特有的 /proc/PID/status 文件包含有各种位掩码字段，通过检查这些掩码可以确定进程对信号的处理。位掩码以十六进制数形式显示，最低有效位代表信号 1，相临的左边一位代表信号 2，以此类推。这些字段分别为 SigPnd（基于线程的等待信号）、 ShdPnd（进程级等待信号，始于 Linux 2.6）、 SigBlk（阻塞信号）、 SigIgn（忽略信号）和 SigCgt（捕获信号）。 

### 5.6.2. 信号的类型

信号分为两大类：第一组用于内核向进程通知事件，构成所谓传统或者标准信号，Linux 中标准信号的编号范围为 1～31。另一组信号由实时信号构成，它们没有固定的含义（可以由用户自定义使用）。

Linux 下查看系统定义的信号列表：`kill –l`，其中前 31 个信号为常规信号，其余为实时信号。查看信号的详细信息：`man 7 signal`。Linux 中的标准信号如下表（这里信号编号值对应于大多数 x86/ARM）所示：

| 编号  | 信号名称  | 对应事件                                                                                     | 默认动作                   |
| :---: | :-------- | :------------------------------------------------------------------------------------------- | :------------------------- |
|   1   | SIGHUP    | 用户退出 shell 时，由该 shell 启动的所有进程将收到这个信号                                   | 终止进程                   |
|   2   | SIGINT    | 当用户按下了 `Ctrl+C` 组合键时，用户终端向正在运行中的由该终端启动的程序发出此信号           | 终止进程                   |
|   3   | SIGQUIT   | 用户按下 `Ctrl+\` 组合键时产生该信号，用户终端向正在运行中的由该终端启动的进程发出些信号     | 终止进程                   |
|   4   | SIGILL    | CPU 检测到某进程执行了非法指令                                                               | 终止进程并产生core文件     |
|   5   | SIGTRAP   | 该信号由断点指令或其他 `trap` 指令产生                                                       | 终止进程并产生core文件     |
|   6   | SIGABRT   | 调用 `abort` 函数时产生该信号                                                                | 终止进程并产生core文件     |
|   7   | SIGBUS    | 非法访问内存地址，包括内存对齐出错                                                           | 终止进程并产生core文件     |
|   8   | SIGFPE    | 在发生致命的运算错误时发出。不仅包括浮点运算错误，还包括溢出及除数为 0 等所有的算法错误      | 终止进程并产生core文件     |
|   9   | SIGKILL   | 无条件终止进程。该信号不能被忽略，处理和阻塞                                                 | 终止进程，可以杀死任何进程 |
|  10   | SIGUSR1   | 该信号和 SIGUSR2 信号供程序员自定义使用。                                                    | 终止进程                   |
|  11   | SIGSEGV   | 指示进程进行了无效内存访问(段错误)                                                           | 终止进程并产生core文件     |
|  12   | SIGUSR2   | 另外一个用户自定义信号，程序员可以在程序中定义并使用该信号                                   | 终止进程                   |
|  13   | SIGPIPE   | Broken pipe 向一个没有读端的管道写数据                                                       | 终止进程                   |
|  14   | SIGALRM   | 定时器超时，超时的时间由系统调用 `alarm` 设置                                                | 终止进程                   |
|  15   | SIGTERM   | 程序结束信号，与 SIGKILL 不同的是，该信号可以被阻塞和终止。                                  | 终止进程                   |
|  16   | SIGSTKFLT | Linux 早期版本出现的信号，现仍保留向后兼容                                                   | 终止进程                   |
|  17   | SIGCHLD   | 子进程结束时(终止、收到 SIGSTOP 停止、处在停止态收到 SIGCONT 唤醒），父进程会收到这个信号    | 忽略这个信号               |
|  18   | SIGCONT   | 如果进程已停止，则使其继续运行                                                               | 继续/忽略                  |
|  19   | SIGSTOP   | 停止进程的执行。信号不能被忽略，处理和阻塞                                                   | 为终止进程                 |
|  20   | SIGTSTP   | 停止终端交互进程的运行。按下 `ctrl+z` 组合键时发出这个信号                                   | 暂停进程                   |
|  21   | SIGTTIN   | 后台进程读终端控制台                                                                         | 暂停进程                   |
|  22   | SIGTTOU   | 该信号类似于 SIGTTIN，在后台进程要向终端输出数据时发生                                       | 暂停进程                   |
|  23   | SIGURG    | 套接字上有紧急数据时，向当前正在运行的进程发出些信号，报告有紧急数据到达。如网络带外数据到达 | 忽略该信号                 |
|  24   | SIGXCPU   | 进程执行时间超过了分配给该进程的 CPU 时间，系统产生该信号并发送给该进程                      | 终止进程                   |
|  25   | SIGXFSZ   | 超过文件的最大长度设置                                                                       | 终止进程                   |
|  26   | SIGVTALRM | 虚拟时钟超时时产生该信号。类似于 SIGALRM，但是该信号只计算该进程占用 CPU 的使用时间          | 终止进程                   |
|  27   | SGIPROF   | 类似于 SIGVTALRM，它不仅包括该进程占用 CPU 时间还包括执行系统调用时间                        | 终止进程                   |
|  28   | SIGWINCH  | 窗口变化大小时发出 忽略该信号                                                                |
|  29   | SIGIO     | 此信号向进程指示发出了一个异步 IO 事件 忽略该信号                                            |
|  30   | SIGPWR    | 关机                                                                                         | 终止进程                   |
|  31   | SIGSYS    | 无效的系统调用                                                                               | 终止进程并产生core文件     |

### 5.6.3. 信号的发送

```cpp {class=line-numbers}
int kill(pid_t pid, int sig);
int raise(int sig);
void abort(void);
```

#### 5.6.3.1. kill()

``` cpp {class=line-numbers}
#include <sys/types.h>
#include <signal.h>

int kill(pid_t pid, int sig);
/**
  * @brief:
  *  - 向任何进程或者进程组发送任意的信号
  *  - 当进程使用 kill() 向自身发送信号时，信号将立即传递（即，在 kill() 返回调用者之前）。如果信号导致调用一个信号处理程序，则 kill() 将在处理程序返回之后再返回
  * @param: 
  *  - pit_t pid：指定的进程或者进程组 id
  *    - pid > 0：向由 pid 所指定的进程发送信号
  *    - pid = 0：向调用进程所在的进程组包括调用进程自身发送信号
  *    - pid = -1：向调用进程有权将信号发往的每个目标进程发送信号，除去 init（进程 ID 为 1）和调用进程自身
  *    - pid < -1：向指定的进程组发送信号，进程组 id 取 pid 的绝对值
  *  - int sig：发送信号的编号或者宏值，为 0 表示不发送信号
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

#### 5.6.3.2. raise()

``` cpp {class=line-numbers}
#include <signal.h>

int raise(int sig);
/**
  * @brief:
  *  - 给调用进程或线程发送指定的信号，
  *  - 当进程使用 raise() 向自身发送信号时，信号将立即传递（即，在 raise() 返回调用者之前）。如果信号导致调用一个信号处理程序，则 raise() 将在处理程序返回之后再返回
  *  - 在单线程程序中等价于 kill(getpid(), sig)
  *  - 在多线程程序中等价于 pthread_kill(pthread_self(), sig)
  * @param: 
  *  - int sig：信号的编号或者宏值
  * @return:
  *  - 成功：0
  *  - 失败：非 0
  **/
```

#### 5.6.3.3. abort()

``` cpp {class=line-numbers}
#include <stdlib.h>

void abort(void);
/**
  * @brief:
  *  - 终止其调用进程，并生成核心转储。首先解阻塞 SIGABRT 信号，然后向当前进程发送 SIGABRT 信号
  *  - 这会使得进程异常终止，除非捕获 SIGABRT 信号且信号处理程序不返回，当在信号处理器函数中使用非本地跳转时，将抵消 abort() 的效果
  *  - 如果 abort() 成功终止了进程，那么还将刷新 stdio 流并将其关闭
  * @param: 
  *  - void
  * @return:
  *  - void
  **/
```

### 5.6.4. 信号的等待

``` cpp {class=line-numbers}
#include <unistd.h>

int pause(void);
/**
  * @brief:
  *  - 
  * @param: 
  *  - void
  * @return:
  *  - 
  **/
```

### 5.6.5. 信号的捕捉

- UNIX 系统提供了两种方法来改变信号处置：`signal()` 和 `sigaction()`。
- `signal()` 系统调用，是设置信号处置的原始 API，其行为在不同 UNIX 实现间存在差异，这也意味着对可移植性有所追求的程序绝不能使用此调用来建立信号处理器函数。
- `sigaction()` 系统调用是设置信号处置的另一选择。虽然 `sigaction()` 的用法比之 `signal()` 更为复杂，但作为回报，也更具灵活性。尤其是，`sigaction()` 允许在获取信号处置的同时无需将其改变，并且，还可设置各种属性对调用信号处理器程序时的行为施以更加精准的控制。此外，在建立信号处理器程序时，`sigaction()` 较之 `signal()` 函数可移植性更佳。

``` cpp {class=line-numbers}
sighandler_t signal(int signum, sighandler_t handler);
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```

#### 5.6.5.1. signal()

```cpp {class=line-numbers}
#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
/**
  * @brief:
  *  - 捕获特定信号，并执行指定的信号处理程序
  *  - 使用 signal()，将无法在不改变信号处置的同时，还能获取到当前的信号处置。要想做到这一点，必须使用 sigaction() 
  * @param: 
  *  - int signum：指定的信号
  *  - sighandler_t handler：信号处理程序
  *    - SIG_IGN：忽略信号
  *    - SIG_DFL：执行默认的信号处理动作
  *    - 回调函数：程序员提供，内核进行调用，其中 int 类型的参数表示捕捉到的信号的值
  * @return:
  *  - 成功：返回上一次注册的信号处理函数，第一次调用返回 NULL
  *  - 失败：SIG_ERR，并设置 errno
  **/
```

#### 5.6.5.2. sigaction()

```cpp {class=line-numbers}
#include <signal.h>

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

struct sigaction
{
  void (*sa_handler)(int);                        /* 信号捕捉到之后的处理函数 */
  void (*sa_sigaction)(int, siginfo_t *, void *); /* 不常用 */
  sigset_t sa_mask;                               /* 临时阻塞信号集，在信号捕捉函数执行过程中，临时阻塞某些信号 */
  int sa_flags;                                   /* 位掩码，0 表示使用 sa_handler，SA_SIGINFO 表示使用 sa_sigaction */
  void (*sa_restorer)(void);                      /* 不适用于应用程序，仅供内部使用 */
};

/**
  * @brief:
  *  - 检查或更改进程受到信号后的处理动作，用于捕捉信号实现软中断
  *  - 引发对处理器程序调用的信号将自动添加到进程信号掩码中。这意味着，当正在执行处理器程序时，如果同一个信号实例第二次抵达，信号处理器程序将不会递归中断自己
  * @param: 
  *  - int signum：特定的信号
  *  - const struct sigaction *act：设置捕捉到信号的处理行为
  *  - struct sigaction *oldact：获取上一次设置的捕捉到信号的处理行为
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/

struct sigaction
{
  union
  {
    void (*sa_handler)(int);
    void (*sa_sigaction)(int, siginfo_t *, void *);
  } _sigaction_handler;
  sigset_t sa_mask;
  int sa_flags;
  void (*sa_restorer)(void);
};

/* Following defines make the union fields look like simple fields in the parent structure */

#define sa_handler _sigaction_handler.sa_handler
#define sa_sigaction _sigaction_handler.sa_sigaction
```

### 5.6.6. 信号集和信号掩码

- 许多信号相关的系统调用都需要能表示一组不同的信号，多个信号可使用一个称之为信号集的数据结构来表示，其系统数据类型为 `sigset_t`
- 在 PCB 中有两个非常重要的信号集。一个称之为**阻塞信号集（信号掩码）** ，另一个称之为**未决（pending）信号集**。这两个信号集都是内核使用位图机制来实现的。但操作系统不允许我们直接对这两个信号集进行位操作。而需自定义另外一个集合，借助信号集操作函数来对 PCB 中的这两个信号集进行修改。
- 信号的 “未决” 是一种状态，指的是从信号的产生到信号被处理前的这一段时间；信号的 “阻塞” 是一个开关动作，指的是阻止信号被处理，但不是阻止信号产生。
- 信号的阻塞就是让系统暂时保留信号留待以后发送。由于另外有办法让系统忽略信号，所以一般情况下信号的阻塞只是暂时的，只是为了防止信号打断敏感的操作。如果接收的信号当前遭到阻塞，那么该信号将保持等待状态，直至解除对其阻塞。
- **对于多线程的进程而言，每一个线程都具有独立的信号掩码**
</br>

- 向信号掩码中添加一个信号，有如下几种方式：
  - 当调用信号处理器程序时，可将引发调用的信号自动添加到信号掩码中。是否发生这一情况，要视 `sigaction()` 函数在安装信号处理器程序时所使用的标志而定。
  - 使用 `sigaction()` 函数建立信号处理器程序时，可以指定一组额外信号，当调用该处理器程序时会将其阻塞。
  - 使用 `sigprocmask()` 系统调用，随时可以显式向信号掩码中添加或移除信号。
- pending 信号集只是一个掩码，仅表明一个信号是否发生，而未表明其发生的次数。系统不会对标准信号进行排队处理，也就是说，将信号标记为等待状态（以及后续的传递）只会发生一次。（标准信号和实时信号之间的差异之一在于，对实时信号进行了排队处理。）
</br>

- 信号集相关函数如下所示：

```cpp {class=line-numbers}
/* 信号集相关函数 */

#include <signal.h>

int sigemptyset(sigset_t *set);
/**
  * @brief:
  *  - 清空信号集中的数据，将信号集中的所有的标志位置为 0
  * @param: 
  *  - sigset_t *set：传出参数，需要操作的信号集
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/

int sigfillset(sigset_t *set);
/**
  * @brief:
  *  - 将信号集中的所有的标志位置为1
  * @param: 
  *  - sigset_t *set：需要操作的信号集
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/

int sigaddset(sigset_t *set, int signum);
/**
  * @brief:
  *  - 设置信号集中的某一个信号对应的标志位为1，表示阻塞这个信号
  * @param: 
  *  - sigset_t *set：需要操作的信号集
  *  - int signum：需要设置阻塞的信号
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置错误号
  **/

int sigdelset(sigset_t *set, int signum);
/**
  * @brief:
  *  - 设置信号集中的某一个信号对应的标志位为 0，表示不阻塞这个信号
  * @param: 
  *  - sigset_t *set：需要操作的信号集
  *  - int signum：需要解除阻塞的信号
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/

int sigismember(const sigset_t *set, int signum);
/**
  * @brief:
  *  - 判断某个信号是否属于指定的信号集
  * @param: 
  *  - const sigset_t *set：需要操作的信号集
  *  - int signum：需要判断的信号
  * @return:
  *  - 成功：1 表示 signum 属于指定的信号集；0 表示不属于
  *  - 失败：-1，并设置 errno
  **/
```

#### 5.6.6.1. sigprocmask()

```cpp {class=line-numbers}
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
/**
  * @brief:
  *  - 将自定义信号集中的数据设置到内核中（设置阻塞，解除阻塞，替换），系统将忽略试图阻塞 SIGKILL 和 SIGSTOP 信号的请求
  *  - 如果想获取信号掩码而又对其不作改动，那么可将 set 参数指定为空，这时将忽略 how 参数
  *  - 要想暂时阻止信号的传递，可以先阻塞信号，然后再将信号掩码重置为先前的状态以解除对信号的锁定
  *  - SUSv3 规定，如果解除了对某个等待信号的锁定，那么会立刻将该信号传递给进程（在 sigprocmask() 调用返回之前）
  *  - 在多线程进程中未指定 sigprocmask() 的使用，应使用 pthread_sigmask()
  * @param: 
  *  - int how:
  *    - SIG_BLOCK：将用户设置的阻塞信号集添加到内核中，内核中原来的数据不变。假设内核中默认的阻塞信号集是 mask，mask | set
  *    - SIG_UNBLOCK：根据用户设置的数据，对内核中的数据进行解除阻塞 mask &= ~set
  *    - SIG_SETMASK：覆盖内核中原来的值
  *  - set：要进行设置的信号集
  *  - oldsset：内核中原先的信号掩码（阻塞信号集）
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

#### 5.6.6.2. sigpending()

```cpp {class=line-numbers}
int sigpending(sigset_t *set);
/**
  * @brief:
  *  - 获取内核中的未决（pending）信号集
  * @param: 
  *  - sigset_t *set：传出参数，保存的时内核中的未决信号集中的信息
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

### 5.6.7. 信号处理器

信号处理器程序（也称为信号捕捉器）是当指定信号传递给进程时将会调用的一个函数。调用信号处理器程序，可能会随时打断主程序流程，且内核代表进程来调用处理器程序，当处理器返回时，主程序会在处理器打断的位置恢复执行。这一工作序列如下所示：

- 用户通过键盘  Ctrl + C, 产生 2 号信号 SIGINT (信号被创建)
- 信号产生但是没有被处理（未决）
  - 在内核中将所有的没有被处理的信号存储在一个集合中 （未决信号集）
  - SIGINT 信号状态被存储在第二个标志位上
    - 这个标志位的值为 0，说明信号不是未决状态
    - 这个标志位的值为 1，说明信号处于未决状态
- 这个未决状态的信号，需要被处理，处理之前需要和信号掩码（阻塞信号集）进行比较
  - 阻塞信号集默认不阻塞任何的信号
  - 如果想要阻塞某些信号需要用户调用系统的API
- 在处理的时候和阻塞信号集中的标志位进行查询，看是不是对该信号设置阻塞了
  - 如果没有阻塞，这个信号就被处理
  - 如果阻塞了，这个信号就继续处于未决状态，直到阻塞解除，这个信号就被处理

![内核实现信号捕捉的过程](webserver/note/figure/内核实现信号捕捉的过程.JPG)

#### 5.6.7.1. 设计信号处理器函数

- 一般而言，将信号处理器函数设计得越简单越好，这将降低引发竞争条件的风险。下面是针对信号处理器函数的两种常见设计：
  - 信号处理器函数设置全局性标志变量并退出。主程序对此标志进行周期性检查，一旦置位随即采取相应动作。（主程序若因监控一个或多个文件描述符的 I/O 状态而无法进行这种周期性检查时，则可令信号处理器函数向一专用管道写入一个字节的数据，同时将该管道的读取端置于主程序所监控的文件描述符范围之内。）
  - 信号处理器函数执行某种类型的清理动作，接着终止进程或者使用非本地跳转将栈解开并将控制返回到主程序中的预定位置。
</br>

- 在执行某信号的处理器函数时会阻塞同类信号的传递（除非在调用 `sigaction()` 时指定了 `SA_NODEFER` 标志）。如果在执行处理器函数时（再次）产生同类信号，那么会将该信号标记为等待状态并在处理器函数返回之后再行传递。
- 不会对标准信号进行排队处理。在处理器函数执行期间，如果多次产生同类信号，那么仍然会将其标记为等待状态，但稍后只会传递一次。
- 信号的这种“失踪”方式无疑将影响对信号处理器函数的设计。首先，无法对信号的产生次数进行可靠计数。其次，在为信号处理器函数编码时可能需要考虑处理同类信号多次产生的情况。
</br>

- 在信号处理器函数中，并非所有系统调用以及库函数均可予以安全调用。要了解来龙去脉，就需要解释一下以下两种概念：可重入（reentrant）函数和异步信号安全（async-signal-safe）函数。

##### 5.6.7.1.1. 可重入函数和非可重入函数

- 可重入函数的概念是针对多线程程序而言的，多线程的概念与使用了信号处理器函数的程序也有关联。因为信号处理器函数可能会在任一时点异步中断程序的执行，从而在同一个进程中实际形成了两条（即主程序和信号处理器函数）独立（虽然不是并发）的执行线程。
- 线程安全函数和可重入函数是两个不同的改变，线程安全函数不一定是可重入函数，可重入函数一定是线程安全函数。
- 如果同一个进程的多条线程可以同时安全地调用某一函数，那么该函数就是可重入的。此处，“安全”意味着，无论其他线程调用该函数的执行状态如何，函数均可产生预期结果。
- SUSv3 对可重入函数的定义是：函数由两条或多条线程调用时，即便是交叉执行，其效果也与各线程以未定义顺序依次调用时一致。
</br>

- 更新全局变量或静态数据结构的函数可能是不可重入的。（只用到本地变量的函数肯定是可重入的。）如果对函数的两个调用（例如：分别由两条执行线程发起）同时试图更新同一全局变量或数据类型，那么二者很可能会相互干扰并产生不正确的结果。例如，假设某线程正在为一链表数据结构添加一个新的链表项，而另一线程也正试图更新同一链表。由于为链表添加新项涉及对多枚指针的更新，一旦另一线程中断这些步骤并修改了相同的指针，结果就会产生混乱。
- 在 C 语言标准函数库中，这种可能性非常普遍。例如，`malloc()` 和 `free()` 就维护有一个针对已释放内存块的链表，用于从堆中重新分配内存。如果主程序在调用 `malloc()` 期间为一个同样调用 `malloc()` 的信号处理器函数所中断，那么该链表可能会遭到破坏。因此，`malloc()` 函数族以及使用它们的其他库函数都是不可重入的。
- 还有一些函数库之所以不可重入，是因为它们使用了经静态分配的内存来返回信息。此类函数的例子包括 `crypt()`、 `getpwnam()`、 `gethostbyname()` 以及`getservbyname()`。如果信号处理器用到了这类函数，那么将会覆盖主程序中上次调用同一函数所返回的信息（反之亦然）。
- 将静态数据结构用于内部记账的函数也是不可重入的。其中最明显的例子就是 stdio 函数库成员（`printf()`、`scanf()`等），它们会为缓冲区 I/O 更新内部数据结构。所以，如果在信号处理器函数中调用了 `printf()`， 而主程序又在调用 `printf()` 或其他 stdio 函数期间遭到了处理器函数的中断，那么有时就会看到奇怪的输出，甚至导致程序崩溃或者数据的损坏。

##### 5.6.7.1.2. 异步信号安全函数

- 异步信号安全的函数是指当从信号处理器函数调用时，可以保证其实现是安全的。如果某一函数是可重入的，又或者信号处理器函数无法将其中断时，就称该函数是异步信号安全的。
- SUSv3 标准同时指出仅当信号处理器函数中断了不安全函数的执行，且处理器函数自身也调用了这个不安全函数时，该函数才是不安全的。换言之，编写信号处理器函数有如下两种选择。
  - 确保信号处理器函数代码本身是可重入的，且只调用异步信号安全的函数。
  - 当主程序执行不安全函数或是去操作信号处理器函数也可能更新的全局数据结构时，阻塞信号的传递。
- 如果使用同一处理器函数来处理多个不同信号，或者在调用 `sigaction()` 时设置了 `SA_NODEFER` 标志，那么处理器函数就有可能中断自己。因此，处理器函数如果更新了全局（或静态）变量，即便主程序不使用这些变量，那么它们依然可能是不可重入的。
- 当信号处理器函数内部需要使用 errno 时，因为可能会覆盖之前由主程序调用函数时所设置的 errno 值。有一种变通方法，即当信号处理器函数调用了可能改变 errno 的函数时，可在其入口处保存 errno 值，并在其出口处恢复 errno 的旧有值。

```cpp {class=line-numbers}
void sig_handler(int signum)
{
  int save_errno = errno;

  /* 调用可能会修改 errno 的函数 */

  errno = save_errno;
}
```

##### 5.6.7.1.3. 全局变量和 sig_atomic_t 数据类型

- 尽管存在可重入问题，有时仍需要在主程序和信号处理器函数之间共享全局变量。信号处理器函数可能会随时修改全局变量，只要主程序能够正确处理这种可能性，共享全局变量就是安全的。例如，一种常见的设计是，信号处理器函数只做一件事情，设置全局标志。主程序则会周期性地检查这一标志，并采取相应动作来响应信号传递（同时清除标志）。当信号处理器函数以此方式来访问全局变量时，应该总是在声明变量时使用 `volatile` 关键字，从而防止编译器将其优化到寄存器中。
</br>

- 对全局变量的读写可能不止一条机器指令，而信号处理器函数就可能会在这些指令序列之间将主程序中断（也将此类变量访问称为非原子操作）。因此，C 语言标准以及 SUSv3 定义了一种整型数据类型 `sig_atomic_t`，意在保证读写操作的原子性。因此，所有在主程序与信号处理器函数之间共享的全局变量都应声明为：`volatile sig_atomic_t flag`。
- 注意，C 语言的递增（`++`）和递减（`--`）操作符并不在 `sig_atomic_t` 所提供的保障范围之内。这些操作在某些硬件架构上可能不是原子操作。在使用`sig_atomic_t` 变量时唯一所能做的就是在信号处理器中进行设置，在主程序中进行检查。
- C99 和 SUSv3 规定，实现应当（在 `<stdint.h>` 中）定义两个常量 `SIG_ATOMIC_MIN` 和 `SIG_ATOMIC_MAX`，用于规定可赋给 `sig_atomic_t` 类型的值范围。标准要求，如果将 `sig_atomic_t` 表示为有符号值，其范围至少应该在 `-127～127` 之间，如果作为无符号值，则应该在 `0～255` 之间。在 Linux 中，这两个常量分别等于有符号 32 位整型数的负、正极限值。

#### 5.6.7.2. 终止信号处理器函数的其他方法

- 只是简单地从信号处理器函数中返回主程序有时并不能满足需要。（比如在处理硬件产生的信号时。）以下是从信号处理器函数中终止的其他一些方法：
  - 使用 `_exit()` 终止进程。处理器函数事先可以做一些清理工作。注意，不要使用 `exit()` 来终止信号处理器函数，因为它不是异步信号安全函数，之所以不安全，是因为如该函数会在调用 `_exit()` 之前刷新 stdio 的缓冲区。
  - 使用 `kill()` 发送信号来杀掉进程（即，信号的默认动作是终止进程）。
  - 使用 `abort()` 函数终止进程，并产生核心转储。
  - 从信号处理器函数中执行非本地跳转，以便从一个函数跳转至该函数的某个调用者。这也是因硬件异常（例如内存访问错误）而导致信号传递之后的一条恢复途径，允许将信号捕获并把控制返回到程序中某个特定位置。例如，一旦收到 SIGINT 信号（通常由键入 Ctrl-C 产生），shell 执行一个非本地跳转，将控制返回到主输入循环中（以便读取下一条命令）。

```cpp {class=line-numbers}
#include <setjmp.h>

int setjmp(jmp_buf env);
int sigsetjmp(sigjmp_buf env, int savesigs);

void longjmp(jmp_buf env, int val);
void siglongjmp(sigjmp_buf env, int val);
```

#### 5.6.7.3. 在备选栈中处理信号：sigaltstack()

- 在调用信号处理器函数时，内核通常会在进程栈中为其创建一帧。不过，如果进程对栈的扩展突破了对栈大小的限制时，这种做法就不大可行了。例如，栈的增长过大，以至于会触及到一片映射内存或者向上增长的堆，又或者栈的大小已经直逼 RLIMIT_STACK 资源限制，这些都会造成这种情况的发生。
- 当进程对栈的扩展试图突破其上限时，内核将为该进程产生 SIGSEGV 信号。不过，因为栈空间已然耗尽，内核也就无法为进程已经安装的 SIGSEGV 处理器函数创建栈帧。结果是，处理器函数得不到调用，而进程也就终止了（SIGSEGV 的默认动作）。
- 如果希望在这种情况下确保对 SIGSEGV 信号处理器函数的调用，就需要做如下工作：
  - 分配一块被称为“备选信号栈”的内存区域，作为信号处理器函数的栈帧。
  - 调用 `sigaltstack()`，告之内核该备选信号栈的存在。
  - 在创建信号处理器函数时指定 SA_ONSTACK 标志，亦即通知内核在备选栈上为处理器函数创建栈帧

```cpp {class=line-numbers}
#include <signal.h>

int sigaltstack(const stack_t *ss, stack_t *old_ss);
```

#### 5.6.7.4. SA_SIGINFO 标志

如果在使用 `sigaction()` 创建处理器函数时设置了 SA_SIGINFO 标志，那么在收到信号时处理器函数可以获取该信号的一些附加信息。为获取这一信息，需要将处理器函数声明如下：

```cpp {class=line-numbers}
void sig_handler(int sig, siginfo_t *siginfo, void *ucontext);

int sig /* 信号的具体编号 */

typedef struct
{
  int si_signo;         /* Signal number */
  int si_errno;         /* An errno value */
  int si_code;          /* Signal code */
  int si_trapno;        /* Trap number that caused hardware-generated signal (unused on most architectures) */
  pid_t si_pid;         /* Sending process ID */
  uid_t si_uid;         /* Real user ID of sending process */
  int si_status;        /* Exit value or signal */
  clock_t si_utime;     /* User time consumed */
  clock_t si_stime;     /* System time consumed */
  sigval_t si_value;    /* Signal value */
  int si_int;           /* POSIX.1b signal */
  void *si_ptr;         /* POSIX.1b signal */
  int si_overrun;       /* Timer overrun count; POSIX.1b timers */
  int si_timerid;       /* Timer ID; POSIX.1b timers */
  void *si_addr;        /* Memory location which caused fault */
  long si_band;         /* Band event (was int in glibc 2.3.2 and earlier) */
  int si_fd;            /* File descriptor */
  short si_addr_lsb;    /* Least significant bit of address (since Linux 2.6.32) */
  void *si_lower;       /* Lower bound when address violation occurred (since Linux 3.19) */
  void *si_upper;       /* Upper bound when address violation occurred (since Linux 3.19) */
  int si_pkey;          /* Protection key on PTE that caused fault (since Linux 4.6) */
  void *si_call_addr;   /* Address of system call instruction (since Linux 3.5) */
  int si_syscall;       /* Number of attempted system call (since Linux 3.5) */
  unsigned int si_arch; /* Architecture of attempted system call (since Linux 3.5) */
} siginfo_t;

void *ucontext; /* 该结构提供了所谓的用户上下文信息，用于描述调用信号处理器函数前的进程状态，
                   其中包括上一个进程信号掩码以及寄存器的保存值，例如程序计数器（ cp）和栈指针寄存器（ sp）。
                   信号处理器函数很少用到此类信息 */
```

#### 5.6.7.5. 系统调用的中断和重启

当阻塞的系统调用受到信号的中断时，可能会引发对信号处理器函数的调用。当信号处理器函数返回时，默认情况下系统调用失败，并将 errno 设置为 EINTR。不过，更为常见的情况是希望遭到中断的系统调用得以继续运行。为此，可在系统调用遭信号处理器中断的事件中，利用如下代码来手动重启系统调用

```cpp {class=line-numbers}
while ((cnt = read(fd, buf, BUF_SIZE)) == -1 && errno = EINTR)
  continue;

if (cnt == -1)
  perror("read");
```

此外，可以调用指定了 `SA_RESTART` 标志的 `sigaction()` 来创建信号处理器函数，从而令内核代表进程自动重启系统调用，还无需处理系统调用可能返回的 EINTR 错误。标志 SA_RESTART 是针对每个信号的设置。换言之，允许某些信号的处理器函数中断阻塞的系统调用，而其他系统调用则可以自动重启。不幸的是，并非所有的系统调用都可以通过指定 SA_RESTART 来达到自动重启的目的。在 Linux 中，如果采用 SA_RESTART 标志来创建系统处理器函数，则如下阻塞的系统调用（以及构建于其上的库函数）在遭到中断时是可以自动重启的。
- 用来等待子进程的系统调用：`wait()、 waitpid()、 wait3()、 wait4()、 waitid()`。
- 访问慢速设备时的 I/O 系统调用： `read()、 readv()、 write()、 writev()、 ioctl()`。如果在收到信号时已经传递了部分数据，那么还是会中断输入输出系统调用，但会返回成功状态：一个整型值，表示已成功传递数据的字节数。
- 系统调用 `open()`，在可能阻塞的情况下（例如在打开 FIFO 时）。
- 用于套接字的各种系统调用：`accept()、 accept4()、 connect()、 send()、 sendmsg()、 sendto()、recv()、 recvfrom()、 recvmsg()`。（在 Linux 中，如果使用 `setsockopt()` 来设置超时，这些系统调用就不会自动重启。更多细节请参考 `signal(7)` 手册页。）
- 对 POSIX 消息队列进行 I/O 操作的系统调用：`mq_receive()、 mq_timedreceive()、 mq_send()、 mq_timedsend()`。
- 用于设置文件锁的系统调用和库函数：`flock()、 fcntl()、 lockf()`。
- Linux 特有系统调用 `futex()` 的 FUTEX_WAIT 操作。
- 用于递减 POSIX 信号量的 `sem_wait()` 和 `sem_timedwait()` 函数。（在一些 UNIX 实现上，如果设置了 SA_RESTART 标志，`sem_wait()` 就会重启。）
- 用于同步 POSIX 线程的函数：`pthread_mutex_lock()、 pthread_mutex_trylock()、 pthread_mutex_timedlock()、 pthread_cond_wait()、 pthread_cond_timedwait()`。

以下阻塞的系统调用（以及构建于其上的库函数）则绝不会自动重启（即便指定了 SA_RESTART）。
- I/O 多路复用调用 `poll()、 ppoll()、 select()、 pselect()`。（SUSv3 明文规定，无论设置 SA_RESTART 标志与否，都不对 `select()` 和 `pselect()` 遭处理器函数中断时的行为进行定义。）
- Linux 特有的 `epoll_wait()` 和 `epoll_pwait()` 系统调用。
- Linux 特有的 `io_getevents()` 系统调用。
- 操作 System V 消息队列和信号量的阻塞系统调用：`semop()、 semtimedop()、 msgrcv()、 msgsnd()`。（虽然 System V 原本并未提供自动重启系统调用的功能，但在某些 UNIX实现上，如果设置了 SA_RESTART 标志，这些系统调用还是会自动重启。）
- 对 inotify 文件描述符发起的 `read()` 调用。
- 用于将进程挂起指定时间的系统调用和库函数：`sleep()、 nanosleep()、 clock_nanosleep()`。
- 特意设计用来等待某一信号到达的系统调用：`pause()、 sigsuspend()、 sigtimedwait()、 sigwaitinfo()`。

### 5.6.8. 信号的高级特性

#### 5.6.8.1. 核心转储文件

具体可参考《Linux-Unix 系统编程手册》上册第 22 章 22.1

#### 5.6.8.2. 传递、处置及处理特殊情况

具体可参考《Linux-Unix 系统编程手册》上册第 22 章 22.2

#### 5.6.8.3. 可中断和不可中断的进程睡眠状态

具体可参考《Linux-Unix 系统编程手册》上册第 22 章 22.3

#### 5.6.8.4. 硬件产生的信号

- 硬件异常可以产生 SIGBUS、 SIGFPE、 SIGILL，和 SIGSEGV 信号，调用 kill()函数来发送此类信号是另一种途径，但较为少见。 SUSv3 规定，在硬件异常的情况下，如果进程从此类信号的处理器函数中返回，亦或进程忽略或阻塞了此类信号，那么进程的行为未定义。
- 正确处理硬件产生信号的方法有二：要么接受信号的默认行为（进程终止）；要么为其编写不会正常返回的处理器函数。除了正常返回之外，终结处理器执行的手段还包括调用`_exit()` 以终止进程，或者调用 `siglongjmp()`，确保将控制传递回程序中（产生信号的指令位置之外）的某一位置。

#### 5.6.8.5. 信号的同步生成和异步生成

- 信号的异步生成：引发信号产生（无论信号发送者是内核还是另一进程）的事件，其发生与进程的执行无关。（例如，用户输入中断字符，或者子进程终止。）对于异步产生的信号，进程一般无法预测其接收信号的时间。
- 信号的同步生成：信号的产生是由进程本身的执行造成的，此时会立即传递信号。对于同步生成的信号，其传递不但可以预测，而且可以重现。例如：
  - 执行特定的机器语言指令，可导致硬件异常，并因此而产生相关信号（SIGBUS、 SIGFPE、 SIGILL、 SIGSEGV 和 SIGEMT）。
  - 进程可以使用 `raise()`、 `kill()` 或者 `killpg()` 向自身发送信号。

#### 5.6.8.6. 信号传递的时机和顺序

- **信号传递的时机：**
- 同步产生的信号会立即传递。例如，硬件异常会触发一个即时信号，而当进程使用 `raise()` 向自身发送信号时，信号会在 `raise()` 调用返回前就已经发出。
- 异步产生一个信号时，即使并未将其阻塞，在信号产生和实际传递之间仍可能会存在一个（瞬时）延迟。在此期间，信号处于等待状态。这是因为内核将等待信号传递给进程的时机是，该进程正在执行，且发生由内核态到用户态的下一次切换时。实际上，这意味着在以下时刻才会传递信号：
  - 进程在前度超时后，再度获得调度时（即，在一个时间片的开始处）。
  - 系统调用完成时（信号的传递可能引起正在阻塞的系统调用过早完成）。
</br>

- **信号传递的顺序：**
- 如果进程使用 `sigprocmask()` 解除了对多个等待信号的阻塞，那么所有这些信号会立即传递给该进程。
- 就目前的 Linux 实现而言，Linux 内核按照信号编号的升序来传递信号。例如，如果对处于等待状态的信号 SIGINT（信号编号为 2）和 SIGQUIT（信号编号为 3）同时解除阻塞，那么无论这两个信号的产生次序如何，SIGINT 都将先于 SIGQUIT 而传递。然而，也不能对传递（标准）信号的特定顺序产生任何依赖，因为 SUSv3 规定，多个信号的传递顺序由系统实现决定。（该条款仅适用于标准信号，而实时信号的相关标准规定，对于解除阻塞的实时信号而言，其传递顺序必须得到保障。）
- 当多个解除了阻塞的信号正在等待传递时，如果在信号处理器函数执行期间发生了内核态和用户态之间的切换，那么将中断此处理器函数的执行，转而去调用第二个信号处理器函数（如此递进）。

#### 5.6.8.7. 实时信号

- 定义于 POSIX.1b 中的实时信号，意在弥补对标准信号的诸多限制。较之于标准信号，其优势如下所示
  - 实时信号的信号范围有所扩大，可应用于应用程序自定义的目的。而标准信号中可供应用随意使用的信号仅有两个： SIGUSR1 和 SIGUSR2。
  - 对实时信号所采取的是队列化管理。如果将某一实时信号的多个实例发送给一进程，那么将会多次传递信号。相反，如果某一标准信号已经在等待某一进程，而此时即使再次向该进程发送此信号的实例，信号也只会传递一次。
  - 当发送一个实时信号时，可为信号指定伴随数据（一整型数或者指针值），供接收进程的信号处理器获取。
  - 不同实时信号的传递顺序得到保障。如果有多个不同的实时信号处于等待状态，那么将率先传递具有最小编号的信号。换言之，信号的编号越小，其优先级越高。如果是同一类型的多个信号在排队，那么信号（以及伴随数据）的传递顺序与信号发送来时的顺序保持一致。
</br>

- SUSv3 要求，实现所提供的各种实时信号不得少于 `_POSIX_RTSIG_MAX`（定义为 8）个。Linux 内核则定义了 32 个不同的实时信号，编号范围为 32～63。`<signal.h>` 头文件所定义的 `RTSIG_MAX` 常量则表征实时信号的可用数量，而此外所定义的常量 `SIGRTMIN` 和 `SIGRTMAX` 则分别表示可用实时信号编号的最小值和最大值。程序员不应将实时信号编号的整型值在应用程序代码中写死，因为实时信号的范围因 UNIX 实现的不同而各异。与之相反，指代实时信号编号则可以采用 `SIGRTMIN + x` 的形式。例如，表达式（`SIGRTMIN + 1`）就表示第二个实时信号。注意， SUSv3 并未要求 `SIGRTMAX` 和 `SIGRTMIN` 是简单的整数值。可以将其定义为函数（就像 Linux 中那样）。
</br>

- 对排队实时信号数量的限制：排队的实时信号（及其相关数据）需要内核维护相应的数据结构，用于罗列每个进程的排队信号。由于这些数据结构会消耗内核内存，故而内核对排队实时信号的数量设置了限制。
- SUSv3 允许实现为每个进程中可排队的（各类）实时信号数量设置上限，并要求其不得少于 `_POSIX_SIGQUEUE_MAX`（定义为 32）。实现可借助于对 `SIGQUEUE_MAX` 常量的定义
来表示其所允许的排队实时信号数量。发起如下调用也能获得这一信息：`lim = sysconf(_SC_SIGQUEUE_MAX)`。

##### 5.6.8.7.1. 发送实时信号：sigqueue()

- 发送进程使用 `sigqueue()` 系统调用来发送信号及其伴随数据。使用 `kill()`、`killpg()` 和 `raise()` 调用也能发送实时信号。然而，至于系统是否会对利用此类接口所发送的信号进行排队处理， SUSv3 规定，由具体实现决定。这些接口在 Linux 中会对实时信号进行排队，但在其他许多 UNIX 实现中，情况则不然。

```cpp {class=line-numbers}
#include <signal.h>

int sigqueue(pid_t pid, int sig, const union sigval value);

union sigval
{
  int sival_int;
  void *sival_ptr;
};

/**
  * @brief:
  *  - 向指定进程 pid 发送实时信号 sig，发送信号的权限同 kill()
  * @param: 
  *  - pid：指定的进程，不能设为负值而向整个进程组发送信号
  *  - sig：要发送的实时信号，为 0 表示不发送任何信号可用于检查指定的进程是否存在
  *  - value：发送信号指定的伴随数据，很少使用 sival_ptr，因为指针的作用范围在进程内部，对于另一进程几乎没有意义
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

##### 5.6.8.7.2. 处理实时信号

- 要为实时信号建立了一个处理器函数，接收进程应以 `SA_SIGINFO` 标志发起对 `sigaction()` 的调用。因此，调用信号处理器时就会附带额外参数，其中之一是实时信号的伴随数据。
- 在 Linux 中，即使接收进程在建立信号处理器时并未指定 `SA_SIGINFO` 标志，也能对实时信号进行队列化管理（但在这种情况下，将不可能获得信号的伴随数据）。然而， SUSv3
也不要求实现确保这一行为，所以依赖这一点将有损于应用的可移植性

#### 5.6.8.8. 使用掩码来等待信号：sigsuspended()

将解除信号阻塞和挂起进程这两个动作封装成一个原子操作，防止在这两个过程之间有指定的信号到达。这正是 `sigsuspend()` 系统调用

```cpp {class=line-numbers}
#include <signal.h>

int sigsuspend(const sigset_t *mask);
/**
  * @brief:
  *  - 将以 mask 所指向的信号集来替换进程的信号掩码，然后挂起进程的执行，直到其捕获到信号，并从信号处理器中返回
  *  - 一旦处理器返回，sigsuspend() 会将进程信号掩码恢复为调用前的值。
  * @param: 
  *  - mask：指定的要替换进程信号掩码的信号集
  * @return:
  *  - 返回 -1，并设置 errno
  *    - EFAULT：mask 指向的地址无效
  *    - EINTR：sigsuspend() 因信号的传递而中断
  **/
```

#### 5.6.8.9. 同步方式等待信号

```cpp {class=line-numbers}
#include <signal.h>

int sigwaitinfo(const sigset_t *set, siginfo_t *info);

int sigtimedwait(const sigset_t *set, siginfo_t *info, const struct timespec *timeout);

/**
  * @brief:
  *  - 挂起进程的执行，直至 set 指向信号集中的某一信号抵达，省去了对信号处理器的设计和编码工作
  *  - 如果调用 sigwaitinfo() 时，set 中的某一信号已经处于等待状态，那么 sigwaitinfo() 将立即返回。传递来的的信号就此从进程的等待信号队列中移除
  *  - 将对 set 中信号集的阻塞与调用 sigwaitinfo() 结合起来，这当属明智之举。即便某一信号遭到阻塞，仍然可以使用 sigwaitinfo() 来获取等待信号
  *  - SUSv3 规定，调用 sigwaitinfo() 而不阻塞 set 中的信号将导致不可预知的行为（其行为未定义）
  *  - 接受信号的传递顺序和排队特性与信号处理器所捕获的信号相同，即不对标准信号进行排队处理，对实时信号进行排队处理，并且对实时信号的传递遵循低编号优先的原则
  * @param: 
  *  - set：需要等待的信号集
  *  - info：接收等待信号的伴随数据
  * @return:
  *  - 成功：返回接收的信号的编号
  *  - 失败：返回 -1，并设置 errno
  *    - EFAULT：mask 指向的地址无效
  *    - EINTR：sigsuspend() 因信号的传递而中断
  **/
```

#### 5.6.8.10. 通过文件描述符来获取信号

始于内核 2.6.22， Linux 提供了（非标准的）`signalfd()` 系统调用；利用该调用可以创建一个特殊文件描述符，发往调用者的信号都可从该描述符中读取。`signalfd` 机制为同步接受信号提供了 `sigwaitinfo()` 之外的另一种选择。

```cpp {class=line-numbers}
#include <sys/signalfd.h>

int signalfd(int fd, const sigset_t *mask, int flags);

struct signalfd_siginfo
{
  uint32_t ssi_signo;    /* Signal number */
  int32_t ssi_errno;     /* Error number (unused) */
  int32_t ssi_code;      /* Signal code */
  uint32_t ssi_pid;      /* PID of sender */
  uint32_t ssi_uid;      /* Real UID of sender */
  int32_t ssi_fd;        /* File descriptor (SIGIO) */
  uint32_t ssi_tid;      /* Kernel timer ID (POSIX timers) */
  uint32_t ssi_band;     /* Band event (SIGIO) */
  uint32_t ssi_overrun;  /* POSIX timer overrun count */
  uint32_t ssi_trapno;   /* Trap number that caused signal */
  int32_t ssi_status;    /* Exit status or signal (SIGCHLD) */
  int32_t ssi_int;       /* Integer sent by sigqueue(3) */
  uint64_t ssi_ptr;      /* Pointer sent by sigqueue(3) */
  uint64_t ssi_utime;    /* User CPU time consumed (SIGCHLD) */
  uint64_t ssi_stime;    /* System CPU time consumed (SIGCHLD) */
  uint64_t ssi_addr;     /* Address that generated signal (for hardware-generated signals) */
  uint16_t ssi_addr_lsb; /* Least significant bit of address (SIGBUS; since Linux 2.6.37) */
  uint8_t pad[X];        /* Pad size to 128 bytes (allow for additional fields in the future) */
};

/**
  * @brief:
  *  - 创建一个文件描述符，可用于接收针对调用者的信号
  *  - 创建文件描述符之后，可以使用 read() 调用从中读取信号。提供给 read()的缓冲区必须足够大，至少应能够容纳一个 signalfd_siginfo 结构
  *  - 如同 sigwaitinfo() 一样，通常也应该使用 sigprocmask() 阻塞 mask 中的所有信号，以确保在有机会读取这些信号之前，不会按照默认处置对它们进行处理
  * @param: 
  *  - fd：
  *    - −1，创建一个新的文件描述符，用于读取 mask 中的信号；
  *    - 否则，将修改与 fd 相关的 mask 值，且该 fd 一定是由之前对 signalfd() 的一次调用创建而成
  *  - mask：信号集，指定了有意通过 signalfd 文件描述符来读取的信号
  *  - flags：
  *    - SFD_CLOEXEC：
  *    - SFD_NONBLOCK：
  * @return:
  *  - 成功：signalfd 文件描述符
  *  - 失败：返回 -1，并设置 errno
  **/
```

### 5.6.9. 信号和线程

### 5.6.10. 应用示例

#### 5.6.10.1. 信号捕捉实现周期性定时器

```cpp {class=line-numbers}
/**
 * @description:
 *  - 使用 setitimer() 和信号捕捉实现周期性定时任务
 **/
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void myalarm(int num)
{
  printf("捕捉到了信号的编号是：%d\n", num);
  printf("xxxxxxx\n");
}

int main()
{
  struct sigaction act;
  act.sa_flags = 0;
  act.sa_handler = myalarm;
  sigemptyset(&act.sa_mask);
  sigaction(SIGALRM, &act, NULL);

  struct itimerval new_value;
  new_value.it_interval.tv_sec = 2;
  new_value.it_interval.tv_usec = 0;
  new_value.it_value.tv_sec = 3;
  new_value.it_value.tv_usec = 0;

  int ret = setitimer(ITIMER_REAL, &new_value, NULL);
  printf("定时器开始了...\n");

  if (ret == -1)
  {
    perror("setitimer");
    exit(0);
  }

  while (1) ;

  return 0;
}
```

#### 5.6.10.2. 使用SIGCHLD信号解决僵尸进程的问题

```cpp {class=line-numbers}
/**
 * @description:
 *  - 使用SIGCHLD信号解决僵尸进程的问题
 **/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>

void myFun(int num)
{
  printf("捕捉到的信号 ：%d\n", num);
  while (1)
  {
    int ret = waitpid(-1, NULL, WNOHANG);
    if (ret > 0)
      printf("child die , pid = %d\n", ret);
    else if (ret == 0)
      break; // 说明还有子进程或者
    else if (ret == -1)
      break; // 没有子进程
  }
}

int main()
{
  // 提前设置好阻塞信号集，阻塞 SIGCHLD，因为有可能子进程很快结束，父进程还没有注册完信号捕捉
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGCHLD);
  sigprocmask(SIG_BLOCK, &set, NULL);

  // 创建一些子进程
  pid_t pid;
  for (int i = 0; i < 20; i++)
  {
    pid = fork();
    if (pid == 0)
      break;
  }

  if (pid > 0)
  {
    // 捕捉子进程死亡时发送的 SIGCHLD 信号
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = myFun;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD, &act, NULL);

    // 注册完信号捕捉以后，解除阻塞
    sigprocmask(SIG_UNBLOCK, &set, NULL);

    while (1)
    {
      printf("parent process pid : %d\n", getpid());
      sleep(2);
    }
  }
  else if (pid == 0)
  {
    printf("child process pid : %d\n", getpid());
  }

  return 0;
}
```

#### 5.6.10.3. 信号集操作函数范例

```cpp {class=line-numbers}
/**
 * @description:
 *  - 对常用信号集操作函数的简单练习
 **/
#include <signal.h>
#include <stdio.h>

int main()
{
  // 创建一个信号集
  sigset_t set;

  // 清空信号集的内容
  sigemptyset(&set);

  // 判断 SIGINT 是否在信号集 set 里
  int ret = sigismember(&set, SIGINT);
  if (ret == 0) printf("SIGINT 不阻塞\n");
  else if (ret == 1) printf("SIGINT 阻塞\n");

  // 添加几个信号到信号集中
  sigaddset(&set, SIGINT);
  sigaddset(&set, SIGQUIT);

  // 判断SIGINT是否在信号集中
  ret = sigismember(&set, SIGINT);
  if (ret == 0) printf("SIGINT 不阻塞\n");
  else if (ret == 1) printf("SIGINT 阻塞\n");

  // 判断SIGQUIT是否在信号集中
  ret = sigismember(&set, SIGQUIT);
  if (ret == 0) printf("SIGQUIT 不阻塞\n");
  else if (ret == 1) printf("SIGQUIT 阻塞\n");

  // 从信号集中删除一个信号
  sigdelset(&set, SIGQUIT);

  // 判断SIGQUIT是否在信号集中
  ret = sigismember(&set, SIGQUIT);
  if (ret == 0) printf("SIGQUIT 不阻塞\n");
  else if (ret == 1) printf("SIGQUIT 阻塞\n");

  return 0;
}

/**
 * @description:
 *  - 编写一个程序，把所有的常规信号（1-31）的未决状态打印到屏幕
 *  - 设置某些信号是阻塞的，通过键盘产生这些信号
 **/
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  // 设置2、3号信号阻塞
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGINT);
  sigaddset(&set, SIGQUIT);

  // 修改内核中的阻塞信号集
  sigprocmask(SIG_BLOCK, &set, NULL);

  int num = 0;
  while (1)
  {
    num++;
    printf("num=%d:", num);

    // 获取当前的未决信号集的数据
    sigset_t pendingset;
    sigemptyset(&pendingset);
    sigpending(&pendingset);

    // 遍历前32位
    for (int i = 1; i <= 31; i++)
    {
      if (sigismember(&pendingset, i) == 1)
        printf("1");
      else if (sigismember(&pendingset, i) == 0)
        printf("0");
      else
      {
        perror("sigismember");
        exit(0);
      }
    }

    printf("\n");
    sleep(1);
    if (num == 10)
      sigprocmask(SIG_UNBLOCK, &set, NULL); // 解除阻塞
  }

  return 0;
}
```


# 6. 时间

## 6.1. 日历时间和时间转换函数

- 真实时间：对应于时间定义的每一天
- 日历时间：当真实时间通过一些标准点计算的时候，我们称它为日历时间
- 和经过的时间相对，它是度量一个进程生命周期中的一些点（通常是开始）
- 进程时间是由一个进程使用的 CPU 时间量，并划分为用户时间和系统时间

```cpp {class=linenumbers}
#include <time.h>

char *asctime(const struct tm *tm);
char *asctime_r(const struct tm *tm, char *buf);

char *ctime(const time_t *timep);
char *ctime_r(const time_t *timep, char *buf);

struct tm *gmtime(const time_t *timep);
struct tm *gmtime_r(const time_t *timep, struct tm *result);

struct tm *localtime(const time_t *timep);
struct tm *localtime_r(const time_t *timep, struct tm *result);

time_t mktime(struct tm *tm);

struct tm
{
  int tm_sec;   /* Seconds (0-60) */
  int tm_min;   /* Minutes (0-59) */
  int tm_hour;  /* Hours (0-23) */
  int tm_mday;  /* Day of the month (1-31) */
  int tm_mon;   /* Month (0-11) */
  int tm_year;  /* Year - 1900 */
  int tm_wday;  /* Day of the week (0-6, Sunday = 0) */
  int tm_yday;  /* Day in the year (0-365, 1 Jan = 0) */
  int tm_isdst; /* Daylight saving time */
};

/**
  * @brief:
  * @param: 
  * @return:
  **/
```

## 6.2. 软件时钟（jiffies）

- 系统软件时钟（software clock）的分辨率的度量单位被称为 jiffies。
- jiffies 的大小是定义在内核源代码的常量 HZ。这是内核按照 round-robin 的分时调度算法分配 CPU 进程的单位。
- 软件时钟频率是一个可配置的内核的选项（包括处理器类型和特性，定时器的频率）。
- 自 2.6.13 内核，时钟频率可以设置到 100、250（默认）或 1000 赫兹，对应的 jiffy 值分别为 10、 4、 1 毫秒。
- 自内核 2.6.20，增加了一个频率： 300 赫兹，它可以被两种常见的视频帧速率 25 帧每秒（PAL）和 30 帧每秒（ NTSC）整除。

## 6.3. 进程时间

- 进程时间是进程创建后使用的 CPU 时间数量，内核把 CPU 时间分成以下两个部分：
  - 用户 CPU 时间：进程在用户态下执行所花费的时间数量，也称为虚拟时间（virtual time）。对于程序来说，就是它已经得到 CPU 的时间。
  - 系统 CPU 时间：进程在内核态下执行所花费的时间数量，这是内核用于执行系统调用或代表程序执行的其他任务（例如，服务页错误）的时间。
- 当运行一个 shell 程序， 我们可以使用的 `time process_name` 命令， 同时获得这两个部分的时间值，以及运行程序所需的实际时间

### 6.3.1. times()

```cpp {class=linenumbers}
#include <sys/times.h>

clock_t times(struct tms *buf);

struct tms
{
  clock_t tms_utime;  /* user time */
  clock_t tms_stime;  /* system time */
  clock_t tms_cutime; /* user time of children */
  clock_t tms_cstime; /* system time of children */
};

/**
  * @brief:
  *  - 检索进程时间信息，并把结果通过 buf 指向的结构体返回
  *  - tms_utime, tms_stime 返回调用进程到目前为止使用的用户和系统组件的 CPU 时间
  *  - tms_cutime, tms_cstime 返回父进程（比如，times()的调用者）执行了系统调用 wait() 的所有已经终止的子进程使用的 CPU 时间
  *  - 可以使用 sysconf(_SC_CLK_TCK) 获得每秒包含的 clock ticks 数目
  * @param: 
  *  - buf：存储检索的进程时间信息结果
  * @return:
  *  - 成功：
  *    - 返回自过去某个时间点（取决于具体实现）到当前时刻所经过的 clock ticks 数目
  *    - 返回值可能会产生溢出，所以采用一对 times() 调用做差可能会得到错误的结果
  *  - 失败：(clock_t) -1，并设置 errno
  **/
```

### 6.3.2. clock()

```cpp {class=linenumbers}
#include <time.h>

clock_t clock(void);
/**
  * @brief:
  *  - 返回调用进程到当前调用时刻所经过的 CPU 时间
  * @param: 
  * @return:
  *  - 成功：返回调用进程到当前时刻所经过的 clock ticks 数目，可以除以 CLOCKS_PERSEC 获得秒数
  *  - 失败：(clock_t) -1
  **/
```

# 7. 定时器和休眠

## 7.1. 间隔定时器

定时器的用途之一是为系统调用的阻塞设定时间上限

### 7.1.1. setitimer()

```cpp {class=linenumbers}
#include <sys/time.h>
int setitimer(int which, const struct itimerval *new_val, struct itimerval *old_value);

struct itimerval
{
  struct timeval it_interval; /* 定时周期，若为 0，则为非周期定时器 */
  struct timeval it_value;    /* 定时器超时时间，首次超时后被重置为 it_interval；若为 0，则关闭定时器 */
};
struct timeval
{
  time_t tv_sec;       /* 秒数 */
  suseconds_t tv_usec; /* 微秒 */
};

/**
  * @brief:
  *  - 在延迟指定时间后向调用进程发送指定信号，之后按照指定间隔周期性地发送指定信号
  *  - 对信号的默认处置会终止进程，若想作为定时器使用，则需要对信号创建信号处理函数
  *  - 使用 setitimer()和 alarm() 创建的定时器可以跨越 exec() 调用而得以保存，但由 fork() 创建的子进程并不继承该定时器
  * @param: 
  *  - which：设置定时器以何种时间标准进行定时
  *    - ITIMER_REAL：真实时间，到期发送 SIGALRM
  *    - ITIMER_VIRTUAL：进程的用户态所消耗的 CPU 时间，到期发送 SIGVTALRM
  *    - ITIMER_PROF：进程的用户态和内核态消耗的总的 CPU 时间（包括该进程下的所有线程），到期发送 SIGPROF
  *    - 一个进程针对 ITIMER_REAL、ITIMER_VIRTUAL 和 ITIMER_PROF 这 3 类定时器，每种只能设置一个。当第 2 次调用 setitimer()时，修改已有定时器的属性要符合参数 which 中的类型
  *    - 如果调用 setitimer() 时将 new_value.it_value 的两个字段均置为 0，那么会屏蔽任何已有的定时器
  *  - new_val：设置定时器的属性
  *  - old_value：获取先前定时器的属性
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置错误号
  **/

int getitimer(int which, struct itimerval *curr_value);
/**
  * @brief:
  *  - 获取定时器的当前状态
  * @param: 
  *  - which
  *  - curr_value：
  *    - 子结构 curr_value.it_value 返回距离下一次到期所剩余的总时间，该值会随定时器倒计时而变化。如果设置定时器时将 it_interval 置为非 0 值，那么会在定时器到期时将其重置
  *    - 子结构 curr_value.it_interval 返回定时器的间隔时间，除非再次调用 setitimer()，否则该值一直保持不变
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/

/* 简单示例 */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

void sig_handle(int signum)
{
  printf("catch signal num: %d\n", signum);

  return;
}

int main()
{
  printf("main start\n");

  /* 设置定时器 */
  struct itimerval itv;
  itv.it_interval.tv_sec = 0;
  itv.it_interval.tv_usec = 0;
  itv.it_value.tv_sec = 0;
  itv.it_value.tv_usec = 1000;
  setitimer(ITIMER_REAL, &itv, NULL);
  setitimer(ITIMER_VIRTUAL, &itv, NULL);
  setitimer(ITIMER_PROF, &itv, NULL);

  /* 信号捕捉 */
  struct sigaction sigact;
  sigemptyset(&sigact.sa_mask);
  sigact.sa_flags = 0;
  sigact.sa_handler = sig_handle;
  sigaction(SIGALRM, &sigact, NULL);

  sigemptyset(&sigact.sa_mask);
  sigact.sa_flags = 0;
  sigact.sa_handler = sig_handle;
  sigaction(SIGVTALRM, &sigact, NULL);

  sigemptyset(&sigact.sa_mask);
  sigact.sa_flags = 0;
  sigact.sa_handler = sig_handle;
  sigaction(SIGPROF, &sigact, NULL);

  while (1)
  {
    /* 获取定时器的当前剩余时间 */
    // struct itimerval cur_itv;
    // getitimer(ITIMER_REAL, &cur_itv);
    // printf("ITIMER_REAL: %ld, %ld\n", cur_itv.it_value.tv_sec, cur_itv.it_value.tv_usec);

    // getitimer(ITIMER_VIRTUAL, &cur_itv);
    // printf("ITIMER_VIRTUAL: %ld, %ld\n", cur_itv.it_value.tv_sec, cur_itv.it_value.tv_usec);

    // getitimer(ITIMER_PROF, &cur_itv);
    // printf("ITIMER_PROF: %ld, %ld\n", cur_itv.it_value.tv_sec, cur_itv.it_value.tv_usec);

    /* sleep(1); */
  }

  printf("main end\n");

  return 0;
}
```

### 7.1.2. alarm()

``` cpp {class=line-numbers}
#include <unistd.h>
unsigned int alarm(unsigned int seconds);
/**
  * @brief:
  *  - 在定时指定秒数后向调用进程发送 SIGALRM 信号，默认会终止调用进程
  *  - 可以捕捉该信号并执行特定的定时任务，从而实现定时器的功能
  *  - 每个进程只能由一个 alarm 定时器，且 alarm 计时与进程的状态无关（自然定时法，真实时间） 
  * @param: 
  *  - seconds：定时的秒数，当为 0 时，不执行任何动作或者取消原来设置的定时器
  * @return:
  *  - 如果先前没有设置定时器，则返回 0；否则返回先前定时器剩余的秒数
  **/
```

## 7.2. 定时器的调度和精度

取决于当前负载和对进程的调度，系统可能会在定时器到期的瞬间（通常是几分之一秒）之后才去调度其所属进程。尽管如此，由 `setitimer()` 或其他接口所创建的周期性定时器，在到期后依然会恪守其规律性。例如，假设设置一个实时定时器每两秒到期一次，虽然上述延迟可能会影响每个定时器事件的送达，但系统对后续定时器到期的调度依然会严格遵循两秒的时间间隔。换言之，间隔式定时器不受潜在错误左右。

虽然 `setitimer()` 使用的 `timeval` 结构提供有微秒级精度，但是传统意义上定时器精度还是受制于软件时钟频率。如果定时器值未能与软件时钟间隔的倍数严格匹配，那么定时器值则会向上取整。也就是说，假如有一个间隔为 19100 微秒（刚刚超过 19 毫秒）的定时器，如果 jiffy（软件时钟周期）为 4 毫秒，那么定时器实际上会每隔 20 毫秒过期一次。

对于现代 Linux 内核而言，关于定时器分辨率受限于软件时钟频率的论断已经不再成立。自版本 2.6.21 开始， Linux 内核可选择是否支持高分辨率定时器。如果选择支持（通过内核配置选项 `CONFIG_HIGH_RES_TIMERS`），那么各种定时器以及休眠接口的的精度则不再受内核 jiffy（软件时钟周期）的影响，可以达到底层硬件所支持的精度。在现代硬件平台上，精度达到微秒级是司空见惯的事情。

可通过 `clock_getres()` 的返回值来判断系统是否支持高分辨率定时器。

## 7.3. 休眠进程

### 7.3.1. sleep()

``` cpp {class=line-numbers}
#include <unistd.h>

unsigned int sleep(unsigned int seconds);
/**
  * @brief:
  *  - 将调用进程休眠 seconds 秒，或者在捕获到信号（从而中断调用）后恢复进程的运行
  *  - 由于系统负载的原因，内核可能会在完成 sleep() 的一段（通常很短）时间后才对进程重新加以调度
  *  - 一些老系统，会使用 alarm() 以及 SIGALRM 信号处理器函数来实现 sleep()，考虑到可移植性，应避免将 sleep() 和 alarm() 以及 setitimer() 混用
  * @param: 
  *  - seconds：指定让进程休眠的秒数
  * @return:
  *  - 如果休眠正常结束，返回 0；
  *  - 如果因为信号而中断休眠，返回剩余未休眠的秒数
  **/
```

### 7.3.2. nanosleep()

```cpp {class=line-numbers}
 #include <time.h>

int nanosleep(const struct timespec *rqtp, struct timespec *rmtp);

struct timespec
{
  time_t tv_sec; /* 秒数 */
  long tv_nsec;  /* 纳秒数 */
};

/**
  * @brief:
  *  - 功能类似 sleep()，可以以更高的分辨率来设定休眠时长
  *  - SUSv3 明文规定不得使用信号来实现该函数。这意味着，与 sleep() 不同，即使将 nanosleep() 与 alarm() 或 setitimer() 混用，也不会危及程序的可移植性
  *  - 虽然 nanosleep() 允许设定纳秒级精度的休眠间隔值，但其精度依然受制于软件时钟的间隔大小。如果指定的间隔值并非软件时钟间隔的整数倍，那么会对其向上取整
  *  - 支持高精度定时器的系统中，休眠时间间隔的精度要比软件时钟间隔精细许多
  * @param: 
  *  - rqtp：指定让进程休眠的时间
  *  - rmtp：传出参数，返回剩余的休眠时间，可利用这一返回值重启该系统调用以完成休眠
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

## 7.4. POSIX 时钟

POSIX 时钟（原定义于 POSIX.1b）所提供的时钟访问 API 可以支持纳秒级的时间精度，其中表示纳秒级时间值的 `timespec` 结构同样也用于 `nanosleep()` 调用。
Linux 中，调用此 API 的程序必须以 `-lrt` 选项进行编译，从而与 librt（realtime）函数库相链接。

POSIX 时钟 API 的主要系统调用包括获取时钟当前值的 `clock_gettime()`、 返回时钟分辨率的 `clock_getres()`，以及更新时钟的 `clock_settime()`。

POSIX.1b 时钟类型如下所示：

| 时钟ID                                      | 描述                                                                                                                                                                                                                          |
| :------------------------------------------ | :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| CLOCK_REALTIME                              | 可设定的系统级实时时钟，用于度量真实时间                                                                                                                                                                                      |
| CLOCK_MONOTONIC                             | 不可设定的恒定态时钟，对时间的度量始于“未予规范的过去某一时点”， 系统启动后就不会发生改变。 该时钟适用于那些无法容忍系统时钟发生跳跃性变化（例如：手工改变了系统时间）的应用程序。 Linux 上，这种时钟对时间的测量始于系统启动 |
| CLOCK_PROCESS_CPUTIME_ID（自 Linux 2.6.12） | 每进程 CPU 时间的时钟，测量调用进程所消耗的用户和系统 CPU 时间                                                                                                                                                                |
| CLOCK_THREAD_CPUTIME_ID（自 Linux 2.6.12）  | 每线程 CPU 时间的时钟，测量调用线程所消耗的用户和系统 CPU 时间                                                                                                                                                                |
| CLOCK_MONOTONIC_RAW（自 Linux 2.6.28）      | 类似于 CLOCK_MONOTONIC，这也是一种无法设置的时钟，但是提供了对纯基于硬件时间的访问，且不受 NTP 时间调整的影响。这种非标准时钟适用于专业时钟同步应用程序                                                                       |

```cpp {class=line-numbers}
int clock_gettime(clockid_t clk_id, struct timespec *tp);
/**
  * @brief:
  *  - 针对参数 clockid 所指定的时钟返回时间
  * @param: 
  *  - clk_id：
  *    - CLOCK_REALTIME：可设定的系统级实时时钟
  *    - CLOCK_MONOTONIC：不可设定的恒定态时钟，。
  *    - CLOCK_PROCESS_CPUTIME_ID：每进程 CPU 时间的时钟（自 Linux 2.6.12）
  *    - CLOCK_THREAD_CPUTIME_ID：每线程 CPU 时间的时钟（自 Linux 2.6.12）
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```


```cpp {class=line-numbers}
#include <time.h>

int clock_getres(clockid_t clk_id, struct timespec *res);
/**
  * @brief:
  *  - 获得由 clockid 所指定时钟的分辨率
  * @param: 
  *  - clk_id：
  *    - CLOCK_REALTIME：可设定的系统级实时时钟
  *    - CLOCK_MONOTONIC：不可设定的恒定态时钟
  *    - CLOCK_PROCESS_CPUTIME_ID：每进程 CPU 时间的时钟（自 Linux 2.6.12）
  *    - CLOCK_THREAD_CPUTIME_ID：每线程 CPU 时间的时钟（自 Linux 2.6.12）
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

```cpp {class=line-numbers}
int clock_settime(clockid_t clk_id, const struct timespec *tp);
/**
  * @brief:
  *  - 利用参数 tp 所指向缓冲区中的时间来设置由 clockid 指定的时钟
  *  - 特权级（CAP_SYS_TIME）进程可以设置 CLOCK_REALTIME 时钟。该时钟的初始值通常是自 Epoch（1970-01-01 00:00:00）以来的时间
  * @param: 
  *  - clk_id：时钟类型
  *  - tp：要设定的值
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

```cpp {class=line-numbers}
#include <time.h>

int clock_getcpuclockid(pid_t pid, clockid_t *clock_id);
/**
  * @brief:
  *  - 获取特定进程的时钟 ID
  *  - 如果要测量特定进程所消耗的 CPU 时间，则
  *    - 首先获取时钟 ID
  *    - 然后以此返回 ID 去调用 clock_gettime()，从而获得进程耗费的 CPU 时间
  * @param: 
  *  - pid：进程 ID，若为 0 表示当前调用进程
  *  - clock_id：传出参数，存储隶属于 pid 进程的 CPU 时间时钟的标识符
  * @return:
  *  - 成功：0
  *  - 失败：大于 0 的错误号
  **/
```

```cpp {class=line-numbers}
#include <pthread.h>
#include <time.h>

int pthread_getcpuclockid(pthread_t thread, clockid_t *clock_id);
/**
  * @brief:
  *  - 获取特定线程的时钟 ID
  *  - 如果要测量特定线程所消耗的 CPU 时间，则
  *    - 首先获取时钟 ID
  *    - 然后以此返回 ID 去调用 clock_gettime()，从而获得线程耗费的 CPU 时间。
  * @param: 
  *  - thread：线程 ID，若为 0 表示当前调用线程
  *  - clock_id：传出参数，存储隶属于 thread 线程的 CPU 时间时钟的标识符
  * @return:
  *  - 成功：0
  *  - 失败：大于 0 错误号
  **/
```

```cpp {class=line-numbers}
int clock_nanosleep(clockid_t clock_id, int flags, const struct timespec *request,
                    struct timespec *remain);
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

## 7.5. POSIX 间隔定时器

- 使用 `setitimer()` 来设置经典 UNIX 间隔式定时器，会受到如下制约：
  - 针对 ITIMER_REAL、 ITIMER_VIRTUAL 和 ITIMER_PROF 这 3 类定时器，每种只能设置一个。
  - 只能通过发送信号的方式来通知定时器到期。另外，也不能改变到期时产生的信号。
  - 如果一个间隔式定时器到期多次，且相应信号遭到阻塞时，那么会只调用一次信号处理器函数。换言之，无从知晓是否出现过定时器溢出（timer overrun）的情况。
  - 定时器的分辨率只能达到微秒级。不过，一些系统的硬件时钟提供了更为精细的时钟分辨率，软件此时应采用这一较高分辨率。
</br>

- POSIX.1b 定义了一套 API 来突破这些限制，Linux 2.6 实现了这一 API。POSIX 定时器 API 将定时器生命周期划分为如下几个阶段：
  - 以系统调用 `timer_create()` 创建一个新定时器，并定义其到期时对进程的通知方法。
  - 以系统调用 `timer_settime()` 来启动或停止一个定时器。
  - 以系统调用 `timer_delete()` 删除不再需要的定时器。
- 程序可以使用 `timer_create()` 创建多个间隔定时器。在当前实现中，内核会为每个用 `timer_create()` 创建的 POSIX 定时器在队列中预分配一个实时信号结构。之所以要采取预分配，旨在确保当定时器到期时，至少有一个有效结构可服务于所产生的队列化信号。这也意味着可以创建的 POSIX 定时器数量受制于排队实时信号的数量，因此，定时器的数量受 `RLIMIT_SIGPENDING` 资源限制（请参阅 `setrlimit(2)`）。
- 由 `fork()` 创建的子进程不会继承 POSIX 定时器。 调用 `exec()` 期间亦或进程终止时将停止并删除定时器。
- Linux 上，调用 POSIX 定时器 API 的程序编译时应使用 `-lrt` 选项，从而与 `librt` 函数库相链接。


### 7.5.1. timer_create()

```cpp {class=line-numbers}
#include <signal.h>
#include <time.h>

int timer_create(clockid_t clockid, struct sigevent *sevp, timer_t *timerid);

union sigval
{
  int sival_int;   /* Integer value */
  void *sival_ptr; /* Pointer value */
};

struct sigevent
{
  int sigev_notify;                            /* Notification method */
  int sigev_signo;                             /* Notification signal */
  union sigval sigev_value;                    /* Data passed with notification */
  void (*sigev_notify_function)(union sigval); /* Function used for thread notification (SIGEV_THREAD) */
  void *sigev_notify_attributes;               /* Attributes for notification thread (SIGEV_THREAD) */
  pid_t sigev_notify_thread_id;                /* ID of thread to signal (SIGEV_THREAD_ID) */
};

/**
  * @brief:
  *  - 创建一个新定时器，并以由 clockid 指定的时钟来进行时间度量
  * @param: 
  *  - clockid：
  *    - CLOCK_REALTIME：可设定的系统级实时时钟
  *    - CLOCK_MONOTONIC：不可设定的恒定态时钟
  *    - CLOCK_PROCESS_CPUTIME_ID：每进程 CPU 时间的时钟（自 Linux 2.6.12）
  *    - CLOCK_THREAD_CPUTIME_ID：每线程 CPU 时间的时钟（自 Linux 2.6.12）
  *  - sevp：具体如上所示
  *    - sigev_notify：定时器超时后的通知方式
  *      - SIGEV_NONE：不通知；使用 timer_gettime()监测定时器
  *      - SIGEV_SIGNAL：发送 sigev_signo 信号给进程
  *      - SIGEV_THREAD：调用 sigev_notify_function 作为新线程的启动函数
  *      - SIGEV_THREAD_ID：发送 sigev_signo 信号给 sigev_notify_thread_id 所标识的线程
  *  - timerid：传出参数，放置定时器句柄（handle），供后续调用中指代该定时器之用
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

### 7.5.2. timer_settime()

```cpp {class=line-numbers}
#include <time.h>

int timer_settime(timer_t timerid, int flags, const struct itimerspec *new_value,
                  struct itimerspec *old_value);
struct timespec
{
  time_t tv_sec; /* Seconds */
  long tv_nsec;  /* Nanoseconds */
};

struct itimerspec
{
  struct timespec it_interval; /* Timer interval */
  struct timespec it_value;    /* Initial expiration */
};

/**
  * @brief:
  *  - 配备（启动）或解除（停止）定时器
  *  - 为了启动定时器，需要调用函数 timer_settime()，并将 value.it_value 的一个或全部下属字段设为非 0 值
  *  - 如果之前曾经配备过定时器 timer_settime() 会将之前的设置替换掉
  *  - 如果要解除定时器，需要调用 timer_settime() 将 value.it_value 的所有字段指定为 0
  *  - 如果定时器的值和间隔时间并非对应时钟分辨率（由 clock_getres() 返回）的整数倍，那么会对这些值做向上取整处理
  * @param: 
  *  - timerid：定时器句柄（handle），由之前对 timer_create() 的调用获得
  *  - flags：
  *    - 0：value.it_value 是始于 timer_settime()（与 setitimer() 类似）调用时间点的相对值
  *    - TIMER_ABSTIME：value.it_value 是一个绝对时间（从时钟值 0 开始）。一旦时钟过了这一时间，定时器会立即到期
  *  - new_value：设置定时器的周期和初始超时时长
  *  - old_value：获取上一次定时器的超时属性
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/

int timer_gettime(timer_t timerid, struct itimerspec *curr_value);
/**
  * @brief:
  *  - 获取由 timerid 指定 POSIX 定时器的间隔以及剩余时间
  *  - 如果返回结构 curr_value.it_value 的两个字段均为 0，那么定时器当前处于停止状态
  *  - 如果返回结构 curr_value.it_interval 的两个字段都是 0，那么该定时器仅在 curr_value.it_value 给定的时间到期过一次
  * @param: 
  *  - curr_value：存储由 timerid 指定 POSIX 定时器的间隔以及剩余时间
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

### 7.5.3. timer_delete()

```cpp {class=line-numbers}
#include <time.h>

int timer_delete(timer_t timerid);
/**
  * @brief:
  *  - 每个 POSIX 定时器都会消耗少量系统资源。所以，一旦使用完毕，应当用 timer_delete() 来移除定时器并释放这些资源
  *  - 对于已启动的定时器，会在移除前自动将其停止
  *  - 如果因定时器到期而已经存在待定（pending）信号，那么信号会保持这一状态。（SUSv3 对此并未加以规范，所以其他的一些 UNIX 实现可能会有不同行为）
  *  - 当进程终止时，会自动删除所有定时器
  * @param: 
  *  - timerid：之前调用 timer_create() 时返回的句柄
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

### 7.5.4. 通过信号通知

- Posix 间隔定时器产生的信号可以由进程内的任意一个线程进行处理？？？
</br>

- 如果选择通过信号来接收定时器通知，那么处理这些信号时既可以采用信号处理器函数 `sigaction()`，也可以调用 `sigwaitinfo()` 或是 `sigtimerdwait()`。接收进程借助于这两种方法可以获得一个 `siginfo_t` 结构，其中包含与信号相关的深入信息，在结构 `siginfo_t` 中设置了如下字段：
  - `si_signo`：包含由定时器产生的信号。
  - `si_code`：置为 SI_TIMER，表示这是因 POSIX 定时器到期而产生的信号。
  - `si_value`：将该字段置为以 `timer_create()` 创建定时器时在 `evp.sigev_value` 中提供的值。为 sevp.sigev_value 指定不同的值， 可以将到期时发送同类信号的不同定时器区分开来。
- 调用 `timer_create()` 时，通常将 `sevp.sigev_value.sival_ptr` 赋值为当前调用中参数 `timerid` 的地址。从而允许信号处理器函数（或 `sigwaitinfo()` 调用）获得产生信号的定时器 ID。（另外，也可以将调用函数 `timer_create()` 时给定的 `timerid` 参数置于一结构体中，并将结构地址赋予 `sevp.sigev_value.sival_ptr`。）
- Linux 还为 `siginfo_t` 结构提供了非标准字段：`si_overrun`，其中包含了定时器溢出个数。

### 7.5.5. 通过线程通知

- SIGEV_THREAD 标志允许程序从一个独立的线程中调用函数来获取定时器到期通知。
- 每当定时器到期时，会在一条独立线程中调用由 `sevp.sigev_notify_function` 指定的函数。调用函数时，使用由 `sev.sigev_value.sival_ptr` 指定的值作为参数。通常将 `sevp.sigev_value.sival_ptr` 赋值为当前调用中参数 `timerid` 的地址。从而允许信号处理器函数（或 `sigwaitinfo()` 调用）获得产生信号的定时器 ID 。（另外，也可以将调用函数 `timer_create()` 时给定的 `timerid` 参数置于一结构体中，并将结构地址赋予 `sevp.sigev_value.sival_ptr`。）

### 7.5.6. 定时器溢出

- 当使用信号的方式来发送定时器到期通知时，在捕获或接收相关信号之前，定时器可能会到期多次。这可能是因为进程再次获得调度前的延时所致。另外，不论是直接调用 `sigprocmask()`，还是在信号处理器函数里暗中处理，也都有可能堵塞相关到期信号的发送。如何知道发生了这些定时器溢出呢？
- POSIX.1b 规定：一旦选择通过信号来接收定时器通知，那么即便用了实时信号，也绝不会对该信号的多个实例进行排队。相反，在接收信号后（无论是通过信号处理器函数还是调用 `sigwaitinfo()`），可以获取定时器溢出计数，即在信号生成与接收之间发生的定时器到期额外次数。如果上次收到信号后定时器发生了 3 次到期，那么溢出计数是 2。每次收到定时器信号后，都会重置定时器溢出计数。若自处理或接收定时器信号之后，定时器仅到期一次，则溢出计数为 0（即无溢出）接收到定时器信号之后，有两种方法可以获取定时器溢出值
  - 调用 `timer_getoverrun()`。
  - 使用随信号一同返回的结构 `siginfo_t` 中的 `si_overrun` 字段值。这种方法可以避免 `timer_getoverrun()` 的系统调用开销，但同时也是一种 Linux 扩展方法，无法移植。
- 通过线程通知也可能产生定时器溢出的问题，因为在调用新线程的通知函数前，定时器可能会多次到期

```cpp {class=line-numbers}
#include <time.h>

int timer_getoverrun(timer_t timerid);
/**
  * @brief:
  *  - 获得由参数 timerid 指定定时器的溢出值
  * @param: 
  *  - timerid：Posix 定时器标识
  * @return:
  *  - 成功：返回定时器溢出值
  *  - 失败：-1，并设置 errno
  **/
```

## 7.6. 利用文件描述符进行通知的定时器： timerfd API

始于版本 2.6.25， Linux 内核提供了另一种创建定时器的 API。 Linux 特有的 timerfd API，可从文件描述符中读取其所创建定时器的到期通知。因此可以使用 `select()`、 `poll()` 和 `epoll()` 将这种文件描述符会同其他描述符一同进行监控，所以非常实用。

```cpp {class=line-numbers}
#include <sys/timerfd.h>

int timerfd_create(int clockid, int flags);

int timerfd_settime(int fd, int flags, const struct itimerspec *new_value, struct itimerspec *old_value);

int timerfd_gettime(int fd, struct itimerspec *curr_value);
```

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