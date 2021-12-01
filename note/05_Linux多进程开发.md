- [1. 进程概述](#1-进程概述)
  - [1.1. 程序和进程](#11-程序和进程)
  - [1.2. 进程控制块 PCB](#12-进程控制块-pcb)
  - [1.3. 进程状态转换](#13-进程状态转换)
- [2. Linux 进程相关命令](#2-linux-进程相关命令)
  - [2.1. ps](#21-ps)
  - [2.2. top](#22-top)
  - [2.3. kill](#23-kill)
  - [2.4. 进程号和相关函数](#24-进程号和相关函数)
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
    - [4.1.4. 使用范例](#414-使用范例)
  - [4.2. 有名管道 FIFO](#42-有名管道-fifo)
    - [有名管道 FIFO 的特点](#有名管道-fifo-的特点)

# 1. 进程概述

## 1.1. 程序和进程

## 1.2. 进程控制块 PCB

## 1.3. 进程状态转换

# 2. Linux 进程相关命令

## 2.1. ps

## 2.2. top

## 2.3. kill

## 2.4. 进程号和相关函数

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
### 4.1.4. 使用范例

- 父进程向子进程发送消息

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

- 实现 `ps aux | grep xxx` 父子进程间通信

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

- 设置管道非阻塞

  ```cpp {class=line-numbers}

  ```

## 4.2. 有名管道 FIFO

### 有名管道 FIFO 的特点

- FIFO 不仅可以用于具有亲缘关系的进程间通信，还可以用于不存在亲缘关系的进程间通信