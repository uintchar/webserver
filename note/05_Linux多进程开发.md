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
- [4. 进程间通信](#4-进程间通信)
  - [4.1. 匿名管道](#41-匿名管道)
    - [4.1.1. 管道的特点](#411-管道的特点)
    - [4.1.2. 管道的数据结构](#412-管道的数据结构)
    - [4.1.3. 匿名管道的使用](#413-匿名管道的使用)
    - [4.1.4. 应用示例](#414-应用示例)
      - [4.1.4.1. 父进程向子进程发送消息](#4141-父进程向子进程发送消息)
      - [4.1.4.2. 实现 `ps aux | grep xxx` 父子进程间通信](#4142-实现-ps-aux--grep-xxx-父子进程间通信)
      - [4.1.4.3. 设置管道非阻塞](#4143-设置管道非阻塞)
  - [4.2. 有名管道 FIFO](#42-有名管道-fifo)
    - [4.2.1. 有名管道的特点](#421-有名管道的特点)
    - [4.2.2. 有名管道的使用](#422-有名管道的使用)
    - [4.2.3. 应用示例](#423-应用示例)
      - [4.2.3.1. 不同进程使用有名管道进行通信](#4231-不同进程使用有名管道进行通信)
  - [4.3. 内存映射](#43-内存映射)
    - [4.3.1. 内存映射相关系统调用](#431-内存映射相关系统调用)
    - [4.3.2. 应用示例](#432-应用示例)
  - [4.4. 信号](#44-信号)
    - [4.4.1. 信号的概念](#441-信号的概念)
    - [4.4.2. Linux 信号一览](#442-linux-信号一览)
    - [4.4.3. 信号的 5 种默认处理动作](#443-信号的-5-种默认处理动作)
    - [4.4.4. 信号相关函数](#444-信号相关函数)
    - [4.4.5. 信号捕捉函数](#445-信号捕捉函数)
    - [4.4.6. 信号集](#446-信号集)
    - [4.4.7. 内核实现信号捕捉的过程](#447-内核实现信号捕捉的过程)
    - [4.4.8. 多线程中的信号处理机制](#448-多线程中的信号处理机制)
    - [4.4.9. 应用示例](#449-应用示例)
      - [4.4.9.1. 信号捕捉实现周期性定时器](#4491-信号捕捉实现周期性定时器)
      - [4.4.9.2. 使用SIGCHLD信号解决僵尸进程的问题](#4492-使用sigchld信号解决僵尸进程的问题)
      - [4.4.9.3. 信号集操作函数范例](#4493-信号集操作函数范例)
  - [4.5. 共享内存](#45-共享内存)
    - [4.5.1. 共享内存的概念](#451-共享内存的概念)
    - [4.5.2. 共享内存的使用步骤](#452-共享内存的使用步骤)
    - [4.5.3. 共享内存操作函数](#453-共享内存操作函数)
    - [4.5.4. 应用示例](#454-应用示例)
  - [4.6. POSIX消息队列](#46-posix消息队列)
    - [4.6.1. POSIX消息队列概述](#461-posix消息队列概述)
    - [4.6.2. mq_open()](#462-mq_open)
    - [4.6.3. mq_close()](#463-mq_close)
    - [4.6.4. mq_unlink()](#464-mq_unlink)
    - [4.6.5. mq_send()](#465-mq_send)
    - [4.6.6. mq_receive()](#466-mq_receive)
    - [4.6.7. mq_notify()](#467-mq_notify)
    - [4.6.8. mq_attr](#468-mq_attr)
    - [4.6.9. POSIX消息队列限制](#469-posix消息队列限制)
    - [4.6.10. 应用示例](#4610-应用示例)
- [5. 终端、会话和守护进程](#5-终端会话和守护进程)
  - [5.1. 终端](#51-终端)
  - [5.2. 进程组](#52-进程组)
  - [5.3. 会话](#53-会话)
  - [5.4. 进程组、会话操作函数](#54-进程组会话操作函数)
  - [5.5. 守护进程](#55-守护进程)
    - [5.5.1. 应用示例](#551-应用示例)
      - [5.5.1.1. 每 1s 向磁盘文件打印当前系统时间的守护进程](#5511-每-1s-向磁盘文件打印当前系统时间的守护进程)
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

# 4. 进程间通信

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

## 4.1. 匿名管道

### 4.1.1. 管道的特点

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

### 4.1.2. 管道的数据结构

- 环形队列；

### 4.1.3. 匿名管道的使用

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
### 4.1.4. 应用示例

#### 4.1.4.1. 父进程向子进程发送消息

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

#### 4.1.4.2. 实现 `ps aux | grep xxx` 父子进程间通信

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

#### 4.1.4.3. 设置管道非阻塞

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

## 4.2. 有名管道 FIFO

### 4.2.1. 有名管道的特点

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

### 4.2.2. 有名管道的使用

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

### 4.2.3. 应用示例

#### 4.2.3.1. 不同进程使用有名管道进行通信

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

## 4.3. 内存映射

### 4.3.1. 内存映射相关系统调用

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

### 4.3.2. 应用示例

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

## 4.4. 信号

### 4.4.1. 信号的概念

- 信号是 Linux 进程间通信的最古老的方式之一，是事件发生时对进程的通知机制，有时也称之为软件中断，它是在软件层次上对中断机制的一种模拟，是一种异步通信的方式。信号可以导致一个正在运行的进程被另一个正在运行的异步进程中断，转而处理某一个突发事件；
- 发往进程的诸多信号，通常都是源于内核。引发内核为进程产生信号的各类事件如下：
  - 对于前台进程，用户可以通过输入特殊的终端字符来给它发送信号。比如输入 `Ctrl+C` 通常会给进程发送一个中断信号；
  - 硬件发生异常，即硬件检测到一个错误条件并通知内核，随即再由内核发送相应信号给相关进程。比如执行一条异常的机器语言指令，诸如被 0 除，或者引用了无法访问的内存区域；
  - 系统状态变化，比如 `alarm` 定时器到期将引起 `SIGALRM` 信号，进程执行的 CPU时间超限，或者该进程的某个子进程退出；
  - 运行 kill 命令或调用 kill 函数；
- 使用信号的两个主要目的是：
  - 让进程知道已经发生了一个特定的事情；
  - 强迫进程执行它自己代码中的信号处理程序；
- 信号的特点：
  - 简单，不能携带大量信息；
  - 满足某个特定条件才发送；
  - 优先级比较高；
- 查看系统定义的信号列表： `kill –l`，其中前 31 个信号为常规信号，其余为实时信号；

### 4.4.2. Linux 信号一览

| 编号  |     信号名称      | 对应事件                                                                                                                   | 默认动作                   |
| :---: | :---------------: | :------------------------------------------------------------------------------------------------------------------------- | :------------------------- |
|   1   |      SIGHUP       | 用户退出 shell 时，由该 shell 启动的所有进程将收到这个信号                                                                 | 终止进程                   |
|   2   |      SIGINT       | 当用户按下了 `Ctrl+C` 组合键时，用户终端向正在运行中的由该终端启动的程序发出此信号                                         | 终止进程                   |
|   3   |      SIGQUIT      | 用户按下 `Ctrl+\` 组合键时产生该信号，用户终端向正在运行中的由该终端启动的进程发出些信号                                   | 终止进程                   |
|   4   |      SIGILL       | CPU 检测到某进程执行了非法指令                                                                                             | 终止进程并产生core文件     |
|   5   |      SIGTRAP      | 该信号由断点指令或其他 `trap` 指令产生                                                                                     | 终止进程并产生core文件     |
|   6   |      SIGABRT      | 调用 `abort` 函数时产生该信号                                                                                              | 终止进程并产生core文件     |
|   7   |      SIGBUS       | 非法访问内存地址，包括内存对齐出错                                                                                         | 终止进程并产生core文件     |
|   8   |      SIGFPE       | 在发生致命的运算错误时发出。不仅包括浮点运算错误，还包括溢出及除数为0等所有的算法错误                                      | 终止进程并产生core文件     |
|   9   |      SIGKILL      | 无条件终止进程。该信号不能被忽略，处理和阻塞                                                                               | 终止进程，可以杀死任何进程 |
|  10   |      SIGUSR1      | 用户定义的信号。即程序员可以在程序中定义并使用该信号                                                                       | 终止进程                   |
|  11   |      SIGSEGV      | 指示进程进行了无效内存访问(段错误)                                                                                         | 终止进程并产生core文件     |
|  12   |      SIGUSR2      | 另外一个用户自定义信号，程序员可以在程序中定义并使用该信号                                                                 | 终止进程                   |
|  13   |      SIGPIPE      | Broken pipe 向一个没有读端的管道写数据                                                                                     | 终止进程                   |
|  14   |      SIGALRM      | 定时器超时，超时的时间由系统调用 `alarm` 设置                                                                              | 终止进程                   |
|  15   |      SIGTERM      | 程序结束信号，与 SIGKILL 不同的是，该信号可以被阻塞和终止。通常用来要示程序正常退出。执行shell命令Kill时，缺省产生这个信号 | 终止进程                   |
|  16   |     SIGSTKFLT     | Linux 早期版本出现的信号，现仍保留向后兼容                                                                                 | 终止进程                   |
|  17   |      SIGCHLD      | 子进程结束时(终止、收到 SIGSTOP 停止、处在停止态收到 SIGCONT 唤醒），父进程会收到这个信号                                  | 忽略这个信号               |
|  18   |      SIGCONT      | 如果进程已停止，则使其继续运行                                                                                             | 继续/忽略                  |
|  19   |      SIGSTOP      | 停止进程的执行。信号不能被忽略，处理和阻塞                                                                                 | 为终止进程                 |
|  20   |      SIGTSTP      | 停止终端交互进程的运行。按下 `ctrl+z` 组合键时发出这个信号                                                                 | 暂停进程                   |
|  21   |      SIGTTIN      | 后台进程读终端控制台                                                                                                       | 暂停进程                   |
|  22   |      SIGTTOU      | 该信号类似于 SIGTTIN，在后台进程要向终端输出数据时发生                                                                     | 暂停进程                   |
|  23   |      SIGURG       | 套接字上有紧急数据时，向当前正在运行的进程发出些信号，报告有紧急数据到达。如网络带外数据到达                               | 忽略该信号                 |
|  24   |      SIGXCPU      | 进程执行时间超过了分配给该进程的 CPU 时间，系统产生该信号并发送给该进程                                                    | 终止进程                   |
|  25   |      SIGXFSZ      | 超过文件的最大长度设置                                                                                                     | 终止进程                   |
|  26   |     SIGVTALRM     | 虚拟时钟超时时产生该信号。类似于 SIGALRM，但是该信号只计算该进程占用 CPU 的使用时间                                        | 终止进程                   |
|  27   |      SGIPROF      | 类似于 SIGVTALRM，它不仅包括该进程占用 CPU 时间还包括执行系统调用时间                                                      | 终止进程                   |
|  28   |     SIGWINCH      | 窗口变化大小时发出 忽略该信号                                                                                              |
|  29   |       SIGIO       | 此信号向进程指示发出了一个异步 IO 事件 忽略该信号                                                                          |
|  30   |      SIGPWR       | 关机                                                                                                                       | 终止进程                   |
|  31   |      SIGSYS       | 无效的系统调用                                                                                                             | 终止进程并产生core文件     |
| 34~64 | SIGRTMIN~SIGRTMAX | LINUX 的实时信号，它们没有固定的含义（可以由用户自定义）                                                                   | 终止进程                   |

### 4.4.3. 信号的 5 种默认处理动作

- 查看信号的详细信息： man 7 signal
- 信号的 5 中默认处理动作
  - Term 终止进程
  - Ign 当前进程忽略掉这个信号
  - Core 终止进程，并生成一个Core文件
  - Stop 暂停当前进程
  - Cont 继续执行当前被暂停的进程
- 信号的几种状态：产生、未决、递达
- SIGKILL 和 SIGSTOP 信号不能被捕捉、阻塞或者忽略，只能执行默认动作。
- 生成 core 文件 `ulimit -c new_size`

### 4.4.4. 信号相关函数

```cpp {class=line-numbers}
int kill(pid_t pid, int sig);
int raise(int sig);
void abort(void);
unsigned int alarm(unsigned int seconds);
int setitimer(int which, const struct itimerval *new_val, struct itimerval *old_value);
int getitimer(int which, struct itimerval *curr_value);

#include <sys/types.h>
#include <signal.h>
int kill(pid_t pid, int sig);
/**
  * @brief:
  *  - 向任何进程或者进程组发送任意的信号
  * @param: 
  *  - pit_t pid：指定的进程或者进程组 id
  *    - pid > 0：向指定的进程发送信号
  *    - pid = 0：向调用进程所在的进程组发送信号
  *    - pid = -1：向任何具有接收该信号权限的进程发送信号
  *    - pid < -1：向指定的进程组发送信号，进程组 id 取绝对值
  *  - int sig：发送信号的编号或者宏值，为 0 表示不发送信号
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/

#include <signal.h>
int raise(int sig);
/**
  * @brief:
  *  - 给调用进程或线程发送指定的信号，如果信号导致调用一个信号处理程序，则 raise() 将在处理程序返回之后再返回
  *  - 在单线程程序中等价于 kill(getpid(), sig)
  *  - 在多线程程序中等价于 pthread_kill(pthread_self(), sig)
  * @param: 
  *  - int sig：信号的编号或者宏值
  * @return:
  *  - 成功：0
  *  - 失败：非 0
  **/

#include <stdlib.h>
void abort(void);
/**
  * @brief:
  *  - 首先解阻塞 SIGABRT 信号，然后向当前进程发送 SIGABRT 信号
  *  - 这会使得进程异常终止，除非捕获 SIGABRT 信号且信号处理程序不返回
  * @param: 
  *  - void
  * @return:
  *  - void
  **/
```

### 4.4.5. 信号捕捉函数

```cpp {class=line-numbers}
sighandler_t signal(int signum, sighandler_t handler);
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
/**
  * @brief:
  *  - 捕获特定信号，并执行指定的信号处理程序
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

#include <signal.h>
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
/**
  * @brief:
  *  - 检查或更改进程受到信号后的处理动作，用于捕捉信号实现软中断
  * @param: 
  *  - int signum：特定的信号
  *  - const struct sigaction *act：设置捕捉到信号的处理行为
  *  - struct sigaction *oldact：获取上一次设置的捕捉到信号的处理行为
       struct sigaction 
       {
          void (*sa_handler)(int); // 信号捕捉到之后的处理函数
          void (*sa_sigaction)(int, siginfo_t *, void *); // 不常用
          sigset_t sa_mask; // 临时阻塞信号集，在信号捕捉函数执行过程中，临时阻塞某些信号
          int sa_flags; // 0 表示使用 sa_handler，SA_SIGINFO 表示使用 sa_sigaction
          void (*sa_restorer)(void); // 被废弃掉了
        };
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

### 4.4.6. 信号集

- 许多信号相关的系统调用都需要能表示一组不同的信号，多个信号可使用一个称之为信号集的数据结构来表示，其系统数据类型为 `sigset_t`
- 在 PCB 中有两个非常重要的信号集。一个称之为**阻塞信号集** ，另一个称之为**未决信号集**。这两个信号集都是内核使用位图机制来实现的。但操作系统不允许我们直接对这两个信号集进行位操作。而需自定义另外一个集合，借助信号集操作函数来对 PCB 中的这两个信号集进行修改
- **对于多线程的进程而言，每一个线程都具有独立的信号掩码**
- 信号的 “未决” 是一种状态，指的是从信号的产生到信号被处理前的这一段时间；信号的 “阻塞” 是一个开关动作，指的是阻止信号被处理，但不是阻止信号产生
- 信号的阻塞就是让系统暂时保留信号留待以后发送。由于另外有办法让系统忽略信号，所以一般情况下信号的阻塞只是暂时的，只是为了防止信号打断敏感的操作

```cpp {class=line-numbers}
// 信号集相关函数

#include <signal.h>

int sigemptyset(sigset_t *set);
/**
  * @brief:
  *  - 清空信号集中的数据，将信号集中的所有的标志位置为0
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
  *  - 判断某个信号是否阻塞
  * @param: 
  *  - const sigset_t *set：需要操作的信号集
  *  - int signum：需要判断的信号
  * @return:
  *  - 成功：1 表示 signum 被阻塞；0 表示不阻塞
  *  - 失败：-1，并设置 errno
  **/

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
/**
  * @brief:
  *  - 将自定义信号集中的数据设置到内核中（设置阻塞，解除阻塞，替换）
  *  - 在多线程进程中未指定 sigprocmask 的使用，应使用 pthread_sigmask()
  * @param: 
  *  - int how:
  *    - SIG_BLOCK：将用户设置的阻塞信号集添加到内核中，内核中原来的数据不变。假设内核中默认的阻塞信号集是 mask，mask | set
  *    - SIG_UNBLOCK：根据用户设置的数据，对内核中的数据进行解除阻塞 mask &= ~set
  *    - SIG_SETMASK：覆盖内核中原来的值
  *  - 
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/

int sigpending(sigset_t *set);
/**
  * @brief:
  *  - 获取内核中的未决信号集
  * @param: 
  *  - sigset_t *set：传出参数，保存的时内核中的未决信号集中的信息
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
  **/
```

### 4.4.7. 内核实现信号捕捉的过程

- 用户通过键盘  Ctrl + C, 产生 2 号信号 SIGINT (信号被创建)
- 信号产生但是没有被处理（未决）
  - 在内核中将所有的没有被处理的信号存储在一个集合中 （未决信号集）
  - SIGINT 信号状态被存储在第二个标志位上
    - 这个标志位的值为 0，说明信号不是未决状态
    - 这个标志位的值为 1，说明信号处于未决状态
- 这个未决状态的信号，需要被处理，处理之前需要和另一个信号集（阻塞信号集）进行比较
  - 阻塞信号集默认不阻塞任何的信号
  - 如果想要阻塞某些信号需要用户调用系统的API
- 在处理的时候和阻塞信号集中的标志位进行查询，看是不是对该信号设置阻塞了
  - 如果没有阻塞，这个信号就被处理
  - 如果阻塞了，这个信号就继续处于未决状态，直到阻塞解除，这个信号就被处理

![内核实现信号捕捉的过程](webserver/note/figure/内核实现信号捕捉的过程.JPG)

### 4.4.8. 多线程中的信号处理机制

### 4.4.9. 应用示例

#### 4.4.9.1. 信号捕捉实现周期性定时器

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

#### 4.4.9.2. 使用SIGCHLD信号解决僵尸进程的问题

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

#### 4.4.9.3. 信号集操作函数范例

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

## 4.5. 共享内存

### 4.5.1. 共享内存的概念

### 4.5.2. 共享内存的使用步骤

### 4.5.3. 共享内存操作函数

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

### 4.5.4. 应用示例

## 4.6. POSIX消息队列

### 4.6.1. POSIX消息队列概述

```cpp {class=line-numbers}
mq_open() 函数创建一个新消息队列或打开一个既有队列，返回后续调用中会用到的消息队列描述符。
mq_send() 函数向队列写入一条消息。
mq_receive() 函数从队列中读取一条消息。
mq_close() 函数关闭进程之前打开的一个消息队列。
mq_unlink() 函数删除一个消息队列名并当所有进程关闭该队列时对队列进行标记以便删除
mq_notify() 函数允许一个进程向一个队列注册接收消息通知。在注册完之后，当一条消息可用时会通过发送一个信号或在一个单独的线程中调用一个函数来通知进程。
```

### 4.6.2. mq_open()

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

### 4.6.3. mq_close()

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

### 4.6.4. mq_unlink()

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

### 4.6.5. mq_send()

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

### 4.6.6. mq_receive()

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

### 4.6.7. mq_notify()

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

### 4.6.8. mq_attr

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

### 4.6.9. POSIX消息队列限制

- **MQ_PRIO_MAX：** 
- **MQ_OPEN_MAX：** 指明一个进程最多能打开的消息队列数量。 SUSv3 要求这个限制最小为 _POSIX_MQ_OPEN_MAX（8）。 Linux 并没有定义这个限制，相反，由于 Linux 将消息队列描述符实现成了文件描述符，因此适用于文件描述符的限制将适用于消息队列描述符
- **msg_max：** 为新消息队列的 `mq_maxmsg` 特性的取值规定了一个上限。这个限制的默认值是 10，最小值是 1（在早于 2.6.28 的内核中是 10），最大值由内核常量 `HARD_MSGMAX` 定义，该常量的值是通过公式 `(131072 / sizeof(void *))` 计算得来的，在 Linux/x86-32 上其值为 32768。当一个特权进程（CAP_SYS_RESOURCE）调用 `mq_open()` 时 `msg_max` 限制会被忽略，但 `HARD_MSGMAX` 仍然担当着 `mq_maxmsg` 的上限值的角色
- **msgsize_max：** 为非特权进程创建的新消息队列的 mq_msgsize 特性的取值规定了一个上限（即使用 `mq_open()` 创建队列时 `attr.mq_msgsize` 字段的上限值）。这个限制的默认值是 8192，最小值是 128（在早于 2.6.28 的内核中是 8192），最大值是 1048576（在早于 2.6.28 的内核中是 INT_MAX）。当一个特权进程调用 `mq_open()` 时会忽略这个限制
- **queues_max：** 系统级别的限制，规定了系统上最多能够创建的消息队列的数量。一旦达到这个限制，就只有特权进程才能够创建新队列。这个限制的默认值是 256，其取值可以为范围从 0 到 INT_MAX 之间的任意一个值。

- Linux 还提供了一些/proc 文件来查看和修改（需具备特权）控制 POSIX 消息队列的使用的限制。下面这三个文件位于 /proc/sys/fs/mqueue 目录中（`man 7 mq_overview`）

### 4.6.10. 应用示例

# 5. 终端、会话和守护进程

## 5.1. 终端

- 在 UNIX 系统中，用户通过终端登录系统后得到一个 shell 进程，这个终端成为 shell 进程的控制终端；
- 进程中，控制终端是保存在 PCB 中的信息，而 `fork()` 会复制 PCB 中的信息，因此由 shell 进程启动的其它进程的控制终端也是这个终端；
- 默认情况下（没有重定向），每个进程的标准输入、标准输出和标准错误输出都指向控制终端，进程从标准输入读也就是读用户的键盘输入，进程往标准输出或标准错误输出写也就是输出到显示器上；
- 在控制终端输入一些特殊的控制键可以给前台进程发信号，例如 `Ctrl + C` 会产生 `SIGINT` 信号， `Ctrl + \` 会产生 `SIGQUIT` 信号；
- `echo $$`：显示当前 shell 进程的进程号；

## 5.2. 进程组

- 进程组和会话在进程之间形成了一种两级层次关系：进程组是一组相关进程的集合，会话是一组相关进程组的集合。进程组和会话是为支持 shell 作业控制而定义的抽象概念，用户通过 shell 能够交互式地在前台或后台运行命令；
- 进行组由一个或多个共享同一进程组标识符（PGID）的进程组成。一个进程组拥有一个进程组首进程，该进程是创建该组的进程，其进程 ID 为该进程组的 ID，新进程会继承其父进程所属的进程组 ID；
- 进程组拥有一个生命周期，其开始时间为首进程创建组的时刻，结束时间为最后一个成员进程退出组的时刻。一个进程可能会因为终止而退出进程组，也可能会因为加入了另外一个进程组而退出进程组。进程组首进程无需是最后一个离开进程组的成员；

## 5.3. 会话

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

## 5.4. 进程组、会话操作函数

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

## 5.5. 守护进程

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

### 5.5.1. 应用示例

#### 5.5.1.1. 每 1s 向磁盘文件打印当前系统时间的守护进程

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

| 时钟ID                   | 描述                                     |
| :----------------------- | :--------------------------------------- |
| CLOCK_REALTIME           | 可设定的系统级实时时钟，用于度量真实时间   |
| CLOCK_MONOTONIC          | 不可设定的恒定态时钟，对时间的度量始于“未予规范的过去某一时点”， 系统启动后就不会发生改变。 该时钟适用于那些无法容忍系统时钟发生跳跃性变化（例如：手工改变了系统时间）的应用程序。 Linux 上，这种时钟对时间的测量始于系统启动 |
| CLOCK_PROCESS_CPUTIME_ID（自 Linux 2.6.12）| 每进程 CPU 时间的时钟，测量调用进程所消耗的用户和系统 CPU 时间 |
| CLOCK_THREAD_CPUTIME_ID（自 Linux 2.6.12） | 每线程 CPU 时间的时钟，测量调用线程所消耗的用户和系统 CPU 时间 |
| CLOCK_MONOTONIC_RAW（自 Linux 2.6.28） | 类似于 CLOCK_MONOTONIC，这也是一种无法设置的时钟，但是提供了对纯基于硬件时间的访问，且不受 NTP 时间调整的影响。这种非标准时钟适用于专业时钟同步应用程序 |

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
  *    - CLOCK_MONOTONIC：不可设定的恒定态时钟，。
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

### 7.5.5. 通过线程通知

### 7.5.6. 定时器溢出

通过信号通知和通过线程通知都可能产生定时器溢出的问题

```cpp {class=line-numbers}
#include <time.h>

int timer_getoverrun(timer_t timerid);
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

## 7.6. 利用文件描述符进行通知的定时器： timerfd API

始于版本 2.6.25， Linux 内核提供了另一种创建定时器的 API。 Linux 特有的 timerfd API，可从文件描述符中读取其所创建定时器的到期通知。因此可以使用 `select()`、 `poll()` 和 `epoll()` 将这种文件描述符会同其他描述符一同进行监控，所以非常实用。

```cpp {class=line-numbers}
#include <sys/timerfd.h>

int timerfd_create(int clockid, int flags);

int timerfd_settime(int fd, int flags, const struct itimerspec *new_value,
                    struct itimerspec *old_value);

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