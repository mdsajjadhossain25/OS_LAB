#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

void * forkthread(void *arg){
    printf("Thread %d started\n", (long)arg);
    pid_t thread1 = fork();
    if(thread1==0){
        printf("thread 1 craeted a child process of pid %d\n", getpid());
        exit(0);
    }else{
        printf("Parent waiting for child to finish its work\n");
        wait(NULL);
    }
    return NULL;
}

void * execfunc(void *arg){
    printf("Thread %d started\n", (long)arg);
    pid_t thread2 = fork();
    if(thread2==0){
        char *args[] = {"./test", NULL};
        execv(args[0], args);
        exit(0);
    }else{
        wait(NULL);
        printf("Parent got control back from exec child call\n");
    }
}

void * exec_new(void *arg){
    printf("Thread %d started\n", (long)arg);
    fork();
    char *args[] = {"./test2", NULL};
    execv(args[0], args);
    printf("Parent2 got controll back\n");
}

int main(){
    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, forkthread, (void * )1);
    pthread_join(tid1, NULL);
    pthread_create(&tid2, NULL, execfunc, (void * )2);
    pthread_join(tid2, NULL);
    pthread_create(&tid3, NULL, exec_new, (void * )3);
    pthread_join(tid3, NULL);
}
