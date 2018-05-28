#include <sys/types.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#define MSGKEY1 75
#define MSGKEY2 76

char msg1[1024];
char msg2[1024];

int msgqid1;
int msgqid2;

const char *quit = "quit";

int main() 
{
    pid_t pid;
    if ((pid=fork()) == 0) {
        // 子进程rcv
        msgqid1 = msgget(MSGKEY1, 0777);
        do {
            msgrcv(msgqid1, &msg1, sizeof(msg1), 0, 0);
            printf("(Process B) received: %s\n", msg1);
        }while(strcmp(msg1, quit) != 0);

        // 结束父进程
        kill(getppid(), SIGINT);
        exit(0);
    }
    else {
        // 父进程snd
        msgqid2 = msgget(MSGKEY2, 0777);
        do {
            scanf("%s", msg2);
            printf("(Process B) sent: %s\n", msg2);
            msgsnd(msgqid2, &msg2, sizeof(msg2), 0);
        } while(strcmp(msg2, quit) != 0);
        
        // 结束子进程
        kill(pid, SIGINT);
    }
    return 0;
}