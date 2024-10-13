#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void main() {
    int c = 5;
    pid_t pid = fork();

    if (pid == 0) {
        c += 5;
        // printf("Child: c = %d\n", c);
    } else {
        pid = fork();
        c += 10;
        if(pid) {
            c += 10;
        }
        // printf("Parent: c = %d\n", c);
    }

    fork();
    printf("c = %d\n", c);
}
