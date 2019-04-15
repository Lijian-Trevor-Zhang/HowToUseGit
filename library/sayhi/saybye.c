#include <stdio.h>

extern char *showCompany(void);

int sayBye(const char *name)
{
    // 动态链接库中的函数允许未定义，
    // 比如showCompany()函数允许在调用者文件中进行定义
    //
    // printf("Hi %s (%s), goodbye!\n", name, showCompany());
    printf("Hi %s, goodbye!\n", name);
    return 0;
}
