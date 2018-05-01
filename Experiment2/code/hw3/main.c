#include "apue.h"

int main() 
{  
    FILE *fp = fopen("file.txt", "w");
    fprintf(fp, "%d\n", 0);
    fclose(fp);
    pid_t pid;
    int cnt = 1;
    if ((pid=fork()) == 0) {
        cnt++;
        while (1) {
            TELL_WAIT();
            sleep(2);
            WAIT_PARENT();
            printf("Child %d\n", cnt);
            cnt += 2;

            FILE *fp1 = fopen("file.txt", "r+");
            int b;
            fscanf(fp1, "%d", &b);
            b++;
            fseek(fp1, 0, 0);
            fprintf(fp1, "%d\n", b);
            fclose(fp1);

            
            TELL_PARENT(getppid());
        }
        exit(0);
    }
    
    while (1) {
        TELL_WAIT();
        sleep(1);
        printf("Parent %d\n", cnt);

        FILE *fp2 = fopen("file.txt", "r+");
        int a;
        fscanf(fp2, "%d", &a);
        a++;
        fseek(fp2, 0, 0);
        fprintf(fp2, "%d\n", a);
        fclose(fp2);

        cnt += 2;
        TELL_CHILD(pid);
        WAIT_CHILD();
    }
    exit(0);
}