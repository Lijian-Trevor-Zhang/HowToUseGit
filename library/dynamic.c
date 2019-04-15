#include <stdio.h>
#include "sayhi.h"
#include "saybye.h"


char *showCompany(void)
{
    static char *arm = "Arm Co, Ltd.";
    return arm;
}

int main()
{
    printf("Hello World: ->\n");
    sayHi("Lijian.Zhang");
    sayBye("Lijian.Zhang");
    return 0;
}
