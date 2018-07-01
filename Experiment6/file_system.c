#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>

#define LENGTH 100

void list_info(struct dirent *dirp, char *path) {
    struct stat buf;
    char tmpBuf[LENGTH];
    char now[LENGTH] = {0};
    getcwd(now, LENGTH);
    chdir(path);
    if (stat(path, &buf) == -1) {
        printf("error!\n");
        exit(1);
    }

    strftime(tmpBuf, LENGTH, "%F %T", localtime(&buf.st_mtime));

    if (dirp->d_type == 4) printf("Dir\t");
    else printf("File\t");

    printf("%d\t", buf.st_size);
    printf("%s\t", tmpBuf);
    printf("%s\n", dirp->d_name);
    chdir(now);
}

int main()
{  
    
    while (1) {
        char cmd[LENGTH]={0}, ins[LENGTH]={0}, obj[LENGTH]={0};
        int fd;
        DIR *dirptr;
        struct dirent *dirp;

        printf("> ");
        fgets(cmd, LENGTH, stdin);
        sscanf(cmd, "%s %s", ins, obj);
        // printf("cmd = %s\nins = %s\nobj = %s\n", cmd, ins, obj);

        if (strcmp(ins, "create") == 0) {
            // 创建文件
            // printf("Create a file\n");
            if ((fd = open(obj, O_RDONLY)) != -1) {
                // printf("fd = %d, File exist\n", fd);
                printf("The file %s already exists.\n", obj);
                close(fd);
            }
            else {
                // printf("fd = %d, No such file\n", fd);
                fd = open(obj, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | S_IROTH);
                close(fd);
            }
        }
        else if (strcmp(ins, "delete") == 0) {
            // 删除文件
            if ((fd = open(obj, O_RDONLY)) != -1) {
                // printf("fd = %d, File exist\n", fd);
                close(fd);
                remove(obj);
            }
            else {
                // printf("fd = %d, No such file\n", fd);
                printf("The file %s does not exists.\n", obj);
            }
        }
        else if (strcmp(ins, "mkdir") == 0) {
            // 创建目录
            if ((dirptr = opendir(obj)) == NULL) {
                mkdir(obj, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
            }
            else {
                closedir(dirptr);
                printf("The dir %s already exists.\n", obj);
            }
        }
        else if (strcmp(ins, "rmdir") == 0) {
            // 删除目录
            if ((dirptr = opendir(obj)) == NULL) {
                printf("The dir %s does not exists.\n", obj);
            }
            else {
                closedir(dirptr);
                rmdir(obj);
            }
        }
        else if (strcmp(ins, "list") == 0) {
            if (strlen(obj) == 0) sprintf(obj, "%c", '.');
            if ((dirptr = opendir(obj)) == NULL) {
                printf("The dir %s does not exists.\n", obj);
            } 
            else {
                while ((dirp = readdir(dirptr)) != NULL) {
                    // printf("%s\n", dirp->d_name);
                    list_info(dirp, obj);
                }
                closedir(dirptr);
            }
        }
        else {
            if (strlen(cmd) != 1) printf("No such command\n");
        }
    }

    return 0;
}
