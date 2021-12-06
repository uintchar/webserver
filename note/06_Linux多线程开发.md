- [1. 线程概述](#1-线程概述)
  - [1.1. 线程和进程的区别](#11-线程和进程的区别)
  - [1.2. 线程和进程的虚拟地址空间](#12-线程和进程的虚拟地址空间)
  - [1.3. 线程之间共享和非共享资源](#13-线程之间共享和非共享资源)
  - [1.4. NPTL](#14-nptl)
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
  - [3.5. 条件变量](#35-条件变量)
  - [3.6. 信号量](#36-信号量)
  - [3.7. 生产者消费者模型](#37-生产者消费者模型)

# 1. 线程概述

## 1.1. 线程和进程的区别

## 1.2. 线程和进程的虚拟地址空间

## 1.3. 线程之间共享和非共享资源

## 1.4. NPTL

# 2. 线程控制

## 2.1. 线程创建

```cpp {class=line-numbers}
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
                   void *(*start_routine) (void *), void *arg);
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

## 3.5. 条件变量

```cpp {class=line-numbers}
pthread_cond_t
int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
```

## 3.6. 信号量

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

## 3.7. 生产者消费者模型

```cpp {class=line-numbers}

```