#include <stdio.h>
#include <string.h>

int stack_smashing(char* input){
    char buffer[4];
    strcpy(buffer, input);
    printf("Buffer contain: %s", buffer);
}

int main(int argc, char* argv[] ){
    stack_smashing(argv[1]);
    printf("Return to main function\n");
}