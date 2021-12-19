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
  - [2.8. 应用示例](#28-应用示例)
- [3. 线程同步](#3-线程同步)
  - [3.1. 线程同步的基本概念](#31-线程同步的基本概念)
  - [3.2. 互斥锁](#32-互斥锁)
    - [3.2.1. 互斥锁基本概念](#321-互斥锁基本概念)
    - [3.2.2. 互斥锁相关函数](#322-互斥锁相关函数)
    - [3.2.3. 互斥锁应用示例](#323-互斥锁应用示例)
  - [3.3. 死锁](#33-死锁)
  - [3.4. 读写锁](#34-读写锁)
    - [3.4.1. 读写锁基本概念](#341-读写锁基本概念)
    - [3.4.2. 读写锁相关函数](#342-读写锁相关函数)
    - [3.4.3. 读写锁应用示例](#343-读写锁应用示例)
  - [3.5. 自旋锁](#35-自旋锁)
    - [3.5.1. 自旋锁基本概念](#351-自旋锁基本概念)
    - [3.5.2. 自旋锁相关函数](#352-自旋锁相关函数)
    - [3.5.3. 自旋锁应用示例](#353-自旋锁应用示例)
  - [3.6. 条件变量](#36-条件变量)
    - [3.6.1. 条件变量基本概念](#361-条件变量基本概念)
    - [3.6.2. 条件变量相关函数](#362-条件变量相关函数)
    - [3.6.3. 条件变量应用示例](#363-条件变量应用示例)
  - [3.7. 信号量](#37-信号量)
    - [3.7.1. 信号量基本概念](#371-信号量基本概念)
    - [3.7.2. 信号量相关函数](#372-信号量相关函数)
    - [3.7.3. 信号量应用示例](#373-信号量应用示例)
  - [3.8. 线程和信号](#38-线程和信号)
    - [3.8.1. 信号模型如何映射到线程中](#381-信号模型如何映射到线程中)
    - [3.8.2. 线程信号掩码：pthread_sigmask()](#382-线程信号掩码pthread_sigmask)
    - [3.8.3. 向线程发送信号](#383-向线程发送信号)
    - [3.8.4. 妥善处理异步信号](#384-妥善处理异步信号)
    - [3.8.5. 应用示例](#385-应用示例)
  - [3.9. 生产者消费者模型](#39-生产者消费者模型)

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
 * @description:
 *  - 线程属性相关操作
 **/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *callback(void *arg)
{
  printf("chid thread id : %ld\n", pthread_self());
  return NULL;
}

int main()
{

  // 创建一个线程属性变量
  pthread_attr_t attr;
  // 初始化属性变量
  pthread_attr_init(&attr);

  // 设置属性
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  // 创建一个子线程
  pthread_t tid;

  int ret = pthread_create(&tid, &attr, callback, NULL);
  if (ret != 0)
  {
    char *errstr = strerror(ret);
    printf("error1 : %s\n", errstr);
  }

  // 获取线程的栈的大小
  size_t size;
  pthread_attr_getstacksize(&attr, &size);
  printf("thread stack size : %ld\n", size);

  // 输出主线程和子线程的id
  printf("tid : %ld, main thread id : %ld\n", tid, pthread_self());

  // 释放线程属性资源
  pthread_attr_destroy(&attr);

  pthread_exit(NULL);

  return 0;
}
```

## 2.8. 应用示例

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

## 3.2. 互斥锁

### 3.2.1. 互斥锁基本概念

- 为避免线程更新共享变量时出现问题，可以使用互斥量（mutex 是 mutual exclusion 的缩写）来确保同时仅有一个线程可以访问某项共享资源。可以使用互斥量来保证对任意共享资源的原子访问
- 互斥量有两种状态：已锁定（locked）和未锁定（unlocked）。任何时候，至多只有一个线程可以锁定该互斥量。试图对已经锁定的某一互斥量再次加锁，将可能阻塞线程或者报错失败，具体取决于加锁时使用的方法
- 一旦线程锁定互斥量，随即成为该互斥量的所有者，只有所有者才能给互斥量解锁。一般情况下，对每一共享资源（可能由多个相关变量组成）会使用不同的互斥量，每一线程在访问同一资源时将采用如下协议：
  - 针对共享资源锁定互斥量
  - 访问共享资源
  - 对互斥量解锁

### 3.2.2. 互斥锁相关函数

```cpp {class=line-numbers}
#include <pthread.h>

/* 静态分配初始化 */
pthread_mutex_t fastmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t recmutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
pthread_mutex_t errchkmutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;

/* 动态分配初始化 */
int pthread_mutexattr_init(pthread_mutexattr_t *attr); /* 总是返回 0 */
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr); /* 总是返回 0 */
int pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *kind); /* 总是返回 0 */
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int kind); /* 成功返回 0，失败返回错误号 */
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr); /* 总是返回 0 */
int pthread_mutex_destroy(pthread_mutex_t *mutex); /* 成功返回 0，失败返回错误号 */

/* 加锁和解锁操作 */
int pthread_mutex_lock(pthread_mutex_t *mutex);
/**
   * @brief:
   *  - 尝试锁定给定的一个锁变量，若该锁变量之前未锁定，则调用线程将成功锁定该锁变量并立即返回
   *  - 若锁变量先前已被其它线程锁定，则调用线程被阻塞直到该锁变量被解锁‘
   *  - 若锁变量先前已被自己锁定，则其处理行为取决于锁的属性，LinuxThread 支持的锁的属性有以下几种：
   *    - PTHREAD_MUTEX_FAST_NP：将调用线程挂起，造成死锁
   *    - PTHREAD_MUTEX_RECURSIVE_NP：立即返回错误码 EDEADLK
   *    - PTHREAD_MUTEX_ERRORCHECK_NP：立即返回成功码，并记录对该锁变量的加锁次数，拥有锁的线程必须调用相同次数的 pthread_mutex_unlock() 才能解锁该锁变量
   *    - 默认情况下为 PTHREAD_MUTEX_FAST_NP，NP 后缀表示不可扩展
   * @param:
   *  - mutex：尝试锁定的锁变量
   * @return:
   *  - 成功返回 0，失败返回非 0 错误号
   **/

int pthread_mutex_trylock(pthread_mutex_t *mutex);
/**
   * @brief:
   *  - 尝试锁定给定的一个锁变量，但是其为非阻塞调用
   *  - 如果锁变量先前已被其它线程锁定（或者锁变量属性为 "fast" 时被先前已被自身锁定），其立即返回错误号 EBUSY
   * @param:
   *  - mutex：尝试锁定的锁变量
   * @return:
   *  - 成功返回 0，失败返回非 0 错误号
   **/

int pthread_mutex_unlock(pthread_mutex_t *mutex);
/**
   * @brief:
   *  - 解锁给定的锁变量 mutex，其对不同属性的锁变量具有不同的操作，具体参考 man 文档
   * @param:
   *  - mutex
   * @return:
   *  - 成功返回 0，失败返回非 0 错误号
   **/
```

### 3.2.3. 互斥锁应用示例

## 3.3. 死锁

- 有时，一个线程需要同时访问两个或更多不同的共享资源，而每个资源又都由不同的互斥量管理。当超过一个线程加锁同一组互斥量时，就有可能发生死锁
- 两个或两个以上的进程在执行过程中，因争夺共享资源而造成的一种互相等待的现象
- 若无外力作用，它们都将无法推进下去。此时称系统处于死锁状态或系统产生了死锁
- 死锁的几种场景：
  - 忘记释放锁
  - 重复加锁
  - 多线程多锁，抢占锁资源

  [!死锁示意图](webserver/note/figure/死锁示意图.JPG)

## 3.4. 读写锁

### 3.4.1. 读写锁基本概念

- 当有一个线程已经持有互斥锁时，互斥锁将所有试图进入临界区的线程都阻塞住。但是考虑一种情形，当前持有互斥锁的线程只是要读访问共享资源，而同时有其它几个线程也想读取这个共享资源，但是由于互斥锁的排它性，所有其它线程都无法获取锁，也就无法读访问共享资源了，但是实际上多个线程同时读访问共享资源并不会导致问题
- 在对数据的读写操作中，更多的是读操作，写操作较少，例如对数据库数据的读写应用
- 为了满足当前能够允许多个读出，但只允许一个写入的需求，线程提供了读写锁来实现
- 读写锁的特点：
  - 如果有其它线程读数据，则允许其它线程执行读操作，但不允许写操作
  - 如果有其它线程写数据，则其它线程都不允许读、写操作
  - 写是独占的，写的优先级高。

### 3.4.2. 读写锁相关函数

```cpp {class=line-numbers}
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

### 3.4.3. 读写锁应用示例

## 3.5. 自旋锁

### 3.5.1. 自旋锁基本概念

### 3.5.2. 自旋锁相关函数

```cpp {class=line-numbers}
int pthread_spin_init(pthread_spinlock_t *lock, int pshared);
int pthread_spin_destroy(pthread_spinlock_t *lock);
int pthread_spin_lock(pthread_spinlock_t *lock);
int pthread_spin_trylock(pthread_spinlock_t *lock);
int pthread_spin_unlock(pthread_spinlock_t *lock);
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

### 3.5.3. 自旋锁应用示例

## 3.6. 条件变量

### 3.6.1. 条件变量基本概念

### 3.6.2. 条件变量相关函数

### 3.6.3. 条件变量应用示例

```cpp {class=line-numbers}
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

### 3.7.1. 信号量基本概念

### 3.7.2. 信号量相关函数

```cpp {class=line-numbers}
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

### 3.7.3. 信号量应用示例

## 3.8. 线程和信号

UNIX 信号模型是基于 UNIX 进程模型而设计的， 问世比 Pthreads 要早几十年。 自然而然，信号与线程模型之间存在一些明显的冲突。主要是因为，一方面，针对单线程进程要保持传
统的信号语义（Pthreads 不应改变传统进程的信号语义），与此同时，又需要开发出适用于多线程进程环境的新信号模型。信号与线程模型之间的差异意味着，将二者结合使用，将会非常复杂，应尽可能加以避免。尽管如此，有的时候还是必须在多线程程序中处理信号问题。

### 3.8.1. 信号模型如何映射到线程中

- 信号动作属于进程层面。如果某进程的任一线程收到任何未经（特殊）处理的信号，且其缺省动作为 stop 或 terminate，那么将停止或者终止该进程的所有线程。
- 信号处置属于进程层面，进程中的所有线程共享对每个信号的处置设置。如果某一线程使用函数 `sigaction()` 为某类信号（比如，SIGINT）创建了处理函数，那么当收到 SIGINT 时，任何线程都可以去调用该处理函数（针对一次信号到达任选一个线程调用一次信号处理器函数）。与之类似，如果将对信号的处置设置为忽略（ignore），那么所有线程都会忽略该信号。注意：如果在不同线程中对同一个信号指定不同的信号处理器函数或者在同一线程对同一信号两次指定不同的信号处理器函数，则进程针对该信号的处置以最新一次设置为准。
- 信号的发送既可针对整个进程，也可针对某个特定线程。满足如下三者之一的信号当属面向线程的。
  - 信号的产生源于线程上下文中对特定硬件指令的执行（例如： SIGBUS、 SIGFPE、 SIGILL 和 SIGSEGV）。
  - 当线程试图对已断开的（broken pipe）管道进行写操作时所产生的 SIGPIPE 信号。
  - 由函数 `pthread_kill()` 或 `pthread_sigqueue()` 所发出的信号，这些函数允许线程向同一进程下的其他线程发送信号。
  - 由其他机制产生的所有信号都是面向进程的。例如，其他进程通过调用 `kill()` 或者 `sigqueue()` 所发送的信号；用户键入特殊的终端字符所产生的信号，诸如 SIGINT和 SIGTSTP； 还有一些信号由软件事件产生， 例如终端窗口大小的调整（SIGWINCH）或者定时器到期（例如，SIGALRM）。
- 当多线程程序收到一个信号，且该进程已然为此信号创建了信号处理程序时，内核会任选一条线程来接收这一信号，并在该线程中调用信号处理程序对其进行处理。这种行为与信号的原始语义保持了一致。让进程针对单个信号重复处理多次是没有意义的。
- 信号掩码（mask）是针对每个线程而言。对于多线程程序来说，并不存在一个作用于整个进程范围的信号掩码，可以管理所有线程。使用 Pthreads API 所定义的函数 `pthread_sigmask()`，各线程可独立阻止或放行各种信号。通过操作每个线程的信号掩码，应用程序可以控制哪些线程可以处理进程收到的信号。
- 针对为整个进程所挂起（pending）的信号，以及为每条线程所挂起的信号，内核都分别维护有记录。调用函数 `sigpending()` 会返回为整个进程和当前线程所挂起信号的并集。在新创建的线程中，每线程的挂起信号集合初始时为空。可将一个针对线程的信号仅向目标线程投送。如果该信号遭线程阻塞，那么它会一直保持挂起，直至线程将其放行（或者线程终止）。
- 如果信号处理程序中断了对 `pthread_mutex_lock()` 的调用，那么该调用总是会自动重新开始。如果一个信号处理函数中断了对 `pthread_cond_wait()` 的调用，则该调用要么自动重新开始（Linux 就是如此），要么返回 0，表示遭遇了假唤醒（此时，设计良好的应用程序会重新检查相应的判断条件并重新发起调用）。 SUSv3 对这两个函数的行为要求与此处的描述一致。
- 备选信号栈是每线程特有的。新创建的线程并不从创建者处继承备选信号栈。

### 3.8.2. 线程信号掩码：pthread_sigmask()

```cpp {class=line-numbers}
#include <signal.h>

int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset);
/**
 * @brief:
 *  - 刚创建的新线程会从其创建者处继承信号掩码的一份拷贝。线程可以使用 pthread_sigmask() 来改变或/并获取当前的信号掩码
 *  - 与 sigprocmask()的用法完全相同，将自定义信号集中的数据设置到内核中（设置阻塞，解除阻塞，替换），系统将忽略试图阻塞 SIGKILL 和 SIGSTOP 信号的请求
 *  - 如果想获取信号掩码而又对其不作改动，那么可将 set 参数指定为空，这时将忽略 how 参数
 *  - SUSv3 规定，如果解除了对某个等待信号的锁定，那么会立刻将该信号传递给进程（在 sigprocmask() 调用返回之前）
 *  - SUSv3 特别指出在多线程程序中使用 sigprocmask() 结果是未定义的，也无法保证程序的可移植性
 * @param: 
 *  - how：
 *    - SIG_BLOCK：将用户设置的阻塞信号集添加到内核中，内核中原来的数据不变。假设内核中默认的阻塞信号集是 mask，mask | set
 *    - SIG_UNBLOCK：根据用户设置的数据，对内核中的数据进行解除阻塞 mask &= ~set
 *    - SIG_SETMASK：覆盖内核中原来的值
 *  - set：要进行设置的信号集
 *  - oldset：传出参数，获得内核中原先的线程信号掩码（阻塞信号集）
 * @return:
 *  - 成功：0
 *  - 失败：大于 0 的错误号
 **/
```

### 3.8.3. 向线程发送信号

```cpp {class=line-numbers}
#include <signal.h>

int pthread_kill(pthread_t thread, int sig);
/**
 * @brief:
 *  - 向同一进程内的指定线程 thread 发送信号 sig
 *  - 只有指定的目标线程才能处理该信号（仅指发送给 thread 的 sig），假如目标线程阻塞了该信号，则直到目标线程解除该信号的阻塞后才会处理该信号
 *  - 针对该信号 sig 的信号处理器函数可以在其他线程内指定
 * @param: 
 *  - thread：目标线程 ID
 *  - sig：要发送的信号编号
 * @return:
 *  - 成功：0
 *  - 失败：大于 0 的错误号 
 **/
```

```cpp {class=line-numbers}
#include <signal.h>
#include <pthread.h>

int pthread_sigqueue(pthread_t thread, int sig, const union sigval value);
/**
 * @brief:
 *  - 向同一进程内的指定线程 thread 发送携带数据的信号 sig（
 *  - 发送给 thread 的信号仅能由 thread 进行处理
 * @param: 
 *  - thread：目标线程 ID
 *  - sig：要发送的信号编号
 *  - value：信号的伴随数据
 * @return:
 *  - 成功：0
 *  - 失败：大于 0 的错误号 
 **/
```

### 3.8.4. 妥善处理异步信号

- 没有任何 Pthreads API 属于异步信号安全（async-signal-safe）函数，均无法在信号处理函数中安全加以调用。因为这些原因，所以当多线程应用程序必须处理异步产生的信
号时，通常不应该将信号处理函数作为接收信号到达的通知机制。相反，推荐的方法如下。
  - 所有线程都阻塞进程可能接收的所有异步信号。最简单的方法是，在创建任何其他线程之前，由主线程阻塞这些信号。后续创建的每个线程都会继承主线程信号掩码的一份拷贝。
  - 再创建一个专用线程，调用函数 `sigwaitinfo()`、 `sigtimedwait()` 或 `sigwait()` 来接收收到的信号。 
- 这一方法的优势在于，同步接收异步产生的信号。当接收到信号时，专有线程可以安全地修改共享变量（在互斥量的保护之下），并可调用并非异步信号安全（non-async-signal-safe）的函数。也可以就条件变量发出信号，并采用其他线程或进程的通讯及同步机制。
- 函数 `sigwait()` 会等待 `set` 所指信号集合中任一信号的到达，接收该信号，且在参数 `sig` 中将其返回。

```cpp {class=line-numbers}
#include <signal.h>

int sigwait(const sigset_t *set, int *sig);
/**
 * @brief:
 *  - 阻塞调用线程知道 set 所指信号集合中任一信号的到达，并接收该信号在参数 sig 中将其返回
 *  - 将对 set 中信号集的阻塞与调用 sigwaitinfo() 结合起来，这当属明智之举。即便某一信号遭到阻塞，仍然可以使用 sigwaitinfo() 来获取等待信号
 *  - 调用 sigwait() 而不阻塞 set 中的信号将导致不可预知的行为（其行为未定义）
 *  - 如有多个线程在调用 sigwait() 等待同一信号， 那么当信号到达时只有一个线程会实际接收到，也无法确定收到信号的会是哪条线程
 * @param: 
 *  - set：指定要等待的信号集合
 *  - sig：传出参数，接收到达的信号
 * @return:
 *  - 成功：0
 *  - 失败：大于 0 的错误号
 **/
```

### 3.8.5. 应用示例

```cpp {class=line-numbers}
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

void sig_handle1(int signum)
{
  if (signum == SIGALRM)
  {
    printf("********************sig_handle1 --- SIGALRM:%d\n", signum);
  }
  else if (signum == SIGUSR1)
  {
    printf("********************sig_handle1 --- SIGUSR1:%d\n", signum);
  }
  else if (signum == SIGUSR2)
  {
    printf("********************sig_handle2 --- SIGUSR2:%d\n", signum);
  }
}

void sig_handle2(int signum)
{
  if (signum == SIGALRM)
  {
    printf("********************sig_handle2 --- SIGALRM:%d\n", signum);
  }
  else if (signum == SIGUSR1)
  {
    printf("********************sig_handle2 --- SIGUSR1:%d\n", signum);
  }
  else if (signum == SIGUSR2)
  {
    printf("********************sig_handle2 --- SIGUSR2:%d\n", signum);
  }
}

void *task1(void *arg)
{
  printf("task1 start\n");

  sigset_t sigset;
  sigemptyset(&sigset);
  sigaddset(&sigset, SIGUSR1);
  pthread_sigmask(SIG_BLOCK, &sigset, NULL);

  while (1)
  {
    printf("task1 start sleep\n");
    int rem = sleep(3);
    printf("task1 remain seconds: %d\n", rem);
  }

  printf("task1 end\n");
}

void *task2(void *arg)
{
  printf("task2 start\n");

  while (1)
  {
    printf("task2  start sleep\n");
    int rem = sleep(3);
    printf("task2 remain seconds: %d\n", rem);
  }

  printf("task2 end\n");
}

void *task3(void *arg)
{
  printf("task3 start\n");

  sigset_t sigset;
  sigemptyset(&sigset);
  sigaddset(&sigset, SIGUSR1);
  sigaddset(&sigset, SIGUSR2);
  sigaddset(&sigset, SIGALRM);
  pthread_sigmask(SIG_BLOCK, &sigset, NULL);

  int signum;
  while (sigwait(&sigset, &signum) == 0)
  {
    printf("task3 -> sigwait signum %d\n", signum);
  }

  printf("task3 end\n");
}

int main()
{
  printf("main start\n");

  pthread_t tid1, tid2, tid3;
  pthread_create(&tid1, NULL, task1, NULL);
  pthread_create(&tid2, NULL, task2, NULL);
  pthread_create(&tid3, NULL, task3, NULL);

  sleep(2);

  struct sigaction sa2;
  sigemptyset(&sa2.sa_mask);
  sa2.sa_flags = 0;
  sa2.sa_handler = sig_handle2;
  if (sigaction(SIGUSR2, &sa2, NULL) == -1)
    perror("sigaction SIGUSR2\n");

  pthread_kill(tid1, SIGUSR1);
  pthread_kill(tid2, SIGUSR2);
  pthread_kill(tid3, SIGUSR1);
  pthread_kill(tid3, SIGUSR2);
  pthread_kill(tid3, SIGALRM);
  // pthread_kill(pthread_self(), SIGUSR1);

  while (1)
  {
    printf("main task  start sleep\n");
    int rem = sleep(3);
    printf("main task remain seconds: %d\n", rem);
  }

  printf("main end\n");
  pthread_exit(NULL);

  return 0;
}

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

## 3.9. 生产者消费者模型

```cpp {class=line-numbers}

```