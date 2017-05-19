#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

// void parent(int fildes[2]) {
//     char *p, c;
//     close(fildes[0]);
//     p = "hello\n";
//     while(*p) {
//         c = *p++;
//         write(fildes[1], &c, 1);
//     }
//     close(fildes[1]);
// }
//
// void child(int fildes[2]) {
//     char c;
//     close(fildes[1]);
//     while(read(fildes[0], &c, 1) > 0) {
//         write(1, &c, 1);
//     }
//     close(fildes[0]);
// }

// 小文字の文字列を受け取り，大文字に変換する関数.
// 別スレッドで実行する
// 親プロセスから文字列を与え以下の実行結果を得る
// capitalizeの返り値はvoidであるため，親プロセスに値を返すには受け取ったポインタの中身を書き換える
// 静的な文字列を書き換えようとするとBus Errorもしくはセグメンテーションフォルトが起こる
// スレッドの終了を待つにはthread_joinを利用する
void chapitalized(char *str, int fildes[2]) {
    char c;
    close(fildes[0]);
    while(*str) {
        c = *str++;
        c = toupper(c);
        write(fildes[1], &c, 1);
    }
    close(fildes[1]);
}

void parent(int fildes[2]) {
    char c;
    close(fildes[1]);
    while(read(fildes[0], &c, 1) > 0) {
        write(1, &c, 1);
    }
    write(1, "\n", 1);
    close(fildes[0]);
}

int main(void) {
    char str[] = "abcdefghij";
    char *strp;
    int fildes[2];
    pid_t pid;

    if(pipe(fildes) == -1) {
        perror("pipe");
        exit(1);
    }

    strp = str;

    if((pid = fork()) == 0) {
        chapitalized(strp, fildes);
    } else if(pid > 0) {
        parent(fildes);
    } else {
        perror("fork");
        exit(1);
    }
}
