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

static int vF = 0;
static int vB = 0;

// --------------------------
int sEnQueue (T elem[], int n)
{
    int i;
    int back_r = __atomic_load_n (&back, __ATOMIC_RELAXED);
    if ( ((vF - back_r - 1 + SIZE)%SIZE) < n ) {
        vF = __atomic_load_n (&front, __ATOMIC_ACQUIRE);
        if ( ((vF - back_r - 1 + SIZE)%SIZE) < n  )
            return FALSE; // 队满
    }
    for (i = 0; i < n; i++) {
        data[(back_r+i)%SIZE] = elem[i];
    }
    __atomic_store_n (&back, (back_r+n)%SIZE, __ATOMIC_RELEASE);
    return TRUE;
}

int sDeQueue(T elem[], int n)
{
    int i;
    int front_r = __atomic_load_n (&front, __ATOMIC_RELAXED);
    if ((vB - front_r + SIZE)%SIZE < n) {
        vB = __atomic_load_n (&back, __ATOMIC_ACQUIRE);
        if ((vB - front_r + SIZE)%SIZE < n)
            return FALSE; // 队空
    }
    for (i = 0; i < n; i++) {
        elem[i] = data[(front_r+i)%SIZE];
    }
    __atomic_store_n (&front, (front_r+n)%SIZE, __ATOMIC_RELEASE);
    return TRUE;
}

// --------------------------
#define EN_N 3
#define DE_N 4
void * producerRoutine (void *arg)
{
    int i, oop;
    int val[EN_N];
    for (i = 0; i < 300;) {
        for (oop = 0; oop < EN_N; oop++) {
            val[oop] = i+oop;
        }
        if (sEnQueue (val, EN_N)) {
            i += EN_N;
        }
    }
    return NULL;
}
void * consumerRoutine (void *arg)
{
    int i, oop;
    int val[DE_N];
    for (i = 0; i < 300;) {
        if (sDeQueue (val, DE_N)) {
            for (oop = 0; oop < DE_N; oop++) {
                if (i+oop != val[oop]) {
                    printf ("expecting %d, but got %d\n", i+oop, val[oop]);
                } else {
                    printf ("got %d\n", val[oop]);
                }
            }
            i += DE_N;
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
