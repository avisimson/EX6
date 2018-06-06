/*
 * Name: Avi Simson
 * ID: 205789100
 */
#include "threadPool.h"
/**
 function creates threadpool with numOfThreads.
 param name = numOfThreads, the number of threads being created.
 return the struct of thread-pool created.
 */
ThreadPool *tpCreate(int numOfThreads) {
    ThreadPool *threadPool;
    //allocating memory for struct of thread-pool.
    if ((threadPool = (ThreadPool*)malloc(sizeof(ThreadPool))) == NULL) {
        error();
    }
    //initializing all fields of struct.
    threadPool->size = numOfThreads;
    pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * numOfThreads);
    if (threads == NULL) {
        error();
    }
    threadPool->threads = threads;
    threadPool->waitTask = true;
    threadPool->tasksQueue = osCreateQueue();
    if (pthread_mutex_init(&threadPool->lock, NULL)) {
        error();
    }
    if(pthread_cond_init(&threadPool->cond , NULL)) {
        error();
    }
    //creating the threads.
    int i;
    for (i = 0; i < threadPool->size; i++){
        pthread_t thread;
        int ret = pthread_create(&thread, NULL, threadFunc, threadPool);
        if (ret != 0) {
            error();
        }
        //insert the new created thread into thread-pool.
        threadPool->threads[i] = thread;
    }
    return threadPool;
}
/*
 * function executes the functions in thread-pool. it gets a task from queue and execute it.
 * param name = arg, a void* of the threadPool.
 */
void threadFunc(void* arg) {
    ThreadPool *tp = (ThreadPool*) arg;
    Task* task = NULL;
    //loop continues until destroy func will make waitTask false.
    while(tp->waitTask) {
        if(pthread_mutex_lock(&tp->lock)) {
            error();
        }
        //check if queue is empty.
        if (osIsQueueEmpty(tp->tasksQueue)) {
            pthread_cond_wait(&tp->cond, &tp->lock); //wait until queue will not be empty.
            if (!tp->waitTask) { //if destroy func executed.
                if(pthread_mutex_unlock(&tp->lock)){
                    error();
                }
                return;
            }
        }
        task = (Task *) osDequeue(tp->tasksQueue); //get data to execute.
        if(pthread_mutex_unlock(&tp->lock)) {
            error();
        }
        (*task->taskFunc)(task->args); //execute the data.
        free(task);
    }
}
/*
 * function insert new task to queue to be executed in the future by thread-pool.
 * param name = threadPool, the threadPool.
 * param name = computeFunc, the pointer for the task needs to be executed.
 * param name = param, a void* of the parameters to the function.
 * returns - SUCCESS if entered to queue, fail if not entered well.
 */
int tpInsertTask(ThreadPool *threadPool, void (*computeFunc)(void *), void *param) {
    if(threadPool->waitTask) { //if destroy func wasn't executed.
        Task* task;
        //allocate memory for task.
        if ((task = (Task *)malloc(sizeof(Task))) == NULL) {
            error();
        }
        task->taskFunc = computeFunc;
        task->args = param;

        if(osIsQueueEmpty(threadPool->tasksQueue)){
            if (pthread_cond_broadcast(&threadPool->cond)){ //inform the cond.
                error();
            }
        }
        //add new task for queue.
        osEnqueue(threadPool->tasksQueue, task);
        return SUCCESS;
    }
    //case of destroy. no new tasks can be entered.
    return FAIL;
}
/*
 * function destroys thread-pool. if second param is 0 it finishes only threads that are working'
 * if not 0 the thread-pool will execute all tasks in queue and then will be destroyed.
 * through all proccess-new tasks will not be able to enter the queue.
 * param name = threadPool, the thread-pool.
 * param name = shouldWaitForTasks, 0 if only wait for current threads, other number if wait for all queue.
 */
void tpDestroy(ThreadPool *threadPool, int shouldWaitForTasks) {
    if(shouldWaitForTasks == 0) { //only finish current tasks in threads.
        threadPool->waitTask = false;
    } else {
        while(!osIsQueueEmpty(threadPool->tasksQueue)); //wait for queue to be empty.
        threadPool->waitTask = false;
    }
    //inform the cond not to wait anymore in threads.
    if(pthread_cond_broadcast(&threadPool->cond)){
        error();
    }
    int i;
    //wait for all current threads to end.
    for (i = 0; i < threadPool->size; i++) {
        pthread_join(threadPool->threads[i], NULL);
    }
    //free ALL the memory of thread-pool struct and destroy it.
    free(threadPool->threads);
    osDestroyQueue(threadPool->tasksQueue);
    if(pthread_mutex_destroy(&threadPool->lock)){
        error();
    }
    if(pthread_cond_destroy(&threadPool->cond)){
        error();
    }
    free(threadPool);
}
/*
 * function being called in case of system error-ending program and writing err message.
 */
void error() {
    write(STDERR_FILENO, ERROR, sizeof(ERROR));
    exit(-1);
}
