/**
 * @copyright: uintchar
 * @version: v1.0
 * @author: uintchar
 * @date: 2021-12-20
 * @description:
 *  - 线程池模板类
 * @revision:
 *  - last revised by *name* on *date*
 *    - content
 **/

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>
#include "locker.h"

/* 线程池类，模板参数 T 是任务类 */
template <typename T>
class threadpool
{
public:
  threadpool(int thread_number = 8, int max_jobs = 10000);
  ~threadpool();
  bool append(T *job);

private:
  static void *worker(void *arg);
  void run();

private:
  int thread_number;       /* 线程数量 */
  pthread_t *threads;      /* 存储线程池中各线程的 ID */
  int max_jobs;            /* 请求队列中最多允许的、等待处理的请求的数量 */
  std::list<T *> jobqueue; /* 请求队列，双向链表 */
  locker qlocker;      /* 保护请求队列的互斥锁 */
  semvar qsem;        /* 表示是否有任务需要处理 */
  bool stop;               /* 表示是否结束线程 */
};

/**
 * @brief:
 *  - 线程池类的构造函数
 * @param:
 *  - thread_number：线程池的大小，即线程的数量
 *  - max_jobs：请求队列中最多允许的等待处理的请求的数量
 * @return:
 **/
template <typename T>
threadpool<T>::threadpool(int thread_number, int max_jobs) : thread_number(thread_number), max_jobs(max_jobs), stop(false), threads(NULL)
{
  if ((thread_number <= 0) || (max_jobs <= 0))
  {
    throw std::exception();
  }

  threads = new pthread_t[thread_number];
  if (!threads)
  {
    throw std::exception();
  }

  /* 创建 thread_number 个线程，并将他们设置为脱离线程 */
  for (int i = 0; i < thread_number; ++i)
  {
    printf("create the %dth thread\n", i);
    if (pthread_create(threads + i, NULL, worker, this) != 0)
    {
      delete[] threads;
      throw std::exception();
    }

    if (pthread_detach(threads[i]))
    {
      delete[] threads;
      throw std::exception();
    }
  }
}

/**
 * @brief:
 *  - 线程池类的析构函数
 * @param:
 * @return:
 **/
template <typename T>
threadpool<T>::~threadpool()
{
  delete[] threads;
  stop = true;
}

/**
 * @brief:
 *  - 向工作队列中添加一个任务
 * @param:
 *  - T：要添加的任务
 * @return:
 *  - true 表示成功，false 表示失败
 **/
template <typename T>
bool threadpool<T>::append(T *job)
{
  /* 操作工作队列时一定要加锁，因为它被所有线程共享 */
  qlocker.lock();
  if (jobqueue.size() > max_jobs)
  {
    qlocker.unlock();
    return false;
  }
  jobqueue.push_back(job);
  qlocker.unlock();
  qsem.post();

  return true;
}

/**
 * @brief:
 *  - 线程的启动函数
 * @param:
 *  - arg：线程创建者传递给新线程的参数
 * @return:
 **/
template <typename T>
void *threadpool<T>::worker(void *arg)
{
  threadpool *pool = (threadpool *)arg;

  pool->run();

  return pool;
}

/**
 * @brief:
 *  - 从工作队列中取出一个任务并执行相应任务
 * @param:
 * @return:
 **/
template <typename T>
void threadpool<T>::run()
{
  while (!stop)
  {
    qsem.wait();
    qlocker.lock();
    if (jobqueue.empty())
    {
      qlocker.unlock();
      continue;
    }
    T *job = jobqueue.front();
    jobqueue.pop_front();
    qlocker.unlock();
    if (!job)
    {
      continue;
    }
    job->process();
  }
}

#endif
