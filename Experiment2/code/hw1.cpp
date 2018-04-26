#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void func()
{
    printf("func\n");
    pid_t pid;
    if ((pid=vfork()) == 0) {
        printf("child process\n");
        exit(0);
    } else {
        printf("Child pid = %d\n", pid);
    }
    printf("func end\n");
}

int main() 
{
    printf("Main\n");
    func();
    //int i = 2;
    // printf("1");
    // printf("2");
    // printf("3");
    printf("Main end\n");
    exit(0);
}