#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <pthread.h>
#include <ctype.h>

#define READ 0
#define WRITE 1

void parent(int *in_fildes, int *out_fildes) {
    char *p, c;
    p = "hello\n";
    close(in_fildes[READ]);
    while(*p) {
        c = *p++;
        write(in_fildes[WRITE], &c, 1);
    }
    close(in_fildes[WRITE]);

    close(out_fildes[WRITE]);
    while(read(out_fildes[READ], &c, 1) > 0) {
        write(1, &c, 1);
    }
    close(out_fildes[READ]);
}

void child(int *in_fildes, int *out_fildes) {
    char c;
    char *p, *str;
    p = str;
    close(in_fildes[WRITE]);
    close(out_fildes[READ]);
    while(read(in_fildes[READ], &c, 1) > 0) {
        c = toupper(c);
        write(out_fildes[WRITE], &c, 1);
    }
    close(in_fildes[READ]);
    close(out_fildes[WRITE]);
}

int main(void) {
    // char str[] = "abcdefghij";
    // char *strp;
    int status;
    int in_fildes[2], out_fildes[2];
    pid_t pid;

    // パイプの生成
    if(pipe(in_fildes) == -1) {
        perror("pipe");
        exit(1);
    }
    if(pipe(out_fildes) == -1) {
        perror("pipe");
        exit(1);
    }
    // 子プロセス
    if((pid = fork()) == 0) {
        child(in_fildes, out_fildes);
    } else if(pid > 0) { // 親プロセス
        parent(in_fildes, out_fildes);
    } else {
        perror("fork");
        exit(1);
    }
}
