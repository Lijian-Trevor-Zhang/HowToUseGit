#include <stdio.h>
#include <dlfcn.h>

int (*saySomething)(const char *name);

int main()
{
    printf("Hello World: ->\n");
    //void *phandle = dlopen("/home/lijian/task/C/library/sayhi/libsay.so", RTLD_LAZY);
    void *phandle = dlopen("./sayhi/libsay.so", RTLD_LAZY);
    saySomething = dlsym(phandle, "sayHi");
    saySomething("Lijian.Zhang");
    saySomething = dlsym(phandle, "sayBye");
    saySomething("Lijian.Zhang");
    dlclose(phandle);
    return 0;
}
