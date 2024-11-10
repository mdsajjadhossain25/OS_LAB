#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int input_fd, output_fd;
    char buffer[100];
    ssize_t n;

    input_fd = open("input.txt", O_RDONLY);

    output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    n = read(input_fd, buffer, sizeof(buffer) - 1);
    buffer[n] = '\0'; 
    write(output_fd, buffer, strlen(buffer));

    close(input_fd);
    close(output_fd);

    return 0;
}
