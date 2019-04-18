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

// --------------------------
int sEnQueue (T elem)
{
    //int back_r = __atomic_load_n (&back, __ATOMIC_RELAXED);
    int back_r = back; // 此处可以不用原子操作!
    int front_r = __atomic_load_n (&front, __ATOMIC_ACQUIRE);
    if ((back_r+1)%SIZE == front_r)
        return FALSE; // 队满
    data[back_r] = elem;
    __atomic_store_n (&back, (back_r+1)%SIZE, __ATOMIC_RELEASE);
    return TRUE;
}

int sDeQueue(T *elem)
{
    //int front_r = __atomic_load_n (&front, __ATOMIC_RELAXED);
    int front_r = front; // 此处可以不用原子操作!
    int back_r = __atomic_load_n (&back, __ATOMIC_ACQUIRE);
    if (front_r == back_r)
        return FALSE; // 队空
    *elem = data[front_r];
    __atomic_store_n (&front, (front_r+1)%SIZE, __ATOMIC_RELEASE);
    return TRUE;
}

// --------------------------
void * producerRoutine (void *arg)
{
    int i;
    for (i = 0; i < 300000;) {
        if (sEnQueue (i)) {
            i++;
        }
    }
    return NULL;
}
void * consumerRoutine (void *arg)
{
    int val, i;
    for (i = 0; i < 300000;) {
        if (sDeQueue (&val)) {
            if (i != val) {
                printf ("expecting %d, but got %d\n", i, val);
            }
            i++;
        }
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
