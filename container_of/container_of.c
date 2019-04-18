#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <memory.h>

 #define CLIB_PACKED(type, x) type x __attribute__ ((packed))

// 返回type结构体的member数据成员的指针ptr，所在的type结构体指针
// 这也是个很好的定义宏定义的示例!!
#define container_of(ptr, type, member) ({				\
	void *__mptr = (void *)(ptr);					\
	((type *)(__mptr - offsetof(type, member))); })

struct BiNode {
    int age;
    int addr;
    long ho;
    char M;
    CLIB_PACKED(int, summ);
    char name[24];
};


int main (void)
{
    struct BiNode *n = malloc (sizeof(struct BiNode));
    printf ("n : %p\n", n);
    printf ("n->M : %p\n", &(n->M));
    printf ("n : %p\n", container_of(&(n->M), struct BiNode, M));

    // 对压缩形式的数据成员依然成立
    printf ("n : %p\n", n);
    printf ("n->summ : %p\n", &(n->summ));
    printf ("n : %p\n", container_of(&(n->summ), struct BiNode, summ));

    printf ("M: %d\n", offsetof(struct BiNode, M));
    printf ("summ: %d\n", offsetof(struct BiNode, summ));
    printf ("name: %d\n", offsetof(struct BiNode, name));
    return 0;
}
