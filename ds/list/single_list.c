#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

typedef struct Node {
    int data;
    struct Node *next;
} listNode, *List;


int revertList(List *L)
{
    listNode *s, *sa, *p, *pa;
    s = *L;
    p = s->next;
    while (p) {
        sa = p;
        pa = p->next;
        if (*L == s)
            p->next = NULL;
        else
            p->next = s;
        s = p;
        p = pa;
    }
    (*L)->next = s;
    return 0;
}

int initList(List *L)
{
    *L = malloc(sizeof(listNode));
    (*L)->data = 0;
    (*L)->next = NULL;
    return 0;
}

int addList(List *L, int a)
{
    listNode *p, *s;
    s = (*L);
    p = (*L)->next;
    while (p) {
        s = p;
        p = p->next;
    }
    s->next = malloc(sizeof(listNode));
    s->next->data = a;
    s->next->next = NULL;
    return 0;
}

int printList(List *L)
{
    listNode *p, *s;
    s = (*L);
    p = (*L)->next;
    while (p) {
        printf("%2d ", p->data);
        s = p;
        p = p->next;
    }
    printf("\n");
    return 0;
}

int sortList(List *L)
{
    int swapped = 1;
    int tmp;
    listNode *p, *s, *q;

    s = (*L);
    if (NULL == s->next)
        return 0;
    if (NULL == s->next->next)
        return 0;

    swapped = 1;
    while (swapped) {
        s = (*L);
        p = s->next;
        q = p->next;
        swapped = 0;
        while (p && q) {
            if (p->data > q->data) {
                tmp = p->data;
                p->data = q->data;
                q->data = tmp;
                swapped = 1;
            }
            p = q;
            q = p->next;
        }
    }
    return 0;
}

int main()
{
    List myList;
    initList(&myList);
    addList(&myList, 8);
    addList(&myList, 3);
    addList(&myList, 1);
    addList(&myList, 6);
    addList(&myList, 8);
    addList(&myList, 19);
    addList(&myList, 13);
    addList(&myList, 4);
    addList(&myList, 99);
    printList(&myList);
    sortList(&myList);
    printList(&myList);
    return 0;
}
