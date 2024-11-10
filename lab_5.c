#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

int signal_received = 0;
void signal_handler(int sig){
    signal_received = sig;
}

void * func_1(void *arg){
    pthread_t thread2 = *(pthread_t *)arg;
    sleep(1);
    printf("Thread 1: sending signal to thread 2\n");
    pthread_kill(thread2, SIGUSR1);

    return NULL;
}
void * func_2(void *arg){
    printf("Thread 2: waiting for Signal\n");
    signal(SIGUSR1, signal_handler);
    pause();
    printf("Thread 2: Signal received: %d\n", signal_received);
    printf("Thread 2: Signal Handling complete\n");

    return NULL;
}

int main(){
    pthread_t thread1, thread2;
    pthread_create(&thread2, NULL, func_2, NULL);
    pthread_create(&thread1, NULL, func_1, &thread2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}