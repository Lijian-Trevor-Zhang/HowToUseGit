#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <memory.h>
#include "binary.h"


typedef struct BiNode {
    int data;
    struct BiNode *left;
    struct BiNode *right;
} BiNode, *BiTree;

int *globalArgs;
int globalIndex = 0;

int initTree(BiTree *T)
{
    int val = globalArgs[globalIndex++];
    if (val) {
        *T = malloc(sizeof(BiNode));
        (*T)->data = val;
        printf("create %2d\n", (*T)->data);
        initTree(&((*T)->left));
        initTree(&((*T)->right));
    } else {
        *T = NULL;
    }
    return 0;
}

int releaseTree(BiTree *T)
{
    if (*T) {
        releaseTree(&((*T)->left));
        releaseTree(&((*T)->right));
        printf("free %2d\n", (*T)->data);
        free(*T);
        *T = NULL;
    }
    return 0;
}

int preTrans(BiTree *T)
{
    if (*T) {
        printf("%2d ", (*T)->data);
        preTrans(&((*T)->left));
        preTrans(&((*T)->right));
    }
    return 0;
}

int midTrans(BiTree *T)
{
    if (*T) {
        midTrans(&(*T)->left);
        printf("%2d ", (*T)->data);
        midTrans(&(*T)->right);
    }
    return 0;
}

int postTrans(BiTree *T)
{
    if (*T) {
        postTrans(&(*T)->left);
        postTrans(&(*T)->right);
        printf("%2d ", (*T)->data);
    }
    return 0;
}

int verifyTrans()
{
#if 0
             9
           /    \
        2        11
       / \      /  \
     5    1   31    6
    / \  / \  /\   / \
   N  9 7  N N  N 4  N
#endif
    BiTree T;
    int array[128] = {9,2,5,0,9,0,0,1,7,0,0,0,11,31,0,0,6,4,0,0,0};
    globalArgs = array;
    globalIndex = 0;

    initTree(&T);

    printf("pre-order tranverse: \n");
    preTrans(&T);
    printf("\n done with pre-order tranverse\n");

    printf("in-order tranverse: \n");
    midTrans(&T);
    printf("\n done with mid-order tranverse\n");

    printf("post-order tranverse: \n");
    postTrans(&T);
    printf("\n done with post-order tranverse\n");

    releaseTree(&T);

    return 0;
}

int verifyInitRelease()
{
#if 0
             9
           /    \
        2        11
       / \      /  \
     5    1   31    6
    / \  / \  /\   / \
   N  9 7  N N  N 4  N
#endif
    BiTree T;
    int array[128] = {9,2,5,0,9,0,0,1,7,0,0,0,11,31,0,0,6,4,0,0,0};
    globalArgs = array;
    globalIndex = 0;
    initTree(&T);
    releaseTree(&T);

    return 0;
}

int cmpTree(BiTree T1, BiTree T2)
{
    if (T1 == T2)
        return TRUE;
    else if ((NULL == T1) || (NULL == T2))
        return FALSE;
    else {
        return ((T1->data == T2->data) &&
                cmpTree(T1->left, T2->left) &&
                cmpTree(T1->right, T2->right));
    }
    return 0;
}

int verifyCmp()
{
#if 0
             9
           /    \
        2        11
       / \      /  \
     5    1   31    6
    / \  / \  /\   / \
   N  9 7  N N  N 4  N
#endif
   BiTree T1, T2;
    int array1[128] = {9,2,5,0,9,0,0,1,7,0,0,0,11,31,0,0,6,4,0,0,0};
    int array2[128] = {9,2,5,0,9,0,0,1,7,0,0,0,11,31,0,0,6,4,0,0,0};
    globalArgs = array1;
    globalIndex = 0;
    initTree(&T1);
    globalArgs = array2;
    globalIndex = 0;
    initTree(&T2);

    int cmp = cmpTree(T1, T2);
    printf("result is %d\n", cmp);
    return 0;
}

