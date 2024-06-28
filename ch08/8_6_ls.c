#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define BUFSIZE 500

void fsize(char *name);
void directory(char *name);

int main(int argc, char **argv) {
    if (argc == 1) {
        fsize(".");
    } else {
        while (--argc > 0) {
            fsize(*++argv);
        }
    }
    return 0;
}

void fsize(char *name) {
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't find %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        directory(name);
    }
    printf("%8lld %s\n", (long long)stbuf.st_size, name);
}

void directory(char *name) {
    DIR *dp;
    struct dirent *entry;
    char path[BUFSIZE];

    if ((dp = opendir(name)) == NULL) {
        fprintf(stderr, "directory: can't open %s\n", name);
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
        fsize(path);
    }
    closedir(dp);
}

