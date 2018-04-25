#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
    pid_t pid;
    printf("Before fork() or vfork(), pid = %d\n",getpid());
    for(int i=0;i<3;i++) {
        /*fork() or vfork()*/
        vfork();
        printf("%d: pid = %d\n",i,getpid());
    }
    exit(0);
}