#define MAX_TREE 100
typedef struct BiQueue {
    BiTree tree[MAX_TREE];
    int head, tail;
} BiQueue;
int initQueue(BiQueue *Q)
{
    memset(Q, 0, sizeof(BiQueue));
    return 0;
}
int isEmpty(BiQueue *Q) {
    if (Q->head == Q->tail)
        return TRUE;
    else
        return FALSE;
}
int EnQueue(BiQueue *Q, BiTree T)
{
    if ((Q->tail+1)%MAX_TREE == Q->head) {
        printf("Queue is full\n");
        return 0;
    } else {
        Q->tree[Q->tail] = T;
        Q->tail = (Q->tail+1)%MAX_TREE;
    }
    return 0;
}

BiTree DeQueue(BiQueue *Q)
{
    BiTree T;
    if (Q->head == Q->tail) {
        printf("Queue is empty\n");
        return 0;
    } else {
        T = Q->tree[Q->head];
        Q->head = (Q->head + 1)%MAX_TREE;
    }
    return T;
}

int levelTrans(BiTree T)
{
    BiQueue Q;
    initQueue(&Q);
    if (T) {
        EnQueue(&Q, T);
    }
    while (!isEmpty(&Q)) {
        BiNode *n = DeQueue(&Q);
        printf("%2d ", n->data);
        if (n->left)
            EnQueue(&Q, n->left);
        if (n->right)
            EnQueue(&Q, n->right);
    }
    return 0;
}

int verifyLevelTrans()
{
    BiTree T;
    int array[128] = {9,2,5,0,9,0,0,1,7,0,0,0,11,31,0,0,6,4,0,0,0};
    globalArgs = array;
    globalIndex = 0;
    initTree(&T);
    levelTrans(T);
    releaseTree(&T);

    return 0;
}
#if 0
int nonRecurseTrans(BiTree T)
{
    while (n->left) {
        Push(S, n);
        n = n->left;
    }
    n = n;
    if (n->right)
        n = n->right;
}
#endif
int maxHight(BiTree T)
{
    if (!T)
        return 0;
    else {
        return (1+MAX(maxHight(T->left), maxHight(T->right)));
    }
    return 0;
}
int minHight(BiTree T)
{
    if (!T)
        return 0;
    else {
        return (1+MIN(minHight(T->left), minHight(T->right)));
    }

}
int NodesNo(BiTree T)
{
    if (!T)
        return 0;
    else
        return (1+NodesNo(T->left)+NodesNo(T->right));
}

int leafNodesNo(BiTree T)
{
    if (!T)
        return 0;
    else if ((NULL == T->left) && (NULL == T->right))
    {
        printf("%2d ", T->data);
        return 1;
    }
    else
        return (leafNodesNo(T->left)+leafNodesNo(T->right));
}

int nodesOnLevel(BiTree T, int i, int level)
{
    if (!T)
        return 0;
    else if (i == level)
        printf("%2d ", T->data);
    else {
        nodesOnLevel(T->left, i+1, level);
        nodesOnLevel(T->right, i+1, level);
    }
    return 0;
}

int isBalance(BiTree T) // 平衡二叉树
{
    if(!T)
        return TRUE;
    else {
        int leftHight = maxHight(T->left);
        int rightHight = maxHight(T->right);
        int factor = (leftHight > rightHight)?(leftHight-rightHight):(rightHight-leftHight);
        return ((factor < 2) && isBalance(T->left) && isBalance(T->right));
    }
}

int isLessThan(BiTree T, int val)
{
    if (T) {
        return ((T->data <= val)
                && isLessThan(T->left, val) &&
                isLessThan(T->right, val));
    } else {
        return TRUE;
    }
}

int isGreaterThan(BiTree T, int val)
{
    if (T) {
        return ((T->data <= val)
                && isGreaterThan(T->left, val) &&
                isGreaterThan(T->right, val));
    } else {
        return TRUE;
    }
}

int isOrderedTree(BiTree T)
{
    if (T) {
        return (isLessThan(T->left, T->data) &&
                isGreaterThan(T->right, T->data) &&
                isOrderedTree(T->left) &&
                isOrderedTree(T->right));
    } else {
        return TRUE;
    }

}

