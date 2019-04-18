#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>

#define FALSE   0
#define TRUE    1

#define SIZE 32
typedef int T;

static int front;
static int back;
static T data[SIZE] = {0};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;/*初始化互斥锁*/

// --------------------------
int EnQueue (T elem)
{
    if ((back+1)%SIZE == front)
        return FALSE; // 队满
    data[back] = elem;
    back = (back+1)%SIZE;
    return TRUE;
}

int DeQueue(T *elem)
{
    if (front == back)
        return FALSE; // 队空
    *elem = data[front];
    front = (front+1)%SIZE;
    return TRUE;
}
// --------------------------

void * producerRoutine (void *arg)
{
    int i;
    for (i = 0; i < 300000;) {
        //pthread_mutex_lock(&mutex);/*锁住互斥量*/
        if (EnQueue (i)) {
            i++;
        }
        //pthread_mutex_unlock(&mutex);/*解锁互斥量*/
    }
    return NULL;
}

void * consumerRoutine (void *arg)
{
    int val, i;
    for (i = 0; i < 300000;) {
        //pthread_mutex_lock(&mutex);/*锁住互斥量*/
        if (DeQueue (&val)) {
            if ( (i != val) ) {
                printf ("expecting %d, but got %d\n", i, val);
            }
            i++;
        }
        //pthread_mutex_unlock(&mutex);/*解锁互斥量*/
    }
    return NULL;
}

int main (void)
{
    pthread_t proID, conID;
    pthread_create (&proID, NULL, producerRoutine, (void *)NULL);
    pthread_create (&conID, NULL, consumerRoutine, (void *)NULL);

    pthread_join (proID, NULL);
    pthread_join (conID, NULL);
    return 0;
}
