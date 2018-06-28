#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

#define LENGTH 20

int main()
{  
    
    while (1) {
        char cmd[LENGTH] = {0}, ins[LENGTH] = {0}, obj[LENGTH]={0};
        printf("> ");
        fgets(cmd, LENGTH, stdin);

        if (strncmp(ins, "create", 7) == 0) {
            printf("Create a file\n");
        }
        else if (strncmp(ins, "delete", 7)) {
            printf("Delete a file\n");
        }
    }

    return 0;
}
