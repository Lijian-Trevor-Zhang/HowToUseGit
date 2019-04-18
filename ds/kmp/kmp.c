#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 常规模式匹配函数
int strstr_n (char *s, int s_n, char *p, int p_n)
{
    int i = 0, j = 0;
    while ((i < s_n) && (j < p_n)) {
        if (s[i] == p[j]) {
            i++;
            j++;
        } else {
            i = (i-j+1);
            j = 0;
        }
    }
    if (j == p_n) {
        return (i-j);
    } else {
        return -1;
    }
}

// KMP优化后的模式匹配算法
int getNext (char *p, int p_n, int next[])
{
    int j, k;
    j = 0;
    k = -1;
    next[j] = k;
    while (j < p_n) {
        if ((k==-1) || (p[j]==p[k])) {
            j++; k++;
            next[j] = k;
        } else {
            k = next[k];
        }
    }
    return 0;
}

int strstr_optimize (char *s, int s_n, char *p, int p_n)
{
    int i = 0, j = 0;
    int next[256] = {0};
    getNext (p, p_n, next);
    while ((i < s_n) && (j < p_n)) {
        if ((-1==j) || (s[i]==p[j])) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    if (j == p_n)
        return (i-j);
    else
        return -1;
}

int Verify (void)
{
    int pos;
    char *s = "goodgoogle";
    char *p = "goog";
    pos = strstr_n (s, strlen(s), p, strlen(p));
    printf ("%s\n", s+pos);
    pos = strstr_optimize (s, strlen(s), p, strlen(p));
    printf ("%s\n", s+pos);
    return 0;
}

int main (int argc, char *argv[])
{
    Verify();
    return 0;
}
