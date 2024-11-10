#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

long long int n  = 0;

void * func_1(void *arg){
    for(int i=0; i<100000; i++){
        n++;
        printf("Incrementing n: %lld\n", n);
    }
    return NULL;
}
void * func_2(void *arg){
    for (int i = 0; i < 100000; i++)
    {
        n--;
        printf("Decrementing n: %lld\n", n);
    }
    return NULL;
}

int main(){
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, func_1, NULL);
    pthread_create(&thread2, NULL, func_2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}