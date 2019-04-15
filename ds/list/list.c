#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include "list.h"

int InitList(LnList *L)
{
    (*L) = malloc(sizeof(LnNode));
    (*L)->data = 0;
    (*L)->next = NULL;
    return 0;
}
int DestroyList(LnList *L)
{
    LnNode *n = NULL;
    if (!(*L))
        return 0;
    while (n) {
        LnNode *s = n->next;
        free(n);
        n = s;
    }
    free(*L);
    *L = NULL;
    return 0;
}

int ListEmpty(LnList L)
{
    if (!L)
        return TRUE;
    if (L->next == NULL)
        return TRUE;
    else return FALSE;
}

int creatList(LnList *L, int a[], int n)
{
    int i;
    InitList(L);
    for (i = 0; i < n; i++) {
        LnNode *s = malloc(sizeof(LnNode));
        s->data = a[i];
        s->next = (*L)->next;
        (*L)->next = s;
    }
    return 0;
}

int clearList(LnList *L)
{
    LnNode *n = (*L)->next;
    while (n) {
        LnNode *s = n->next;
        free(n);
        n = s;
    }
    (*L)->next = 0;
    return 0;
}

int showList(LnList L)
{
    if (!L)
        return 0;
    LnNode *n = L->next;
    printf("showList: ");
    while (n) {
        printf("%2d ", n->data);
        n = n->next;
    }
    printf("\n");
    return 0;
}

int getElem(LnList L, int n, int *e)
{
    int i = 0;
    if (!L)
        return FALSE;
    LnNode *s = L->next;
    while (s && i < n) {
        s = s->next;
        i++;
    }
    if (i < n) {
        return FALSE;
    } else {
        if (s) {
            *e = s->data;
            return TRUE;
        }
        else
            return FALSE;
    }
}

int LocateElem(LnList L, int e) {
    if (!L)
        return -1;
    LnNode *n = L->next;
    int i = 0;
    while (n && (n->data != e)) {
        i++;
        n = n->next;
    }
    if (n && (e == n->data))
        return i;
    else
        return -1;
}

int reverseList(LnList *L)
{
    LnNode *s = NULL;
    LnNode *n = (*L)->next;
    while (n) {
        LnNode *Q = n->next;
        n->next = s;
        s = n;
        n = Q;
    }
    (*L)->next = s;
    return 0;
}

int revList(LnList *L, LnNode *s, LnNode *n)
{
    if (!n) {
        (*L)->next = s;
        return 0;
    }
    else {
        revList(L, n, n->next);
        n->next = s;
        return 0;
    }
}

int insertElem(LnList L, int i, int e)
{
    LnNode *s = L;
    LnNode *n = L->next;
    int m = 0;
    while (n && (m < i)) {
        s = n;
        n = n->next;
        m++;
    }
    if (n && (m == i)) {
        LnNode *Q = malloc(sizeof(LnNode));
        s->next = Q;
        Q->next = n;
        Q->data = e;
    }
    return 0;
}
int removeElem(LnList L, int i)
{
    LnNode *s = L;
    LnNode *n = L->next;
    int m = 0;
    while (n && (m < i)) {
        s = n;
        n = n->next;
        m++;
    }
    if (n && (m == i)) {
        s->next = n->next;
        free(n);
    }
    return 0;
}

int removeLastNth(LnList L, int n)
{
    LnNode *s = L->next;
    int i = 0;
    while (s && (i < n)) {
        s = s->next;
        i++;
    }
    if (s && (i == n)) {
        LnNode *X = L;
        LnNode *Q = L->next;
        while (s->next) {
            s = s->next;
            Q = Q->next;
            X = X->next;
        }
        X->next = Q->next;
        free(Q);
    } else {
        printf("there's no so many nodes\n");
    }
}

int calNo(LnList L)
{
    if (!L)
        return 0;
    else {
        return (1 + calNo(L->next));
    }
}

int rmLastNth(LnList L, LnList Q, int n)
{
    if (!Q)
        return 0;
    if (0 == n) {
        L->next = Q->next;
        free(Q);
    } else {
        rmLastNth(Q, Q->next, n-1);
    }
    return 0;
}

int MergeList(LnList L1, LnList L2)
{
    LnNode *Q = L1;
    LnNode *s1 = L1->next;
    LnNode *s2 = L2->next;
    while(s1 && s2) {
        if (s1->data > s2->data) {
            Q->next = s2;
            Q = s2;
            s2 = s2->next;
        } else {
            Q->next = s1;
            Q = s1;
            s1 = s1->next;
        }
    }
    if (s1) {
        Q->next = s1;
    }
    if (s2) {
        Q->next = s2;
    }
    return 0;
}

int sListVerify(void)
{
    LnList L;
    int a[] = {4,1,22,13,5,7,9,13,12,9,6,3,0};
    int n = sizeof(a)/sizeof(a[0]);
    creatList(&L, a, n);
    showList(L);
    DestroyList(&L);
    showList(L);
    creatList(&L, a, n);
    showList(L);

//  int e;
//  int i = 3;
//  printf("%s %dth: %d\n", getElem(L, i, &e)?"found":"not found", i, e);
//  i = 0;
//  printf("%s %dth: %d\n", getElem(L, i, &e)?"found":"not found", i, e);


//  printf("Locate value 22: %d\n", LocateElem(L, 6));
//  printf("Locate value 22: %d\n", LocateElem(L, 22));
//  printf("Locate value 21: %d\n", LocateElem(L, 21));

    showList(L);
    reverseList(&L);
    showList(L);
    revList(&L, NULL, L->next);
    showList(L);

    printf("...\n");
    insertElem(L, 2, 31);
    showList(L);
    removeElem(L, 2);
    showList(L);
    removeLastNth(L, 2);
    showList(L);

    printf("totally has %d nodes\n", calNo(L->next));
    rmLastNth(L, L->next, 2);
    showList(L);

    printf(":::::\n");

    LnList L1;
    int a1[] = {4,12,13,13,22,29,36,43,50};
    int n1 = sizeof(a1)/sizeof(a1[0]);
    creatList(&L1, a1, n1);
    reverseList(&L1);

    LnList L2;
    int a2[] = {2,2,3,18,32,39,46,53,60};
    int n2 = sizeof(a2)/sizeof(a2[0]);
    creatList(&L2, a2, n2);
    reverseList(&L2);

    MergeList(L1, L2);
    showList(L1);
    return 0;
}

int main()
{
    sListVerify();
    return 0;
}
