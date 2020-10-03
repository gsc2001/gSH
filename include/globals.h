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
#include <fcntl.h>

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

// The basic struct of command
// cmd args1 args2 <inp > out ... &
typedef struct Command
{
    int argc;
    char *cmd;
    char **args;
    int bg;

    // for inp and out redirection
    char *inp;
    char *out;

    // is out for appending ?
    int append;
} Command;

// piped commands
// cmd1 | cmd 2 | cmd 3
typedef struct PipedCommands
{
    int n;
    Command *commands;
} PipedCommands;

// commands broken into PipedCommands (break on ;)
// pipe1; pipe2
typedef struct ParsedCommands
{
    int n;
    PipedCommands *piped;
} ParsedCommands;

typedef struct Process
{
    char *name;
    pid_t id;
} Process;

char *HOME;

// global stdin and stdout save
int stdoutSaveGlobal;

char *lastDir;

#endif // __GLOBAL_H