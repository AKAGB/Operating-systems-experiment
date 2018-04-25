#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    pid_t pid;
    printf("Thank you. Are you OK?\n");
    printf("Hello. Thank you. Thank you very much.");
    printf("\n");
    pid = fork();
    if(pid>0) {
        int state = 0;
        printf("HeHello. Thank you. Thank you very much.\n");
        printf("1");
        printf("2");
        wait(&state);
    } else {
        printf("How are you Indian Mi fans? Do you like Mi 4i?\n");
        printf("");
        exit(0);
    }
}
