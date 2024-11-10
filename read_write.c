#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int main(){
    char * msge, buffer[100];
    int n;
    msge = "Insert a string: ";
    write(STDOUT_FILENO, msge, strlen(msge)+1);
    n = read(STDIN_FILENO, &buffer, sizeof(buffer));
    buffer[n] = '\0';
    write(STDOUT_FILENO, buffer, strlen(buffer));
}