int isMirrorTree(BiTree T1, BiTree T2)
{
    if ((NULL == T1) && (NULL == T2))
        return TRUE;
    else if ((NULL == T1) || (NULL == T2))
        return FALSE;
    else {
        return ((T1->data == T2->data) &&
            (isMirrorTree(T1->left, T2->right)) &&
            (isMirrorTree(T1->right, T2->left)));
    }
}

int doMirror(BiTree T)
{
    if (T) {
        BiTree left = T->left;
        BiTree right = T->right;
        doMirror(left);
        doMirror(right);
        T->left = right;
        T->right = left;
    }
    return 0;
}

int verifyHight()
{
    BiTree T;
    int array[128] = {9,2,5,0,9,0,0,1,7,0,0,0,11,31,0,0,6,4,0,0,0};
    globalArgs = array;
    globalIndex = 0;
    initTree(&T);

    int max = maxHight(T);
    int min = minHight(T);
    printf("hight max: %d min %d\n", max, min);
    int nodes = NodesNo(T);
    printf("total node No. %d\n", nodes);

    printf("leaf nodes:\n");
    int leaf_nodes = leafNodesNo(T);
    printf("\nleaf node No. %d\n", leaf_nodes);

    int level = 3;
    printf("target level: %d\n", level);
    nodesOnLevel(T, 1, level);
    printf("\ndone with level %d\n", level);

    BiTree T0;
    int array0[128] = {1,2,3,4,0,0,0,0,0};
    globalArgs = array0;
    globalIndex = 0;
    initTree(&T0);
    int isB = isBalance(T0);
    printf("isBalance: %d\n", isB);

    BiTree TI;
    int arrayI[128] = {9,2,3,1,0,0,2,0,0,4,3,0,0,4,0,0,2,4,4,0,0,3,0,0,3,2,0,0,1,0,0};
    globalArgs = arrayI;
    globalIndex = 0;
    initTree(&TI);
    printf("isMirror: %d\n", isMirrorTree(TI, TI));
    return 0;
}

int verifyMirror()
{
    BiTree T0;
    int array0[128] = {1,2,3,4,0,0,0,0,0};
    globalArgs = array0;
    globalIndex = 0;
    initTree(&T0);
    midTrans(&T0);
    doMirror(T0);
    midTrans(&T0);
    return 0;
}

struct commonData {
    int val1, val2, valParent;
    int val1Found, val2Found, parentFound;
};

int commonParent(BiTree T, struct commonData *data)
{
    if (T) {
        commonParent(T->left, data);
        commonParent(T->right, data);
        if (data->parentFound)
            return 0;
        if (data->val1Found && data->val2Found) {
            data->parentFound = TRUE;
            data->valParent = T->data;
            return 0;
        }
        if (!data->val1Found && data->val1 == T->data) {
            data->val1Found = TRUE;
        }
        if (!data->val2Found && data->val2 == T->data) {
            data->val2Found = TRUE;
        }
    }
    return 0;
}

int verifyCommon()
{
    BiTree T;
    int array[128] = {9,2,5,0,9,0,0,1,7,0,0,0,11,31,0,0,6,4,0,0,0};
    globalArgs = array;
    globalIndex = 0;
    initTree(&T);

    struct commonData data;
    memset(&data, 0, sizeof(struct commonData));
    data.val1 = 5;
    data.val2 = 7;
    commonParent(T, &data);
    printf("common parent is %2d\n", data.valParent);

    return 0;
}

int searchNode(BiTree T, int val)
{
    if (!T)
        return FALSE;
    if (T->data == val)
        return TRUE;
    if (searchNode(T->left, val))
        return TRUE;
    if (searchNode(T->right, val))
        return TRUE;
    return FALSE;
}

int verifySearchNode()
{
    BiTree T;
    int array[128] = {9,2,5,0,9,0,0,1,7,0,0,0,11,31,0,0,6,4,0,0,0};
    globalArgs = array;
    globalIndex = 0;
    initTree(&T);
    printf("search node:%d return:%d\n", 12, searchNode(T, 12));
    printf("search node:%d return:%d\n", 11, searchNode(T, 11));
    return 0;
}

