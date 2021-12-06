- [1. 线程概述](#1-线程概述)
  - [1.1. 线程和进程的区别](#11-线程和进程的区别)
  - [1.2. 线程之间共享和非共享资源](#12-线程之间共享和非共享资源)
- [2. 线程控制](#2-线程控制)
  - [2.1. 线程创建](#21-线程创建)
  - [2.2. 线程终止](#22-线程终止)
  - [2.3. 线程连接](#23-线程连接)
  - [2.4. 线程分离](#24-线程分离)
  - [2.5. 线程取消](#25-线程取消)
  - [2.6. 其他线程函数](#26-其他线程函数)
  - [2.7. 线程属性](#27-线程属性)
  - [2.8. 应用范例](#28-应用范例)
- [3. 线程同步](#3-线程同步)
  - [3.1. 线程同步的基本概念](#31-线程同步的基本概念)
  - [3.2. 互斥量（锁）](#32-互斥量锁)
    - [3.2.1. 互斥量的基本概念](#321-互斥量的基本概念)
    - [3.2.2. 互斥量相关操作函数](#322-互斥量相关操作函数)
  - [3.3. 死锁](#33-死锁)
  - [3.4. 读写锁](#34-读写锁)
    - [3.4.1. 读写锁的基本概念](#341-读写锁的基本概念)
    - [3.4.2. 读写锁相关操作函数](#342-读写锁相关操作函数)
  - [3.5. 自旋锁](#35-自旋锁)
  - [3.6. 条件变量](#36-条件变量)
  - [3.7. 信号量](#37-信号量)
  - [3.8. 生产者消费者模型](#38-生产者消费者模型)

# 1. 线程概述

## 1.1. 线程和进程的区别

- 进程是 CPU 分配资源的最小单位，线程是操作系统调度执行的最小单位。与进程（process）类似，线程（thread）是允许应用程序并发执行多个任务的一种机制，一个进程可以包含多个线程
- 线程是轻量级的进程（LWP：Light Weight Process），Linux 环境下查看指定进程的 LWP 号：`ps –Lf pid`
- 同一个进程中的所有线程具有相同的虚拟地址空间，且它们共享代码段（.text）、初始化数据段（.bss）、未初始化数据段（.data）和堆内存段，可以方便地利用全局变量来共享信息
- 不同的进程具有独立的虚拟地址空间，因此进程间的信息难以共享，必须采用一些进程间通信方式（信号、管道（匿名、FIFO）、消息队列、内存映射、共享内存、Socket）来在进程间进行信息交换
- 线程相对于进程来说其创建和切换效率更高。调用 `fork()` 来创建进程的代价相对较高，即便利用写时复制技术，仍然需要复制诸如内存页表和文件描述符表之类的多种进程属性，这意味着 `fork()` 调用在时间上的开销依然不菲。创建线程比创建进程通常要快 10 倍甚至更多，因为线程间是共享虚拟地址空间的，无需采用写时复制来复制内存，也无需复制页表

## 1.2. 线程之间共享和非共享资源

- **共享资源**
  - 进程 ID 、父进程 ID、进程组 ID 、会话 ID、用户 ID 和用户组 ID
  - 文件描述符表
  - 信号处理方式（SIG_IDN、SIG_DFL 或自定义的信号处理函数）
  - 文件系统的相关信息：文件权限掩码（umask）、当前工作目录
  - 虚拟地址空间（除栈、.text）
</br>

- **非共享资源**
  - 线程 ID
  - 信号掩码
  - 上下文，包括各种寄存器的值、程序计数器和栈指针
  - error 变量
  - 实时调度策略和优先级
  - 栈，本地变量和函数的调用链接信息

# 2. 线程控制

- 本节描述的是 Posix 线程库，称为 Posix thread 或 pthread。在 Linux 上线程函数位于 libpthread 共享库中，需要添加头文件 `#include <pthread.h>` 并在编译时加上 `-lpthread` 或 `-pthread` 选项
- 查看当前 pthread 库版本：`getconf GNU_LIBPTHREAD_VERSION`

## 2.1. 线程创建

```cpp {class=line-numbers}
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
/**
   * @brief:
   *  - 创建一个子线程，启动函数为 start_routine()。新线程将在以下的几种情况下终止：
   *    - 子线程调用 pthread_exit()
   *    - start_routine() 函数返回，等效于 pthread_exit()
   *    - 被取消（pthread_cancel）
   *    - 主线程在 main 函数中返回或者进程中的任一进程调用 exit()，这将导致该进程中的所有线程终止
   *  - 新线程继承创建线程的信号掩码 pthread_sigmask()；新线程的未决信号集为空 sigpending()；新线程不继承创建线程的备用信号堆栈 sigaltstack()
   *  - 新线程的默认状态为连接态，此时需要使用 pthread_join() 来连接新线程以在新线程结束后回收新线程的资源；可以将线程设为分离态，此时线程终止时将自动回收资源
   * @param: 
   *  - thread：传出参数，子线程创建成功后，子线程的 id 号存储在 thread 所指向的内存中
   *  - attr：设置子线程的属性，一般采用默认值 NULL
   *  - start_routine：函数指针，子线程的启动函数
   *  - arg：用于给子线程的启动函数传递参数
   * @return:
   *  - 成功：0
   *  - 失败：错误号，获取错误号信息：char * strerror(int errnum)
   **/
```

## 2.2. 线程终止

```cpp {class=line-numbers}
void pthread_exit(void *retval);
/**
   * @brief:
   *  - 终止调用线程，通过 retval 来返回相关的值
   *  - 当线程的 start_routine() 返回时等效于 pthread_exit()
   * @param: 
   *  - retval：线程退出返回值，若为 joinable 则可通过 pthread_join() 来获取该返回值。注意 retval 所指向的内存不应该在线程结束后就被回收
   * @return:
   **/
```

## 2.3. 线程连接

```cpp {class=line-numbers}
int pthread_join(pthread_t thread, void **retval);
/**
   * @brief:
   *  - 等待 thread 所指定的线程终止，回收连接线程的资源
   *  - 阻塞调用，当所等待的线程终止时函数才返回，所等待的线程必须是 joinable 的
   *  - 如果多个线程同时连接所指定的线程，则结果未定义；如果调用线程被取消，则所指定线程将保持 joinable
   * @param: 
   *  - thread：需要回收的线程 ID
   *  - retval：接收所指定线程退出时的返回值，如果所指定线程被取消，则为线程退出状态被设置为 PTHREAD_CANCELED
   * @return:
   *  - 成功：0
   *  - 失败：错误号，获取错误号信息：char * strerror(int errnum)
   **/
```

## 2.4. 线程分离

```cpp {class=line-numbers}
int pthread_detach(pthread_t thread);
/**
   * @brief:
   *  - 分离一个指定的线程，被分离的线程在终止时会自动释放资源返回给系统
   *  - 不能连接一个 detached 的线程，会报错；不能将一个 detached 的线程设置为 joinable
   *  - 重复分离一个 detached 的线程会带来未定义的行为
   * @param: 
   *  - thread：需要设置为 detached 的线程 ID
   * @return:
   *  - 成功：0
   *  - 失败：错误号，获取错误号信息：char * strerror(int errnum)
   **/
```

## 2.5. 线程取消

```cpp {class=line-numbers}
int pthread_cancel(pthread_t thread);
/**
   * @brief:
   *  - 向指定的线程发送一个取消请求，指定线程是否取消取决于它的取消状态和取消类型
   *  - 可通过 pthread_setcancelstate() 设置 cancelability state 为 enabled 或 disabled
   *    - 若为 disabled，则取消请求将排队等待知道 enabled
   *    - 若为 enabled，则 cancellation type 确定何时进行取消操作
   *  - 可通过 pthread_setcanceltype() 设置 cancellation type 为 asynchronous 或 deferred（新线程默认为该类型）
   *    - 若为 asynchronous 则可在任意时刻进行取消操作，一般为立即执行，但是系统并不保证立即执行
   *    - 若为 deferred 则延期到目标线程的取消点才执行。取消点：系统规定好的一些系统调用，可以粗略的理解为从用户区到内核区的切换，这个位置称之为取消点
   * @param: 
   *  - thread：要取消的线程的 ID
   * @return:
   *  - 成功：0
   *  - 失败：错误号，获取错误号信息：char * strerror(int errnum)
   **/
```

## 2.6. 其他线程函数

```cpp {class=line-numbers}
pthread_t pthread_self(void);
/**
   * @brief:
   *  - 获取线程自身 ID
   * @param: 
   * @return:
   *  - 返回调用线程的 ID
   **/

int pthread_equal(pthread_t t1, pthread_t t2);
/**
   * @brief:
   *  - 比较两个线程 ID
   * @param: 
   * @return:
   *  - 相等返回非 0，不等返回 0
   **/

```

## 2.7. 线程属性

```cpp {class=line-numbers}
pthread_attr_t
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);
int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
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

## 2.8. 应用范例

```cpp {class=line-numbers}
/**
 * @description:
 *  - 取消线程相关操作
 **/

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define handle_error_en(en, msg) \
  do                             \
  {                              \
    errno = en;                  \
    perror(msg);                 \
    exit(EXIT_FAILURE);          \
  } while (0)

static void *thread_func(void *ignored_argument)
{
  int s;

  /* Disable cancellation for a while, so that we don't immediately react to a cancellation request */
  s = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
  if (s != 0)
    handle_error_en(s, "pthread_setcancelstate");
  printf("thread_func(): started; cancellation disabled\n");

  sleep(5);
  printf("thread_func(): about to enable cancellation\n");
  s = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  if (s != 0)
    handle_error_en(s, "pthread_setcancelstate");

  /* sleep() is a cancellation point */
  sleep(1000); /* Should get canceled while we sleep */

  /* Should never get here */
  printf("thread_func(): not canceled!\n");
  return NULL;
}

int main(void)
{
  pthread_t thr;
  void *res;
  int s;

  /* Start a thread and then send it a cancellation request */
  s = pthread_create(&thr, NULL, &thread_func, NULL);
  if (s != 0) handle_error_en(s, "pthread_create");

  sleep(2); /* Give thread a chance to get started */

  printf("main(): sending cancellation request\n");
  s = pthread_cancel(thr);
  if (s != 0) handle_error_en(s, "pthread_cancel");

  /* Join with thread to see what its exit status was */
  s = pthread_join(thr, &res);
  if (s != 0) handle_error_en(s, "pthread_join");

  if (res == PTHREAD_CANCELED)
    printf("main(): thread was canceled\n");
  else
    printf("main(): thread wasn't canceled (shouldn't happen!)\n");
  
  exit(EXIT_SUCCESS);
}
```

# 3. 线程同步

## 3.1. 线程同步的基本概念

- 线程的主要优势在于，能够通过全局变量来共享信息。不过，这种便捷的共享是有代价的：必须确保多个线程不会同时修改同一变量，或者某一线程不会读取正在由其他线程修改的变量
- **临界区**是指访问某一共享资源的代码片段，并且这段代码的执行应为原子操作，也就是同时访问同一共享资源的其他线程不应中断该片段的执行
- 线程同步：即当有一个线程在对内存进行操作时，其他线程都不可以对这个内存地址进行操作，直到该线程完成操作，其他线程才能对该内存地址进行操作，而其他线程则处于等待状态

## 3.2. 互斥量（锁）

### 3.2.1. 互斥量的基本概念

### 3.2.2. 互斥量相关操作函数

```cpp {class=line-numbers}
pthread_mutex_t
int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
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

## 3.3. 死锁

## 3.4. 读写锁

### 3.4.1. 读写锁的基本概念

### 3.4.2. 读写锁相关操作函数

```cpp {class=line-numbers}
pthread_rwlock_t
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr);
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
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
## 3.5. 自旋锁

## 3.6. 条件变量

```cpp {class=line-numbers}
pthread_cond_t
int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
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

## 3.7. 信号量

```cpp {class=line-numbers}
sem_t
int sem_init(sem_t *sem, int pshared, unsigned int value);
int sem_destroy(sem_t *sem);
int sem_wait(sem_t *sem);
int sem_trywait(sem_t *sem);
int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
int sem_post(sem_t *sem);
int sem_getvalue(sem_t *sem, int *sval);
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

## 3.8. 生产者消费者模型

```cpp {class=line-numbers}

```