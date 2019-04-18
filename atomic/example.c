#include <stdio.h>
#include <stdint.h>

struct perf {
    int a;
    long ab;
} perf;

int main (void)
{
    uint32_t ptr = 0;
    uint32_t val;

    printf("%d\n", sizeof(long long));
    printf("%d\n", sizeof(long));

//  if (__atomic_always_lock_free (16, 0)) {
//      printf("16 is lock free\n");
//  }
    if ( __atomic_always_lock_free ((sizeof (struct perf)), 0)) {
        printf("double float is lock free\n");
    }
    if (__atomic_always_lock_free (sizeof (long long), 0)) {
        printf("long long is lock free\n");
    }
    if (__atomic_always_lock_free (sizeof (long), 0)) {
        printf("long is lock free\n");
    }
    if (__atomic_always_lock_free (sizeof (int), 0)) {
        printf("int is lock free\n");
    }
    if (__atomic_always_lock_free (sizeof (short), 0)) {
        printf("short is lock free\n");
    }
    if (__atomic_always_lock_free (sizeof (char), 0)) {
        printf("char is lock free\n");
    }
    return 0;
}
