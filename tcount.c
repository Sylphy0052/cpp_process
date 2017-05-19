/*
Thread
メモリ空間を共有
 */

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int val;

void run(const char *name) {
    for(int i = 0; i < 5; ++i) {
        printf("%s:%d\n", name, ++val);
        sleep(1);
    }
}

int main(void) {
    // pthread_tはスレッドのスレッド識別子/スレッドID
    // typedef unsigned long int pthread_t;
    pthread_t thread;
    int iret;

    // int pthread_create(pthread_t * thread, pthread_attr_t * attr, void * (*start_routine)(void *), void * arg);
    // pthread_createは呼び出しスレッドと並行して実行する,新しい制御スレッドを生成する.
    // 新しいスレッドは,argを第1引数とするstart_routineという関数になる.
    // 新しいスレッドは,pthread_exit(3)を呼び出すことによって明示的に終了するか,関数start_routineから返ることで暗黙的に終了する.
    // 後者の場合は,start_routineの終了コードとして返す結果を引数としてpthread_exit(3)を呼び出すことに等しい.
    // 引数attrには,その新しいスレッドに適用するスレッド属性を指定する.
    // スレッド属性に関する完全なリストはpthread_attr_init(3)に見つけることができる.
    // 引数attrはまたNULLをとることができ,その時はデフォルトの属性が用いられる: 生成したスレッドは合流可能で(つまりデタッチされない),デフォルト(つまりリアルタイムではない)のスケジューリング方針になる.

    // 返り値
    // 成功すると新しく作成したスレッドの識別子が引数threadの指す領域へ格納され,0が返る.
    // エラーの場合,非0のエラーコードが返る.
    iret = pthread_create(&thread, NULL, (void*)run, (void*)"child");

    run("parent");
    pthread_join(thread, NULL);
    printf("end\n");
}
