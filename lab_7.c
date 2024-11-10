#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

double average = 0;
int max = 0;
int min = 0;

pthread_mutex_t mutex =  PTHREAD_MUTEX_INITIALIZER;

void * cal_average(void *arg){
    int* numbers = (int*)arg;
    int cnt = numbers[0];
    int total = 0;
    for(int i=1; i<=cnt; i++){
        total += numbers[i];
    }
    pthread_mutex_lock(&mutex);
    average = (double)total / cnt;
    pthread_mutex_unlock(&mutex);

    return NULL;

}

void * find_min(void *arg){
    int* numbers = (int*)arg;
    int cnt = numbers[0];
    int min_value = 10000;
    for(int i=1; i<=cnt; i++){
        if(numbers[i]<min_value){
            min_value = numbers[i];
        }
    }
    pthread_mutex_lock(&mutex);
    min = min_value;
    pthread_mutex_unlock(&mutex);
}


int main(int argc, char* argv[]){
    int cnt = argc - 1;
    int* numbers = (int*)malloc((cnt+1)*sizeof(int));

    numbers[0] = cnt;
    for(int i=1; i<=cnt; i++){
        numbers[i] = atoi(argv[i]);
    }

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, cal_average, (void *)numbers);
    pthread_create(&thread2, NULL, find_min, (void *)numbers);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("The average: %f\n", average);
    printf("The minimum: %d\n", min);


    free(numbers);
    pthread_mutex_destroy(&mutex);

}