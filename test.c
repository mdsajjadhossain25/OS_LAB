#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/prctl.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s n child_1 child_2 ... child_n\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    pid_t pids[n];

    for (int i = 0; i < n; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            prctl(PR_SET_PDEATHSIG, SIGTERM);
            prctl(PR_SET_NAME, argv[i + 2], NULL, NULL, NULL);
            sleep(10);
            printf("%s (PID: %d)\n", argv[i + 2], getpid());
            exit(0);
        }else{
            // sleep(1);
            wait(NULL);
        }
    }

    printf("parent_process (PID: %d)\n", getpid());

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    return 0;
}
