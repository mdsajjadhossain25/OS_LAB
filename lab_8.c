#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

int * fib;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * gen_fibo(void *arg){
    int cnt = *(int*)arg;
    pthread_mutex_lock(&mutex);
    fib[0] = 0;
    if(cnt>1){
        fib[1] = 1;
        for(int i=2; i<cnt; i++){
            fib[i] = fib[i-1] + fib[i-2];
        }
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char *argv[]){
    int cnt = atoi(argv[1]);
    printf("%d\n", cnt);
    fib = (int*)malloc(cnt*sizeof(int));

    pthread_t thread;
    pthread_create(&thread, NULL, gen_fibo, &cnt);

    pthread_join(thread, NULL);

    for(int i=0; i<cnt; i++){
        printf("%d ", fib[i]);
    }
    printf("\n");
    free(fib);
    pthread_mutex_destroy(&mutex);
}