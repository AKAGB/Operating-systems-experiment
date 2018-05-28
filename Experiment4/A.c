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

void quit_parent(int sig) {
    // 父进程关闭队列后退出
    msgctl(msgqid1, IPC_RMID,0);
    exit(0);
}

void quit_child(int sig) {
    // 父进程关闭队列后退出
    msgctl(msgqid2, IPC_RMID,0);
    exit(0);
}

int main()
{
    pid_t pid;
    if ((pid=fork()) == 0) {
        // 子进程rcv
        signal(SIGINT, quit_child);
        msgqid2 = msgget(MSGKEY2, 0777|IPC_CREAT);
        do {
            msgrcv(msgqid2, &msg2, sizeof(msg2), 0, 0);
            printf("(Process A) received: %s\n", msg2);
        }while(strcmp(msg2, quit) != 0);
        msgctl(msgqid2, IPC_RMID,0);

        // 结束父进程
        kill(getppid(), SIGINT);

        exit(0);
    }
    else {
        // 父进程snd
        signal(SIGINT, quit_parent);
        msgqid1 = msgget(MSGKEY1, 0777|IPC_CREAT);
        do {
            scanf("%s", msg1);
            printf("(Process A) sent: %s\n", msg1);
            msgsnd(msgqid1, &msg1, sizeof(msg1), 0);
        } while(strcmp(msg1, quit) != 0);
        msgctl(msgqid1, IPC_RMID,0);
        
        // 结束子进程
        kill(pid, SIGINT);
    }
    return 0;
}