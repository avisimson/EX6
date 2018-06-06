/*
 * Name: Avi Simson
 * ID: 205789100
 */
#ifndef __THREAD_POOL__
#define __THREAD_POOL__
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include "osqueue.h"
#include <stdio.h>
#include <malloc.h>
#define ERROR "Error in system call\n"
typedef enum boolean {false = 0, true = 1}bool;
#define SUCCESS 1
#define FAIL -1
typedef struct task
{
    void (*taskFunc)(void *); //function.
    void * args; //arguements for function.
} Task;
typedef struct thread_pool
{
    int size; //the number of threads.
    int waitTask; //true or false
    pthread_t* threads;
    OSQueue* tasksQueue;
    pthread_cond_t cond;
    pthread_mutex_t lock;
} ThreadPool;
void error();
void threadFunc(void* arg);
ThreadPool* tpCreate(int numOfThreads);
void tpDestroy(ThreadPool* threadPool, int shouldWaitForTasks);
int tpInsertTask(ThreadPool* threadPool, void (*computeFunc) (void *), void* param);

#endif