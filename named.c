#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(){
    char *fifo_path = "./namedpipe";
    char mssge[] = "Hello from Parent\n";
    char readmsge[100];

    mkfifo(fifo_path, 0666);
    
    pid_t pid = fork();
    
    if(pid==0){
        int fd = open(fifo_path, O_RDONLY);
        read(fd, readmsge, sizeof(readmsge));
        printf("Child recieved mssge: %s", readmsge);
        close(fd);
        exit(0);
    }else{
        int fd = open(fifo_path, O_WRONLY);
        write(fd, mssge, strlen(mssge));
        close(fd);
        wait(NULL);

        unlink(fifo_path);
    }
}