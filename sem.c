#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>

long long int n  = 0;

sem_t semaphore;


void * func_1(void *arg){
    for(int i=0; i<100000; i++){
        sem_wait(&semaphore);
        n++;
        sem_post(&semaphore);
        printf("Incrementing n: %lld\n", n);
    }
    return NULL;
}
void * func_2(void *arg){
    for (int i = 0; i < 100000; i++)
    {
        sem_wait(&semaphore);
        n--;
        sem_post(&semaphore);
        printf("Decrementing n: %lld\n", n);
    }
    return NULL;
}

int main(){
    sem_init(&semaphore, 0, 1);
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, func_1, NULL);
    pthread_create(&thread2, NULL, func_2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sem_destroy(&semaphore);
}