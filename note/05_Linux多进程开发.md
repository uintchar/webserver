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
    - [4.1.4. 使用范例](#414-使用范例)
  - [4.2. 有名管道 FIFO](#42-有名管道-fifo)
    - [4.2.1. 有名管道的特点](#421-有名管道的特点)
    - [4.2.2. 有名管道的使用](#422-有名管道的使用)
    - [4.2.3. 使用范例](#423-使用范例)
  - [4.3. 内存映射](#43-内存映射)
    - [4.3.1. 内存映射相关系统调用](#431-内存映射相关系统调用)
    - [4.3.2. 应用范例](#432-应用范例)
  - [4.4. 信号](#44-信号)
    - [4.4.1. 信号的概念](#441-信号的概念)
    - [4.4.2. Linux 信号一览](#442-linux-信号一览)
    - [4.4.3. 信号的 5 种默认处理动作](#443-信号的-5-种默认处理动作)
    - [4.4.4. 信号相关函数](#444-信号相关函数)
    - [4.4.5. 信号捕捉函数](#445-信号捕捉函数)
    - [4.4.6. 信号集](#446-信号集)
    - [4.4.7. 内核实现信号捕捉的过程](#447-内核实现信号捕捉的过程)
    - [4.4.8. 多线程中的信号处理机制](#448-多线程中的信号处理机制)
    - [4.4.9. 应用范例](#449-应用范例)
      - [4.4.9.1. 信号捕捉实现周期性定时器](#4491-信号捕捉实现周期性定时器)
      - [4.4.9.2. 使用SIGCHLD信号解决僵尸进程的问题](#4492-使用sigchld信号解决僵尸进程的问题)
      - [4.4.9.3. 信号集操作函数范例](#4493-信号集操作函数范例)
  - [4.5. 共享内存](#45-共享内存)
    - [4.5.1. 共享内存的概念](#451-共享内存的概念)
    - [4.5.2. 共享内存的使用步骤](#452-共享内存的使用步骤)
    - [4.5.3. 共享内存操作函数](#453-共享内存操作函数)
    - [4.5.4. 应用范例](#454-应用范例)
  - [4.6. 守护进程](#46-守护进程)
    - [4.6.1. 终端](#461-终端)
    - [4.6.2. 进程组](#462-进程组)
    - [4.6.3. 会话](#463-会话)
    - [4.6.4. 进程组、会话操作函数](#464-进程组会话操作函数)
    - [4.6.5. 守护进程](#465-守护进程)
    - [4.6.6. 应用范例](#466-应用范例)
      - [4.6.6.1. 每 1s 向磁盘文件打印当前系统时间的守护进程](#4661-每-1s-向磁盘文件打印当前系统时间的守护进程)

# 1. 进程概述

## 1.1. 程序和进程

## 1.2. 进程控制块 PCB

## 1.3. 进程状态转换

# 2. Linux 进程相关命令

## 2.1. ps

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

### 4.2.3. 使用范例

- 不同进程使用有名管道进行通信

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

### 4.3.2. 应用范例

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

编号 | 信号名称 | 对应事件 | 默认动作
:-: | :------: | :------- | :- 
1  | SIGHUP    | 用户退出 shell 时，由该 shell 启动的所有进程将收到这个信号 | 终止进程
2  | SIGINT    | 当用户按下了 `Ctrl+C` 组合键时，用户终端向正在运行中的由该终端启动的程序发出此信号 | 终止进程
3  | SIGQUIT   | 用户按下 `Ctrl+\` 组合键时产生该信号，用户终端向正在运行中的由该终端启动的进程发出些信号 | 终止进程
4  | SIGILL    | CPU 检测到某进程执行了非法指令 | 终止进程并产生core文件
5  | SIGTRAP   | 该信号由断点指令或其他 `trap` 指令产生 | 终止进程并产生core文件
6  | SIGABRT   | 调用 `abort` 函数时产生该信号 | 终止进程并产生core文件
7  | SIGBUS    | 非法访问内存地址，包括内存对齐出错 | 终止进程并产生core文件
8  | SIGFPE    | 在发生致命的运算错误时发出。不仅包括浮点运算错误，还包括溢出及除数为0等所有的算法错误 | 终止进程并产生core文件
9  | SIGKILL   | 无条件终止进程。该信号不能被忽略，处理和阻塞 | 终止进程，可以杀死任何进程
10 | SIGUSR1   | 用户定义的信号。即程序员可以在程序中定义并使用该信号 | 终止进程
11 | SIGSEGV   | 指示进程进行了无效内存访问(段错误) | 终止进程并产生core文件
12 | SIGUSR2   | 另外一个用户自定义信号，程序员可以在程序中定义并使用该信号 | 终止进程
13 | SIGPIPE   | Broken pipe 向一个没有读端的管道写数据 | 终止进程
14 | SIGALRM   | 定时器超时，超时的时间由系统调用 `alarm` 设置 | 终止进程
15 | SIGTERM   | 程序结束信号，与 SIGKILL 不同的是，该信号可以被阻塞和终止。通常用来要示程序正常退出。执行shell命令Kill时，缺省产生这个信号 | 终止进程
16 | SIGSTKFLT | Linux 早期版本出现的信号，现仍保留向后兼容 | 终止进程
17 | SIGCHLD   | 子进程结束时(终止、收到 SIGSTOP 停止、处在停止态收到 SIGCONT 唤醒），父进程会收到这个信号 | 忽略这个信号
18 | SIGCONT   | 如果进程已停止，则使其继续运行 | 继续/忽略
19 | SIGSTOP   | 停止进程的执行。信号不能被忽略，处理和阻塞 | 为终止进程
20 | SIGTSTP   | 停止终端交互进程的运行。按下 `ctrl+z` 组合键时发出这个信号 | 暂停进程
21 | SIGTTIN   | 后台进程读终端控制台 | 暂停进程
22 | SIGTTOU   | 该信号类似于 SIGTTIN，在后台进程要向终端输出数据时发生 | 暂停进程
23 | SIGURG    | 套接字上有紧急数据时，向当前正在运行的进程发出些信号，报告有紧急数据到达。如网络带外数据到达 | 忽略该信号
24 | SIGXCPU   | 进程执行时间超过了分配给该进程的 CPU 时间，系统产生该信号并发送给该进程 | 终止进程
25 | SIGXFSZ   | 超过文件的最大长度设置 | 终止进程
26 | SIGVTALRM | 虚拟时钟超时时产生该信号。类似于 SIGALRM，但是该信号只计算该进程占用 CPU 的使用时间 | 终止进程
27 | SGIPROF   | 类似于 SIGVTALRM，它不仅包括该进程占用 CPU 时间还包括执行系统调用时间 | 终止进程
28 | SIGWINCH  | 窗口变化大小时发出 忽略该信号
29 | SIGIO     | 此信号向进程指示发出了一个异步 IO 事件 忽略该信号
30 | SIGPWR    | 关机 | 终止进程
31 | SIGSYS    | 无效的系统调用 | 终止进程并产生core文件
34~64 | SIGRTMIN~SIGRTMAX | LINUX 的实时信号，它们没有固定的含义（可以由用户自定义） | 终止进程

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

#include <unistd.h>
unsigned int alarm(unsigned int seconds);
/**
  * @brief:
  *  - 在定时指定秒数后向调用进程发送 SIGALRM 信号，默认会终止调用进程
  *  - 可以捕捉该信号并执行特定的定时任务，从而实现定时器的功能
  *  - 每个进程只能由一个 alarm 定时器，且 alarm 计时与进程的状态无关（自然定时法） 
  * @param: 
  *  - unsigned int seconds：定时的秒数，当为 0 时，不执行任何动作或者取消原来设置的定时器
  * @return:
  *  - 如果先前没有设置定时器，则返回 0；否则返回先前定时器剩余的秒数
  **/

#include <sys/time.h>
int setitimer(int which, const struct itimerval *new_val, struct itimerval *old_value);
/**
  * @brief:
  *  - 在延迟指定时间后向调用进程发送指定信号，之后按照指定间隔周期性地发送指定信号
  *  - 可以作为周期性的定时器，定时精度为微妙
  * @param: 
  *  - int which：设置定时器以何种时间标准进行定时
  *    - ITIMER_REAL：真实时间，到期发送 SIGALRM
  *    - ITIMER_VIRTUAL：进程的用户态所消耗的 CPU 时间，到期发送 SIGVTALRM
  *    - ITIMER_PROF：进程的用户态和内核态消耗的总的 CPU 时间（包括该进程下的所有线程），到期发送 SIGPROF
  *    - 一个进程只能拥有以上三种类型定时器中的一种
  *  - const struct itimerval *new_val：设置定时器的属性
       struct itimerval
       {
         struct timeval it_interval; // 定时周期，若为 0，则为非周期定时器
         struct timeval it_value;    // 定时器超时时间，首次超时后被重置为 it_interval；若为 0，则关闭定时器
       };
       struct timeval
       {
         time_t tv_sec;       //  秒数
         suseconds_t tv_usec; //  微秒
       };
  *  - struct itimerval *old_value：获取先前定时器的属性
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置错误号
  **/

int getitimer(int which, struct itimerval *curr_value);
/**
  * @brief:
  *  - 获取定时器的属性
  * @param: 
  * @return:
  *  - 成功：0
  *  - 失败：-1，并设置 errno
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

### 4.4.9. 应用范例

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

### 4.5.4. 应用范例

## 4.6. 守护进程

### 4.6.1. 终端

- 在 UNIX 系统中，用户通过终端登录系统后得到一个 shell 进程，这个终端成为 shell 进程的控制终端；
- 进程中，控制终端是保存在 PCB 中的信息，而 `fork()` 会复制 PCB 中的信息，因此由 shell 进程启动的其它进程的控制终端也是这个终端；
- 默认情况下（没有重定向），每个进程的标准输入、标准输出和标准错误输出都指向控制终端，进程从标准输入读也就是读用户的键盘输入，进程往标准输出或标准错误输出写也就是输出到显示器上；
- 在控制终端输入一些特殊的控制键可以给前台进程发信号，例如 `Ctrl + C` 会产生 `SIGINT` 信号， `Ctrl + \` 会产生 `SIGQUIT` 信号；
- `echo $$`：显示当前 shell 进程的进程号；

### 4.6.2. 进程组

- 进程组和会话在进程之间形成了一种两级层次关系：进程组是一组相关进程的集合，会话是一组相关进程组的集合。进程组和会话是为支持 shell 作业控制而定义的抽象概念，用户通过 shell 能够交互式地在前台或后台运行命令；
- 进行组由一个或多个共享同一进程组标识符（PGID）的进程组成。一个进程组拥有一个进程组首进程，该进程是创建该组的进程，其进程 ID 为该进程组的 ID，新进程会继承其父进程所属的进程组 ID；
- 进程组拥有一个生命周期，其开始时间为首进程创建组的时刻，结束时间为最后一个成员进程退出组的时刻。一个进程可能会因为终止而退出进程组，也可能会因为加入了另外一个进程组而退出进程组。进程组首进程无需是最后一个离开进程组的成员；

### 4.6.3. 会话

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

### 4.6.4. 进程组、会话操作函数

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

### 4.6.5. 守护进程

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

### 4.6.6. 应用范例

#### 4.6.6.1. 每 1s 向磁盘文件打印当前系统时间的守护进程

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