#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void func()
{
    int a = 5;
    vfork();
    printf("a = %d\n", a);
    return;
}

int main() 
{
    printf("Main\n");
    func();
    printf("Main end\n");
    return 0;
}
