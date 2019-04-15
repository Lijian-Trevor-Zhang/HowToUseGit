#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#define TRUE    0x1
#define FALSE   0x0

int gIndex = 0;
int gArray[] = {62, 58, 47, 35, 0, 37, 0, 0, 51, 0, 0, 0, 88, 73, 0, 0, 99, 93, 0, 0, 0};
typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} *BiTree;

int createTree(BiTree *T)
{
    if (gArray[gIndex] == 0) {
        *T = NULL;
        gIndex++;
        return 0;
    }
    *T = (struct Node *)malloc(sizeof(struct Node));
    (*T)->data = gArray[gIndex++];

    createTree(&((*T)->lchild));
    createTree(&((*T)->rchild));

    return 0;
}

int InTransTree(BiTree T)
{
    if (NULL == T)
        return 0;
    InTransTree(T->lchild);
    printf("%2d ", T->data);
    InTransTree(T->rchild);
    return 0;
}

int preTransTree(BiTree T)
{
    if (NULL == T)
        return 0;
    printf("%2d ", T->data);
    preTransTree(T->lchild);
    preTransTree(T->rchild);
    return 0;
}

int afTransTree(BiTree T)
{
    if (NULL == T)
        return 0;
    afTransTree(T->lchild);
    afTransTree(T->rchild);
    printf("%2d ", T->data);
    return 0;
}

int searchNode(BiTree T, int key, BiTree *pre, BiTree *cur)
{
    if (NULL == T) {
        *cur = *pre;
        return FALSE;
    } else if (T->data == key) {
        *cur = T;
        return TRUE;
    } else if (key < T->data) {
        *pre = T;
        return searchNode(T->lchild, key, pre, cur);
    }
    else {
        *pre = T;
        return searchNode(T->rchild, key, pre, cur);
    }
}

int insertNode(BiTree *T, int key)
{
    BiTree cur;
    if (!searchNode(*T, key, NULL, &cur)) {
        struct Node *s = malloc(sizeof(struct Node));
        s->data = key;
        s->lchild = s->rchild = NULL;
        if (cur == NULL) {
            *T = s;
        } else if (cur->data > key) {
            cur->lchild = s;
        } else {
            cur->rchild = s;
        }
    }
    return 0;
}

int DelNode(BiTree *T)
{
    BiTree q,s;
    if (NULL == (*T)->lchild) {
        q = *T; *T = (*T)->rchild; free(q);
    } else if (NULL == (*T)->rchild) {
        q = *T; *T = (*T)->lchild; free(q);
    } else {
        q = *T; s = (*T)->lchild;
        while(s->rchild) {
            q = s; s = s->rchild;
        }
        q->data = s->data;
        if (q == *T) {
            q->lchild = s->lchild;
        } else {
            q->rchild = s->lchild;
        }
        free(s);
    }
    return 0;
}

int deleteNode(BiTree *T, int key)
{
    if (NULL == T) {
        return FALSE;
    } else if (key == (*T)->data) {
        return DelNode(T);
    } else if (key < (*T)->data) {
        return DelNode(&(*T)->lchild);
    } else {
        return DelNode(&(*T)->rchild);
    }
    return 0;
}

int main()
{
    BiTree myTree;
    createTree(&myTree);

//  preTransTree(myTree);
//  printf("\n");

//  InTransTree(myTree);
//  printf("\n");

//  afTransTree(myTree);
//  printf("\n");

//  {
//      BiTree preTree, curTree;
//      if (searchNode(myTree, 35, &preTree, &curTree))
//          printf("%2d is leading %2d\n", preTree->data, curTree->data);
//  }
    return 0;
}
