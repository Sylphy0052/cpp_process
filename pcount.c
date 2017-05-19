/*
Process
メモリは独立
 */

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int val = 0;

void run(const char *name) {
    for(int i = 0; i < 5; ++i) {
        printf("%s:%d\n", name, ++val);
        sleep(1);
    }
}

int main(void) {
    int status;
    int pid, wait_pid;

    // fork関数は呼び出し元プロセスを複製して,子プロセス（新しいプロセス）を生成する
    // fork関数を呼び出した（実行した）プロセスを親プロセス，新しく生成したプロセスを子プロセスと呼んでいる．
    // 子プロセスにはユニークなプロセスIDが付与される
    pid = fork();

    // 子プロセスのpidが0なら，runする
    // pidが0になるのは処理が成功した時
    // 失敗すると-1を返す
    
    // 子プロセスはfork関数実行時点の親プロセスの複製（コピー）だから，オープン済みのファイルや変数は子プロセスにそのまま引き継ぎつぐ．
    // そのため，それらは子プロセスで引き続き使うことができる
    if(pid == 0) {
        run("child");
        exit(0);
    }

    printf("parent, child is %d\n", pid);
    run("parent");

    return 0;
}
