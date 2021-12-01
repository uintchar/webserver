/**
 * @copyright: uintchar
 * @version: v1.0
 * @author: uintchar
 * @date: 2021-12-01
 * @description:
 *  - first
 *  - second
 * @revision:
 *  - last revised by uintchar on 2021-12-01
 *  - last revised by *** on ***
 **/

// #include <iostream>

// #include <stdio.h>

// #include "test.h"

// int main()
// {
//   std::cout << "main start" << std::endl;

//   testFunc1();

//   std::cout << "main end" << std::endl;

//   return 0;
// }

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
      fgets(wbuf, 1024, stdin);
      write(pipefd[1], wbuf, strlen(wbuf) + 1);
      if (strcmp(wbuf, "quit\n") == 0)
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
      if (strcmp(rbuf, "quit\n") == 0)
        break;
      memset(rbuf, 0, 1024);
    }

    close(pipefd[0]);
    exit(EXIT_SUCCESS);
  }

  return 0;
}