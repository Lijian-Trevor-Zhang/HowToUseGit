#include <stdio.h>

static inline void swap(int *a, int i, int j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
    return;
}

static void printArray(int *a, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf("%2d ", a[i]);
    }
    printf("\n");
    return;
}

int selectSort(int a[], int n)
{
    int i, j, min;
    for (i = 0; i < n; i++) {
        min = i;
        for (j = i+1; j < n; j++) {
            if (a[min] > a[j])
                min = j;
        }
        if (min != i) {
            swap(a, i, min);
        }
    }
    return 0;
}

int bubbleSort(int *a, int n)
{
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = n-1; j > i; j--) {
            if (a[j] < a[j-1])
                swap(a, j, j-1);
        }
    }
    return 0;
}

int insertSort(int *a, int n)
{
    int i, j, tmp;
    for (i = 1; i < n; i++) {
        if (a[i] < a[i-1]) {
            tmp = a[i];
            for (j = i-1; j >= 0; j--) {
                if (tmp < a[j])
                    a[j+1] = a[j];
            }
            a[j+1] = tmp;
        }
    }
    return 0;
}

static int partition(int *a, int s, int e)
{
    int key = a[s];
    while (s < e) {
        while ((s<e) && (key <= a[e])) {
            e--;
        }
        swap(a, e, s);
        while ((s<e) && (key >= a[s])) {
            s++;
        }
        swap(a, e, s);
    }
    return s;
}

int QSort(int *a, int s, int e)
{
    int mid;
    if (s < e) {
    mid = partition(a, s, e);
    QSort(a, s, mid-1);
    QSort(a, mid+1, e);
    }
    return 0;
}

void Merge(int *result, int *tmp, int s, int mid, int e)
{
    int o;
    int i = s;
    int j = mid+1;
    int k = s;
    while((i<=mid) && (j<=e)) {
        if(tmp[i]<tmp[j])
            result[k++] = tmp[i++];
        else
            result[k++] = tmp[j++];
    }
    if (i > mid) {
        for (o = j; o <=e; o++) {
            result[k++] = tmp[o];
        }
    }
    if (j > e) {
        for (o = i; o <= mid; o++) {
            result[k++] = tmp[o];
        }
    }
}

int MSort(int *a, int *result, int s, int e)
{
    int mid;
    int tmp[24];
    if (s==e) {
        result[s] = a[s];
        return 0;
    }
    mid = (s+e)/2;
    MSort(a, tmp, s, mid);
    MSort(a, tmp, mid+1, e);
    Merge(result, tmp, s, mid, e);
    return 0;
}

void HeapAdjust(int *a, int s, int e)
{
    int i, key;
    key = a[s];
    for (i = s*2; i <= e; i*=2) {
        if ((i < e) && (a[i] < a[i+1])) {
            i++;
        }
        if (key >= a[i])
            break;
        a[s] = a[i];
        s = i;
    }
    a[s] = key;
    return;
}

int HeapSort(int *a, int n)
{
    int i;
    printf("OK??\n");
    for (i = n/2; i >= 0; i--) {
        HeapAdjust(a, i, n-1);
        printArray(a, n);
    }
    printf("OK..\n");
    for (i = n-1; i >= 0; i--) {
        swap(a, 0, i);
        HeapAdjust(a, 0, i-1);
    }
    return 0;
}

int main()
{
    int a[] = {10, 23, 21, 9, 5, 99, 65, 23, 14};
    printf("Hello!\n");

//  printArray(a, sizeof(a)/sizeof(a[0]));
//  selectSort(a, sizeof(a)/sizeof(a[0]));
//  printArray(a, sizeof(a)/sizeof(a[0]));
//
//  printArray(a, sizeof(a)/sizeof(a[0]));
//  bubbleSort(a, sizeof(a)/sizeof(a[0]));
//  printArray(a, sizeof(a)/sizeof(a[0]));

//  printArray(a, sizeof(a)/sizeof(a[0]));
//  QSort(a, 0, sizeof(a)/sizeof(a[0]));
//  printArray(a, sizeof(a)/sizeof(a[0]));

//  int result[24] = {10, 23, 21, 9, 5, 99, 65, 23, 14};
//  printArray(a, sizeof(a)/sizeof(a[0]));
//  MSort(a, result, 0, sizeof(a)/sizeof(a[0]) - 1);
//  printArray(result, sizeof(a)/sizeof(a[0]));
//
    printArray(a, sizeof(a)/sizeof(a[0]));
    HeapSort(a, sizeof(a)/sizeof(a[0]));
    printArray(a, sizeof(a)/sizeof(a[0]));
    return 0;
}
