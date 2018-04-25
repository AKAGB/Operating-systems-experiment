#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    pid_t pid;
    printf("Thank you. Are you OK?\n");
    printf("Hello. Thank you. Thank you very much.");
    pid = fork();
    printf("\n");
if(pid>0) {
        int state = 0;
        sleep(1);
        printf("HeHello. Thank you. Thank you very much.\n");
        wait(&state);
    } else {
        sleep(2);
        printf("How are you Indian Mi fans? Do you like Mi 4i?\n");
        exit(0);
    }
}
