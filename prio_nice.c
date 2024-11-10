#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
    int core = sched_getcpu();
    int priority = getpriority(PRIO_PROCESS,0);
    printf("Core: %d Priority: %d\n",core, priority);
    setpriority(PRIO_PROCESS, 0, 2);
    nice(15);
    priority = getpriority(PRIO_PROCESS, 0);
    printf("core: %d Priority: %d\n", core, priority);
    setpriority(PRIO_PROCESS, 0, 19);
    printf("core: %d Priority: %d\n", core, getpriority(PRIO_PROCESS, 0));
    nice(-2);
    printf("core: %d Priority: %d\n", core, getpriority(PRIO_PROCESS, 0));
}
