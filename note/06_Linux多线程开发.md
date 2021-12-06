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

- 查看当前 pthread 库版本：`getconf GNU_LIBPTHREAD_VERSION`

## 2.1. 线程创建

```cpp {class=line-numbers}
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
```

## 2.2. 线程终止

```cpp {class=line-numbers}
void pthread_exit(void *retval);
```

## 2.3. 线程连接

```cpp {class=line-numbers}
int pthread_join(pthread_t thread, void **retval);
```

## 2.4. 线程分离

```cpp {class=line-numbers}
int pthread_detach(pthread_t thread);
```

## 2.5. 线程取消

```cpp {class=line-numbers}
int pthread_cancel(pthread_t thread);
```

## 2.6. 其他线程函数

```cpp {class=line-numbers}
pthread_t pthread_self(void);
int pthread_equal(pthread_t t1, pthread_t t2);
```

## 2.7. 线程属性

```cpp {class=line-numbers}
pthread_attr_t
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);
int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
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
```

## 3.8. 生产者消费者模型

```cpp {class=line-numbers}

```