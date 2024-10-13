#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Demonstrating exec family system calls\n\n");

    // Fork to create a child process for each exec call
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process

        // 1. execlp()
        printf("1. Demonstrating execlp():\n");
        printf("   This call will execute 'ls -l' using the PATH environment.\n");
        execlp("ls", "ls", "-l", NULL);
        // If execlp() is successful, the code below won't be executed
        perror("execlp");
        exit(1);
    } else {
        // Parent process
        wait(NULL); // Wait for the child to finish

        pid = fork();
        if (pid == 0) {
            // 2. execle()
            printf("\n2. Demonstrating execle():\n");
            printf("   This call will execute 'echo' with a custom environment.\n");
            char *envp[] = {"PATH=/bin:/usr/bin", "TERM=console", NULL};
            execle("/bin/echo", "echo", "Hello from execle!", NULL, envp);
            perror("execle");
            exit(1);
        } else {
            wait(NULL);

            pid = fork();
            if (pid == 0) {
                // 3. execv()
                printf("\n3. Demonstrating execv():\n");
                printf("   This call will execute 'ps aux' using an array of arguments.\n");
                char *args[] = {"ps", "aux", NULL};
                execv("/bin/ps", args);
                perror("execv");
                exit(1);
            } else {
                wait(NULL);

                pid = fork();
                if (pid == 0) {
                    // 4. execvp()
                    printf("\n4. Demonstrating execvp():\n");
                    printf("   This call will execute 'grep root' on '/etc/passwd' using PATH.\n");
                    char *args[] = {"grep", "root", "/etc/passwd", NULL};
                    execvp("grep", args);
                    perror("execvp");
                    exit(1);
                } else {
                    wait(NULL);

                    pid = fork();
                    if (pid == 0) {
                        // 5. execve()
                        printf("\n5. Demonstrating execve():\n");
                        printf("   This call will execute 'env' with a custom environment.\n");
                        char *args[] = {"env", NULL};
                        char *envp[] = {"USER=testuser", "HOME=/home/testuser", NULL};
                        execve("/usr/bin/env", args, envp);
                        perror("execve");
                        exit(1);
                    } else {
                        wait(NULL);
                        printf("\nAll demonstrations completed.\n");
                    }
                }
            }
        }
    }

    return 0;
}
