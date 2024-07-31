#include "pipeline.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <wait.h>

char ***commands;
int a = 0, b = 0;

/**
 * Adds array[0], array[1], ..., array[size - 1] as
 * a program arguments to the end of the sequence of programs arguments.
 * Initially the sequence is empty.
 * Terminating null argument is not passed here.
 * Returns 0 if success, non 0 otherwise.
 */

int add_to_pipeline(const char *array[], int size) {    
    if (a == b) {
        if (b == 0) {
            b = 100;
        } else {
            b = 2 * b;
        }
        commands = realloc(commands, b * sizeof *commands);
        if (commands == NULL) {
            return 1;
        }
    }
    
    commands[a] = malloc((size+1) * sizeof(char*));
    if (commands[a] == NULL) {
        return 1;
    }

    for (int i=0; i<size; i++) {
        commands[a][i] = strdup(array[i]);
        if (commands[a][i] == NULL) {
            return 1;
        }
    }
    commands[a][size] = NULL;
    a++;
    return 0;
}

/**
 * Runs the pipeline of the sequence of program arguments.
 * Waits for ending all children processes.
 * Returns 0 if success, non 0 otherwise.
 */
int run_pipeline(void) {
    int fd_next[2] = {0, 1}, fd_prev[2];
    
    for (int i = 0; i < a; ++i)
    {
        // printf("%s\n", commands[i][0]);

        fd_prev[0] = fd_next[0];
        fd_prev[1] = fd_next[1];
        if (i != (a-1))
        {
            int res = pipe(fd_next);
            if (res == -1) {
                return 1;
            }
        }
        
        if (fork() == 0)
        {   
            if (i > 0)
            {
                dup2(fd_prev[0], 0);
                close(fd_prev[0]);
                close(fd_prev[1]);
            }
            if (i != (a-1))
            {
                dup2(fd_next[1], 1);
                close(fd_next[0]);
                close(fd_next[1]);
            }
            execvp(commands[i][0], commands[i]);
            return 0;
        }
        if ((i > 0) || (i == (a-1)))
        {
            close(fd_prev[0]);
            close(fd_prev[1]);
        }
    }

    while(wait(NULL) != -1);
    return 0;
}

/**
 * Frees any resources which is created by pipeline.
 * Must be called after the completion of all operations.
 */
void free_pipeline(void) {
    for (int i=0; i<a; i++) {
        int j = 0;
        while (commands[i][j] != NULL) {
            free(commands[i][j++]);
        }
        free(commands[i]);
    }
    free(commands);
    a = 0; b = 0;
}
