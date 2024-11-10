#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
    pid_t child1, child2, child3;
    int a= 10 , b=20;
    printf("Parent Process Started\n");
    child1 = fork();
    if(child1 == 0){
        printf("Child pid= %d, Performing addition = %d+%d=%d\n", getpid(), a, b, a+b);
        exit(0);
    }
    child2 = fork();
    if(child2 == 0){
        printf("Child pid= %d, Performing multiplication = %d*%d=%d\n", getpid(), a , b, a*b);
        exit(0);
    }
    child3 = fork();
    if(child3==0){
        printf("Child pid= %d, Performing subtraction = %d*%d=%d\n", getpid(), b, a, b-a);  
        exit(0);     
    }

    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);
    waitpid(child3, NULL, 0);

}