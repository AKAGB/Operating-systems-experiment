#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() 
{
    pid_t pid;
    if ((pid=fork()) == 0) {
        printf("Child(Before setsid): PID = %d, PGID = %d, SID = %d\n", getpid(), getpgid(0), getsid(0));
        sleep(10);
        setsid();
        printf("Child(After setsid): PID = %d, PGID = %d, SID = %d\n", getpid(), getpgid(0), getsid(0));
    } else {
        printf("Parent: PID = %d, PGID = %d, SID = %d\n", getpid(), getpgid(0), getsid(0));
    }

    sleep(20);

    return 0;
}