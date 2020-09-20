/****************************************************
    author: gsc2001
    brief: file with header files
           and global struct definations
*****************************************************/
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#ifndef __GLOBAL_H
#define __GLOBAL_H

#define MAX_LEN 1024

// colors
#define COL_BLU "\033[34;1m"
#define COL_GRN "\033[32;1m"
#define COL_WHT "\033[0m"

#ifdef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

typedef struct Command
{
    int argc;
    char *cmd;
    char **args;
    int bg;
} Command;

typedef struct ParsedCommands
{
    int n;
    Command *commands;
} ParsedCommands;

typedef struct Process
{
    char *name;
    pid_t id;
} Process;

char *HOME;

#endif // __GLOBAL_H