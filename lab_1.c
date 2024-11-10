#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child1, child2, child3;
    int a = 10, b = 5;

    printf("Parent Process (PID: %d) started.\n", getpid());

    child1 = fork();
    if (child1 == 0) {
        printf("Child 1 (PID: %d) performing addition: %d + %d = %d\n", getpid(), a, b, a + b);
        exit(0);
    }else{
        child2 = fork();
        if (child2 == 0) {
            printf("Child 2 (PID: %d) performing subtraction: %d - %d = %d\n", getpid(), a, b, a - b);
            exit(0);
        }else{
            child3 = fork();
            if (child3 == 0) {
                printf("Child 3 (PID: %d) performing multiplication: %d * %d = %d\n", getpid(), a, b, a * b);
                exit(0);
            }else{
                for (size_t i = 0; i <10000000000; i++){

                }
                waitpid(child1, NULL, 0);
                waitpid(child2, NULL, 0);
                waitpid(child3, NULL, 0);

                printf("Parent Process (PID: %d) completed.\n", getpid());
            }
        }

    }
    return 0;
}