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
    - [4.2.1. 有名管道的特点](#421-有名管道的特点)
    - [4.2.2. 有名管道的使用](#422-有名管道的使用)
    - [4.2.3. 使用范例](#423-使用范例)
  - [4.3. 内存映射](#43-内存映射)
    - [4.3.1. 内存映射相关系统调用](#431-内存映射相关系统调用)
    - [4.3.2. 使用范例](#432-使用范例)
  - [4.4. 信号](#44-信号)
    - [4.4.1. 信号的概念](#441-信号的概念)
    - [4.4.2. Linux 信号一览](#442-linux-信号一览)
    - [4.4.3. 信号的 5 种默认处理动作](#443-信号的-5-种默认处理动作)
    - [4.4.4. 信号相关函数](#444-信号相关函数)
    - [4.4.5. 信号捕捉函数](#445-信号捕捉函数)
    - [4.4.6. 信号集](#446-信号集)
    - [4.4.7. 阻塞信号集和未决信号集](#447-阻塞信号集和未决信号集)
    - [4.4.8. 信号集相关函数](#448-信号集相关函数)
    - [4.4.9. 内核实现信号捕捉的过程](#449-内核实现信号捕捉的过程)
    - [4.4.10. SIGCHILD 信号](#4410-sigchild-信号)
  - [4.5. 共享内存](#45-共享内存)
    - [4.5.1. 共享内存的概念](#451-共享内存的概念)
    - [4.5.2. 共享内存的使用步骤](#452-共享内存的使用步骤)
    - [4.5.3. 共享内存操作函数](#453-共享内存操作函数)
    - [4.5.4. 使用范例](#454-使用范例)
  - [4.6. 守护进程](#46-守护进程)
    - [4.6.1. 终端](#461-终端)
    - [4.6.2. 进程组](#462-进程组)
    - [4.6.3. 会话](#463-会话)
    - [4.6.4. 进程组、会话操作函数](#464-进程组会话操作函数)
    - [4.6.5. 守护进程](#465-守护进程)

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

### 4.3.2. 使用范例

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

### 4.4.2. Linux 信号一览

### 4.4.3. 信号的 5 种默认处理动作

- 生成 core 文件 `ulimit -c new_size`

### 4.4.4. 信号相关函数

- `kill`

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
- `raise`

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
- `abort`

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

- `alarm`

  ```cpp {class=line-numbers}
  /**
    * @brief:
    *  - 非阻塞
    * @param: 
    *  - 
    *  - 
    * @return:
    *  - 成功：
    *  - 失败：
    **/
  ```

- `setitimer`

  ```cpp {class=line-numbers}
  /**
    * @brief:
    *  - 非阻塞
    * @param: 
    *  - 
    *  - 
    * @return:
    *  - 成功：
    *  - 失败：
    **/
  ```

### 4.4.5. 信号捕捉函数

- `signal`

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

- `sigaction`

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

### 4.4.6. 信号集

### 4.4.7. 阻塞信号集和未决信号集

### 4.4.8. 信号集相关函数

```cpp {class=line-numbers}
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
int sigdelset(sigset_t *set, int signum);
int sigismember(const sigset_t *set, int signum);
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
int sigpending(sigset_t *set);
```

- 后台进程与前台进程

### 4.4.9. 内核实现信号捕捉的过程

### 4.4.10. SIGCHILD 信号

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

### 4.5.4. 使用范例

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
  ![进程组-会话-控制终端间的关系](./code/webserver/note/figure/进程组_会话_控制终端间的关系.PNG)

### 4.6.4. 进程组、会话操作函数

```cpp {class=line-numbers}
#include <sys/types.h>
#include <unistd.h>

int setpgid(pid_t pid, pid_t pgid);
pid_t getpgid(pid_t pid);

pid_t getpgrp(void);                 /* POSIX.1 version */
pid_t getpgrp(pid_t pid);            /* BSD version */

int setpgrp(void);                   /* System V version */
int setpgrp(pid_t pid, pid_t pgid);  /* BSD version */
```

### 4.6.5. 守护进程