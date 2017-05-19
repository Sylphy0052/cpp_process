#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void parent(int fildes[2]) {
    char *p, c;
    close(fildes[0]);
    p = "hello\n";
    while(*p) {
        c = *p++;
        write(fildes[1], &c, 1);
    }
    close(fildes[1]);
}

void child(int fildes[2]) {
    char c;
    close(fildes[1]);
    while(read(fildes[0], &c, 1) > 0) {
        write(1, &c, 1);
    }
    close(fildes[0]);
}

int main(void) {
    int fildes[2];
    // UNIXおよびPOSIX準拠システム(Linuxなど)のC/C++で使われる,プロセスIDを表わす型.
    pid_t pid;

    // pipe():パイプを生成する
    // 処理が成功したら0，エラーなら-1を返す
    // 引数のpipefd[2]のpipefd[0]がパイプの読み出し側で,pipefd[1]がパイプの書き込み側
    // 例えば,親プロセスから子プロセスにデータを送る場合,親プロセスはpipefd[1]を使ってデータを出力し,子プロセスはpipefd[0]を使ってデータを入力する.
    if(pipe(fildes) == -1) {
        perror("pipe");
        exit(1);
    }
    if((pid = fork()) == 0) {
        child(fildes);
    } else if(pid > 0) {
        parent(fildes);
    } else {
        perror("fork");
        exit(1);
    }
}
