#include "splitter.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

char **cpy_argv;
int cpy_argc;
char *divider;
int k = 0;

void set_array(int argc, const char *argv[]) {
    cpy_argv = malloc(argc * sizeof(char*));
    cpy_argc = argc;
    for (int i=0; i<argc; i++) {
        cpy_argv[i] = strdup(argv[i]);
    }
}

void set_delimiter(const char *d) {
    divider = strdup(d);
}

int next_block(int *begin, int *end) {
    if (k > cpy_argc) { return 1; }
    
    for (int i = k; i <= cpy_argc; ++i)
    {
        if ((i == cpy_argc) || (strcmp(cpy_argv[i], divider) == 0))
        {
            *begin = k;
            *end = i;
            k = i+1;
            break;
        }
    }
    return 0;
}

void free_splitter(void) {
    for (int i=0; i < cpy_argc; ++i) {
        free(cpy_argv[i]);
    }
    free(cpy_argv);
    free(divider);
    cpy_argc = 0;
    k = 0;
}