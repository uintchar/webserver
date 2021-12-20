/**
 * @copyright: uintchar
 * @version: v1.0
 * @author: uintchar
 * @date: 2021-12-20
 * @description:
 *  - 线程同步机制的封装类
 * @revision:
 *  - last revised by *name* on *date*
 *    - content：
 **/

#ifndef LOCKER_H_
#define LOCKER_H_

#include <exception>
#include <pthread.h>
#include <semaphore.h>

/* 互斥锁类的封装 */
class locker
{
public:
  locker()
  {
    if (pthread_mutex_init(&mut, NULL) != 0)
    {
      throw std::exception();
    }
  }

  ~locker()
  {
    pthread_mutex_destroy(&mut);
  }

  bool lock()
  {
    return pthread_mutex_lock(&mut) == 0;
  }

  bool unlock()
  {
    return pthread_mutex_unlock(&mut) == 0;
  }

  pthread_mutex_t *get()
  {
    return &mut;
  }

private:
  pthread_mutex_t mut;
};

/* 条件变量类的封装 */
class condvar
{
public:
  condvar()
  {
    if (pthread_cond_init(&cond, NULL) != 0)
    {
      throw std::exception();
    }
  }

  ~condvar()
  {
    pthread_cond_destroy(&cond);
  }

  bool wait(pthread_mutex_t *mut)
  {
    return pthread_cond_wait(&cond, mut) == 0;
  }

  bool timewait(pthread_mutex_t *mut, struct timespec t)
  {
    return pthread_cond_timedwait(&cond, mut, &t) == 0;
  }

  bool signal()
  {
    return pthread_cond_signal(&cond) == 0;
  }

  bool broadcast()
  {
    return pthread_cond_broadcast(&cond) == 0;
  }

private:
  pthread_cond_t cond;
};

/* 信号量类的封装 */
class semvar
{
public:
  semvar()
  {
    if (sem_init(&sem, 0, 0) != 0)
    {
      throw std::exception();
    }
  }

  semvar(int num)
  {
    if (sem_init(&sem, 0, num) != 0)
    {
      throw std::exception();
    }
  }

  ~semvar()
  {
    sem_destroy(&sem);
  }
  
  bool wait()
  {
    return sem_wait(&sem) == 0;
  }

  bool post()
  {
    return sem_post(&sem) == 0;
  }

private:
  sem_t sem;
};

#endif