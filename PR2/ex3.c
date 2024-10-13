#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

        pid_t pid = fork();

        if (pid == 0) {
        // Child process
            printf("Niko Juja\n");
        } else {
        // Parent process
            sleep(1);
            printf("ICS2305 ni softlife\n");
        }

        return 0;
}
