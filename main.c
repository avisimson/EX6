//

//
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include "threadPool.h"
void  function1();
void  function2();
void  function3();
void  function1WithSleep();
void  function2Sleep();
int main() {
    ThreadPool *threadPool = tpCreate(2);
    char *args = (char *) malloc(10);

    tpInsertTask(threadPool, function1WithSleep, args);
    tpInsertTask(threadPool, function2Sleep, args);
    tpInsertTask(threadPool, function3, args);
    tpInsertTask(threadPool, function1, args);
    tpInsertTask(threadPool, function2Sleep, args);
    sleep(2);
    tpDestroy(threadPool, 1);
    free(args);
    return 0;
}


void  function3() {
    int i;
    for(i=1; i<5;i++) {
        printf("3\n");

    }
}

void  function1() {
    int i;
    for(i=1; i<5;i++) {
        printf("1\n");

    }
}
void  function1WithSleep() {
    int i;
    for(i=1; i<5;i++) {
        printf("1\n");
        sleep(1);

    }
}

void  function2() {
    int i;
    for(i=1; i<5;i++) {
        printf("2\n");
    }
}
void  function2Sleep() {
    int i;
    for(i=1; i<5;i++) {
        printf("2\n");
        sleep(1);
    }
}


void * function3Sleep() {
    int i;
    for(i=1; i<5;i++) {
        printf("3\n");
        sleep(1);

    }
}