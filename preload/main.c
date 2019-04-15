#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void)
{
    srand (time(NULL));
    int i = 10;
    while (i--) {
        printf("%2d ", rand()%100);
    }
    printf("\n");
    return 0;
}