#if 0
             9
           /    \
        2        11
       / \      /  \
     5    1   31    6
    / \  / \  /\   / \
   N  9 7  N N  N 4  N
#endif

int sMaxHight(BiTree T)
{
    if (!T)
        return 0;
    return (1 + MAX(sMaxHight(T->left), sMaxHight(T->right)));
}

int sMinHight(BiTree T)
{
    if (!T)
        return 0;
    return (1 + MIN(sMinHight(T->left), sMinHight(T->right)));
}

int sNodeNo(BiTree T)
{
    if (!T)
        return 0;
    return (1+sNodeNo(T->left)+sNodeNo(T->right));
}

int sLeafs(BiTree T)
{
    if (!T)
        return 0;
    if ((NULL == T->left) && (NULL == T->right))
        return 1;
    else
        return (sLeafs(T->left)+sLeafs(T->right));
}

int sNodeInLevel(BiTree T, int level, int i)
{
    if (!T)
        return 0;
    if (i == level)
        return 1;
    else
        return (sNodeInLevel(T->left, level, i+1) +
                sNodeInLevel(T->right, level, i+1));
}

#define ABS(x) ((x)>0?(x):(-(x)))

int sIsB(BiTree T)
{
    if (!T)
        return TRUE;
    return (ABS(sMaxHight(T->left) - sMaxHight(T->right)) < 2);
}

int sComplete(BiTree T)
{
    if (!T)
        return TRUE;
    return (sIsB(T) && sComplete(T->left) && sComplete(T->right) &&
            (sMaxHight(T->left) >= sMaxHight(T->right)));
}

int sIsEqual(BiTree T1, BiTree T2)
{
    if (T1 == T2)
        return TRUE;
    else if ((NULL == T1) || (NULL == T2))
        return FALSE;
    else
        return ((T1->data == T2->data) &&
                sIsEqual(T1->left, T2->left) &&
                sIsEqual(T1->right, T2->right));
}

int sIsMirror(BiTree T1, BiTree T2)
{
    if ((NULL == T1) && (NULL == T2))
        return TRUE;
    else if ((NULL == T1) || (NULL == T2))
        return FALSE;
    else {
        return ((T1->data == T2->data) &&
                sIsMirror(T1->left, T2->right) &&
                sIsMirror(T1->right, T2->left));
    }
}

int sHaveNode(BiTree T, int val)
{
    if (!T)
        return FALSE;
    if (T->data == val)
        return TRUE;
    else
        return (sHaveNode(T->left, val) || sHaveNode(T->right, val));
}

static int gCommonNode = 0;

int sCommonParent(BiTree T, int val1, int val2)
{
    if (!T)
        return 0;
    if (sHaveNode(T, val1) && sHaveNode(T, val2)) {
        gCommonNode = T->data;
    }
    sCommonParent(T->left, val1, val2);
    sCommonParent(T->right, val1, val2);
    return 0;
}

typedef struct sStack {
    int top;
    BiTree data[128];
} sStack;

int sStackInit(sStack *s)
{
    memset(s, 0, sizeof(sStack));
    s->top = -1;
    return 0;
}
int sPush(sStack *s, BiTree val)
{
    s->top++;
    s->data[s->top] = val;
    return 0;
}
BiTree sPop(sStack *s)
{
    BiTree val = s->data[s->top];
    s->top--;
    return val;
}
int sEmpty(sStack s)
{
    if (-1 == s.top)
        return TRUE;
    else
        return FALSE;
}

int sPreTrans(BiTree T)
{
    sStack s;
    if (!T)
        return 0;
    printf("pre-order tranverse: ");
    sStackInit(&s);
    sPush(&s, T);
    while (!sEmpty(s)) {
        T = sPop(&s);
        printf("%2d ", T->data);
        if (T->right)
            sPush(&s, T->right);
        if (T->left)
            sPush(&s, T->left);
    }
    printf("\n");
    return 0;
}

