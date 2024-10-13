#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_PATH 1024

void print_process_info(const char *pid) {
    char path[MAX_PATH];
    FILE *fp;
    char line[256];
    int ppid = -1, priority = -1;

    // Get parent PID
    snprintf(path, sizeof(path), "/proc/%s/status", pid);
    fp = fopen(path, "r");
    if (fp) {
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "PPid:", 5) == 0) {
                sscanf(line, "PPid:\t%d", &ppid);
                break;
            }
        }
        fclose(fp);
    }

    // Get priority
    snprintf(path, sizeof(path), "/proc/%s/stat", pid);
    fp = fopen(path, "r");
    if (fp) {
        if (fgets(line, sizeof(line), fp)) {
            char *token = strtok(line, " ");
            for (int i = 0; i < 17 && token != NULL; i++) {
                token = strtok(NULL, " ");
            }
            if (token != NULL) {
                priority = atoi(token);
            }
        }
        fclose(fp);
    }

    printf("PID: %s, Priority: %d, Parent PID: %d\n", pid, priority, ppid);
}

int main() {
    DIR *dir;
    struct dirent *ent;

    dir = opendir("/proc");
    if (dir == NULL) {
        perror("Cannot open /proc");
        return 1;
    }

    while ((ent = readdir(dir)) != NULL) {
        if (isdigit(ent->d_name[0])) {
            print_process_info(ent->d_name);
        }
    }

    closedir(dir);
    return 0;
}
