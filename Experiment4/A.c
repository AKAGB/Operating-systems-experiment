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

struct msgform {
    long mtype;
    char mtext[1000];
} msg1, msg2;

int msgqid1;
int msgqid2;

const char *quit = "quit";

int main()
{
    pid_t pid;
    if ((pid=fork()) == 0) {
        // 子进程rcv
        // while(1) {}
        // printf("ChildA start\n");
        // do {
        //     msgrcv(msgqid1, &msg1, sizeof(msg1),0,0);
        //     printf("(Process A) received: %s\n", msg1.mtext);
        // } while (strcmp(msg1.mtext, quit));
        // msgctl(msgqid1, IPC_RMID, 0);
        // // 结束父进程
        // kill(getppid(), SIGQUIT);
    }
    else {
        // 父进程snd
        msgqid1 = msgget(MSGKEY1, 0777|IPC_CREAT);
        do {
            scanf("%s", msg1.mtext);
            msgsnd(msgqid1, &msg1, sizeof(msg1),0);
            printf("(Process A) sent: %s\n", msg1.mtext);
        } while(strcmp(msg1.mtext, quit) != 0);
    }
    return 0;
}