int sMidTrans(BiTree T)
{
    sStack s;
    if (!T)
        return 0;
    printf("in-order tranverse: ");
    sStackInit(&s);
    BiTree n = T;
    while ((NULL != n) || !sEmpty(s)) {
        while (n) {
            sPush(&s, n);
            n = n->left;
        }
        n = sPop(&s);
        printf("%2d ", n->data);
        n = n->right;
    }
    printf("\n");
}

int sInsert(BiTree T, int val, BiTree P)
{
    if (!T) {
            BiTree n = malloc(sizeof(BiNode));
            memset(n, 0, sizeof(BiNode));
            n->data = val;
        if (val < P->data) {
            P->left = n;
        }
        if (val > P->data) {
            P->right = n;
        }
        return 0;
    }

    if (val < T->data)
        sInsert(T->left, val, T);
    else if (val > T->data)
        sInsert(T->right, val, T);
    else
        return 0;
}

static BiTree preBST = NULL;
int sBST(BiTree T)
{
    if (!T)
        return TRUE;
    if (!sBST(T->left))
        return FALSE;

    if (preBST && (preBST->data > T->data)) {
        return FALSE;
    }
    preBST = T;

    if (!sBST(T->right))
        return FALSE;

    return TRUE;
}

int sPaths(BiTree T, int a[], int n)
{
    int i;
    int array[64];
    if (!T)
        return FALSE;

    if ((NULL == T->left) && (NULL == T->right)) {
        printf("\nPath: ");
        for (i = 0; i < n; i++) {
            printf("%2d-> ", a[i]);
        }
        printf("%2d\n", T->data);
    } else {
        memcpy(array, a, sizeof(int)*n);
        array[n] = T->data;
        n++;
        sPaths(T->left, array, n);
        sPaths(T->right, array, n);
    }

    return FALSE;
}

int sVerify()
{
#if 0
             9
           /    \
        2        11
       / \      /  \
     5    1   31    6
    / \  / \  /\   / \
   N  9 7  N N  N 4  N
#endif
    BiTree T;
    int array[128] = {9,2,5,0,9,0,0,1,7,0,0,0,11,31,0,0,6,4,0,0,0};
    globalArgs = array;
    globalIndex = 0;

    initTree(&T);

    printf("maximum hight: %d\n", sMaxHight(T));
    printf("minimum hight: %d\n", sMinHight(T));
    printf("total nodes: %d\n", sNodeNo(T));
    printf("total leafs: %d\n", sLeafs(T));
    printf("nodes: %d in level:%d\n", sNodeInLevel(T, 4, 1));
    printf("is balanced? %d\n", sIsB(T));
    printf("is complete tree? %d\n", sComplete(T));
    printf("is equal? %d\n", sIsEqual(T, T));
    printf("is equal? %d\n", sIsEqual(T->left, T));
    printf("is mirror? %d\n", sIsMirror(T, T));
    sCommonParent(T, 9, 4);
    printf("Common node: %d\n", gCommonNode);
    sPreTrans(T);
    sMidTrans(T);
    int a[64] = {0};
    sPaths(T, a, 0);

#if 0
             9
           /    \
        2        11
       / \      /  \
     N    N   N     N
#endif
    BiTree T0;
    int array0[128] = {9,2,0,0,11,0,0};
    globalArgs = array0;
    globalIndex = 0;

    initTree(&T0);
    sInsert(T0, 10, NULL);
    sPreTrans(T0);
    sMidTrans(T0);
    preBST = NULL;
    printf("is BST? %d\n", sBST(T0));
    preBST = NULL;
    printf("is BST? %d\n", sBST(T));
    return 0;
}

int main(int argc, char *argv[])
{
    //verifyInitRelease();
    //verifyTrans();
    //verifyCmp();
    //verifyLevelTrans();
    //verifyHight();
    //verifyMirror();
    //verifyCommon();
    //verifySearchNode();
    sVerify();

    return 0;
}
