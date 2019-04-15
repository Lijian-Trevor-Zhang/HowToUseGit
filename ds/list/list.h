#ifndef __LIST_H_
#define __LIST_H__

#define TRUE    1
#define FALSE   0

typedef struct LnNode {
    int data;
    struct LnNode *next;
} LnNode, *LnList;


/*
 * InitList(*L);
 * ListEmpty(L);
 * ClearList(*L);
 * getElem(L, i, *e);
 * LocateElem(L, e);
 * ListInsert(L, i, e);
 * ListDelete(L, i, *e);
 * ListLength(L);
 *
 * */
#endif
